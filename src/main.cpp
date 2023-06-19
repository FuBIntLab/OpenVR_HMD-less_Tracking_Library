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

int trk::getNumberOfBaseStations() {
    return app.getNumberOfBaseStations();
}

int trk::getNumberOfTrackers() {
    return app.getNumberOfTrackers();
}
void trk::updatePositions(float *data, bool invertAxis, bool flipXZ) {
    app.updatePoses(data, invertAxis, flipXZ);
}




