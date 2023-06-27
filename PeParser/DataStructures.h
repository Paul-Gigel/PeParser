#pragma once
#include "Preprocessor.h"
#include <Windows.h>
#include <concepts>
#include <type_traits>
#include <concepts>
#include <iostream>
//#include "PEParser.h"
//I think I will have to implement getter and setter either
//as methods in classes/structs (make everything privat and the compiler tells where to replace with new getter / setter)
//or as macros in pr�processor.h
namespace PEParserNamespace {
	void PEParser_memcpy(void* dest, void* src, size_t n) noexcept {
		for (int i = 0; i < sizeof(void*); i++) {
			((char*)dest)[i] = ((char*)src)[i];
		}
	}
	template<typename T1, typename ...Tn> constexpr T1 unpack(T1 t1, Tn... ) noexcept {return t1;}	//compiletime function, disapears after compilation
	
	typedef struct functionExecutionLog {
		PEParser_OFFSET bool failed;					// if used as dummy class, this contains either absolut adress or displacement from derived class Structure
		union alignas(void*) Code {
			void* codeVoidptr;
			unsigned long codeUnsignedLong;
			int codeInt;
		} code;			//64bit alignment
		template<typename ...T>
		functionExecutionLog(functionExecutionLog* pfx, T*... pderived) {
			if constexpr (sizeof...(pderived) == 1) {
				alignas(void*) unsigned long long temp = (unsigned long long)pfx - (unsigned long long)unpack(pderived...);
				PEParser_memcpy(&(this->failed), &temp, sizeof(temp));
			}	else	{
				//store address of pfx->failed in this->failed
				//reinterpret_cast<functionExecutionLog*>(this->failed) = *pfx;
				alignas(void*) unsigned long long temp = (unsigned long long)pfx;
				PEParser_memcpy(&(this->failed), &temp, sizeof(temp));
			}
		}
		functionExecutionLog() {};
		//getter
		template<typename ...T> bool getFailed(T... derived) {
			static_assert(sizeof...(derived) <= 1, "to much Arguments");
			if constexpr(sizeof...(derived) == 1)	{
				std::cout <<unpack(derived...)->ppEParser.Dummy.pEParserFunctionExecutionLog.failed<<"\n";
				return ((functionExecutionLog*)(
					(void*)((unsigned char*)unpack(derived...) + this->failed)
					))->failed;
			}	else {
				return ((functionExecutionLog*)&(this->failed))->failed;
				//return ((functionExecutionLog*)(void*)((unsigned long long*) & (this->failed)))->failed;
			}
		}
		functionExecutionLog::Code getCode() {
			//implement in same way as above
			return reinterpret_cast<functionExecutionLog*>(this->failed)->code;
		}
	} PEParserfunctionExecutionLog;
	typedef struct signatur {
		const char* Signatur;
		const char* UnmangledSig;
	} PEParsersignatur;

	struct PEParserBase :
		virtual public functionExecutionLog,
		virtual public signatur 
	{
		HANDLE hFile;
		DWORD dwFileSize;
		DWORD bytes;
		void* fileBuffer;
	};
	typedef struct PEHEADER : 
		virtual public functionExecutionLog,
		virtual public signatur	
	{
		PIMAGE_DOS_HEADER		pDosH;
		PIMAGE_NT_HEADERS		pNtH;
		PIMAGE_SECTION_HEADER	pSecH;					//points to the first SecH
		PIMAGE_SECTION_HEADER	pSecHSingle;			//points to a selected SecH
		PIMAGE_FILE_HEADER		pFileH;
		PIMAGE_OPTIONAL_HEADER	pOptH;
		PIMAGE_DATA_DIRECTORY	pDataDir;
		PIMAGE_DATA_DIRECTORY	pDataDirSingle;
	} PEParserHeader;
	struct PEParser : 
		public PEParserBase, 
		public PEParserHeader
	{

	};
	template<typename Type>	//Type meight be for e.a. PEParserHeader
	auto ClassConverter(Type type) noexcept {
		if constexpr (std::is_base_of_v<functionExecutionLog, Type> /*not right!!!*/) {
			functionExecutionLog* fx;
			void* fxVBPTR;				//Virtual Base PoinTeR (displacement/offset/RVA from base of type to begin of virtualBase instance)
		};
		if constexpr (std::is_base_of_v<signatur, Type>) {
			signatur* sig;
			void* sigVBPTR;
		}
		if constexpr (std::is_base_of_v<Type, PEParser>)	{
			//if all ifs above true, than Diamandshape inheritence
		}
		/*
		* returns pointer of unnamed class
		*/
		return;
	}
}
/*
			static_assert(!(sizeof...(pderived) > 1), "to much Arguments");
			std::cout << sizeof...(pderived)<<"	sadasdfasdfasdfasdfasdfasdfasdf\n";
			std::cout << (pfx->code.codeInt)<<"\n";
			std::cout << pfx<<"\n";
			std::cout << unpack(pderived...)->ppEParser.Dummy.pEParserFunctionExecutionLog.code.codeInt <<"\n";
			std::cout << unpack(pderived...)<<"\n";
			std::cout << (int)pfx - (int)unpack(pderived...)<<"\n";
*/