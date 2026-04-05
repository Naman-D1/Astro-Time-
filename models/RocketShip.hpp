#ifndef ROCKETSHIP_H
#define ROCKETSHIP_H

#include "Spacecraft.hpp"

class RocketShip : public Spacecraft {
private:
    int boosterCount;

public:
    RocketShip(std::string name, double maxFuelCapacity,
               double payloadCapacity, int maxCrew, int boosterCount);

    int getBoosterCount() const;
    void setBoosterCount(int count);

    std::string getType() const override;
    double getSpeed() const override;
    double getFuelEfficiency() const override;
    double calculateFuelNeeded(double distanceKm) override;

    void displayInfo() const override;
};

#endif