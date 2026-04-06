#ifndef ANIMATIONUTILS_H
#define ANIMATIONUTILS_H

#include <string>

class AnimationUtils {
public:
    // Plays the spinning planet animation with a message
    static void spinningPlanet(const std::string& message, int durationMs = 1200);

    // Prints a styled section divider
    static void printDivider(const std::string& title);
};

#endif