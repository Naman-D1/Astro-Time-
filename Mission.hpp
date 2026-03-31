#ifndef MISSION_H
#define MISSION_H

#include <string>
#include <memory>
#include "Spacecraft.hpp"
#include "CelestialBody.hpp"

class Mission {
private:
    std::string missionName;
    std::shared_ptr<Spacecraft>    spacecraft;
    std::shared_ptr<CelestialBody> destination;
    std::string status; // "Planned", "Ongoing", "Completed", "Aborted"

public:
    Mission(std::string missionName,
            std::shared_ptr<Spacecraft> spacecraft,
            std::shared_ptr<CelestialBody> destination);

    virtual ~Mission() = default;

    // Getters
    std::string getMissionName() const;
    std::string getStatus() const;
    std::shared_ptr<Spacecraft>    getSpacecraft() const;
    std::shared_ptr<CelestialBody> getDestination() const;

    // Setters
    void setStatus(std::string status);
    void setMissionName(std::string name);

    // Prediction methods (shared by all mission types)
    double calculateTravelTime() const;   // in days
    double calculateFuelNeeded() const;   // in tonnes

    // Pure virtual methods (each mission type handles differently)
    virtual std::string getMissionType() const = 0;
    virtual double      calculateRiskScore() const = 0;
    virtual int         getMinCrewRequired() const = 0;

    // Virtual display
    virtual void displaySummary() const;
};

#endif