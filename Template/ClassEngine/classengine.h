#pragma once

#include <algorithm>
#include <mutex>
#include <functional>

#pragma pack(1)

#include "assert.h"
#include "Resfile.h"
#include "CompactArray.h"
#include "pool.h"
#include "TagsList.h"
#include "StrHash.h"
#pragma warning( disable : 4297)
#pragma warning( disable : 4180)
#pragma warning( disable : 4091)
#include "unihash.h"
#include "SimplestHashes.h"
#include "haser.h"

#ifdef COMMS_WINDOWS
#define SAFETYPE
#endif

const int nCP_Branches=256;

bool IsHidden(const  char* s,const char* host);

class BaseClass;
class Enumerators;
class Enumerator;
class  OneClassStorage{
public:
	OneClassStorage(){
		OneMemb=NULL;
		CurrentSet=-1;
		ClassTopic=NULL;
	}
	~OneClassStorage();
	int CurrentSet;
	BaseClass* OneMemb;
	comms::cList<char*>Children;
	comms::cList<char*>Parents;
	CompactStringsHash MembIDS;
	char* ClassTopic;

	bool	CheckChildren	(const char* ChildrenName);
	bool	CheckParent		(const char* ParentName  );
	bool	CheckAll		(const char* string, bool inParent, bool inChildren, bool FullCompatibility);
	void    Clear();
private:
	bool	CheckString( comms::cList<char*>* pList, const char* string, bool FullCompatibility=true );
};
inline bool ___ifonce(bool& _one) {
	if (_one) {
		_one = false;
		return true;
	}
	return false;
}

template <typename X>
class __keep {
public:
	X temp;
	X* ref;
	__keep(X& k) {
		temp = k;
		ref = &k;
	}
	~__keep() {
		*ref = temp;
	}
};
#define ___LINE_NAME( prefix ) ___JOIN( prefix, __LINE__ )
#define ___JOIN( symbol1, symbol2 ) ____DO_JOIN( symbol1, symbol2 )
#define ____DO_JOIN( symbol1, symbol2 ) symbol1##symbol2

#define auto_keep(x) __keep ___LINE_NAME(temp)(x)
#define auto_keep_ex(temp,x) __keep ___LINE_NAME(temp)(x)

//////////////////////////////////////////////////////////////////////////
///////////                  STATIC ENUMERATOR                ////////////
//////////////////////////////////////////////////////////////////////////

class  Enumerator{
	CompactStringsHash Strings;
	comms::cList<DWORD> Values;
public:
	Enumerator(){
		
	}	
	~Enumerator(){
        
	}
	CompactStringsHash Topics;	
	comms::cList<DWORD> TopicRefs;
	char* EnumeratorID;
	void  Add(const char* s){
		Add(s,Values.GetAmount());
	}
	void  Add(const char* s,DWORD V){
		int id=Strings.find(s);
		if(id!=-1){			
			Values[id]=V;            
		}else{
			Strings.add(s);
			Values.Add(V);
			TopicRefs.Add(0xFFFFFFFF);
		}
	}
	void  Insert(int pos,const char* s,DWORD V,const char* Topic){
		int tid=Topics.find(Topic);
		if(tid==-1){
			Topics.add(Topic);
			tid=Topics.find(Topic);
		}
		Strings.add(s);
		Values.Add(V);
		TopicRefs.Add(tid);
	}
	void  Add(const char* s,DWORD V,const char* Topic){
		int id=Strings.find(s);
		int tid=Topics.find(Topic);
		if(tid==-1){
            Topics.add(Topic);
			tid=Topics.find(Topic);
		}
		if(id!=-1){			
			Values[id]=V;            
		}else{
			Strings.add(s);
			Values.Add(V);
			TopicRefs.Add(tid);
		}
	}
	void  Add(const char* s,const char* Topic){
		Add(s,Values.GetAmount(),Topic);
	}
	DWORD Get(const char* s) const {
		int idx=Strings.find(s);
		if(idx!=-1){
			return Values[idx];
		}else return -1;
	}
	const char* Get(DWORD V){
		int idx=Values.find(V);
		if(idx!=-1){
            return Strings.get(idx);
		}else return "";
	}
    comms::cStr GetStr( int idx ) const{
        if ( idx<Values.GetAmount() )return Strings.get( idx );
        return "";
    }
    const char* GetStr( int idx ){
		if(idx<Values.GetAmount())return Strings.get(idx);
		return "";
	}
	DWORD GetVal(int idx) const {
		if(idx<Values.GetAmount())return Values[idx];

		return 0;
	}
	int GetAmount() const {
		return Values.GetAmount();
	}
	bool IsEmpty() const {
		return (GetAmount() == 0);
	}
	int FindStr(const char* s) const {
		int idx=Strings.find(s);
		if(idx!=-1)return idx;
		return -1;
	}
	int FindVal(DWORD v) const {
		int idx=Values.find(v);
		if(idx!=-1)return idx;
		return -1;
	}
	void Clear(){
		Strings.clear();
        Values.Clear();
		Topics.clear();	
		TopicRefs.Clear();
	}
	virtual char* GetCategory(int idx){
		if(idx<Values.GetAmount()){
            DWORD id=TopicRefs[idx];
			if(id!=0xFFFFFFFF){
                return Topics.get(id);
			}
			return NULL;
		}
		return NULL;
	}	
};
class  Enumerators{
    typedef comms::cList< Enumerator* >  enums_t;
	enums_t Enums;
	StringsHash EnumNames;
public:
	Enumerator* Create(const char* Name);
	Enumerator* Get(const char* Name);
    const enums_t& Get() const { return Enums; }
	void ClearAll();
};

extern  Enumerators ENUM;

class  ClassGarbage{
public:
	comms::cList<OneClassStorage*> Storage;
	StringsHash NamesHash;

	//ClassGarbage();
	//~ClassGarbage();
	OneClassStorage* GetClass(const char* ClassName);
	OneClassStorage* CreateClassStorage(const char* ClassName);
};
extern  void TestClassStorage(OneClassStorage** OCS);
#define AUTONEW(x) \
	virtual int GetClassSize() const override {\
		return sizeof(*this);\
	}\
	virtual BaseClass* new_element() const override {\
		BaseClass* T=new x;\
		return T;\
	}

extern  ClassGarbage CGARB;
struct ClassExpParams{
	comms::cList<char*> ExpList;
	comms::cList<char*> TopicsList;
	comms::cList<int>   TopicsIdxs;
};
struct iRct{
	iRct(){};
	iRct(int a,int b,int c,int d){
		x=a;y=b;w=c;h=d;
	}
	int x,y,w,h;
};
class CECopyContext{
public:
	CECopyContext(){
		CopyGlobalID=0;
	}
	comms::cList<DWORD> LocalClassIDS;
	DWORD CopyGlobalID;
};



class Rct;
class BaseWidget;

/**
\brief Context for creationg own class editor control.
\details
The structure is passed to BaseClass::OnCreateControlFromScratch
*/
struct ClassEditorContext{
	BaseClass* BC;
	///Ptr to data that corresponds BaseClass, it is equal to class pointer if class supports dicect casting (CheckDirectCasting returs true)
	void* Ptr;
	///pointer to the custom static data used, for example, for _index
	void* Extra;
	///
	BaseClass* ParentClass;
	///Field name without name modifiers, it is never NULL
	const char* FieldName;
	///Field name as is after registration, including all name modifiers, it is never NULL
	const char* FullFieldName;
	///HintID for the item, may be NULL
	const char* HintID;
	///Name of parent class
	const char* ParentClassType;
	///Identifier of the field, used as part of the Name field of the Widget. See CtrlFSlider and CtrlISlider as usage example.
	const char* id;
	///The field is read only
	bool ReadOnly;
	///default height of usual controls
	int DefYSize;
	///Color of background for the control
	DWORD CurrGlobalColor;
	///Color of the font for the control
	DWORD CurrGlobalFontColor;
	///Control is mandatory left-aligned
	bool Lalign;
	///Proportion (0..1) between left and right part of the control if it is two-component, like ComboBox or input line
	float LeftRightProportion;
	///true if beed to apply additional scale for numerical controls
	bool ApplyScale;
	///Additional scale for numerical controls
	float ExScale;
	///Parent widget
	BaseWidget* ParentW;
	///GroupID for checkbox
	int GroupID;
	///icon 
	const char* icon;
};
typedef std::tuple<> _empty;

#include "BaseClass.h"

#ifdef SAFETYPE
#define typerr(field)\
	if(!m->CheckCompartabilityWith(typeid(field).name(),sizeof(field))){\
		comms::cMessageBox::Ok("Incompartible type used for %s %s::%s : %s",typeid(field).name(),GetClassName(),#field,m->GetClassName());\
	};
#else
#define typerr(field)
#endif 

#define __constructor(x)void reset_class(void* p){((x*)p)->Init();};x(){Init();};void Init()

/**
\def REG_MEMBER(type,fieldID)
Use this command when `fieldID` is not derived from `BaseClass`.
\see REG_AUTO
*/
#define REG_MEMBER(type,fieldID) REG_TYPE_ANYTHING(fieldID,type,#fieldID,nullptr);
/// Use this command when `fieldID` is not derived from `BaseClass`.
/// \see REG_AUTO
#define REG_MEMBER_EX(type,fieldID,Name)REG_TYPE_ANYTHING(fieldID,type,#Name,nullptr);
/// \see REG_MEMBER_EX
#define REG_MEMBER_EX2(type,fieldID,Name)REG_TYPE_ANYTHING(fieldID,type,Name,nullptr);

#define REG_ISLIDER_EX2(nField, Min, Max, Def, Name)\
	{\
		static CtrlISliderArgs *pArgs = nullptr;\
		if(!pArgs){\
			pArgs = new CtrlISliderArgs;\
			pArgs->MinValue = Min, pArgs->MaxValue = Max, pArgs->DefValue = Def;\
		}\
		REG_TYPE_ANYTHING(nField,CtrlISlider,Name,pArgs);\
	}
//-----------------------------------------------------------------------------
// REG_FSLIDER
//-----------------------------------------------------------------------------
#define REG_FSLIDEREX2(fField, Min, Max, Def, VisMod, _Inv, newname)\
	{\
		static CtrlFSliderArgs *pArgs = nullptr;\
		if(!pArgs){\
			pArgs = new CtrlFSliderArgs;\
			pArgs->MinValue = Min, pArgs->MaxValue = Max, pArgs->DefValue = Def;\
			pArgs->VisModulator = VisMod;pArgs->Inv = int(_Inv)==1;pArgs->SwapEnds = int(_Inv)==2;\
		}\
		REG_TYPE_ANYTHING(fField,CtrlFSlider,newname,pArgs);\
	}

#define REG_FSLIDER_EX2(fField, Min, Max, Def, Name) REG_FSLIDEREX2(fField, Min, Max, Def,1.0,0,Name);

#define REG_FSLIDER(fField, Min, Max, Def)REG_FSLIDER_EX2(fField, Min, Max, Def,#fField);

#define REG_FSLIDEREX(fField, Min, Max, Def, VisMod, _Inv) REG_FSLIDEREX2(fField, Min, Max, Def,VisMod,_Inv,#fField);

#define IREG_M4D(M)\
{\
	float* P=M.ToFloatPtr();\
	int L=strlen(#M);\
	for(int i=0;i<4;i++){\
		for(int j=0;j<4;j++){\
			INVISIBLE REG_MEMBER_EX2(_float,*P,BCPrintf("M%d%d",i,j));\
			P++;\
		}\
	}\
}

extern int GlobalTick;
#define ONETIME {static bool __once=false;if(__once)return;__once=true;}

#define SAVE_SECTION(x) if(result)result->Mask=x;

 BaseClass* _getClassFromPalette(const char* classname);
template <class X>
X* _get_cmemb(X* S,const char* name){
    X* bc=(X*)_getClassFromPalette(name);
	if(!bc){
		X* x=new X;
        reg_class(x);
		delete(x);
		bc=(X*)_getClassFromPalette(name);
	}
	if(!bc)bc=new X;
	return bc;
}
inline const char* ConvTypeName(comms::cStr& D){
	D.Replace("struct ","");
	D.Replace("class ","");
	D.Replace("<",".");
	D.Replace(">","");
	D.Replace(",",".");
	return D.ToCharPtr();
}
 void reg_class_bc(BaseClass* BC, char* Topic, char* Typeid, bool AutoMode);
template <class X>
void reg_class(X* x, char* Topic = NULL) {
	//reg_class_bc(x,Topic,(char*)typeid(X).name(),false);	
	reg_class_bc(x, Topic, (char*)x->GetClassName(), false);
}
template <class X>
void reg_class_auto(X* x, char* Topic = NULL) {
	//reg_class_bc(x,Topic,(char*)typeid(X).name(),true);		
	reg_class_bc(x, Topic, (char*)x->GetClassName(), true);
}
template <class X>
void __set_parent(BaseClass* P, X& el) {
	el.SetParent(P);
}
#define reg_auto_specialisation_template(base,myclass) \
	template <>\
	inline void __set_parent<myclass>(BaseClass* P, myclass& el) {\
	}\
	template <>\
	inline void reg_class_auto(myclass* x, char* Topic) {\
	}\
	template <>\
	inline BaseClass* _conjugate(myclass& x) {\
		static base* X = new base;\
		return X;\
	}

inline void UNREG_CLASS(char* Name){
	OneClassStorage*OCS=CGARB.GetClass(Name);	
	if(OCS&&OCS->OneMemb){
		delete(OCS->OneMemb);
		OCS->OneMemb=NULL;
	}	
}
/*template <class X,class Y>
void reg_class_ex(X* x,Y* y,char* Topic=NULL){
	X* elm=dynamic_cast<X*>(x->new_element());
	if(!elm)return;
	OneClassStorage*OCS=CGARB.GetClass(x->GetClassName());
	if(!OCS)OCS=CGARB.CreateClassStorage(x->GetClassName());
	if(OCS->OneMemb){
		delete(elm);
	}else OCS->OneMemb=(Y*)elm;
	if(!OCS->Members.GetAmount()){
		elm->RegisterMembers();
	}
	if(Topic&&!OCS->ClassTopic){
		OCS->ClassTopic=new char[strlen(Topic)+1];
		strcpy(OCS->ClassTopic,Topic);
	}
}*/
/// Registering member that is class, derived from `BaseClass`.
#define REG_AUTO_EX(x,Name)     REG_AUTO_ANYTHING(x,#Name);
/// Registering member that is class, derived from `BaseClass`.
#define REG_AUTO_EX_EMPTY(x)    REG_AUTO_ANYTHING(x,"");
/// Registering member that is class, derived from `BaseClass`.
#define REG_AUTO_EX2(x,Name)    REG_AUTO_ANYTHING(x,Name);

#include "useful_macro.h"
#include "class_reg.h"

/**
\breif Registering class type that can be created by new.
\details
For example, if you are using `ClassArray< SomeClass >`, then you
must register classes, that can be stored in this array.
*/

#define REG_CLASS(x) {\
	static x*m = nullptr;\
	if(!m){\
		m = new x;\
		reg_class(m);\
		delete(m);\
		}\
	}

/**
\brief Registering parent class.
\details
Deriving from several classses is not supported,
but you can derive class from class, that is
already derived from `BaseClass`.
*/
//template <class x>

void reg_parent( BaseClass* bas, BaseClass*m );

#define REG_PARENT(x) x::CountObjects(required_index, counter, hash, result, ForEachElem,OnlyPointersMode); if(required_index<0)return;

#define MARGIN(x) NOSAVE REG_AUTO_EX2(GDLM,"[MARGIN "#x"]");
#define VSPACE(x) NOSAVE REG_AUTO_EX2(GDLM,"[VSPACE "#x"]");
/// A text unediting identifier.
#define TEXTMSG(text) NOSAVE REG_AUTO_EX(GDLM,text)
/// A left aligned text unediting identifier.
#define LTEXTMSG(text) NOSAVE REG_AUTO_EX(GDLM,*text)
/// An empty text unediting identifier.
#define TEXTMSG_EMPTY NOSAVE REG_AUTO_EX_EMPTY(GDLM)
#define TEXTMSG2(text) NOSAVE REG_AUTO_EX2(GDLM,text)

template <class BaseT>
class _stdboolfunction : public BaseClass {
public:
	std::function<bool(BaseT*)> fnc;
	_stdboolfunction() {
	}
	int condition_call(void* data) override {
		if (fnc != NULL) {
			return fnc((BaseT*)data) ? 1 : 0;
		}return 1;
	}
	const char* GetClassName() const override {
		return "_stdboolfunction";
	}
	virtual bool CheckDirectCasting() const {
		return false;
	}
	virtual void Save(TagsList&, void*, void*) override {
	}
	virtual bool Load(TagsList&, void*, void*) override {
		return true;
	}
	AUTONEW(_stdboolfunction);
};
template <class BaseT>
class _stdfunction : public BaseClass {
public:
	std::function<void()> fn;
	std::function<void (BaseT*)> fnc;
	_stdfunction() {
	}
	virtual void UpdateHash(HashSummator& S, void* data, void* extra) override {
		S += cPtrDiff(data);
	}
	void _call() {
		if (fn != NULL)fn();
		//if (fnc != NULL)fnc();
	}
	const char* GetClassName() const override {
		return "_stdfunction";
	}
	virtual bool CheckIfFunction() const override {
		return true;
	}
	virtual bool CheckDirectCasting() const {
		return false;
	}
	virtual int condition_call(void* base) override {
		if (fn != NULL)fn();
		if (fnc != NULL)fnc((BaseT*)base);
		return -1;
	}
	virtual void Save(TagsList&, void*, void*) override {
	}
	virtual bool Load(TagsList&, void*, void*) override {
		return true;
	}
	AUTONEW(_stdfunction);
};

template< class BaseT, class F, class... Args >
std::enable_if_t<std::is_member_function_pointer<F>::value, BaseClass*>
 _get_method_class(F&& f, Args&& ... args) {
	_stdfunction<BaseT>* m = new _stdfunction<BaseT>;
	m->fnc = std::bind(f, std::placeholders::_1, args...);
	return m;
}

template< class BaseT, class F, class... Args >
std::enable_if_t<!std::is_member_function_pointer<F>::value,BaseClass*>
 _get_method_class(F&& f, Args&& ... args) {
	_stdfunction<void>* m = new _stdfunction<void>;
	m->fn = std::bind(f, args...);
	return m;
}

template< class BaseT, class F>
BaseClass* _get_method_bool(F&& f) {
	_stdboolfunction<BaseT>* m = new _stdboolfunction<BaseT>;
	m->fnc = std::bind(f, std::placeholders::_1);
	return m;
}

inline cPtrDiff _rotprt(const void* ptr) {
	cPtrDiff d = (cPtrDiff)ptr;
	return (d >> 3) | ((d & 3) << (sizeof(cPtrDiff) * 8 - 3));
}
template<class Type>
inline bool BaseClass::valid() const
{
	std::scoped_lock sl(*pmutex);
	bool res = false;
	if (presence->get(_rotprt(this))) {
		res = dynamic_cast<const Type*>(this) != NULL;
	}
	return res;
}

template <typename type>
type* BaseClass::FindParent() {
	BaseClass* P = ParentBC;
	while(P && P->valid()) {
		type* t = dynamic_cast<type*>(P);
		if (t)return t;
		P = P->ParentBC;
	}
	return nullptr;
}

template<>
inline bool BaseClass::valid<BaseClass>() const
{
	std::scoped_lock sl(*pmutex);
	bool res = presence->get(_rotprt(this)) != nullptr;
	return res;
}

inline const char* BaseClass::GetCurrentSaveFile() { return CurrentSaveFile; }

inline void BaseClass::UpdateClassMembersAndMask( bool recursive ) {
	if (CheckDirectCasting()) {
		_ClassMask = GetClassMask();
		if (recursive) {
			_EACH(this, el) {
				if (el.BC && el.Ptr) {
					if (el.BC->CheckDirectCasting()) {
						el.BC->SimplySetParent(this);
					}
					el.BC->UpdateClassMembersAndMask(recursive);
				}
			} _EACH_FAST_END
		}
	}
}
inline BaseClassElement::BaseClassElement() {
	reset();
}

inline void BaseClassElement::fill(void* _Ptr, void* _Extra, bool _vis, bool _ui, bool OnlyPointersMode) {
	Ptr = _Ptr;
	Extra = _Extra;
	if (!OnlyPointersMode)ID = TagsList::GetConstantLocation(RegOpt.ToCharPtr());
	Visible &= _vis & BaseClass::UI_definition;
	Serialize &= _ui & BaseClass::Serialization;
}

inline void BaseClassElement::reset() {
	RegOpt.Clear();
	ID = "";
	BC = nullptr;
	Ptr = nullptr;
	Extra = nullptr;
	ID = nullptr;
	Visible = true;
	Serialize = true;
	ReadOnly = false;
	Mask = 0xFFFFFFFF;
	ApplyScale = false;
	Noname = false;
	Noreset = false;
	Scaling = 1.0;
	CachedIndex = 0xFFFF;
	CachedValue = true;	
}

inline void BaseClassElement::minimal_reset() {
	RegOpt.Clear();
	ID = "";
	BC = nullptr;
	Ptr = nullptr;
	Extra = nullptr;
	Visible = true;
	Noreset = false;
	Serialize = true;
	ReadOnly = false;
}

void StrToFile(const comms::cStr& src, const char* FileName);
bool StrFromFile(comms::cStr& dest, const char* FileName);


#include "classlist.h"
#include "bitset.h"
#include "more_types.h"

#define REG_NAVI(Navi) REG_TYPE_GENERAL(GDLM,&GDLM,"@NaviControl@",&Navi);

#pragma pack()
