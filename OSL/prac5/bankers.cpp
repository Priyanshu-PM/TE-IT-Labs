#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int remaining_need[100][100], allocation[100][100], maximumDemands[100][100], availableResources[100];
bool isProcessFinished[100];
int safeSequence[100];

void isSystemSafe(int numProcesses, int numResources)
{
    int i, j, work[100], count = 0;
    for (i = 0; i < numResources; i++)
        work[i] = availableResources[i];

    for (i = 0; i < 100; i++)
        isProcessFinished[i] = false;

    while (count < numProcesses)
    {
        bool canAllocate = false;

        for (i = 0; i < numProcesses; i++)
        {
            if (!isProcessFinished[i])
            {
                for (j = 0; j < numResources; j++)
                {
                    if (work[j] < remaining_need[i][j])
                    {
                        break;
                    }
                }
                if (j == numResources)
                {
                    for (j = 0; j < numResources; j++)
                    {
                        work[j] += allocation[i][j];
                    }

                    safeSequence[count++] = i;
                    isProcessFinished[i] = true;
                    canAllocate = true;
                }
            }
        }

        if (!canAllocate)
        {
            cout << "System Is not safe" << endl;
            return;
        }
    }

    cout << "System is in a safe state" << endl;
    cout << "Safe sequence: ";
    for (i = 0; i < numProcesses; i++)
        cout << safeSequence[i] << " ";
    cout << endl;
}

void needMatrix(int numProcesses, int numResources)
{
    for (int i = 0; i < numProcesses; i++)
    {
        for (int j = 0; j < numResources; j++)
        {
            remaining_need[i][j] = maximumDemands[i][j] - allocation[i][j];
        }
    }
}

int main()
{
    int i, j, numProcesses, numResources;
    int processIndex, resourceRequest[100];
    cout << "Enter the number of processes and resources: ";
    cin >> numProcesses >> numResources;

    cout << "Enter the available resources:" << endl;
    for (i = 0; i < numResources; i++)
    {
        cin >> availableResources[i];
    }

    cout << "Enter the Allocation Matrix:" << endl;
    for (i = 0; i < numProcesses; i++)
    {
        for (j = 0; j < numResources; j++)
        {
            cin >> allocation[i][j];
        }
    }

    cout << "Enter the matrix for maximum demand of each process:" << endl;
    for (i = 0; i < numProcesses; i++)
    {
        for (j = 0; j < numResources; j++)
        {
            cin >> maximumDemands[i][j];
        }
    }

    needMatrix(numProcesses, numResources);

    while (true)
    {
        cout << "1) Calculate Need Matrix" << endl;
        cout << "2) Check safety" << endl;
        cout << "3) Request Resource" << endl;
        cout << "4) Exit" << endl;
        cout << "Enter your choice:";
        int choice;
        cin >> choice;

        if (choice == 4)
        {
            cout << "\nThank you for using system..." << endl;
            break;
        }

        switch (choice)
        {
        case 1:
            needMatrix(numProcesses, numResources);
            break;
        case 2:
            isSystemSafe(numProcesses, numResources);
            break;
        case 3:
            cout << "Enter the process number for resource request: ";
            cin >> processIndex;

            cout << "Enter the requested instances of Each: ";
            for (i = 0; i < numResources; i++)
            {
                cin >> resourceRequest[i];
            }

            for (i = 0; i < numResources; i++)
            {
                if (remaining_need[processIndex][i] < resourceRequest[i] || resourceRequest[i] > availableResources[i])
                {
                    cout << "Cannot request" << endl;
                    break;
                }
            }

            if (i == numResources)
            {
                for (i = 0; i < numResources; i++)
                {
                    allocation[processIndex][i] += resourceRequest[i];
                    availableResources[i] -= resourceRequest[i];
                    remaining_need[processIndex][i] -= resourceRequest[i];
                }
                isSystemSafe(numProcesses, numResources);
            }
            break;
        default:
            cout << "\nInvalid Choice, Try again..." << endl;
            break;
        }
    }
    return 0;
}
