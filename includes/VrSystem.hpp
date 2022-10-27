//
// Created by Carles on 17/10/2022.
//
#pragma once

#include "../openvr/includes/openvr.h"
#include <iostream>
#include <cmath>

namespace trk {

    struct Vector3{
        float x;
        float y;
        float z;
    };

    class VrSystem{
        vr::IVRSystem *vrSystem;
        bool trackerIndexes[vr::k_unMaxTrackedDeviceCount];
    public:
        VrSystem(){};
        ~VrSystem(){};

        void initVrSystem();
        void shutdownVrSystem();

        //testing functions
        Vector3 test(float time, int radius);
        int testTrackedDevice();
    };




} // trk

