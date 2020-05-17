
#ifdef COMMS_WINDOWS

//Opening the resource file
ResFile RReset(LPCSTR lpFileName)
{
#ifdef USE_CIO
	comms::cStr s=comms::cIO::EnsureAbsolutePath(lpFileName);
	comms::cStr s1=s;
	comms::cIO::ReplaceReadPath(&s1);
	SetLastError(0);
	ResFile F1 = CreateFile(s1.ToCharPtr(), GENERIC_READ, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, 0, NULL);


	if (F1 != INVALID_HANDLE_VALUE) {
		return F1;
	}

	SetLastError(0);
	F1 = CreateFile(s.ToCharPtr(), GENERIC_READ, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, 0, NULL);
	return F1;
#else
	SetLastError(0);
	ResFile F1 = CreateFile(lpFileName, GENERIC_READ, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, 0, NULL);
	return F1;
#endif
}
ResFile RAppend(LPCSTR lpFileName)
{
#ifdef USE_CIO
	cStr s=comms::cIO::EnsureAbsolutePath(lpFileName);
	comms::cIO::ReplaceReadPath(&s);
	comms::cIO::CreatePath(s.ToCharPtr());
	SetLastError(0);
	ResFile R=CreateFile(s.ToCharPtr(),GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,
		OPEN_EXISTING,0,NULL);
	if(R!=INVALID_HANDLE_VALUE){
		RSeek(R,RFileSize(R));
	}
#else
	ResFile R = CreateFile(lpFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
		OPEN_EXISTING, 0, NULL);
	if (R != INVALID_HANDLE_VALUE) {
		RSeek(R, RFileSize(R));
	}
#endif
	return R;
}
//Rewriting file
ResFile RRewrite(LPCSTR lpFileName)
{
#ifdef USE_CIO
	cStr s=comms::cIO::EnsureAbsolutePath(lpFileName);
	comms::cIO::ReplaceReadPath(&s);
	comms::cIO::CreatePath(s.ToCharPtr());
	SetLastError(0);
	ResFile F = CreateFile(s.ToCharPtr(),GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,
		CREATE_ALWAYS,0,NULL);
#else
	SetLastError(0);
	ResFile F = CreateFile(lpFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
		CREATE_ALWAYS, 0, NULL);
#endif
	return F;
}
//Getting size of the resource file
cPtrDiff RFileSize(HANDLE hFile)
{
	SetLastError(0);
#ifdef COMMS_64
	LARGE_INTEGER L;
	GetFileSizeEx(hFile,&L);
	return L.QuadPart;
#else
	return GetFileSize(hFile,NULL);
#endif
}
// Setting file position 
cPtrDiff RSeek(ResFile hFile, cPtrDiff pos)
{
	SetLastError(0);
	return SetFilePointer(hFile,(LONG)pos,NULL,FILE_BEGIN);
}

cPtrDiff RSeekFromCurrent(ResFile hFile, cPtrDiff nBytes)
{
	SetLastError(0);
	return SetFilePointer(hFile,(LONG)nBytes,NULL,FILE_CURRENT);
}

//Reading the file
cPtrDiff RBlockRead(ResFile hFile,LPVOID lpBuffer, cPtrDiff BytesToRead)
{
	SetLastError(0);
	DWORD readBytes;
	ReadFile(hFile,lpBuffer,(LONG)BytesToRead,&readBytes,NULL);
	return readBytes;
}			
//Writing the file
cPtrDiff RBlockWrite(ResFile hFile,const void* lpBuffer, cPtrDiff BytesToWrite)
{
	SetLastError(0);
	DWORD writeBytes;
	WriteFile(hFile,lpBuffer,(LONG)BytesToWrite,&writeBytes,NULL);
	return writeBytes;
}
DWORD IOresult(void)
{
	return GetLastError();
}
void RClose(ResFile hFile)
{
	SetLastError(0);
	if(!CloseHandle(hFile))
		MessageBox(NULL,"Failed to close file!","Strange error",0);
}

#else // !COMMS_WINDOWS

//Opening the resource file
ResFile RReset(LPCSTR lpFileName)
{
	if(lpFileName){
		FILE* F=OpenFILE(lpFileName,"rb");
		if(F)return (ResFile)F;
		else return INVALID_HANDLE_VALUE;	
	}else return INVALID_HANDLE_VALUE;	
}
//Rewriting file
ResFile RRewrite(LPCSTR lpFileName)
{
	if(lpFileName){
		FILE* F=OpenFILE(lpFileName,"wb");
		if(F)return (ResFile)F;
		else return INVALID_HANDLE_VALUE;
	}else return INVALID_HANDLE_VALUE;
}
ResFile RAppend(LPCSTR lpFileName)
{
	if(lpFileName){
		FILE* F=OpenFILE(lpFileName,"ab");
		if(F)return (ResFile)F;
		else return INVALID_HANDLE_VALUE;
	}else return INVALID_HANDLE_VALUE;
}
//Getting size of the resource file
cPtrDiff RFileSize(HANDLE hFile) {
	if(hFile != INVALID_HANDLE_VALUE) {
		FILE *F = (FILE *)hFile;
		off_t Cur = ftello(F);
		fseeko(F, 0, SEEK_END);
		off_t End = ftello(F);
		fseeko(F, Cur, SEEK_SET);
		return (cPtrDiff)End;
	} else {
		return 0;
	}
}
// Setting file position 
cPtrDiff RSeek(ResFile hFile, cPtrDiff pos)
{
	if(hFile!=INVALID_HANDLE_VALUE){
		FILE* F=(FILE*)hFile;
		int cp=fseek(F,pos,SEEK_SET);		
		return cp;
	}else return 0;	
}

cPtrDiff RSeekFromCurrent(ResFile hFile, cPtrDiff nBytes)
{
	if(hFile!=INVALID_HANDLE_VALUE){
		FILE* F=(FILE*)hFile;
		int cp=fseek(F,nBytes,SEEK_CUR);		
		return cp;
	}else return 0;	
}

//Reading the file
cPtrDiff RBlockRead(ResFile hFile,LPVOID lpBuffer, cPtrDiff BytesToRead)
{
	if(hFile!=INVALID_HANDLE_VALUE){
		FILE* F=(FILE*)hFile;
		return fread(lpBuffer,1,BytesToRead,F);
	}else return 0;
}
//Writing the file
cPtrDiff RBlockWrite(ResFile hFile,const void* lpBuffer, cPtrDiff BytesToWrite)
{
	if(hFile!=INVALID_HANDLE_VALUE){
		FILE* F=(FILE*)hFile;
		return fwrite(lpBuffer,1,BytesToWrite,F);
	}else return 0;
}
DWORD IOresult(void)
{
	return 0;
}
void RClose(ResFile hFile)
{
	if(hFile!=INVALID_HANDLE_VALUE){
		FILE* F=(FILE*)hFile;
		fclose(F);
	}
}

#endif //COMMS_WINDOWS
