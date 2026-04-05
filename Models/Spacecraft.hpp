#ifndef SPACECRAFT_H
#define SPACECRAFT_H

#include <string>

class Spacecraft {
private:
    std::string name;
    double maxFuelCapacity;  // in tonnes
    double currentFuel;      // in tonnes
    double payloadCapacity;  // in tonnes
    int    maxCrew;

public:
    Spacecraft(std::string name, double maxFuelCapacity,
               double payloadCapacity, int maxCrew);

    virtual ~Spacecraft() = default;

    // Getters
    std::string getName() const;
    double getMaxFuelCapacity() const;
    double getCurrentFuel() const;
    double getPayloadCapacity() const;
    int    getMaxCrew() const;

    // Setters
    void setName(std::string name);
    void setCurrentFuel(double fuel);
    void setPayloadCapacity(double capacity);
    void setMaxCrew(int crew);

    // Pure virtual methods (makes this abstract)
    virtual std::string getType() const = 0;
    virtual double getSpeed() const = 0;                        // in km/s
    virtual double getFuelEfficiency() const = 0;               // km per tonne of fuel
    virtual double calculateFuelNeeded(double distanceKm) = 0;  // in tonnes

    // Regular virtual
    virtual void displayInfo() const;
};

#endif