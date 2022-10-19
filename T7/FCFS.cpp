
#include "Process.hpp"

int main(int argc, char const *argv[])
{
    auto processes = Process::addProcessesFromInput();

    std::sort(processes->begin(), processes->end(), Process::compareByAT);

    int waitOffset = processes->at(0).arrivalTime;

    for (size_t i = 0; i < processes->size(); i++)
    {
        auto&& process = processes->at(i);
        if (i == 0)
        {
            process.completionTime = process.burstTime;
        }
        else {
            auto&& prevProcess = processes->at(i-1);
            process.completionTime = prevProcess.completionTime + process.burstTime;
        }
        process.turnAroundTime = process.completionTime - process.arrivalTime;
        process.waitingTime = process.turnAroundTime - process.burstTime + waitOffset;
    }

    std::sort(processes->begin(), processes->end(), Process::compareById);


    std::cout << "ID\tAT\tBT\tCT\tTAT\tWT\n";
    for (auto &&i : *processes)
    {
        std::cout << i.id << "\t" << i.arrivalTime << "\t" << i.burstTime << "\t" << i.completionTime << "\t" <<
             i.turnAroundTime << "\t" << i.waitingTime << "\n";
    }

    auto sum = std::accumulate(processes->begin(), processes->end(),0 , 
                                [](int i, const Process& p) {return p.waitingTime + i;});

    std::cout << "Average waiting time: " << (double) sum / processes->size() << std::endl;

    return 0;
}



