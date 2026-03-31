#include "ResearchMission.hpp"
#include <iostream>
#include <algorithm>

ResearchMission::ResearchMission(std::string missionName,
                                 std::shared_ptr<Spacecraft> spacecraft,
                                 std::shared_ptr<CelestialBody> destination,
                                 std::string researchTopic,
                                 int sampleCollectionTarget,
                                 bool requiresEVA)
    : Mission(missionName, spacecraft, destination),
      researchTopic(researchTopic),
      sampleCollectionTarget(sampleCollectionTarget),
      requiresEVA(requiresEVA) {}

std::string ResearchMission::getResearchTopic()          const { return researchTopic; }
int         ResearchMission::getSampleCollectionTarget() const { return sampleCollectionTarget; }
bool        ResearchMission::getRequiresEVA()            const { return requiresEVA; }

void ResearchMission::setResearchTopic(std::string topic) { researchTopic = topic; }
void ResearchMission::setSampleCollectionTarget(int target) {
    if (target < 0) {
        std::cerr << "Error: Sample target cannot be negative.\n";
        return;
    }
    sampleCollectionTarget = target;
}
void ResearchMission::setRequiresEVA(bool eva) { requiresEVA = eva; }

std::string ResearchMission::getMissionType() const { return "Research Mission"; }

// Risk based on destination + EVA danger
double ResearchMission::calculateRiskScore() const {
    double risk = getDestination()->getHazardLevel() * 0.8; // slightly less risky than crew
    if (requiresEVA)                  risk += 2.0; // spacewalks are dangerous
    if (sampleCollectionTarget > 20)  risk += 1.0; // lots of fieldwork = more exposure
    return std::min(risk, 10.0);
}

// Research missions need at least a pilot + scientist
int ResearchMission::getMinCrewRequired() const { return 2; }

void ResearchMission::displaySummary() const {
    Mission::displaySummary();
    std::cout << "  Research Topic  : " << researchTopic << "\n";
    std::cout << "  Sample Target   : " << sampleCollectionTarget << "\n";
    std::cout << "  Requires EVA    : " << (requiresEVA ? "Yes" : "No") << "\n";
    std::cout << "====================================\n";
}