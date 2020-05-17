#pragma once
class UnlimitedBitset{
	comms::cList<DWORD> Data;
public:
    UnlimitedBitset() {}
	~UnlimitedBitset();
	void operator=( const UnlimitedBitset& );
	UnlimitedBitset(const UnlimitedBitset& src);
	void set(int pos,bool value);
	bool get(int pos) const;
	void clear();
	void zero();
	void Store(BinStream& BS);
	void Restore(BinStream& BS);
	bool IsEmpty();
	void copyto(UnlimitedBitset& bs);
	bool operator==( const UnlimitedBitset& ) const;
	bool operator!=( const UnlimitedBitset& ) const;
	bool operator [] (int pos) const{
		return get(pos);
	}
	static const UnlimitedBitset ZERO;
};
class FastClearUnlimitedBitset : public UnlimitedBitset {
	comms::cList<int> used;
public:
	void set(int pos, bool value);
	void clear();
};
class UnlimitedBytes {
	comms::cList<BYTE> Data;
public:
	UnlimitedBytes() {}
	~UnlimitedBytes();
	void operator=(const UnlimitedBytes&);
	UnlimitedBytes(const UnlimitedBytes& src);
	void set(int pos, BYTE value);
	BYTE get(int pos) const;
	void clear();
	void zero();
	void Store(BinStream& BS);
	void Restore(BinStream& BS);
	bool IsEmpty();
	void copyto(UnlimitedBytes& bs);
	bool operator==(const UnlimitedBytes&) const;
	bool operator!=(const UnlimitedBytes&) const;
	BYTE operator [] (int pos) const {
		return get(pos);
	}
};


class UnlimitedBitset2{
	comms::cList<DWORD> Data;
	comms::cList<DWORD> Data2;
public:
	~UnlimitedBitset2();
	void setmax(int pos);
	void set(int pos,bool value);
	bool get(int pos);
	void clear();
	void fastclear();
};

inline UnlimitedBitset::~UnlimitedBitset(){
    clear();
}
inline void UnlimitedBitset::operator=( const UnlimitedBitset& b ) {
	Data = b.Data;
}
inline UnlimitedBitset::UnlimitedBitset(const UnlimitedBitset& src){
	Data = src.Data;
}
inline void UnlimitedBitset::set(int pos,bool value){
	if(pos<0)return;
	assert(pos < 10000000);
	int nr=1+pos/32;
	if(Data.Count()<nr){
		DWORD v=0;
		Data.Add(v,nr-Data.Count());
	}
	DWORD& v=Data.GetAt(nr-1);
	DWORD ms=1<<(pos&31);
	if(value){
        v|=ms;        
	}else{
        v&=~ms;
	}
}
inline bool UnlimitedBitset::get(int pos) const {
	if(pos<0)return false;
	int nr=pos/32;
	if(nr<Data.Count()){
        return !!(Data[nr]&(1<<(pos&31)));		
	}
	return false;
}
inline void UnlimitedBitset::copyto(UnlimitedBitset& bs){
    bs.Data.Copy( Data );
}
inline void UnlimitedBitset::zero(){
	memset(Data.ToPtr(),0,Data.Count()*4);
}
inline bool UnlimitedBitset::IsEmpty(){
	return Data.Count()==0;
}
inline void UnlimitedBitset::clear(){
	Data.Clear();
};
inline void UnlimitedBitset::Store(BinStream& BS){
	BS.WriteDWORD(Data.Count());
	BS.Write(Data.ToPtr(),Data.Count()*4);
}
inline void UnlimitedBitset::Restore(BinStream& BS){
	int N=BS.ReadDWORD();
	Data.Clear();
	Data.Add(0,N);
	BS.Read(Data.ToPtr(),N*4);
}
inline bool UnlimitedBitset::operator==( const UnlimitedBitset& b ) const {
	return (Data == b.Data);
}
inline bool UnlimitedBitset::operator!=( const UnlimitedBitset& b ) const {
	return (Data != b.Data);
}

inline void FastClearUnlimitedBitset::set(int pos, bool value) {
	if(value){
		if (!get(pos)) {
			used.Add(pos);
			UnlimitedBitset::set(pos, true);
		}
	}else {
		UnlimitedBitset::set(pos, false);
	}
}

inline void FastClearUnlimitedBitset::clear() {
	for(int i=0;i<used.Count();i++) {
		set(used[i], false);
	}
	used.Clear();
}


inline UnlimitedBytes::~UnlimitedBytes() {
	clear();
}
inline void UnlimitedBytes::operator=(const UnlimitedBytes& b) {
	Data = b.Data;
}
inline UnlimitedBytes::UnlimitedBytes(const UnlimitedBytes& src) {
	Data = src.Data;
}
inline void UnlimitedBytes::set(int pos, BYTE value) {
	if (pos < 0)return;
	int nr = pos + 1;
	if (Data.Count() < nr) {
		BYTE v = 0;
		Data.Add(v, nr - Data.Count());
	}
	Data[pos] = value;
}
inline BYTE UnlimitedBytes::get(int pos) const {
	if (pos < 0)return false;
	if (pos < Data.Count()) {
		return Data[pos];
	}
	return 0;
}
inline void UnlimitedBytes::copyto(UnlimitedBytes& bs) {
	bs.Data.Copy(Data);
}
inline void UnlimitedBytes::zero() {
	memset(Data.ToPtr(), 0, Data.Count() * 4);
}
inline bool UnlimitedBytes::IsEmpty() {
	return Data.Count() == 0;
}
inline void UnlimitedBytes::clear() {
	Data.Clear();
};
inline void UnlimitedBytes::Store(BinStream& BS) {
	BS.WriteDWORD(Data.Count());
	BS.Write(Data.ToPtr(), Data.Count());
}
inline void UnlimitedBytes::Restore(BinStream& BS) {
	int N = BS.ReadDWORD();
	Data.Clear();
	Data.Add(0, N);
	BS.Read(Data.ToPtr(), N);
}
inline bool UnlimitedBytes::operator==(const UnlimitedBytes& b) const {
	return (Data == b.Data);
}
inline bool UnlimitedBytes::operator!=(const UnlimitedBytes& b) const {
	return (Data != b.Data);
}



inline UnlimitedBitset2::~UnlimitedBitset2(){
	clear();
}
inline void UnlimitedBitset2::set(int pos,bool value){
	assert(value);
	if(pos<0)return;
	int nr=1+pos/32;
	if(Data.Count()<nr){
		//assert(0);
		DWORD v=0;
		Data.Add(v,nr-Data.Count());
	}
	if(value){
		int nr2=pos/32/32+1;
		if(Data2.Count()<nr2){
			//assert(0);
			Data2.Add(0,nr2-Data2.Count());			
		}
		BYTE* pp=(BYTE*)Data2.ToPtr();
		int p3=pos/32/8;
		pp[p3]=255;		
	}
	DWORD& v=Data.GetAt(nr-1);
	DWORD ms=1<<(pos&31);
	if(value){
		v|=ms;        
	}else{
		v&=~ms;
	}
}
inline bool UnlimitedBitset2::get(int pos){
	if(pos<0)return false;
	int nr=pos/32;
	if(nr<Data.Count()){
		return !!(Data[nr]&(1<<(pos&31)));		
	}
	return false;
}
inline void UnlimitedBitset2::clear(){
	Data.Clear();
	Data2.Clear();
}
inline void UnlimitedBitset2::setmax(int pos){
	if(pos<0)return;
	int nr=1+pos/32;
	if(Data.Count()<nr){
		DWORD v=0;
		Data.Add(v,nr-Data.Count());
	}
	int nr2=pos/32/32+1;
	if(Data2.Count()<nr2){
		Data2.Add(0,nr2-Data2.Count());			
	}
}
inline void UnlimitedBitset2::fastclear(){
	int n2=Data2.Count();
	int n=Data.Count();
	int maxn=(n/8)*8;
	DWORD* dptr=Data.ToPtr();
	DWORD* dptr2=Data2.ToPtr();
	BYTE* bptr2=(BYTE*)dptr2;
	for(int i=0;i<n2;i++)if(dptr2[i]){
		DWORD v=dptr2[i];
		BYTE* p=(BYTE*)&v;
		for(int j=0;j<4;j++)if(p[j]){
			BYTE pp=p[j];
			int ps=i*32+j*8;
			if(ps<maxn){
				memset(dptr+ps,0,32);
			}else{
				for(int k=0;k<8;k++){
					if(ps<n){
						dptr[ps]=0;
					}
					ps++;
				}
			}
		}
		dptr2[i]=0;
	}
}
