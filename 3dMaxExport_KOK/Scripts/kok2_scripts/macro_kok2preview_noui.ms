macroScript macro_WEPreview
	category:"Kok2Exporter"
	buttonText:"Preview"
	tooltip:"Preview"
	Icon:#("kok2", 3)
(
	include "kok2_scripts/fn_ExportAndConvert.ms"
	
	on excute do
	(
		configFile = GetDir #plugcfg
		configFile += "\\kok2utility.ini"
		
		strConverter = getIniSetting configFile "settings" "kk2converter"
		strEffectViewer = getIniSetting configFile "settings" "weeffectview"
		
		weeffectviewpath = substring strEffectViewer 1 (strEffectViewer.count - 16)
		weeffectviewpath += "Effect\\efm\\"
		ExportAndConvertModel strConverter weeffectviewpath weeffectviewpath
		
		strOrigFilename = maxfilename
		strFilename = substring strOrigFilename 1 (strOrigFilename.count - 4)
		strCommand = "\"" + strEffectViewer + "\""
		strCommandFull = strCommand + " " + strFilename
		print strCommandFull
		ShellLaunch strCommand strFilename
	)
)

macroScript macro_WEPreview3
	category:"Kok3Exporter"
	buttonText:"PreviewKoKEditor"
	tooltip:"PreviewKoKEditor"
	Icon:#("kok2", 4)
(
	include "kok2_scripts/fn_ExportAndConvert.ms"
	
	on excute do
	(
		bGroundObject = false
		for i in objects do
		(
			if (i.name == "c_scope") or (i.name == "c_land_stop") or (i.name == "c_sky_stop") or (i.name == "c_arrow") or (i.name == "c_dynamic_stop") or (i.name == "c_cls_stop") then
			(
				bGroundObject = true;
				exit;
			)
		)
		
		configFile = GetDir #plugcfg
		configFile += "\\kok2utility.ini"
		
		strConverter = getIniSetting configFile "settings" "kk2converter"
		strkokeditor = getIniSetting configFile "settings" "kokeditor"
		
		editorpath = substring strkokeditor 1 (strkokeditor.count - 10)
		
		if( bGroundObject == false) then
		(
			editorpath += "Effect\\efm\\"
		)
		else
		(
			editorpath += "TestThing\\"
		)
		
		print strkokeditor
		print editorpath
		
		ExportAndConvertModel strConverter editorpath editorpath
	)
)