//
// Created by Carles on 15/11/2022.
//
#pragma once

#include <string>
#include <vector>
#include "../openvr/includes/openvr.h"

namespace trk{
    struct Vector3{
        float x;
        float y;
        float z;

        static Vector3 zero();
    };
    std::vector<float> getQuaternionFromMatrix(vr::HmdMatrix34_t mat, bool invertAxis, bool flipXZ);
    std::vector<float> getPosAndRotation(vr::TrackedDevicePose_t* poses, std::vector<uint32_t> trackerIndexes, bool invertAxis, bool flipXZ); 
}