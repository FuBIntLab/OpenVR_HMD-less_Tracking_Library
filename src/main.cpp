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

trk::Vector3 trk::getPositionsForTracker(int trackerID) {
    return Vector3{(float)trackerID,0.0,0.0};
}

trk::Vector3 trk::testMovement(float t, int r) {
    return app.test(t,r);
}



