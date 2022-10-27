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
    return Vector3{1.3,1.3,1.3};
}

trk::Vector3 trk::testMovement(float t, int r) {
    return app.test(t,r);
}

int trk::testTrackedDeviceIndex() {
    return app.testTrackedDevice();
}

int trk::test() {
    return 420;
}

