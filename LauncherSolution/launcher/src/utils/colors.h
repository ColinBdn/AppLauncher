#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace Colors {
    // Text colors
    constexpr const char* BLACK = "\033[30m";
    constexpr const char* RED = "\033[31m";
    constexpr const char* GREEN = "\033[32m";
    constexpr const char* YELLOW = "\033[33m";
    constexpr const char* BLUE = "\033[34m";
    constexpr const char* MAGENTA = "\033[35m";
    constexpr const char* CYAN = "\033[36m";
    constexpr const char* WHITE = "\033[37m";
    
    // Bright text colors
    constexpr const char* BRIGHT_BLACK = "\033[90m";
    constexpr const char* BRIGHT_RED = "\033[91m";
    constexpr const char* BRIGHT_GREEN = "\033[92m";
    constexpr const char* BRIGHT_YELLOW = "\033[93m";
    constexpr const char* BRIGHT_BLUE = "\033[94m";
    constexpr const char* BRIGHT_MAGENTA = "\033[95m";
    constexpr const char* BRIGHT_CYAN = "\033[96m";
    constexpr const char* BRIGHT_WHITE = "\033[97m";
    
    // Background colors
    constexpr const char* BG_BLACK = "\033[40m";
    constexpr const char* BG_RED = "\033[41m";
    constexpr const char* BG_GREEN = "\033[42m";
    constexpr const char* BG_YELLOW = "\033[43m";
    constexpr const char* BG_BLUE = "\033[44m";
    constexpr const char* BG_MAGENTA = "\033[45m";
    constexpr const char* BG_CYAN = "\033[46m";
    constexpr const char* BG_WHITE = "\033[47m";
    
    // Bright background colors
    constexpr const char* BG_BRIGHT_BLACK = "\033[100m";
    constexpr const char* BG_BRIGHT_RED = "\033[101m";
    constexpr const char* BG_BRIGHT_GREEN = "\033[102m";
    constexpr const char* BG_BRIGHT_YELLOW = "\033[103m";
    constexpr const char* BG_BRIGHT_BLUE = "\033[104m";
    constexpr const char* BG_BRIGHT_MAGENTA = "\033[105m";
    constexpr const char* BG_BRIGHT_CYAN = "\033[106m";
    constexpr const char* BG_BRIGHT_WHITE = "\033[107m";
    
    // Additional colors
    constexpr const char* ORANGE = "\033[38;5;208m";
    constexpr const char* PINK = "\033[38;5;200m";
    constexpr const char* VIOLET = "\033[38;5;129m";
    constexpr const char* LIGHT_GREEN = "\033[38;5;120m";
    constexpr const char* LIGHT_BLUE = "\033[38;5;123m";
    constexpr const char* LIGHT_CYAN = "\033[38;5;152m";
    constexpr const char* LIGHT_MAGENTA = "\033[38;5;207m";
    constexpr const char* GOLD = "\033[38;5;220m";
    constexpr const char* SILVER = "\033[38;5;7m";
    constexpr const char* TEAL = "\033[38;5;86m";
    constexpr const char* GREY = "\033[38;5;242m";
    
    // Text styles
    constexpr const char* BOLD = "\033[1m";
    constexpr const char* UNDERLINE = "\033[4m";
    constexpr const char* REVERSED = "\033[7m";
    constexpr const char* RESET = "\033[0m";
}



template<typename... Args>
void cPrint(const char* color, Args&&... args) {
    if (color) {
        std::cout << color;
    }
    (std::cout << ... << std::forward<Args>(args));
    std::cout << std::endl;
    if (color) {
        std::cout << Colors::RESET;
    }
}

template<typename... Args>
void cPrint(Args&&... args) {
    (std::cout << ... << std::forward<Args>(args));
    std::cout << std::endl;
}



inline void testPrintAll() {
    cPrint(Colors::BLACK, "BLACK           test ==== //// ---- AAAAA");
    cPrint(Colors::RED, "RED             test ==== //// ---- AAAAA");
    cPrint(Colors::GREEN, "GREEN           test ==== //// ---- AAAAA");
    cPrint(Colors::YELLOW, "YELLOW          test ==== //// ---- AAAAA");
    cPrint(Colors::BLUE, "BLUE            test ==== //// ---- AAAAA");
    cPrint(Colors::MAGENTA, "MAGENTA         test ==== //// ---- AAAAA");
    cPrint(Colors::CYAN, "CYAN            test ==== //// ---- AAAAA");
    cPrint(Colors::WHITE, "WHITE           test ==== //// ---- AAAAA");
    cPrint(Colors::BRIGHT_BLACK, "BRIGHT_BLACK    test ==== //// ---- AAAAA");
    cPrint(Colors::BRIGHT_RED, "BRIGHT_RED      test ==== //// ---- AAAAA");
    cPrint(Colors::BRIGHT_GREEN, "BRIGHT_GREEN    test ==== //// ---- AAAAA");
    cPrint(Colors::BRIGHT_YELLOW, "BRIGHT_YELLOW   test ==== //// ---- AAAAA");
    cPrint(Colors::BRIGHT_BLUE, "BRIGHT_BLUE     test ==== //// ---- AAAAA");
    cPrint(Colors::BRIGHT_MAGENTA, "BRIGHT_MAGENTA  test ==== //// ---- AAAAA");
    cPrint(Colors::BRIGHT_CYAN, "BRIGHT_CYAN     test ==== //// ---- AAAAA");
    cPrint(Colors::BRIGHT_WHITE, "BRIGHT_WHITE    test ==== //// ---- AAAAA");
    cPrint(Colors::ORANGE, "ORANGE          test ==== //// ---- AAAAA");
    cPrint(Colors::PINK, "PINK            test ==== //// ---- AAAAA");
    cPrint(Colors::VIOLET, "VIOLET          test ==== //// ---- AAAAA");
    cPrint(Colors::LIGHT_GREEN, "LIGHT_GREEN     test ==== //// ---- AAAAA");
    cPrint(Colors::LIGHT_BLUE, "LIGHT_BLUE      test ==== //// ---- AAAAA");
    cPrint(Colors::LIGHT_CYAN, "LIGHT_CYAN      test ==== //// ---- AAAAA");
    cPrint(Colors::LIGHT_MAGENTA, "LIGHT_MAGENTA   test ==== //// ---- AAAAA");
    cPrint(Colors::GOLD, "GOLD            test ==== //// ---- AAAAA");
    cPrint(Colors::SILVER, "SILVER          test ==== //// ---- AAAAA");
    cPrint(Colors::GREY, "GREY            test ==== //// ---- AAAAA");
}