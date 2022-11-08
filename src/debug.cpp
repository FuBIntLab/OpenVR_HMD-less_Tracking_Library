//
// Created by u161671 on 2/11/2022.
//

#include "../includes/debug.hpp"

namespace trk{
    void Debug::Log(std::string msg) {
        std::ofstream out("output.log");
        std::streambuf *coutbuf = std::cout.rdbuf();
        std::cout.rdbuf(out.rdbuf());

        std::cout << msg << "\n";

        std::cout.rdbuf(coutbuf);
    }

    void Debug::stopDebugOutput(){
        TerminateProcess(pi.hProcess,0);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
}