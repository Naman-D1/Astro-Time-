#include "CrewMission.hpp"
#include <iostream>
#include <algorithm>
using namespace std;

CrewMission::CrewMission(string missionName,
                         shared_ptr<Spacecraft> spacecraft,
                         shared_ptr<CelestialBody> destination,
                         int crewCount, bool hasLifeSupport,
                         int missionDurationDays)
    : Mission(missionName, spacecraft, destination),
      crewCount(crewCount), hasLifeSupport(hasLifeSupport),
      missionDurationDays(missionDurationDays) {}

int  CrewMission::getCrewCount()           const { return crewCount; }
bool CrewMission::getHasLifeSupport()      const { return hasLifeSupport; }
int  CrewMission::getMissionDurationDays() const { return missionDurationDays; }

void CrewMission::setCrewCount(int count) {
    if (count < 1) {
        cerr << "Error: Crew count must be at least 1.\n";
        return;
    }
    crewCount = count;
}
void CrewMission::setHasLifeSupport(bool support) { hasLifeSupport = support; }
void CrewMission::setMissionDurationDays(int days) {
    if (days < 1) {
        cerr << "Error: Duration must be at least 1 day.\n";
        return;
    }
    missionDurationDays = days;
}

string CrewMission::getMissionType() const { return "Crew Mission"; }

// Crew missions are riskier — lives on the line
double CrewMission::calculateRiskScore() const {
    double risk = getDestination()->getHazardLevel();
    if (!hasLifeSupport)          risk += 3.0; // no life support = very dangerous
    if (crewCount > 4)            risk += 1.0; // more crew = more risk
    if (missionDurationDays > 90) risk += 1.5; // long missions are riskier
    return min(risk, 10.0);
}

// Crew missions need at least 3
int CrewMission::getMinCrewRequired() const { return 3; }

void CrewMission::displaySummary() const {
    Mission::displaySummary();
    cout << "  Crew Count   : " << crewCount << "\n";
    cout << "  Life Support : " << (hasLifeSupport ? "Yes" : "No") << "\n";
    cout << "  Duration     : " << missionDurationDays << " days\n";
    cout << "====================================\n";
}