#include <Windows.h> // Credits: 0xsystem\rootkit
#include <iostream> // Credits: 0xsystem\rootkit
 // Credits: 0xsystem\rootkit
using MessageboxAPtr = int(__stdcall*)(HWND, LPCWSTR, LPCWSTR, UINT); // Credits: 0xsystem\rootkit
int __stdcall HookedMessageBoxA(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType) { // Credits: 0xsystem\rootkit
    return MessageBoxW(hWnd, L"Hello from the hooked function!", L"Hooked!", uType); // Credits: 0xsystem\rootkit
} // Credits: 0xsystem\rootkit
int main() { // Credits: 0xsystem\rootkit
    HMODULE user32 = LoadLibraryW(L"user32.dll"); // Credits: 0xsystem\rootkit
    MessageboxAPtr originalFunc = reinterpret_cast<MessageboxAPtr>(GetProcAddress(user32, "MessageBoxA")); // Credits: 0xsystem\rootkit
    DWORD oldProtect; // Credits: 0xsystem\rootkit
    VirtualProtect(originalFunc, sizeof(HookedMessageBoxA), PAGE_EXECUTE_READWRITE, &oldProtect); // Credits: 0xsystem\rootkit
    memcpy(originalFunc, HookedMessageBoxA, sizeof(HookedMessageBoxA)); // Credits: 0xsystem\rootkit
    VirtualProtect(originalFunc, sizeof(HookedMessageBoxA), oldProtect, &oldProtect); // Credits: 0xsystem\rootkit
    int ret = MessageBoxA(NULL, "This is the original function.", "Original", MB_OK); // Credits: 0xsystem\rootkit
    std::cout << "Return value from original function: " << ret << std::endl; // Credits: 0xsystem\rootkit
    ret = originalFunc(NULL, L"This is the hooked function.", L"Hooked", MB_OK); // Credits: 0xsystem\rootkit
    std::cout << "Return value from hooked function: " << ret << std::endl; // Credits: 0xsystem\rootkit
    FreeLibrary(user32);
    return 0;     // Credits: 0xsystem\rootkit
}
