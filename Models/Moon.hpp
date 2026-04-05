#ifndef MOON_H
#define MOON_H

#include "CelestialBody.hpp"

class Moon : public CelestialBody {
private:
    std::string parentPlanet;
    bool hasIce; // some moons like Europa have subsurface ice

public:
    Moon(std::string name, double distanceFromEarth, double gravity,
         std::string description, std::string parentPlanet, bool hasIce);

    // Getters
    std::string getParentPlanet() const;
    bool getHasIce() const;

    // Setters
    void setParentPlanet(std::string parentPlanet);
    void setHasIce(bool hasIce);

    // Implementing pure virtual methods
    std::string getType() const override;
    double getHazardLevel() const override;

    // Overriding displayInfo
    void displayInfo() const override;
};

#endif