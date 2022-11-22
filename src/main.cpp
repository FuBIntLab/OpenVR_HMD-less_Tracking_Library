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
void trk::updatePositions(int size, float *data) {
    app.updatePoses(size, data);
}

int trk::getSize() {
    //return app.getNumberOfTrackers() * 3;
    return 3*sizeof(double);
}



