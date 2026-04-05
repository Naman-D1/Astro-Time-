#include "ReportExporter.hpp"
#include "../models/Mission.hpp"
#include "../models/CargoMission.hpp"
#include "../models/CrewMission.hpp"
#include "../models/ResearchMission.hpp"
#include <iostream>
#include <ctime>

// Helper to get current timestamp
static std::string getCurrentTimestamp() {
    std::time_t now = std::time(nullptr);
    char buf[80];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return std::string(buf);
}

// Helper to write a divider line
static void writeDivider(std::ofstream& file) {
    file << "==========================================================\n";
}
static void writeSubDivider(std::ofstream& file) {
    file << "----------------------------------------------------------\n";
}

bool ReportExporter::exportReport(
    const std::shared_ptr<Mission>& mission,
    const PhysicsValidation& physics,
    const ValidationResult& validation,
    const std::string& filename)
{
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not create report file '" << filename << "'.\n";
        return false;
    }

    writeHeader(file, mission);
    writeMissionDetails(file, mission);
    writePhysicsReport(file, physics, mission);
    writeValidationReport(file, validation);
    writeFooter(file);

    file.close();
    std::cout << "\n>> Report successfully saved to '" << filename << "'.\n";
    return true;
}

void ReportExporter::writeHeader(std::ofstream& file, const std::shared_ptr<Mission>& mission) {
    writeDivider(file);
    file << "       GALACTICROUTE — OFFICIAL MISSION REPORT\n";
    writeDivider(file);
    file << "  Mission Name  : " << mission->getMissionName() << "\n";
    file << "  Mission Type  : " << mission->getMissionType() << "\n";
    file << "  Generated At  : " << getCurrentTimestamp() << "\n";
    file << "  Status        : " << mission->getStatus() << "\n";
    writeDivider(file);
    file << "\n";
}

void ReportExporter::writeMissionDetails(std::ofstream& file, const std::shared_ptr<Mission>& mission) {
    auto ship = mission->getSpacecraft();
    auto dest = mission->getDestination();

    file << "[ MISSION DETAILS ]\n";
    writeSubDivider(file);
    file << "  Spacecraft    : " << ship->getName() << " (" << ship->getType() << ")\n";
    file << "  Destination   : " << dest->getName() << " (" << dest->getType() << ")\n";
    file << "  Distance      : " << dest->getDistanceFromEarth() << " million km\n";
    file << "  Travel Time   : " << mission->calculateTravelTime() << " days\n";
    file << "  Fuel Needed   : " << mission->calculateFuelNeeded() << " tonnes\n";
    file << "  Risk Score    : " << mission->calculateRiskScore() << "/10\n";
    file << "  Min Crew      : " << mission->getMinCrewRequired() << "\n";
    file << "\n";

    // Mission type specific details
    auto cargo = std::dynamic_pointer_cast<CargoMission>(mission);
    if (cargo) {
        file << "  Cargo Type    : " << cargo->getCargoType() << "\n";
        file << "  Cargo Weight  : " << cargo->getCargoWeight() << " tonnes\n";
    }

    auto crew = std::dynamic_pointer_cast<CrewMission>(mission);
    if (crew) {
        file << "  Crew Count    : " << crew->getCrewCount() << "\n";
        file << "  Life Support  : " << (crew->getHasLifeSupport() ? "Yes" : "No") << "\n";
    }

    auto research = std::dynamic_pointer_cast<ResearchMission>(mission);
    if (research) {
        file << "  Research Topic: " << research->getResearchTopic() << "\n";
        file << "  Sample Target : " << research->getSampleCollectionTarget() << "\n";
        file << "  Requires EVA  : " << (research->getRequiresEVA() ? "Yes" : "No") << "\n";
    }

    file << "\n";
}

void ReportExporter::writePhysicsReport(std::ofstream& file, const PhysicsValidation& physics, const std::shared_ptr<Mission>& mission) {
    auto dest = mission->getDestination();
    double distanceMKm = dest->getDistanceFromEarth();

    file << "[ PHYSICS & TRAJECTORY REPORT ]\n";
    writeSubDivider(file);
    file << "  Delta-V Required  : " << physics.deltaVRequired << " m/s\n";
    file << "  Mission Feasible  : " << (physics.canReachDestination ? "YES" : "NO") << "\n";
    file << "  Flight Notes      : " << physics.flightNotes << "\n";

    // Trajectory type
    if (distanceMKm < 1.0)
        file << "  Transfer Method   : Direct Ascent / Trans-Lunar Injection\n";
    else if (distanceMKm < 1000.0)
        file << "  Transfer Method   : Hohmann Elliptic Transfer Orbit\n";
    else
        file << "  Transfer Method   : Gravity Assist Trajectory\n";

    file << "\n";
}

void ReportExporter::writeValidationReport(std::ofstream& file, const ValidationResult& validation) {
    file << "[ MISSION VALIDATION REPORT ]\n";
    writeSubDivider(file);

    if (validation.errors.empty() && validation.warnings.empty()) {
        file << "  All checks passed. Mission is GO for launch.\n";
    }

    if (!validation.errors.empty()) {
        file << "  ERRORS:\n";
        for (const auto& error : validation.errors)
            file << "  [X] " << error << "\n";
    }

    if (!validation.warnings.empty()) {
        file << "  WARNINGS:\n";
        for (const auto& warning : validation.warnings)
            file << "  [!] " << warning << "\n";
    }

    file << "  Overall Status    : " << (validation.passed ? "GO FOR LAUNCH" : "MISSION BLOCKED") << "\n";
    file << "\n";
}


void ReportExporter::writeFooter(std::ofstream& file) {
    writeDivider(file);
    file << "  GalacticRoute Mission Planner — End of Report\n";
    file << "  Generated by GalacticRoute v1.0\n";
    writeDivider(file);
}