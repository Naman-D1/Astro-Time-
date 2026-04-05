#ifndef SPACESTATION_H
#define SPACESTATION_H

#include "CelestialBody.hpp"

class SpaceStation : public CelestialBody {
private:
    int crewCapacity;
    bool isOperational;
    std::string orbitingBody; // e.g. "Earth", "Moon"

public:
    SpaceStation(std::string name, double distanceFromEarth, double gravity,
                 std::string description, int crewCapacity,
                 bool isOperational, std::string orbitingBody);

    // Getters
    int getCrewCapacity() const;
    bool getIsOperational() const;
    std::string getOrbitingBody() const;

    // Setters
    void setCrewCapacity(int capacity);
    void setIsOperational(bool operational);
    void setOrbitingBody(std::string body);

    // Implementing pure virtual methods
    std::string getType() const override;
    double getHazardLevel() const override;

    // Overriding displayInfo
    void displayInfo() const override;
};

#endif