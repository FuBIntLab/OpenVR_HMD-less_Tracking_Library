//
// Created by Carles on 18/11/2022.
//
#include "../includes/utils.hpp"

namespace trk{
    Vector3 Vector3::zero() {
        return Vector3{0,0,0};
    }

    std::vector<float> getQuaternionFromMatrix(vr::HmdMatrix34_t mat) {
        std::vector<float> quaternion;
        float w, x, y, z;
        w = sqrtf(1 + mat.m[0][0] + mat.m[1][1] + mat.m[2][2]);
        x = (mat.m[2][1] - mat.m[1][2])/ (4 * w);
        y = (mat.m[0][2] - mat.m[2][0]) / (4 * w);
        z = (mat.m[1][0] - mat.m[0][1]) / (4 * w);
        quaternion.push_back(x);
        quaternion.push_back(y);
        quaternion.push_back(z);
        quaternion.push_back(w);
        return quaternion;
    }

    std::vector<float> getPosAndRotation(vr::TrackedDevicePose_t* poses, std::vector<uint32_t> trackerIndexes) {
        std::vector<float> positionsQuaternions;
        for (uint32_t i : trackerIndexes) {
            vr::HmdMatrix34_t mat = poses[i].mDeviceToAbsoluteTracking;
            std::vector<float> quat = getQuaternionFromMatrix(mat);
            positionsQuaternions.push_back(mat.m[0][3]);
            positionsQuaternions.push_back(mat.m[1][3]);
            positionsQuaternions.push_back(mat.m[2][3]);
            positionsQuaternions.push_back(quat[0]);
            positionsQuaternions.push_back(quat[1]);
            positionsQuaternions.push_back(quat[2]);
            positionsQuaternions.push_back(quat[3]);
        }
        return positionsQuaternions;
    }
}