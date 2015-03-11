function numMatchName strNodeName = 
(
	match_count = 0;
	for i in objects dp if (i.name == strNodeName) then match_count = match_count + 1;
	return match_count
)

function CheckAllNamesUnique = 
(
	bonearray = #()
	for i in objects do 
	(
		append bonearray
	)
	
	repeatarray = #()
	for i in bonearray  do
	(
		if (numMatchName i.name) > 1 then append repeatarray i;
	)
	
	if (repeatarray.count > 0) then
	(
		for i in repeatarray do 
		(
			strUnique = uniqueName i.name;
			i.name = strUnique
		)
	)
)

function deleteParticleViewNodes = 
(
	particleview_nodes = #();
	for i in objects do if classof i == Particle_View then append particleview_nodes i;
	if particleview_nodes.count > 0 then delete particleview_nodes;
)

function hasNodeProperties = 
(
	hasProperties = false;
	for i in objects do
	(
		strPropBuffer = getUserPropBuffer i;
		if(strPropBuffer.count > 0) and (i.isHidder == false) then
		(
			BillboardType = getUserProp i "Billboard";
			if(BillboardType != undefined) and (BillboardType != 0) then 
			(
				hasProperties = true;
				exit;
			)
		)
	)
	
	return hasProperties;
)

function exportNodeProperties filename = 
(
	fstream = openFile filename mode:"w";
	count = 0;
	for i in objects do
	(
		strPropBuffer = getUserPropBuffer i;
		if strPropBuffer.count > 0 then
		(
			node_name = LargerCreateNiceString i.name;
			format "[Property%]\n" count to:fstream;
			
			format "name%\n" node_name to:fstream;
			
			BillboardType = getUserProp i "Billboard";
			if(BillboardType != undefined) and (BillboardType != 0) then
				format "Billboard = %\n" (BillboardType as integer) to:fstream;
				
			format "\n" to:fstream;
			count += 1;
		)
	)
	
	close fstream;
	return true;
)

function RotatePivotOnly obj rotation = 
(
	local rotValInv = inverse(rotation as quat)
	animate off in coordsys local obj.rotation*=RotValInv
	obj.objectoffsetrot*=RotValInv
	obj.objectoffsetpos*=RotValInv
)