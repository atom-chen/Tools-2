function Kok2_RemoveMenu = 
(
	local menu = menuMan.findMenu "KingOfKongsII";
	if menu != undefined then
	(
		menuMan.unRegisterMenu menu;
		menuMan.updateMenuBar();
	)
)

function kok2_AddMenu = 
(
	local bCreateMenu = false
	
	if menuMan.registerMenuContext 0x53671218 then
	(
		bCreateMenu = true
	)
	else
	(
		if (menuMan.findMenu "KingOfKongsII") == undefined then
			bCreateMenu = true
	)
	
	if bCreateMenu then
	(
		local mainMenu = menuMan.getMainMenuBar()
		local kok2Menu = menuMan.createMenu "KingOfKongsII"
		
		local ItemsTemp = #()
		append ItemsTemp (menuMan.createActionItem "macro_floaterKok2Exporter" "Kok2Exporter")
		
		append ItemsTemp (menuMan.createActionItem "macro_Kok2MeshCustomAttribute" "Kok2MeshCustomAttribute")
		
		for i=1 to ItemsTemp.count do
		(
			kok2Menu.addItem ItemsTemp[i] -1
		)

		local subMenuItem = menuMan.createSubMenuItem "KingOfKongsII" kok2Menu
		local subMenuIndex = mainMenu.numItems() - 1
		mainMenu.addItem subMenuItem subMenuIndex
		menuMan.updateMenuBar()
	)
)

function kok2_LoadMenu = 
(
	Kok2_RemoveMenu()
	
	kok2_AddMenu()
)