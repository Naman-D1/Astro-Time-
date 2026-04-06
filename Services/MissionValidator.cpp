#include "MissionValidator.hpp"
#include "../Models/CrewMission.hpp"
#include "../Models/CargoMission.hpp"
#include "../Models/ResearchMission.hpp"
#include "../Models/SpaceStation.hpp"
#include "../Models/Mission.hpp"
#include <iostream>

ValidationResult MissionValidator::validate(const std::shared_ptr<Mission>& mission) {
    ValidationResult result;
    result.passed = true;

    auto ship = mission->getSpacecraft();
    auto dest = mission->getDestination();

    // -------------------------------------------------------
    // HARD CHECKS — these block the mission entirely
    // -------------------------------------------------------

    // 1. Check if ship has enough fuel
    double fuelNeeded  = mission->calculateFuelNeeded();
    double fuelOnBoard = ship->getCurrentFuel();
    if (fuelNeeded > fuelOnBoard) {
        result.passed = false;
        result.errors.push_back(
            "FUEL INSUFFICIENT: Needs " + std::to_string((int)fuelNeeded) +
            " tonnes, ship only has " + std::to_string((int)fuelOnBoard) + " tonnes."
        );
    }

    // 2. Check destination is reachable (not a derelict station)
    auto station = std::dynamic_pointer_cast<SpaceStation>(dest);
    if (station && !station->getIsOperational()) {
        result.passed = false;
        result.errors.push_back(
            "DESTINATION OFFLINE: " + dest->getName() + " is not operational."
        );
    }

    // 3. Crew mission specific checks
    auto crewMission = std::dynamic_pointer_cast<CrewMission>(mission);
    if (crewMission) {
        // Check crew doesn't exceed ship capacity
        if (crewMission->getCrewCount() > ship->getMaxCrew()) {
            result.passed = false;
            result.errors.push_back(
                "CREW OVERFLOW: Mission requires " +
                std::to_string(crewMission->getCrewCount()) +
                " crew but ship only fits " +
                std::to_string(ship->getMaxCrew()) + "."
            );
        }
        // Check minimum crew is met
        if (crewMission->getCrewCount() < mission->getMinCrewRequired()) {
            result.passed = false;
            result.errors.push_back(
                "CREW INSUFFICIENT: Minimum " +
                std::to_string(mission->getMinCrewRequired()) +
                " crew required for this mission type."
            );
        }
    }

    // 4. Cargo mission specific checks
    auto cargoMission = std::dynamic_pointer_cast<CargoMission>(mission);
    if (cargoMission) {
        if (cargoMission->getCargoWeight() > ship->getPayloadCapacity()) {
            result.passed = false;
            result.errors.push_back(
                "PAYLOAD EXCEEDED: Cargo is " +
                std::to_string((int)cargoMission->getCargoWeight()) +
                " tonnes but ship capacity is only " +
                std::to_string((int)ship->getPayloadCapacity()) + " tonnes."
            );
        }
    }

    // -------------------------------------------------------
    // SOFT CHECKS — warnings only, mission can still proceed
    // -------------------------------------------------------

    // 5. High risk warning
    if (mission->calculateRiskScore() >= 7.0) {
        result.warnings.push_back(
            "HIGH RISK: Risk score is " +
            std::to_string((int)mission->calculateRiskScore()) +
            "/10. Mission is extremely dangerous."
        );
    }

    // 6. Fuel running low warning (>80% of capacity used)
    if (fuelNeeded > ship->getMaxFuelCapacity() * 0.8) {
        result.warnings.push_back(
            "FUEL WARNING: Mission will consume over 80% of fuel capacity. "
            "Limited reserve for emergencies."
        );
    }

    // 7. Gravity warning for crew missions
    if (crewMission && dest->getGravity() > 15.0) {
        result.warnings.push_back(
            "GRAVITY HAZARD: Destination gravity (" +
            std::to_string((int)dest->getGravity()) +
            " m/s²) may be dangerous for crew without pressure suits."
        );
    }

    // 8. Long travel time warning
    double travelDays = mission->calculateTravelTime();
    if (travelDays > 300.0) {
        result.warnings.push_back(
            "LONG DURATION: Travel time of " +
            std::to_string((int)travelDays) +
            " days requires extended life support and crew psychology planning."
        );
    }

    return result;
}

void MissionValidator::printValidationReport(const ValidationResult& result) {
    std::cout << "\n[ MISSION VALIDATION REPORT ]\n";

    if (result.errors.empty() && result.warnings.empty()) {
        std::cout << "  All checks passed. Mission is GO for launch.\n";
        return;
    }

    // Print hard errors
    if (!result.errors.empty()) {
        std::cout << "\n  ERRORS — Mission Blocked:\n";
        for (const auto& error : result.errors)
            std::cout << "  ✖ " << error << "\n";
    }

    // Print warnings
    if (!result.warnings.empty()) {
        std::cout << "\n  WARNINGS — Proceed with Caution:\n";
        for (const auto& warning : result.warnings)
            std::cout << "  ⚠ " << warning << "\n";
    }

    if (result.passed)
        std::cout << "\n  STATUS: GO for launch with noted warnings.\n";
    else
        std::cout << "\n  STATUS: MISSION BLOCKED. Resolve errors before launch.\n";
}