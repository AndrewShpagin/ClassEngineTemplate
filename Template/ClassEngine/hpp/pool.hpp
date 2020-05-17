
//#define NOPOOL
//#define STRONGCHECK
std::mutex pool_spm;
#define oneassert(x) if(!(x)){static bool w=true;if(w){assert(x);w=false;}}
std_OnePoolType::std_OnePoolType(){
}
std_OnePoolType::~std_OnePoolType()
{
	for (int i = 0; i < Pool.GetAmount(); i++) {
		if (Pool[i])delete[](Pool[i]);
	}
}

//-----------------------------------------------------------------------------
// std_OnePoolType
//-----------------------------------------------------------------------------
void std_OnePoolType::Free() {
	for(int i = 0; i < Pool.GetAmount(); i++) {
		oneassert(Pool[i] && "NULL pointer in pool!");
		if(Pool[i])delete[] Pool[i];
	}
	Pool.Clear();
	FreeList.Clear();
}

BYTE* std_OnePoolType::Allocate()
{
	std::scoped_lock L(pool_spm);
#ifdef NOPOOL
	return new BYTE[QuantSize];
#else //NOPOOL
	if(FreeList.GetAmount()==0){
        BYTE* tmp=new BYTE[SegmentSize*QuantSize];
		Pool.Add(tmp);
		for(int i=0;i<SegmentSize;i++){
			BYTE* P1=tmp+i*QuantSize;
#ifdef _DEBUG
			*(DWORD*)P1=MakeMagic("BAAD");
#endif
			FreeList.Add(P1);
		}
	}	
	BYTE* e=FreeList.pop_back();
	DWORD* A=(DWORD*)e;	
#ifdef _DEBUG
	assert(*A==MakeMagic("BAAD"));
#endif
	*A=MakeMagic("FOOD");
	return e;
#endif
}

//-----------------------------------------------------------------------------
// TotalPool::Free
//-----------------------------------------------------------------------------
void TotalPool::Free() {
	pool_08.Free();
	pool_16.Free();
	pool_32.Free();
	pool_64.Free();
	pool_128.Free();
}

void std_OnePoolType::Free(BYTE* Ptr)
{
	std::scoped_lock L(pool_spm);
#ifdef NOPOOL
	delete[](Ptr);
#else //NOPOOL
	if(Ptr){
#ifdef STRONGCHECK
		int p=int(Ptr);
		int psize=SegmentSize*QuantSize;
		bool haveit=false;
		for(int i=0;i<Pool.GetAmount();i++){
			int p0=int(Pool[i]);
			if(p>=p0 && p<p0+psize){
				haveit=true;
				break;
			}
		}
		if(!haveit){
			return;
		}
#endif //STRONGCHECK
		DWORD* A=(DWORD*)Ptr;
		assert(*A!=MakeMagic("BAAD"));
        *A=MakeMagic("BAAD");
		FreeList.Add(Ptr);
	}
#endif
}
int std_OnePoolType::GetMemoryUsed(){
    return Pool.GetAmount() * SegmentSize * QuantSize +
        (Pool.Capacity() + FreeList.Capacity()) * sizeof( BYTE* );
}
void std_OnePoolType::KillDirtyGarbage(){
	std::scoped_lock L(pool_spm);
	UnlimitedBitset used[2];
	UnlimitedBitset todel;
	DWORD Mag[3]={MakeMagic("BOOK"),MakeMagic("GLUK"),MakeMagic("BAAD")};
	DWORD M=Mag[2];
	for(int i=0;i<FreeList.GetAmount();i++){
		*((DWORD*)FreeList[i])=M;
	}
	for(int j=0;j<2;j++){
		DWORD M=Mag[j];
		for(int i=0;i<FreeList.GetAmount();i++){
			*((DWORD*)FreeList[i])=M;
		}
		for(int i=0;i<Pool.GetAmount();i++){
			bool u=used[j].get(i);
			BYTE* P=Pool[i];
			for(int k=0;k<SegmentSize;k++){
				if(*((DWORD*)P)!=M){
					if(!u){
						used[j].set(i,true);
						u=true;
					}
				}
				P+=QuantSize;
			}
			if(j==1 && used[0].get(i)==false && used[1].get(i)==false){
				P=Pool[i];
				for(int k=0;k<SegmentSize;k++){
					*((DWORD*)P)=0;
					P+=QuantSize;
				}
			}
		}
	}
	int p=0;
	for(int i=0;i<FreeList.GetAmount();i++){
		if(*((DWORD*)FreeList[i])!=0){
			FreeList[p++]=FreeList[i];
		}
	}
	M=Mag[2];
	for(int i=0;i<FreeList.GetAmount();i++){
		*((DWORD*)FreeList[i])=M;
	}
	int nd1=0;
	int nd2=0;
	if(p<FreeList.GetAmount()){
		nd1=FreeList.GetAmount()-p;
        FreeList.RemoveAt( p, FreeList.GetAmount() - p );
	}
	p=0;
	for(int i=0;i<Pool.GetAmount();i++){
		if(used[0].get(i) || used[1].get(i)){
			Pool[p++]=Pool[i];
		}else{
			delete[](Pool[i]);
		}
	}
	if(p<Pool.GetAmount()){
		nd2=(Pool.GetAmount()-p)*SegmentSize;
		Pool.RemoveAt(p,Pool.GetAmount()-p);
		Pool.SetCapacityMod< 16 >();
	}
	FreeList.SetCapacityMod< 16 >();
	float eff=100.0f;
	if(Pool.GetAmount())eff=(Pool.GetAmount()*SegmentSize-FreeList.GetAmount())*100.0f/Pool.GetAmount()/SegmentSize;
	//Log.Message("Pool efficiency=%.01f",eff);
	assert(nd1==nd2);
}
//this function should be called only once, after object constructing
void std_OnePoolType::SetQuantSize(cPtrDiff size){
	assert(size>=8);
    QuantSize=(int)size;
	//SegmentSize=4096/QuantSize;
	SegmentSize=256;//4096/QuantSize;
	for(int i=0;i<Pool.GetAmount();i++){
		delete[](Pool[i]);
	}
	Pool.Clear();
	FreeList.Clear();
}
void std_OnePoolType::SetQuantSize2(cPtrDiff size){
	if(Pool.GetAmount()==0 && FreeList.GetAmount()==0){
		assert(size>=8);
		QuantSize=(int)size;
		SegmentSize=256;//4096/QuantSize;
		for(int i=0;i<Pool.GetAmount();i++){
			delete[](Pool[i]);
		}
		Pool.Clear();
		FreeList.Clear();
	}
}
void TotalPool::Init(){
	if(!m_fIsInitialized) {
		m_fIsInitialized = true;
		pool_08.SetQuantSize(8);
		pool_16.SetQuantSize(16);
		pool_32.SetQuantSize(32);
		pool_64.SetQuantSize(64);
		pool_128.SetQuantSize(128);
	}
}
TotalPool::TotalPool(){
	m_fIsInitialized = false;
	Init();
}
std_OnePoolType* TotalPool::GetPoolBySize(int size){
#ifdef NOPOOL
	return NULL;
#endif //NOPOOL
	if(size<=8)return &pool_08;
	if(size<=16)return &pool_16;
	if(size<=32)return &pool_32;
	if(size<=64)return &pool_64;
	if(size<=128)return &pool_128;
	return NULL;
}
TotalPool::~TotalPool(){

}
BYTE* TotalPool::Allocate(int size)
{
	Init();
	if(size==0)return NULL;
	std_OnePoolType* pool=GetPoolBySize(size);
	if(pool)return pool->Allocate();
	else return new BYTE[size];
}

void  TotalPool::Free(BYTE* ptr, cPtrDiff size){
	std_OnePoolType* pool=GetPoolBySize((int)size);
	if(pool)pool->Free(ptr);
	else if(ptr)delete[](ptr);
}

BYTE* TotalPool::Realloc(BYTE* ptr, cPtrDiff size, cPtrDiff newsize){
	std_OnePoolType* old_pool=GetPoolBySize((int)size);
	std_OnePoolType* new_pool=GetPoolBySize((int)newsize);
	if(ptr&&old_pool&&old_pool==new_pool)return ptr;
	BYTE* nptr=Allocate((int)newsize);
	if(ptr&&nptr)memcpy(nptr,ptr,std::min(size,newsize));
    Free(ptr,size);
	return nptr;
}
set_of_int::set_of_int(){
	set=NULL;
	set_size=0;
}
set_of_int::~set_of_int(){
	g_SetOfIntPool.Free((BYTE*)set,set_size*4);
}
void set_of_int::add(int value){
	if(have(value))return;
	set=(int*)g_SetOfIntPool.Realloc((BYTE*)set,set_size*4,set_size*4+4);
	set[set_size]=value;
	set_size++;
}
void set_of_int::del(int value){
	for(int i=0;i<set_size;i++)if(set[i]==value){
		if(i<set_size-1){
			memcpy(set+i,set+i+1,(set_size-i-1)*4);
		}
		set=(int*)g_SetOfIntPool.Realloc((BYTE*)set,set_size*4,set_size*4-4);
		set_size--;
		return;
	}
}
void set_of_int::clear(){
	g_SetOfIntPool.Free((BYTE*)set,set_size*4);
	set=NULL;
	set_size=0;
}
bool set_of_int::have(int value) const {
	for(int i = 0; i < set_size; i++) if(set[i] == value) return true;
	return false;
}
void set_of_int::copyTo(set_of_int& dest){
	dest.clear();
	dest.set=(int*)g_SetOfIntPool.Allocate(set_size*4);
	memcpy(dest.set,set,set_size*4);
}

TotalPool* _POOL=NULL;

TotalPool& _getPOOL(){
	if(!_POOL)_POOL=new TotalPool;
	return *_POOL;
}

void TotalPool::Cleanup(){
	pool_08.KillDirtyGarbage();
	pool_16.KillDirtyGarbage();
	pool_32.KillDirtyGarbage();
	pool_64.KillDirtyGarbage();
	pool_128.KillDirtyGarbage();
}
void std_OnePoolType::Check(){
#ifdef _DEBUG
	for (int i = 0; i < FreeList.Count(); i++){
		BYTE* e = FreeList[i];
		DWORD* A = (DWORD*)e;
		assert(*A == MakeMagic("BAAD"));
	}
#endif
}
void TotalPool::Check(){
#ifdef _DEBUG
	pool_08.Check();
	pool_16.Check();
	pool_32.Check();
	pool_64.Check();
	pool_128.Check();
#endif
}


TotalPool g_SetOfIntPool;
