'''
Created on 2015Äê3ÔÂ16ÈÕ

@author: luguhu
'''
import MaxPlus

somethingHappened = False
def doSomething():
	global somethingHappened 
	somethingHappened = True
	print 'Something happened'
	
def Kok2_RemoveMenu():
	MaxPlus.MenuManager.UnregisterMenu(u"KingOfKongsII")

def kok2_AddMenu():
	bCreateMenu = False
	name = u"KingOfKongsII"
	if not MaxPlus.MenuManager.MenuExists(name):
		bCreateMenu = True
	
	if bCreateMenu:
		mb = MaxPlus.MenuBuilder(name)
		
		action = MaxPlus.ActionFactory.Create("macro_floaterKok2Exporter", "Kok2Exporter", doSomething)
		if action._IsValidWrapper():
			mb.AddItem(action)
			mb.AddSeparator()
		action = MaxPlus.ActionFactory.Create("macro_Kok2MeshCustomAttribute", "Kok2MeshCustomAttribute", doSomething)
		if action._IsValidWrapper():
			mb.AddItem(action)
			mb.AddSeparator()
			
		#menu = mb.Create(MaxPlus.MenuManager.GetMainMenu())
		mb.Create(MaxPlus.MenuManager.GetMainMenu())

def kok2_LoadMenu():
	Kok2_RemoveMenu()
	kok2_AddMenu()

kok2_LoadMenu()