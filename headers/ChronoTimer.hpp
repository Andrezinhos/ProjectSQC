#pragma once
#include <thread>
#include <string>
#include <atomic>
#include <memory>

struct Timer{
    int duration;
    std::atomic<bool> running;
    std::thread worker;

    Timer(int d);
    ~Timer();

    void start();
    void stop();
};

class ChronoTime{
private:
    std::unique_ptr<Timer> timer;
public:
    ChronoTime();
    ~ChronoTime();

    void setTimer(int seconds);
};