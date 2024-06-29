#ifndef _INC_GCMK
#define _INC_GCMK

#include <iostream>
#include <string>
#include <vector>
#include <wincred.h>
#include <windows.h>

using namespace std;

struct GitContext
{
    string key;
    string command;
    string protocol;
    string host;
    string username;
    string password;
    string target;
};

void parseInput(char*[], int, struct GitContext*);
wstring convertToWideCharacterString(string source);

void get(struct GitContext*);
void store(struct GitContext*);
void erase(struct GitContext*);

const char EXPECTED_ARG_COUNT = {3};
const char ARG_INDEX_KEY = {1};
const string INPUT_LINE_DELIMITER = {"="};
const string COMMAND_GET =  {"get"};
const string COMMAND_STORE = {"store"};
const string COMMAND_ERASE = {"erase"};

#endif // _INC_GCMK
