#ifndef MISSIONLOG_H
#define MISSIONLOG_H

#include <vector>
#include <memory>
#include <string>
#include "../Models/Mission.hpp"

class MissionLog {
private:
    std::vector<std::shared_ptr<Mission>> missions;

public:
    // Add a mission to the log
    void addMission(const std::shared_ptr<Mission>& mission);

    // Display all missions
    void displayAll() const;

    // Display missions filtered by status
    void displayByStatus(const std::string& status) const;

    // Get total mission count
    int getTotalCount() const;

    // Get count by status
    int getCountByStatus(const std::string& status) const;

    // Display summary statistics
    void displaySummary() const;
};

#endif