#define PEPARSER_EXPORT_LIBRARY
#include "../Declarations.h"

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
    switch (fdwReason) {
    case DLL_PROCESS_ATTACH: {
        printf("Initialize once for each new process...\n");
        break;
    }
    case DLL_THREAD_ATTACH: {
        printf("Do thread-specific initialization...\n");
        break;
    }
    case DLL_THREAD_DETACH: {
        printf("Do thread-specific cleanup...\n");
        break;
    }
    case DLL_PROCESS_DETACH: {
        printf("Perform any necessary cleanup...\n");
        break;
    }
    }
    return TRUE;
}