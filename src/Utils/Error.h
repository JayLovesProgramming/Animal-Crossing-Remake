#pragma once

#include <iostream>
#include <fstream>
#include <ctime>

class ErrorHandler
{
public:
    // inline static void DumpCrashInfo(const std::string &message)
    // {
    //     std::ofstream crashLog("crash_log.txt", std::ios::app);
    //     if (crashLog.is_open())
    //     {
    //         // Get the current time
    //         std::time_t now = std::time(nullptr);
    //         char timeBuffer[100];
    //         std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

    //         crashLog << "[" << timeBuffer << "] Error: " << message << std::endl;
    //         crashLog.close();
    //     }
    //     else
    //     {
    //         std::cerr << "Failed to write to crash log!" << std::endl;
    //     }
    // };
    // inline static void ShowErrorMessageBox(const std::string &message)
    // {
    //     MessageBoxA(NULL, message.c_str(), "Error", MB_ICONERROR | MB_OK);
    //     box
    // };
};
