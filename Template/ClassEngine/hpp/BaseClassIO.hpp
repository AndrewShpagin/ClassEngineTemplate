#ifdef IMPLEMENT_CLASS_FACTORY
int BinStream::WriteError = 0;//0 - success, 1 - not enough disk space, 2 - unable to write
comms::cStr BinStream::ErrantFileName;
void  MemoryBinStream::CheckSize(cPtrDiff size) {
	if (size > _MaxSize) {
		if (size <= 128) {
			if (size <= 8)size = 8;
			else if (size <= 16)size = 16;
			else if (size <= 32)size = 32;
			else if (size <= 64)size = 64;
			else size = 128;
		}
		else size = size + _MaxSize / 2;
		Data = POOL.Realloc(Data, _MaxSize, size);
		_MaxSize = size;
	}
}
void  MemoryBinStream::Write(const void* data, cPtrDiff size) {
	CheckSize(_WritePos + size);
	memcpy(Data + _WritePos, data, size);
	_WritePos += size;
	_Size = std::max(_Size, _WritePos);
}
cPtrDiff  MemoryBinStream::Read(void* data, cPtrDiff size) {
	cPtrDiff rsize = _Size - _ReadPos;
	rsize = std::min(rsize, size);
	if (rsize > 0)memcpy(data, Data + _ReadPos, size);
	rsize = std::max(rsize, (cPtrDiff)0);
	_ReadPos += rsize;
	return rsize;
}
cPtrDiff MemoryBinStream::Skip(cPtrDiff size) {
	cPtrDiff rsize = _Size - _ReadPos;
	rsize = std::min(rsize, size);
	rsize = std::max(rsize, (cPtrDiff)0);
	_ReadPos += rsize;
	return rsize;
}
void  MemoryBinStream::WriteToFile(const char* Name) {
	ResFile F = RRewrite((char*)Name);
	if (F != INVALID_HANDLE_VALUE) {
		cPtrDiff sz = RBlockWrite(F, Data, _Size);
		if (sz != _Size) {
			BinStream::WriteError = 1;
			BinStream::ErrantFileName = Name;
		}
		RClose(F);
	}
	else {
		BinStream::WriteError = 2;
		BinStream::ErrantFileName = Name;
	}
}
void  MemoryBinStream::ReadFromFile(const char* Name) {
	Clear();
	ResFile F = RReset((char*)Name);
	if (F != INVALID_HANDLE_VALUE) {
		cPtrDiff sz = RFileSize(F);
		CheckSize(sz);
		RBlockRead(F, Data, sz);
		RClose(F);
		_Size = sz;
	}
}

MemoryBinStream::MemoryBinStream() {
	Data = NULL;
	_Size = 0;
	_MaxSize = 0;
	_WritePos = 0;
	_ReadPos = 0;
}

MemoryBinStream::~MemoryBinStream() {
	Clear();
}

cPtrDiff   MemoryBinStream::Size() {
	return _Size;
}

void  MemoryBinStream::SetReadPos(cPtrDiff pos) {
	_ReadPos = pos;//max(pos,0);
}

void  MemoryBinStream::SetWritePos(cPtrDiff pos) {
	_WritePos = pos;//max(pos,0);
}

cPtrDiff   MemoryBinStream::GetReadPos() {
	return _ReadPos;
}

cPtrDiff   MemoryBinStream::GetWritePos() {
	return _WritePos;
}

BYTE* MemoryBinStream::GetData() {
	return Data;
}

DWORD MemoryBinStream::GetCheckSumm(int startof) {
	DWORD s = 0;
	cPtrDiff n = (_Size - startof) / 4;
	for (int i = 0; i < n; i++) {
		s += ((DWORD*)(Data + startof))[i];
	}
	return s;
}
void  MemoryBinStream::Clear() {
	if (Data)POOL.Free(Data, _MaxSize);
	//if(Data)_ExFree(Data);
	Data = NULL;
	_Size = 0;
	_MaxSize = 0;
	_WritePos = 0;
	_ReadPos = 0;
}
void BinStream::ReadString(comms::cStr& s, const char* terminators) {
	if (Size() > GetReadPos()) {
		cPtrDiff L = Size() - GetReadPos();
		if (terminators == NULL) {
			s.Clear();
			s.Append(' ', (int)L);
			Read(s.ToNonConstCharPtr(), L);
		}
		else {
			for (int i = 0; i < L; i++) {
				char c = ReadBYTE();
				if (strchr(terminators, c)) {
					break;
				}
				s.Append(c);
			}
		}
	}
}


void  BinStream::WriteBYTE(BYTE c) {
	Write(&c, 1);
}

void  BinStream::WriteWORD(WORD w) {
	Write(&w, 2);
}

void  BinStream::WriteDWORD(DWORD D) {
	Write(&D, 4);
}

void BinStream::WriteString(const char* s) {
	cPtrDiff L = strlen(s);
	Write(s, L);
}

BYTE  BinStream::ReadBYTE() {
	BYTE b = 0;
	Read(&b, 1);
	return b;
}

WORD  BinStream::ReadWORD() {
	WORD w = 0;
	Read(&w, 2);
	return w;
}

DWORD BinStream::ReadDWORD() {
	DWORD D = 0;
	Read(&D, 4);
	return D;
}

void BinStream::WritePackedSize(int s) {
	if (s < 128) {
		WriteBYTE(s);
	}
	else {
		DWORD v = (DWORD)s;
		DWORD D = (v & 127) | 128 + ((v >> 7) << 8);
		WriteDWORD(D);
	}
}

int BinStream::ReadPackedSize() {
	DWORD b = ReadBYTE();
	if (b >= 128) {
		BYTE* pb = (BYTE*)&b;
		Read(pb + 1, 3);
		b = (b & 127) + ((b >> 8) << 7);
	}
	return int(b);
}

#endif
