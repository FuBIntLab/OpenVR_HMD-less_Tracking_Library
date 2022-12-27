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
void trk::updatePositions(int size, float *data, bool rotation = false) {
    if(rotation){
        app.updatePoses(size, data);
    }else{
        app.updatePosesWithRotation(size,data);
    }

}

int trk::getSize(bool rotation) {
    return app.getSizeOfVector(rotation);
}



