#include <string>
#include <sstream>
#include "gcmk.h"

using std::string;

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
#endif

