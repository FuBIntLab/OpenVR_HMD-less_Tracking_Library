//
// Created by Carles on 17/10/2022.
//

#include "../includes/VrSystem.hpp"

namespace trk {
    //api control
    void VrSystem::initVrSystem() {
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

        trackersDetected = 0;
        //Searches fot trackers in the system
        for (uint32_t index = vr::k_unTrackedDeviceIndex_Hmd; index< vr::k_unMaxTrackedDeviceCount; index++) {
            vr::TrackedDeviceClass trackedClass = vrSystem->GetTrackedDeviceClass(index);
            trackerIndexes[index] = false;
            if(trackedClass == vr::TrackedDeviceClass::TrackedDeviceClass_GenericTracker){
                trackerIndexes[index] = true;
                trackersDetected++;
            }
        }

    }

    void VrSystem::shutdownVrSystem() {
        vr::VR_Shutdown();
    }

    //getters and setters
    Vector3 VrSystem::getPlayArea() {
        return Vector3{playAreaX, 0, playAreaY};
    }

    void VrSystem::getPositionFromTracker(int id) {

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