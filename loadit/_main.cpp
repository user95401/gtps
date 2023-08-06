#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>

DWORD WINAPI thread_func(void* hModule) {
    auto libPath = "gtps\\Release\\gtps.dll";
    LoadLibrary(libPath);
    if (!GetModuleHandleA(libPath)) {
        MessageBox(nullptr, std::string("Cant load lib at \"" + std::string(libPath) + "\"!").c_str(), "loadit", MB_OK | MB_ICONERROR);
    }
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, thread_func, hModule, 0, 0);
    return TRUE;
}