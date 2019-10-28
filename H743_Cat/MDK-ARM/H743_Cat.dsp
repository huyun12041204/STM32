# Microsoft Developer Studio Project File - Name="H743_Cat" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=H743_Cat - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "H743_Cat.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "H743_Cat.mak" CFG="H743_Cat - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "H743_Cat - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "H743_Cat - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "H743_Cat - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "USE_HAL_DRIVER" /D "STM32H743xx"  /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "../Inc" /I "../Drivers/STM32H7xx_HAL_Driver/Inc" /I "../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" /I "../Middlewares/Third_Party/FatFs/src" /I "../Middlewares/ST/STM32_USB_Device_Library/Core/Inc" /I "../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" /I "../Drivers/CMSIS/Device/ST/STM32H7xx/Include" /I "../Drivers/CMSIS/Include" /I "../HARDWARE/LCD" /I "../SYSTEM/delay" /I "../SYSTEM/sys" /I "C:\Keil Project\H743_Cat\MDK-ARM"  /D "USE_HAL_DRIVER" /D "STM32H743xx"  /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 user32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 user32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "H743_Cat - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "USE_HAL_DRIVER" /D "STM32H743xx"  /YX /FD /GZ  /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "../Inc" /I "../Drivers/STM32H7xx_HAL_Driver/Inc" /I "../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" /I "../Middlewares/Third_Party/FatFs/src" /I "../Middlewares/ST/STM32_USB_Device_Library/Core/Inc" /I "../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" /I "../Drivers/CMSIS/Device/ST/STM32H7xx/Include" /I "../Drivers/CMSIS/Include" /I "../HARDWARE/LCD" /I "../SYSTEM/delay" /I "../SYSTEM/sys" /I "C:\Keil Project\H743_Cat\MDK-ARM"  /D "USE_HAL_DRIVER" /D "STM32H743xx"  /YX /FD /GZ  /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 user32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 user32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "H743_Cat - Win32 Release"
# Name "H743_Cat - Win32 Debug"
# Begin Group "Application/MDK-ARM"

# PROP Default_Filter ""
# Begin Source File

SOURCE="startup_stm32h743xx.s"
# End Source File
# End Group
# Begin Group "HARDWARE"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\HARDWARE\LCD\lcd.c"
# End Source File
# End Group
# Begin Group "SYSTEM"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\SYSTEM\sys\sys.c"
# End Source File
# Begin Source File

SOURCE="..\SYSTEM\delay\delay.c"
# End Source File
# Begin Source File

SOURCE="..\SYSTEM\usart\usart_if.c"
# End Source File
# End Group
# Begin Group "Application/User"

# PROP Default_Filter ""
# Begin Source File

SOURCE="../Src/main.c"
# End Source File
# Begin Source File

SOURCE="..\Src\var.c"
# End Source File
# Begin Source File

SOURCE="..\Src\operation.c"
# End Source File
# Begin Source File

SOURCE="../Src/usb_device.c"
# End Source File
# Begin Source File

SOURCE="..\Src\usbd_cdc_if.c"
# End Source File
# Begin Source File

SOURCE="../Src/usbd_conf.c"
# End Source File
# Begin Source File

SOURCE="../Src/usbd_desc.c"
# End Source File
# Begin Source File

SOURCE="../Src/stm32h7xx_it.c"
# End Source File
# Begin Source File

SOURCE="../Src/stm32h7xx_hal_msp.c"
# End Source File
# Begin Source File

SOURCE="..\Src\bsp_driver_sd.c"
# End Source File
# Begin Source File

SOURCE="..\Src\sd_diskio.c"
# End Source File
# Begin Source File

SOURCE="..\Src\sdmmc.c"
# End Source File
# Begin Source File

SOURCE="..\Src\fatfs.c"
# End Source File
# Begin Source File

SOURCE="..\Src\gpio.c"
# End Source File
# Begin Source File

SOURCE="..\Src\tim.c"
# End Source File
# Begin Source File

SOURCE="..\Src\usart.c"
# End Source File
# Begin Source File

SOURCE="..\Src\rtc.c"
# End Source File
# End Group
# Begin Group "Drivers/STM32H7xx_HAL_Driver"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\Drivers\STM32H7xx_HAL_Driver\Src\stm32h7xx_hal_pcd.c"
# End Source File
# Begin Source File

SOURCE="..\Drivers\STM32H7xx_HAL_Driver\Src\stm32h7xx_hal_pcd_ex.c"
# End Source File
# Begin Source File

SOURCE="../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_usb.c"
# End Source File
# Begin Source File

SOURCE="../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_cortex.c"
# End Source File
# Begin Source File

SOURCE="../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_sdmmc.c"
# End Source File
# Begin Source File

SOURCE="../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_delayblock.c"
# End Source File
# Begin Source File

SOURCE="../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sd.c"
# End Source File
# Begin Source File

SOURCE="../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sd_ex.c"
# End Source File
# Begin Source File

SOURCE="../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim.c"
# End Source File
# Begin Source File

SOURCE="../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim_ex.c"
# End Source File
# Begin Source File

SOURCE="../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_uart.c"
# End Source File
# Begin Source File

SOURCE="../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_uart_ex.c"
# End Source File
# Begin Source File

SOURCE="../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc.c"
# End Source File
# Begin Source File

SOURCE="../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc_ex.c"
# End Source File
# Begin Source File

SOURCE="../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash.c"
# End Source File
# Begin Source File

SOURCE="../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash_ex.c"
# End Source File
# Begin Source File

SOURCE="../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_gpio.c"
# End Source File
# Begin Source File

SOURCE="../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_hsem.c"
# End Source File
# Begin Source File

SOURCE="../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma.c"
# End Source File
# Begin Source File

SOURCE="../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma_ex.c"
# End Source File
# Begin Source File

SOURCE="../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_mdma.c"
# End Source File
# Begin Source File

SOURCE="../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr.c"
# End Source File
# Begin Source File

SOURCE="../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr_ex.c"
# End Source File
# Begin Source File

SOURCE="../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal.c"
# End Source File
# Begin Source File

SOURCE="../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c.c"
# End Source File
# Begin Source File

SOURCE="../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c_ex.c"
# End Source File
# Begin Source File

SOURCE="..\Drivers\STM32H7xx_HAL_Driver\Src\stm32h7xx_hal_rtc.c"
# End Source File
# Begin Source File

SOURCE="..\Drivers\STM32H7xx_HAL_Driver\Src\stm32h7xx_hal_rtc_ex.c"
# End Source File
# End Group
# Begin Group "Drivers/CMSIS"

# PROP Default_Filter ""
# Begin Source File

SOURCE="../Src/system_stm32h7xx.c"
# End Source File
# End Group
# Begin Group "Middlewares/USB_Device_Library"

# PROP Default_Filter ""
# Begin Source File

SOURCE="../Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c"
# End Source File
# Begin Source File

SOURCE="../Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c"
# End Source File
# Begin Source File

SOURCE="../Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c"
# End Source File
# Begin Source File

SOURCE="../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.c"
# End Source File
# End Group
# Begin Group "Middlewares/FatFs"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\Middlewares\Third_Party\FatFs\src\diskio.c"
# End Source File
# Begin Source File

SOURCE="..\Middlewares\Third_Party\FatFs\src\ff.c"
# End Source File
# Begin Source File

SOURCE="..\Middlewares\Third_Party\FatFs\src\ff_gen_drv.c"
# End Source File
# Begin Source File

SOURCE="..\Middlewares\Third_Party\FatFs\src\option\syscall.c"
# End Source File
# Begin Source File

SOURCE="..\Middlewares\Third_Party\FatFs\src\option\cc936.c"
# End Source File
# End Group
# Begin Group "::CMSIS"

# PROP Default_Filter ""
# End Group
# End Target
# End Project
