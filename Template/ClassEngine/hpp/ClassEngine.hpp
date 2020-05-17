#pragma once
#ifdef IMPLEMENT_CLASS_FACTORY

#include "BaseClassIO.hpp"
#include "Resfile.hpp"

Enumerators ENUM;
float ToFloat(const char *str);

OneClassStorage::~OneClassStorage()
{
	if(OneMemb)delete OneMemb;
	OneMemb=NULL;
	for(int i=0;i<Children.GetAmount();i++)if(Children[i])delete[](Children[i]);
	if(ClassTopic)delete[](ClassTopic);
	ClassTopic=NULL;
}
void CheckValidChild(BaseClass* Parent,BaseClass* C);
void BaseClass::SimplySetParent(BaseClass* Parent){
	if (Parent && !Parent->MayBeParent())return;
	ParentBC = Parent;
}
void BaseClass::SetParent(BaseClass* Parent){
	if (Parent && !Parent->MayBeParent())return;
	ParentBC=Parent;
	//SetParents();
}

const char* BaseClass::GetClassName() const{
	return "BaseClass";
}
BaseClass* BaseClass::GetRoot(){
	BaseClass* pp=this;
	BaseClass* p=pp->GetParent();
	if(!p)return NULL;
	while(pp){
		p=pp->GetParent();
		if(p==pp || !p)return pp;
		pp=p;
	}
	return NULL;
}
BaseClass::BaseClass(){	
	register_this();
	ParentBC=NULL;
	_ClassMask = 0xFFFFFFFF;
}
BaseClass::BaseClass(const BaseClass& B) {
	register_this();
	ParentBC = NULL;
	_ClassMask = 0xFFFFFFFF;
}
void BaseClass::ForEach(const std::function<bool(BaseClassElement* el)>& fn, bool OnlyPointsers) {
	BaseClassElement bc;
	int ze = 0;
	CountObjects(ze, nullptr, nullptr, &bc, &fn, OnlyPointsers);
}
void BaseClass::reset_class(void* DataPtr){
	if(CheckDirectCasting()){		
		_EACH(this, el) {
			if (el.BC && el.Ptr && el.Noreset == false) {
				el.BC->reset_class(el.Ptr);
			}
		} _EACH_END
		
	}
}
int GetExtraBCOpt(const char* id);
bool _reg_get(comms::cStr& reg,const char* substr) {
	size_t L = strlen(substr);
	bool has = false;
	do {
		int p = reg.IndexOf(substr);
		if (p != -1) {
			reg.Remove(p, (int)L);
			has = true;
		}
		else break;
	}while(true);
	return has;
}
inline bool BaseClass::GetElement(BaseClassElement& res, int idx, const void* Ptr, const void* Extra) {
	res.reset();
	CountObjects(idx, nullptr, nullptr, &res, nullptr);
	return res.BC && res.Ptr;
}

int BaseClass::GetClassSize() const { return sizeof(*this); }

BaseClass* BaseClass::new_element() const { return new BaseClass; }

BaseClass::~BaseClass(){	
	remove_this();
	if(CheckDirectCasting())reset_class(this);
};
void BaseClass::RegisterMembers(){
}
int BaseClass::GetAmountOfElements() {
	int num = 0;
	int ze = 100000000;
	CountObjects(ze, &num, nullptr, nullptr);
	return num;
}

void BaseClass::DeleteDefaultSubFields(TagsList& xml,void* ClassPtr, void* Extra) {
	if(CheckDirectCasting()&&!Extra){
		BaseClass* BC=static_cast<BaseClass*>(ClassPtr);
		int N=BC->GetAmountOfElements();
		if(!N)return;
		bool s=BaseClass::SaveInShortForm;
		BaseClass::SaveInShortForm=false;
		BaseClass* temp=new_element();
		TagsList XML;
		temp->Save(XML,temp,Extra);
		BaseClass::SaveInShortForm=s;
		for(int i=0;i<xml.GetSubTagsCount();i++){
			TagsList* sub=xml.GetSubTag(i);
			TagsList* SUB1=XML.GetSubTag( (char*)sub->GetTagName() );
			bool del=false;
			if(SUB1){
				if(!sub->GetSubTagsCount()){
					const char* S = SUB1->to_string();
					const char* s = sub->to_string();
					if ((s == NULL && S == NULL) || (s && S && !strcmp(s, S))) {
						del = true;
					}
				}
			}
			if(del){
				xml.RemoveSubTag(i);
				i--;
			}
		}
		delete(temp);
	}
}
void BaseClass::Save(TagsList& xml, void* ClassPtr, void* Extra) {
	if (CheckDirectCasting() && valid()) {
		BaseClass* BC = auto_cast(ClassPtr);
		if (BC) {
			UpdateClassMembersAndMask(false);
			_EACH(this, be) {
				if (be.Serialize && be.BC) {
					TagsList* xi = new TagsList(be.ID);
					be.BC->Save(*xi, be.Ptr, be.Extra);
					xml.AddSubTag(xi);
				}
			} _EACH_END
			if (SaveInShortForm) {
				DeleteDefaultSubFields(xml, BC, Extra);
			}
			const char* qn = xml.GetTagName();
			if (qn == NULL || qn[0] == 0)xml.SetTagName(GetClassName());
		}
	}
}
bool BaseClass::Load(TagsList& xml,void* ClassPtr, void* Extra){
	if (CheckDirectCasting()) {
		UpdateClassMembersAndMask(false);
		int N = xml.GetSubTagsCount();
		bool WasLink = false;
		BaseClass* BC = auto_cast(ClassPtr);
		if (BC) {
			for (int i = 0; i < N; i++) {
				BaseClassElement be;
				TagsList* sub = xml.GetSubTag(i);
				const auto idx = BC->ExpandWith(sub->GetTagName(), ClassPtr);
				auto res = false;
				if (idx != -1) {
					res = BC->GetElement(be, idx, ClassPtr, Extra);
				}
				else {
					res = BC->GetElementByName(sub->GetTagName(), ClassPtr, Extra, be, false, true);
				}
				if (res && be.Serialize) {
					be.BC->Load(*sub, be.Ptr, be.Extra);
					UpdateClassMembersAndMask(false);
				}
			}
		}
	}
	return true;
}
bool BaseClass::ReadFromFile(const char* Name){
	if(!CheckDirectCasting())return false;
	TagsList xml;
	if(xml.ReadTagsFromFile((char*)Name)){		
		CurrentSaveFile=Name;
		Load(xml,this,NULL);
		CurrentSaveFile=NULL;
		return true;
	}
	return false;
}
bool BaseClass::WriteToFile(const char* Name){
	if(!CheckDirectCasting())return false;
	CurrentSaveFile=Name;
	TagsList xml;
	SaveInShortForm=ShouldSaveInShortForm();
	Save(xml,this);
	SaveInShortForm=false;
	xml.WriteTagsToFile((char*)Name);
	CurrentSaveFile=NULL;
	return true;
}
bool BaseClass::FullCopy(const void* SrcData,const void* SrcDataExtra,BaseClass* Dest,void* DestData,void* DestExtraPtr,CECopyContext* C) {
	if(SrcData==DestData)return true;
	UpdateClassMembersAndMask(false);
	DWORD M = _ClassMask;
	_EACH(this, be) {
		if(be.BC && be.ID) {
			Dest = Dest->auto_cast(DestData);
			const auto idx = Dest->ExpandWith(be.ID, DestData);
			auto res = false;
			BaseClassElement be1;
			if (idx != -1) {
				res = Dest->GetElement(be1, idx, DestData, DestExtraPtr);
			}
			else {
				res = Dest->GetElementByName(be.ID, DestData, DestExtraPtr, be1, false, true);
			}
			if (res && be1.Serialize) {
				be.BC->FullCopy(be.Ptr, be.Extra, be1.BC, be1.Ptr, be1.Extra, C);
			}
		}
	}_EACH_END
	return true;
}
bool BaseClass::CopyBaseClass(BaseClass* Dest, bool Add) {
	if(!CheckDirectCasting())return false;
	if(strcmp(GetClassName(),Dest->GetClassName()))return false;
	if(!Add) Dest->reset_class(Dest);
	CECopyContext C;
	return FullCopy(this,nullptr,Dest,Dest, NULL,&C);	
}

bool BaseClass::GetElementByName(const char* ElmName, void* base, void* Extra, BaseClassElement& res, bool UI, bool Serialize) {
	res.reset();
	if (!ElmName)return false;
	BaseClass* BC = CheckDirectCasting() ? this : static_cast<BaseClass*>(base);
	if (BC) {
		_EACH(this, el) {
			if (el.ID && !strcmp(ElmName, el.ID)) {
				if ((UI && el.Visible) || (Serialize && el.Serialize)) {
					res = el;
					return true;
				}
			}
		} _EACH_END
	}
	return res.BC != nullptr;
}
bool BaseClass::GetElementByNameAndType(const char* ElmName, const char* Type, void* base, void* Extra,
	BaseClassElement& res, bool UI, bool Serialize) {
	res.reset();
	if (!ElmName)return false;
	BaseClass* BC = CheckDirectCasting() ? this : static_cast<BaseClass*>(base);
	if (BC) {
		_EACH(this, el) {
			if (el.ID && !strcmp(ElmName, el.ID) && el.BC && !strcmp(el.BC->GetClassName(),Type)) {
				if ((UI && el.Visible) || (Serialize && el.Serialize)) {
					res = el;
					return true;
				}
			}
		} _EACH_END
	}
	return res.BC != nullptr;
}
int BaseClass::GetAmountOfElementsInXML() {
	int Ne = 0;
	BaseClassElement bc;
	_EACH(this, el) {
		if (el.BC->CheckDirectCasting()) {
			Ne += el.BC->GetAmountOfElementsInXML();
		}
		else Ne++;
	} _EACH_END
	return Ne;
}

int BaseClass::GetAmountOfElementsInUI() {
	int Ne = 0;
	_EACH(this, el) {
		if (el.Visible) {
			if (el.BC->CheckDirectCasting()) {
				Ne += el.BC->GetAmountOfElementsInUI();
			}
			else Ne++;
		}
	} _EACH_END
	return Ne;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~/
//~~~~~~~~~~~_int~~~~~~~~~~~~/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~/
void _int::Save(TagsList& xml, void* ClassPtr, void* Extra) {
	int* V=(int*)ClassPtr;
	xml.Assign(*V);
}
bool _int::Load(TagsList& xml,void* ClassPtr, void* Extra){
	int* V=(int*)ClassPtr;
	const char* c=xml.to_string();
	*V=0;
	int z=0;
	if(c)z=sscanf_s(c,"%d",V);
	return true;
};
const char* _int::GetClassName() const{
	return "_int";
}
bool CtrlFSlider::ZeroHash = false;
bool CtrlISlider::ZeroHash = false;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~/
//~~~~~~~~~~~_float~~~~~~~~~~~~/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~/
void _float::Save(TagsList& xml, void* ClassPtr, void* Extra) {
	float* V=(float*)ClassPtr;
	char c[256];
	sprintf_s(c,"%f",*V);
	char* c1=strchr(c,',');
	if(c1)c1[0]='.';
	xml.Assign(c);
}
bool _float::Load(TagsList& xml,void* ClassPtr, void* Extra){
	float* V=(float*)ClassPtr;
	const char* c=xml.to_string();
	*V=0;
	int z=0;
	if(c){
		*V=ToFloat(c);
	}		
	return true;
};
const char* _float::GetClassName() const{
	return "_float";
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~/
//~~~~~~~~~~~_bool~~~~~~~~~~~~/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~/
void _bool::Save(TagsList& xml, void* ClassPtr, void* Extra) {
	bool* V=(bool*)ClassPtr;
	char c[16];
	if (*V) strcpy_s( c, 16, "true" ); else strcpy_s( c, 16, "false" );
	xml.Assign(c);
}

bool _bool::Load(TagsList& xml,void* ClassPtr, void* Extra)
{
	bool* V=(bool*)ClassPtr;
	const char* c=xml.to_string();
	*V=false;
	if(c){
		while (*c == ' ') c++;
		if (!_strnicmp( c, "true", 4 )) *V = true;
	}
	return true;
};
const char* _bool::GetClassName() const{
	return "_bool";
}
int num_OneClassMemberStorage=0;
void Enumerators::ClearAll(){
	Enums.Clear();
	EnumNames.clear();
}    
Enumerator* Enumerators::Get(const char* Name){
	int idx=EnumNames.find(Name);
	if(idx!=-1){
		return Enums[idx];
	}else{
		return Create(Name);
	}
}
Enumerator* Enumerators::Create(const char* Name){
	Enumerator* E=new Enumerator;		
	Enums.Add(E);
	EnumNames.add(Name);
	E->EnumeratorID=EnumNames.get(EnumNames.find(Name));
	if(E->GetAmount() == 0 && strchr(Name,'|'))
	{
		StringsList list;
		list.Split(Name, "|");
		for(int i=0;i<list.Count();i++)
		{
			E->Add(list[i]);
		}
	}
	return E;
}
OneClassStorage* ClassGarbage::GetClass(const char* ClassName){
	int idx=NamesHash.find(ClassName);
	if(idx!=-1)return Storage[idx];
	return CreateClassStorage(ClassName);
}
OneClassStorage* ClassGarbage::CreateClassStorage(const char* ClassName){
	OneClassStorage* ST;
	NamesHash.add(ClassName);
	ST=new OneClassStorage;
	Storage.Add(ST);
	return ST;
}

void  OneClassStorage::Clear(){
	
}
bool	OneClassStorage::CheckChildren(const char* ChildrenName){
	return CheckString(&Children,ChildrenName);
};
bool	OneClassStorage::CheckParent(const char* ParentName){
	return CheckString(&Parents,ParentName);
};
bool	OneClassStorage::CheckAll(const char* string, bool inParent, bool inChildren, bool FullCompatibility){
	bool ret = false;
	if ( inParent ){
		ret = CheckString(&Parents,string,FullCompatibility);
		if (ret) return true;
	};
	if ( inChildren ){
		ret = CheckString(&Children,string,FullCompatibility);
		if (ret) return true;
	};
	return false;
};
bool	OneClassStorage::CheckString(cList<char*>* pList, const char* string, bool FullCompatibility ){
	if ( pList==NULL  || pList->GetAmount()==0 )	return false;
	if ( string==NULL || string[0]==0 )				return false;
	for ( int i=0; i<pList->GetAmount(); i++ ){
		if (FullCompatibility) {
			if ( ( (*pList)[i]!=NULL && ((*pList)[i])[0]!=0 ) && strcmp((*pList)[i],string)==0 ) return true;
		}else{
			if ( ( (*pList)[i]!=NULL && ((*pList)[i])[0]!=0 ) && strstr((*pList)[i],string) ) return true;
		}
	};
	return false;
};
 void TestClassStorage(OneClassStorage** OCS);
 void reg_class_bc(BaseClass* BC,char* Topic,char* Typeid,bool AutoMode){	
	static comms::cStr D;
	D=Typeid;	
	ConvTypeName(D);
	if(AutoMode && strstr(D.ToCharPtr(),"."))return;
	OneClassStorage* OCS=CGARB.GetClass(D.ToCharPtr());
	TestClassStorage(&OCS);
	if(!OCS)OCS=CGARB.CreateClassStorage(D.ToCharPtr());	
	if(OCS->OneMemb){
		try{
            OCS->OneMemb->GetClassName();
		}catch(...){
            OCS->OneMemb=NULL;
		}
	}
	if(!OCS->OneMemb){
		BaseClass* elm=(BaseClass*)BC->new_element();
		if(!elm)return;
		OCS->OneMemb=elm;
	}
	if(Topic&&!OCS->ClassTopic){
		size_t L = strlen(Topic) + 1;
		OCS->ClassTopic=new char[L];
		strcpy_s(OCS->ClassTopic, L, Topic);
	}	
}

 ClassGarbage CGARB;
const char* BaseClass::CurrentSaveFile=NULL;
bool BaseClass::SaveInShortForm=false;
bool BaseClass::UI_definition = true;
bool BaseClass::Serialization = true;
std::mutex* BaseClass::pmutex;
uni_hash<_empty, cPtrDiff, (1 << 18), 2048>* BaseClass::presence;

#include "TagsList.hpp"

#ifdef __STDAPPLICATION__

char* GetTextByID(char* x){
	return x;
}
bool GetHintDebugMode(){
	return false;
}
#endif //__STDAPPLICATION__

#include "pool.hpp"

void BaseClass::register_this() {
	static bool one = true;
	if (one) {
		one = false;
		presence = new uni_hash<_empty, cPtrDiff, (1 << 18), 2048>;
		pmutex = new std::mutex;
	}
	std::scoped_lock l(*pmutex);
#ifdef _DEBUG
	assert(presence->get(_rotprt(this)) == nullptr);
#endif
	presence->add_quick(_rotprt(this), _empty());
	static int n = 0;
	if (n > 16384) {
		presence->refine_table();
		n = 0;
	}
	n++;
}
void BaseClass::remove_this() {
	std::scoped_lock l(*pmutex);
#ifdef _DEBUG
	assert(presence->get(_rotprt(this)) != nullptr);
#endif
	presence->del(_rotprt(this));
}

BaseClass* BaseClass::auto_cast(void* ptr) const
{
	if (valid() && ptr) {
		if (CheckDirectCasting()) {
			BaseClass* B1=(BaseClass*)ptr;
			if (B1->valid())return B1;
		}
		else return (BaseClass*)this;
	}
	return nullptr;
}

//_color
void _color::Save(TagsList& xml, void* ClassPtr, void* Extra) {
	DWORD* V=(DWORD*)ClassPtr;
	char c[16];
	sprintf_s(c, 16, "%08X", *V);
	xml.Assign(c);
}
bool _color::Load(TagsList& xml, void* ClassPtr, void* Extra) {
	DWORD* V = (DWORD*)ClassPtr;
	const char* c = xml.to_string();
	*V = 0;
	int z = 0;
	if (c)z = sscanf_s(c, "%X", V);
	return true;
}
void _color::UpdateHash(HashSummator& H, void* data,void* extra) {
	char* s = (char*)data;
	H << s[0] << s[1] << s[2] << s[3];
}
const char* _color::GetClassName() const{
	return "_color";
}
#define IMPLEMENT_SIMPLETYPE(x) \
	void _##x::Save(TagsList& xml, void* ClassPtr, void* Extra) {\
		x* w=(x*)ClassPtr;\
		xml.Assign(*w);\
	}\
	bool _##x::Load(TagsList& xml,void* ClassPtr,void* Extra){\
		x* w=(x*)ClassPtr;\
		int i;\
		int z=sscanf_s(xml.to_string(),"%d",&i);\
		if(z==1){\
			*w=(x)i;\
		}\
		return true; \
	}\
	const char* _##x::GetClassName() const{\
		return "_"#x;\
	}
IMPLEMENT_SIMPLETYPE(WORD);
IMPLEMENT_SIMPLETYPE(short);
IMPLEMENT_SIMPLETYPE(char);
IMPLEMENT_SIMPLETYPE(BYTE);
//end simple types
#ifdef USE_CIO
void _TextureID::Save(TagsList& xml, void* ClassPtr, void* Extra) {
	DWORD v=*((DWORD*)ClassPtr);
	if(v!=-1){
		xml.Assign((char*)IRS->GetTextureName(v));
	}
}
bool _TextureID::Load(TagsList& xml,void* ClassPtr, void* Extra){
	*((DWORD*)ClassPtr)=(DWORD)IRS->GetTextureID((char*)xml.to_string());
	return true;
}
#endif //USE_CIO

const char* _TextureID::GetClassName() const{
	return "_TextureID";
}
 BaseClass* _getClassFromPalette(const char* classname){
	comms::cStr D=(char*)classname;	
	ConvTypeName(D);	
	int idx=CGARB.NamesHash.find(D.ToCharPtr());
	if(idx!=-1){
		OneClassStorage*OCS=CGARB.Storage[idx];
		if(OCS)return OCS->OneMemb;
	}
	return NULL;
}

 void TestClassStorage(OneClassStorage** OCS){
}

void _cStr::Save(TagsList& xml, void* ClassPtr, void* Extra) {
	comms::cStr* ss = (comms::cStr*)ClassPtr;
	xml.Assign(ss->ToCharPtr());
}

bool _cStr::Load(TagsList& xml, void* ClassPtr, void* Extra) {
	comms::cStr* ss = (comms::cStr*)ClassPtr;
	*ss = xml.to_string();
	return true;
}

void _cStr::reset_class(void* ptr) {
	if (!strcmp(GetClassName(), "_cStr")) {
		comms::cStr* ss = (comms::cStr*)ptr;
		if (ss)ss->Clear();
	}
}

bool _cStr::FullCopy(const void* SrcData, const void* SrcDataExtra, BaseClass* Dest, void* DestData,
	void* DestExtraPtr, CECopyContext* C) {
	if(!strcmp(Dest->GetClassName(), "_cStr")) {
		comms::cStr* ss = (comms::cStr*)SrcData;
		comms::cStr* sd = (comms::cStr*)DestData;
		*sd = *ss;
	}
	return true;
}

void _cStr::SaveBin(void* Data, void* Extra, BinStream* Out, Enumerator* ExDictionary, Enumerator* SkipList) {
	comms::cStr& _string = *((comms::cStr*)Data);
	const char* s = _string.ToCharPtr();
	DWORD ID = ExDictionary ? ExDictionary->FindStr(s) : 0xFFFFFFFF;
	if (ID != 0xFFFFFFFF) {
		Out->WriteBYTE(255);
		Out->WriteWORD(*((WORD*)&ID));
	}
	else {
		size_t L = strlen(s);
		size_t L2 = L;
		if (L > 253) {
			Out->WriteBYTE(254);
			Out->WriteWORD((WORD)L);
		}
		else {
			Out->WriteBYTE((BYTE)L);
		}
		Out->Write(s, L);
	}
}
void _cStr::LoadBin(void* Data, void* Extra, BinStream* In, Enumerator* ExDictionary) {
	comms::cStr& _string = *((comms::cStr*)Data);
	int sz = In->ReadBYTE();
	if (sz == 0xFF) {
		WORD ID = In->ReadWORD();
		if (ID != 0xFFFF && ExDictionary) {
			_string = ExDictionary->GetStr(ID);
		}
		else _string = "";
	}
	else {
		if (sz == 0xFE)sz = In->ReadWORD();
		if (sz > 0) {
			char* p = new char[sz + 1];
			In->Read(p, sz);
			p[sz] = 0;
			_string = p;
			delete[](p);
		}
		else _string = "";
	}
}
void _int::SaveBin(void* Data,void* Extra,BinStream* Out,Enumerator* ExDictionary,Enumerator* SkipList){
	Out->Write(Data,4);
}
void _int::LoadBin(void* Data,void* Extra,BinStream* In,Enumerator* ExDictionary){
    In->Read(Data,4);
}
void _float::SaveBin(void* Data,void* Extra,BinStream* Out,Enumerator* ExDictionary,Enumerator* SkipList){
	Out->Write(Data,4);
}
void _float::LoadBin(void* Data,void* Extra,BinStream* In,Enumerator* ExDictionary){
	In->Read(Data,4);
}
void _bool::SaveBin(void* Data,void* Extra,BinStream* Out,Enumerator* ExDictionary,Enumerator* SkipList){
	Out->Write(Data,1);
}
void _bool::LoadBin(void* Data,void* Extra,BinStream* In,Enumerator* ExDictionary){
	In->Read(Data,1);
}
void _index::SaveBin(void* Data,void* Extra,BinStream* Out,Enumerator* ExDictionary,Enumerator* SkipList){
	Out->Write(Data,4);
}
void _index::LoadBin(void* Data,void* Extra,BinStream* In,Enumerator* ExDictionary){
	In->Read(Data,4);
}
void _color::SaveBin(void* Data,void* Extra,BinStream* Out,Enumerator* ExDictionary,Enumerator* SkipList){
	Out->Write(Data,4);
}
void _color::LoadBin(void* Data,void* Extra,BinStream* In,Enumerator* ExDictionary){
	In->Read(Data,4);
}
void _WORD::SaveBin(void* Data,void* Extra,BinStream* Out,Enumerator* ExDictionary,Enumerator* SkipList){
	Out->Write(Data,2);
}
void _WORD::LoadBin(void* Data,void* Extra,BinStream* In,Enumerator* ExDictionary){
	In->Read(Data,2);
}
void _short::SaveBin(void* Data,void* Extra,BinStream* Out,Enumerator* ExDictionary,Enumerator* SkipList){
	Out->Write(Data,2);
}
void _short::LoadBin(void* Data,void* Extra,BinStream* In,Enumerator* ExDictionary){
	In->Read(Data,2);
}
void _char::SaveBin(void* Data,void* Extra,BinStream* Out,Enumerator* ExDictionary,Enumerator* SkipList){
	Out->Write(Data,1);
}
void _char::LoadBin(void* Data,void* Extra,BinStream* In,Enumerator* ExDictionary){
	In->Read(Data,1);
}
void _BYTE::SaveBin(void* Data,void* Extra,BinStream* Out,Enumerator* ExDictionary,Enumerator* SkipList){
	Out->Write(Data,4);
}
void _BYTE::LoadBin(void* Data,void* Extra,BinStream* In,Enumerator* ExDictionary){
	In->Read(Data,4);
}
void BaseClass::SaveBin(void* Data,void* Extra,BinStream* Out,Enumerator* ExDictionary,Enumerator* SkipList){
	if(CheckDirectCasting()){
		MemoryBinStream temp;
		BaseClass* BC=static_cast<BaseClass*>(Data);
		BC->RegisterMembers();
		BC->_ClassMask = BC->GetClassMask();
		int i = 0;
		_EACH(this, be) {
			if (be.Serialize) {
				size_t L = be.ID ? strlen(be.ID) : 0;
				if (L) {
					if (L > 254)L = 254;
					Out->WriteBYTE((BYTE)L);
					if (L > 0)Out->Write(be.ID, L);
					const char* cn = be.BC->GetClassName();
					L = cn ? strlen(cn) : 0;
					if (L > 254)L = 254;
					Out->WriteBYTE((BYTE)L);
					if (L > 0)Out->Write(cn, L);
					temp.Clear();
					be.BC->SaveBin(be.Ptr, be.Extra, &temp, ExDictionary, SkipList);
					Out->WritePackedSize((int)temp.Size());
					Out->Write(temp.GetData(), temp.Size());
				}
				
			}
			i++;
		} _EACH_END
		Out->WriteBYTE(255);
	} 
}
void BaseClass::LoadBin(void* Data,void* Extra,BinStream* In,Enumerator* ExDictionary){
	if(CheckDirectCasting()){
		BaseClass* BC = static_cast<BaseClass*>(Data);
		BC->RegisterMembers();
		BC->reset_class(Data);
		char ID[257];
		char cn[257];
		for(int i=0;i<65534;i++){
			int L=In->ReadBYTE();
			if (L == 255)break;
			In->Read(ID, L);
			ID[L] = 0;
			L = In->ReadBYTE();
			In->Read(cn, L);
			cn[L] = 0;
			int sz = In->ReadPackedSize();
			BaseClassElement be;
			BC->GetElementByNameAndType(ID, cn, Data, Extra, be, false, true);
			size_t p0 = In->GetReadPos();
			if (be.BC && be.Ptr) {
				be.BC->LoadBin(be.Ptr, be.Extra, In, ExDictionary);
				assert(In->GetReadPos() == p0 + sz);
				In->SetReadPos(p0 + sz);
			}else {
				assert(0);
				In->Skip(sz);
			}
			if (In->GetReadPos() >= In->Size()) {
				break;
			}
		}		
	}
}
void BaseClass::UpdateHash(HashSummator& H, void* data, void* extra) {
	if(CheckDirectCasting()){
		int ze = 0;
		CountObjects(ze, nullptr, &H, nullptr);
		H += GetClassMask();
	}
}
void BaseClass::SetParents() {
	if (CheckDirectCasting()) {
		_EACH(this, el) {
			if (el.BC && el.BC->CheckDirectCasting()) {
				el.BC->SetParent(this);
			}
		} _EACH_END
	}
}
bool _float::DontUseInHash = false;
void _float::UpdateHash(HashSummator& H, void* data, void* extra) {
	H += *((float*)data);
}
void _int::UpdateHash(HashSummator& H, void* data, void* extra) {
	H += *((int*)data);
}
void _cStr::UpdateHash(HashSummator& H, void* data, void* extra) {
	const comms::cStr* s = (const comms::cStr*)data;
	int L = s->Length();
	if (L) {
		H += s->ToCharPtr();
	}
}

comms::cStr* StringsList::elem(int idx) {
	return cList<comms::cStr*>::operator[](idx);
}

const comms::cStr* StringsList::elem(int idx) const {
	return cList<comms::cStr*>::operator[](idx);
}
StringsList::StringsList() {
}

StringsList::~StringsList() {
	Free();
}

StringsList::StringsList(const StringsList& r) {
	Free();
	for(int i=0;i<r.Count();i++){
		Add(r[i].ToCharPtr());
	}
}

void StringsList::operator=(const StringsList& r) {
	Free();
	for (int i = 0; i < r.Count(); i++) {
		Add(r[i].ToCharPtr());
	}
}

int StringsList::Count() const {
	return cList<comms::cStr*>::Count();
}

int StringsList::GetAmount() const {
	return Count();
}

const comms::cStr& StringsList::operator[](int pos) const {
	return *elem(pos);
}

comms::cStr& StringsList::operator[](int pos) {
	return *elem(pos);
}

void StringsList::Clear() {
	for (int i = 0; i < Count(); i++) {
		delete(elem(i));
		cList<comms::cStr*>::SetAt(i, nullptr);
	}
	cList<comms::cStr*>::Clear();
}

void StringsList::Free() {
	for (int i = 0; i < Count(); i++) {
		delete(elem(i));
		cList<comms::cStr*>::SetAt(i, nullptr);
	}
	cList<comms::cStr*>::Free();
}

void StringsList::Save(TagsList& xml, void* ClassPtr, void* Extra) {
	for(int i=0;i<Count();i++) {
		TagsList* x = new TagsList("_str");
		x->Assign((*this)[i].ToCharPtr());
		xml.AddSubTag(x);
	}
}

bool StringsList::Load(TagsList& xml, void* ClassPtr, void* Extra) {
	Free();
	for(int i=0;i<xml.GetSubTagsCount();i++) {
		comms::cStr s = xml.GetSubTag(i)->to_string();
		Add(s);
	}
	return true;
}

void StringsList::reset_class(void* ptr) {
	Free();
}

bool StringsList::FullCopy(const void* SrcData, const void* SrcDataExtra, BaseClass* Dest, void* DestData,
	void* DestExtraPtr, CECopyContext* C) {
	BaseClass* sl = Dest->auto_cast(DestData);
	if(sl) {
		StringsList* list2 = dynamic_cast<StringsList*>(sl);
		if (list2) {
			list2->Clear();
			for(int i=0;i<Count();i++) {
				list2->Add((*this)[i].ToCharPtr());
			}
		}
	}
	return true;
}

void StringsList::SaveBin(void* Data, void* Extra, BinStream* Out, Enumerator* ExDictionary, Enumerator* SkipList) {
	Out->WriteDWORD(Count());
	comms::cStr s = "_str";
	_cStr sc;
	for (int i = 0; i < Count(); i++) {
		sc.SaveBin(&s, NULL, Out, ExDictionary, SkipList);
		sc.SaveBin(&((*this)[i]), nullptr, Out, ExDictionary, SkipList);
	}
}
void StringsList::LoadBin(void* Data, void* Extra, BinStream* In, Enumerator* ExDictionary) {
	Free();
	int N = In->ReadDWORD();
	comms::cStr s;
	_cStr sc;
	for (int i = 0; i < N; i++) {
		sc.LoadBin(&s, nullptr, In, ExDictionary);
		s.Clear();
		sc.LoadBin(&s,nullptr, In, ExDictionary);
		Add(s);
	}
}

void StringsList::UpdateHash(HashSummator& H, void* data, void* extra) {
	_cStr se;
	for(int i=0;i<Count();i++) {
		se.UpdateHash(H, &((*this)[i]), nullptr);
	}
}

inline void StringsList::CountObjects(int& required_index, int* counter, HashSummator* hash, BaseClassElement* result,
                                      const std::function<bool(BaseClassElement*)>* ForEachElem, bool OnlyPointers) {
	if (counter)*counter += Count();
	if (hash) { UpdateHash(*hash, nullptr, nullptr); }
	static _cStr ns;
	if (ForEachElem) {
		for (int i = 0; i < GetAmount(); i++) {
			result->BC = &ns;
			if(!OnlyPointers)result->ID = "_str";
			result->Ptr = &GetAt(i);
			if ((*ForEachElem)(result))return;
		}
	}
	else if (result && required_index >= 0 && required_index < GetAmount()) {
		result->BC = &ns;
		if (!OnlyPointers)result->ID = "_str";
		result->Ptr = &GetAt(required_index);
	}
}

void StringsList::FromList(const cList<comms::cStr>& list) {
	for(int i=0;i<list.Count();i++) {
		Add(list[i]);
	}
}

bool StringsList::DelElement(int Index) {
	RemoveAt(Index);
	return true;
}

int StringsList::Add(const char* str) {
	comms::cStr* s = new comms::cStr(str);
	return cList<comms::cStr*>::Add(s);
}
//int StringsList::Add(comms::cStr* str) {
//	return Add(*str);
//}

int StringsList::IndexOf(const char* str) const {
	for(int i=0;i<Count();i++) {
		if (elem(i)->Equals(str))return i;
	}
	return -1;
}

void StringsList::Split(const char* WhatToSplit, const char* delimiters) {
	cList<comms::cStr> items;
	comms::cStr::Split(WhatToSplit, &items, delimiters);
	FromList(items);
}

comms::cStr& StringsList::GetLast() {
	if (Count()) {
		return *elem(Count() - 1);
	}
	static comms::cStr s;
	return s;
}
const char* StringsList::GetLast() const {
	if (Count()) {
		return elem(Count() - 1)->ToCharPtr();
	}
	return "";
}

comms::cStr& StringsList::GetAt(int idx) {
	return *elem(idx);
}
const comms::cStr& StringsList::GetAt(int idx) const {
	return *elem(idx);
}

void StringsList::Insert(int pos, const char* str) {
	comms::cStr* s = new comms::cStr(str);
	cList<comms::cStr*>::Insert(pos, s, 1);
}

bool StringsList::IsEmpty() const {
	return Count() == 0;
}

const char* StringsList::GetFirst() const {
	if(Count()) {
		return elem(0)->ToCharPtr();
	}
	return "";
}
comms::cStr& StringsList::GetFirst() {
	if (Count()) {
		return *elem(0);
	}
	static comms::cStr s;
	return s;
}

void StringsList::RemoveLast() {
	if(Count())RemoveAt(Count() - 1, 1);
}

int StringsList::AddOnce(const char* str) {
	if(IndexOf(str) == -1) {
		return Add(str);
	}
	return -1;
}

void StringsList::Sort(cList<comms::cStr>::Compare* C) {
	StringsList::Sort(0, Count(), C);
}

void StringsList::Sort(const cList<comms::cStr>::CompareFunctor& F) {
	StringsList::Sort(0, Count(), F);
}

void StringsList::Sort(const int Index, const int Count, cList<comms::cStr>::Compare* C) {
	int i = 0, j = 0, M = 0;
	bool f = false;

	M = Count / 2;
	while (M >= 1) {
		for (i = M; i < Count; i++) {
			comms::cStr* K = elem(i + Index);
			j = i - M;
			f = false;
			while (j >= 0 && !f) {
				if (C(K, elem(j + Index)) < 0) {
					cList<comms::cStr*>::SetAt(j + M + Index, elem(j + Index));
					j -= M;
				}
				else {
					f = true;
				}
			}
			cList<comms::cStr*>::SetAt(j + M + Index, K);
		}
		M /= 2;
	}
}

void StringsList::Sort(int Index, int Count, const cList<comms::cStr>::CompareFunctor& C) {
	
	int i = 0, j = 0, M = 0;
	bool f = false;

	M = Count / 2;
	while (M >= 1) {
		for (i = M; i < Count; i++) {
			comms::cStr* K = elem(i + Index);
			j = i - M;
			f = false;
			while (j >= 0 && !f) {
				if (C(*K, *elem(j + Index))) {
					f = true;
				}
				else {
					SetAt(j + M + Index, cList<comms::cStr*>::GetAt(j + Index));
					j -= M;
				}
			}
			cList<comms::cStr*>::SetAt(j + M + Index, K);
		}
		M /= 2;
	}
}

cList<comms::cStr> StringsList::ToList() const {
	cList<comms::cStr> L;
	for (int i = 0; i < Count(); i++) {
		L.Add(*elem(i));
	}
	return L;
}

void StringsList::RemoveAt(int pos, int num) {
	if(elem(pos)) {
		for (int i = 0; i < num; i++) {
			delete(elem(pos + i));
		}
	}
	cList<comms::cStr*>::RemoveAt(pos, num);
}

void _bool::UpdateHash(HashSummator& H, void* data, void* extra) {
	H += *((bool*)data);
}
void _index::UpdateHash(HashSummator& H, void* data, void* extra) {
	H += *((int*)data);
}
void BaseClass::ToBS(BinStream& bs,void* data,void* extra,bool IncludeLength){
	UpdateClassMembersAndMask(true);
	TagsList xml;	
	Save(xml, data, extra);
	comms::cStr s1;
	xml.PutTagsIntoString(&s1);
	if(IncludeLength)bs.WriteDWORD(s1.Length());
	bs.Write(s1.ToCharPtr(),s1.Length());
}
void BaseClass::FromBS(BinStream& bs, void* data, void* extra){
	UpdateClassMembersAndMask(true);
	int L=bs.ReadDWORD();
	char* s=new char[L+1];
	bs.Read(s,L);
	s[L]=0;
	TagsList xml;
	xml.GetTagsFromString(s);
	
	Load(xml,data, extra);
	UpdateClassMembersAndMask(true);
	delete[]s;
}
void BaseClass::ToBS(BinStream& bs, bool IncludeLength) {
	ToBS(bs, this, nullptr, IncludeLength);
}
void BaseClass::FromBS(BinStream& bs) {
	FromBS(bs, this, nullptr);
}
void BaseClass::ToStr(comms::cStr& bs){
	UpdateClassMembersAndMask(true);
	TagsList xml;	
	Save(xml,this);
	bs.Clear();
	xml.PutTagsIntoString(&bs);
}
void BaseClass::FromStr(const comms::cStr& bs){
	TagsList xml;
	xml.GetTagsFromString(bs.ToCharPtr());
	
	Load(xml,this);
}
Delimiter GDLM;

void StrToFile(const comms::cStr& src, const char* FileName) {
	ResFile F = RRewrite(FileName);
	if (F != INVALID_HANDLE_VALUE) {
		RBlockWrite(F, src.ToCharPtr(), src.Length());
		RClose(F);
	}

}
bool StrFromFile(comms::cStr& dest, const char* FileName) {
	ResFile F = RReset(FileName);
	if (F != INVALID_HANDLE_VALUE) {
		size_t sz = RFileSize(F);
		char* s = new char[sz + 1];
		RBlockRead(F, s, sz);
		s[sz] = 0;
		dest = s;
		delete[](s);
		return true;
	}
	return false;
}
const UnlimitedBitset UnlimitedBitset::ZERO;
const char* _modify_class_name(const char* s) {
#ifdef COMMS_WINDOWS
	s = strchr(s, ' ') + 1;
	do {
		const char* s1 = strstr(s, "::");
		if (s1)s = s1 + 2;
		else break;
	} while (true);
#endif
#ifdef COMMS_MACOS
	if (s[0] == 'N') {
		s++;
		int L = atoi(s);
		while (s[0] >= '0' && s[0] <= '9')s++;
		s += L;
		L = atoi(s);
		while (s[0] >= '0' && s[0] <= '9')s++;
		return TagsList::GetConstantSubstringLocation(s, L);
	}
	else {
		while (s[0] >= '0' && s[0] <= '9')s++;
	}
#endif //COMMS_MACOS
	return s;
}
float ToFloat(const char* str) {
	double number;
	int exponent;
	int negative;
	char* p = (char*)str;
	double p10;
	int n;
	int num_digits;
	int num_decimals;

	// Skip leading whitespace
	while (isspace(*p)) p++;

	// Handle optional sign
	negative = 0;
	switch (*p)
	{
	case '-': negative = 1; // Fall through to increment position
	case '+': p++;
	}

	number = 0.;
	exponent = 0;
	num_digits = 0;
	num_decimals = 0;

	// Process string of digits
	while (isdigit(*p))
	{
		number = number * 10.0 + (*p - '0');
		p++;
		num_digits++;
	}

	// Process decimal part
	if (*p == '.' || *p == ',')
	{
		p++;

		while (isdigit(*p))
		{
			number = number * 10.0 + (*p - '0');
			p++;
			num_digits++;
			num_decimals++;
		}

		exponent -= num_decimals;
	}

	if (num_digits == 0)
	{
		errno = ERANGE;
		return 0.0;
	}

	// Correct for sign
	if (negative) number = -number;

	// Process an exponent string
	if (*p == 'e' || *p == 'E')
	{
		// Handle optional sign
		negative = 0;
		switch (*++p)
		{
		case '-': negative = 1;   // Fall through to increment pos
		case '+': p++;
		}

		// Process string of digits
		n = 0;
		while (isdigit(*p))
		{
			n = n * 10 + (*p - '0');
			p++;
		}

		if (negative)
			exponent -= n;
		else
			exponent += n;
	}

	if (exponent < FLT_MIN_EXP || exponent > FLT_MAX_EXP)
	{
		errno = ERANGE;
		return HUGE_VAL;
	}

	// Scale the result
	p10 = 10.;
	n = exponent;
	if (n < 0) n = -n;
	while (n)
	{
		if (n & 1)
		{
			if (exponent < 0)
				number /= p10;
			else
				number *= p10;
		}
		n >>= 1;
		p10 *= p10;
	}

	if (number == HUGE_VAL) errno = ERANGE;

	return (float)number;
}
#endif //IMPLEMENT_CLASS_FACTORY
