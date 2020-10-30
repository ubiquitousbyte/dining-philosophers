//
// Created by nas on 30.10.20.
//

#ifndef DINING_PHILOSOPHERS_PHILOSOPHER_H
#define DINING_PHILOSOPHERS_PHILOSOPHER_H
#include <iostream>
#include <chrono>
#include <random>
#include <mutex>

const int NUM_OF_CHOPSTICKS = 5;

// False means that the chopstick is not being used
// True means that it is being used
bool chopsticks[NUM_OF_CHOPSTICKS] = {false, false, false, false, false};
std::mutex m = {};

class Philosopher
{
public:
    explicit Philosopher(int32_t idx): state{State::THINKING}, id{idx} {};
    Philosopher(int32_t idx, uint64_t dur): state{State::THINKING}, id{idx}, duration{dur} {};
private:
    enum State
    {
        THINKING,
        EATING
    };
    Philosopher::State state;
    int32_t id;
    uint64_t duration = random() % 5+3;
    uint8_t numberOfMeals = 0;
public:
    void eat();
    void think();
    void run();
    static void pickUpChopstick(bool &chopstick);
    static void putDownChopstick(bool &chopstick);
};

void Philosopher::eat()
{
    state = State::EATING;
    std::cout << "Philosopher " << id << " is eating.\n";
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    while (state == State::EATING)
    {
        if (std::chrono::steady_clock::now() - start > std::chrono::milliseconds(duration))
        {
            ++numberOfMeals;
            break;
        }
    }
}

void Philosopher::think()
{
    state = State::THINKING;
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    while (state == State::THINKING)
    {
        if (std::chrono::steady_clock::now() - start > std::chrono::milliseconds(duration)) { break; }
    }
}

void Philosopher::run() {
    while (true)
    {
        think();

     /*   int first = id;
        int second = (id == 0) ? NUM_OF_CHOPSTICKS - 1 : id - 1;*/
        int first = id % NUM_OF_CHOPSTICKS;
        int second = (first == 0) ? NUM_OF_CHOPSTICKS - 1 : first - 1;
        if (chopsticks[first] == chopsticks[second])
        {
            if (!chopsticks[first])
            {
                m.lock();
                pickUpChopstick(chopsticks[first]);
                pickUpChopstick(chopsticks[second]);
                std::cout << "#" << id << " holding chopsticks (" << first << "," << second << ").\n";
                m.unlock();
                eat();
                m.lock();
                putDownChopstick(chopsticks[first]);
                putDownChopstick(chopsticks[second]);
                std::cout << "#" << id << " releasing chopsticks (" << first << "," << second << ").\n";
                m.unlock();
            }
        }

        if (numberOfMeals == 4)
        {
            std::cout << "Philosopher " << id << " ate enough and left the table.\n";
            break;
        }
    }
}

void Philosopher::putDownChopstick(bool &chopstick) {
    chopstick = false;
}

void Philosopher::pickUpChopstick(bool &chopstick) {
    chopstick = true;
}

#endif //DINING_PHILOSOPHERS_PHILOSOPHER_H
