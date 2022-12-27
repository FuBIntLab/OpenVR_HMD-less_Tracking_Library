//
// Created by Carles on 17/10/2022.
//
#pragma once

#include "../openvr/includes/openvr.h"
#include "../includes/utils.hpp"

#include <iostream>
#include <cmath>
#include <vector>


namespace trk {
    class VrSystem{
    private:
        int nTrackers = 0;
        int nBaseStations = 0;

        vr::IVRSystem *vrSystem;
        vr::IVRChaperone *chaperone;

        std::vector<Tracker> trackers;
        std::vector<uint32_t> trackerIndexes;

        int trackersDetected;
        int baseStationsDetected;
        float playAreaX;
        float playAreaY;

        std::vector<float> getPositionsFromPose(vr::TrackedDevicePose_t poses[]);
        std::vector<float> getTransformsAsVector(vr::TrackedDevicePose_t poses[]);

        //testing functions
        void printPoseToDebug(vr::HmdVector3_t pos);
    public:
        VrSystem(){};
        ~VrSystem(){};

        //api control
        void initVrSystem(int numberOfPlayers, int numberOfBases);
        void shutdownVrSystem();

        //getters & setters
        Vector3 getPlayArea();
        void updatePoses(int size, float *data);
        void updatePosesWithRotation(int size, float *data);
        int getNumberOfTrackers(){return trackersDetected;}
        int getNumberOfBaseStations(){return baseStationsDetected;}
        bool isValidSetUp();
        int getSizeOfVector(bool rotation);

        //testing functions
    };




} // trk

