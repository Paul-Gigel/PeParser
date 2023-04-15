#pragma once
#include "Preprocessor.h"
#include <Windows.h>
namespace PEParserNamespace {
	class PEParserBase {
	public:
		HANDLE hFile;
		DWORD dwFileSize;
		DWORD bytes;
		void* fileBuffer;
	};
	typedef class PEHEADER {
	public:
		PIMAGE_DOS_HEADER		pDosH;
		PIMAGE_NT_HEADERS		pNtH;
		PIMAGE_SECTION_HEADER	pSecH;					//points to the first SecH
		PIMAGE_SECTION_HEADER	pSecHSingle;			//points to a selected SecH
		IMAGE_FILE_HEADER		FileH;
		IMAGE_OPTIONAL_HEADER	OptH;
	} PEParserHeader;
	typedef class functionExecutionLog {
	public:
		bool failed;
		union alignas(64){
			void* codeVoidptr;
			unsigned long codeUnsignedLong;
			int codeInt;
		} code;			//64bit alignment
	} PEParserfunctionExecutionLog;
	typedef class signatur{
	public:
		const char* Signatur;
		const char* UnmangledSig;
	} PEParsersignatur;
	class PEParser : public PEParserBase, public PEParserHeader, public functionExecutionLog, public signatur	{

	};
}