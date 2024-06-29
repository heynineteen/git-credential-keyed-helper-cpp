#include <windows.h>
#include <wincred.h>
#include <iostream>
#include "gcmk.h"

using namespace std;
int main(int argc, char *argv[])
{
    // setlocale(LC_ALL, "");

    if(argc < EXPECTED_ARG_COUNT)
        return 1;

    GitContext context;

    parseInput(argv, argc, &context);

    if(context.command == COMMAND_GET)
        get(&context);
    else if(context.command == COMMAND_STORE)
        store(&context);
    else if(context.command == COMMAND_ERASE)
        erase(&context);

    return 0;
}

void get(struct GitContext* context)
{
    PCREDENTIALW credential;

    const wstring targetName = convertToWideCharacterString(context->target);
    BOOL result = CredReadW(const_cast<LPWSTR>(targetName.c_str()), CRED_TYPE_GENERIC, 0, &credential);

    // if(!result)
    //     handleWin32Error("CredReadW", result);

    if(!result || credential->CredentialBlobSize == 0)
        return;

    WCHAR *password = (WCHAR*)malloc(credential->CredentialBlobSize + sizeof(WCHAR));
    memcpy(password, credential->CredentialBlob, credential->CredentialBlobSize);
    password[credential->CredentialBlobSize / sizeof(WCHAR)] = L'\0';

    wcout << L"username=" << credential->UserName << endl;
    wcout << L"password=" << password << endl;

    free(password);
    CredFree(&credential);
}

void store(struct GitContext* context)
{
    if(context->username.empty() || context->password.empty())
        return;

    auto target = convertToWideCharacterString(context->target);
    auto username = convertToWideCharacterString(context->username);
    auto password = convertToWideCharacterString(context->password);

    CREDENTIALW credential = {0};
    credential.TargetName = const_cast<LPWSTR>(target.c_str());
    credential.CredentialBlob = reinterpret_cast<LPBYTE>(const_cast<LPWSTR>(password.c_str()));
    credential.CredentialBlobSize = static_cast<DWORD>(password.size() * sizeof(WCHAR));
    credential.UserName = const_cast<LPWSTR>(username.c_str());
    credential.Type = CRED_TYPE_GENERIC;
    credential.Persist = CRED_PERSIST_LOCAL_MACHINE;

    BOOL result = CredWriteW(&credential, 0);

    // if(!result)
        // handleWin32Error("CredWriteW", result);
}

void erase(struct GitContext* context)
{
    auto target = convertToWideCharacterString(context->target);
    BOOL result = CredDeleteW(target.c_str(), CRED_TYPE_GENERIC, 0);

    // if(!result)
    //     handleWin32Error("CredDeleteW", result);
}

wstring convertToWideCharacterString(string source)
{
    wstring dest(source.size(), L' ');
    mbstowcs(&dest[0], source.c_str(), source.size());
    return dest;
}

void parseInput(char* argv[], int argc, GitContext* context)
{
    string line;
    while(getline(cin, line))
    {
        if(line.empty())
            break;

        size_t pos = line.find(INPUT_LINE_DELIMITER);

        if(pos == string::npos || pos == 0 || pos == line.length() - 1)
            continue;

        auto key = line.substr(0, pos);
        auto value = line.substr(pos + 1);

        if(key == "username")
            context->username = value;
        else if(key == "password")
            context->password = value;
        else if(key == "protocol")
            context->protocol = value;
        else if(key == "host")
            context->host = value;
    }

    context->key = argv[ARG_INDEX_KEY];
    context->command = argv[argc - 1];

    if(!context->key.empty() && !context->host.empty())
        context->target = context->key + " @ " + context->host;
}
