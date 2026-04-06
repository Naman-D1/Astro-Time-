#ifndef ROCKETSHIP_H
#define ROCKETSHIP_H

#include "Spacecraft.hpp"
using namespace std;

class RocketShip : public Spacecraft {
private:
    int boosterCount;

public:
    RocketShip(string name, double maxFuelCapacity,
               double payloadCapacity, int maxCrew, int boosterCount);

    int getBoosterCount() const;
    void setBoosterCount(int count);

    string getType() const override;
    double getSpeed() const override;
    double getFuelEfficiency() const override;
    double calculateFuelNeeded(double distanceKm) override;

    void displayInfo() const override;
};

#endif