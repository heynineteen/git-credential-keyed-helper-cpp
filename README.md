# git-credential-keyed-helper-cpp

## Usage scenario
When accessing git repos over https, existing windows credential helpers e.g. `manager-core` will allow a set of credentials to be stored per domain. So if you are accessing remote repos on github.com, one set of credentials can be stored. If you need to use another set of credentials for a repo on github.com one option is to use the SSH protocol rather than https, but if you'd rather use https, this credential helper will allow you to configure multiple credentials for the same host, storing the credentials under a specific key that you provide in your configuration.

## Useful links
[Git documentation of credential storage](https://git-scm.com/book/en/v2/Git-Tools-Credential-Storage)

## Installation instructions
The executable can either be built from the source code or downloaded from an existing release.

### Building from source
#### Prerequisites
 To build or debug this project the following are required:
- Windows SDK. This is most easily done by installing C and C++ support in Visual Studio 20XX. Instructions [here](https://learn.microsoft.com/en-us/cpp/build/vscpp-step-0-installation?view=msvc-170).
- Visual Studio Code. This has been the IDE used for this project and is required to follow the debugging instructions.
- Developer Command Prompt for Visual Studio 20XX (installed as part of Visual Studio).

#### Compilation
The following steps will create a build of `git-credential-keyed-helper.exe`:
- Open a Developer Command Prompt in the root directory of this repo.
- Run the following command for a Release build:
```
cl /std:c++17 src/main.cpp src/log.cpp src/GitContext.cpp src/error.cpp Advapi32.lib Kernel32.lib User32.lib /EHsc /Fegit-credential-keyed-helper.exe
```
- Alternatively, run `build.bat` from the root directory of this repo.
- Run the following command for a Debug build:
```
cl /std:c++17 /DDEBUG /Zi src/main.cpp src/log.cpp src/GitContext.cpp src/error.cpp Advapi32.lib Kernel32.lib User32.lib /EHsc /Fegit-credential-keyed-helper.exe
```
- Alternatively, run `build-debug.bat` from the root directory of this repo.

### Download an existing release
Release are available [here](../../releases).
- Navigate to the latest release.
- Release build is named `git-credential-keyed-helper.exe`.
- Debug build is named `git-credential-keyed-helper-debug.exe`. Rename this to `git-credential-keyed-helper.exe` before copying.

### Running a debug build
Running the debug version of the executable will enable the logging of debug information to the system. This can be viewed in a tool such as [DebugView](https://learn.microsoft.com/en-us/sysinternals/downloads/debugview). This may output sensitive data to ensure to delete if you have configured this to be persisted to a file.

### Copy the executable
Copy the executable to the location on your hard-drive where your other credential helpers are located. In a typical Git for Windows intallation this will be `C:\Program Files\Git\mingw64\libexec\git-core`.

### Create a .gitconfig
Create new `.gitconfig` file which will include your specific user information and the helper to use. Sensible location for this file would be in your user folder or in the parent folder that will contain repos for this particular account. For example:
```
[user]
    email = clem.fandango@foo.com
    name = Clem Fandango

[github]
    user = clem.fandango

[credential]
    helper = 
    helper = keyed-helper heynineteen
```
Unlike other git config items, a value for `credential.helper` will not replace values in any parent config files but add another helper to the list. The helpers in this list get called in turn until one provides some credentials. To avoid this and replace helpers specified in parent configs, we first include a blank helper (` helper = `) followed by the the configuration for our overriding helper (`helper = keyed-helper heynineteen`).

This configuration sets the credential helper to be an executable named `git-credential-keyed-helper` and passes an argument of `heynineteen`. This argument is an arbitrary key value used along with the remote git host to distiguish between different accounts and allows multiple accounts to be configured on the same machine.

### Update your user .gitconfig file
Add this entry to your system or user .git config file:
```
[includeIf "gitdir:C:/my-repos/heynineteen/"] # include for all .git projects under my-repos/ 
    path = C:/my-repos/heynineteen/.gitconfig
```
This entry means the content of `C:/my-repos/heynineteen/.gitconfig` will be included in the git conguration when the current folder is or is a child folder of `C:/my-repos/heynineteen/`.

## Using the credential helper
Attempting to access the remote git repo will result in git asking the helper for credentials. The helper will attempt to retrieve the credentials Windows Credential Manager using the key built from the argument in the `credential.helper` section of the .gitconfig file and the host of the remote repo e.g.`heynineteen @ github.com`. If the credentials cannot be found, the user is prompted for the username and password. Since the use of passwords has been deprecated in this situation, you need to provide a personal access token when prompted for the password. The credential helper will then store the credential in Windows Credential Manager.

## Debuging in Visual Studio Code
- Ensure all steps in the [prerequisites](#prerequisites) have been followed.
- Ensure this project is opened in Visual Studio Code from the command line of the Developer Command Prompt. This runs a script that sets up the paths and environment variables necessary to access the C/C++ binaries and tools.
- Set breakpoints.
- Click the `Run and Debug` button on the sidebar.
- Select `Debug C Program` from the drop down.
- Click `Start Debugging` or press F5.
