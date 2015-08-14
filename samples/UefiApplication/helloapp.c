#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>

extern CONST UINT32 _gUefiDriverRevision = 0;

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
    //
    // Print stuff out
    //
    Print(L"Hello World! My handle is %lx and System Table is at %p\n",
          ImageHandle, SystemTable);
    return EFI_SUCCESS;
}

