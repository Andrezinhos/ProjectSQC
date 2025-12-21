#include <iostream>
#include "ChronoTimer.hpp"
#include <chrono>
#include <memory>
#include <windows.h>
#include "states.hpp"

Timer::Timer(int d) : duration(d), running(false) {}

Timer::~Timer(){
    stop();
}

void Timer::start(){
    running = true;
    worker = std::thread([this]() {
        std::this_thread::sleep_for(std::chrono::seconds(duration));
        if (running) {
            HWND hwnd = GetConsoleWindow();
            MessageBoxW(
                hwnd,
                L"Time Over",
                L"SQC CHRONO",
                MB_OK | MB_ICONINFORMATION | MB_TOPMOST
            );
            //std::cout << "Time Over\n";
        }
    });
}

void Timer::stop(){
    running = false;
    if (worker.joinable()){
        worker.join();
    }
}

ChronoTime::ChronoTime() : timer(nullptr) {}

ChronoTime::~ChronoTime(){
    if (timer) {
        timer->stop();
    }
}

void ChronoTime::setTimer(int seconds) {
    if (timer) {
        timer->stop();
    }
    timer = std::make_unique<Timer>(seconds);
    timer->start();
}