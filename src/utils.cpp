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

    vr::HmdMatrix33_t transposeRotation(vr::HmdMatrix34_t mat) {
        vr::HmdMatrix33_t rot = vr::HmdMatrix33_t();
        rot.m[0][0] = mat.m[0][0];
        rot.m[0][1] = mat.m[1][0];
        rot.m[0][2] = mat.m[2][0];

        rot.m[1][0] = mat.m[0][1];
        rot.m[1][1] = mat.m[1][1];
        rot.m[1][2] = mat.m[2][1];

        rot.m[2][0] = mat.m[0][2];
        rot.m[2][1] = mat.m[1][2];
        rot.m[2][2] = mat.m[2][2];
        return  vr::HmdMatrix33_t();
    }

    std::vector<float> getQuaternionFromMatrix(vr::HmdMatrix34_t mat) {
        std::vector<float> quaternion;
        float w, x, y, z;
       //vr::HmdMatrix33_t mat = transposeRotation(m);
        
        w = sqrt( std::max( 0.f, 1 + mat.m[0][0] + mat.m[1][1] + mat.m[2][2] ) ) / 2;
        x = sqrt( std::max( 0.f, 1 + mat.m[0][0] - mat.m[1][1] - mat.m[2][2] ) ) / 2;
        y = sqrt( std::max( 0.f, 1 - mat.m[0][0] + mat.m[1][1] - mat.m[2][2] ) ) / 2;
        z = sqrt( std::max( 0.f, 1 - mat.m[0][0] - mat.m[1][1] + mat.m[2][2] ) ) / 2;
        x = copysign(x, mat.m[2][1] - mat.m[1][2]);
        y = copysign(y, mat.m[0][2] - mat.m[2][0]);
        z = copysign( z, mat.m[1][0] - mat.m[0][1]);
        
        //w = sqrtf(1 + mat.m[0][0] + mat.m[1][1] + mat.m[2][2]);
        //x = (mat.m[2][1] - mat.m[1][2])/ (4 * w);
        //y = (mat.m[0][2] - mat.m[2][0]) / (4 * w);
        //z = (mat.m[1][0] - mat.m[0][1]) / (4 * w);
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