For the future:
If the vs code debugger doesn't work, try this:

1. set every file insise .vscode-server/cpp.../debyugAdapters/bin to be executable
2. use the following configuration:
```{
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "name": "(gdb) Launch",
            "type": "cppdbg",
            "request": "launch",
            "program": "${env:HOME}/os161/root/kernel",
            "args": [],
            "stopAtEntry": true,
            "cwd": "${env:HOME}/os161/root",
            "environment": [],
            "externalConsole": false,
            "miDebuggerServerAddress": "unix:.sockets/gdb",
            "miDebuggerPath": "${env:HOME}/os161/tools/bin/mips-harvard-os161-gdb",
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            "logging": {
                "trace": true,
                "traceResponse": true
            }
        }
    ]
}```

