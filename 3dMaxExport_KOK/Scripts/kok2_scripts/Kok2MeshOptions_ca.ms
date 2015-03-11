Kok2MeshOptionsCA = attributes "Kok2MeshOptions"
(
	parameters ExtendedMeshType rollout:ExtendedMeshTypeRollout
	(
		meshtype type:#integer default:1 animatable:false ui:Kok2MeshTypes
		
		ribbonwidth type:#float default:0.5 animatable:false ui:Kok2RibbonWidth
		
		ribbonlength type:#float default:10.0 animatable:false ui:Kok2RibbonLength
	)
	
	rollout ExtendedMeshTypeRollout "Kok2 Extended Mesh Type" width:221 height:96
	(
		radiobuttons Kok2MeshTypes "" pos:[13,7] width:90 height:120 labels:#("BillBoard", "BillBoard Y", "Ribbon", "Zodiac", "VolumeLine" ) columns:1
		
		spinner Kok2RibbonWidth "Width:" pos:[110,44] width:100 height:16 enable:false
		spinner Kok2RibbonLength "Length:" pos:[106,64] width:104 height:16 enable:false
		
		on ExtendedMeshTypeRollout open do
		(
			if meshtype == 3 do
			(
				Kok2RibbonWidth.enable = true
				Kok2RibbonLength.enable = true
			)
		)
		on Kok2MeshTypes changed state do
		(
			if(state == 3) then
			(
				Kok2RibbonWidth.enable = true
				Kok2RibbonLength.enable = true
			)
			else
			(
				Kok2RibbonWidth.enable = false
				Kok2RibbonLength.enable = false
			)
		)
	)
)