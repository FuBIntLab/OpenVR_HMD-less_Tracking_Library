//
// Created by u161671 on 2/11/2022.
//

#include "../includes/debug.hpp"

namespace trk{
    Debug::Debug(){
        myFile.open("output.log");
    }

    void Debug::Log(std::string msg) {
        myFile << msg <<"\n";
    }

    void Debug::stopDebugOutput(){
        myFile.close();
    }
}