/** @file
  Global GUID Definitions

Copyright (c) 2015, Alex Ionescu. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Uefi.h>
#include <Library/UefiLib.h>

#include <Protocol/HiiFont.h>
#include <Protocol/GraphicsOutput.h>
#include <Protocol/UgaDraw.h>
#include <Protocol/DebugPort.h>
#include <Protocol/DevicePathFromText.h>
#include <Protocol/DevicePathToText.h>
#include <Protocol/DevicePathUtilities.h>
#include <Protocol/PciIo.h>
#include <Protocol/LoadedImage.h>
#include <Protocol/AcpiTable.h>

#include <Guid/PcAnsi.h>
#include <Guid/GlobalVariable.h>

EFI_GUID gEfiPciIoProtocolGuid = EFI_PCI_IO_PROTOCOL_GUID;
EFI_GUID gEfiDriverDiagnosticsProtocolGuid = EFI_DRIVER_DIAGNOSTICS_PROTOCOL_GUID;
EFI_GUID gEfiDriverDiagnostics2ProtocolGuid = EFI_DRIVER_DIAGNOSTICS2_PROTOCOL_GUID;
EFI_GUID gEfiDriverConfigurationProtocolGuid = EFI_DRIVER_CONFIGURATION_PROTOCOL_GUID;
EFI_GUID gEfiDriverConfiguration2ProtocolGuid = EFI_DRIVER_CONFIGURATION2_PROTOCOL_GUID;
EFI_GUID gEfiComponentName2ProtocolGuid = EFI_COMPONENT_NAME2_PROTOCOL_GUID;
EFI_GUID gEfiComponentNameProtocolGuid = EFI_COMPONENT_NAME_PROTOCOL_GUID;
EFI_GUID gEfiDriverBindingProtocolGuid = EFI_DRIVER_BINDING_PROTOCOL_GUID;
EFI_GUID gEfiSimpleTextOutProtocolGuid = EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID;
EFI_GUID gEfiGraphicsOutputProtocolGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
EFI_GUID gEfiUgaDrawProtocolGuid = EFI_UGA_DRAW_PROTOCOL_GUID;
EFI_GUID gEfiHiiFontProtocolGuid = EFI_HII_FONT_PROTOCOL_GUID;
EFI_GUID gEfiDevicePathProtocolGuid = EFI_DEVICE_PATH_PROTOCOL_GUID;
EFI_GUID gEfiPcAnsiGuid = EFI_PC_ANSI_GUID;
EFI_GUID gEfiVT100Guid = EFI_VT_100_GUID;
EFI_GUID gEfiVT100PlusGuid = EFI_VT_100_PLUS_GUID;
EFI_GUID gEfiVTUTF8Guid = EFI_VT_UTF8_GUID;
EFI_GUID gEfiUartDevicePathGuid = DEVICE_PATH_MESSAGING_UART_FLOW_CONTROL;
EFI_GUID gEfiSasDevicePathGuid = EFI_SAS_DEVICE_PATH_GUID;
EFI_GUID gEfiDebugPortProtocolGuid = EFI_DEBUGPORT_PROTOCOL_GUID;
EFI_GUID gEfiDevicePathUtilitiesProtocolGuid = EFI_DEVICE_PATH_UTILITIES_PROTOCOL_GUID;
EFI_GUID gEfiDevicePathToTextProtocolGuid = EFI_DEVICE_PATH_TO_TEXT_PROTOCOL_GUID;
EFI_GUID gEfiDevicePathFromTextProtocolGuid = EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL_GUID;
EFI_GUID gEfiGlobalVariableGuid = EFI_GLOBAL_VARIABLE;
EFI_GUID gEfiLoadedImageProtocolGuid = EFI_LOADED_IMAGE_PROTOCOL_GUID;
EFI_GUID gEfiAcpiTableProtocolGuid = EFI_ACPI_TABLE_PROTOCOL_GUID;

