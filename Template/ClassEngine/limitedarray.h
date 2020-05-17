#pragma once

#ifndef __STDAPPLICATION__
#include "../3D-Coat/smart_assert.h"
#else //__STDAPPLICATION__
//#include "assert.h"
#endif //__STDAPPLICATION__
class BinStream;
//#define SAFE_ARRAY
template <class Elem,int MaxValues=20>
class LmArray{
public:
	Elem Values[MaxValues];
	int NValues;
	
	inline Elem* operator + (int idx){
		assert(idx>=0&&idx<NValues);
		assert(NValues);
		return Values+idx;
	}
	inline LmArray(){		
		NValues=0;		
	}
	inline LmArray(int Size, Elem Filling){
		NValues=0;
		Add(Filling,Size);
	}
	inline ~LmArray(){
		Clear();		
	}
	inline int Add(const Elem& V){
		if(NValues<MaxValues)NValues++;
		else assert(1);
		Values[NValues-1]=V;		
		return NValues-1;
	}	
	inline void Del(int pos,int N){
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
		if(NValues>=MaxValues)return false;
		if(pos<0||pos>NValues)return false;		
		if(pos<NValues)memmove(Values+pos+1,Values+pos,(NValues-pos)*sizeof(Elem));
		Values[pos]=V;
		NValues++;
		return true;
	}
	
	inline Elem& operator [](int pos){
		return Values[pos];
	}
	inline Elem operator [](int pos) const {
		return Values[pos];
	}	
	inline void operator += (Elem V){
		Add(V);
	}
	inline Elem* GetValues()const{//use only to save data!!!
		return &Values;
	}	
	inline int GetAmount()const{
		return NValues;
	}
	inline void Clear(){
		NValues=0;		
	}
	inline void FastClear(){		
		NValues=0;
	}
	inline void Fill(int Value){		
		memset(Values,Value,NValues*sizeof(Elem));
	}
	inline Elem Begin(){
		assert(NValues!=0);
#ifdef SAFE_ARRAY
		if(NValues==0)return Values[0];//DlaBitja;
#endif
		return Values[0];
	}
	inline Elem End(){
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
	inline void pop_front(){
		Del(0,1);
	}
	inline bool AddOnce(Elem V){
		if(find(V)==-1){
			Add(V);
			return true;
		}
		return false;
	}	
};

