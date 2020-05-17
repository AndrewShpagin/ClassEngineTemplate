#pragma once

// MakeMagic
inline DWORD MakeMagic(const char* Magic) {
	int l = comms::cStr::Length(Magic);
	int i;
	DWORD c, M = 0;
	for (i = l - 1; i >= 0; i--) {
		c = Magic[i];
		M += c << (8 * (3 - i));
	}
	return M;
}

class  BinStream {
public:
	DWORD StreamCustomID;
	BinStream() {
		StreamCustomID = 0;
	}
	virtual void  Write(const void* data, cPtrDiff size) = 0;
	virtual cPtrDiff Read(void* data, cPtrDiff size) = 0;
	virtual void  WriteToFile(const char* Name) = 0;
	virtual void  ReadFromFile(const char* Name) = 0;
	virtual cPtrDiff Size() = 0;
	virtual void  SetReadPos(cPtrDiff pos) = 0;
	virtual void  SetWritePos(cPtrDiff pos) = 0;
	virtual cPtrDiff GetReadPos() = 0;
	virtual cPtrDiff GetWritePos() = 0;
	virtual cPtrDiff Skip(cPtrDiff size) {
		//assert(0);
		return size;
	}
	virtual BYTE* GetData() = 0;
	virtual void  Clear() = 0;
	
	void  WriteBYTE(BYTE c);
	void  WriteWORD(WORD w);
	void  WriteDWORD(DWORD D);
	void  WriteString(const char* s);
	BYTE  ReadBYTE();
	WORD  ReadWORD();
	DWORD ReadDWORD();
	void  WritePackedSize(int size);
	int   ReadPackedSize();
	void  ReadString(comms::cStr& s, const char* terminators = "\n\r");

	static int WriteError;//0 - success, 1 - not enough disk space, 2 - unable to write
	static comms::cStr ErrantFileName;
};



class  BinStreamCounter :public BinStream {
public:
	BinStreamCounter() {
		sz = 0;
	}
	cPtrDiff sz;
	virtual void  Write(const void* data, cPtrDiff size) { sz += size; }
	virtual cPtrDiff Read(void* data, cPtrDiff size) { return size; };
	virtual void  WriteToFile(const char* Name) {};
	virtual void  ReadFromFile(const char* Name) {};
	virtual cPtrDiff Size() { return sz; };
	virtual void  SetReadPos(cPtrDiff pos) {};
	virtual void  SetWritePos(cPtrDiff pos) {};
	virtual cPtrDiff GetReadPos() { return 0; };
	virtual cPtrDiff GetWritePos() { return sz; };
	virtual BYTE* GetData() { return NULL; };
	virtual void  Clear() { sz = 0; };
	virtual cPtrDiff Skip(cPtrDiff size) {
		sz += size;
		return size;
	}
};

class  MemoryBinStream :public BinStream {
	BYTE* Data;
	cPtrDiff _Size;
	cPtrDiff _MaxSize;
	cPtrDiff _WritePos;
	cPtrDiff _ReadPos;
public:
	MemoryBinStream();
	~MemoryBinStream();
	void  CheckSize(cPtrDiff size);
	virtual void  Write(const void* data, cPtrDiff size);
	virtual cPtrDiff Read(void* data, cPtrDiff size);
	virtual void  WriteToFile(const char* Name);
	virtual void  ReadFromFile(const char* Name);
	virtual cPtrDiff Size();
	virtual void  SetReadPos(cPtrDiff pos);
	virtual void  SetWritePos(cPtrDiff pos);
	virtual cPtrDiff GetReadPos();
	virtual cPtrDiff GetWritePos();
	virtual BYTE* GetData();
	virtual cPtrDiff Skip(cPtrDiff size);
	virtual void  Clear();
	DWORD GetCheckSumm(int startof);
};