//
// We support unload (but deny it)
//
const UINT8 _gDriverUnloadImageCount = 1;

//
// We require at least UEFI 2.0
//
const UINT32 _gUefiDriverRevision = 0x200;

//
// Our name
//
CHAR8 *gEfiCallerBaseName = "FtdiUsbSerialDxe";

EFI_STATUS
EFIAPI
FtdiUsbSerialUnload (
    IN EFI_HANDLE  ImageHandle
    );

EFI_STATUS
EFIAPI
FtdiUsbSerialEntryPoint (
    IN EFI_HANDLE        ImageHandle,
    IN EFI_SYSTEM_TABLE  *SystemTable
    );

EFI_STATUS
EFIAPI
UefiUnload (
    IN EFI_HANDLE ImageHandle
    )
{
    return FtdiUsbSerialUnload(ImageHandle);
}

EFI_STATUS
EFIAPI
UefiMain (
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
    )
{
    return FtdiUsbSerialEntryPoint(ImageHandle, SystemTable);
}

