#pragma once

#pragma warning( disable : 4002)
#pragma warning( disable : 4003)


#define __COUNTOBJ CountObjects(int& required_index, int* counter, HashSummator* hash, BaseClassElement* result, const std::function<bool(BaseClassElement*)>* ForEachElem, bool OnlyPointersMode)
#define __ADDREG(x) if(OnlyPointersMode == false && (ForEachElem || (required_index == 0 && result)))result->RegOpt+=x;
#define __FIELD(x,value) if(ForEachElem || (required_index == 0 && result))result->x = value;
template <class type>
inline BaseClass* _conjugate(type& x) {
	static type* X = new type;
	return X;
}
template <class type>
inline BaseClass* _exemplar() {
	static type* X = new type;
	return X;
}

#define REG_TYPE_GENERAL(x,bc_ptr,Name,ExtraPtr) { \
	if(counter)(*counter)++;\
	if(hash){\
		using _type = decltype(x);\
		BaseClass* B=bc_ptr;\
		if(B->CheckDirectCasting())B=(BaseClass*)&x;\
		B->UpdateHash(*hash, &x, nullptr);\
	}\
	if(required_index == 0 && result){\
		result->BC=bc_ptr;\
		if(result->BC->CheckDirectCasting()){\
			result->BC=(BaseClass*)&x;\
			result->BC->SimplySetParent((BaseClass*)this);\
		}\
		if(!OnlyPointersMode)result->RegOpt += comms::cStr(Name);\
		bool enable=(result->Mask & _ClassMask) != 0;\
		result->fill((void*)&x, ExtraPtr, enable, enable,OnlyPointersMode);\
		if(ForEachElem){\
			if ((*ForEachElem)(result))return; \
		} else{\
			required_index--;\
			return;\
		}\
	}\
	if(!ForEachElem)required_index--;\
}

#define REG_AUTO_ANYTHING(x,Name) REG_TYPE_GENERAL(x,_conjugate(x),Name,nullptr)
#define REG_TYPE_ANYTHING(x,type,Name,ExtraPtr) REG_TYPE_GENERAL(x,_exemplar<type>(),Name,ExtraPtr)

#define _FUNCDEF_REALTIME2(method,name) \
	if(counter)(*counter)++;\
	if(hash){\
		(*hash) << #method;\
	}\
	if(required_index == 0 && result && !OnlyPointersMode){\
		const char* cname = name;\
		using myclass = std::remove_pointer<decltype(this)>::type;\
		static BaseClass* m=_get_method_class<myclass>(&myclass::method);\
		result->RegOpt += comms::cStr(cname);\
		bool enable = (result->Mask & _ClassMask) != 0;\
		result->BC = m;\
		result->fill(this, nullptr, enable,false,OnlyPointersMode);\
		if(ForEachElem){\
			if ((*ForEachElem)(result))return;\
		} else{\
			required_index--;\
			return;\
		}\
	}\
	if(!ForEachElem)required_index--;

#define _FUNCDEF_REALTIME3(method,name,...) \
	if(counter)(*counter)++;\
	if(hash){\
	    (*hash) << #method;\
	}\
	if(required_index == 0 && result && !OnlyPointersMode){\
	    const char* cname = name;\
	    using myclass = std::remove_pointer<decltype(this)>::type;\
	    static BaseClass* m=_get_method_class<myclass>(&myclass::method,__VA_ARGS__);\
	    result->RegOpt += comms::cStr(cname);\
	    bool enable = (result->Mask & _ClassMask) != 0;\
	    result->BC = m;\
	    result->fill(this, nullptr, enable,false,OnlyPointersMode);\
	    if(ForEachElem){\
	        if ((*ForEachElem)(result))return;\
	    } else{\
	        required_index--;\
	        return;\
	    }\
	}\
	if(!ForEachElem)required_index--;

#define FUNCTION_CALL1(method) _FUNCDEF_REALTIME2(method, #method)
#define FUNCTION_CALL2(method, name) _FUNCDEF_REALTIME2(method,name)
#define FUNCTION_CALL3(method,name, ...) _FUNCDEF_REALTIME3(method,name,__VA_ARGS__)

#define ICON_BUTTON2(icon,method) _FUNCDEF_REALTIME2(method,"{justicon " icon"}")
#define ICON_BUTTON3(icon,method,name) _FUNCDEF_REALTIME2(method,"{justicon " icon"}" name)
#define ICON_BUTTON4(icon,method,name,...) _FUNCDEF_REALTIME3(method,"{justicon " icon"}" name,__VA_ARGS__)

#define REG_AUTO_1(x) REG_AUTO_ANYTHING(x,#x);
#define REG_AUTO_2(x,Name) REG_AUTO_ANYTHING(x,Name);


#define __FIRST_ARG_(x,...) x
#define __FIRST_ARG(args) __FIRST_ARG_ args
#define MULTI_ARGUMENT(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, ...) a11
#define __VA_ARGS_SIZE(...) MULTI_ARGUMENT(dummy, ## __VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#ifdef COMMS_MACOS
#define GET_THIRD_ARG(Arg1, Arg2, Arg3, ...) Arg3
#define GET_ARG_10(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, ...) Arg10
#endif // macOS
#ifdef COMMS_WINDOWS 
#define GET_THIRD_ARG_(Arg1, Arg2, Arg3, ...) Arg3
#define GET_ARG_10_(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, ...) Arg10
#define GET_THIRD_ARG(tuple) GET_THIRD_ARG_ tuple
#define GET_ARG_10(tuple) GET_ARG_10_ tuple
#endif // Windows

#ifdef COMMS_WINDOWS
#define ARG3_CHOOSER(name1, name2, name3, ...) GET_ARG_10((__VA_ARGS__, name3, name3, name3, name3, name3, name3, name3, name2, name1))(__VA_ARGS__)
#define ARG4_CHOOSER(name1, name2, name3, name4, ...) GET_ARG_10((__VA_ARGS__, name3, name3, name3, name3, name3, name4, name3, name2, name1))(__VA_ARGS__)

#endif // Windows
#ifdef COMMS_MACOS
#define ARG3_CHOOSER(name1, name2, name3, ...) GET_ARG_10(__VA_ARGS__, name3, name3, name3, name3, name3, name3, name3, name2, name1)(__VA_ARGS__)
#define ARG4_CHOOSER(name1, name2, name3, name4, ...) GET_ARG_10(__VA_ARGS__, name3, name3, name3, name3, name3, name4, name3, name2, name1)(__VA_ARGS__)
#endif // macOS

#ifdef COMMS_WINDOWS
#define REG_AUTO_MACRO_CHOOSER(...)\
GET_THIRD_ARG((__VA_ARGS__, REG_AUTO_2, REG_AUTO_1))(__VA_ARGS__)
#endif // Windows
#ifdef COMMS_MACOS
#define REG_AUTO_MACRO_CHOOSER(...)\
GET_THIRD_ARG(__VA_ARGS__, REG_AUTO_2, REG_AUTO_1)(__VA_ARGS__)
#endif // macOS

#define _this_class std::remove_pointer<decltype(this)>::type
const char* _modify_class_name(const char* s);
#define _DEFAULT_NEW \
	virtual const char* GetClassName() const override{\
		const char* s = typeid(_this_class).name();\
        s = _modify_class_name(s);\
		return s;\
	};\
	virtual bool CheckDirectCasting() const override{\
		return true;\
	}\
	virtual int GetClassSize() const override {\
		return sizeof(*this);\
	}\
	virtual BaseClass* new_element() const override{\
		std::remove_const<_this_class>::type* X=new std::remove_const<_this_class>::type;\
		X->SetParents();\
		return X;\
	}

#define __KEEPREGOPT bool _vis = result ? result->Visible : false; bool _ui = result ? result->Serialize : false;
#define __RESTOREREG \
	if(result){\
		result->Visible = _vis;\
		result->Serialize = _ui;\
	}
