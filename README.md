# cpp_simplehttpserver

Minimal synchronous, single-threaded html server using uWebSockets.

Place html files to be served in the "public" folder. On startup, the server copies the file contents into memory, so the server must be stopped then started in order to reflect file changes. The server does not look in subfolders of the "public" folder.

## Build instructions:
1. Download uWebSockets from here: [https://github.com/uNetworking/uWebSockets](https://github.com/uNetworking/uWebSockets).
2. After cloning the repository, be sure to run `git submodule init` then `git submodule update` to get the submodules.
3. Build uWebSockets by running `make` at the root of the repository.

4. To build this project, run: `make UWEBSOCKETS_DIR=/path/to/uWebSockets`.

## VSCode Linting:
VSCode may complain that "App.h" cannot be found. One solution is to use the *Makefile Tools* extension. Create a bash script that exports the "UWEBSOCKETS_DIR" environment variable then in the workspace settings for *Makefile Tools*, set "Pre Configure Script" to the path to your bash script. You can also check the setting "Always Pre Configure".