#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <unordered_map>


namespace Blocks {
namespace Assets {

const std::string assets_path = "./assets/";

// fonts are encoded in a 5x5 grid
const uint32_t FONT_X = 5;
const uint32_t FONT_Y = 5;

typedef int** Font;

std::unordered_map<std::string, Font> fontsCache; // Hashmap for caching fonts

Font createMatrix() {
    Font font = new int*[FONT_X];
    for (int i = 0; i < FONT_X; i++) {
        font[i] = new int[FONT_Y];
    }
    return font;
}


Font readAsset(const std::string& assetName) {
    
    auto it = fontsCache.find(assetName);
    if (it != fontsCache.end()) {
        return it->second; // Return the cached font
    }

    std::filesystem::path filePath = std::filesystem::path(assets_path) / assetName;
    std::ifstream file(filePath);
    Font font = createMatrix();
    std::string line;

    if (file.is_open()) {
        int i = 0;
        int j = 0;
        while (std::getline(file, line)) {
            for (char c : line) {
                font[i][j] = c - '0';
                j++;
            }
            i++;
        }
        file.close();
    } else {
        std::cout << "Unable to open file: " << filePath << std::endl;
    }

    fontsCache[assetName] = font; // Cache the loaded font

    return font;
}


}};