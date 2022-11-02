//
// Created by u161671 on 2/11/2022.
//

#pragma once

#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#define CMDPATH "C:\\Windows\\System32\\cmd.exe"


namespace trk{
    class Debug{
    public:
        //attributes -----
        STARTUPINFO si;
        PROCESS_INFORMATION pi;

        //methods --------
        Debug(){}
        ~Debug(){}
        void startDebugOutput();
        void stopDebugOutput();
    private:

    };
}
