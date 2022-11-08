//
// Created by Carles on 17/10/2022.
//
#pragma once

#include "../openvr/includes/openvr.h"
#include "../includes/debug.hpp"

#include <iostream>
#include <cmath>
#include <vector>


namespace trk {

    struct Vector3{
        float x;
        float y;
        float z;
    };

    class VrSystem{
    private:
        vr::IVRSystem *vrSystem;
        vr::IVRChaperone *chaperone;

        std::vector<uint32_t> trackerIndexes;
        std::vector<uint32_t> baseStationsIndexes;

        Debug debug;

        int trackersDetected;
        int baseStationsDetected;
        float playAreaX;
        float playAreaY;

        vr::HmdVector3_t getPositionFromPose(vr::TrackedDevicePose_t pose);

        //testing functions
        void printPoseToDebug(vr::HmdVector3_t pos);
    public:
        VrSystem(){};
        ~VrSystem(){};

        //api control
        void initVrSystem();
        void shutdownVrSystem();

        //getters & setters
        Vector3 getPlayArea();
        void getPositionFromTracker();
        int getNumberOfTrackers(){return trackersDetected;}
        int getNumberOfBaseStations(){return baseStationsDetected;}
        bool isValidSetUp(int minBaseStations);

        //testing functions
        Vector3 test(float time, int radius);
        int testTrackedDevice();
    };




} // trk

