# cpp_simplehttpserver

Minimal synchronous, single-threaded html server using uWebSockets.

Place html files to be served in the "public" folder. On startup, the server copies the file contents into memory, so the server must be stopped then started in order to reflect file changes. The server does not look in subfolders of the "public" folder.