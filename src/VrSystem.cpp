//
// Created by Carles on 17/10/2022.
//

#include "../includes/VrSystem.hpp"

namespace trk {
    //api control
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
        /*
         * in:
         *      size: Size of the array to fill
         *      *data: float array to fill
         */
        //poses array
        vr::TrackedDevicePose_t poses[vr::k_unMaxTrackedDeviceCount];
        std::vector<float> positions;

        vrSystem->GetDeviceToAbsoluteTrackingPose(vr::TrackingUniverseOrigin::TrackingUniverseStanding,
                                                  0,
                                                  poses,
                                                  vr::k_unMaxTrackedDeviceCount);

        positions = getPositionsFromPose(poses);
        memcpy(data, positions.data(), size);
    }

    void VrSystem::updatePosesWithRotation(int size, float *data) {
        vr::TrackedDevicePose_t poses[vr::k_unMaxTrackedDeviceCount];
        std::vector<float> transforms;

        vrSystem->GetDeviceToAbsoluteTrackingPose(vr::TrackingUniverseOrigin::TrackingUniverseStanding,
                                                  0,
                                                  poses,
                                                  vr::k_unMaxTrackedDeviceCount);

        transforms = getTransformsAsVector(poses);
        memcpy(data, transforms.data(), size);
    }

    std::vector<float> VrSystem::getPositionsFromPose(vr::TrackedDevicePose_t *poses) {
        std::vector<float> trackerPositions;
        for(uint32_t i : trackerIndexes){
            vr::HmdMatrix34_t mat = poses[i].mDeviceToAbsoluteTracking;
            trackerPositions.push_back(mat.m[0][3]);
            trackerPositions.push_back(mat.m[1][3]);
            trackerPositions.push_back(mat.m[2][3]);
        }
        return trackerPositions;
    }

    std::vector<float> VrSystem::getTransformsAsVector(vr::TrackedDevicePose_t *poses) {
        std::vector<float> transformsVector;
        for (uint32_t i : trackerIndexes) {
            vr::HmdMatrix34_t mat = poses[i].mDeviceToAbsoluteTracking;
            for (int j = 0; j < 4; ++j) {
                for (int k = 0; k < 3; ++k) {
                    transformsVector.push_back(mat.m[k][j]);
                }
            }
        }
        return transformsVector;
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

    int VrSystem::getSizeOfVector(bool rotation = false) {
        if(rotation){
            //if rotation is enabled pass whole transform matrix to unity
            return nTrackers * 12 * sizeof(float); //numberOfTrackers * rigidTransformMatrixSize * sizeOfFloat
        }
        return nTrackers * 3 * sizeof(float); //numberOfTrackers * positionVector * sizeofFloat
    }

    //testing functions
    void VrSystem::printPoseToDebug(vr::HmdVector3_t pos) {
        //TODO: Print position of all trackers with ids to identify them
        debugPrint("x: "+ std::to_string(pos.v[0])+
        " y: "+ std::to_string(pos.v[1])+
        " z: "+ std::to_string(pos.v[2])
        );

    }


} // trk