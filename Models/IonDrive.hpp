#ifndef IONDRIVE_H
#define IONDRIVE_H
using namespace std;

#include "Spacecraft.hpp"

class IonDrive : public Spacecraft {
private:
    double thrusterPower; // in kW

public:
    IonDrive(string name, double maxFuelCapacity,
             double payloadCapacity, int maxCrew, double thrusterPower);

    double getThrusterPower() const;
    void setThrusterPower(double power);

    string getType() const override;
    double getSpeed() const override;
    double getFuelEfficiency() const override;
    double calculateFuelNeeded(double distanceKm) override;

    void displayInfo() const override;
};

#endif