#ifndef BODYREGISTRY_H
#define BODYREGISTRY_H

#include <vector>
#include <string>
#include <memory>
#include "CelestialBody.hpp"

class BodyRegistry {
private:
    std::vector<std::shared_ptr<CelestialBody>> bodies;

    void loadPresets(); // loads all known celestial bodies

public:
    BodyRegistry();

    // Fetch by name (returns nullptr if not found)
    std::shared_ptr<CelestialBody> findByName(const std::string& name) const;

    // Add a custom body
    void addBody(std::shared_ptr<CelestialBody> body);

    // List all available bodies
    void listAll() const;
};

#endif