//
// Created by Carles on 17/10/2022.
//

#include "../includes/VrSystem.hpp"

namespace trk {
    //api control
    VrSystem::VrSystem() {
        vrSystem = nullptr;
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
    /*
    in:
     *data: float array to fill
    */
    void VrSystem::updatePoses(int size, float *data, bool invertX, bool invertZ, bool flipXZ) {
       
        //poses array
        vr::TrackedDevicePose_t poses[vr::k_unMaxTrackedDeviceCount];
        std::vector<float> positions;

        vrSystem->GetDeviceToAbsoluteTrackingPose(vr::TrackingUniverseOrigin::TrackingUniverseRawAndUncalibrated,
                                                  0,
                                                  poses,
                                                  vr::k_unMaxTrackedDeviceCount);

        positions = trk::getPosAndRotation(poses, trackerIndexes, invertX, invertZ, flipXZ);
        memcpy(data, positions.data(), size);
    }
} // trk