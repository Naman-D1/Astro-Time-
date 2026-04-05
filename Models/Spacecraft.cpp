#include "Spacecraft.hpp"
#include "../Services/SpaceException.hpp"
#include <iostream>

Spacecraft::Spacecraft(std::string name, double maxFuelCapacity,
                       double payloadCapacity, int maxCrew)
    : name(name), maxFuelCapacity(maxFuelCapacity),
      currentFuel(maxFuelCapacity), // start full
      payloadCapacity(payloadCapacity), maxCrew(maxCrew) {}

// Getters
std::string Spacecraft::getName() const { return name; }
double Spacecraft::getMaxFuelCapacity() const { return maxFuelCapacity; }
double Spacecraft::getCurrentFuel() const { return currentFuel; }
double Spacecraft::getPayloadCapacity() const { return payloadCapacity; }
int    Spacecraft::getMaxCrew() const { return maxCrew; }

// Setters
void Spacecraft::setName(std::string name) { this->name = name; }
void Spacecraft::setCurrentFuel(double fuel) {
    /*if (fuel < 0 || fuel > maxFuelCapacity) {
        std::cerr << "Error: Invalid fuel amount.\n";
        return;
    }
    this->currentFuel = fuel;*/

     if (fuel < 0)
        throw InvalidFuelException("Fuel cannot be negative. Got: " + std::to_string(fuel));
    if (fuel > maxFuelCapacity)
        throw InvalidFuelException("Fuel exceeds tank capacity of " + std::to_string(maxFuelCapacity) + " tonnes.");
    this->currentFuel = fuel;
    }

void Spacecraft::setMaxCrew(int crew) {
 if (crew < 0)
      throw InvalidCrewException("Crew count cannot be negative. Got: " + std::to_string(crew));
      this->maxCrew = crew;
}

void Spacecraft::setPayloadCapacity(double capacity) {
    if (capacity < 0) {
        std::cerr << "Error: Payload capacity cannot be negative.\n";
        return;
    }
    this->payloadCapacity = capacity;
}

void Spacecraft::displayInfo() const {
    std::cout << "[ " << getType() << " ] " << name << "\n";
    std::cout << "  Speed              : " << getSpeed() << " km/s\n";
    std::cout << "  Fuel Capacity      : " << maxFuelCapacity << " tonnes\n";
    std::cout << "  Current Fuel       : " << currentFuel << " tonnes\n";
    std::cout << "  Payload Capacity   : " << payloadCapacity << " tonnes\n";
    std::cout << "  Max Crew           : " << maxCrew << "\n";
    std::cout << "  Fuel Efficiency    : " << getFuelEfficiency() << " km/tonne\n";
}