#include "IonDrive.hpp"
#include <iostream>
#include <algorithm>

IonDrive::IonDrive(std::string name, double maxFuelCapacity,
                   double payloadCapacity, int maxCrew, double thrusterPower)
    : Spacecraft(name, maxFuelCapacity, payloadCapacity, maxCrew),
      thrusterPower(thrusterPower) {}

double IonDrive::getThrusterPower() const { return thrusterPower; }
void IonDrive::setThrusterPower(double power) {
    if (power < 0) {
        std::cerr << "Error: Thruster power cannot be negative.\n";
        return;
    }
    thrusterPower = power;
}

std::string IonDrive::getType() const { return "Ion Drive"; }

// Slower but very fuel efficient
double IonDrive::getSpeed() const { return 50.0 + (thrusterPower * 0.01); } // km/s

double IonDrive::getFuelEfficiency() const { return 2000000.0 + (thrusterPower * 1000.0); } // km/tonne

double IonDrive::calculateFuelNeeded(double distanceKm) {
    double fuel = distanceKm / getFuelEfficiency();
    return std::min(fuel, getMaxFuelCapacity());
}

void IonDrive::displayInfo() const {
    Spacecraft::displayInfo();
    std::cout << "  Thruster Power     : " << thrusterPower << " kW\n";
}