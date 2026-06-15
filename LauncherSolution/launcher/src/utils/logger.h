#pragma once

#include "colors.h"

#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <memory>



inline std::string getCurrentDate()
{
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::tm tm{};
    localtime_s(&tm, &time);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d/%m/%Y %H:%M:%S");
    return oss.str();
}

inline std::string generateLogFileName()
{
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::tm tm{};
    localtime_s(&tm, &time);
    std::ostringstream oss;
    oss << "log_" << std::put_time(&tm, "%d-%m-%Y_%Hh%Mmin%Ssec") << ".txt";
    return oss.str();
}



class Logger
{
public:
    enum Level
    {
        DEBUG = 1,
        INFO = 2,
        WARNING = 3,
        ERROR = 4,
        CRITICAL = 5
    };

private:
    static inline std::unique_ptr<std::ofstream> file = nullptr;
    static inline bool fileLogging = false;
    static inline Level level = DEBUG;
    static inline std::string logFileName = "";
    static inline bool initialized = false;

    Logger() = delete;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static void addToFile(const std::string& data)
    {
        if (!fileLogging || !file) return;
        *file << data << "\n";
        file->flush();
    }

    template<typename... Args>
    static std::string argsToString(Args&&... args)
    {
        std::ostringstream oss;
        (oss << ... << std::forward<Args>(args));
        return oss.str();
    }

    template<typename... Args>
    static void info(const char* color, Args&&... args)
    {
        if (level <= INFO)
        {
            std::string message = argsToString(std::forward<Args>(args)...);
            std::string prefix = "[ " + getCurrentDate() + " ]  [ INFO ]     ";
            cPrint(color, prefix, message);
            addToFile(prefix + message);
        }
    }


public:
    static void init(bool logToFile = false)
    {
        if (initialized) return;

        level = DEBUG;

        if (logToFile)
        {
            logFileName = generateLogFileName();
            file = std::make_unique<std::ofstream>(logFileName);
            if (file->is_open())
            {
                fileLogging = true;
            }
        }

        initialized = true;
    }

    static void shutdown()
    {
        if (file && file->is_open()) file->close();
        file.reset();
        fileLogging = false;
        initialized = false;
    }

    static void setLevel(Level lvl)
    {
        level = lvl;
    }

    static Level getLevel()
    {
        return level;
    }


    static void newLine()
    {
        std::cout << "\n";
        addToFile("");
	}

    template<typename... Args>
    static void debug(Args&&... args)
    {
        if (level <= DEBUG)
        {
            std::string message = argsToString(std::forward<Args>(args)...);
            std::string prefix = "[ " + getCurrentDate() + " ]  [ DEBUG ]    ";
            cPrint(Colors::GREY, prefix, message);
            addToFile(prefix + message);
        }
    }


    template<typename... Args>
    static void infoSmall(Args&&... args)
    {
        info(Colors::SILVER, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void infoMid(Args&&... args) 
    {
        info(Colors::BLUE, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void infoBig(Args&&... args)
    {
        info(Colors::LIGHT_BLUE, std::forward<Args>(args)...);
    }




    template<typename... Args>
    static void warning(Args&&... args)
    {
        std::string message = argsToString(std::forward<Args>(args)...);
        if (level <= WARNING)
        {
            std::string prefix = "[ " + getCurrentDate() + " ]  [ WARNING ]  ";
            cPrint(Colors::YELLOW, prefix, message);
            addToFile(prefix + message);
        }
    }

    template<typename... Args>
    [[noreturn]] static void warningThrow(Args&&... args)
    {
        std::string message = argsToString(std::forward<Args>(args)...);
        if (level <= WARNING)
        {
            std::string prefix = "[ " + getCurrentDate() + " ]  [ WARNING ]  ";
            cPrint(Colors::YELLOW, prefix, message);
            addToFile(prefix + message);
        }
        throw std::runtime_error(message);
    }




    template<typename... Args>
    static void error(Args&&... args)
    {
        std::string message = argsToString(std::forward<Args>(args)...);
        if (level <= ERROR)
        {
            std::string prefix = "[ " + getCurrentDate() + " ]  [ ERROR ]    ";
            cPrint(Colors::RED, prefix, message);
            addToFile(prefix + message);
        }
    }

    template<typename... Args>
    [[noreturn]] static void errorThrow(Args&&... args)
    {
        std::string message = argsToString(std::forward<Args>(args)...);
        if (level <= ERROR)
        {
            std::string prefix = "[ " + getCurrentDate() + " ]  [ ERROR ]    ";
            cPrint(Colors::RED, prefix, message);
            addToFile(prefix + message);
        }
        throw std::runtime_error(message);
    }




    template<typename... Args>
    static void critical(Args&&... args)
    {
        std::string message = argsToString(std::forward<Args>(args)...);
        if (level <= CRITICAL)
        {
            std::string prefix = "[ " + getCurrentDate() + " ]  [ CRITICAL ] ";
            cPrint(Colors::BG_RED, prefix, message);
            addToFile(prefix + message);
        }
    }

    template<typename... Args>
    [[noreturn]] static void criticalThrow(Args&&... args)
    {
        std::string message = argsToString(std::forward<Args>(args)...);
        if (level <= CRITICAL)
        {
            std::string prefix = "[ " + getCurrentDate() + " ]  [ CRITICAL ] ";
            cPrint(Colors::BG_RED, prefix, message);
            addToFile(prefix + message);
        }
        throw std::runtime_error(message);
    }
};