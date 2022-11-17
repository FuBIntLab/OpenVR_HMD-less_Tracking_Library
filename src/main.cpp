//
// Created by Carles on 12/10/2022.
//

#include "../includes/main.hpp"

void trk::startTracking(int numberOfPlayers, int numberOfBaseStations) {
    app.initVrSystem(numberOfPlayers, numberOfBaseStations);
}

void trk::stopTracking() {
    app.shutdownVrSystem();
}

void trk::getPositionsForTracker() {
    app.updatePoses();
}

/*
trk::Vector3 trk::testMovement(float t, int r) {
    return app.test(t,r);
}
 */



