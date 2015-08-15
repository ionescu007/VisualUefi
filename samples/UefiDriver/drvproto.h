#include <Uefi/UefiBaseType.h>

//
// Custom Protocol GUID
//
#define EFI_SAMPLE_DRIVER_PROTOCOL_GUID \
    { \
    0xd487ddb4, 0x008b, 0x11d9, {0xaf, 0xdc, 0x00, 0x10, 0x83, 0xff, 0xca, 0x4d } \
    }
extern EFI_GUID gEfiSampleDriverProtocolGuid;

//
// Custom Protocol Definition
//
typedef struct _EFI_SAMPLE_DRIVER_PROTOCOL
{
    EFI_HANDLE SampleValue;
} EFI_SAMPLE_DRIVER_PROTOCOL, *PEFI_SAMPLE_DRIVER_PROTOCOL;
