//
// We require at least UEFI 2.0
//
const UINT32 _gUefiDriverRevision = 0x200;

//
// Our name
//
CHAR8 *gEfiCallerBaseName = "Cryptest";

EFI_STATUS
EFIAPI
CryptestMain (
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE* SystemTable
    );

EFI_STATUS
EFIAPI
UefiUnload (
    IN EFI_HANDLE ImageHandle
    )
{
    //
    // This code should be compiled out and never called
    //

}

EFI_STATUS
EFIAPI
UefiMain (
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
    )
{
    return CryptestMain(ImageHandle, SystemTable);
}
