macroScript macro_Kok2MeshCustomAttribute
	category:"Kok2MeshCustomAttribute"
	buttonText:"CustomAttribute"
	tooltip:"Add Kok2 Mesh CustomAttribute"
	Icon:#("kok2", 2)
(
	on execute do
	(
		for obj in selection do
		(
			AddKok2MeshCustomAttribute obj Kok2MeshOptionsCA
		)
		
		max modify mode
	)
)