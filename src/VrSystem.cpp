//
// Created by Carles on 17/10/2022.
//

#include "../includes/VrSystem.hpp"

namespace trk {
    //api control
    void VrSystem::initVrSystem(int numberOfPlayers, int numberOfBases) {
        debugPrint("VrSystem ON:");
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

        debugPrint("Play Area: ("+ std::to_string(playAreaX) + " , " + std::to_string(playAreaY) +") ");

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
        debugPrint("Tracker indexes:");
        for(uint32_t i : trackerIndexes){
            debugPrint("\t" + std::to_string(i));
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
        vr::VR_Shutdown();
    }

    //getters and setters
    Vector3 VrSystem::getPlayArea() {
        return Vector3{playAreaX, 0, playAreaY};
    }

    void VrSystem::updatePoses(int size, float *data) {
        std::vector<float> testing = {1.0f,2.0f,3.0f};

        vr::TrackedDevicePose_t poses[vr::k_unMaxTrackedDeviceCount];
        vr::VRControllerState_t controllerState;
        vr::HmdVector3_t position;
        //TODO: Get position of all trackers

        vrSystem->GetDeviceToAbsoluteTrackingPose(vr::TrackingUniverseOrigin::TrackingUniverseStanding,
                                                  0,
                                                  poses,
                                                  vr::k_unMaxTrackedDeviceCount);


        position = getPositionFromPose(poses[1]);
        printPoseToDebug(position);
        memcpy(data, position.v, size);
    }

    bool VrSystem::isValidSetUp() {
        /*
         * Returns true if the given number of base stations are detected
         */
        if(baseStationsDetected == nBaseStations && trackersDetected == nTrackers){
            return true;
        }
        debugPrint("Check plugin configuration: Number of trackers or base stations are different from detected");
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
        //TODO: Print position of all trackers with ids to identify them
        debugPrint("x: "+ std::to_string(pos.v[0])+
        " y: "+ std::to_string(pos.v[1])+
        " z: "+ std::to_string(pos.v[2])
        );

    }

    Vector3 VrSystem::test(float time, int radius) {
        return Vector3{radius* cosf(time), 1.0f, radius* sinf(time)};
    }

    void VrSystem::testPointers(int size, double *data) {
        std::vector<double> testing = {1.0f,2.0f,3.0f};

        memcpy(data, testing.data(), size);
    }


} // trk