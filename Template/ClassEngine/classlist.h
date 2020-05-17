///classes implementation
class Delimiter: public BaseClass{	
public:
	virtual bool ForceProperty(){
		return true;
	}
	const char* GetClassName() const override{
		return "Delimiter";
	}
	virtual bool FullCopy(const void* SrcData, const void* SrcDataExtra, BaseClass* Dest, void* DestData, void* DestExtraPtr, CECopyContext* C) override{
		return true;
	}
	virtual void SaveBin(void* Data, void* Extra, BinStream* Out, Enumerator* ExDictionary, Enumerator* SkipList) override{}
	virtual	void LoadBin(void* Data, void* Extra, BinStream* In, Enumerator* ExDictionary) override{}
	AUTONEW(Delimiter);
};
extern Delimiter GDLM;
class  _cStr : public BaseClass {
public:
	_cStr() {};
	~_cStr() {
	}

	virtual void Save(TagsList& xml, void* ClassPtr, void* Extra = NULL) override;
	virtual bool Load(TagsList& xml,void* ClassPtr,void* Extra = NULL) override;
	virtual const char* GetClassName() const override {
		return "_cStr";
	}
	virtual void  reset_class(void* ptr);
	virtual bool FullCopy(const void* SrcData, const void* SrcDataExtra, BaseClass* Dest, void* DestData, void* DestExtraPtr, CECopyContext* C) override;
	virtual void SaveBin(void* Data, void* Extra, BinStream* Out, Enumerator* ExDictionary, Enumerator* SkipList) override;
	virtual	void LoadBin(void* Data, void* Extra, BinStream* In, Enumerator* ExDictionary) override;
	virtual	void UpdateHash(HashSummator& H, void* data = nullptr, void* extra = nullptr) override;

	AUTONEW(_cStr);
};//_cStr
reg_auto_specialisation_template(_cStr, comms::cStr);

/**
 * \brief StringsList is the main container used as array of strings
 */
class StringsList: public BaseClass, comms::cList<comms::cStr*> {
	comms::cStr*		elem(int idx);
	const comms::cStr*	elem(int idx) const;
public:
						StringsList();
						~StringsList();
						StringsList(const StringsList& r);
	void				operator = (const StringsList& Src);
	
	int					Count() const ;
	int					GetAmount() const;
	const comms::cStr&	operator[](int pos) const ;
	comms::cStr&		operator[](int pos);
	void				Clear();
	void				Free();
	int					Add(const char* str);
	//int				Add(comms::cStr* str);
	void				RemoveAt(int pos, int num = 1);
	int					IndexOf(const char* str) const;
	void				Split(const char* WhatToSplit, const char* delimiters = " ,;\t");
	const char*			GetLast() const;
	comms::cStr&		GetLast();
	comms::cStr&		GetAt(int idx);
	const comms::cStr&	GetAt(int idx) const;
	void				Insert(int pos, const char* str);
	bool				IsEmpty() const ;
	const char*			GetFirst() const;
	comms::cStr&		GetFirst();
	void				RemoveLast();
	int					AddOnce(const char* str);
	void				Sort(cList<comms::cStr>::Compare* C);
	void				Sort(const cList<comms::cStr>::CompareFunctor& F);
	void				Sort(const int Index, const int Count, cList<comms::cStr>::Compare* C);
	void				Sort(int Index, int Count, const cList<comms::cStr>::CompareFunctor& F);
	
	comms::cList<comms::cStr>  ToList() const ;
	void				FromList(const cList<comms::cStr>& list);
	
	virtual bool		DelElement(int Index) override;
	
	virtual void Save(TagsList& xml, void* ClassPtr, void* Extra = NULL) override;
	virtual bool Load(TagsList& xml, void* ClassPtr, void* Extra = NULL) override;
	virtual const char* GetClassName() const override {
		return "ClassArray._str";
	}
	virtual void  reset_class(void* ptr);
	virtual bool FullCopy(const void* SrcData, const void* SrcDataExtra, BaseClass* Dest, void* DestData, void* DestExtraPtr, CECopyContext* C) override;
	virtual void SaveBin(void* Data, void* Extra, BinStream* Out, Enumerator* ExDictionary, Enumerator* SkipList) override;
	virtual	void LoadBin(void* Data, void* Extra, BinStream* In, Enumerator* ExDictionary) override;
	virtual	void UpdateHash(HashSummator& H, void* data = nullptr, void* extra = nullptr) override;
	virtual bool CheckDirectCasting() const override {
		return true;
	}

	virtual void CountObjects(int& required_index, int* counter, HashSummator* hash, BaseClassElement* result,
	                          const std::function<bool(BaseClassElement*)>* ForEachElem, bool OnlyPointersMode) override;

	AUTONEW(StringsList);
};
class  _int :public BaseClass {
public:
	virtual void Save(TagsList& xml, void* ClassPtr, void* Extra = NULL) override;
	virtual bool Load(TagsList& xml,void* ClassPtr,void* Extra = NULL) override;
	virtual const char* GetClassName() const override;
	virtual void reset_class(void* ptr) {
		*((int*)ptr) = 0;
	}
	virtual bool CheckCompartabilityWith(const char* TypeName, int TypeSize) {
		return TypeSize == 4;
	}
	virtual bool FullCopy(const void* SrcData, const void* SrcDataExtra, BaseClass* Dest, void* DestData, void* DestExtraPtr, CECopyContext* C) override {
		*((int*)DestData) = *((int*)SrcData);
		return true;
	}
	virtual void SaveBin(void* Data, void* Extra, BinStream* Out, Enumerator* ExDictionary, Enumerator* SkipList) override;
	virtual	void LoadBin(void* Data, void* Extra, BinStream* In, Enumerator* ExDictionary) override;
	virtual	void UpdateHash(HashSummator& H, void* data = nullptr, void* extra = nullptr) override;
	AUTONEW(_int);
};
reg_auto_specialisation_template(_int, int);

class  _float :public BaseClass {
public:
	static bool DontUseInHash;
	virtual void Save(TagsList& xml, void* ClassPtr, void* Extra = NULL) override;
	virtual bool Load(TagsList& xml,void* ClassPtr,void* Extra = NULL) override;
	virtual const char* GetClassName() const override;
	virtual void reset_class(void* ptr) {
		*((float*)ptr) = 0.0f;
	}
	virtual bool CheckCompartabilityWith(const char* TypeName, int TypeSize) {
		return !strcmp(TypeName, "float");
	}
	virtual bool FullCopy(const void* SrcData, const void* SrcDataExtra, BaseClass* Dest, void* DestData, void* DestExtraPtr, CECopyContext* C) override {
		*((int*)DestData) = *((int*)SrcData);
		return true;
	}
	virtual void SaveBin(void* Data, void* Extra, BinStream* Out, Enumerator* ExDictionary, Enumerator* SkipList) override;
	virtual	void LoadBin(void* Data, void* Extra, BinStream* In, Enumerator* ExDictionary) override;
	virtual	void UpdateHash(HashSummator& H, void* data = nullptr, void* extra = nullptr) override;
	AUTONEW(_float);
}; // class _float
reg_auto_specialisation_template(_float, float);
//-----------------------------------------------------------------------------
// CtrlISlider
//-----------------------------------------------------------------------------
class CtrlISlider : public _int {
public:
	static bool ZeroHash;
	virtual	void UpdateHash(HashSummator& H, void* data = nullptr, void* extra = nullptr) override {
		if(!ZeroHash)_int::UpdateHash(H, data, extra);
	}
	virtual const char* GetClassName() const override { return "CtrlISlider"; }
	AUTONEW(CtrlISlider);
	virtual BaseWidget* OnCreateControlFromScratch(const ClassEditorContext& Context, Rct& Rect);
};

struct CtrlISliderArgs {
	int MinValue;
	int MaxValue;
	int DefValue;
};

//-----------------------------------------------------------------------------
// CtrlFSlider
//-----------------------------------------------------------------------------
class CtrlFSlider : public _float {
public:
	static bool ZeroHash;
	virtual	void UpdateHash(HashSummator& H, void* data = nullptr, void* extra = nullptr) override {
		if(!ZeroHash)_float::UpdateHash(H, data, extra);
	}
	virtual const char* GetClassName() const override { return "CtrlFSlider"; }
	AUTONEW(CtrlFSlider);
	virtual BaseWidget* OnCreateControlFromScratch(const ClassEditorContext& Context, Rct& Rect);

};

struct CtrlFSliderArgs {
	CtrlFSliderArgs() {
		MinValue = 0;
		MaxValue = 1;
		DefValue = 1;
		VisModulator = 1;
		Inv = false;
		SwapEnds = false;
	}
	float MinValue;
	float MaxValue;
	float DefValue;
	float VisModulator;
	bool  Inv;
	bool SwapEnds;
};
template <class tp>
std::tuple<BaseClass*,void*> GetSliderContainer(tp minvalue, tp maxvalue)
{
	//comms::cMessageBox::Ok("SLIDER registration error!", "SLIDER may not be bound to the type \"%s\"", typeid(tp).name());
	return std::tuple<BaseClass*, void*>(nullptr, nullptr);
}
template <>
inline std::tuple<BaseClass*, void*> GetSliderContainer(float minvalue, float maxvalue)
{
	CtrlFSliderArgs* arg = new CtrlFSliderArgs;
	arg->MinValue = minvalue;
	arg->MaxValue = maxvalue;
	return std::tuple<BaseClass*, void*>( CGARB.GetClass("CtrlFSlider")->OneMemb, (void*)arg);
}
template <>
inline std::tuple<BaseClass*, void*> GetSliderContainer(int minvalue, int maxvalue)
{
	CtrlISliderArgs* arg = new CtrlISliderArgs;
	arg->MinValue = minvalue;
	arg->MaxValue = maxvalue;
	return std::tuple<BaseClass*, void*>(CGARB.GetClass("CtrlISlider")->OneMemb, (void*)arg);
}
class  _bool :public BaseClass {
public:
	virtual void Save(TagsList& xml, void* ClassPtr, void* Extra = NULL) override;
	virtual bool Load(TagsList& xml,void* ClassPtr,void* Extra = NULL) override;
	virtual const char* GetClassName() const override;
	virtual void reset_class(void* ptr) {
		*((bool*)ptr) = false;
	}
	virtual bool CheckCompartabilityWith(const char* TypeName, int TypeSize) {
		return TypeSize == 1;
	}
	virtual bool FullCopy(const void* SrcData, const void* SrcDataExtra, BaseClass* Dest, void* DestData, void* DestExtraPtr, CECopyContext* C) override {
		*((BYTE*)DestData) = *((BYTE*)SrcData);
		return true;
	}
	virtual void SaveBin(void* Data, void* Extra, BinStream* Out, Enumerator* ExDictionary, Enumerator* SkipList) override;
	virtual	void LoadBin(void* Data, void* Extra, BinStream* In, Enumerator* ExDictionary) override;
	virtual	void UpdateHash(HashSummator& H, void* data = nullptr, void* extra = nullptr) override;
	BaseWidget* OnCreateControlFromScratch(const ClassEditorContext& Context, Rct& Rect);
	AUTONEW(_bool);
}; // class _bool
reg_auto_specialisation_template(_bool, bool);

class  _index :public BaseClass {
public:
	virtual bool CheckCompartabilityWith(const char* TypeName, int TypeSize) {
		return TypeSize == 4;
	}
	virtual void Save(TagsList& xml, void* ClassPtr, void* Extra = NULL) override {
		if (Extra) {
			Enumerator* E = (Enumerator*)Extra;
			xml.Assign(E->Get(*((int*)ClassPtr)));
		}
	}
	virtual bool Load(TagsList& xml,void* ClassPtr,void* Extra = NULL) override {
		if (Extra) {
			Enumerator* E = (Enumerator*)Extra;
			const char* s = xml.to_string();
			if (s) {
				int p = E->Get((char*)xml.to_string());
				if (p != -1) {
					*((int*)ClassPtr) = E->Get((char*)xml.to_string());
				}
				else {
					*((int*)ClassPtr) = E->GetVal(0);
					//Error->xml_print(xml,"identifier \"%s\" not found in list \"%s\" for variable \"%s\"\n",xml.Get_string(),E->EnumeratorID,xml.GetQuoteName());
				}
			}
			else {
				*((int*)ClassPtr) = E->GetVal(0);
				//Error->xml_print(xml,"xml node is empty for variable %s\n",xml.GetQuoteName());
			}
			return true;
		}
		return false;
	}
	virtual const char* GetClassName() const override {
		return "_index";
	}
	virtual void reset_class(void* ptr) {
		*((int*)ptr) = 0;
	}
	virtual bool FullCopy(const void* SrcData, const void* SrcDataExtra, BaseClass* Dest, void* DestData, void* DestExtraPtr, CECopyContext* C) override {
		*((int*)DestData) = *((int*)SrcData);
		return true;
	}
	virtual void SaveBin(void* Data, void* Extra, BinStream* Out, Enumerator* ExDictionary, Enumerator* SkipList) override;
	virtual	void LoadBin(void* Data, void* Extra, BinStream* In, Enumerator* ExDictionary) override;
	virtual	void UpdateHash(HashSummator& H, void* data = nullptr, void* extra = nullptr) override;
	AUTONEW(_index);
};
template<class X>class ClassArray :public BaseClass, public comms::cList<X*> {
public:
	ClassArray() {
		
	}
	ClassArray(const ClassArray<X>& src);
	void operator = (const ClassArray<X>& src);
	virtual ~ClassArray() {
		reset_class(this);
	};
	virtual void reset_class(void* ptr) {
		ClassArray<X>* CA = (ClassArray<X>*)ptr;
		for (int i = 0; i < CA->Count(); i++)if ((*CA)[i]) {
			//try{
			delete((*CA)[i]);
			//}catch(...){
			//}
			CA->ToPtr()[i] = NULL;
		}
		CA->Free();
	}
	void Clear() {
		reset_class(this);
	}
	const char* GetClassName() const override {
		static char N[64] = "";
		if (N[0] != 'C') {
			X* x = new X;
			sprintf(N, "ClassArray.%s", x->GetClassName());
			delete(x);
		}
		return N;
	}
	int GetAmountOfElements() override {
        return comms::cList<X*>::Count();
	}
	virtual void CountObjects(int& required_index, int* counter, HashSummator* hash, BaseClassElement* result, const std::function<bool(BaseClassElement*)>* ForEachElem, bool OnlyPointersMode) override {
        if (counter)* counter += GetAmountOfElements();
		if(hash) {
			bool pa = MayBeParent();
			for(int i=0;i<GetAmountOfElements();i++) {
				BaseClass* B = (*this)[i];
				if (B) {
					B->UpdateHash(*hash, nullptr, nullptr);
					if(pa &&  B->UsePointerInHashCalculation())(*hash) << cPtrDiff(B);
				}
			}
		}
		if (ForEachElem) {
			for (int i = 0; i < GetAmountOfElements(); i++) {
				BaseClass* elm = (*this)[i];
				result->BC = elm;
				if(!OnlyPointersMode)result->ID = elm ? elm->GetClassName() : NULL;
				result->Ptr = elm;
				if ((*ForEachElem)(result))return;
			}
		} else
		if(result && required_index>=0 && required_index < GetAmountOfElements()) {
			BaseClass* elm = (*this)[required_index];
			result->BC = elm;
			if (!OnlyPointersMode)result->ID = elm ? elm->GetClassName() : NULL;
			result->Ptr = elm;
		}
	}

	// @copy DynArray::End()
	X* End() const {
		const int  n = comms::cList<X*>::Count();
		if (n == 0) {
#ifdef SAFE_ARRAY
			return comms::cList<X*>::m_Container->List[0];//DlaBitja;
#endif
		}
		return comms::cList<X*>::m_Container->List[n - 1];
	}

	inline int Add(X* V) {
		if (V)V->SimplySetParent(this);
		return comms::cList<X*>::Add(V);
	}
	inline int Add(X* V, int N) {
		int p = comms::cList<X*>::Add(V, N);
		if (V)V->SetParent(this);
		return p;
	}
	inline bool Insert(int pos, X* V) {
		bool p = false;
		if (!(pos<0 || pos>comms::cList<X*>::Count())) {
			comms::cList<X*>::Insert(pos, V);
			p = true;
		}
		if (V)V->SetParent(this);
		return p;
	}
	virtual bool Load(TagsList& xml,void* ClassPtr,void* Extra = NULL) override {
		((ClassArray<X>*)ClassPtr)->Clear();
		return BaseClass::Load(xml,ClassPtr,Extra);
	}
	virtual int ExpandWith(const char* ElmName, void* base) {
		ClassArray<X>* BC = (ClassArray<X>*)base;
		OneClassStorage* OCS = CGARB.GetClass(ElmName);
		if (OCS) {
			BaseClass* NewBase = OCS->OneMemb;
			if (NewBase) {
				BaseClass* B1 = NewBase->new_element();
				BC->Add((X*)B1);
				B1->SetParent(this);
				return BC->Count() - 1;
			}
            else {
                cAssert(0); // Reg class "REG_CLASS(ElmName)" or check "_modify_class_name"
                return -1;
            }
		}
        else {
            cAssert(0);
            return -1;
        }
	}
	virtual bool DelElement(int index) {
		if (index >= 0 && index < comms::cList<X*>::Count()) {
			if ((*this)[index])delete((*this)[index]);
			comms::cList<X*>::RemoveAt(index, 1);
			return true;
		}
		else return false;
	}

	// @copy DynArray::Del()
	void Del(int index, int n) {
		// @todo stable We always called in the project DynArray::Del().
		//       But look to DelElement() above! Verify it.
		comms::cList<X*>::RemoveAt(index, n);
	}

	virtual bool CheckDirectCasting() const {
		return true;
	}
	virtual bool FullCopy(const void* SrcData, const void* SrcDataExtra, BaseClass* Dest, void* DestData, void* DestExtraPtr, CECopyContext* C) override {
		ClassArray<X>* SA = (ClassArray<X>*)SrcData;
		ClassArray<X>* DA = (ClassArray<X>*)DestData;
		DA->Clear();
		for (int i = 0; i < SA->Count(); i++)if ((*SA)[i]) {
			X* E = (X*)(*SA)[i]->new_element();
			DA->Add(E);
			(*SA)[i]->FullCopy((*SA)[i], SrcDataExtra, E, E, DestExtraPtr, C);
		}
		return true;
	}
	virtual void SaveBin(void* Data, void* Extra, BinStream* Out, Enumerator* ExDictionary, Enumerator* SkipList) override {
		Out->WriteDWORD(comms::cList<X*>::Count());
		comms::cStr s;
		for (int i = 0; i < comms::cList<X*>::Count(); i++) {
			BaseClass* BC = (*this)[i];
			s = BC->GetClassName();
			_cStr sc;
			sc.SaveBin(&s, NULL, Out, ExDictionary, SkipList);
			BC->SaveBin(BC, Extra, Out, ExDictionary, SkipList);
		}
	}
	virtual	void LoadBin(void* Data, void* Extra, BinStream* In, Enumerator* ExDictionary) override {
		Clear();
		int N = In->ReadDWORD();
		comms::cStr s;
		for (int i = 0; i < N; i++) {
			_cStr sc;
			sc.LoadBin(&s, NULL, In, ExDictionary);
			int id = ExpandWith(s.ToCharPtr(), Data);
			if (id != -1) {
				BaseClass* BC = (*this)[id];
				BC->LoadBin(BC, Extra, In, ExDictionary);
			}
			else {
				//Log.Warning("%s::LoadBin : unable to find class %s",GetClassName(),s.ToCharPtr());
			}
			if (In->GetReadPos() >= In->Size()) {
				break;
			}
		}
	}
	X* GetLast() {
		if (comms::cList<X*>::Count() == 0)return NULL;
		return comms::cList<X*>::m_Container->List[comms::cList<X*>::m_Container->Count - 1];
	}
	AUTONEW(ClassArray);
};

template <class X>
ClassArray<X>::ClassArray(const ClassArray<X>& src) {
	operator = (src);
}

template <class X>
void ClassArray<X>::operator=(const ClassArray<X>& src) {
	Clear();
	for (int i = 0; i < src.Count(); i++) {
		BaseClass* B1 = src[i]->new_element();
		BaseClass* B0 = static_cast<BaseClass*>(src[i]);
		B0->CopyBaseClass(B1);
		Add((X*)B1);
	}
}

template<class X>class ClonesArray :public ClassArray<X> {
public:
	virtual int GetExpansionRules() {
		return 1;//0-no expansion 1-expand with base type only 2-expand with child classes
	}
};
template <class X> class ClassPtr :public BaseClass {
	X* ptr;
public:
	virtual bool FullCopy(const void* SrcData, const void* SrcDataExtra, BaseClass* Dest, void* DestData, void* DestExtraPtr, CECopyContext* C) override {
		if (ptr) {
			X* x = (X*)ptr->new_element();
			x->SetParent(Dest);
			((ClassPtr<X>*)Dest)->ptr = x;
			ptr->FullCopy(ptr, SrcDataExtra, x, x, DestExtraPtr, C);
		}
		return true;
	}
	virtual void SaveBin(void* Data, void* Extra, BinStream* Out, Enumerator* ExDictionary, Enumerator* SkipList) override {
		BaseClass* BC = Get();
		Out->WriteBYTE(BC ? 1 : 0);
		if (BC) {
			comms::cStr s = BC->GetClassName();
			_cStr sc;
			sc.SaveBin(&s, Extra, Out, ExDictionary, SkipList);
			BC->SaveBin(BC, Extra, Out, ExDictionary, SkipList);
		}
	}
	virtual	void LoadBin(void* Data, void* Extra, BinStream* In, Enumerator* ExDictionary) override {
		int N = In->ReadBYTE();
		if (N) {
			comms::cStr s;
			_cStr sc;
			sc.LoadBin(&s, Extra, In, ExDictionary);
			ExpandWith(s.ToCharPtr(), Data);
			BaseClass* BC = Get();
			if (BC) {
				BC->LoadBin(BC, Extra, In, ExDictionary);
			}
		}
		else Set(NULL);
	}
	//ClassPtr& operator = (X* x){ptr=x;}
	X* Get() {
		return ptr;
	}
	void Set(X* x) {
		ptr = x;
		if (ptr)ptr->SetParent(this);
	}


	ClassPtr() {
		ptr = nullptr;
	}
	virtual ~ClassPtr() {
		reset_class(this);
	};
	virtual void reset_class(void* p) {
		ClassPtr<X>* cp = (ClassPtr<X>*)p;
		if (cp->ptr)delete(cp->ptr);
		cp->ptr = NULL;
	}
	void Clear() {
		reset_class(this);
	}
	const char* GetClassName() const override {
		static char N[64] = "";
		if (!N[0]) {
			X* x = new X;
			sprintf(N, "ClassPtr.%s", x->GetClassName());
			delete(x);
		}
		return N;
	}
	int GetAmountOfElements() override {
		return ptr ? 1 : 0;
	}
	virtual bool GetElement(BaseClassElement& res, int idx, const void* Ptr, const void* Extra) override {
		if (idx == 0 && ptr) {
			res.BC = ptr;
			res.ID = ptr->GetClassName();
			res.Ptr = ptr;
			return true;
		}
		return false;
	}
	virtual int ExpandWith(const char* ElmName, void* base) {
		reset_class(base);
		ClassPtr<X>* BC = (ClassPtr<X>*)base;
		OneClassStorage* OCS = CGARB.GetClass(ElmName);
		if (OCS) {
			BaseClass* NewBase = OCS->OneMemb;
			if (NewBase) {
				BC->ptr = (X*)NewBase->new_element();
				BC->ptr->SetParent(this);
				return 0;
			}
			else return -1;
		}
		else return -1;
	}
	
	virtual bool DelElement(int index) {
		reset_class(this);
		return true;
	}
	virtual bool CheckDirectCasting() const {
		return true;
	}
	virtual bool ForceProperty() { return true; }
	virtual void CountObjects(int& required_index, int* counter, HashSummator* hash, BaseClassElement* result, const std::function<bool(BaseClassElement*)>* ForEachElem, bool OnlyPointersMode) override {
		if (counter && ptr)* counter ++;
		if (hash) {
			if(ptr){
				ptr->UpdateHash(*hash, ptr, nullptr);
				//(*hash) << cPtrDiff(ptr);
			}
		}
		if (ForEachElem) {
			if(ptr){
				result->BC = ptr;
				if (!OnlyPointersMode) {
					result->ID = ptr->GetClassName();
				}
				result->Ptr = ptr;
				(*ForEachElem)(result);
			}
		}
		else
		if (result && required_index == 0 && ptr) {
			result->BC = ptr;
			if (!OnlyPointersMode) {
				result->ID = ptr->GetClassName();
			}
			result->Ptr = ptr;
		}
	}
	AUTONEW(ClassPtr);
};

template <class X> class ClassRef :public BaseClass {
	X* ptr;
public:
	virtual bool FullCopy(const void* SrcData, const void* SrcDataExtra, BaseClass* Dest, void* DestData, void* DestExtraPtr, CECopyContext* C) override {
		return true;
	}
	virtual void SaveBin(void* Data, void* Extra, BinStream* Out, Enumerator* ExDictionary, Enumerator* SkipList) override {
	}
	virtual	void LoadBin(void* Data, void* Extra, BinStream* In, Enumerator* ExDictionary) override {
	}
	//ClassRef& operator = (X* x){ptr=x;}
	X* Get() {
		return ptr;
	}
	void Set(X* x) {
		ptr = x;
	}


	ClassRef() {
		ptr = nullptr;
	}
	virtual ~ClassRef() {
		ptr = nullptr;
	};
	virtual void reset_class(void* p) {
		ptr = nullptr;
	}
	void Clear() {
		ptr = nullptr;
	}
	const char* GetClassName() const override {
		static char N[64] = "";
		if (!N[0]) {
			X* x = new X;
			sprintf(N, "ClassRef.%s", x->GetClassName());
			delete(x);
		}
		return N;
	}
	int GetAmountOfElements() override {
		return ptr ? 1 : 0;
	}
	virtual bool GetElement(BaseClassElement& res, int idx, const void* Ptr, const void* Extra) override {
		if (idx == 0 && ptr) {
			res.BC = ptr;
			res.ID = ptr->GetClassName();
			res.Ptr = ptr;
			return true;
		}
		return false;
	}
	virtual int ExpandWith(const char* ElmName, void* base) {
		return -1;
	}

	virtual bool DelElement(int index) {
		ptr = nullptr;
		return true;
	}
	virtual bool CheckDirectCasting() const {
		return true;
	}
	virtual bool MayBeParent() override {
		return false;
	}
	virtual bool ForceProperty() { return true; }
	virtual void CountObjects(int& required_index, int* counter, HashSummator* hash, BaseClassElement* result, const std::function<bool(BaseClassElement*)>* ForEachElem, bool OnlyPointersMode) override {
		if (counter && ptr)* counter++;
		if (hash) {
			if (ptr) {
				ptr->UpdateHash(*hash, ptr, nullptr);
				//(*hash) << cPtrDiff(ptr);
			}
		}
		if (ForEachElem) {
			if (ptr) {
				result->BC = ptr;
				if (!OnlyPointersMode) {
					result->ID = ptr->GetClassName();
				}
				result->Ptr = ptr;
				(*ForEachElem)(result);
			}
		}
		else
			if (result && required_index == 0 && ptr) {
				result->BC = ptr;
				if (!OnlyPointersMode) {
					result->ID = ptr->GetClassName();
				}
				result->Ptr = ptr;
			}
	}
	AUTONEW(ClassRef);
};
template<class X, class BaseForX> class LinearArray :public BaseClass, public comms::cList<X> {
public:
	BaseForX B;
	X B1;
	virtual ~LinearArray() {
		reset_class(this);
	};
	virtual void reset_class(void* DataPtr) {
		LinearArray* LA = (LinearArray*)DataPtr;
		LA->Free();
	}
	virtual bool Load(TagsList& xml,void* ClassPtr,void* Extra = NULL) override {
		((LinearArray<X, BaseForX>*)ClassPtr)->Clear();
		return BaseClass::Load(xml,ClassPtr,Extra);
	}
	const char* GetClassName() const override {
		static char N[64] = "";
		if (N[0] != 'L') {
			BaseForX* x = new BaseForX;
			sprintf(N, "LinearArray.%s", x->GetClassName());
			delete(x);
		}
		return N;
	}
	int GetAmountOfElements() override {
		return comms::cList<X>::Count();
	}
	virtual void CountObjects(int& required_index, int* counter, HashSummator* hash, BaseClassElement* result, const std::function<bool(BaseClassElement*)>* ForEachElem, bool OnlyPointersMode) override {
		if (counter)* counter += GetAmountOfElements();
		if (hash) {
			for (int i = 0; i < GetAmountOfElements(); i++) {
				B.UpdateHash(*hash, &(*this)[i], nullptr);
			}
		}
		if (ForEachElem) {
			for (int i = 0; i < GetAmountOfElements(); i++) {
				result->BC = &B;
				if (!OnlyPointersMode) {
					static char temp[16] = "";
					sprintf(temp, "e%d", i);
					result->ID = temp;
				}
				result->Ptr = &(*this)[i];
				if ((*ForEachElem)(result))return;
			}
		}
		else
			if (result && required_index >= 0 && required_index < GetAmountOfElements()) {
				result->BC = &B;
				if (!OnlyPointersMode){
					static char temp[16] = "";
					sprintf(temp, "e%d", required_index);
					result->ID = temp;
				}
				result->Ptr = &(*this)[required_index];
			}
	}
	virtual int ExpandWith(const char* ElmName, void* base) {
		LinearArray<X, BaseForX>* BC = (LinearArray<X, BaseForX>*)base;
		BC->Add(B1);
		return BC->Count() - 1;
	}
	virtual bool DelElement(int index) {
		if (index >= 0 && index < comms::cList<X>::Count()) {
			comms::cList<X>::RemoveAt(index, 1);
			return true;
		}
		else return false;
	}
	typedef LinearArray<X, BaseForX> LA;
	virtual bool CheckDirectCasting() const {
		return true;
	}
	AUTONEW(LA);
};
