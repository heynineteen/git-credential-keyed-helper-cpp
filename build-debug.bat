cl /std:c++17 /DDEBUG /Zi src/main.cpp src/log.cpp src/GitContext.cpp src/error.cpp Advapi32.lib Kernel32.lib User32.lib /EHsc /Fegit-credential-keyed-helper.exe
