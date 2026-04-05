#include "BodyRegistry.hpp"
#include "Planet.hpp"
#include "Moon.hpp"
#include "SpaceStation.hpp"
#include "../Services/SpaceException.hpp"
#include <iostream>
#include <algorithm>

BodyRegistry::BodyRegistry() {
    loadPresets();
}

void BodyRegistry::loadPresets() {
    // Planets
    bodies.push_back(std::make_shared<Planet>("Mars",    225.0,  3.72, "The Red Planet",       true,  0.006));
    bodies.push_back(std::make_shared<Planet>("Venus",   261.0,  8.87, "The Hottest Planet",   true,  92.0));
    bodies.push_back(std::make_shared<Planet>("Jupiter", 778.0, 24.79, "The Gas Giant",        true,  1000.0));
    bodies.push_back(std::make_shared<Planet>("Mercury", 91.7,   3.7,  "The Smallest Planet",  false, 0.0));

    // Moons
    bodies.push_back(std::make_shared<Moon>("Luna",   0.384,  1.62,  "Earth's Moon",          "Earth",   false));
    bodies.push_back(std::make_shared<Moon>("Europa", 628.3,  1.315, "Icy Moon of Jupiter",   "Jupiter", true));
    bodies.push_back(std::make_shared<Moon>("Titan",  1272.0, 1.352, "Saturn's Largest Moon", "Saturn",  true));
    bodies.push_back(std::make_shared<Moon>("Io",     628.0,  1.796, "Volcanic Moon",         "Jupiter", false));

    // Space Stations
    bodies.push_back(std::make_shared<SpaceStation>("ISS",         0.000408, 0.0, "International Space Station", 6,  true,  "Earth"));
    bodies.push_back(std::make_shared<SpaceStation>("Gateway",     0.000384, 0.0, "Lunar Gateway Station",       4,  true,  "Moon"));
    bodies.push_back(std::make_shared<SpaceStation>("Derelict-7",  0.002,    0.0, "Abandoned Research Station",  0,  false, "Mars"));
}

std::shared_ptr<CelestialBody> BodyRegistry::findByName(const std::string& name) const {
    for (const auto& body : bodies) {
        if (body->getName() == name)
            return body;
    }
   throw DestinationNotFoundException(name); // not found
}

void BodyRegistry::addBody(std::shared_ptr<CelestialBody> body) {
    bodies.push_back(body);
    std::cout << "Custom body '" << body->getName() << "' added to registry.\n";
}

void BodyRegistry::listAll() const {
    std::cout << "\n=== Available Destinations ===\n";
    for (const auto& body : bodies) {
        std::cout << "  [" << body->getType() << "] " << body->getName()
                  << " — " << body->getDistanceFromEarth() << " million km\n";
    }
}