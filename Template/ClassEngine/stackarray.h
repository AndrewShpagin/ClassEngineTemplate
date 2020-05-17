#pragma once

class BinStream;
//#define SAFE_ARRAY
template <class Elem,int DefElmCount=16>
class StackArray{
public:
	Elem* Values;
	Elem* AllocElem;
	Elem StackValues[DefElmCount];
	int NValues;
	int MaxValues;

	inline void Check(int N){
		if(N>=MaxValues){
			MaxValues=N+DefElmCount+MaxValues/2;
			Elem* tmp=(Elem*)_ExMalloc(MaxValues*sizeof(Elem));
			if(NValues){
				memcpy(tmp,Values,NValues*sizeof(Elem));
			}
			if(AllocElem)_ExFree(AllocElem);
			Values=AllocElem=tmp;
		}
	}
	inline Elem* operator + (int idx){
		assert(idx>=0&&idx<NValues);
		assert(NValues);
		return Values+idx;
	}
	inline StackArray(){
		Values=&StackValues[0];
		NValues=0;
		MaxValues=DefElmCount;
		AllocElem=NULL;
	}
	inline StackArray(int Size, Elem Filling){
		Values=&StackValues[0];
		NValues=0;
		MaxValues=DefElmCount;
		Add(Filling,Size);
	}
	inline ~StackArray(){
		Clear();		
	}
	inline int Add(const Elem& V){
		Check(NValues+1);
		Values[NValues]=V;
		NValues++;
		return NValues-1;
	}
	inline int Add(const Elem& V,int NTimes){
		Check(NValues+NTimes);
		for(int i=0;i<NTimes;i++){
			memcpy(&Values[NValues],&V,sizeof(Elem));
			NValues++;
		}
		return NValues-1;
	}
	inline void RemoveAt(int pos,int N){
		if(pos<0){
			N+=pos;
			pos=0;
		}
		if(N<=0||pos>=NValues)return;
		if(pos+N>NValues)N=NValues-pos;
		if(pos+N<NValues)memcpy(Values+pos,Values+pos+N,(NValues-pos-N)*sizeof(Elem));
		NValues-=N;
	}

	inline int find(const Elem& v){
		for(int i=0;i<NValues;i++)if(v==Values[i])return i;
		return -1;
	}

	inline bool Insert(int pos,const Elem& V){
		if(pos<0||pos>NValues)return false;
		Check(NValues+1);
		if(pos<NValues)memmove(Values+pos+1,Values+pos,(NValues-pos)*sizeof(Elem));
		Values[pos]=V;
		NValues++;
		return true;
	}

	inline bool Move(int from, int to){		
		if(from>=NValues) from=NValues-1; else if(from<0) from=0;
		if(to>=NValues) to=NValues-1; else if(to<0) to=0;
		if(from==to) return false;		
		Elem t=Values[from];
		if(from<to){
			memcpy(Values+from,Values+from+1,(to-from)*sizeof(Elem));
		}else{
			memmove(Values+to+1,Values+to,(from-to)*sizeof(Elem));
		}		
		Values[to]=t;
		return true;
	}
	inline Elem& operator [](int pos){
		assert(pos>=0&&pos<NValues);
#ifdef SAFE_ARRAY
		if(pos<0||pos>=NValues)return Values[0];//DlaBitja
#endif //SAFE_ARRAY
		return Values[pos];
	}
	inline Elem operator [](int pos) const {
		assert(pos>=0&&pos<NValues);
#ifdef SAFE_ARRAY
		if(pos<0||pos>=NValues)return Values[pos];//DlaBitja;
#endif //SAFE_ARRAY
		return Values[pos];
	}
	inline void operator += (const StackArray& A){
		AddRange(A.Values,A.NValues);
	}
	inline void operator += (Elem V){
		Add(V);
	}
	inline Elem* ToPtr()const{//use only to save data!!!
		return Values;
	}
	inline void AddRange(Elem* Data,int N){
		Check(NValues+N);
		memcpy(Values+NValues,Data,N*sizeof(Elem));
		NValues+=N;
	}
	inline int Count()const{
		return NValues;
	}
	inline void Clear(){
		if(AllocElem)_ExFree(AllocElem);
		Values=&StackValues[0];
		NValues=0;
		MaxValues=DefElmCount;
		AllocElem=NULL;
	}
	inline void FastClear(){		
		NValues=0;
	}
	inline void Fill(int Value){		
		memset(Values,Value,NValues*sizeof(Elem));
	}
	inline Elem& GetFirst(){
		assert(NValues!=0);
#ifdef SAFE_ARRAY
		if(NValues==0)return Values[0];//DlaBitja;
#endif
		return Values[0];
	}
	inline Elem& GetLast(){
		assert(NValues!=0);
		if(NValues==0){
#ifdef SAFE_ARRAY
			return Values[0];//DlaBitja;
#endif
		}
		return Values[NValues-1];
	}	
	inline Elem pop_back(){
		if(NValues>0){
			return Values[--NValues];
		}else return Values[0];
	}
    inline void CopyTo(StackArray<Elem>& dest){
        dest.Check(NValues);
        memcpy(dest.Values,Values,NValues*sizeof(Elem));
        dest.NValues=NValues;
    }
	inline void MoveArrayTo(StackArray<Elem>& dest){
		dest.Clear();
		dest.Values=Values;
		dest.NValues=NValues;
		Values=NULL;
		NValues=0;
	}
	inline void pop_front(){
		RemoveAt(0,1);
	}
	inline bool AddOnce(Elem V){
		if(find(V)==-1){
			Add(V);
			return true;
		}
		return false;
	}
	inline void ToBS(BinStream& BS);
	inline void FromBS(BinStream& BS,int ne);
};

