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

        DllExport void updatePositions(){ app.updatePoses();};
        //TODO some kind of setup functions

        //getters ----------
        DllExport int getNumberOfTrackers() {return app.getNumberOfTrackers();}

        DllExport int getNumberOfBaseStations() {return app.getNumberOfBaseStations();}

        DllExport void pointerTest(int *size, double **data);
        //DllExport Vector3 testMovement(float t, int r);
        DllExport void freeArray(double **data) { app.freeArray(data);}

    }

}

