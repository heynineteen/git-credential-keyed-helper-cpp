#include <windows.h>
#include <fstream>
#include <filesystem>

#include "gckh.h"

using namespace std;
namespace fs = std::filesystem;

static const string filename = "git-credential-keyed-helper.log";
static string filePathAndName = (fs::path{(fs::temp_directory_path())} / filename).string();

static string getErrorString(int error)
{
    switch (error)
    {
      case ERROR_ALREADY_EXISTS:
          return "ERROR_ALREADY_EXISTS";
      case ERROR_NO_SUCH_LOGON_SESSION:
          return "ERROR_NO_SUCH_LOGON_SESSION";
      case ERROR_BAD_USERNAME:
          return "ERROR_BAD_USERNAME";
      case ERROR_INVALID_PARAMETER:
          return "ERROR_INVALID_PARAMETER";
      case ERROR_NOT_FOUND:
          return "ERROR_NOT_FOUND";
      case ERROR_INVALID_FLAGS:
          return "ERROR_INVALID_FLAGS";
      default:
          return "UNKNOWN_ERROR";
    }
}

void handleWin32Error(string file, string func, int line, string win32Function, int error)
{
    TRACE
    LOG(filePathAndName);

    ofstream errorFile(filePathAndName, ios::app);

    if(!errorFile.is_open())
        return;

    errorFile << "ERROR at"
        << " file: " << file 
        << " function: " << func
        << " at line: " << line
        << " calling: " << win32Function
        << " error code: 0x" << hex << error << " " << getErrorString(error)
        << endl; 

    errorFile.close();
}