#ifndef REPORTEXPORTER_H
#define REPORTEXPORTER_H

#include <string>
#include <memory>
#include <fstream>
#include "Mission.hpp"
#include "Navigation_Suite.hpp"
#include "MissionValidator.hpp"

class ReportExporter {
public:
    static bool exportReport(
        const std::shared_ptr<Mission>& mission,
        const PhysicsValidation& physics,
        const ValidationResult& validation,
        const std::string& filename
    );

private:
    static void writeHeader(std::ofstream& file, const std::shared_ptr<Mission>& mission);
    static void writeMissionDetails(std::ofstream& file, const std::shared_ptr<Mission>& mission);
    static void writePhysicsReport(std::ofstream& file, const PhysicsValidation& physics, const std::shared_ptr<Mission>& mission);
    static void writeValidationReport(std::ofstream& file, const ValidationResult& validation);
    static void writeFooter(std::ofstream& file);
};

#endif