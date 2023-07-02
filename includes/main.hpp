//
// Created by Carles on 12/10/2022.
//

//prevents double declaration
#pragma once

#include <iostream>
#include <vector>
#include "../includes/VrSystem.hpp"

#define DllExport __declspec(dllexport)

namespace trk {
    //VrSystem object
    VrSystem app{};

    extern "C" {
        //api control --------------
        DllExport void startTracking(int numberOfPlayers, int numberOfBaseStations);

        DllExport void stopTracking();

        DllExport void updatePositions(int size, float *data, bool invertX, bool invertZ, bool flipXZ);

        //getters ----------
        DllExport int getNumberOfTrackers();

        DllExport int getNumberOfBaseStations();

    }

}

