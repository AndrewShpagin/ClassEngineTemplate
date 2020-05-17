#pragma once

template <class Elem,int CellSize=1024>
class BigDynArray
{
	Elem** Values;
	int NValues;
	int MaxValues;	
	int MaxCells;
public:	

	inline void Check(int N){
		if(N>=MaxValues){
			int n=1+(N/CellSize);
			int n0=MaxCells;
			if(n>=MaxCells){				
				MaxCells=std::max(MaxCells+512,n+1);
				Elem** np=(Elem**)_ExMalloc(MaxCells*sizeof(Elem*));
				memset(np,0,MaxCells*sizeof(Elem*));
				if(Values){
					memcpy(np,Values,n0*sizeof(Elem*));
					_ExFree(Values);
				}
				Values=np;
			}
			for(int i=MaxValues/CellSize;i<n;i++){
				Values[i]=(Elem*)_ExMalloc(CellSize*sizeof(Elem));
			}
			MaxValues=n*CellSize;
		}
	}
	inline BigDynArray(){
		Values=NULL;
		NValues=0;
		MaxValues=0;		
		MaxCells=0;
	}
	inline BigDynArray(int Size, Elem Filling){
		Values=NULL;
		NValues=0;
		MaxValues=0;		
		MaxCells=0;
		Add(Filling,Size);
	}
	inline ~BigDynArray(){
		Clear();		
	}
	inline int Add(const Elem& V){
		Check(NValues+1);
		int p1=NValues/CellSize;
		Values[p1][NValues%CellSize]=V;
		NValues++;
		return NValues-1;
	}
	inline int Add(const Elem& V,int NTimes){		
		int r=NValues-1;
		for(int i=0;i<NTimes;i++){
			r=Add(V);
		}
		return r;
	}		
	
	inline Elem& operator [](int pos){
		assert(pos>=0&&pos<NValues);		
		return Values[pos/CellSize][pos%CellSize];
	}
	inline Elem operator [](int pos) const {
		assert(pos>=0&&pos<NValues);		
		return Values[pos/CellSize][pos%CellSize];
	}		
	inline int Count()const{
		return NValues;
	}
	inline void Clear(){
		if(Values){
			for(int i=0;i<MaxCells;i++){
				if(Values[i])_ExFree(Values[i]);
			}
			_ExFree(Values);
		}
		Values=NULL;
		NValues=0;
		MaxValues=0;		
		MaxCells=0;
	}
	inline void FastClear(){		
		NValues=0;
	}	
	inline void Del(int pos,int num){
		int nv=Count();
		if(pos+num>nv){
			num=nv-pos;
		}
		if(num<=0)return;
		for(int p=0;p<num;p++){
			int ps=pos+p;
			int pn=ps+num;			
			if(pn<nv && ps<nv){
				(*this)[ps]=(*this)[pn];
			}
		}
		NValues-=num;
	}
	inline void ToBS(BinStream& BS){
		int nvc=NValues/CellSize;
		for(int i=0;i<=nvc;i++){
			int sz=i==nvc? (NValues%CellSize) : CellSize;
			if(sz)BS.Write(Values[i],sz*sizeof(Elem));
		}
	}
	inline void FromBS(BinStream& BS,int ne){
		Clear();
		Check(ne);
		NValues=ne;
		int nvc=ne/CellSize;		
		for(int i=0;i<=nvc;i++){
			int sz=i==nvc? (NValues%CellSize) : CellSize;
			if(sz)BS.Read(Values[i],sz*sizeof(Elem));
		}
	}
	Elem& ExpandTo(int pos,Elem def){
        if ( pos >= Count() )Add( def, pos - Count() + 1 );
        return (*this)[ pos ];
	}
};
