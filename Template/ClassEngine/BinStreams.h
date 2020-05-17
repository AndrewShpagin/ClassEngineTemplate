#pragma once

#include "Resfile.h"
#include "BaseClassIO.h"

struct MT_Chunk{
	void Free();
	void* ptr;
	int Size;
	comms::cThread::ThreadHandle H;
	ResFile F;
	char* n1;
	char* n2;
	bool ZipIt;
	DWORD CustomID;
};
struct MT_ChunkData{
	comms::cThread::ThreadHandle TH;
	ResFile TH_ResFiles;
	DWORD StreamCustomID;
};
class MT_ChunksWriter{
public:
	static comms::cList<MT_ChunkData> MtData;//threads
	static tbb::spin_mutex MT;
	static comms::cList<MT_Chunk> Ptrs;
	static bool SkipMode;
    static int WrittenPercent;
	static char WrittenFile[512];
	static void AddToQueue(const void* ptr, int Size, ResFile F, const char* n1 = NULL, const char* n2 = NULL, bool zip = false, DWORD StreamID = 0);
	static void AddClose(ResFile F, const char* name1, const char* name2, bool zip = false, DWORD StreamID = 0);
	static void EndAll(DWORD OnlyCustom = 0);
	static void Thread(void*);
	static bool FileInQueue(const char* name);
};
class  FileWriteBinStream:public BinStream{	
    ResFile F;	
    cPtrDiff Pos;
public:
	FileWriteBinStream(const char* Name=NULL);
	~FileWriteBinStream();	
	bool Valid();
	virtual void  Write(const void* data,cPtrDiff size);
	virtual cPtrDiff Read(void* data,cPtrDiff size);
	virtual void  WriteToFile(const char* Name);
	virtual void  ReadFromFile(const char* Name);
	virtual cPtrDiff Size();
	virtual void  SetReadPos(cPtrDiff pos);
	virtual void  SetWritePos(cPtrDiff pos);
	virtual cPtrDiff GetReadPos();
	virtual cPtrDiff GetWritePos();
	virtual BYTE* GetData();
	virtual void  Clear();
};
class  FileReadBinStream:public BinStream{
	ResFile F;
	cPtrDiff Pos;	
    cPtrDiff fSize;
public:
	FileReadBinStream(const char* Name=NULL);
	~FileReadBinStream();	
	bool Valid();
	virtual void  Write(const void* data,cPtrDiff size);
	virtual cPtrDiff Read(void* data,cPtrDiff size);
	virtual cPtrDiff Skip(cPtrDiff size);
	virtual void  WriteToFile(const char* Name);
	virtual void  ReadFromFile(const char* Name);
	virtual cPtrDiff Size();
	virtual void  SetReadPos(cPtrDiff pos);
	virtual void  SetWritePos(cPtrDiff pos);
	virtual cPtrDiff GetReadPos();
	virtual cPtrDiff GetWritePos();
	virtual BYTE* GetData();
	virtual void  Clear();
};

class  FILE_ReadBinStream:public BinStream{
	ResFile F;
	cPtrDiff Pos;
	cPtrDiff fSize;

	BYTE* TempBuffer;
	cPtrDiff TempSize;
	cPtrDiff TempPos;
	cPtrDiff TempCurrSize;
public:
	FILE_ReadBinStream(const char* Name=NULL);
	~FILE_ReadBinStream();	
	bool Valid();
	virtual void  Write(const void* data,cPtrDiff size);
	virtual cPtrDiff Read(void* data,cPtrDiff size);
	virtual cPtrDiff Skip(cPtrDiff size);
	virtual void  WriteToFile(const char* Name);
	virtual void  ReadFromFile(const char* Name);
	virtual cPtrDiff Size();
	virtual void  SetReadPos(cPtrDiff pos);
	virtual void  SetWritePos(cPtrDiff pos);
	virtual cPtrDiff GetReadPos();
	virtual cPtrDiff GetWritePos();
	virtual BYTE* GetData();
	virtual void  Clear();
};

class  FILE_WriteBinStream :public BinStream {
	ResFile F;
	cPtrDiff Pos;
	bool Multithreaded;
	bool AllowZip;
	BYTE* TempBuffer;
	cPtrDiff TempSize;
	cPtrDiff TempCurrSize;
	cPtrDiff TempPos;
public:
	comms::cStr FileName;
	comms::cStr InitialName;
	comms::cStr RenameTo;

	void MoveStructure(FILE_WriteBinStream* Dest);
	static void EnsureThreadEnded();
	FILE_WriteBinStream(const char* Name = NULL, bool Multi = false, bool AutoZip = false);
	~FILE_WriteBinStream();
	bool Valid();
	virtual void  Write(const void* data, cPtrDiff size);
	virtual cPtrDiff Read(void* data, cPtrDiff size);
	virtual void  WriteToFile(const char* Name);
	void  WriteToFileImm(const char* Name);
	virtual void  ReadFromFile(const char* Name);
	virtual cPtrDiff Size();
	virtual void  SetReadPos(cPtrDiff pos);
	virtual void  SetWritePos(cPtrDiff pos);
	virtual cPtrDiff GetReadPos();
	virtual cPtrDiff GetWritePos();
	virtual BYTE* GetData();
	virtual void  Clear();
};