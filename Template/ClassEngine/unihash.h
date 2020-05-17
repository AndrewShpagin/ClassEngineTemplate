#pragma once

//enable this define to check if depth of each chain is no more that 10
//if depth exceeds breakpoint may be triggered, seek for DEBUG_UNI_DEPTH
//#define DEBUG_UNI_DEPTH


//uni_hash is somtehing like STL's multimap. It makes corespondence between Key and multiple Elements
//Key is class that satisfies several easy requirements. Simple types like int, char, DWORD satisfy 
//that conditions automatically. You may see examples of more complex classes below - bi_DWORD, tri_DWORD, 
//DWORDS2 etc.
//The important possibility is convenient cycles organisation with uni_hash
//For example this cycle scans thorough all elements in hash:
//scan(hash,Element* E,Key* K){
//   ... operate over E and K ...
//}scan_end
//
//Scan through elements that correspond to key Key
//scan_key(hash,Key,Element* E){
//   ... operate over E ...
//}scan_end
//
//you may add/delete elements in hash within scan... cycles, but there is no warranty that scan will went through new element 

const int DefaultHashTSize=3517;
//KeyClass should have functions, if not defined by default:
//DWORD  operator =  (const Class& c) const;
//Class& operator =  (const Class& c) const;
//bool   operator == (const Class& c) const;
//Class should have functions, if not defined by default:
//Class& operator =  (const Class& c) const;
class hash_context{
public:
    hash_context(){
		ptr = pptr = NULL;
        ScanAll=false;
		TblPos = pTblPos = 0;
    }
    void* ptr;
	void* pptr;
    bool ScanAll;
    int  TblPos;
	int  pTblPos;
};

template <class KeyClass=DWORD,class Class=DWORD>
struct Pair{
	KeyClass first;
	Class second;
};

template <class Class, class KeyClass, int PoolSectionSize>
class uni_hash_allocator {
public:
	class temp_s {
		///dependent on implementation
		temp_s* next;
		int			index;
	public:
		friend uni_hash_allocator;
		///mandatory fields
		KeyClass	key;
		Class		element;
	};
private:
	///dependent on implementation
	int TableSize;
	temp_s** table;
	comms::cArray<temp_s*>	pool;
	comms::cArray<temp_s*>	freeVals;
public:
	
	
	temp_s* allocate() {
		if (!freeVals.Count()) {
			temp_s* pa = new temp_s[PoolSectionSize];
			int sz0 = pool.Count() * PoolSectionSize;
			pool.Add(pa);
			freeVals.SetCapacity(freeVals.Count() + PoolSectionSize);
			for (int i = 0; i < PoolSectionSize; i++) {
				temp_s* ts = pa + PoolSectionSize - i - 1;
				release(ts);
			}
		}
		temp_s* fv = freeVals.pop_back();
		fv->index = -1 - fv->index;
		assert(fv->index >= 0);
		return fv;
	}
	void release(temp_s* p) {
		if (p->index >= 0)p->index = -1 - p->index;
		freeVals.Add(p);
	}
	temp_s* next(temp_s* cur) {
		return cur->next;
	}
	temp_s* value(int table_index) {
		return (*table)[table_index];
	}
	void release_table() {
		if (table)delete(table);
		table = nullptr;
	}
	///returns size that it was able to allocate
	int allocate_table(int size) {
		
	}
};

template <class Class,class KeyClass=DWORD,int DefTableSize = DefaultHashTSize,int PoolSectionSize=512>
class uni_hash{	
public:
	struct temp_s{
		KeyClass	key;
		Class		element;
		temp_s*		next;
		int			index;
	};
private:
    typedef temp_s _parray [PoolSectionSize];
	typedef temp_s* ptemp_s;
	int					TableSize;
	int					PoolSize;
    temp_s**			table;
    comms::cArray<temp_s*>	pool;
    comms::cArray<temp_s*>	freeVals;
	void _check_table(){
		if(table==NULL){
			if(TableSize==0)TableSize=32;
			table=new ptemp_s[TableSize];
			memset(table,0,TableSize*sizeof(void*));
		}
	}
    temp_s* _get_temp_s(){
        if(!freeVals.Count()){
            temp_s* pa=new temp_s[PoolSectionSize];
            int sz0=pool.Count()*PoolSectionSize;
            pool.Add(pa);
            freeVals.SetCapacity( freeVals.Count() + PoolSectionSize );
            for(int i=0;i<PoolSectionSize;i++){
                temp_s* ts=pa+PoolSectionSize-i-1;
                ts->index=-1-(PoolSectionSize-i-1+sz0);
                freeVals.Add(ts);
            }
        }        
        temp_s* fv=freeVals.pop_back();
        fv->index=-1-fv->index;
        assert(fv->index>=0);
        return fv;
    }	
	void _chk_depth(temp_s* ts){
		int sz=0;
		while(ts){
			sz++;
			ts=ts->next;
		}
		if(sz>10){
			//set breakpoint there if need to catch long and slow chains
			//don't forget to enable DEBUG_UNI_DEPTH 
			sz++;
			//Log.Message("uni_hash slowdown!");
		}
		
	}
public:
	uni_hash& operator = (uni_hash& other) {
		TableSize = other.TableSize;
		PoolSize = other.PoolSize;
		table = new ptemp_s[TableSize];
		memset(table, 0, TableSize * sizeof(temp_s*));
		comms::cArray< temp_s*> temp;
		for (int i = 0; i < TableSize; i++) {
			temp.Clear();
			temp_s* t = other.table[i];
			while (t) {
				temp.Add(t);
				t = t->next;
			}
			for (int k = temp.Count() - 1; k >= 0; k--) {
				add_quick(temp[k]->key, temp[k]->element);
			}
		}
		return *this;
	}
	temp_s* get_s(KeyClass K,int SubIndex,bool AddIfNotExists){
		DWORD hash=K;
		hash%=TableSize;
		if(table){
			temp_s* el=table[hash];
			while(el){
				if(el->key==K){
					if(SubIndex>0)SubIndex--;
					else return el;
				}
				el=el->next;
			}
		}
		if(AddIfNotExists){		
			_check_table();
			return add_s(K,DefValue);
		}
		return NULL;
	}
	temp_s* add_s(KeyClass K,Class& C){
		DWORD hash=K;
		hash%=TableSize;
		temp_s* ptr=_get_temp_s();
		_check_table();
		temp_s* el=table[hash];	    
		ptr->element=C;
		ptr->key=K;
		ptr->next=NULL;
		el=table[hash];
		if(el){		
			while(el->next)el=el->next;
			el->next=ptr;
		}else{
			table[hash]=ptr;
		} 
		return ptr;
	}
	//////////////////////////////////////////////////////////////////////////
	Class DefValue;
	inline void touch(){_check_table();}
	inline	void		set_table_size(int sz){
		if(table==NULL){
			TableSize=sz ? sz : 32;
		}
	}
	inline int get_table_size(){
		return TableSize;
	}
	inline void reset_table_size(int sz=0);
	inline void refine_table();
	inline int			get_mem_usage() const {
		return (TableSize+freeVals.Count()+pool.Count())*sizeof(void*)+pool.Count()*sizeof(temp_s)*PoolSectionSize;
	}
    inline				uni_hash	();	
    inline				~uni_hash	();	
    inline	int			size		() const;
    inline int			size		(KeyClass K) const;
    inline Class*		get			(KeyClass K,int SubIndex=0,bool AddIfNotExists=false);
	inline int			get_i		(KeyClass K,int SubIndex=0,bool AddIfNotExists=false);
	inline Class*		get_last	(KeyClass K,bool AddIfNotExists=false);
	inline int			get_i_last	(KeyClass K,bool AddIfNotExists=false);
    inline Class*		add			(KeyClass K, const Class& C);
	inline Class*		add_quick	(KeyClass K, const Class& C);
    inline int			add_i		(KeyClass K, const Class& C);
	inline Class*		add_uniq	(KeyClass K, const Class& C);//add uniq combination (K,C) - C should define operator ==
    inline int			add_uniq_i	(KeyClass K, const Class& C);
    inline Class*		replace		(KeyClass K, const Class& C,int SubIndex=-1);
    inline int			replace_i	(KeyClass K, const Class& C,int SubIndex=-1);
    inline Class*		add_once	(KeyClass K, const Class& C);
    inline int			add_once_i	(KeyClass K, const Class& C);
    inline bool		del			(KeyClass K,int SubIndex=-1);	
    inline bool		del_elm		(KeyClass K, const Class& C);//requires operator == for C
    inline Class*		operator[]  (KeyClass K);
	/// direct access through all elements in pool in range 0..pool_size-1. Some elements may be zero (invalid)
    inline Class*		elem		(int idx) const;
    inline KeyClass*	key 		(int idx) const;
	inline bool        get_direct	(int idx,Class** pc,KeyClass** pk);
	inline int			pool_size	();
	//////////////////////////////////////////////////////////////////////////
    inline void		reset		();
	inline void		fast_reset	();
	inline void		optimal_reset();
    inline void		start_scan	(KeyClass K,hash_context& ct) const;
    inline void		start_scan	(hash_context& ct) const;
    inline Class*		next		(hash_context& ct) const;
	inline Class*		next_ke		(hash_context& ct,KeyClass** _key) const;
    inline int			next_i		(hash_context& ct) const;
    inline KeyClass*   next_key    (hash_context& ct) const;
    inline DWORD		get_free_idx();
    inline void        del_all     ();
	inline void		set_default (Class C){DefValue=C;}
	inline int			simple_serialize(BYTE** buf);//this function will allocate the buffer and return size
	inline int			simple_unserialize(BYTE* buf,int ElmSizeLimit=0);//returns amount of used bytes from buffer

	//////////////////////////////////////////////////////////////////////////

	//List.AddOnce may take long time because of N^2 comparisons. Next routines will speed up AddOnce due to using the hash to check if element is already in array
	inline bool QuickAddOnceToList(comms::cList<KeyClass>& List, const KeyClass& E);
	//call this function before using QuickAddOnceToList to initialize array
	inline void InitFromList(comms::cList<KeyClass>& List);

    //////////////////////////////////////////////////////////////////////////    

    inline void        self_test   (){
		_check_table();
        for(int i=0;i<TableSize;i++){
            temp_s* ts=table[i];
            int nn=512;
            while(ts && nn--){
                assert(ts->index>=0);
                ts=ts->next;
            }
            assert(nn>0);
        }
		for (int i = 0; i < pool.Count(); i++) {
			for (int j = 0; j < PoolSectionSize; j++) {
				temp_s* ts = &pool[i][j];
				if (ts->index >= 0) {
					DWORD hash = ts->key;
					hash %= TableSize;
					temp_s* el = table[hash];
					bool found = false;
					while (el) {
						if (el == ts) {
							found = true;
						}
						el = el->next;
					}
					assert(found);
				}
			}
		}
    }

	//Useful to get paralell speed up
	inline int toList(comms::cList<Pair<KeyClass,Class> >& result){		
		int n=0;
		if (table){
			for(int i=0;i<TableSize;i++){
				temp_s* e=table[i];
				while(e){
					Pair<KeyClass,Class> p;
					p.first  = e->key;
					p.second = e->element;
					result.Add(p);

					n++;
					e=e->next;
				}
			}
		}
		return n;
	} 
	inline KeyClass* _key(hash_context* ct) const {
		return &((temp_s*)ct->pptr)->key;
	}
};
//useful macro commands
#define scan(_Hash,_ElmPtr,_KeyPtr) {hash_context _hct##__LINE__; _Hash.start_scan(_hct##__LINE__);  while(_ElmPtr=_Hash.next(_hct##__LINE__)){ _KeyPtr= _Hash._key(&_hct##__LINE__);

#define scan_e(_Hash,_ElmPtr) {hash_context _hct##__LINE__;\
    _Hash.start_scan(_hct##__LINE__);\
    while(_ElmPtr=_Hash.next(_hct##__LINE__)){       

#define scan_k(_Hash,_KeyPtr) {hash_context _hct##__LINE__;\
    _Hash.start_scan(_hct##__LINE__);\
    while(_KeyPtr=_Hash.next_key(_hct##__LINE__)){       

// Same as scan_k(), for scanning by unique keys.
// @example scan_k_unique( hash, int, key ) {
//              // do something with 'int key'
//          } scan_end;
#define scan_k_unique( _Hash, _Type, _Name ) {       \
	uni_hash< bool, K > visited;                     \
	hash_context hct;                                \
    _Hash.start_scan( hct );                         \
    while ( _Type* _Name = _Hash.next_key( hct ) ) { \
		if ( visited.get( *_Name ) ) { continue; }   \
		visited.add_quick( *_Name, true );

#define scan_key(_Hash,_Key0,_ElmPtr) {hash_context _hct##__LINE__;\
    _Hash.start_scan(_Key0,_hct##__LINE__);\
    while(_ElmPtr=_Hash.next(_hct##__LINE__)){        

#define scan_key2(_Hash,_Key0,_ElmPtr,_KeyPtr) {hash_context _hct##__LINE__;\
	_Hash.start_scan(_Key0,_hct##__LINE__);\
	while(_ElmPtr=_Hash.next_ke(_hct##__LINE__,&_KeyPtr)){        

#define scan_end }}

#include "SimplestHashes.h"

//////////////////////////////////////////////////////////////////////////

inline DWORD& _DWORD(DWORD V){
    static DWORD v;
    v=V;
    return v;
}


/// Two values of type DWORD.
typedef struct bi_DWORD{
    DWORD V1,V2;
    bi_DWORD(){};
    bi_DWORD(DWORD v1,DWORD v2){V1=v1;V2=v2;}
    operator DWORD() const {
		return V1 + V2 * 123761;
    }	
    bool   operator == (const bi_DWORD& c) const{
        return c.V1==V1 && c.V2==V2;
    }
	//operator size_t() const{ //Used for tbb hashing, the faster , the better
	//	 return size_t(V1)+size_t(V2);  //V1+V2*1791;//return sizeof(struct bi_DWORD);
	//}	
}bi_DWORD;


/// Sorted two values of type DWORD.
struct DWORDS2{
    DWORD V1,V2;
    void sort(){
		if(V2<V1)std::swap(V2,V1);
    }
    DWORDS2(){};
    DWORDS2(DWORD v1,DWORD v2){
        V1=v1;
        V2=v2;
        sort();
    }
    void set(DWORD v1,DWORD v2){
        V1=v1;
        V2=v2;
        sort();
    }
    operator DWORD() const {
        return V1+V2*123761;
    }	
    bool   operator == (const DWORDS2& c) const{
        return c.V1==V1 && c.V2==V2;
    }
};


/// Sorted three values plus attribute of type DWORD.
struct DWORDS2A{
	DWORD V1,V2,A;
	void sort(){
		if(V2<V1)std::swap(V2,V1);
	}
	DWORDS2A(){};
	DWORDS2A(DWORD v1,DWORD v2,DWORD a){
		V1=v1;
		V2=v2;
		A=a;
		sort();
	}
	void set(DWORD v1,DWORD v2,DWORD a){
		V1=v1;
		V2=v2;
        A=a;
		sort();
	}
	operator DWORD() const {
		return V1+V2*12361+A*17217;
	}	
	bool   operator == (const DWORDS2A& c) const{
		return c.V1==V1 && c.V2==V2 && c.A==A;
	}
};


/// Sorted three values of type DWORD.
struct DWORDS3{
    DWORD V1,V2,V3;
    void sort(){
        for(int i=0;i<2;i++){
            if(V2<V1)std::swap(V2,V1);
            if(V3<V2)std::swap(V3,V2);
        }
    }
    DWORDS3(){};
    DWORDS3(DWORD v1,DWORD v2,DWORD v3){
        V1=v1;
        V2=v2;
        V3=v3;
        sort();
    }
    void set(DWORD v1,DWORD v2,DWORD v3){
        V1=v1;
        V2=v2;
        V3=v3;
        sort();
    }
    operator DWORD() const {
        return V1+V2*123761+V3*17393;
    }	
    bool   operator == (const DWORDS3& c) const{
        return c.V1==V1 && c.V2==V2 && c.V3==V3;
    }
};


/// Three values of type DWORD.
struct tri_DWORD{
    DWORD V1,V2,V3;
    tri_DWORD(){};
    tri_DWORD(DWORD v1,DWORD v2,DWORD v3){V1=v1;V2=v2;V3=v3;}
    operator DWORD() const {
        return V1+V2*123761+V3*1971;
    }
    bool   operator == (const tri_DWORD& c) const{
        return c.V1==V1 && c.V2==V2 && c.V3==V3;
    }
};


/// Three values plus attribute of type DWORD.
struct tri_DWORDA{
	DWORD V1,V2,V3,A;
	tri_DWORDA(){};
	tri_DWORDA(DWORD v1,DWORD v2,DWORD v3){V1=v1;V2=v2;V3=v3;}
	operator DWORD() const {
		return V1+V2*123761+V3*1971;
	}
	bool   operator == (const tri_DWORDA& c) const{
		return c.V1==V1 && c.V2==V2 && c.V3==V3;
	}
};

/// Sorted three values of type short.
struct tri_SHORT{
	short V1,V2,V3;
	tri_SHORT(){};
	tri_SHORT(short v1,short v2,short v3){V1=v1;V2=v2;V3=v3;}
	operator DWORD() const {
		return V1+V2*123761+V3*1971;
	}
	bool   operator == (const tri_SHORT& c) const{
		return c.V1==V1 && c.V2==V2 && c.V3==V3;
	}
};
struct cube_EDGE{
	union{
		struct{
			short V1,V2,V3,Dir;
		};
		DWORD DW;
	};
	void SetDW(DWORD v){
		V1=V2=V3=Dir=0;
		DW = v;
	}
	cube_EDGE(DWORD v){
		V1=V2=V3=Dir=0;
		DW = v;
	}
	operator DWORD() const {
		return DW+V3*1971+Dir;
	}
	cube_EDGE(){};
#undef min
	cube_EDGE(const tri_SHORT& s1,const tri_SHORT s2){
		V1=std::min(s1.V1,s2.V1);		
		V2=std::min(s1.V2,s2.V2);
		V3=std::min(s1.V3,s2.V3);
		if(s1.V1!=s2.V1)Dir=0;
		else if(s1.V2!=s2.V2)Dir=1;
		if(s1.V3!=s2.V3)Dir=2;
	}
	bool   operator == (const cube_EDGE& c) const{
		return c.V1==V1 && c.V2==V2 && c.V3==V3 && c.Dir==Dir;
	}
};
struct bi_cube_EDGE{
	cube_EDGE v1;
	cube_EDGE v2;
	bi_cube_EDGE(){};
	bi_cube_EDGE(const cube_EDGE& e1,const cube_EDGE& e2){
		v1=e1;
		v2=e2;
		if(v2.V1<v1.V1)std::swap(v2,v1);
		else{
			if(v2.V1==v1.V1){
				if(v2.V2<v1.V2)std::swap(v2,v1);
				else{
					if(v2.V2==v1.V2){
						if(v2.V2==v1.V2){
							if(v2.V3<v1.V3)std::swap(v2,v1);
							else{
								if(v2.V3==v1.V3){
									if(v2.Dir<v1.Dir)std::swap(v2,v1);
								}
							}
						}
					}
				}
			}
		}
	}
	operator DWORD() const {
		return DWORD(v1)+DWORD(v2);
	}
	bool   operator == (const bi_cube_EDGE& c) const{
		return c.v1==v1 && c.v2==v2;
	}
};


/// Sorted four values of type DWORD.
struct quad_DWORD{
	DWORD V1,V2,V3,V4;
	quad_DWORD(){};
	quad_DWORD(DWORD v1,DWORD v2,DWORD v3,DWORD v4){V1=v1;V2=v2;V3=v3;V4=v4;}
	operator DWORD() const {
		return V1+V2*123761+V3*1971+V4*98641;
	}
	bool   operator == (const quad_DWORD& c) const{
		return c.V1==V1 && c.V2==V2 && c.V3==V3 && c.V4==V4;
	}
};


/// Agile class aka bi_DWORD, tri_DWORD etc..
template < size_t Dim, typename Type >
class dim_Type {
public:
	typedef Type  value_type;

public:
	explicit dim_Type( Type def = Type() ) {
		std::fill_n( V, Dim, def );
	}

	explicit dim_Type( const Type* source ) {
		std::copy( source, source + Dim, V );
	}

	virtual ~dim_Type() {}

	const Type& operator[]( size_t i ) const { return V[ i ]; }
	Type&       operator[]( size_t i )       { return V[ i ]; }

	dim_Type< Dim, Type > operator+( const dim_Type< Dim, Type >& b ) const {
		dim_Type< Dim, Type >  r;
		for (size_t i = 0; i < Dim; ++i) {
			r[ i ] = ( *this )[ i ] + b[ i ];
		}
		return r;
	}

	const Type* raw() const { return V; }

	/// \return Hash for `uni_hash`.
	/// \todo extend  Work when `Type` is a not number.
    operator DWORD() const {
		static const DWORD  K[] = {
		    1, 123761, 1971, 98641, 11411,
			1657, 1801, 9241, 4801, 769,
			// ...
		};
		assert( (Dim <= sizeof( K ) / sizeof( K[ 0 ] ))
			&& "Extend the list 'K' for calc hash." );
		DWORD  acc = V[ 0 ] * K[ 0 ];
		for (size_t i = 1; i < Dim; ++i) {
            acc += V[ i ] * K[ i ];
		}
		return acc;
    }

	bool operator==( const dim_Type& b ) const {
		for (size_t i = 0; i < Dim; ++i) {
			if (V[ i ] != b.V[ i ]) { return false; }
		}
		return true;
    }

private:
    Type  V[ Dim ];
};


//implementation of [ uni_hash ]
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::uni_hash	(){
	TableSize=DefTableSize;
	PoolSize = PoolSectionSize;
	table=NULL;
    reset();
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::~uni_hash	(){
    reset();
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline Class* uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::get(KeyClass K,int SubIndex,bool AddIfNotExists){
    DWORD hash=(DWORD)K;
    hash%=TableSize;
	if(table){
		temp_s* el=table[hash];
		while(el){
			if(el->key==K){
				if(SubIndex>0)SubIndex--;
				else return &el->element;			
			}
			el=el->next;
		}
	}
	if(AddIfNotExists){
		_check_table();
		return add(K,DefValue);
	}
    return NULL;
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline int uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::get_i(KeyClass K,int SubIndex,bool AddIfNotExists){
    DWORD hash=K;
    hash%=TableSize;
	if(table){
		temp_s* el=table[hash];
		while(el){
			if(el->key==K){
				if(SubIndex>0)SubIndex--;
				else return el->index;
			}
			el=el->next;
		}
	}
	if(AddIfNotExists){		
		_check_table();
		return add_i(K,DefValue);
	}
    return -1;
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline Class* uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::get_last(KeyClass K,bool AddIfNotExists){
	DWORD hash=K;
	hash%=TableSize;
	Class* C=NULL;
	if(table){
		temp_s* el=table[hash];
		while(el){
			if(el->key==K){
				C=&el->element;
			}
			el=el->next;
		}
	}
	if(C==NULL && AddIfNotExists){		
		_check_table();
		return add(K,DefValue);
	}
	return C;
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline int uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::get_i_last(KeyClass K,bool AddIfNotExists){
	DWORD hash=K;
	hash%=TableSize;
	int idx=-1;
	if(table){
		temp_s* el=table[hash];
		while(el){
			if(el->key==K){
				idx=el->index;			
			}
			el=el->next;
		}
	}
	if(idx==-1 && AddIfNotExists){		
		_check_table();
		return add_i(K,DefValue);
	}
	return idx;
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline	int uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::size() const {
    return (pool.Count()*PoolSectionSize)-freeVals.Count();
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline int uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::size(KeyClass K) const {
    DWORD hash=K;
    hash%=TableSize;
	int n=0;
	if(table){
		temp_s* el=table[hash];
		if(el){
			do{
				if(el->key==K)n++;
				el=el->next;
			}while(el);    
		}
	}
    return n;
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline Class* uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::add(KeyClass K, const Class& C){
    DWORD hash=(DWORD)K;
    hash%=TableSize;
	temp_s* ptr=_get_temp_s();
	_check_table();
    temp_s* el=table[hash];	   
#ifdef DEBUG_UNI_DEPTH
	_chk_depth(el);
#endif
    ptr->element=C;
    ptr->key=K;
    ptr->next=NULL;
    el=table[hash];    
    if(el){		
        assert(el!=el->next);
        while(el->next){
            assert(el!=el->next);
            el=el->next;
        }
        el->next=ptr;
    }else{
        table[hash]=ptr;
    } 
    return &ptr->element;
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline Class* uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::add_quick(KeyClass K, const Class& C){
	temp_s* ptr=_get_temp_s();
	// @todo optimize  Is really needed _check_table()?
	_check_table();
    ptr->element=C;
    ptr->key=K;
    const DWORD hash=DWORD(K)%TableSize;
#ifdef DEBUG_UNI_DEPTH
	_chk_depth(table[hash]);
#endif
	ptr->next=table[hash];
	table[hash]=ptr;
    return &ptr->element;
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline int uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::add_i(KeyClass K, const Class& C){
    DWORD hash=K;
    hash%=TableSize;
	temp_s* ptr=_get_temp_s();
	_check_table();
    temp_s* el=table[hash];	    
    ptr->element=C;
    ptr->key=K;
    ptr->next=NULL;
    el=table[hash];
#ifdef DEBUG_UNI_DEPTH
	_chk_depth(el);
#endif
    if(el){		
        while(el->next)el=el->next;
        el->next=ptr;
    }else{
        table[hash]=ptr;
    } 
    return ptr->index;
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline Class* uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::add_uniq(KeyClass K, const Class& C){
    DWORD hash=K;
    hash%=TableSize;
	_check_table();
    temp_s* el=table[hash];
#ifdef DEBUG_UNI_DEPTH
	_chk_depth(el);
#endif
    while(el){
        if(el->key==K && el->element==C){
            el->key=K;
            el->element=C;
            return &el->element;
        }
        el=el->next;
    }
	temp_s* ptr=_get_temp_s();
    el=table[hash];	    
    ptr->element=C;
    ptr->key=K;
    ptr->next=NULL;
    el=table[hash];
    if(el){		
        while(el->next)el=el->next;
        el->next=ptr;
    }else{
        table[hash]=ptr;
    } 
    return &ptr->element;
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline int uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::add_uniq_i(KeyClass K, const Class& C){
    DWORD hash=K;
    hash%=TableSize;
	_check_table();
    temp_s* el=table[hash];
#ifdef DEBUG_UNI_DEPTH
	_chk_depth(el);
#endif
    while(el){
        if(el->key==K && el->element==C){
            el->key=K;
            el->element=C;
            return el->index;
        }
        el=el->next;
    }
    el=table[hash];	
    temp_s* ptr=_get_temp_s();
    ptr->element=C;
    ptr->key=K;
    ptr->next=NULL;
    el=table[hash];
    if(el){		
        while(el->next)el=el->next;
        el->next=ptr;
    }else{
        table[hash]=ptr;
    } 
    return ptr->index;
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline Class* uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::replace(KeyClass K, const Class& C,int SubIndex){
    Class* CL=get(K,SubIndex);
    if(CL)*CL=C;
    return CL;
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline int uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::replace_i(KeyClass K, const Class& C,int SubIndex){
    int idx=get_i(K,SubIndex);
    if(idx!=-1)*(elem(idx))=C;
    return idx;
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline Class* uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::add_once(KeyClass K, const Class& C){
    Class* CL=get(K);
    if(CL){
        *CL=C;
        return CL;
    }else return add(K,C);
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline int uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::add_once_i(KeyClass K, const Class& C){
    int idx=get_i(K);
    if(idx!=-1){
        *(elem(idx))=C;
        return idx;
    }else return add_i(K,C);
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline bool uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::del(KeyClass K,int SubIndex){
    DWORD hash=(DWORD)K;
    hash%=TableSize;
	_check_table();
    temp_s* el=table[hash];
    if(!el)return false;
    temp_s* prev=NULL;
    bool _del=false;
    do{
        bool donext=true;
        if(el->key==K){
            if(SubIndex>0)SubIndex--;
            else{
                _del=true;
                if(prev)prev->next=el->next;
                else{
                    table[hash]=el->next;
                }
                el->index=-1-el->index;
                freeVals.Add(el);
                if(SubIndex==0)return true;
                el=prev;
                if(!el){
                    el=table[hash];
                    donext=false;
                }
            }			
        }        
        if(donext){
            prev=el;
            if(el)el=el->next;
        }
    }while(el);
    return _del;
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline bool uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::del_elm(KeyClass K, const Class& C){
    DWORD hash=K;
    hash%=TableSize;
	_check_table();
    temp_s* el=table[hash];
    if(!el)return false;
    temp_s* prev=NULL;
    bool _del=false;
    do{
        if(el->key==K && C==el->element){            
            _del=true;
            if(prev)prev->next=el->next;
            else table[hash]=el->next;
            el->index=-1-el->index;
            freeVals.Add(el);
            return true;
        }
        prev=el;
        el=el->next;
    }while(el);
    return _del;    
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline Class* uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::operator[](KeyClass K){
    return get(K,0);
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline void uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::reset(){
    for(int i=0;i<pool.Count();i++)delete[]pool[i];
    pool.Clear();
    freeVals.Clear();
	if(table){
		delete[]table;
	}
	table=NULL;    
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline void uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::fast_reset(){	
	freeVals.Clear();
	int psz=pool.Count();
	for(int i=psz-1;i>=0;i--){
		temp_s* p=pool[i]+PoolSectionSize-1;
		for(int j=0;j<PoolSectionSize;j++,p--){
			if(p->index>=0)p->index=-1-p->index;                    
			freeVals.Add(p);
		}
	}	
	if(table)memset(table,0,TableSize*sizeof(void*));
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline void uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::optimal_reset(){	
	if(pool.Count()>5000/PoolSectionSize){
		reset();
		return;
	}
	if(size()>TableSize/2){
		fast_reset();
		return;
	}
	freeVals.Clear();
	int psz=pool.Count();
	for(int i=psz-1;i>=0;i--){
		temp_s* p=pool[i]+PoolSectionSize-1;
		for(int j=0;j<PoolSectionSize;j++,p--){
			if(p->index>=0){
				table[DWORD(p->key)%TableSize]=NULL;
				p->index=-1-p->index;				
			}
			freeVals.Add(p);
		}
	}		
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline void uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::start_scan(KeyClass K,hash_context& ct) const {
    ct.ScanAll=false;
    DWORD hash=K;
    hash%=TableSize;
	temp_s* el=NULL;
	if(table){
		el=table[hash];	
		while(el && !(el->key==K))el=el->next;
	}
	ct.pptr = ct.ptr=(void*)el;
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline void uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::start_scan(hash_context& ct) const {
    ct.ScanAll=true;
    ct.TblPos=0;
	if(table){
		ct.ptr=(void*)table[0];
		ct.pptr = NULL;
	}else ct.ptr=NULL;
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline Class* uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::next(hash_context& ct) const {	
    if(ct.ScanAll){
		do{
			int pid=ct.TblPos/PoolSectionSize;
			int pin=ct.TblPos%PoolSectionSize;
			ct.TblPos++;
			if(pid<pool.Count()){
				temp_s* v=&pool[pid][pin];
				if (v->index >= 0){
					ct.pptr = v;
					return &v->element;
				}
			}else return NULL;
		}while(true);        
    }else{
        temp_s* ts=(temp_s*)ct.ptr;
        if(ts){
            temp_s* el=ts;
            if(el)el=el->next;
            while(el && !(el->key==ts->key))el=el->next;
            ct.ptr=el;
			ct.pptr = ts;
            return &ts->element;
        }
        return NULL;
    }
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline Class* uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::next_ke(hash_context& ct,KeyClass** _k) const {	
	if(ct.ScanAll){
		do{
			int pid=ct.TblPos/PoolSectionSize;
			int pin=ct.TblPos%PoolSectionSize;
			ct.TblPos++;
			if(pid<pool.Count()){
				temp_s* v=&pool[pid][pin];
				if(v->index>=0){
					if(_k)*_k=&v->key;
					ct.pptr = v;
					return &v->element; 
				}
			}else return NULL;
		}while(true);        
	}else{
		temp_s* ts=(temp_s*)ct.ptr;
		if(ts){
			temp_s* el=ts;
			if(el)el=el->next;
			while(el && !(el->key==ts->key))el=el->next;
			ct.ptr=el;
			if(_k)*_k=&ts->key;
			ct.pptr = ts;
			return &ts->element;
		}
		return NULL;
	}
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline KeyClass* uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::next_key(hash_context& ct) const {
    if(ct.ScanAll){
		do{
			int pid=ct.TblPos/PoolSectionSize;
			int pin=ct.TblPos%PoolSectionSize;
			ct.TblPos++;
			if(pid<pool.Count()){
				temp_s* v=&pool[pid][pin];
				if (v->index >= 0){
					ct.pptr = v;
					return &v->key;
				}
			}else return NULL;
		}while(true);
    }else{
        temp_s* ts=(temp_s*)ct.ptr;
        if(ts){
            temp_s* el=ts;
            if(el)el=el->next;
            while(el && !(el->key==ts->key))el=el->next;
            ct.ptr=el;
			ct.pptr = ts;
            return &ts->key;
        }
        return NULL;
    }
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline int uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::next_i(hash_context& ct) const {
    if(ct.ScanAll){
		do{
			int pid=ct.TblPos/PoolSectionSize;
			int pin=ct.TblPos%PoolSectionSize;
			ct.TblPos++;
			if(pid<pool.Count()){
				temp_s* v=&pool[pid][pin];
				if (v->index >= 0){
					ct.pptr = v;
					return v->index;
				}
			}else return -1;
		}while(true);
    }else{
        temp_s* ts=(temp_s*)ct.ptr;
        if(ts){
            temp_s* el=ts;
            while(el && !(el->key==ts->key))el=el->next;
            if(el)ct.ptr=(void*)el->next;
            else ct.ptr=NULL;
			ct.pptr = ts;
            return ts->index;
        }
        return -1;
    }
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline DWORD uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::get_free_idx(){
    temp_s* e=_get_temp_s();
    DWORD id=e->index;
    e->index=-1-e->index;
    freeVals.Add(e);    
    return id;
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline Class* uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::elem(int idx) const {
    temp_s* el=pool[idx/PoolSectionSize]+(idx%PoolSectionSize);
    if(el && el->index>=0)return &el->element;
    else return NULL;
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline bool uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::get_direct(int idx,Class** pc,KeyClass** pk){
	temp_s* el=pool[idx/PoolSectionSize]+(idx%PoolSectionSize);
	if(el && el->index>=0){
		if(pc)*pc=&el->element;
		if(pk)*pk=&el->key;
		return true;
	}else return false;
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline int uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::pool_size(){
	return PoolSectionSize*pool.Count();
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline KeyClass* uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::key(int idx) const {
    temp_s* el=pool[idx/PoolSectionSize]+(idx%PoolSectionSize);
    if(el->index>=0)return &el->key;
    else return NULL;
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline void uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::del_all(){
    int psz=pool.Count();
	_check_table();
    for(int i=0;i<psz;i++){
        temp_s* p=pool[i];
        for(int j=0;j<PoolSectionSize;j++,p++){
            if(p->index>=0){
                DWORD k=DWORD(p->key)%TableSize;
                temp_s* tps=table[k];
                while(tps){
                    tps->index=-1-tps->index;                    
                    tps=tps->next;
                }
                table[k]=0;
            }
        }
    }
    freeVals.Clear();
    for(int i=psz-1;i>=0;i--){
        temp_s* p=pool[i]+PoolSectionSize-1;
        for(int j=0;j<PoolSectionSize;j++,p--)
            freeVals.Add(p);
    }
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline int uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::simple_serialize(BYTE** buf){
	_check_table();
	int n=0;
	for(int i=0;i<TableSize;i++){
		temp_s* e=table[i];
		while(e){
			n++;
			e=e->next;
		}
	}	
	int sz=n*(sizeof(KeyClass)+sizeof(Class))+4;
	*buf=new BYTE[sz];
	int pos=4;
	memcpy(*buf,&n,4);
	int tbpos=0;
	for(int i=0;i<TableSize;i++){
		temp_s* e=table[i];
		while(e){
			memcpy((*buf)+pos,&e->key,sizeof(KeyClass));
			pos+=sizeof(KeyClass);
			memcpy((*buf)+pos,&e->element,sizeof(Class));
			pos+=sizeof(Class);
			e=e->next;
		}
	}
	return pos;
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline int uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::simple_unserialize(BYTE* buf,int ElmSizeLimit){
	int n=0;
	int pos=4;
    memcpy(&n,buf,4);
	reset();
	int sz=ElmSizeLimit?ElmSizeLimit:sizeof(Class);
	for(int i=0;i<n;i++){
		KeyClass K;
		Class C;
		memcpy(&K,buf+pos,sizeof(KeyClass));
		pos+=sizeof(KeyClass);		
		memcpy(&C,buf+pos,sz);
		pos+=sz;
        add(K,C);
	}
	return n*(sizeof(KeyClass)+sz)+4;
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline void uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::reset_table_size(int sz){
	if(sz==0)sz=size()+7;
	if(table){
		comms::cList<temp_s*> list;
        list.SetCapacity( size() );
		for(int i=0;i<TableSize;i++){
			temp_s* t=table[i];
			while(t){
				list.Add(t);
				t=t->next;
			}
		}
		delete[]table;
		table=NULL;
		TableSize=sz;
		_check_table();
		for(int i=list.Count()-1;i>=0;i--){
			int p=DWORD(list[i]->key)%TableSize;
			temp_s* t=list[i];
			t->next=table[p];
			table[p]=t;
		}
	}else{
		TableSize=sz;
	}
}
template <class Class,class KeyClass,int DefTableSize,int PoolSectionSize>
inline void uni_hash<Class,KeyClass,DefTableSize,PoolSectionSize>::refine_table(){
	if(size()>TableSize*2){
		reset_table_size();
	}
}
template <class Class, class KeyClass, int DefTableSize, int PoolSectionSize>
inline bool uni_hash<Class, KeyClass, DefTableSize, PoolSectionSize>::QuickAddOnceToList(comms::cList<KeyClass>& List, const KeyClass& E){
	if (!get(E)){
		add_quick(E, E);
		List.Add(E);
		refine_table();
		return true;
	}
	return false;
}

template <class Class, class KeyClass, int DefTableSize, int PoolSectionSize>
inline void uni_hash<Class, KeyClass, DefTableSize, PoolSectionSize>::InitFromList(comms::cList<KeyClass>& List){
	reset();
	reset_table_size(List.Count() + 4);
	for (int i = 0; i < List.Count(); i++){
		add_quick(List[i], List[i]);
	}
}


template< class K, class E >
std::ostream& operator<<( std::ostream& out,  const uni_hash< K, E >& h );
