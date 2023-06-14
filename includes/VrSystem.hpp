//
// Created by Carles on 17/10/2022.
//
#pragma once

#include "../openvr/includes/openvr.h"
#include "../includes/utils.hpp"

#include <cmath>
#include <vector>


namespace trk {
    class VrSystem{
    public:
        VrSystem();
        ~VrSystem() {};

        //api control
        void initVrSystem(int numberOfPlayers, int numberOfBases);
        void shutdownVrSystem();

        //getters & setters
        Vector3 getPlayArea();
        void updatePoses(int size, float* data);
        int getNumberOfTrackers() { return trackersDetected; }
        int getNumberOfBaseStations() { return baseStationsDetected; }
        bool isValidSetUp();

    private:
        int nTrackers = 0;
        int nBaseStations = 0;

        vr::IVRSystem *vrSystem;
        vr::IVRChaperone *chaperone;

        std::vector<uint32_t> trackerIndexes;

        int trackersDetected = 0;
        int baseStationsDetected = 0;
        float playAreaX = 0.0f;
        float playAreaY = 0.0f;

        std::vector<float> getPositionsFromPose(vr::TrackedDevicePose_t poses[]);
    };




} // trk

