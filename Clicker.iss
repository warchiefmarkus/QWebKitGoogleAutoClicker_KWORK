; -- Example1.iss --
; Demonstrates copying 3 files and creating an icon.

; SEE THE DOCUMENTATION FOR DETAILS ON CREATING .ISS SCRIPT FILES!

[Setup]
AppName=Clicker
AppVersion=1.0
DefaultDirName={pf}\Clicker
DefaultGroupName=Clicker
UninstallDisplayIcon={app}\clicker.exe
Compression=lzma2
SolidCompression=yes
OutputDir=userdocs:Inno Setup Examples Output
PrivilegesRequired=admin
[Files]
Source: "clicker.exe"; DestDir: "{app}"
Source: "settings.ini"; DestDir: "{sd}"
Source: "icudt54.dll"; DestDir: "{app}"
Source: "icuin54.dll"; DestDir: "{app}"
Source: "icuuc54.dll"; DestDir: "{app}"
Source: "libEGL.dll"; DestDir: "{app}"
Source: "libgcc_s_dw2-1.dll"; DestDir: "{app}"
Source: "libGLESv2.dll"; DestDir: "{app}"
Source: "libstdc++-6.dll"; DestDir: "{app}"
Source: "libwinpthread-1.dll"; DestDir: "{app}"
Source: "opengl32sw.dll"; DestDir: "{app}"
Source: "Qt5Core.dll"; DestDir: "{app}"
Source: "Qt5Gui.dll"; DestDir: "{app}"
Source: "Qt5Multimedia.dll"; DestDir: "{app}"
Source: "Qt5MultimediaWidgets.dll"; DestDir: "{app}"
Source: "Qt5Network.dll"; DestDir: "{app}"
Source: "Qt5OpenGL.dll"; DestDir: "{app}"
Source: "Qt5Positioning.dll"; DestDir: "{app}"
Source: "Qt5PrintSupport.dll"; DestDir: "{app}"
Source: "Qt5Qml.dll"; DestDir: "{app}"
Source: "Qt5Quick.dll"; DestDir: "{app}"
Source: "Qt5Sensors.dll"; DestDir: "{app}"
Source: "Qt5Sql.dll"; DestDir: "{app}"
Source: "Qt5WebChannel.dll"; DestDir: "{app}"
Source: "Qt5WebKit.dll"; DestDir: "{app}"
Source: "Qt5WebKitWidgets.dll"; DestDir: "{app}"
Source: "Qt5Widgets.dll"; DestDir: "{app}"
Source: "platforms\qminimal.dll"; DestDir: "{app}\platforms"
Source: "platforms\qoffscreen.dll"; DestDir: "{app}\platforms"
Source: "platforms\qwindows.dll"; DestDir: "{app}\platforms"


[Icons]
Name: "{group}\Clicker"; Filename: "{app}\Clicker.exe"

[Registry]
Root: HKLM; Subkey: "SOFTWARE\Microsoft\Windows\CurrentVersion\Run"; ValueType: string; ValueName: "Clicker"; ValueData: """{app}\Clicker.exe"""; Flags: uninsdeletevalue