#include "gcmk.h"

GitContext::GitContext(string key, string command) : key{key}, command{command}
{

}

string GitContext::target() const
{
    string result;
    if(!key.empty() && !host.empty())
        result = key + " @ " + host;

    return result;
}