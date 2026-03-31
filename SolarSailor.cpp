#include "SolarSailor.hpp"
#include <iostream>

SolarSailer::SolarSailer(std::string name, double payloadCapacity,
                         int maxCrew, double sailAreaM2, double solarEfficiency)
    : Spacecraft(name, 0.0, payloadCapacity, maxCrew), // no fuel tank!
      sailAreaM2(sailAreaM2), solarEfficiency(solarEfficiency) {}

double SolarSailer::getSailArea() const { return sailAreaM2; }
double SolarSailer::getSolarEfficiency() const { return solarEfficiency; }

void SolarSailer::setSailArea(double area) {
    if (area <= 0) {
        std::cerr << "Error: Sail area must be positive.\n";
        return;
    }
    sailAreaM2 = area;
}
void SolarSailer::setSolarEfficiency(double efficiency) {
    if (efficiency < 0.0 || efficiency > 1.0) {
        std::cerr << "Error: Efficiency must be between 0 and 1.\n";
        return;
    }
    solarEfficiency = efficiency;
}

std::string SolarSailer::getType() const { return "Solar Sailer"; }

// Speed depends on sail size and efficiency
double SolarSailer::getSpeed() const { return (sailAreaM2 * solarEfficiency) / 1000.0; } // km/s

// Infinite fuel efficiency — runs on sunlight!
double SolarSailer::getFuelEfficiency() const { return 99999999.0; }

// Solar sailer needs no fuel
double SolarSailer::calculateFuelNeeded(double distanceKm) { return 0.0; }

void SolarSailer::displayInfo() const {
    Spacecraft::displayInfo();
    std::cout << "  Sail Area          : " << sailAreaM2 << " m²\n";
    std::cout << "  Solar Efficiency   : " << solarEfficiency * 100 << "%\n";
}