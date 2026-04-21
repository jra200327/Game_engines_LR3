#ifndef READ_CONFIG_H
#define READ_CONFIG_H

#include <string>
#include <filesystem>
#include <cstdint>

struct WindowConfig {
    int width = 1280;
    int height = 720;
};

struct ShooterConfig {
    float cd;
};

struct ImageConfig {
    std::filesystem::path path;
};

struct AsteroidConfig {
    float minSpeed;
    float maxSpeed;
    float minSize;
    float maxSize;
    float offset;
};

struct SpawnConfig {
    float cd;
};

struct TextConfig
{
    std::filesystem::path path;
};

bool ReadConfig(WindowConfig& window, ShooterConfig& shooter, ImageConfig& image, AsteroidConfig& asteroid, SpawnConfig& spawn, TextConfig& text);

#endif // READ_CONFIG_H