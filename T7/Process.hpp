#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <utility>

class Process
{
public:
    int id;
    int arrivalTime;
    int burstTime;
    int completionTime = -1;
    int turnAroundTime = -1;
    int waitingTime = -1;
    int responseTime = -1;
    bool isCompleted = false;

    static void addProcessesFromInput(std::vector<Process> *processes)
    {
        int n;
        std::cout << "Size: ";
        std::cin >> n;

        for (int i = 0; i < n; i++)
        {
            std::cout << "PID " << i << ":\n";
            int arrivalTime, burstTime;
            std::cout << "Arrival time: ";
            std::cin >> arrivalTime;

            std::cout << "Burst Time: ";
            std::cin >> burstTime;
            processes->push_back({i, arrivalTime, burstTime});
            std::cout << "\n\n";
        }
    }

    static std::vector<Process> *addProcessesFromInput()
    {
        auto processes = new std::vector<Process>{};
        Process::addProcessesFromInput(processes);
        return processes;
    }

    static bool compareById(Process& p1, Process& p2)
    {
        return p1.id < p2.id;
    }

    static bool compareByAT(Process& p1, Process& p2)
    {
        return p1.arrivalTime < p2.arrivalTime;
    }

    static bool compareByBT(Process& p1, Process& p2) {
        return p1.burstTime < p2.burstTime;
    }

    static bool compareByBTRev(Process& p1, Process& p2) {
        return p1.burstTime < p2.burstTime;
    }

    static bool compareBySJF(Process& p1, Process& p2) {
        if (p1.arrivalTime != p2.arrivalTime) {
            return p1.arrivalTime < p2.arrivalTime;
        }
        return p1.burstTime < p2.burstTime;
    }


    static int addWT(Process& p1, Process& p2) {
        return p1.waitingTime + p2.waitingTime;
    }
};
