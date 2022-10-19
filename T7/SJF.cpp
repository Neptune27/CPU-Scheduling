#include "Process.hpp"

int main(int argc, char const *argv[])
{
    auto processes = Process::addProcessesFromInput();

    std::sort(processes->begin(), processes->end(), Process::compareBySJF);

    std::vector<Process> processesByTime = {};
    int processTime = 0;
    std::vector<Process> tempProcess = {};
    for (int i = 0; i < processes->size(); i++)
    {
        auto currentProcesses = processes->at(i);
        if (i == 0)
        {
            processesByTime.push_back(processes->at(i));
            processTime += currentProcesses.burstTime + currentProcesses.arrivalTime;
            continue;
        }
        if (currentProcesses.arrivalTime <= processTime)
        {
            tempProcess.push_back(currentProcesses);
        }
        else
        {
            std::sort(tempProcess.begin(), tempProcess.end(), Process::compareByBT);
            for (auto &&i : tempProcess)
            {
                processesByTime.push_back(i);
            }
            tempProcess.clear();
            tempProcess.push_back(currentProcesses);
        }
    }

    std::sort(tempProcess.begin(), tempProcess.end(), Process::compareByBT);
    for (auto &&i : tempProcess)
    {
        processesByTime.push_back(i);
    }



    int waitOffset = processesByTime.at(0).arrivalTime;

    for (size_t i = 0; i < processesByTime.size(); i++)
    {
        auto &&process = processesByTime.at(i);
        if (i == 0)
        {
            process.completionTime = process.burstTime + process.arrivalTime;
        }
        else
        {
            auto &&prevProcess = processesByTime.at(i - 1);
            process.completionTime = prevProcess.completionTime + process.burstTime;
        }
        process.turnAroundTime = process.completionTime - process.arrivalTime;
        process.waitingTime = process.turnAroundTime - process.burstTime + waitOffset;
    }

    std::sort(processesByTime.begin(), processesByTime.end(), Process::compareById);

    std::cout << "ID\tAT\tBT\tCT\tTAT\tWT\n";
    for (auto &&i : processesByTime)
    {
        std::cout << i.id << "\t" << i.arrivalTime << "\t" << i.burstTime << "\t" << i.completionTime << "\t" << i.turnAroundTime << "\t" << i.waitingTime << "\n";
    }

    auto sum = std::accumulate(processesByTime.begin(), processesByTime.end(), 0,
                               [](int i, const Process &p)
                               { return p.waitingTime + i; });

    std::cout << "Average waiting time: " << (double)sum / processes->size() << std::endl;

    return 0;
}
