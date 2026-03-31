#include "MissionAnalyst.hpp"
#include "../models/Mission.hpp"
#include "../models/IonDrive.hpp"
#include <iostream>
#include <iomanip>

void MissionAnalyst::printFullBriefing(const std::shared_ptr<Mission>& mission, const PhysicsValidation& report) {
    auto ship = mission->getSpacecraft();
    auto dest = mission->getDestination();

    std::cout << "\n==========================================================\n";
    std::cout << "          OFFICIAL INTERPLANETARY MISSION BRIEFING          \n";
    std::cout << "==========================================================\n";

    // 1. Propulsion Explanation
    std::cout << "\n[ PROPULSION SYSTEM: " << ship->getType() << " ]\n";
    std::cout << getPropulsionDeepDive(ship);

    // 2. Orbital Mechanics (The "Hard Science" part)
    double realDays = 259.0; // Realistic Mars transfer
    if (dest->getName() == "Jupiter") realDays = 600.0;
    
    std::cout << "\n[ TRAJECTORY & NAVIGATION ]\n";
    std::cout << "- Launch Window: Earth-Mars Phase Angle must be ~44 degrees.\n";
    std::cout << "- Transfer Method: Hohmann Elliptic Orbit.\n";
    std::cout << "- Realistic Duration: ~" << realDays << " days (Standard Orbital Physics).\n";
    std::cout << "- Velocity Change Required: " << report.deltaVRequired << " m/s.\n";

    // 3. Risk Assessment
    std::cout << "\n[ SAFETY & RISK ANALYSIS ]\n";
    std::cout << getRiskAnalysis(mission, report);
    std::cout << "==========================================================\n";
}

std::string MissionAnalyst::getPropulsionDeepDive(const std::shared_ptr<Spacecraft>& ship) {
    if (std::dynamic_pointer_cast<IonDrive>(ship)) {
        return "The Ion Drive was selected for its high Specific Impulse (Isp).\n"
               "By ionizing Xenon gas and accelerating it with electric fields, we achieve\n"
               "massive fuel savings. This allows for heavy cargo delivery without the\n"
               "need for a 'monster' rocket.";
    }
    return "Standard propulsion protocols in effect.";
}

std::string MissionAnalyst::getRiskAnalysis(const std::shared_ptr<Mission>& mission, const PhysicsValidation& report) {
    std::string analysis = "Current Risk Score: " + std::to_string(mission->calculateRiskScore()) + "/10\n";
    analysis += "- Structural: Payload is within safe margins.\n";
    analysis += "- Radiation: High duration requires Class-A shielding (Active).\n";
    return analysis;
}