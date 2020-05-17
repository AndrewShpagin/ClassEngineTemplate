#pragma once
float ToFloat(const char* str);
class _color:public BaseClass{
public:
	virtual bool CheckCompartabilityWith(const char* TypeName,int TypeSize){
		return TypeSize==4;
	}
	virtual void Save(TagsList& xml, void* ClassPtr, void* Extra=NULL) override;
	virtual bool Load(TagsList& xml,void* ClassPtr,void* Extra=NULL) override;
	virtual const char* GetClassName() const override;  
	virtual void reset_class(void* ptr){
		*((DWORD*)ptr)=0;
	}
	virtual bool FullCopy(const void* SrcData, const void* SrcDataExtra, BaseClass* Dest, void* DestData, void* DestExtraPtr, CECopyContext* C) override{
		*((int*)DestData)=*((int*)SrcData);
		return true;
	}
	virtual void SaveBin(void* Data, void* Extra, BinStream* Out, Enumerator* ExDictionary, Enumerator* SkipList) override;
	virtual	void LoadBin(void* Data, void* Extra, BinStream* In, Enumerator* ExDictionary) override;
	virtual	void UpdateHash(HashSummator& H, void* data = nullptr, void* extra = nullptr) override;
	virtual BaseWidget* OnCreateControlFromScratch(const ClassEditorContext& Context, Rct& Rect) override;
	AUTONEW(_color);
};
reg_auto_specialisation_template(_color, DWORD);
class _WinFont:public BaseClass{
public:
	virtual bool CheckCompartabilityWith(const char* TypeName,int TypeSize){
		return strstr(TypeName,"int")!=NULL;
	}
	virtual const char* GetClassName() const override{
		return "_WinFont";
	}
	virtual void reset_class(void* ptr){		
	}
	virtual bool FullCopy(const void* SrcData, const void* SrcDataExtra, BaseClass* Dest, void* DestData, void* DestExtraPtr, CECopyContext* C) override{		
		return true;
	}
	virtual void Save(TagsList& xml, void* ClassPtr, void* Extra) override{

	}
	virtual bool Load(TagsList& xml,void* ClassPtr,void* Extra) override{
		return true;
	}
	AUTONEW(_WinFont);
};

class _WORD:public BaseClass{
public:
	virtual bool CheckCompartabilityWith(const char* TypeName,int TypeSize){
		return TypeSize==2;
	}
	virtual void Save(TagsList& xml, void* ClassPtr, void* Extra=NULL) override;
	virtual bool Load(TagsList& xml,void* ClassPtr,void* Extra=NULL) override;
	virtual const char* GetClassName() const override; 
	virtual void reset_class(void* ptr){
		*((WORD*)ptr)=0;
	}
	virtual bool FullCopy(const void* SrcData, const void* SrcDataExtra, BaseClass* Dest, void* DestData, void* DestExtraPtr, CECopyContext* C) override{
		*((WORD*)DestData)=*((WORD*)SrcData);
		return true;
	}
	virtual void SaveBin(void* Data, void* Extra, BinStream* Out, Enumerator* ExDictionary, Enumerator* SkipList) override;
	virtual	void LoadBin(void* Data, void* Extra, BinStream* In, Enumerator* ExDictionary) override;
	AUTONEW(_WORD);
};//_WORD
reg_auto_specialisation_template(_WORD, WORD);
class _short:public BaseClass{
public:
	virtual bool CheckCompartabilityWith(const char* TypeName,int TypeSize){
		return TypeSize==2;
	}
	virtual void Save(TagsList& xml, void* ClassPtr, void* Extra=NULL) override;
	virtual bool Load(TagsList& xml,void* ClassPtr,void* Extra=NULL) override;
	virtual const char* GetClassName() const override;  
	virtual void reset_class(void* ptr){
		*((short*)ptr)=0;
	}
	virtual bool FullCopy(const void* SrcData, const void* SrcDataExtra, BaseClass* Dest, void* DestData, void* DestExtraPtr, CECopyContext* C) override{
		*((WORD*)DestData)=*((WORD*)SrcData);
		return true;
	}
	virtual void SaveBin(void* Data, void* Extra, BinStream* Out, Enumerator* ExDictionary, Enumerator* SkipList) override;
	virtual	void LoadBin(void* Data, void* Extra, BinStream* In, Enumerator* ExDictionary) override;
	AUTONEW(_short);
};//_short
reg_auto_specialisation_template(_short, short);
class _char:public BaseClass{
public:
	virtual bool CheckCompartabilityWith(const char* TypeName,int TypeSize){
		return TypeSize==1;
	}
	virtual void Save(TagsList& xml, void* ClassPtr, void* Extra=NULL) override;
	virtual bool Load(TagsList& xml,void* ClassPtr,void* Extra=NULL) override;
	virtual const char* GetClassName() const override; 
	virtual void reset_class(void* ptr){
		*((char*)ptr)=0;
	}
	virtual bool FullCopy(const void* SrcData, const void* SrcDataExtra, BaseClass* Dest, void* DestData, void* DestExtraPtr, CECopyContext* C) override{
		*((char*)DestData)=*((char*)SrcData);
		return true;
	}
	virtual void SaveBin(void* Data, void* Extra, BinStream* Out, Enumerator* ExDictionary, Enumerator* SkipList) override;
	virtual	void LoadBin(void* Data, void* Extra, BinStream* In, Enumerator* ExDictionary) override;
	AUTONEW(_char);
};//_char
reg_auto_specialisation_template(_char, char);
class _BYTE:public BaseClass{
public:
	virtual bool CheckCompartabilityWith(const char* TypeName,int TypeSize){
		return TypeSize==1;
	}
	virtual void Save(TagsList& xml, void* ClassPtr, void* Extra=NULL) override;
	virtual bool Load(TagsList& xml,void* ClassPtr,void* Extra=NULL) override;
	virtual const char* GetClassName() const override; 
	virtual void reset_class(void* ptr){
		*((BYTE*)ptr)=0;
	}
	virtual bool FullCopy(const void* SrcData, const void* SrcDataExtra, BaseClass* Dest, void* DestData, void* DestExtraPtr, CECopyContext* C) override{
		*((BYTE*)DestData)=*((BYTE*)SrcData);
		return true;
	}
	virtual void SaveBin(void* Data, void* Extra, BinStream* Out, Enumerator* ExDictionary, Enumerator* SkipList) override;
	virtual	void LoadBin(void* Data, void* Extra, BinStream* In, Enumerator* ExDictionary) override;
	AUTONEW(_BYTE);
};//_byte
reg_auto_specialisation_template(_BYTE, byte);
class _ModelID:public BaseClass{
public:
	virtual bool CheckCompartabilityWith(const char* TypeName,int TypeSize){
		return TypeSize==4;
	}
	virtual void Save(TagsList& xml, void* ClassPtr, void* Extra=NULL) override;
	virtual bool Load(TagsList& xml,void* ClassPtr,void* Extra=NULL) override;
	virtual const char* GetClassName() const override;  
	virtual bool FullCopy(const void* SrcData, const void* SrcDataExtra, BaseClass* Dest, void* DestData, void* DestExtraPtr, CECopyContext* C) override{
		*((int*)DestData)=*((int*)SrcData);
		return true;
	}
	virtual void SaveBin(void* Data, void* Extra, BinStream* Out, Enumerator* ExDictionary, Enumerator* SkipList) override{
	}
	virtual	void LoadBin(void* Data, void* Extra, BinStream* In, Enumerator* ExDictionary) override{
	}
	AUTONEW(_ModelID);
};//_ModelID
class _TextureID:public BaseClass{
public:
	virtual bool CheckCompartabilityWith(const char* TypeName,int TypeSize){
		return TypeSize==4;
	}
	virtual void Save(TagsList& xml, void* ClassPtr, void* Extra=NULL) override;
	virtual bool Load(TagsList& xml,void* ClassPtr,void* Extra=NULL) override;
	virtual const char* GetClassName() const override;    	
	virtual bool FullCopy(const void* SrcData, const void* SrcDataExtra, BaseClass* Dest, void* DestData, void* DestExtraPtr, CECopyContext* C) override{
		*((int*)DestData)=*((int*)SrcData);
		return true;
	}
	virtual void SaveBin(void* Data, void* Extra, BinStream* Out, Enumerator* ExDictionary, Enumerator* SkipList) override{
		Out->Write(Data,4);
	}
	virtual	void LoadBin(void* Data, void* Extra, BinStream* In, Enumerator* ExDictionary) override{
		In->Read(Data,4);
	}
	virtual BaseWidget* OnCreateControlFromScratch(const ClassEditorContext& Context, Rct& Rect) override;
	AUTONEW(_TextureID);
};//_TextureID
