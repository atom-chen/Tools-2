fn getFilesRecursive root pattern = 
(
	dir_array = GetDirectories (root+"/*")
	for d in dir_array do
		join dir_array (GetDirectories (d+"/*"))
		
	my_files = getFiles (root + "\\" + pattern)
	for f in dir_array do
		join my_files (getFiles (f + pattern))
		
	return my_files
)

fn IsHavAnimTable node = 
(
	if (node.modifiers == undefined) then return undefined
	
	if (node.modifiers.count == 0) then return undefined
	
	for j=1 to node.modifiers.count do
	(
		if node.modifiers[j].classid[1] == 0x5ffb3ef5 and node.modifiers[j].classid[2] == 0x5a6a3550 then
			return node.modifiers[j];
	)
	return undefined
)

fn IsPhysique node = 
(
	if (node.modifiers.count == 0) then return false
	
	for i = 1 to node.modifiers.count do 
	(
		if node.modifiers[i].classid[1] == 0x00100 and node.modifiers[i].classid[2] == 0x00000 then
			return true;
	)
	return false
)

fn IsKK2Modifiers node = 
(
	if (node.modifiers.count == 0) then return false
	
	for i = 1 to node.modifiers.count do
	(
		if node.modifiers.count do
		(
			if node.modifiers[i].classid[1] == 0x5ffb3ef5 and node.modifiers[i].classid[2] == 0x5a6a3550 then
				return true;
		)
		return false
	)
)

fn ExportAndConvertModel strConverter strCopuPath strTexCopyPath = 
(
	bPhysique = false
	bKK2Modifier = false
	bGroundObject = false
	bEffectModel = false
	for i in objects do
	(
		if (IsPhysique i ) then
		(
			bPhysique = true;
			exit;
		)
	)
	
	for i in objects do
	(
		if (IsKK2Modifiers i ) then
		(
			bKK2Modifier = true;
			exit;
		)
	)
	
	for i in objects do
	(
		if(i.name == "c_scope") or (i.name == "c_land_stop") or (i.name == "c_sky_stop") or (i.name == "c_arrow") or (i.name == "c_dynamic_stop") or (i.name == "c_cls_stop") then
		(
			bGroundObject = true;
			exit;
		)
	)
	
	for i in objects do
	(
		if(i.name == "b_effect_model") or (i.name == "b_effect") then
		(
			bEffectModel = true;
			exit;
		)
	)
	
	format "Physique = %, KK2Modifier = %, GroundObject = %, bEffectModel = % \n" bPhysique bKK2Modifier bGroundObject bEffectModel
	
	if bPhysique == true and bKK2Modifier == true and bEffectModel == false and maxfilename.count > 0 then
	(
		expNumAnims = 0;
		expAnimNames = #()
		expAnimTickStart = #()
		expAnimTickEnd = #()
		expAnimFrameStart = #()
		expAnimFrameEnd = #()
		
		expMod = undefined;
		for i in objects do 
		(
			mod = IsHavAnimTable i 
			if( mod != undefined ) then
				expMod = mod;
		)
		try
		(
			expNumAnims = expMod.anames.count
			for i in expMod.anames do append expAnimNames i;
			for i in expMod.afframes do append expAnimFrameStart i;
			for i in expMod.alframes do append expAnimFrameEnd i;
			for i in expMod.afframes do append expAnimTickStart (i * ticksPerFrame);
			for i in expMod.alframes do append expAnimTickEnd (i * ticksPerFrame);
			
			for i in #{1..expNumAnims} do
			(
				format "[%] ==> TickStart(%), TickEnd(%), FrmStart(%)\n" expAnimNames[i] expAnimTickStart[i] expAnimTickEnd[i] expAnimFrameStart[i] expAnimFrameEnd[i]
				if( expAnimFrameStart[i] == expAnimFrameEnd[i] ) then
				(
					MessageBox "动作表中有无效的动作."
				)
			)
			
			strOrigFilename = maxfilepath + maxfilename
			strXFilename = substring strOrigFilename 1 (strOrigFilename.count - 3)
			strXFilename += "x"
			LagerExportXFile strXFilename true true
			
			strOrigFilename = maxfilepath + maxfilename
			strCatFilename = substring strOrigFilename 1 (strOrigFilename.count - 3)
			strCatFilename += "cat"
			catFileStream = fopen strCatFilename "wb"
			WriteLong catFileStream expNumAnims #unsigned-- first write the number of animations
			
			for i in #{1..expNumAnims} do
			(
				WriteLong catFileStream (expAnimNames[i].count + 1) #unsigned
				WriteString catFileStream expAnimNames[i]
				WriteLong catFileStream expAnimTickStart[i] #unsigned
				WriteLong catFileStream expAnimTickEnd[i] #unsigned
				WriteLong catFileStream expAnimFrameStart[i] #unsigned
				WriteLong catFileStream expAnimFrameEnd[i] #unsigned
			)
			fclose catFileStream
			
			strOrigFilename = maxfilepath + maxfilename
			strOutputFilename = substring strOrigFilename 1 (strOrigFilename.count - 4)
			
			if strConverter.count != 0 then
			(
				strCommand = "\"" + strConverter + "\"" + " -inx " + strXFilename + " -incat " + strCatFilename;
				strCommand += (" -out " + strOutputFilename + " -atf -atm -act -ct");
				print strCommand
				DosCommand strCommand
				
				strOrigFilename = maxfilepath + maxfilename
				strActFilename = substring strOrigFilename 1 (strOrigFilename.count - 3)
				strActFilename += "act"
				
				strCommand = "\"" + strConverter + "\"" + " -inact "
				strCommand += strActFilename
				strCommand += (" -aft -out " + strOutputFilename )
				print strCommand
				DosCommand strCommand
			)
			
			if strCopyPath.count != 0 then
			(
				strCommand = "Copy " + "\"" + strOutputFilename + ".act\" \"" + strCopyPath + "\"";
				print strCommand
				DosCommand strCommand
				strCommand = "Copy " + "\"" + strOutputFilename + ".atm\" \"" + strCopyPath + "\"";
				print strCommand
				DosCommand strCommand
				strCommand = "Copy " + "\"" + strOutputFilename + ".atf\" \"" + strCopyPath + "\"";
				print strCommand
				DosCommand strCommand
				strCommand = "Copy " + "\"" + strOutputFilename + ".aft\" \"" + strCopyPath + "\"";
				print strCommand
				DosCommand strCommand
			)
		)catch(
			MessageBox "Undefine Animation Table. \n Please use KOKII Modifier to edit info of animation table."
		)
	)
	else if bPhysique == false and bKK2Modifier == true and maxfilename.count > 0 then
	(
		expNumAnims = 0;
		expAnimNames = #()
		expAnimTickStart = #()
		expAnimTickEnd = #()
		expAnimFrameStart = #()
		expAnimFrameEnd = #()
		
		expMod = undefined;
		for i in objects do 
		(
			mod = IsHavAnimTable i 
			if( mod != undefined ) then
				expMod = mod;
		)
		try
		(
			expNumAnims = expMod.anames.count
			for i in expMod.anames do append expAnimNames i;
			for i in expMod.afframes do append expAnimFrameStart i;
			for i in expMod.alframes do append expAnimFrameEnd i;
			for i in expMod.afframes do append expAnimTickStart (i * ticksPerFrame);
			for i in expMod.alframes do append expAnimTickEnd (i * ticksPerFrame);
			
			for i in #{1..expNumAnims} do
			(
				format "[%] ==> TickStart(%), TickEnd(%), FrmStart(%)\n" expAnimNames[i] expAnimTickStart[i] expAnimTickEnd[i] expAnimFrameStart[i] expAnimFrameEnd[i]
				if( expAnimFrameStart[i] == expAnimFrameEnd[i] ) then
				(
					MessageBox "动作表中有无效的动作."
				)
			)
			
			strOrigFilename = maxfilepath + maxfilename
			strXFilename = substring strOrigFilename 1 (strOrigFilename.count - 3)
			strXFilename += "x"
			LagerExportXFile strXFilename true true
			
			strOrigFilename = maxfilepath + maxfilename
			strCatFilename = substring strOrigFilename 1 (strOrigFilename.count - 3)
			strCatFilename += "cat"
			catFileStream = fopen strCatFilename "wb"
			WriteLong catFileStream expNumAnims #unsigned-- first write the number of animations
			
			for i in #{1..expNumAnims} do
			(
				WriteLong catFileStream (expAnimNames[i].count + 1) #unsigned
				WriteString catFileStream expAnimNames[i]
				WriteLong catFileStream expAnimTickStart[i] #unsigned
				WriteLong catFileStream expAnimTickEnd[i] #unsigned
				WriteLong catFileStream expAnimFrameStart[i] #unsigned
				WriteLong catFileStream expAnimFrameEnd[i] #unsigned
			)
			fclose catFileStream
			
			strOrigFilename = maxfilepath + maxfilename
			strOutputFilename = substring strOrigFilename 1 (strOrigFilename.count - 4)
			
			if strConverter.count != 0 then
			(
				strCommand = "\"" + strConverter + "\"" + " -inx " + strXFilename + " -incat " + strCatFilename;
				
				if strTexCopyPath.count != 0 then
				(
					strCommand += (" -copytex " + strTexCopyPath);
				)
				
				strCommand += (" -out " + strOutputFilename + " -obj -act -sto -ct");
				print strCommand
				DosCommand strCommand
			)
			
			if strCopyPath.count != 0 then
			(
				strCommand = "Copy " + "\"" + strOutputFilename + ".act " + "\" \"" + strCopyPath + "\"";
				print strCommand
				DosCommand strCommand
				strCommand = "Copy " + "\"" + strOutputFilename + ".obj " + "\" \""  + strCopyPath + "\"";
				print strCommand
				DosCommand strCommand
				strCommand = "Copy " + "\"" + strOutputFilename + ".sto " + "\" \""  + strCopyPath + "\"";
				print strCommand
				DosCommand strCommand
			)
		)catch(
			MessageBox "Undefine Animation Table. \n Please use KOKII Modifier to edit info of animation table."
		)
	)
	else if bPhysique == false and bKK2Modifier == false and maxfilename.count > 0 then
	(
		strOrigFilename = maxfilepath + maxfilename
		strXFilename = substring strOrigFilename 1 (strOrigFilename.count - 3)
		strXFilename += "x"
		LagerExportXFile strXFilename true false
		
		strOrigFilename = maxfilepath + maxfilename
		strOutputFilename = substring strOrigFilename 1 (strOrigFilename.count - 4)
		
		if strConverter.count != 0 then
		(
			strCommand = ""
			if (bGroundObject == true) then
			(
				strCommand = "\"" + strConverter + "\"" + " -inx " + strXFilename;
				if strTexCopyPath.count != 0 then
				(
					strCommand += (" -copytex " + strTexCopyPath);
				)
				
				strCommand += (" -out " + strOutputFilename + " -obj -sto -ct")
			)
			else
			(
				strCommand = "\"" + strConverter + "\"" + " -inx " + strXFilename;
				if strTexCopyPath.count != 0 then
				(
					strCommand += (" -copytex " + strTexCopyPath);
				)
				
				strCommand += (" -out " + strOutputFilename + " -obj -ct")				
			)
			print strCommand
			DosCommand strCommand
		)
		
		if strCopyPath.count != 0 then
		(
			strCommand = "Copy " + "\"" + strOutputFilename + ".sto\" \"" + strCopyPath + "\"";
			print strCommand
			DosCommand strCommand
			strCommand = "Copy " + "\"" + strOutputFilename + ".obj\" \"" + strCopyPath + "\"";
			print strCommand
			DosCommand strCommand
		)
	)
	else if bPhysique == true and bKK2Modifier == true and bEffectModel == true and maxfilename.count > 0 then
	(
		expNumAnims = 0;
		expAnimNames = #()
		expAnimTickStart = #()
		expAnimTickEnd = #()
		expAnimFrameStart = #()
		expAnimFrameEnd = #()
		
		expMod = undefined;
		for i in objects do 
		(
			mod = IsHavAnimTable i 
			if( mod != undefined ) then
				expMod = mod;
		)
		try
		(
			expNumAnims = expMod.anames.count
			for i in expMod.anames do append expAnimNames i;
			for i in expMod.afframes do append expAnimFrameStart i;
			for i in expMod.alframes do append expAnimFrameEnd i;
			for i in expMod.afframes do append expAnimTickStart (i * ticksPerFrame);
			for i in expMod.alframes do append expAnimTickEnd (i * ticksPerFrame);
			
			for i in #{1..expNumAnims} do
			(
				format "[%] ==> TickStart(%), TickEnd(%), FrmStart(%)\n" expAnimNames[i] expAnimTickStart[i] expAnimTickEnd[i] expAnimFrameStart[i] expAnimFrameEnd[i]
				if( expAnimFrameStart[i] == expAnimFrameEnd[i] ) then
				(
					MessageBox "动作表中有无效的动作."
				)
			)
			
			strOrigFilename = maxfilepath + maxfilename
			strXFilename = substring strOrigFilename 1 (strOrigFilename.count - 3)
			strXFilename += "x"
			LagerExportXFile strXFilename true true
			
			strOrigFilename = maxfilepath + maxfilename
			strCatFilename = substring strOrigFilename 1 (strOrigFilename.count - 3)
			strCatFilename += "cat"
			catFileStream = fopen strCatFilename "wb"
			WriteLong catFileStream expNumAnims #unsigned-- first write the number of animations
			
			for i in #{1..expNumAnims} do
			(
				WriteLong catFileStream (expAnimNames[i].count + 1) #unsigned
				WriteString catFileStream expAnimNames[i]
				WriteLong catFileStream expAnimTickStart[i] #unsigned
				WriteLong catFileStream expAnimTickEnd[i] #unsigned
				WriteLong catFileStream expAnimFrameStart[i] #unsigned
				WriteLong catFileStream expAnimFrameEnd[i] #unsigned
			)
			fclose catFileStream
			
			strOrigFilename = maxfilepath + maxfilename
			strOutputFilename = substring strOrigFilename 1 (strOrigFilename.count - 4)
			
			if strConverter.count != 0 then
			(
				strCommand = "\"" + strConverter + "\"" + " -inx " + strXFilename + " -incat " + strCatFilename;
				
				if strTexCopyPath.count != 0 then
				(
					strCommand += (" -copytex " + strTexCopyPath);
				)
				strCommand += (" -out " + strOutputFilename + " -obj -act -ct");
				print strCommand
				DosCommand strCommand
			)
			
			if strCopyPath.count != 0 then
			(
				strCommand = "Copy " + "\"" + strOutputFilename + ".act " + "\" \"" + strCopyPath + "\"";
				print strCommand
				DosCommand strCommand
				strCommand = "Copy " + "\"" + strOutputFilename + ".obj " + "\" \"" + strCopyPath + "\"";
				print strCommand
				DosCommand strCommand
			)
		)catch(
			MessageBox "Undefine Animation Table. \n Please use KOKII Modifier to edit info of animation table."
		)
	)
	else if bPhysique == true and bKK2Modifier == false and bEffectModel == true and maxfilename.count > 0 then
	(
		strOrigFilename = maxfilepath + maxfilename
		strXFilename = substring strOrigFilename 1 (strOrigFilename.count - 3)
		strXFilename += "x"
		LagerExportXFile strXFilename true false
		
		strOrigFilename = maxfilepath + maxfilename
		strOutputFilename = substring strOrigFilename 1 (strOrigFilename.count - 4)
		
		if strConverter.count != 0 then
		(
			strCommand = ""

			strCommand = "\"" + strConverter + "\"" + " -inx " + strXFilename;
			if strTexCopyPath.count != 0 then
			(
				strCommand += (" -copytex " + strTexCopyPath);
			)
			
			strCommand += (" -out " + strOutputFilename + " -obj -ct")

			print strCommand
			DosCommand strCommand
		)
		
		if strCopyPath.count != 0 then
		(
			strCommand = "Copy " + "\"" + strOutputFilename + ".obj\" \"" + strCopyPath + "\"";
			print strCommand
			DosCommand strCommand
		)
		
		MessageBox "yy: 没 act 文件 动画没有用! "
	)
)