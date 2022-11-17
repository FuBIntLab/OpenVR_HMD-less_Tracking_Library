//
// Created by u161671 on 2/11/2022.
//

#include "../includes/debug.hpp"

namespace trk{
    Debug::Debug(){
        //TODO: DebugString
        //myFile.open("output.log");
        AllocConsole();
        freopen("CONOUT$", "w",stdout);
    }

    void Debug::Log(std::string msg) {
        //myFile << msg <<"\n";
        std::cout << msg << std::endl;
    }

    void Debug::stopDebugOutput(){
        //myFile.close();
    }
}