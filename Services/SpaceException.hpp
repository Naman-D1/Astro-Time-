#ifndef SPACEEXCEPTION_H
#define SPACEEXCEPTION_H

#include <exception>
#include <string>

// -------------------------------------------------------
// Base exception for all GalacticRoute errors
// -------------------------------------------------------
class SpaceException : public std::exception {
private:
    std::string message;
public:
    SpaceException(const std::string& message) : message(message) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// -------------------------------------------------------
// Thrown when fuel values are invalid
// -------------------------------------------------------
class InvalidFuelException : public SpaceException {
public:
    InvalidFuelException(const std::string& msg)
        : SpaceException("FUEL ERROR: " + msg) {}
};

// -------------------------------------------------------
// Thrown when crew count is invalid
// -------------------------------------------------------
class InvalidCrewException : public SpaceException {
public:
    InvalidCrewException(const std::string& msg)
        : SpaceException("CREW ERROR: " + msg) {}
};

// -------------------------------------------------------
// Thrown when destination is not found in registry
// -------------------------------------------------------
class DestinationNotFoundException : public SpaceException {
public:
    DestinationNotFoundException(const std::string& name)
        : SpaceException("DESTINATION NOT FOUND: '" + name + "' does not exist in registry.") {}
};

// -------------------------------------------------------
// Thrown when mission parameters are invalid
// -------------------------------------------------------
class InvalidMissionException : public SpaceException {
public:
    InvalidMissionException(const std::string& msg)
        : SpaceException("MISSION ERROR: " + msg) {}
};

// -------------------------------------------------------
// Thrown when physics validation fails critically
// -------------------------------------------------------
class PhysicsException : public SpaceException {
public:
    PhysicsException(const std::string& msg)
        : SpaceException("PHYSICS ERROR: " + msg) {}
};

#endif