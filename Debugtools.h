//
// Created by Jkurt on 7/4/2026.
//

#ifndef RUNEGUARDTACTICS_DEBUGTOOLS_H
#define RUNEGUARDTACTICS_DEBUGTOOLS_H
#pragma once

#include <chrono>
#include <iomanip>
#include <iostream>
#include <string_view>
// Please note this entire script was written by Codex. I wanted a quick way to test performance of functions.
namespace debugtools {

    inline void printFormattedNano(const long long nanoseconds) {
        const auto total = std::chrono::nanoseconds(nanoseconds);

        const auto minutes = std::chrono::duration_cast<std::chrono::minutes>(total);
        const auto seconds = std::chrono::duration_cast<std::chrono::seconds>(total - minutes);
        const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(total - minutes - seconds);
        const auto remainingNanoseconds = total - minutes - seconds - milliseconds;

        std::cout << std::setfill('0')
                  << std::setw(2) << minutes.count() << ":"
                  << std::setw(2) << seconds.count() << ":"
                  << std::setw(3) << milliseconds.count() << ":"
                  << std::setw(6) << remainingNanoseconds.count()
                  << std::setfill(' ');
    }

    template <typename Func>
    long long timeNano(Func function) {
        const auto start = std::chrono::steady_clock::now();

        function();

        const auto end = std::chrono::steady_clock::now();

        return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }

    template <typename Func>
    void printTimeNano(std::string_view label, Func function) {
        const auto ns = timeNano(function);

        std::cout << label << " took ";
        printFormattedNano(ns);
        std::cout << "\n";
    }

}
#endif //RUNEGUARDTACTICS_DEBUGTOOLS_H
