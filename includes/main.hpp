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
        //api control
        DllExport void startTracking();

        DllExport void stopTracking();

        //getters and setters
        DllExport Vector3 getPlayArea();

        //testing
        DllExport Vector3 getPositionsForTracker(int trackerID);

        DllExport Vector3 testMovement(float t, int r);

        DllExport int getNumberOfTrackers();

        DllExport int test();
    }

}

