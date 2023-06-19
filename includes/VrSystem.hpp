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
        void updatePoses(float* data, bool invertAxis, bool flipXZ);
        int getNumberOfTrackers() { return trackersDetected; }
        int getNumberOfBaseStations() { return baseStationsDetected; }

    private:
        int nTrackers = 0;
        int nBaseStations = 0;

        vr::IVRSystem *vrSystem;

        std::vector<uint32_t> trackerIndexes;

        int trackersDetected = 0;
        int baseStationsDetected = 0;
    };




} // trk

