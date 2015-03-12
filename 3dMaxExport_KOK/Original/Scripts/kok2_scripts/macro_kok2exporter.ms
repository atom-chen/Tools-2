macroScript macro_floaterKok2Exporter
	category:"Kok2Exporter"
	buttonText:"Kok2 Exporter"
	tooltip:"King of Kings II Exporter"
	Icon:#("kok2", 1)
(
	local strConverter = "";
	local strCopyPath = "";
	
	local strEffectViewer = "";
	local strKOKEditor = "";
	on execute do
	(
		rollout rolloutKok2exporter "Kok2 exporter" width:290 height:350
		(
			bitmap LogoImage " Max Plugin of Kof2 " pos:[0,10] width:280 height:80 filename:"gkk2-3.bmp"
			label lbl1 "Console Converter:" pos:[5,25 + LogoImage.height] width:120 height:18
			editText edt1 "" pos:[5,42 + LogoImage.height] width:260 height:23
			button btn_browse "Browse" pos:[150,15 + LogoImage.height] width:90 height:24
			label lbl2 "Copy to directory:" pos:[5,85 + LogoImage.height] width:120 height:18
			editText edt2 "" pos:[5,99 + LogoImage.height] width:260 height:23
			button btn_browseoutputdir "Browse" pos:[150,72 + LogoImage.height] width:90 height:24
			button btn_export_kk2model "Export Kok2 Model" pos:[8,140 + LogoImage.height] width:130 height:34
			button btn_check_scene "Model Type?" pos:[155,140 + LogoImage.height] width:90 height:34
			
			on btn_browse pressed do
			(
				kk2converter = getOpenFileName caption:"Select Kok2 file-converter" types:"Executable(*.exe)|*.exe|Batch File(*.bat)|*.bat|All|*.*|"
				if (kk2converter != undefined) then
				(
					edt1.text = kk2converter;
					strConverter = kk2converter;
				)
			)
			
			on btn_browseoutputdir pressed do
			(
				copypath = getSavePath caption:"Select Copy Directory"
				if(copypath != undefined) then
				(
					if(copypath[copypath.count] != "\\") then copypath += "\\"
					edt2.text = copypath
					strCopyPath = copypath;
				)
			)
			
			on btn_check_scene pressed do
			(
				bPhysique = false
				bKK2Modifier = false
				bGroundObject = false
				bEffectModel = false
				for i in objects do
				(
					if(IsPhysique i) then 
					(
						bPhysique = true;
						exit;
					)
				)
				
				for i in objects do
				(
					if (IsKk2Modifier i) then 
					(
						bKk2Modifier = true;
						exit;
					)
				)
				
				for i in objects do 
				(
					if (i.name == "c_scope") or (i.name == "c_land_stop") or (i.name == "c_sky_stop") or (i.name == "c_arrow") or (i.name == "c_dynamic_stop") or (i.name == "c_cls_stop") then
					(
						bGroundObject = true;
						exit;
					)
				)
				
				for i in objects do
				(
					if (i.name == "b_effect_model") or (i.name == "c_effect") then
					(
						bEffectModel = true;
						exit;
					)
				)
				
				if(bPhysique == true) and (bKK2Modifier == true) and (bGroundObject == false) and (bEffectModel == false) and maxfilename.count > 0 then
				(
					MessageBox = "Skinned Model"
				)
				else if(bPhysique == false) and (bKK2Modifier == true) and (bGroundObject == true) and maxfilename.count > 0 then
				(
					MessageBox = "Ground Object (motion)"
				)
				else if(bPhysique == false) and (bKK2Modifier == false) and (bGroundObject == true) and maxfilename.count > 0 then
				(
					MessageBox = "Ground Object (static)"
				)
				else if(bPhysique == false) and (bKK2Modifier == false) and (bGroundObject == false) and maxfilename.count > 0 then
				(
					MessageBox = "Static Object (maybe weapon, equipment, or something still.)"
				)
				else if(bEffectModel == true) and (bPhysique == true) and (bKK2Modifier == true) and maxfilename.count > 0 then
				(
					MessageBox = "Skinned Effect Model"
				)
				else if(bEffectModel == true) and (bKK2Modifier == false) and maxfilename.count > 0 then
				(
					MessageBox = "Skinned Effect Model NO Animation"
				)
				else
				(
					MessageBox = "Un-recognized Scene"
				)
			)
			
			on btn_export_kk2model pressed do
			(
				if(edt2.text == undefined) or (edt2.text == "") then 
				(
					ExportAndConvertModel edt1.text edt2.text maxfilename
				)
				else
				(
					ExportAndConvertModel edt1.text edt2.text edt2.text
				)
			)
			
			on rolloutKok2exporter open do
			(
				configFile = GetDir #plugcfg
				configFile += "\\kok2utility.ini"
				
				edt1.text = getIniSetting configFile "settings" "kk2converter"
				edt2.text = getIniSetting configFile "settings" "copypath"
				
				if(edt1.text == undefined) or (edt1.text == "") then 
				(
					edt1.text = "C:\\3dmax7\\SwitchModel_console.exe"
				)
				
				strConverter = edt1.text;
				strCopyPath = edt2.text;
			)
			
			on rolloutKok2exporter close do
			(
				configFile = GetDir #plugcfg
				configFile += "\\kok2utility.ini"
				
				setIniSetting configFile "settings" "kk2converter" edt1.text;
				setIniSetting configFile "settings" "copypath" edt2.text;
			)
		)
		
		rollout rolloutViewer "WE Effect View"
		(
			label lbl1 "Effect View:" pos:[5,25] width:120 height:18
			editText edt1 "" pos:[5,42] width:260 height:23
			button btn_browse "Browse:" pos:[150,15] width:90 height:24
			button btn_view_effect "Preview" pos:[8,70] width:60 height:34
			
			button btn_view_effect2 "新查看器" pos:[80,701] width:60 height:34
			editText edt2 "" pos:[5,110] width:260 height:23
			button btn_browse2 "新查看器目录" pos:[150,70] width:90 height:24
			
			on btn_browse pressed do
			(
				weeffectviewer = getOpenFileName caption:"Select WE effect viewer" types:"Executable(*.exe)|*.exe"
				if(weeffectviewer != undefined) then
				(
					edt1.text = weeffectviewer;
					strEffectViewer = weeffectviewer;
				)
			)
			
			on btn_browse2 pressed do
			(
				editorpath = getOpenFileName caption:"选择新编辑器目录位置" types:"Executable(*.exe)|*.exe"
				if(editorpath != undefined) then
				(
					edt2.text = editorpath;
					strEffectViewer = editorpath;
				)
			)
			
			on rolloutViewer open do
			(
				configFile = GetDir #plugcfg
				configFile += "\\kok2utility.ini"
				
				edt1.text = getIniSetting configFile "settings" "weeffectviewer"
				edt2.text = getIniSetting configFile "settings" "kokeditor"
				
				if(edt1.text == undefined) or (edt1.text == "") then edt1.text = "C:\\3dsmax7\\EffectViewer.exe"
				if(edt2.text == undefined) or (edt2.text == "") then edt2.text = "C:\\kok\\editor.exe"
				strEffectViewer = edt1.text;
				strKOKEditor = edt2.text;
			)
			
			on rolloutViewer close do
			(
				configFile = GetDir #plugcfg
				configFile += "\\Kok2utility.ini"
				
				setIniSetting configFile "settings" "weeffectviewer" edt1.text;
				setIniSetting configFile "settings" "kokeditor" edt2.text;
			)
			
			on btn_view_effect pressed do
			(
				weeffectviewerpath = substring strEffectViewer 1 (strEffectViewer.count - 16)
				weeffectviewerpath += "Effect\\efm\\"
				ExportAndConvertModel strConverter weeffectviewerpath weeffectviewerpath
				
				strOrigFilename = maxfilename
				strFilename = substring strOrigFilename 1 (strOrigFilename.count - 4)
				strCommand = "\"" + strEffectViewer + "\""
				strCommandFull = strCommand + " " + strFilename
				print strCommandFull
				ShellLaunch strCommand strFilename
			)
			
			on btn_view_effect2 pressed do
			(
				editorpath = substring strKOKEditor 1 (strKOKEditor.count - 10)
				editorpath += "Effect\\efm\\"
				
				print strKOKEditor
				print editorpath
				
				ExportAndConvertModel strConverter editorpath editorpath
			)
		)
		
		rollout rolloutBatchExport "Kok2 Batch Export"
		(
			editText edt1 "search path:" pos:[7,10] width:260 height:21
			button btn_browse_path "Browse Path" pos:[7,40] width:260 height:20
			button btn_batchexport "Batch Export, GO!" pos:[7,63] width:260 height:36
			
			on btn_browse_path pressed do
			(
				searchPath = getSavePath caption:"Select Copy Directory"
				if(searchPath != undefined) then
				(
					if(searchPath[ searchPath.count ] != "\\") then searchPath += "\\"
					edt1.text = searchPath
				)
			)
			
			on btn_batchexport pressed do
			(
				if(edt1.text != undefined) and (edt1.text.count > 0) and (strConverter.count > 0) then
				(
					file_array = getFilesRecursive edt1.text "*.max"
					
					for i in file_array do print i;
					
					for i in file_array do
					(
						loadMaxfile i useFileUnits:true guiet:true
						
						ExportAndConvertModel strConverter strCopyPath ""
					)
				)
			)
		)
		
		floaterConfiguration = newRolloutFloater "King of Kings II" 290 520
		addRollout rolloutKok2exporter floaterConfiguration
		
		addRollout rolloutViewer floaterConfiguration
		
		addRollout rolloutBatchExport floaterConfiguration
	)
)