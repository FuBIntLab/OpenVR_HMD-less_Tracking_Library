//
// Created by Carles on 15/11/2022.
//
#pragma once

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
        void updatePosition(Vector3 newPos);

    };

    void debugPrint(std::string msg);
}