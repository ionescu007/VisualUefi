## Synopsis

VisualUEFI is 

* A Solution and set of Visual Studio 2015 Project Files to allow building the official EDK-II without the use of inf files, python and 50 other build tools, a custom dependency tracker and build system, and twenty other custom pieces of code.
  The EDK-II is present as a submodule, directly from the official TianoCore Tree, and no changes are done to it.

* A Solution and couple of Visual Studio 2015 Project Files to show two UEFI sample components: A UEFI Application, and a UEFI Boot Driver. The code is 100% EDK-II compatible, but built with VisualUEFI instead.

* A working copy of QEMU64 2.3 for Windows, with a fairly recent UEFI 2.5 OVMF Secure Boot ROM. These will updated on an ongoing basis as needed. This is integrated with the Visual Studio 2015 Sample Solution so that pressing F5 will spin up the instance for testing.

## Code Example

Show what the library does as concisely as possible, developers should be able to figure out **how** your project solves their problem by looking at the code example. Make sure the API you are showing off is obvious, and that your code is short and concise.

## Motivation

A short description of the motivation behind the creation and maintenance of the project. This should explain **why** the project exists.

## Installation

You should be able to open the EDK-II.SLN file and build without any issues in Visual Studio 2015. WDK or other 3rd party installations are not needed.

Once the EDK-II libraries are built, you should be able to open the SAMPLES.SLN file and build the two samples, which will create UefiApplication.efi and UefiDriver.efi. 

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
