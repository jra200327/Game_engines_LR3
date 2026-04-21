#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include <cstdint>
#include <filesystem>
#include "ReadConfig.h"


bool ReadConfig(WindowConfig& window, ShooterConfig& shooter, ImageConfig& image, AsteroidConfig& asteroid, SpawnConfig& spawn, TextConfig& text) {
    std::cout << "Current path: " << std::filesystem::current_path() << std::endl;
    std::ifstream file("../../config.txt");
    if (!file) {
        std::cerr << "Cannot open config file\n";
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;
        if (cmd == "Window") {
            iss >> window.width >> window.height;
            std::cout << window.width << " " << window.height << std::endl;
        } else if (cmd == "Shooter") {
            iss >> shooter.cd;
            std::cout << shooter.cd << std::endl;
         } else if (cmd == "Image") {
            iss >> image.path;
            std::cout << image.path;
        } else if (cmd == "Asteroid") {
            iss >> asteroid.minSpeed >> asteroid.maxSpeed >> asteroid.minSize >> asteroid.maxSize >> asteroid.offset;
        } else if (cmd == "Spawn") {
            iss >> spawn.cd;
        } else if (cmd == "Font") {
            iss >> text.path;
        } else {
            // Для плейсхолдера или неизвестных команд
            std::cout << "Unknown config line: " << line << "\n";
        }
    }

    //std::cout << "Text " << text;

    return true;
}