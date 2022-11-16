//
// Created by Carles on 17/10/2022.
//

#include "../includes/VrSystem.hpp"

namespace trk {
    //api control
    void VrSystem::initVrSystem(int numberOfPlayers, int numberOfBases) {
        debug.Log("VrSystem ON:");
        nTrackers = numberOfPlayers;
        nBaseStations = numberOfBases;

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

        debug.Log("Play Area: ("+ std::to_string(playAreaX) + ", " + std::to_string(playAreaY) +"&d ) ");

        //Searches fot trackers in the system from hmd 0 to maxTrackedDeviceCount and saves the indexes to a vector
        for (uint32_t index = vr::k_unTrackedDeviceIndex_Hmd; index< vr::k_unMaxTrackedDeviceCount; index++) {
            vr::TrackedDeviceClass trackedClass = vrSystem->GetTrackedDeviceClass(index);
            if(trackedClass == vr::TrackedDeviceClass::TrackedDeviceClass_GenericTracker){
                Tracker currentTracker{index,Vector3::zero()};
                trackers.push_back(currentTracker);

                //temp----
                trackersDetected++;
                trackerIndexes.push_back(index);
                //--------

            }
            if(trackedClass == vr::TrackedDeviceClass::TrackedDeviceClass_TrackingReference){
                baseStationsDetected++;
            }
        }
        debug.Log("Tracker indexes:");
        for(uint32_t i : trackerIndexes){
            debug.Log("\t" + std::to_string(i));
        }
    }

    void VrSystem::shutdownVrSystem() {
        //resetting values and shutting down vrSystem
        nTrackers = 0;
        nBaseStations = 0;
        trackersDetected = 0;
        baseStationsDetected = 0;
        trackers.clear();

        //temp ---
        trackerIndexes.clear();
        //--------

        debug.stopDebugOutput();
        vr::VR_Shutdown();
    }

    //getters and setters
    Vector3 VrSystem::getPlayArea() {
        return Vector3{playAreaX, 0, playAreaY};
    }

    void VrSystem::updatePositions() {
        vr::TrackedDevicePose_t pose;
        vr::VRControllerState_t controllerState;
        vr::HmdVector3_t position;

        vrSystem->GetControllerStateWithPose(vr::TrackingUniverseStanding,
                                             trackerIndexes[0],
                                             &controllerState,
                                             sizeof(controllerState),
                                             &pose);

        position = getPositionFromPose(pose);
        printPoseToDebug(position);

        if(pose.bPoseIsValid){
            debug.Log("Valid Pose");
        }

    }

    bool VrSystem::isValidSetUp(int minBaseStations) {
        /*
         * Returns true if the given number of base stations are detected
         */
        if(baseStationsDetected == nBaseStations && trackersDetected == nTrackers){
            return true;
        }
        debug.Log("Check plugin configuration: Number of trackers or base stations are different from detected");
        return false;
    }

    vr::HmdVector3_t VrSystem::getPositionFromPose(vr::TrackedDevicePose_t pose) {
        vr::HmdMatrix34_t mat = pose.mDeviceToAbsoluteTracking;

        vr::HmdVector3_t vec;

        vec.v[0] = mat.m[0][3];
        vec.v[1] = mat.m[1][3];
        vec.v[2] = mat.m[2][3];

        return vec;
    }

    //testing functions
    void VrSystem::printPoseToDebug(vr::HmdVector3_t pos) {
        debug.Log("x: "+ std::to_string(pos.v[0])+
        " y: "+ std::to_string(pos.v[1])+
        " z: "+ std::to_string(pos.v[2])
        );

    }

    Vector3 VrSystem::test(float time, int radius) {
        return Vector3{radius* cosf(time), 1.0f, radius* sinf(time)};
    }


} // trk