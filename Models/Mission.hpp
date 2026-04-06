#ifndef MISSION_H
#define MISSION_H

#include <string>
#include <memory>
#include "Spacecraft.hpp"
#include "CelestialBody.hpp"
using namespace std;

class Mission {
private:
    string missionName;
    shared_ptr<Spacecraft>    spacecraft;
    shared_ptr<CelestialBody> destination;
    string status; // "Planned", "Ongoing", "Completed", "Aborted"

public:
    Mission(string missionName,
            shared_ptr<Spacecraft> spacecraft,
            shared_ptr<CelestialBody> destination);

    virtual ~Mission() = default;

    // Getters
    string getMissionName() const;
    string getStatus() const;
    shared_ptr<Spacecraft>    getSpacecraft() const;
    shared_ptr<CelestialBody> getDestination() const;

    // Setters
    void setStatus(string status);
    void setMissionName(string name);

    // Prediction methods (shared by all mission types)
    double calculateTravelTime() const;   // in days
    double calculateFuelNeeded() const;   // in tonnes

    // Pure virtual methods (each mission type handles differently)
    virtual string getMissionType() const = 0;
    virtual double      calculateRiskScore() const = 0;
    virtual int         getMinCrewRequired() const = 0;

    // Virtual display
    virtual void displaySummary() const;
};

#endif