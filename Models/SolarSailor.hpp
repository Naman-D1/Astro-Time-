#ifndef SOLARSAILER_H
#define SOLARSAILER_H

#include "Spacecraft.hpp"

class SolarSailer : public Spacecraft {
private:
    double sailAreaM2;       // sail area in m²
    double solarEfficiency;  // 0.0 to 1.0

public:
    SolarSailer(std::string name, double payloadCapacity,
                int maxCrew, double sailAreaM2, double solarEfficiency);

    double getSailArea() const;
    double getSolarEfficiency() const;
    void setSailArea(double area);
    void setSolarEfficiency(double efficiency);

    std::string getType() const override;
    double getSpeed() const override;
    double getFuelEfficiency() const override;
    double calculateFuelNeeded(double distanceKm) override;

    void displayInfo() const override;
};

#endif