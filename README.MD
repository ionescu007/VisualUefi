## Synopsis

VisualUEFI is 

* A Solution and set of Visual Studio 2015 Project Files to allow building the official EDK-II without the use of inf files, python and 50 other build tools, a custom dependency tracker and build system, and twenty other custom pieces of code.
  The EDK-II is present as a submodule, directly from the official TianoCore Tree, and no changes are done to it.

* A Solution and couple of Visual Studio 2015 Project Files to show two UEFI sample components: A UEFI Application, and a UEFI Boot Driver. The code is 100% EDK-II compatible, but built with VisualUEFI instead.

* A working copy of QEMU64 2.5 for Windows, with a fairly recent UEFI 2.5 OVMF Secure Boot ROM. These will updated on an ongoing basis as needed. This is integrated with the Visual Studio 2015 Sample Solution so that pressing F5 will spin up the instance for testing.

## Code Example

Here is a very simple example of a UEFI application communicating with a UEFI driver protocol. This sample is part of VisualUefi.

```c
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

```

## Motivation

Although EDK-II's build subsystem supports Visual Studio, it doesn't work with "in-IDE" building. Instead, special .inf files and other templates are used to define projects, and a custom build composed of multiple 3rd party
tools must be ran -- including dependencies on Python, Ruby, and Perl. For developers already familiar with Visual Studio's project files/MSBUILD, as well as the IDE it offers, this can be cumbersome and limiting, slowing down
the ability to quickly jump into UEFI development. Additionally, the EDK-II's default "test" environment is to build a Windows "NT32" layer around your application and running it as a command line executable. While this might
work for very simple applications, it doesn't reliably provide an environment for testing DXE drivers, runtime services, and more.

VisualUefi aims to bridge these gaps by compiling 100% unmodified EDK-II libraries with a proper Visual Studio build envioronment, adding some VisualUefi-specific glue to support building within Visual Studio without 3rd
party tools, and includes the latest QEMU and OVMF w/ SecureBoot packages for bare-metal testing of UEFI, without relying on Windows emulation.

## Installation

You should be able to open the EDK-II.SLN file and build without any issues in Visual Studio 2015. WDK or other 3rd party installations are not needed.

Once the EDK-II libraries are built, you should be able to open the SAMPLES.SLN file and build the three samples, which will create UefiApplication.efi, UefiDriver.efi and FtdiUsbSerialDxe.efi

## Documentation

Please refer to EDK-II/TianoCore for all documentation/help regarding EDK-II.

## Tests

You can press F5 (Run/Debug) from within the Sample Solution, which should spin up the QEMU instance with 512MB of ram, and your release directory as a virtual file system accessible through fs0:

You can then try loading the driver as follows:

	* Load fs0:\UefiDriver.efi

You can verify its presence by using either of these commands:

	* drivers (Should display "Sample Driver")
	* devtree (Should show a few "Sample Device" entries)

You can also launch the sample application, which should find the driver:

	* fs0:\UefiApplication.efi

## Contributors

Please use the GitHub issue tracker to submit any bugs/requests/etc.

For other feedback, you can reach me on Twitter at @aionescu

## License

* For the "samples" and "edk-ii" directory, the following license applies:

		Copyright (c) 2015, Alex Ionescu. All rights reserved.
		This program and the accompanying materials are licensed and made available under
		the terms and conditions of the BSD License which accompanies this distribution. 
		The full text of the license may be found at
		http://opensource.org/licenses/bsd-license.php

* For the "debugger" directory, the following license applies:

		The following points clarify the QEMU license:

		1) QEMU as a whole is released under the GNU General Public License,
		version 2.

		2) Parts of QEMU have specific licenses which are compatible with the
		GNU General Public License, version 2. Hence each source file contains
		its own licensing information.  Source files with no licensing information
		are released under the GNU General Public License, version 2 or (at your
		option) any later version.

		As of July 2013, contributions under version 2 of the GNU General Public
		License (and no later version) are only accepted for the following files
		or directories: bsd-user/, linux-user/, hw/misc/vfio.c, hw/xen/xen_pt*.

		3) The Tiny Code Generator (TCG) is released under the BSD license
		   (see license headers in files).

		4) QEMU is a trademark of Fabrice Bellard.

		Fabrice Bellard and the QEMU team

* The "edk2" submodule has its own licensing information, please read it.
