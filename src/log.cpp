#include <iostream>
#include <sstream>
#include <windows.h>
#include "log.h"

using std::string;

#ifdef DEBUG
void debug_printer(string type, string fn, string func, int line, string msg) {
    std::ostringstream s;

    s   << type << ": "
        << fn << "(" << line << "): "
        << func;
        if (msg.size()) {
            s << "\t:\t" << msg;
        }
    s << std::endl;

    OutputDebugString((LPCSTR)s.str().c_str());
}

void log_context(const GitContext& context)
{
    std::ostringstream s;

    s   << "key: '" << context.key << "'"
        << "\tcommand: '" << context.command << "'"
        << "\thost: '" << context.host << "'"
        << "\tprotocol: '" << context.protocol << "'"
        << "\ttarget: '" << context.target() << "'"
        << "\tusername: '" << context.username << "'"
        << "\tpassword: '" << context.password << "'";

    cout << "logcontext";
    
    OutputDebugString((LPCSTR)s.str().c_str());
}
#endif // DEBUG
