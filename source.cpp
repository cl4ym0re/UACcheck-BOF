#include "bofdefs.h"



#define print_error(msg, hr) _print_error(__FUNCTION__, __LINE__, msg, hr)

BOOL _print_error(char* func, int line, char* msg, HRESULT hr) {
#ifdef BOF
    BeaconPrintf(CALLBACK_ERROR, "(%s at %d): %s 0x%08lx", func, line, msg, hr);
#else
    printf("[-] (%s at %d): %s 0x%08lx", func, line, msg, hr);
#endif // BOF

    return FALSE;
}
#pragma endregion



#ifdef BOF


enum UAC_LEVEL {
    UAC_ALWAYS_NOTIFY = 2,
    UAC_DEFAULT_NOTIFY = 5,
    UAC_NEVER_NOTIFY = 0,
    UAC_ERROR = 9,
};

UAC_LEVEL GetUACLevel() {
    HKEY hKey;
    LONG result = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
        "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",
        0, KEY_READ, &hKey);

    if (result != ERROR_SUCCESS) {
        BeaconPrintf(CALLBACK_ERROR, "Error opening registry key.");
        return UAC_ERROR;  
    }

    DWORD enableLUA = 0;
    DWORD size = sizeof(enableLUA);
    result = RegQueryValueEx(hKey, "EnableLUA", NULL, NULL, (LPBYTE)&enableLUA, &size);

    if (result != ERROR_SUCCESS) {
        BeaconPrintf(CALLBACK_ERROR, "Error reading EnableLUA registry value.");
        RegCloseKey(hKey);
        return UAC_ERROR;  
    }


    DWORD consentPromptBehaviorAdmin = 0;
    size = sizeof(consentPromptBehaviorAdmin);
    result = RegQueryValueEx(hKey, "ConsentPromptBehaviorAdmin", NULL, NULL,
        (LPBYTE)&consentPromptBehaviorAdmin, &size);

    RegCloseKey(hKey);


    
    switch (consentPromptBehaviorAdmin) {

    case 2:  // ²»Í¨Öª
        return UAC_ALWAYS_NOTIFY;
    case 0:
        return UAC_NEVER_NOTIFY;

    default:
        return UAC_DEFAULT_NOTIFY;  
    }
}
void go(char* args, int len) {
    datap parser;
    BeaconDataParse(&parser, args, len);
 
    UAC_LEVEL uacLevel = GetUACLevel();

    switch (uacLevel) {
    case UAC_ALWAYS_NOTIFY:
        BeaconPrintf(CALLBACK_ERROR, "UAC Level : Always Notify");
        break;
    case UAC_DEFAULT_NOTIFY:
        BeaconPrintf(CALLBACK_OUTPUT, "UAC Level : Default Notify");
        break;
    case UAC_NEVER_NOTIFY:
        BeaconPrintf(CALLBACK_OUTPUT, "UAC Level : Never Notify");
        break;
    default:
        BeaconPrintf(CALLBACK_OUTPUT, "UAC Level : Default Notify");
        break;
    }

}

#else

void main(int argc, char* argv[]) {

}

#endif