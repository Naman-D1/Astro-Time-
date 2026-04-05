#include "MissionLog.hpp"
#include <iostream>
#include <iomanip>

void MissionLog::addMission(const std::shared_ptr<Mission>& mission) {
    missions.push_back(mission);
    std::cout << ">> Mission '" << mission->getMissionName() << "' added to log.\n";
}

void MissionLog::displayAll() const {
    if (missions.empty()) {
        std::cout << "\n  No missions in log yet.\n";
        return;
    }

    std::cout << "\n==========================================================\n";
    std::cout << "                    MISSION LOG                          \n";
    std::cout << "==========================================================\n";

    int index = 1;
    for (const auto& mission : missions) {
        std::cout << "\n  [" << index++ << "] " << mission->getMissionName() << "\n";
        std::cout << "      Type        : " << mission->getMissionType() << "\n";
        std::cout << "      Status      : " << mission->getStatus() << "\n";
        std::cout << "      Destination : " << mission->getDestination()->getName() << "\n";
        std::cout << "      Ship        : " << mission->getSpacecraft()->getName() << "\n";
        std::cout << "      Travel Time : " << mission->calculateTravelTime() << " days\n";
        std::cout << "      Risk Score  : " << mission->calculateRiskScore() << "/10\n";
    }

    std::cout << "\n==========================================================\n";
}

void MissionLog::displayByStatus(const std::string& status) const {
    std::cout << "\n  Missions with status '" << status << "':\n";

    bool found = false;
    for (const auto& mission : missions) {
        if (mission->getStatus() == status) {
            std::cout << "  - " << mission->getMissionName()
                      << " → " << mission->getDestination()->getName() << "\n";
            found = true;
        }
    }

    if (!found)
        std::cout << "  None found.\n";
}

void MissionLog::displaySummary() const {
    std::cout << "\n==========================================================\n";
    std::cout << "                  MISSION LOG SUMMARY                    \n";
    std::cout << "==========================================================\n";
    std::cout << "  Total Missions  : " << getTotalCount() << "\n";
    std::cout << "  Planned         : " << getCountByStatus("Planned") << "\n";
    std::cout << "  Ongoing         : " << getCountByStatus("Ongoing") << "\n";
    std::cout << "  Completed       : " << getCountByStatus("Completed") << "\n";
    std::cout << "  Aborted         : " << getCountByStatus("Aborted") << "\n";
    std::cout << "==========================================================\n";
}

int MissionLog::getTotalCount() const {
    return (int)missions.size();
}

int MissionLog::getCountByStatus(const std::string& status) const {
    int count = 0;
    for (const auto& mission : missions)
        if (mission->getStatus() == status)
            count++;
    return count;
}