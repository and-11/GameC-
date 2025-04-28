#pragma once

#include "libraryes.h"

void clear_window()
{
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        system("clear"); // Unix/Linux/macOS
    #endif
}

int getRandomNumber() {
    
    int low = 1, high = INT_MAX;
    
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(low, high);
    return distr(gen);
}