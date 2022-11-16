//
// Created by Carles on 15/11/2022.
//
#pragma once

namespace trk{
    struct Vector3{
        float x;
        float y;
        float z;
    };

    struct Tracker{
        uint32_t id;
        Vector3 pos;
    };
}