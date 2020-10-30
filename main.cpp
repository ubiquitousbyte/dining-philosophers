#include <thread>
#include "inc/Philosopher.h"


static void show_usage(const std::string& name)
{
    std::cerr << "Usage: " << name << " <option(s)> PHILOSOPHERS "
              << "Options: \n"
              << "\t-h,--help\t\tShow this help message\n"
              << "\t-t,--time DURATION\t The upperbound of time in ms that each philosopher will think and eat. Default is a random number between 3 and 5.\n"
              << std::endl;
}

void sitAtTable(Philosopher *ph)
{
    ph->run();
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        show_usage(argv[0]);
        return 1;
    }

    std::string numberOfPhilosophers, time;
    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];
        if ((arg == "-h") || (arg == "--help"))
        {
            show_usage(argv[0]);
            return 0;
        }
        else if ((arg == "-t") || (arg == "--time"))
        {
            if (i + 1 < argc)
            {
                time = argv[i+1];
            }
            else
            {
                std:: cerr << "--time option requires one argument." << std::endl;
                show_usage(argv[0]);
                return 1;
            }
        }
        else
        {
            numberOfPhilosophers = argv[i];
        }
    }

    const uint32_t N = std::stoi(numberOfPhilosophers);

    std::vector<Philosopher> philosophers;
    philosophers.reserve(N);

    for (int i = 0; i < N; i++)
    {
        if (time.empty())
        {
            philosophers.emplace_back(Philosopher(i));
        }
        else
        {
            philosophers.emplace_back(Philosopher(i, std::stol(time)));
        }
    }

    std::thread philosopherThreads[N];

    for (int i = 0; i < N; i++)
    {
        std::thread philosopher (sitAtTable, &philosophers[i]);
        philosopherThreads[i] = std::move(philosopher);
    }

    for (std::thread &th : philosopherThreads)
    {
        if (th.joinable())
            th.join();
    }

    return 0;
}
