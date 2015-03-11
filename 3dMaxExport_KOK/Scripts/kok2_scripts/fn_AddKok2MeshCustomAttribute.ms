fn AddKok2MeshCustomAttribute obj ca = 
(
	nuCustAttr = custAttributes.count obj
	foundIndex = -1
	
	for i = 1 to numCustAttr do
	(
		attrDef = custAttributes.getdef obj i
		if attrDef != undefined and attrDef.name == ca.name do
		(
			foundIndex = i
		)
	)
	
	if foundIndex > 0 do
	(
		strContents = "Remove Custom Attributes from '"
		strContents = strContents + (obj.name as string)
		strContents = strContents + "'?"
		bRemove = queryBox strContents title:"Warning" beep:false
		
		if bRemove do
		(
			custAttributes.delete obj foundIndex
		)
	)
	
	if foundIndex <= 0 do
	(
		custAttributes.add obj ca
	)
)