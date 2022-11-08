//
// Created by Carles on 12/10/2022.
//

#include "../includes/main.hpp"

void trk::startTracking() {
    app.initVrSystem();
}

void trk::stopTracking() {
    app.shutdownVrSystem();
}

void trk::getPositionsForTracker() {
    app.getPositionFromTracker();
}

trk::Vector3 trk::testMovement(float t, int r) {
    return app.test(t,r);
}



