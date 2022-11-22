//
// Created by Carles on 15/11/2022.
//
#pragma once

#include <windows.h>
#include <debugapi.h>
#include <string>

namespace trk{
    struct Vector3{
        float x;
        float y;
        float z;

        static Vector3 zero();
    };

    struct Tracker{
        uint32_t id;
        Vector3 pos;
        void setPosition(float x, float y, float z);

    };

    void debugPrint(std::string msg);
}