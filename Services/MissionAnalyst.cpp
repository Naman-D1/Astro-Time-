#include "MissionAnalyst.hpp"
#include "../models/Mission.hpp"
#include "../models/IonDrive.hpp"
#include "../models/RocketShip.hpp"
#include "../models/SolarSailor.hpp"
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
    double realDays = mission->calculateTravelTime();

    /*std::cout << "\n[ TRAJECTORY & NAVIGATION ]\n";
    std::cout << "- Launch Window: Earth-Mars Phase Angle must be ~44 degrees.\n";
    std::cout << "- Transfer Method: Hohmann Elliptic Orbit.\n";
    std::cout << "- Realistic Duration: ~" << realDays << " days (Standard Orbital Physics).\n";
    std::cout << "- Velocity Change Required: " << report.deltaVRequired << " m/s.\n";*/

    std::cout << "\n[ TRAJECTORY & NAVIGATION ]\n";

// Dynamic phase angle based on destination distance
double distanceMKm = dest->getDistanceFromEarth();
double phaseAngle  = 0.0;
std::string transferMethod = "";

if (distanceMKm < 1.0) {
    // Earth orbit / Lunar
    phaseAngle     = 0.0; // no phase angle needed, direct transfer
    transferMethod = "Direct Ascent / Trans-Lunar Injection";
    std::cout << "- Launch Window    : Direct launch, no phase angle required.\n";
} else if (distanceMKm < 100.0) {
    // Inner planets (Mars, Venus, Mercury)
    phaseAngle     = 180.0 - (distanceMKm / 2.5);
    transferMethod = "Hohmann Elliptic Transfer Orbit";
    std::cout << "- Launch Window    : Earth-" << dest->getName()
              << " Phase Angle must be ~" << (int)phaseAngle << " degrees.\n";
} else if (distanceMKm < 1000.0) {
    // Outer planets (Jupiter, Saturn)
    phaseAngle     = 97.0 - (distanceMKm / 100.0);
    transferMethod = "Hohmann Elliptic Transfer Orbit (Outer Planet)";
    std::cout << "- Launch Window    : Earth-" << dest->getName()
              << " Phase Angle must be ~" << (int)phaseAngle << " degrees.\n";
} else {
    // Deep space (Titan, Europa etc.)
    transferMethod = "Gravity Assist Trajectory recommended";
    std::cout << "- Launch Window    : Gravity assist via Jupiter recommended.\n";
    std::cout << "- Phase Angle      : Complex multi-body calculation required.\n";
}

    std::cout << "- Transfer Method  : " << transferMethod << "\n";
    std::cout << "- Realistic Duration: ~" << mission->calculateTravelTime() << " days.\n";
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
               "massive fuel savings. Ideal for long-range deep space missions.\n";
    } 
    else if (std::dynamic_pointer_cast<RocketShip>(ship)) {
        return "Chemical Rocket selected for high-thrust operations.\n"
               "Burns liquid propellant for maximum speed at the cost of fuel efficiency.\n"
               "Best suited for short to medium range missions requiring fast transit.\n";
    } 
    else if (std::dynamic_pointer_cast<SolarSailer>(ship)) {
        return "Solar Sail propulsion selected — zero fuel consumption.\n"
               "Harnesses radiation pressure from the Sun to accelerate gradually.\n"
               "Ideal for ultra long range missions where time is not a constraint.\n";
    }
    return "Unknown propulsion system. Standard protocols in effect.\n";
}

std::string MissionAnalyst::getRiskAnalysis(const std::shared_ptr<Mission>& mission, const PhysicsValidation& report) {
    std::string analysis = "Current Risk Score: " + std::to_string(mission->calculateRiskScore()) + "/10\n";
    analysis += "- Structural: Payload is within safe margins.\n";
    analysis += "- Radiation: High duration requires Class-A shielding (Active).\n";
    return analysis;
}