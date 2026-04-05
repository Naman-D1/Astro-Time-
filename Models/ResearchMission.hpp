#ifndef RESEARCHMISSION_H
#define RESEARCHMISSION_H

#include "Mission.hpp"

class ResearchMission : public Mission {
private:
    std::string researchTopic;
    int         sampleCollectionTarget; // number of samples to collect
    bool        requiresEVA;            // Extra Vehicular Activity (spacewalk)

public:
    ResearchMission(std::string missionName,
                    std::shared_ptr<Spacecraft> spacecraft,
                    std::shared_ptr<CelestialBody> destination,
                    std::string researchTopic,
                    int sampleCollectionTarget,
                    bool requiresEVA);

    // Getters
    std::string getResearchTopic()         const;
    int         getSampleCollectionTarget() const;
    bool        getRequiresEVA()           const;

    // Setters
    void setResearchTopic(std::string topic);
    void setSampleCollectionTarget(int target);
    void setRequiresEVA(bool eva);

    // Overrides
    std::string getMissionType() const override;
    double      calculateRiskScore() const override;
    int         getMinCrewRequired() const override;

    void displaySummary() const override;
};

#endif