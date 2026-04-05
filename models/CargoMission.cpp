#include "CargoMission.hpp"
#include <iostream>
#include <algorithm>

CargoMission::CargoMission(std::string missionName,
                           std::shared_ptr<Spacecraft> spacecraft,
                           std::shared_ptr<CelestialBody> destination,
                           double cargoWeightTonnes,
                           std::string cargoType)
    : Mission(missionName, spacecraft, destination),
      cargoWeightTonnes(cargoWeightTonnes), cargoType(cargoType) {}

double      CargoMission::getCargoWeight() const { return cargoWeightTonnes; }
std::string CargoMission::getCargoType()   const { return cargoType; }

void CargoMission::setCargoWeight(double weight) {
    if (weight < 0) {
        std::cerr << "Error: Cargo weight cannot be negative.\n";
        return;
    }
    cargoWeightTonnes = weight;
}
void CargoMission::setCargoType(std::string type) { cargoType = type; }

std::string CargoMission::getMissionType() const { return "Cargo Mission"; }

// Risk based on destination hazard + how heavy the cargo is
double CargoMission::calculateRiskScore() const {
    double risk = getDestination()->getHazardLevel();
    if (cargoWeightTonnes > getSpacecraft()->getPayloadCapacity() * 0.8)
        risk += 2.0; // carrying near max capacity = riskier
    return std::min(risk, 10.0);
}

// Cargo missions need minimal crew
int CargoMission::getMinCrewRequired() const { return 2; }

void CargoMission::displaySummary() const {
    Mission::displaySummary();
    std::cout << "  Cargo Type   : " << cargoType << "\n";
    std::cout << "  Cargo Weight : " << cargoWeightTonnes << " tonnes\n";
    std::cout << "====================================\n";
}