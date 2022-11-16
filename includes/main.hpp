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

        DllExport void updatePositions(){};
        //TODO some kind of setup functions

        //getters ----------
        DllExport int getNumberOfTrackers() {return app.getNumberOfTrackers();}

        DllExport int getNumberOfBaseStations() {return app.getNumberOfBaseStations();}

        DllExport Vector3 getPlayArea() {return app.getPlayArea();}

        DllExport bool verifySetup() {return app.isValidSetUp();}

        //testing ------------
        DllExport void getPositionsForTracker();

        //DllExport Vector3 testMovement(float t, int r);


    }

}

