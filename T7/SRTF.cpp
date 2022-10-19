#include "Process.hpp"

int main(int argc, char const *argv[])
{
    auto processes = Process::addProcessesFromInput();

    std::sort(processes->begin(), processes->end(), Process::compareByAT);

    std::vector<int> burstTimeRemaining = {};
    for (auto i : *processes)
    {
        burstTimeRemaining.push_back(i.burstTime);
    }

    int currentTime = 0;
    int completed = 0;
    int prevTime = 0;

    int length = processes->size();
    while (completed != length)
    {
        int idx = -1;
        int mn = 99999999;

        for (int i = 0; i < length; i++)
        {
            auto &currentProcess = processes->at(i);
            if (currentProcess.arrivalTime <= currentTime && currentProcess.isCompleted == false)
            {
                if (burstTimeRemaining[i] < mn)
                {
                    mn = burstTimeRemaining[i];
                    idx = i;
                }
                if (burstTimeRemaining[i] == mn)
                {
                    if (currentProcess.arrivalTime < processes->at(idx).arrivalTime)
                    {
                        mn = burstTimeRemaining[i];
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1)
        {
            auto &processRemaining = processes->at(idx);
            if (burstTimeRemaining[idx] == processRemaining.burstTime)
            {
                processRemaining.completionTime = currentTime;
            }
            burstTimeRemaining[idx] -= 1;
            currentTime++;
            prevTime = currentTime;

            if (burstTimeRemaining[idx] == 0)
            {
                processRemaining.completionTime = currentTime;
                processRemaining.turnAroundTime = processRemaining.completionTime - processRemaining.arrivalTime;
                processRemaining.waitingTime = processRemaining.turnAroundTime - processRemaining.burstTime;
                processRemaining.isCompleted = true;
                completed++;
            }
        }
        else
        {
            currentTime++;
        }
    }

    

    std::cout << "ID\tAT\tBT\tCT\tTAT\tWT\n";
    for (auto &&i : *processes)
    {
        std::cout << i.id << "\t" << i.arrivalTime << "\t" << i.burstTime << "\t" << i.completionTime << "\t" << i.turnAroundTime << "\t" << i.waitingTime << "\n";
    }

    auto sum = std::accumulate(processes->begin(), processes->end(),0 , 
                                [](int i, const Process& p) {return p.waitingTime + i;});
    std::cout << "Average waiting time: " << (double) sum / processes->size() << std::endl;

    return 0;
}
