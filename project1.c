#include <stdio.h>
#include <stdlib.h>

typedef struct InstructionData
{
    unsigned int pid;
    unsigned int burst;
    unsigned int priority;
} InstructionData;

int main(int argc, char *argv[])
{
    // input data, first two lines
    int numProcesses;
    int numExecutionElements;
    int numInstructions;
    
    // data to output
    int voluntary;
    int nonvoluntary;
    double utilization;
    double throughput;
    double turnaround;
    double waiting;
    double response;
    int totalTime;
    int totalWait;

    struct InstructionData* instructionList;

    FILE* file;

    // open if not stdin
    if (argc > 1)
    {
        file = fopen(argv[1], "r");
    } 

    // rean first two lines of the file in
    if (argc > 1)
    {
        fscanf(file, "%d\n", &numProcesses);
        fscanf(file, "%d %d\n", &numExecutionElements, &numInstructions);
    }
    else
    {
        fscanf(stdin, "%d\n", &numProcesses);
        fscanf(stdin, "%d %d\n", &numExecutionElements, &numInstructions);
    }

    // allocate memory for array
    instructionList = malloc(sizeof(InstructionData) * numInstructions);

    //initialize array
    for (int i = 0; i < numInstructions; ++i)
    {
        instructionList[i].pid = 0;
        instructionList[i].burst = 0;
        instructionList[i].priority = 0;
    }

    // read values of each process
    for (int i = 0; i < numInstructions; ++i)
    {
        if (argc > 1)
            fscanf(file, "%d %d %d\n", &instructionList[i].pid, &instructionList[i].burst, &instructionList[i].priority);
        else
            fscanf(stdin, "%d %d %d\n", &instructionList[i].pid, &instructionList[i].burst, &instructionList[i].priority);

    }

    // close if not stdin
    if (argc > 1)
        fclose(file);

    // count voluntary and non-voluntary switches
    voluntary = 1; // first switch skipped due to nothing else to compare to
    nonvoluntary = 0;
    int previous = instructionList[0].pid;
    int current;
    for (int i = 1; i < numInstructions; ++i)
    {
        current = instructionList[i].pid;

        // if same pid back to back then there is no switch
        if (previous != current)
        {
            ++voluntary; // assume voluntary until proven nonvoluntary

            // check if process is nonvoluntary rather than voluntary
            for (int j = i + 1; j < numInstructions; ++j)
            {
                if (previous == instructionList[j].pid)
                {
                    ++nonvoluntary;
                    --voluntary;
                    break;
                }
            }
        }
      
        previous = current;
    }

    // get total process time
    totalTime = 0;
    for (int i = 0; i < numInstructions; ++i)
    {
        totalTime += instructionList[i].burst;
    }

    // get total wait time
    int wait[numExecutionElements];
    totalWait = 0;
    int lastOccurance = 0;
    for (int i = 0; i < numExecutionElements; ++i)
    {
        wait[i] = 0;
        
        // check for last occurance of Pid
        for (int j = (numInstructions - 1); j >= 0; --j)
        {
            if (instructionList[j].pid == (i + 1))
            {
                lastOccurance = j;

                // simultaneous pid in instruction list
                if (j > 0 && instructionList[j].pid == instructionList[j - 1].pid)
                {
                    continue;
                }

                // last occurance
                break;
            }   
        }

        // count wait time
        for (int j = 0; j < lastOccurance; ++j)
            wait[i] += instructionList[j].burst;
    }

    totalWait = 0;
    for (int i = 0; i < numExecutionElements; ++i)
        totalWait += wait[i];

    // calculate cpu utilization
    // one process always occupied
    utilization = 100.0;

    // calculate throughput
    throughput = numExecutionElements * 1.0 / totalTime;

    // calculate turnaround time
    turnaround = 0.0;

    // calculate waiting time
    waiting = totalWait * 1.0 / numExecutionElements;

    // calculate response time
    response = 0.0;


    printf("%d\n", voluntary);
    printf("%d\n", nonvoluntary);
    printf("%.2f\n", utilization);
    printf("%.2f\n", throughput);
    printf("%.2f\n", 0.0);
    printf("%.2f\n", waiting);
    printf("%.2f\n", 0.0);
}
