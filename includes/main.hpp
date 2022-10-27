//
// Created by Carles on 12/10/2022.
//

//prevents double declaration
#pragma once

#include <iostream>
#include <vector>
#include "../includes/VrSystem.hpp"
#include "../Unity/IUnityInterface.h"

#define DllExport __declspec(dllexport)
namespace trk {
    //VrSystem object
    VrSystem app{};

    extern "C" {
        DllExport void startTracking();

        DllExport void stopTracking();

        DllExport Vector3 getPositionsForTracker(int trackerID);

        DllExport Vector3 testMovement(float t, int r);

        DllExport int testTrackedDeviceIndex();

        DllExport int test();
    }

}

