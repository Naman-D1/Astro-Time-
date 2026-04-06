#include "AnimationUtils.hpp"
#include <iostream>
#include <thread>
#include <chrono>

void AnimationUtils::spinningPlanet(const std::string& message, int durationMs) {
    // Planet spin frames
    const char* frames[] = {
        "  .  o  O  ( )  O  o  .  ",
        "  o  O  ( )  O  o  .     ",
        "  O  ( )  O  o  .        ",
        "  ( )  O  o  .           ",
        "  O  o  .      ( )       ",
        "  o  .         ( )  O    ",
        "  .            ( )  O  o ",
        "               ( )  O  o  . "
    };

    int frameCount  = 8;
    int frameMs     = 150; // ms per frame
    int totalFrames = durationMs / frameMs;

    std::cout << "\n";
    for (int i = 0; i < totalFrames; i++) {
        std::cout << "\r  " << message << "  "
                  << frames[i % frameCount]
                  << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(frameMs));
    }
    std::cout << "\r  " << message << "  ... done!          \n";
}

void AnimationUtils::printDivider(const std::string& title) {
    std::cout << "\n--- " << title << " ---\n";
}