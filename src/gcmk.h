#ifndef _INC_GCMK
#define _INC_GCMK

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;
using std::string;

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

#ifdef DEBUG
#define TRACE debug_printer("TRACE", __FILE__, __func__, __LINE__ , string());
#define LOG(msg) {std::ostringstream _s; _s << msg; debug_printer("LOG", __FILE__, __func__, __LINE__ , _s.str());}
#define LOGCONTEXT(context) log_context(context);

void debug_printer(string type, string fn, string func, int line, string msg);
void log_context(const GitContext& context);
#else
#define TRACE
#define LOG(msg)
#define LOGCONTEXT(context)
#endif // _INC_DEBUG

#define HANDLE_WIN32_ERROR(win32Function, error) handleWin32Error(__FILE__, __func__, __LINE__, win32Function, error);

void handleWin32Error(string file, string func, int line, string win32Function, int error);

#endif // _INC_GCMK
