#ifndef CREWMISSION_H
#define CREWMISSION_H

#include "Mission.hpp"

class CrewMission : public Mission {
private:
    int    crewCount;
    bool   hasLifeSupport;
    int    missionDurationDays;

public:
    CrewMission(std::string missionName,
                std::shared_ptr<Spacecraft> spacecraft,
                std::shared_ptr<CelestialBody> destination,
                int crewCount,
                bool hasLifeSupport,
                int missionDurationDays);

    // Getters
    int  getCrewCount() const;
    bool getHasLifeSupport() const;
    int  getMissionDurationDays() const;

    // Setters
    void setCrewCount(int count);
    void setHasLifeSupport(bool support);
    void setMissionDurationDays(int days);

    // Overrides
    std::string getMissionType() const override;
    double      calculateRiskScore() const override;
    int         getMinCrewRequired() const override;

    void displaySummary() const override;
};

#endif