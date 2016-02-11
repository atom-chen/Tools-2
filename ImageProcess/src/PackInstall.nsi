; 起头的一行是注释

; 安装程序的名称
Name  "PackTool"

; 输出安装程序启动文件
OutFile  "PackTool.exe "

; 默认安装目录，$PROGRAMFILES指示Windows的Programm Files目录
InstallDir $PROGRAMFILES\PackTool

; 安装页面, 比如许可证说明页面等等

; directory表示选择安装目录的页面
Page directory
; instfiles 表示安装的页面
Page instfiles

; 具体要装的东西, 比如拷贝文件
Section  ""   ; 没有components page, 名称不重要
     ; 指定输出目录
     SetOutPath $INSTDIR
     ; 拷贝一个目录
     File /r build\exe.win-amd64-3.3\*
SectionEnd