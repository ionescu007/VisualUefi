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
// Custom Driver Protocol
//
#include "../UefiDriver/drvproto.h"
EFI_GUID gEfiSampleDriverProtocolGuid = EFI_SAMPLE_DRIVER_PROTOCOL_GUID;

//
// We run on any UEFI Specification
//
extern CONST UINT32 _gUefiDriverRevision = 0;

//
// Our name
//
CHAR8 *gEfiCallerBaseName = "UefiApplication";

EFI_STATUS
EFIAPI
UefiUnload (
    IN EFI_HANDLE ImageHandle
    )
{
    //
    // This code should be compiled out and never called
    //
    ASSERT(FALSE);
}

EFI_STATUS
EFIAPI
UefiMain (
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE* SystemTable
    )
{
    EFI_STATUS efiStatus;
    EFI_SAMPLE_DRIVER_PROTOCOL* sampleProtocol;

    //
    // Print stuff out
    //
    Print(L"Hello World! My handle is %lx and System Table is at %p\n",
          ImageHandle, SystemTable);

    //
    // Check if the sample driver is loaded
    //
    efiStatus = gBS->LocateProtocol(&gEfiSampleDriverProtocolGuid, NULL, &sampleProtocol);
    if (EFI_ERROR(efiStatus))
    {
        goto Exit;
    }

    //
    // Print the value and exit
    //
    Print(L"Sample driver is loaded: %lx\n", sampleProtocol->SampleValue);
    efiStatus = EFI_SUCCESS;

Exit:
    return efiStatus;
}

