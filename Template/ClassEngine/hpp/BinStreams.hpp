
const char* GetTempFile(){
	static char cc[1024]="";
	if(cc[0]==0){
		char cct[64];
		sprintf(cct, "Temp/id%d/tempfile.temp", ThisExeUID());
		strcpy(cc,GetSafeUserFolder(cct));
	}
	return cc;
}
const char* GetTempFile2(int idx){
	static char cc[1024]="";
	char cc3[32];
	sprintf(cc3,"tempfile%d.temp",idx);
	strcpy(cc,GetSafeUserFolder(cc3));
	return cc;
}
cList<MT_ChunkData> MT_ChunksWriter::MtData;
tbb::spin_mutex MT_ChunksWriter::MT;
cList<MT_Chunk> MT_ChunksWriter::Ptrs;
bool MT_ChunksWriter::SkipMode=false;
int MT_ChunksWriter::WrittenPercent = 0;
char MT_ChunksWriter::WrittenFile[512]="";
void MT_Chunk::Free(){
	if(n1)delete[](n1);
	if(n2)delete[](n2);
	n1=n2=NULL;
}
bool MT_ChunksWriter::FileInQueue(const char* name){
	cStr n = name;
	n.RemoveFilePath();
	tbb::spin_mutex::scoped_lock lk(MT);
	if (!strcmp(WrittenFile,n.ToCharPtr()))return true;
	return false;
}
cList<MT_Chunk> MT_History;
void MT_ChunksWriter::Thread(void* p){
	//WrittenPercent = 0;
	ResFile F = ResFile(p);
	comms::cThread::ThreadHandle ThisHandle = 0;
	bool something = false;
	{
		tbb::spin_mutex::scoped_lock lock1(MT);
		for (int k = 0; k < MtData.Count(); k++){
			if (MtData[k].TH_ResFiles == F){
				ThisHandle = MtData[k].TH;
			}
		}
	}
	//Log.Message("Thread started: H=%d, F=%X", ThisHandle, F);
	//Log.Flush();
	cStr fname;
	//Log.Message("Thread started: H=%X, F=%X", ThisHandle, F);
	int LastActionTime = GetTickCount();
	do{
		if(Ptrs.GetAmount()){
			MT_Chunk C0;
			bool doit=false;
			tbb::spin_mutex::scoped_lock lock;
			lock.acquire(MT);
			for (int k = 0; k < Ptrs.Count(); k++){
				if (Ptrs[k].F == F){
					C0 = Ptrs[k];
					Ptrs.RemoveAt(k, 1);
					doit = true;
					fname = C0.n2;
					break;
				}
			}
			lock.release();
			if(doit){
				if(C0.ptr){
					//Log.Message("Writing chunk (%d) : H=%X, F=%X", C0.Size, ThisHandle, F);
					int sz=RBlockWrite(C0.F,C0.ptr,C0.Size);
					if(sz!=C0.Size){
						BinStream::WriteError=1;
						BinStream::ErrantFileName="";
					}
					_ExFree(C0.ptr);
				}else{
					if(C0.F!=INVALID_HANDLE_VALUE){
						RClose(C0.F);	
						//Log.Message("Close file: H=%X, F=%X", C0.F, ThisHandle);
					}
                    if ( C0.n1 && C0.n2 && strcmp( C0.n1, C0.n2 ) ){
						//Log.Message("Final saving (%s) : H=%X, F=%X", C0.n2, ThisHandle, F);
                        // rename a file and zipped it
                        // \see PolyMesh::LoadMesh() for unpack it.
                        cStr destFile = C0.n2;
                        comms::cIO::ReplaceReadPath( &destFile );
                        comms::cIO::SetFilePermissions( destFile );
                        comms::cIO::RemoveFile( destFile );
						bool renamedone = __rename(C0.n1, C0.n2);						
						if (C0.ZipIt){
							BinStream::WriteError = 0;
							if (renamedone) {
								ZipFileOnBackground(C0.n2, strstr(C0.n2, ".3b") ? "zip.3b" : NULL);
							}
							else {
								ZipFileOnBackground(C0.n1, strstr(C0.n2, ".3b") ? "zip.3b" : NULL, NULL, C0.n2);
							}
						}						
                    } // if C0...
					C0.Free();
					break;
				}
				//MT_History.Add(C0);												
			}
			LastActionTime = GetTickCount();
		}else{
			comms::cThread::SleepMs(10);
			if (__abs(int(GetTickCount()) - LastActionTime) > 10000){
				break;
			}
		}		
	}while(true);
    //WrittenPercent = 100;
	{
		tbb::spin_mutex::scoped_lock lock(MT);
		for (int k = 0; k < MtData.Count(); k++) {
			if (MtData[k].TH == ThisHandle && MtData[k].TH_ResFiles == F) {
				MtData.RemoveAt(k, 1);
			}
		}
	
		comms::cThread::AddDeadThread(ThisHandle);
	}
	//Log.Message("Thread ended: H=%d, F=%X", ThisHandle, F);
	//Log.Flush();
}
void MT_ChunksWriter::AddToQueue(const void* ptr, int Size, ResFile F, const char* n1, const char* n2, bool zip, DWORD StreamCustomID){
	void* p1=NULL;
	if(ptr){
		p1=(SkipMode||AppOptions::UseMulticoreForSaving==false)? NULL : _ExMalloc(Size);
		if(p1==NULL){
			//EndAll();
			int sz=RBlockWrite(F,ptr,Size);
			if(sz!=Size){
				BinStream::WriteError=1;
				BinStream::ErrantFileName=n2;
			}
			return;
		}
		memcpy(p1,ptr,Size);
	}else{
		if(SkipMode||AppOptions::UseMulticoreForSaving==false){
			//EndAll();
			if(F!=INVALID_HANDLE_VALUE){
				RClose(F);						
			}
			if(n1 && n2 && strcmp(n1,n2)){
				comms::cIO::SetFilePermissions(n2);
				comms::cIO::RemoveFile(n2);
				__rename(n1,n2);
			}
			return;
		}
	}
	MT_Chunk CH;
	CH.ptr=p1;
	CH.Size=Size;
	CH.F=F;
	CH.n1=CH.n2=NULL;
	CH.ZipIt = zip;
	CH.CustomID = StreamCustomID;
	if(n1){
		CH.n1=new char[strlen(n1)+1];
		strcpy(CH.n1,n1);
	}
	if(n2){
		CH.n2=new char[strlen(n2)+1];
		strcpy(CH.n2,n2);
	}
	tbb::spin_mutex::scoped_lock lock;
	lock.acquire(MT);
	int ne=Ptrs.GetAmount();
	bool found = false;
	comms::cThread::ThreadHandle H = 0;
	for (int i = 0; i < MtData.Count(); i++){
		if (MtData[i].TH_ResFiles == F){
			found = true;
			H = MtData[i].TH;
		}
	}
	if(!found){
		//create own thread for each file
		H = comms::cThread::CreateThread(&Thread, (void*)F);
		MT_ChunkData D;
		D.TH = H;
		D.TH_ResFiles = F;
		D.StreamCustomID = StreamCustomID;
		MtData.Add(D);
	}
	Ptrs.Add(CH);
	Ptrs.GetLast().H = H;
	lock.release();
}
void MT_ChunksWriter::AddClose(ResFile F, const char* name1, const char* name2, bool zip, DWORD StreamCustomID){
	assert(name1 && name2);
	AddToQueue(NULL, 0, F, name1, name2, zip, StreamCustomID);
}
void MT_ChunksWriter::EndAll(DWORD CustomID){
	comms::cThread::RemoveDeadThreads();
	int N = MtData.Count();
	for (int k = N - 1; k >= 0; k--){
		bool any = false;
		comms::cThread::ThreadHandle hh;
		{
			tbb::spin_mutex::scoped_lock lock(MT);
			if (k < MtData.Count() && (CustomID == 0 || MtData[k].StreamCustomID == CustomID)){
				hh = MtData[k].TH;
				any = true;
			}
		}
		if (any){
			comms::cThread::WaitAndDeleteThread(&hh);			
		}
	}
	tbb::spin_mutex::scoped_lock lock(MT);
	for (int k = N - 1; k >= 0; k--){
		if (CustomID == 0 || MtData[k].StreamCustomID == CustomID){
			MtData.RemoveAt(k, 1);
		}
	}
}


FileWriteBinStream::FileWriteBinStream(const char* Name){
	Pos=0;
    F=INVALID_HANDLE_VALUE;
	if(Name)F=RRewrite(Name);
	else F=RRewrite(GetTempFile());	
	if(F==INVALID_HANDLE_VALUE){
		BinStream::WriteError=2;
		BinStream::ErrantFileName=Name ? Name : GetTempFile();
	}
}
FileWriteBinStream::~FileWriteBinStream(){
	Clear();
}
bool FileWriteBinStream::Valid(){
	return F!=INVALID_HANDLE_VALUE;
}
void FileWriteBinStream::Write(const void* data,cPtrDiff size){	
	if(F!=INVALID_HANDLE_VALUE){
        int sz=RBlockWrite(F,data,size);
		if(sz!=size){
			BinStream::WriteError=1;
			BinStream::ErrantFileName="";
		}
	}
	Pos+=size;
}
cPtrDiff FileWriteBinStream::Read(void* data,cPtrDiff size){
	assert(1);
	return 0;
}
void FileWriteBinStream::WriteToFile(const char* Name){
	cStr From = comms::cIO::EnsureAbsolutePath(GetTempFile());
	cStr To = comms::cIO::EnsureAbsolutePath(Name);
	if(F){
		Clear();
		comms::cIO::SetFilePermissions(To);
		comms::cIO::RemoveFile(To);//Name);
//		rename("$$$.$$$",Name);	
		__rename(From.ToCharPtr(),To.ToCharPtr());
		F=INVALID_HANDLE_VALUE;
		Pos=0;
	}
}
void FileWriteBinStream::ReadFromFile(const char* Name){
	assert(1);
}
cPtrDiff FileWriteBinStream::Size(){
    return Pos;
}
void FileWriteBinStream::SetReadPos(cPtrDiff pos){
	assert(1);
}
void FileWriteBinStream::SetWritePos(cPtrDiff pos){
	assert(1);
}
cPtrDiff FileWriteBinStream::GetReadPos(){
	assert(1);
	return 0;
}
cPtrDiff FileWriteBinStream::GetWritePos(){
	return Pos;
}
BYTE* FileWriteBinStream::GetData(){
	assert(1);
	return NULL;
}
void FileWriteBinStream::Clear(){
	if(F!=INVALID_HANDLE_VALUE)RClose(F);	
    F=INVALID_HANDLE_VALUE;
	Pos=0;
}
FILE_WriteBinStream::FILE_WriteBinStream(const char* Name,bool Mult, bool DoZip){
	Multithreaded=Mult;
	AllowZip = DoZip;
	//if(Mult)MT_ChunksWriter::EndAll();
	Pos=0;
	F=INVALID_HANDLE_VALUE;
	bool SkipAlloc=false;
	if(Name){
		InitialName=Name;
		if(strcmp(Name,"none")){
			F=RRewrite(Name);
			if(F==INVALID_HANDLE_VALUE){
				WriteError=2;
				ErrantFileName=Name;
				/*cStr s=TextManager::GetText("Unable_to_write_file");
				s+="\n";
				s+=Name;
				ShowModalMessageBox(s.ToCharPtr()," ",Ok,0,0);*/
			}
		}else{
			SkipAlloc=true;
		}
	}else{
		F=RRewrite(GetTempFile());
		if(F==INVALID_HANDLE_VALUE){
			//WriteError=2;
			//ErrantFileName=GetTempFile();
		}
	}
	TempSize=65536*128;
	if(SkipAlloc)TempBuffer=NULL;
	else TempBuffer=new BYTE[TempSize];
	TempCurrSize=0;
	TempPos=0;
}
FILE_WriteBinStream::~FILE_WriteBinStream(){
	Clear();
}
bool FILE_WriteBinStream::Valid(){
	return F!=INVALID_HANDLE_VALUE;
}
void StartTimer(int i);
void EndTimer(const char* Msg,int i);
void FILE_WriteBinStream::Write(const void* data,cPtrDiff size){	
	if(F!=INVALID_HANDLE_VALUE){
		if(TempCurrSize+size>=TempSize){
			//RBlockWrite(F,TempBuffer,TempCurrSize);
			if(Multithreaded){
				MT_ChunksWriter::AddToQueue(TempBuffer, TempCurrSize, F, 0, 0, AllowZip);
			}else{
				int sz=RBlockWrite(F,TempBuffer,TempCurrSize);
				if(sz!=TempCurrSize){
					WriteError=1;
					ErrantFileName=FileName.ToCharPtr();
				}
			}
			TempCurrSize=0;		
		}
		if(size>TempSize){
			//RBlockWrite(F,data,size);
			if(Multithreaded){
				MT_ChunksWriter::AddToQueue(data, size, F, 0, 0, AllowZip);
			}else{
				int sz=RBlockWrite(F,data,size);
				if(sz!=size){
					WriteError=1;
					ErrantFileName=FileName.ToCharPtr();
				}
			}
			//EndTimer("SaveBuffer",6);
		}else{
			memcpy(TempBuffer+TempCurrSize,data,size);
			TempCurrSize+=size;
		}
	}
	Pos+=size;
}
cPtrDiff FILE_WriteBinStream::Read(void* data,cPtrDiff size){
	assert(1);
	return 0;
}
void FILE_WriteBinStream::MoveStructure(FILE_WriteBinStream* Dest){
	Dest->F=F;    
	Dest->Pos=Pos;
	Dest->TempBuffer=TempBuffer;
	Dest->TempSize=TempSize;
	Dest->TempCurrSize=TempCurrSize;
	Dest->TempPos=TempPos;
	F=INVALID_HANDLE_VALUE;
	Pos=0;
	TempBuffer=NULL;
	TempCurrSize=0;
	TempPos=0;
}
struct FileThreadParam{
	FILE_WriteBinStream* D;
	cStr DestName;
	~FileThreadParam(){
		delete(D);
	}
};
void FILE_WriteBinStream::EnsureThreadEnded(){
	//if(ThreadStarted){
	//	comms::cThread::WaitAndDeleteThread(&TH);
	//	ThreadStarted=false;
	//}
}
void FILE_WriteThread(void* param){
	FileThreadParam* PP=(FileThreadParam*)param;
	PP->D->WriteToFileImm(PP->DestName.ToCharPtr());
	delete(PP);
}
void FILE_WriteBinStream::WriteToFile(const char* Name){
	EnsureThreadEnded();
	cStr From = comms::cIO::EnsureAbsolutePath(GetTempFile());
	cStr To = comms::cIO::EnsureAbsolutePath(Name);
	if (Name && Name[0]){
		InitialName = From.ToCharPtr();
		RenameTo = To.ToCharPtr();
	}
	Clear();
	//MT_ChunksWriter::AddClose(F, From.ToCharPtr(), To.ToCharPtr());
}
void FILE_WriteBinStream::WriteToFileImm(const char* Name){
	F=RAppend(GetTempFile());
	cStr From = comms::cIO::EnsureAbsolutePath(GetTempFile());
	cStr To = comms::cIO::EnsureAbsolutePath(Name);
	if(F!=INVALID_HANDLE_VALUE){
		Clear();
		comms::cIO::SetFilePermissions(To);
		comms::cIO::RemoveFile(To);
		__rename(From.ToCharPtr(),To.ToCharPtr());
		F=INVALID_HANDLE_VALUE;
		Pos=0;
	}
}
void FILE_WriteBinStream::ReadFromFile(const char* Name){
	assert(1);
}
cPtrDiff FILE_WriteBinStream::Size(){
    return Pos;
}
void FILE_WriteBinStream::SetReadPos(cPtrDiff pos){
	assert(1);
}
void FILE_WriteBinStream::SetWritePos(cPtrDiff pos){
	assert(1);
}
cPtrDiff FILE_WriteBinStream::GetReadPos(){
	assert(1);
	return 0;
}
cPtrDiff FILE_WriteBinStream::GetWritePos(){
	return Pos;
}
BYTE* FILE_WriteBinStream::GetData(){
	assert(1);
	return NULL;
}
void FILE_WriteBinStream::Clear(){
	if(F!=INVALID_HANDLE_VALUE && TempCurrSize){
		//RBlockWrite(F,TempBuffer,TempCurrSize);
		if(Multithreaded){
			MT_ChunksWriter::AddToQueue(TempBuffer, TempCurrSize, F, 0, 0, AllowZip, StreamCustomID);
		}else{
			int sz=RBlockWrite(F,TempBuffer,TempCurrSize);
			if(sz!=TempCurrSize){
				WriteError=1;
				ErrantFileName=FileName.ToCharPtr();
			}
		}
	}
	if(F!=INVALID_HANDLE_VALUE){
		//RClose(F);
		if(Multithreaded){
			if(RenameTo.Length()){
				MT_ChunksWriter::AddToQueue(NULL, 0, F, InitialName.ToCharPtr(), RenameTo.ToCharPtr(), AllowZip, StreamCustomID);
			}else{
				MT_ChunksWriter::AddToQueue(NULL, 0, F, 0, 0, AllowZip, StreamCustomID);
			}
		}else{
			RClose(F);
			if(RenameTo.Length()){
				comms::cIO::SetFilePermissions(RenameTo.ToCharPtr());
				comms::cIO::RemoveFile(RenameTo.ToCharPtr());
				__rename(InitialName.ToCharPtr(),RenameTo.ToCharPtr());
			}
		}
	}
	delete[]TempBuffer;	
	F=INVALID_HANDLE_VALUE;
	Pos=0;
	TempBuffer=NULL;
	TempCurrSize=0;
}

FileReadBinStream::FileReadBinStream(const char* Name){
	F=INVALID_HANDLE_VALUE;
	Pos=0;
	ReadFromFile(Name);
}
FileReadBinStream::~FileReadBinStream(){
	if(F!=INVALID_HANDLE_VALUE)RClose(F);
    F=INVALID_HANDLE_VALUE;
}
bool FileReadBinStream::Valid(){
	return F!=INVALID_HANDLE_VALUE;
}
void FileReadBinStream::Write(const void* data,cPtrDiff size){	
	assert(1);
}
cPtrDiff FileReadBinStream::Read(void* Data,cPtrDiff size){	
    if(F!=INVALID_HANDLE_VALUE){
        RBlockRead(F,Data,size);
    }
	Pos+=size;    
	return size;
}
cPtrDiff FileReadBinStream::Skip(cPtrDiff size){
    if(F!=INVALID_HANDLE_VALUE){
        RSeek(F,Pos+size);
    }
	Pos+=size;
	return size;
}
void FileReadBinStream::WriteToFile(const char* Name){
	assert(1);
}
void FileReadBinStream::ReadFromFile(const char* Name){
    F=RReset(Name);
    if(F!=INVALID_HANDLE_VALUE){
        fSize=RFileSize(F);
	}else fSize=0;
}
cPtrDiff FileReadBinStream::Size(){
	return fSize;
}
void FileReadBinStream::SetReadPos(cPtrDiff pos){
	assert(1);
}
void FileReadBinStream::SetWritePos(cPtrDiff pos){
	assert(1);
}
cPtrDiff FileReadBinStream::GetReadPos(){
	return Pos;
}
cPtrDiff FileReadBinStream::GetWritePos(){
	assert(1);
	return 0;
}
BYTE* FileReadBinStream::GetData(){
	assert(1);
	return NULL;
}
void FileReadBinStream::Clear(){	
	if(F!=INVALID_HANDLE_VALUE)RClose(F);
    F=INVALID_HANDLE_VALUE;
	Pos=0;
	fSize=0;
}


FILE_ReadBinStream::FILE_ReadBinStream(const char* Name){
	fSize=0;
	F=INVALID_HANDLE_VALUE;
	Pos=0;
	TempSize=65536*128;
	TempBuffer=new BYTE[TempSize];
	TempCurrSize=0;
	TempPos=0;
	ReadFromFile(Name);
}
FILE_ReadBinStream::~FILE_ReadBinStream(){
	if(TempBuffer)delete[]TempBuffer;
	if(F!=INVALID_HANDLE_VALUE)RClose(F);
}
bool FILE_ReadBinStream::Valid(){
	return F!=INVALID_HANDLE_VALUE;
}
void FILE_ReadBinStream::Write(const void* data,cPtrDiff size){	
	assert(1);
}
cPtrDiff FILE_ReadBinStream::Read(void* Data,cPtrDiff size){	
	BYTE* data=(BYTE*)Data;
	int ads=0;
	if(TempPos+size>TempCurrSize){
		cPtrDiff rem=TempCurrSize-TempPos;
		if(rem){
			memcpy(data,TempBuffer+TempPos,rem);			
			data+=rem;
			size-=rem;
			Pos+=rem;
		}
		if(size>TempSize){
            if(F!=INVALID_HANDLE_VALUE)size=RBlockRead(F,data,size);
			TempCurrSize=0;
			TempPos=0;
			Pos+=size;
			return size+rem;
		}else{
			int tsz=0;
			if(F!=INVALID_HANDLE_VALUE)tsz=RBlockRead(F,TempBuffer,TempSize);
			if(size>tsz)size=tsz;
			TempCurrSize=tsz;//TempSize;
			TempPos=0;
			ads=rem;
		}
	}
	memcpy(data,TempBuffer+TempPos,size);
	TempPos+=size;
	Pos+=size;
	return size+ads;
}
cPtrDiff FILE_ReadBinStream::Skip(cPtrDiff size){	
	if(TempPos+size>TempCurrSize){
		cPtrDiff rem=TempCurrSize-TempPos;
		if(rem){
			size-=rem;
			Pos+=rem;
		}
		if(size>TempSize){
			TempCurrSize=0;
			TempPos=0;
			Pos+=size;
			RSeek(F, Pos);
			return size;
		}else{
			RBlockRead(F,TempBuffer,TempSize);
			TempCurrSize=TempSize;
			TempPos=0;
		}
	}	
	TempPos+=size;
	Pos+=size;
	return size;
}
void FILE_ReadBinStream::WriteToFile(const char* Name){
	assert(1);
}
void FILE_ReadBinStream::ReadFromFile(const char* Name){
	if(F!=INVALID_HANDLE_VALUE)RClose(F);
	fSize=0;
	F=INVALID_HANDLE_VALUE;
	Pos=0;
	if(Name){
		F=RReset(Name);
		if(F!=INVALID_HANDLE_VALUE){			
			fSize=RFileSize(F);			
		}
	}
}
cPtrDiff FILE_ReadBinStream::Size(){
	return fSize;
}
void FILE_ReadBinStream::SetReadPos(cPtrDiff pos){
	assert(1);
}
void FILE_ReadBinStream::SetWritePos(cPtrDiff pos){
	assert(1);
}
cPtrDiff FILE_ReadBinStream::GetReadPos(){
	return Pos;
}
cPtrDiff FILE_ReadBinStream::GetWritePos(){
	assert(1);
	return 0;
}
BYTE* FILE_ReadBinStream::GetData(){
	assert(1);
	return NULL;
}
void FILE_ReadBinStream::Clear(){
	if(TempBuffer)delete[]TempBuffer;
	if(F!=INVALID_HANDLE_VALUE)RClose(F);
	F=INVALID_HANDLE_VALUE;
	TempBuffer=NULL;
	Pos=0;
	fSize=0;
}