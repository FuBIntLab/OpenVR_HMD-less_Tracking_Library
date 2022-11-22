//
// Created by Carles on 18/11/2022.
//
#include "../includes/utils.hpp"

namespace trk{
    Vector3 Vector3::zero() {
        return Vector3{0,0,0};
    }

    void Tracker::setPosition(float x, float y, float z) {
        pos = Vector3{x,y,z};
    }

    void debugPrint(std::string msg){
    std::string tag = "TRACKING: " + msg;
    OutputDebugString(tag.c_str());
    }
}