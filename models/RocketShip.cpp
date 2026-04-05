#include "RocketShip.hpp"
#include <iostream>
#include <algorithm>

RocketShip::RocketShip(std::string name, double maxFuelCapacity,
                       double payloadCapacity, int maxCrew, int boosterCount)
    : Spacecraft(name, maxFuelCapacity, payloadCapacity, maxCrew),
      boosterCount(boosterCount) {}

int RocketShip::getBoosterCount() const { return boosterCount; }
void RocketShip::setBoosterCount(int count) {
    if (count < 0) {
        std::cerr << "Error: Booster count cannot be negative.\n";
        return;
    }
    boosterCount = count;
}

std::string RocketShip::getType() const { return "Rocket Ship"; }

// Fast but guzzles fuel
double RocketShip::getSpeed() const { return 30.0 + (boosterCount * 5.0); } // km/s

// More boosters = slightly less efficient
double RocketShip::getFuelEfficiency() const { return 500000.0 - (boosterCount * 20000.0); } // km/tonne

double RocketShip::calculateFuelNeeded(double distanceKm) {
    double fuel = distanceKm / getFuelEfficiency();
    return std::min(fuel, getMaxFuelCapacity());
}

void RocketShip::displayInfo() const {
    Spacecraft::displayInfo();
    std::cout << "  Boosters           : " << boosterCount << "\n";
}