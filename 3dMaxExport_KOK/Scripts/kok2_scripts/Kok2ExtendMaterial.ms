plugin material Kok2ExtMaterial
name:"Kok2 Extended Material"
classID:#(0x1710b1c7, 0x176f2737)
extends:Standard replaceUI:false version:1
(
	parameters Kok2ExtMaterial rollout:Kok2ExtMaterialRollout
	(
		alphablendertype type:#integer default:1 animatable:false ui:Kok2AlphablenderTypes
		
		textureanirows type:#integer default:1 animatable:false ui:Kok2TextureAniRows
		textureanicols type:#integer default:1 animatable:false ui:Kok2TextureAniCols
		textureanirepeat type:#integer default:1 animatable:false ui:Kok2TextureAniRepeat
	)
	
	rollout Kok2ExtMaterialRollout "Kok2Extended Material"
	(
		groupBox grp1 "Alpha Blende Types" pos:[6,6] width:208 height:120
		groupBox grp2 "Texture Animations" pos:[218,6] width:208 height:120
		
		radiobuttons Kok2AlphablenderTypes "" align:#left labels:#("Opaque", "Opaque", "Opaque", "Opaque", "Opaque", "Opaque", "Opaque" ) columns:120
		pos:[16,26]
		
		spinner Kok2TextureAniRows "Rows:" align:#left range:[0,64,1] type:#integer width:96 height:16 pos:[239,26]
		spinner Kok2TextureAniCols "Cols:" align:#left range:[0,64,1] type:#integer width:96 height:16 pos:[246,52]
		spinner Kok2TextureAniRepeat "ËÙ¶È:" align:#left range:[0,999,1] type:#integer width:100 height:16 pos:[228,78]
	)
)