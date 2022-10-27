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
        vr::IVRChaperone *chaperone;
        bool trackerIndexes[vr::k_unMaxTrackedDeviceCount];
        int trackersDetected;
        float playAreaX;
        float playAreaY;
    public:
        VrSystem(){};
        ~VrSystem(){};

        //api control
        void initVrSystem();
        void shutdownVrSystem();

        //getters & setters
        Vector3 getPlayArea();
        void getPositionFromTracker(int id);
        int getNumberOfTrackers(){return trackersDetected;}

        //testing functions
        Vector3 test(float time, int radius);
        int testTrackedDevice();
    };




} // trk

