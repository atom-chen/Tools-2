#ifndef __AutoDefine_H
#define __AutoDefine_H

#define DECLARE_SET_GET_PFUNC(type,name); \
	type* get##name();\
	void set##name(type* value);

#define DEFINE_SET_GET_PFUNC(className,type,name); \
	type* className::get##name()\
	{\
		return m_##name;\
	}\
	\
	\
	void className::set##name(type* value)\
	{\
		m_##name = value;\
	}

#define DECLARE_SET_GET_RETPFUNC(type,name); \
	type* get##name();\
	void set##name(type* value);

#define DEFINE_SET_GET_RETPFUNC(className,type,name); \
	type* className::get##name()\
	{\
		return &m_##name;\
	}\
	\
	\
	void className::set##name(type* value)\
	{\
		m_##name = *value;\
	}

#define DECLARE_SET_GET_FUNC(type,name); \
	type get##name();\
	void set##name(type value);\

#define DEFINE_SET_GET_FUNC(className,type,name); \
	type className::get##name()\
	{\
		return m_##name;\
	}\
	\
	\
	void className::set##name(type value)\
	{\
		m_##name = value;\
	}

#define DECLARE_SET_GET_REF_FUNC(type,name); \
	type& get##name();\
	void set##name(type& value);\

#define DEFINE_SET_GET_REF_FUNC(className,type,name); \
	type& className::get##name()\
	{\
		return m_##name;\
	}\
	\
	\
	void className::set##name(type& value)\
	{\
		m_##name = value;\
	}

#endif