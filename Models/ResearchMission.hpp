#ifndef RESEARCHMISSION_H
#define RESEARCHMISSION_H

#include "Mission.hpp"
usign namespace std;

class ResearchMission : public Mission {
private:
    string researchTopic;
    int         sampleCollectionTarget; // number of samples to collect
    bool        requiresEVA;            // Extra Vehicular Activity (spacewalk)

public:
    ResearchMission(string missionName,
                    shared_ptr<Spacecraft> spacecraft,
                    shared_ptr<CelestialBody> destination,
                    string researchTopic,
                    int sampleCollectionTarget,
                    bool requiresEVA);

    // Getters
    string getResearchTopic()         const;
    int         getSampleCollectionTarget() const;
    bool        getRequiresEVA()           const;

    // Setters
    void setResearchTopic(string topic);
    void setSampleCollectionTarget(int target);
    void setRequiresEVA(bool eva);

    // Overrides
    string getMissionType() const override;
    double      calculateRiskScore() const override;
    int         getMinCrewRequired() const override;

    void displaySummary() const override;
};

#endif