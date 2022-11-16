//
// Created by Carles on 15/11/2022.
//
#pragma once

namespace trk{
    struct Vector3{
        float x;
        float y;
        float z;

        static Vector3 zero(){
            return Vector3{0,0,0};
        };
    };

    struct Tracker{
        uint32_t id;
        Vector3 pos;
        void updatePosition(Vector3 newPos){
            pos = newPos;
        }
    };
}