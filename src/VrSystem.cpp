//
// Created by Carles on 17/10/2022.
//

#include "../includes/VrSystem.hpp"

namespace trk {
    //api control
    void VrSystem::initVrSystem() {

        debug.Log("wassup");

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
                baseStationsIndexes.push_back(index);
            }
        }
        std::cout << "hello " << std::endl;
    }

    void VrSystem::shutdownVrSystem() {
        //resetting values and shutting down vrSystem
        trackersDetected = 0;
        trackerIndexes.clear();
        baseStationsIndexes.clear();
        debug.stopDebugOutput();
        vr::VR_Shutdown();
    }

    //getters and setters
    Vector3 VrSystem::getPlayArea() {
        return Vector3{playAreaX, 0, playAreaY};
    }

    void VrSystem::getPositionFromTracker(int id) {

    }

    bool VrSystem::isValidSetUp(int minBaseStations) {
        /*
         * Returns true if the given number of base stations are detected
         */
        if(baseStationsDetected >= minBaseStations){
            return true;
        }
        return false;
    }

    //testing functions
    Vector3 VrSystem::test(float time, int radius) {
        return Vector3{radius* cosf(time), 1.0f, radius* sinf(time)};
    }

    int VrSystem::testTrackedDevice() {
        vr::TrackedDeviceClass  trackedClass = vrSystem->GetTrackedDeviceClass(0);
        if(trackedClass == vr::TrackedDeviceClass::TrackedDeviceClass_HMD) {
            return 1;
        }
        return 0;
    }
} // trk