//
// Created by u161671 on 2/11/2022.
//

#pragma once

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <iostream>
#include <fstream>

#define CMDPATH "C:\\Windows\\System32\\cmd.exe"


namespace trk{
    class Debug{
    public:
        //attributes -----
        STARTUPINFO si;
        PROCESS_INFORMATION pi;
        SECURITY_ATTRIBUTES sa;
        HANDLE hFile;
        //methods --------
        Debug(){}
        ~Debug(){}
        void Log(std::string msg);
        void stopDebugOutput();
    private:

    };
}
