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
        DllExport void startTracking();

        DllExport void stopTracking();
        //TODO some kind of setup functions

        //getters ----------
        DllExport int getNumberOfTrackers() {return app.getNumberOfTrackers();}

        DllExport int getNumberOfBaseStations() {return app.getNumberOfBaseStations();}

        DllExport Vector3 getPlayArea() {return app.getPlayArea();}

        DllExport bool verifyPlayArea(int minBaseStations) {return app.isValidSetUp(minBaseStations);}

        //testing ------------
        DllExport void getPositionsForTracker();

        DllExport Vector3 testMovement(float t, int r);

    }

}

