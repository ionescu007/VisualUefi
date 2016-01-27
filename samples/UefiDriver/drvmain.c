#include "drv.h"

//
// We support unload (but deny it)
//
const UINT8 _gDriverUnloadImageCount = 1;

//
// We require at least UEFI 2.0
//
const UINT32 _gUefiDriverRevision = 0x200;
const UINT32 _gDxeRevision = 0x200;

//
// Our name
//
CHAR8 *gEfiCallerBaseName = "UefiDriver";

EFI_STATUS
EFIAPI
UefiUnload (
    IN EFI_HANDLE ImageHandle
    )
{
    //
    // Do not allow unload
    //
    return EFI_ACCESS_DENIED;
}

EFI_STATUS
EFIAPI
UefiMain (
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
    )
{
    EFI_STATUS efiStatus;

    //
    // Install required driver binding components
    //
    efiStatus = EfiLibInstallDriverBindingComponentName2(ImageHandle,
                                                         SystemTable,
                                                         &gDriverBindingProtocol,
                                                         ImageHandle,
                                                         &gComponentNameProtocol,
                                                         &gComponentName2Protocol);
    return efiStatus;
}

