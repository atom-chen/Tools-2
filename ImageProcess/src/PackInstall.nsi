; ��ͷ��һ����ע��

; ��װ���������
Name  "PackTool"

; �����װ���������ļ�
OutFile  "PackTool.exe "

; Ĭ�ϰ�װĿ¼��$PROGRAMFILESָʾWindows��Programm FilesĿ¼
InstallDir $PROGRAMFILES\PackTool

; ��װҳ��, �������֤˵��ҳ��ȵ�

; directory��ʾѡ��װĿ¼��ҳ��
Page directory
; instfiles ��ʾ��װ��ҳ��
Page instfiles

; ����Ҫװ�Ķ���, ���翽���ļ�
Section  ""   ; û��components page, ���Ʋ���Ҫ
     ; ָ�����Ŀ¼
     SetOutPath $INSTDIR
     ; ����һ��Ŀ¼
     File /r build\exe.win-amd64-3.3\*
SectionEnd