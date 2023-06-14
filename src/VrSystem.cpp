//
// Created by Carles on 17/10/2022.
//

#include "../includes/VrSystem.hpp"

namespace trk {
    //api control
    VrSystem::VrSystem() {
        vrSystem = nullptr;
        chaperone = nullptr;
    }

    void VrSystem::initVrSystem(int numberOfPlayers, int numberOfBases) {
        nTrackers = numberOfPlayers;
        nBaseStations = numberOfBases;

        //turn on the OpenVR application
        vr::HmdError initErr;
        vrSystem = vr::VR_Init(
                &initErr,
                vr::EVRApplicationType::VRApplication_Background
                );
        if(vrSystem == NULL){
            return;
        }

        chaperone = vr::VRChaperone();
        chaperone->GetPlayAreaSize(&playAreaX, &playAreaY);

        //Searches fot trackers in the system from hmd 0 to maxTrackedDeviceCount and saves the indexes to a vector
        for (uint32_t index = vr::k_unTrackedDeviceIndex_Hmd; index< vr::k_unMaxTrackedDeviceCount; index++) {
            vr::TrackedDeviceClass trackedClass = vrSystem->GetTrackedDeviceClass(index);
            if(trackedClass == vr::TrackedDeviceClass::TrackedDeviceClass_GenericTracker){
                trackersDetected++;
                trackerIndexes.push_back(index);
            }
            if(trackedClass == vr::TrackedDeviceClass::TrackedDeviceClass_TrackingReference){
                baseStationsDetected++;
            }
        }
    }

    void VrSystem::shutdownVrSystem() {
        //resetting values and shutting down vrSystem
        nTrackers = 0;
        nBaseStations = 0;
        trackersDetected = 0;
        baseStationsDetected = 0;
        trackerIndexes.clear();
        //--------
        vr::VR_Shutdown();
    }

    //getters and setters

    Vector3 VrSystem::getPlayArea() {
        return Vector3{playAreaX, 0, playAreaY};
    }

    /*
    in:
     size: Size of the array to fill
     *data: float array to fill
    */
    void VrSystem::updatePoses(int size, float *data) {
       
        //poses array
        vr::TrackedDevicePose_t poses[vr::k_unMaxTrackedDeviceCount];
        std::vector<float> positions;

        vrSystem->GetDeviceToAbsoluteTrackingPose(vr::TrackingUniverseOrigin::TrackingUniverseRawAndUncalibrated,
                                                  0,
                                                  poses,
                                                  vr::k_unMaxTrackedDeviceCount);

        positions = trk::getPosAndRotation(poses, trackerIndexes);
        memcpy(data, positions.data(), size);
    }

    std::vector<float> VrSystem::getPositionsFromPose(vr::TrackedDevicePose_t poses[]) {
        std::vector<float> trackerPositions;
        for(uint32_t i : trackerIndexes){
            vr::HmdMatrix34_t mat = poses[i].mDeviceToAbsoluteTracking;
            trackerPositions.push_back(mat.m[0][3]);
            trackerPositions.push_back(mat.m[1][3]);
            trackerPositions.push_back(mat.m[2][3]);
        }
        return trackerPositions;
    }

    bool VrSystem::isValidSetUp() {
        /*
         * Returns true if the given number of base stations are detected
         */
        if(baseStationsDetected == nBaseStations && trackersDetected == nTrackers){
            return true;
        }
        
        return false;
    }
} // trk