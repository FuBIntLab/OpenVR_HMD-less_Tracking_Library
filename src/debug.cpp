//
// Created by u161671 on 2/11/2022.
//

#include "../includes/debug.hpp"

namespace trk{
    void Debug::startDebugOutput() {
        ZeroMemory(&si,sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi,sizeof(pi));



        CreateProcess(CMDPATH,
                      NULL,
                      NULL,
                      NULL,
                      FALSE,
                      CREATE_NEW_CONSOLE,
                      NULL,
                      NULL,
                      &si,
                      &pi);
    }

    void Debug::stopDebugOutput(){
        TerminateProcess(pi.hProcess,0);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
}