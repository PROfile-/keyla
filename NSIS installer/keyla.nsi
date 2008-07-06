; Headers

!include MUI2.nsh

; Constants

!define PRODUCT keyla
!define VERSION 0.1.0.0
!define WNDCLASS "keyla main window"

; Version information

VIProductVersion ${VERSION}
VIAddVersionKey "LegalCopyright" "© Евгений Аршинов, 2008"
VIAddVersionKey "FileDescription" "Переключатель раскладки клавиатуры"
VIAddVersionKey "FileVersion" ${VERSION}

; General configuration

InstallDir   $PROGRAMFILES\${PRODUCT}
Name         ${PRODUCT}
OutFile      keyla-0.1-setup.exe

  ;Get installation folder from registry if available
InstallDirRegKey HKCU "Software\${PRODUCT}" "installDir"

; General configuration for MUI

!define MUI_ICON   ..\keyla\res\Icon.ico
!define MUI_UNICON ..\keyla\res\Icon.ico

; Pages configuration

!define MUI_ABORTWARNING

; List of pages

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE ..\LICENSE
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES

!define MUI_FINISHPAGE_RUN $INSTDIR\${PRODUCT}.exe
!define MUI_FINISHPAGE_SHOWREADME
!define MUI_FINISHPAGE_SHOWREADME_TEXT "Автоматически запускать keyla при входе в систему"
!define MUI_FINISHPAGE_SHOWREADME_FUNCTION AddToAutostart
Function AddToAutostart
  CreateShortCut $SMSTARTUP\${PRODUCT}.lnk $INSTDIR\${PRODUCT}.exe
FunctionEnd

!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

; Language

!insertmacro MUI_LANGUAGE "Russian"

; Callbacks

Function un.onInit
  retry:
  FindWindow $0 "${WNDCLASS}"
  StrCmp $0 0 continue
    MessageBox MB_RETRYCANCEL "Для продолжения установки завершите работу keyla и повторите попытку" IDRETRY retry
    Abort
  continue:
FunctionEnd

; Sections

Section

  ; Files 
  SetOutPath $INSTDIR
  File ..\keyla\Release\keyla.exe
  SetOutPath $INSTDIR\icons
  File ..\icons\*.ico
  
  ;  Registry keys
  WriteRegStr HKCU Software\${PRODUCT} installDir $INSTDIR
  
  ; Start menu items
  CreateDirectory $SMPROGRAMS\${PRODUCT}
  CreateShortCut $SMPROGRAMS\${PRODUCT}\${PRODUCT}.lnk $INSTDIR\${PRODUCT}.exe
  CreateShortCut $SMPROGRAMS\${PRODUCT}\Удаление.lnk $INSTDIR\Uninstall.exe

  ; Uninstaller registry keys
  WriteRegStr HKLM Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT} DisplayName "keyla - переключатель раскладок клавиатуры"
  WriteRegStr HKLM Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT} UninstallString $INSTDIR\Uninstall.exe
  
  ; Uninstaller
  WriteUninstaller $INSTDIR\Uninstall.exe
  
SectionEnd

 
Section Uninstall

  ;Current working directory can not be deleted. So change it
  SetOutPath $TEMP
  
  ;Files 
  Delete $INSTDIR\${PRODUCT}.exe
  Delete $INSTDIR\Uninstall.exe
  RMDir /r $INSTDIR\icons
  RMDir $INSTDIR
  
  ;Start menu items
  RMDir /r $SMPROGRAMS\${PRODUCT}
  
  ; Autostart
  Delete $SMSTARTUP\${PRODUCT}.lnk
  
  ;Uninstaller registry keys 
  DeleteRegKey HKLM Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT}
  
SectionEnd
