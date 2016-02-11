#include "LuaCObject.h"
#include "LuaCVM.h"
#include "MemPool.h"

LuaCObject::LuaCObject()
{

}

LuaCObject::~LuaCObject()
{

}

int LuaCObject::GetType()
{
	return m_type;
}

//LuaCObject* LuaCObject::newObject(LuaCVM* luavm)
//{
//	return static_cast<LuaCObject*>(luavm->m_memPool->newMem(MemType::MEM_OBJECT));
//}
//
//void LuaCObject::deleteObject(LuaCVM* luavm, LuaCObject* ptr)
//{
//	luavm->m_memPool->deleteMem(MemType::MEM_OBJECT, ptr);
//}