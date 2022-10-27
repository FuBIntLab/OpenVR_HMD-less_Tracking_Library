//
// Created by Carles on 17/10/2022.
//

#include "../includes/VrSystem.hpp"

namespace trk {

    void VrSystem::initVrSystem() {
        vr::HmdError initErr;
        vrSystem = vr::VR_Init(
                &initErr,
                vr::EVRApplicationType::VRApplication_Background
                );
        if(vrSystem == NULL){
            return;
        }

        //Searches fot trackers in the system
        for (uint32_t index = vr::k_unTrackedDeviceIndex_Hmd; index< vr::k_unMaxTrackedDeviceCount; index++) {
            vr::TrackedDeviceClass trackedClass = vrSystem->GetTrackedDeviceClass(index);
            trackerIndexes[index] = false;
            if(trackedClass == vr::TrackedDeviceClass::TrackedDeviceClass_GenericTracker){
                trackerIndexes[index] = true;
            }
        }

    }

    void VrSystem::shutdownVrSystem() {
        vr::VR_Shutdown();
    }

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