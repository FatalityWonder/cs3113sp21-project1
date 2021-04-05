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
    double untilization;
    double throughput;
    double turnaround;
    double waiting;
    double response;

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

        if (previous != current)
        {
            ++voluntary;

            // check if process is nonvoluntary rather than voluntary
            for (int j = i + 2; j < numInstructions; ++j)
            {
                if (previous == instructionList[j].pid)
                {
                    ++nonvoluntary;
                    --voluntary;
                }
            }
        }
      
        previous = current;
    }

    printf("%d\n", voluntary);
    printf("%d\n", nonvoluntary);
    printf("%.2f\n", 100.0);
    printf("%.2f\n", 0.0);
    printf("%.2f\n", 0.0);
    printf("%.2f\n", 0.0);
    printf("%.2f\n", 0.0);
    

    /** // test output
    printf("%d\n", numProcesses);
    printf("%d %d\n", numExecutionElements, numInstructions);

    for (int i = 0; i < numInstructions; ++i)
    {
        printf("%d %d %d\n", instructionList[i].pid, instructionList[i].burst, instructionList[i].priority);
    }
    **/
}
