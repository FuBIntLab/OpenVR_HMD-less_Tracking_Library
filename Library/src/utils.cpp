//
// Created by Carles on 18/11/2022.
//
#include "../includes/utils.hpp"
#include <algorithm>
#include <math.h>

namespace trk{
    Vector3 Vector3::zero() {
        return Vector3{0,0,0};
    }

    std::vector<float> getQuaternionFromMatrix(vr::HmdMatrix34_t mat) {
        std::vector<float> quaternion;
        float w, x, y, z;
        
        w = sqrt( std::max( 0.f, 1 + mat.m[0][0] + mat.m[1][1] + mat.m[2][2] ) ) / 2;
        x = sqrt( std::max( 0.f, 1 + mat.m[0][0] - mat.m[1][1] - mat.m[2][2] ) ) / 2;
        y = sqrt( std::max( 0.f, 1 - mat.m[0][0] + mat.m[1][1] - mat.m[2][2] ) ) / 2;
        z = sqrt( std::max( 0.f, 1 - mat.m[0][0] - mat.m[1][1] + mat.m[2][2] ) ) / 2;
        x = copysign(x, mat.m[2][1] - mat.m[1][2]);
        y = copysign(y, mat.m[0][2] - mat.m[2][0]);
        z = copysign( z, mat.m[1][0] - mat.m[0][1]);
        
        quaternion.push_back(x);
        quaternion.push_back(y);
        quaternion.push_back(z);
        quaternion.push_back(w);
        return quaternion;
    }

    std::vector<float> getPosAndRotation(vr::TrackedDevicePose_t* poses, std::vector<uint32_t> trackerIndexes, bool invertX, bool invertZ, bool flipXZ ) {
        std::vector<float> positionsQuaternions;
        for (uint32_t i : trackerIndexes) {
            vr::HmdMatrix34_t mat = poses[i].mDeviceToAbsoluteTracking;
            //apply bools
            if (invertX) {
                mat.m[0][0] = -mat.m[0][0];
                mat.m[0][1] = -mat.m[0][1];
                mat.m[0][2] = -mat.m[0][2];
                mat.m[0][3] = -mat.m[0][3];
            }
            if (invertZ) {
                mat.m[2][0] = -mat.m[2][0];
                mat.m[2][1] = -mat.m[2][1];
                mat.m[2][2] = -mat.m[2][2];
                mat.m[2][3] = -mat.m[2][3];
            }
            if (flipXZ) {
                float tempXx, tempXy, tempXz, tempXw;
                tempXx = mat.m[0][0];
                tempXy = mat.m[0][1];
                tempXz = mat.m[0][2];
                tempXw = mat.m[0][3];

                mat.m[0][0] = mat.m[2][0];
                mat.m[0][1] = mat.m[2][1];
                mat.m[0][2] = mat.m[2][2];
                mat.m[0][3] = mat.m[2][3];

                mat.m[2][0] = tempXx;
                mat.m[2][1] = tempXy;
                mat.m[2][2] = tempXz;
                mat.m[2][3] = tempXw;
            }

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