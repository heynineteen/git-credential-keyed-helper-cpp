#ifndef _INC_GCMK
#define _INC_GCMK

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class GitContext
{
    public: 
        string key;
        string command;
        string protocol;
        string host;
        string username;
        string password;

        GitContext(string key, string command);

        string target() const;
};

GitContext parseInput(char*[], int);
wstring convertToWideCharacterString(const string source);

void get(const GitContext&);
void store(const GitContext&);
void erase(const GitContext&);

const char EXPECTED_ARG_COUNT = {3};
const char ARG_INDEX_KEY = {1};
const string INPUT_LINE_DELIMITER = {"="};
const string COMMAND_GET =  {"get"};
const string COMMAND_STORE = {"store"};
const string COMMAND_ERASE = {"erase"};

#endif // _INC_GCMK
