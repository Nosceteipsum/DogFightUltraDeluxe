# Microsoft Developer Studio Project File - Name="DF Ultra Deluxe" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DF Ultra Deluxe - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DF Ultra Deluxe.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DF Ultra Deluxe.mak" CFG="DF Ultra Deluxe - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DF Ultra Deluxe - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DF Ultra Deluxe - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DF Ultra Deluxe - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x406 /d "NDEBUG"
# ADD RSC /l 0x406 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "DF Ultra Deluxe - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x406 /d "_DEBUG"
# ADD RSC /l 0x406 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "DF Ultra Deluxe - Win32 Release"
# Name "DF Ultra Deluxe - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Engine"

# PROP Default_Filter ""
# Begin Group "OpenGl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\engine\OpenGl\COpenGl_Camera.cpp
# End Source File
# Begin Source File

SOURCE=.\engine\OpenGl\COpenGl_Camera.h
# End Source File
# Begin Source File

SOURCE=.\engine\OpenGl\COpenGl_Font.cpp
# End Source File
# Begin Source File

SOURCE=.\engine\OpenGl\COpenGl_Font.h
# End Source File
# Begin Source File

SOURCE=.\engine\OpenGl\COpenGl_Math.cpp
# End Source File
# Begin Source File

SOURCE=.\engine\OpenGl\COpenGl_Math.h
# End Source File
# Begin Source File

SOURCE=.\engine\OpenGl\COpenGl_Texture_TGA.cpp
# End Source File
# Begin Source File

SOURCE=.\engine\OpenGl\COpenGl_Texture_TGA.h
# End Source File
# Begin Source File

SOURCE=.\engine\OpenGl\COpenGl_Window.cpp
# End Source File
# Begin Source File

SOURCE=.\engine\OpenGl\COpenGl_Window.h
# End Source File
# End Group
# Begin Group "Windows"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\engine\windows\CRegEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\engine\windows\CRegEdit.h
# End Source File
# Begin Source File

SOURCE=.\engine\windows\CWinSock.cpp
# End Source File
# Begin Source File

SOURCE=.\engine\windows\CWinSock.h
# End Source File
# End Group
# Begin Group "DirectX"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\engine\DirectX\CDirectX_Sound.cpp
# End Source File
# Begin Source File

SOURCE=.\engine\DirectX\CDirectX_Sound.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\engine\CTimer.cpp
# End Source File
# Begin Source File

SOURCE=.\engine\CTimer.h
# End Source File
# End Group
# Begin Group "WinMain"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\WinMain.cpp
# End Source File
# Begin Source File

SOURCE=.\source\WinMain.h
# End Source File
# End Group
# Begin Group "Game"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\CGameHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\source\CGameHandler.h
# End Source File
# Begin Source File

SOURCE=.\source\game\CGameLoader.cpp
# End Source File
# Begin Source File

SOURCE=.\source\game\CGameLoader.h
# End Source File
# Begin Source File

SOURCE=.\source\game\CGameMain.cpp
# End Source File
# Begin Source File

SOURCE=.\source\game\CGameMain.h
# End Source File
# Begin Source File

SOURCE=.\source\game\CGameNetWork.cpp
# End Source File
# Begin Source File

SOURCE=.\source\game\CGameNetWork.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\global.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# End Group
# Begin Group "Resource"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\Script1.rc
# End Source File
# End Group
# Begin Source File

SOURCE=.\DFUD.bmp
# End Source File
# End Target
# End Project
