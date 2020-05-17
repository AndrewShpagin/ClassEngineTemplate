#pragma once

class  BinStream{
public:
	BinStream(){
		StreamCustomID = 0;
	}
	virtual void  Write(const void* data,size_t size)=0;
	virtual size_t Read(void* data, size_t size) = 0;
	virtual void  WriteToFile(const char* Name)=0;
	virtual void  ReadFromFile(const char* Name)=0;
	virtual size_t Size()=0;
	virtual void  SetReadPos(size_t pos)=0;
	virtual void  SetWritePos(size_t pos)=0;
	virtual size_t GetReadPos()=0;
	virtual size_t GetWritePos()=0;
	virtual size_t Skip(size_t size){
		//assert(0);
		return size;
	}
	virtual unsigned char* GetData()=0;
	virtual void  Clear()=0;
			void  Writeunsigned char(unsigned char c);
			void  WriteWORD(unsigned short w);
			void  WriteDWORD(unsigned int D);
			void  WriteString(const char* s);
			unsigned char  Readunsigned char();  
			unsigned short  ReadWORD();
			unsigned int ReadDWORD();
			void  WritePackedSize(int size);
			int   ReadPackedSize();
			void ReadString(comms::cStr& s, const char* terminators = "\n\r");
			unsigned int StreamCustomID;
};

inline void BinStream::WritePackedSize(int s) {
	if (s < 128) {
		Writeunsigned char(s);
	}
	else {
		unsigned int v = (unsigned int)s;
		unsigned int D = (v & 127) | 128 + ((v >> 7) << 8);
		WriteDWORD(D);
	}
}

inline int BinStream::ReadPackedSize() {
	unsigned int b = Readunsigned char();
	if (b >= 128) {
		unsigned char* pb = (unsigned char*)& b;
		Read(pb + 1, 3);
		b = (b & 127) + ((b >> 8) << 7);
	}
	return int(b);
}

class  BinStreamCounter:public BinStream{
public:
	BinStreamCounter(){
		sz=0;
	}
	int sz;
	virtual void  Write(const void* data, size_t size){ sz += size; }
	virtual size_t Read(void* data, size_t size){ return size; };
	virtual void  WriteToFile(const char* Name){};
	virtual void  ReadFromFile(const char* Name){};
	virtual size_t Size(){return sz;};
	virtual void  SetReadPos(size_t pos){};
	virtual void  SetWritePos(size_t pos){};
	virtual size_t GetReadPos(){return 0;};
	virtual size_t GetWritePos(){return sz;};
	virtual unsigned char* GetData(){return NULL;};
	virtual void  Clear(){sz=0;};		
	virtual size_t Skip(size_t size){
		sz+=size;
		return size;
	}
};