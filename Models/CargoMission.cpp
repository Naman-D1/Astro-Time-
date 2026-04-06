#include "CargoMission.hpp"
#include <iostream>
#include <algorithm>
using namespace std;

CargoMission::CargoMission(string missionName,
                           shared_ptr<Spacecraft> spacecraft,
                           shared_ptr<CelestialBody> destination,
                           double cargoWeightTonnes,
                           string cargoType)
    : Mission(missionName, spacecraft, destination),
      cargoWeightTonnes(cargoWeightTonnes), cargoType(cargoType) {}

double      CargoMission::getCargoWeight() const { return cargoWeightTonnes; }
string CargoMission::getCargoType()   const { return cargoType; }

void CargoMission::setCargoWeight(double weight) {
    if (weight < 0) {
        cerr << "Error: Cargo weight cannot be negative.\n";
        return;
    }
    cargoWeightTonnes = weight;
}
void CargoMission::setCargoType(string type) { cargoType = type; }

string CargoMission::getMissionType() const { return "Cargo Mission"; }

// Risk based on destination hazard + how heavy the cargo is
double CargoMission::calculateRiskScore() const {
    double risk = getDestination()->getHazardLevel();
    if (cargoWeightTonnes > getSpacecraft()->getPayloadCapacity() * 0.8)
        risk += 2.0; // carrying near max capacity = riskier
    return min(risk, 10.0);
}

// Cargo missions need minimal crew
int CargoMission::getMinCrewRequired() const { return 2; }

void CargoMission::displaySummary() const {
    Mission::displaySummary();
    cout << "  Cargo Type   : " << cargoType << "\n";
    cout << "  Cargo Weight : " << cargoWeightTonnes << " tonnes\n";
    cout << "====================================\n";
}