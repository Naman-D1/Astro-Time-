#ifndef MISSIONVALIDATOR_H
#define MISSIONVALIDATOR_H

#include <string>
#include <vector>
#include <memory>
#include "../Models/Mission.hpp"

struct ValidationResult {
    bool        passed;
    std::vector<std::string> errors;    // hard failures — mission blocked
    std::vector<std::string> warnings;  // soft issues — mission can proceed
};

class MissionValidator {
public:
    static ValidationResult validate(const std::shared_ptr<Mission>& mission);
    static void printValidationReport(const ValidationResult& result);
};

#endif