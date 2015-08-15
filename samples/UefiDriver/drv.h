//
// Basic UEFI Libraries
//
#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>

//
// Boot and Runtime Services
//
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>

//
// PCI Protocol
//
#include <Protocol/PciIo.h>
#include <IndustryStandard/Pci.h>

//
// Custom Driver Protocol
//
#include "drvproto.h"

//
// Device Extension for our Device
//
#define DEVICE_EXTENSION_SIGNATURE          SIGNATURE_32('S','M','P','L')
#define DEVICE_EXTENSION_FROM_PROTOCOL(a)   CR(a, DEVICE_EXTENSION, DeviceProtocol, DEVICE_EXTENSION_SIGNATURE)
typedef struct _DEVICE_EXTENSION
{
    UINTN Signature;
    EFI_SAMPLE_DRIVER_PROTOCOL DeviceProtocol;
    EFI_HANDLE DeviceHandle;
    EFI_PCI_IO_PROTOCOL* PciIo;
} DEVICE_EXTENSION, *PDEVICE_EXTENSION;

//
// Name Routines
//
EFI_STATUS
EFIAPI
SampleComponentNameGetControllerName (
    IN EFI_COMPONENT_NAME_PROTOCOL *This,
    IN EFI_HANDLE ControllerHandle,
    IN EFI_HANDLE ChildHandle OPTIONAL,
    IN CHAR8 *Language,
    OUT CHAR16 **ControllerName
);

EFI_STATUS
EFIAPI
SampleComponentNameGetDriverName (
    IN EFI_COMPONENT_NAME_PROTOCOL *This,
    IN CHAR8 *Language,
    OUT CHAR16 **DriverName
);

//
// PnP Routines
//
EFI_STATUS
EFIAPI
SampleDriverSupported (
    IN EFI_DRIVER_BINDING_PROTOCOL *This,
    IN EFI_HANDLE Controller,
    IN EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath
);

EFI_STATUS
EFIAPI
SampleDriverStart (
    IN EFI_DRIVER_BINDING_PROTOCOL *This,
    IN EFI_HANDLE Controller,
    IN EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath
);

EFI_STATUS
EFIAPI
SampleDriverStop (
    IN EFI_DRIVER_BINDING_PROTOCOL* This,
    IN EFI_HANDLE Controller,
    IN UINTN NumberOfChildren,
    IN EFI_HANDLE* ChildHandleBuffer
);

extern EFI_DRIVER_BINDING_PROTOCOL gDriverBindingProtocol;
extern EFI_COMPONENT_NAME2_PROTOCOL gComponentName2Protocol;
extern EFI_COMPONENT_NAME_PROTOCOL gComponentNameProtocol;

