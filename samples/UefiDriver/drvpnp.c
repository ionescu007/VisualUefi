#include "drv.h"

//
// EFI Driver Binding Protocol
//
EFI_DRIVER_BINDING_PROTOCOL gDriverBindingProtocol =
{
    SampleDriverSupported,
    SampleDriverStart,
    SampleDriverStop,
    10,
    NULL,
    NULL
};

//
// Our custom GUID
//
EFI_GUID gEfiSampleDriverProtocolGuid = EFI_SAMPLE_DRIVER_PROTOCOL_GUID;

EFI_STATUS
EFIAPI
SampleDriverSupported (
    IN EFI_DRIVER_BINDING_PROTOCOL *This,
    IN EFI_HANDLE Controller,
    IN EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath
    )
{
    EFI_STATUS efiStatus;
    EFI_PCI_IO_PROTOCOL* pciIo;

    //
    // Assume failure
    //
    pciIo = NULL;
    efiStatus = EFI_UNSUPPORTED;

    //
    // Make sure the controller has a device path (meaning it could be hardware
    // or an image)
    //
    efiStatus = gBS->OpenProtocol(Controller,
                                  &gEfiDevicePathProtocolGuid,
                                  NULL,
                                  This->DriverBindingHandle,
                                  Controller,
                                  EFI_OPEN_PROTOCOL_TEST_PROTOCOL);
    if (EFI_ERROR(efiStatus))
    {
        goto Exit;
    }

    //
    // Make sure the controller implements a PCI I/O protocol. Otherwise, this
    // is not a PCI device
    //
    efiStatus = gBS->OpenProtocol(Controller,
                                  &gEfiPciIoProtocolGuid,
                                  (VOID**)&pciIo,
                                  This->DriverBindingHandle,
                                  Controller,
                                  EFI_OPEN_PROTOCOL_BY_DRIVER);
    if (EFI_ERROR(efiStatus))
    {
        pciIo = NULL;
        goto Exit;
    }

    //
    // Attach to all PCI devices
    //
    efiStatus = EFI_SUCCESS;

Exit:
    //
    // If we had a PCI I/O protocol open, close it now to avoid a leak
    //
    if (pciIo != NULL)
    {
        gBS->CloseProtocol(Controller,
                           &gEfiPciIoProtocolGuid,
                           This->DriverBindingHandle,
                           Controller);
    }

    //
    // Return back to DXE
    //
    return efiStatus;
}

EFI_STATUS
EFIAPI
SampleDriverStop (
    IN EFI_DRIVER_BINDING_PROTOCOL* This,
    IN EFI_HANDLE Controller,
    IN UINTN NumberOfChildren,
    IN EFI_HANDLE* ChildHandleBuffer
    )
{
    EFI_STATUS efiStatus;
    BOOLEAN allChildrenStopped;
    UINTN i;
    PDEVICE_EXTENSION deviceExtension;
    PEFI_SAMPLE_DRIVER_PROTOCOL sampleDriverProtocol;

    //
    // Complete all outstanding transactions to Controller.
    // Don't allow any new transaction to Controller to be started.
    //
    if (NumberOfChildren == 0)
    {
        efiStatus = gBS->CloseProtocol(Controller,
                                       &gEfiPciIoProtocolGuid,
                                       This->DriverBindingHandle,
                                       Controller);
        goto Exit;
    }

    //
    // Enumerate all children
    //
    allChildrenStopped = TRUE;
    for (i = 0; i < NumberOfChildren; i++)
    {
        //
        // Children should have our protocol installed
        //
        efiStatus = gBS->OpenProtocol(ChildHandleBuffer[i],
                                      &gEfiSampleDriverProtocolGuid,
                                      (VOID**)&sampleDriverProtocol,
                                      This->DriverBindingHandle,
                                      Controller,
                                      EFI_OPEN_PROTOCOL_GET_PROTOCOL);
        if (EFI_ERROR(efiStatus))
        {
            allChildrenStopped = FALSE;
            continue;
        }

        //
        // Get the device extension for this child device
        //
        deviceExtension = DEVICE_EXTENSION_FROM_PROTOCOL(sampleDriverProtocol);

        //
        // Close the PCI I/O protocol off the child device
        //
        efiStatus = gBS->CloseProtocol(Controller,
                                       &gEfiPciIoProtocolGuid,
                                       This->DriverBindingHandle,
                                       ChildHandleBuffer[i]);
        if (EFI_ERROR(efiStatus))
        {
            allChildrenStopped = FALSE;
            continue;
        }

        //
        // Uninstall our own protocol off this child device 
        //
        efiStatus = gBS->UninstallMultipleProtocolInterfaces(ChildHandleBuffer[i],
                                                             &gEfiSampleDriverProtocolGuid,
                                                             &deviceExtension->DeviceProtocol,
                                                             NULL);
        if (EFI_ERROR(efiStatus))
        {
            allChildrenStopped = FALSE;
            continue;
        }

        //
        // Free our device extension
        //
        FreePool(deviceExtension);
    }

    //
    // If any errors happened, then fail the stop request.
    // Otherwise, return success.
    //
    if (allChildrenStopped == FALSE)
    {
        efiStatus = EFI_DEVICE_ERROR;
    }
    else
    {
        efiStatus = EFI_SUCCESS;
    }

Exit:
    //
    // Return back to DXE
    //
    return efiStatus;
}

EFI_STATUS
EFIAPI
SampleDriverStart (
    IN EFI_DRIVER_BINDING_PROTOCOL *This,
    IN EFI_HANDLE Controller,
    IN EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath
    )
{
    EFI_STATUS efiStatus;
    EFI_PCI_IO_PROTOCOL* pciIo, childPciIo;
    PDEVICE_EXTENSION deviceExtension;

    //
    // Assume failure
    //
    pciIo = NULL;
    deviceExtension = NULL;

    //
    // Open the PCI I/O protocol. We know this should succeed because our
    // supported routine already tried this.
    //
    efiStatus = gBS->OpenProtocol(Controller,
                                  &gEfiPciIoProtocolGuid,
                                  (VOID**)&pciIo,
                                  This->DriverBindingHandle,
                                  Controller,
                                  EFI_OPEN_PROTOCOL_BY_DRIVER);
    if (EFI_ERROR(efiStatus))
    {
        pciIo = NULL;
        ASSERT_EFI_ERROR(efiStatus);
        goto Exit;
    }

    //
    // Allocate the device extension
    //
    deviceExtension = AllocateZeroPool(sizeof(*deviceExtension));
    if (deviceExtension == NULL)
    {
        efiStatus = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    //
    // Fill out the key fields
    //
    deviceExtension->PciIo = pciIo;
    deviceExtension->Signature = DEVICE_EXTENSION_SIGNATURE;
    deviceExtension->DeviceHandle = NULL;

    //
    // Fill out custom protocol value
    //
    deviceExtension->DeviceProtocol.SampleValue = This->DriverBindingHandle;

    //
    // Install our custom protocol on top of a new device handle
    //
    efiStatus = gBS->InstallMultipleProtocolInterfaces(&deviceExtension->DeviceHandle,
                                                       &gEfiSampleDriverProtocolGuid,
                                                       &deviceExtension->DeviceProtocol,
                                                       NULL);
    if (EFI_ERROR(efiStatus))
    {
        goto Exit;
    }

    //
    // Bind the PCI I/O protocol between our new device handle and the controller
    //
    efiStatus = gBS->OpenProtocol(Controller,
                                  &gEfiPciIoProtocolGuid,
                                  (VOID**)&childPciIo,
                                  This->DriverBindingHandle,
                                  deviceExtension->DeviceHandle,
                                  EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER);
    if (EFI_ERROR(efiStatus))
    {
        goto Exit;
    }

    //
    // We're all done successfully
    //
    efiStatus = EFI_SUCCESS;

Exit:
    //
    // Do cleanup in case of error
    //
    if (EFI_ERROR(efiStatus))
    {
        //
        // First check if a device extension was allocated
        //
        if (deviceExtension != NULL)
        {
            //
            // If a device handle was created, then uninstall the custom protocol
            //
            if (deviceExtension->DeviceHandle != NULL)
            {
                gBS->UninstallMultipleProtocolInterfaces(&deviceExtension->DeviceHandle,
                                                         &gEfiSampleDriverProtocolGuid,
                                                         &deviceExtension->DeviceProtocol,
                                                         NULL);
            }

            //
            // Free the device extension
            //
            FreePool(deviceExtension);
        }

        //
        // Check if we obtained a PCI I/O protocol
        //
        if (pciIo != NULL)
        {
            //
            // Close it so that we don't leak it
            //
            gBS->CloseProtocol(Controller,
                               &gEfiPciIoProtocolGuid,
                               This->DriverBindingHandle,
                               Controller);
        }
    }

    //
    // All done, return to DXE
    //
    return efiStatus;
}

