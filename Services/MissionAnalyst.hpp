#ifndef MISSION_ANALYST_HPP
#define MISSION_ANALYST_HPP

#include "../models/Mission.hpp"
#include "Navigation_Suite.hpp"
#include <string>
class MissionAnalyst {
public:
    static void printFullBriefing(const std::shared_ptr<Mission>& mission, const PhysicsValidation& report);

private:
    static std::string getPropulsionDeepDive(const std::shared_ptr<Spacecraft>& ship);
    static std::string getRiskAnalysis(const std::shared_ptr<Mission>& mission, const PhysicsValidation& report);
};

#endif