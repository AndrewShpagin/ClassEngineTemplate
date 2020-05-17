#pragma once

typedef HANDLE ResFile;
//Opening the resource file
ResFile RReset(LPCSTR lpFileName);
//Rewriting file
ResFile RRewrite(LPCSTR lpFileName);
ResFile RAppend(LPCSTR lpFileName);
//Getting size of the resource file
cPtrDiff RFileSize(HANDLE hFile);
// Setting file position 
cPtrDiff RSeek(ResFile hFile, cPtrDiff pos);
cPtrDiff RSeekFromCurrent(ResFile hFile, cPtrDiff nBytes);
//Reading the file
cPtrDiff RBlockRead(ResFile hFile,LPVOID lpBuffer, cPtrDiff BytesToRead);
//Writing the file
cPtrDiff RBlockWrite(ResFile hFile,const void* lpBuffer, cPtrDiff BytesToWrite);
//Returns last error
DWORD IOresult(void);
//Close the file
void RClose(ResFile hFile);
