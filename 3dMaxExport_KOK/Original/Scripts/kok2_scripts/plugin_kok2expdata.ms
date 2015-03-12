plugin SimpleMod ExportableDataModifier
	name:"KOKIII"
	category:"Kok2"
	classID:#(0x5ffb3ef5, 0x5a6a3550)
	version:2
	initialRollupState:0x02
(
	local a_names = #();
	
	parameters panim rollout:ranim
	(
		anames type:#stringTab tabSizeVariable:true
		afframes type:#intTab tabSizeVariable:true
		alframes type:#intTab tabSizeVariable:true
		
		fframe type:#integer ui:fframeSP
		lframe type:#integer ui:lframeSP
	)
	
	rollout ranim "Animation Export Settings"
	(
		button batchAdd "Batch Add" align:#left width:70 across:2
		spinner batchNum "num" align:#right fieldwidth:30 type:#integer range:[1, 999, 20]
		button loadcat "Load CAT file" align:#left width:80
		group "Animations"
		(
			button addButton "Add" align:#left width:80 across:2
			button delButton "Delete" align:#right width:40
			combobox namesCB align:#left height:22 width:140 items:a_names
			label lab2234 "Frames" align:#left
			spinner fframeSP "from " align:#right fieldwidth:40 type:#integer across:2 range:[animationRange.start, animationRange.end, animationRange.start]
			spinner lframeSP "to " align:#right fieldwidth:40 type:#integer range:[animationRange.start, animationRange.end, animationRange.start]
		)
		
		on batchAdd pressed do
		(
			for i in #{1..batchNum.value} do
			(
				strTemp = i as string;
				if strTemp.count < 2 then strTemp = "00" + strTemp;
				if strTemp.count < 3 then strTemp = "0" + strTemp;
				
				append a_names strTemp
				append anames strTemp
				append afframes 0
				append alframes 0
			)
			
			max motion mode
			max modify mode
		)
		
		on loadcat pressed do
		(
			strCatFile = GetOpenFileName()
			if(strCatFile != undefined) then
			(
				a_names = #()
				anames = #()
				afframes = #()
				alframes = #()
				CatFileStream = fopen strCatFile "rb"
				numAnims = ReadLong CatFileStream #unsigned
				for i in #{1..numAnims} do
				(
					value = ReadLong CatFileStream #unsigned
					strValue = ReadString CatFileStream
					append a_names strValue
					append anames strValue
					
					format "anim=% name = %\n" i strValue
					
					value = ReadLong CatFileStream #unsigned
					
					value = ReadLong CatFileStream #unsigned
					
					value = ReadLong CatFileStream #unsigned
					append afframes value
					
					value = ReadLong CatFileStream #unsigned
					append alframes value
				)
				fclose CatFileStream
			)
			
			max motion mode
			max modify mode
		)
		
		on addButton pressed do
		(
			if(namesCB.text != "") then
			(
				append a_names namesCB.text
				append anames namesCB.text
				append afframes fframe
				append alframes lframe
				
				max motion mode
				max modify mode
			)
		)
		
		on delButton pressed do
		(
			if((namesCB.items.count > 0) and (namesCB.selection > 0)) then
			(
				ind = namesCB.selection
				deleteItem a_names ind
				deleteItem anames ind
				deleteItem afframes ind
				deleteItem alframes ind
				
				max motion mode
				max modify mode
			)
		)
		
		on namesCB selected num do
		(
			if(namesCB.items.count >= num) then
			(
				fframe = afframes[num]
				lframe = alframes[num]
			)
		)
		
		on fframeSP changed val do
		(
			if((namesCB.items.count > 0) and (namesCB.selection > 0)) then
			(
				afframes[namesCB.selection] = fframe
			)
		)
		
		on lframeSP changed val do
		(
			if((namesCB.items.count > 0) and (namesCB.selection > 0)) then
			(
				alframes[namesCB.selection] = lframe
			)
		)
	)
	
	on load do
	(
		a_names = #()
		for str in anames do
		(
			append a_names str
		)
	)
)