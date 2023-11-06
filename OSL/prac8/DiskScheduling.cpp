#include <bits/stdc++.h>
using namespace std;

// Function to calculate total seek time for FCFS
int calculateTotalSeekTimeFCFS(vector<int>& requestQueue, int initialHead) {
    int seekTime = 0;
    cout << "\nSeek Sequence: " << initialHead; // Print the initial head position
    for (int i = 0; i < requestQueue.size(); i++) {
        int seek = abs(initialHead - requestQueue[i]);
        seekTime += seek;
        cout << " -> " << requestQueue[i]; // Print the request being serviced
        initialHead = requestQueue[i];
    }
    cout << "\nTotal number of seek operations: " << seekTime;
    float avgSeekTime = static_cast<float>(seekTime) / requestQueue.size();
    cout << "\nAverage Seek Time is " << avgSeekTime << "\n\n";
    return seekTime;
}

// Function to calculate total seek time for SSTF
int calculateTotalSeekTimeSSTF(vector<int>& requestQueue, int initialHead) {
    int seekTime = 0;
    int currentPosition = initialHead;

    vector<int> visited(requestQueue.size(), 0);
    vector<int> seekSequence(requestQueue.size(), -1);

    for (int i = 0; i < requestQueue.size(); i++) {
        int shortestSeek = 999999;
        int nextRequest;

        for (int j = 0; j < requestQueue.size(); j++) {
            if (!visited[j]) {
                int seek = abs(currentPosition - requestQueue[j]);
                if (seek < shortestSeek) {
                    shortestSeek = seek;
                    nextRequest = j;
                }
            }
        }

        seekTime += shortestSeek;
        visited[nextRequest] = 1;
        currentPosition = requestQueue[nextRequest];
        seekSequence[i] = requestQueue[nextRequest];
    }

    cout << "\nSeek Sequence: " << initialHead;
    for (int i = 0; i < requestQueue.size(); i++) {
        if (seekSequence[i] != -1) {
            cout << " -> " << seekSequence[i];
        }
    }
    cout << "\nTotal number of seek operations: " << seekTime;

    float avgSeekTime = static_cast<float>(seekTime) / requestQueue.size();
    cout << "\nAverage Seek Time is " << avgSeekTime << "\n\n";
    return seekTime;
}

// Function to calculate total seek time for LOOK
int calculateTotalSeekTimeLook(vector<int>& requestQueue, int initialHead, int maxRange, int minRange) {
    int seekTime = 0;
    int headPosition = initialHead;
    int startIndex = 0;

    sort(requestQueue.begin(), requestQueue.end());

    for (int i = 0; i < requestQueue.size(); i++) {
        if (requestQueue[i] > headPosition) {
            startIndex = i;
            break;
        }
    }

    int seekRight = abs(requestQueue[startIndex] - headPosition);
    int seekLeft = abs(requestQueue[startIndex - 1] - headPosition);

    cout << "\nSeekRight: " << seekRight;
    cout << "\nSeekLeft: " << seekLeft;

    int direction;
    cout << "\n1. Left Direction (Lower values)";
    cout << "\n2. Right Direction (Greater values)";
    cout << "\nChoose the direction: ";
    cin >> direction;

    if (direction == 1) {
        cout << "\nSeek time towards left is minimum so moving towards left...\n";
        cout << "----------------------------------------------------------------------\n";
        cout << "Seek Sequence: " << headPosition;

        for (int i = startIndex - 1; i >= 0; i--) {
            seekTime += abs(requestQueue[i] - headPosition);
            headPosition = requestQueue[i];
            cout << " -> " << headPosition;
        }
        for (int i = startIndex; i < requestQueue.size(); i++) {
            seekTime += abs(requestQueue[i] - headPosition);
            headPosition = requestQueue[i];
            cout << " -> " << headPosition;
        }
    } else if (direction == 2) {
        cout << "\nSeek time towards right is minimum or equal so moving towards right...\n";
        cout << "----------------------------------------------------------------------\n";
        cout << "Seek Sequence: " << headPosition;

        for (int i = startIndex; i < requestQueue.size(); i++) {
            seekTime += abs(requestQueue[i] - headPosition);
            headPosition = requestQueue[i];
            cout << " -> " << headPosition;
        }
        for (int i = startIndex - 1; i >= 0; i--) {
            seekTime += abs(requestQueue[i] - headPosition);
            headPosition = requestQueue[i];
            cout << " -> " << headPosition;
        }
    }

    cout << "\nTotal number of seek operations: " << seekTime;

    float avgSeekTime = static_cast<float>(seekTime) / requestQueue.size();
    cout << "\nAverage Seek Time is " << avgSeekTime << "\n\n";
    return seekTime;
}


int calculateTotalSeekTimeC_Look(vector<int>& requestQueue, int numRequests, int initialHead, int maxRange, int minRange){
    int seekTime = 0;
    int headPosition = initialHead;
    int startIndex = 0;

    // Sort the requests
    for (int i = 0; i < numRequests - 1; i++) {
        for (int j = 0; j < numRequests - 1 - i; j++) {
            if (requestQueue[j] > requestQueue[j + 1]) {
                int temp = requestQueue[j];
                requestQueue[j] = requestQueue[j + 1];
                requestQueue[j + 1] = temp;
            }
        }
    }
    //find the greater index
    for (int i = 0; i < numRequests; i++) {
        if (requestQueue[i] > headPosition) {
            startIndex = i;
            break;
        }
    }

    //decide the direction
    int seekRight = abs(requestQueue[startIndex] - headPosition);
    int seekLeft = abs(requestQueue[startIndex - 1] - headPosition);
    printf("\nSeekRight: %d", seekRight);
    printf("\nSeekLeft: %d", seekLeft);

    int direction;
    printf("\n1.Left Direction(Lower values)");
    printf("\n2.Right Direction(Greater values)");
    printf("\nChoose the direction: ");
    scanf("%d", &direction);
    if(direction == 1){ //Left direction
        printf("\nSeek time towards left is minimum so moving towards left...");
        printf("\n----------------------------------------------------------------------");
        printf("\nSeek Sequence: %d", headPosition);

        for (int i = startIndex - 1; i >= 0; i--) {
            seekTime += abs(requestQueue[i] - headPosition);
            headPosition = requestQueue[i];
            printf(" -> %d", headPosition);
        }
        seekTime += abs(requestQueue[numRequests-1] - headPosition);
        headPosition = requestQueue[numRequests-1];
        printf(" -> %d", headPosition);
        for (int i = numRequests-2; i>=startIndex; i--) {
            seekTime += abs(requestQueue[i] - headPosition);
            headPosition = requestQueue[i];
            printf(" -> %d", headPosition);
        }
    }
    else if(direction == 2){
        printf("\nSeek time towards right is minimum or equal so moving towards right...");
        printf("\n----------------------------------------------------------------------");
        printf("\nSeek Sequence: %d", headPosition);

        for (int i = startIndex; i < numRequests; i++) {
            seekTime += abs(requestQueue[i] - headPosition);
            headPosition = requestQueue[i];
            printf(" -> %d", headPosition);
        }
        seekTime += abs(requestQueue[0] - headPosition);
        headPosition = requestQueue[0];
        printf(" -> %d", headPosition);
        for (int i = 1; i <=startIndex-1; i++) {
            seekTime += abs(requestQueue[i] - headPosition);
            headPosition = requestQueue[i];
            printf(" -> %d", headPosition);
        }
    }

    printf("\nTotal number of seek operations: %d", seekTime);

    float avgSeekTime = (float)seekTime / numRequests;
    printf("\nAverage Seek Time is %.2f\n", avgSeekTime);
    printf("\n");
    return seekTime;
}


int calculateTotalSeekTimeSCAN(vector<int>& requestQueue, int numRequests, int initialHead, int maxRange, int minRange) {
    int seekTime = 0;
    int headPosition = initialHead;
    int startIndex = 0;

    // Sort the requests
    for (int i = 0; i < numRequests - 1; i++) {
        for (int j = 0; j < numRequests - 1 - i; j++) {
            if (requestQueue[j] > requestQueue[j + 1]) {
                int temp = requestQueue[j];
                requestQueue[j] = requestQueue[j + 1];
                requestQueue[j + 1] = temp;
            }
        }
    }
    //find the greater index
    for (int i = 0; i < numRequests; i++) {
        if (requestQueue[i] > headPosition) {
            startIndex = i;
            break;
        }
    }

    //decide the direction
    int seekRight = abs(requestQueue[startIndex] - headPosition);
    int seekLeft = abs(requestQueue[startIndex - 1] - headPosition);
    printf("\nSeekRight: %d", seekRight);
    printf("\nSeekLeft: %d", seekLeft);

    int direction;
    printf("\n1.Left Direction(Lower values)");
    printf("\n2.Right Direction(Greater values)");
    printf("\nChoose the direction: ");
    scanf("%d", &direction);
    if(direction == 1){ //Left direction
        printf("\nSeek time towards left is minimum so moving towards left...");
        printf("\n----------------------------------------------------------------------");
        printf("\nSeek Sequence: %d", headPosition);

        for (int i = startIndex - 1; i >= 0; i--) {
            seekTime += abs(requestQueue[i] - headPosition);
            headPosition = requestQueue[i];
            printf(" -> %d", headPosition);
        }
        seekTime += abs(minRange - headPosition);
        headPosition = minRange;
        printf(" -> %d", headPosition);
        for (int i = startIndex; i < numRequests; i++) {
            seekTime += abs(requestQueue[i] - headPosition);
            headPosition = requestQueue[i];
            printf(" -> %d", headPosition);
        }
    }
    else if(direction == 2){
        printf("\nSeek time towards right is minimum or equal so moving towards right...");
        printf("\n----------------------------------------------------------------------");
        printf("\nSeek Sequence: %d", headPosition);

        for (int i = startIndex; i < numRequests; i++) {
            seekTime += abs(requestQueue[i] - headPosition);
            headPosition = requestQueue[i];
            printf(" -> %d", headPosition);
        }
        seekTime += abs(maxRange - headPosition);
        headPosition = maxRange;
        printf(" -> %d", headPosition);
        for (int i = startIndex - 1; i >= 0; i--) {
            seekTime += abs(requestQueue[i] - headPosition);
            headPosition = requestQueue[i];
            printf(" -> %d", headPosition);
        }
    }

    printf("\nTotal number of seek operations: %d", seekTime);

    float avgSeekTime = (float)seekTime / numRequests;
    printf("\nAverage Seek Time is %.2f\n", avgSeekTime);
    printf("\n");
    return seekTime;
}

// Function to calculate total seek time for C-SCAN
int calculateTotalSeekTimeC_SCAN(vector<int>& requestQueue, int numRequests, int initialHead, int maxRange, int minRange){
    int seekTime = 0;
    int headPosition = initialHead;
    int startIndex = 0;

    // Sort the requests
    for (int i = 0; i < numRequests - 1; i++) {
        for (int j = 0; j < numRequests - 1 - i; j++) {
            if (requestQueue[j] > requestQueue[j + 1]) {
                int temp = requestQueue[j];
                requestQueue[j] = requestQueue[j + 1];
                requestQueue[j + 1] = temp;
            }
        }
    }
    //find the greater index
    for (int i = 0; i < numRequests; i++) {
        if (requestQueue[i] > headPosition) {
            startIndex = i;
            break;
        }
    }

    //decide the direction
    int seekRight = abs(requestQueue[startIndex] - headPosition);
    int seekLeft = abs(requestQueue[startIndex - 1] - headPosition);
    printf("\nSeekRight: %d", seekRight);
    printf("\nSeekLeft: %d", seekLeft);

    int direction;
    printf("\n1.Left Direction(Lower values)");
    printf("\n2.Right Direction(Greater values)");
    printf("\nChoose the direction: ");
    scanf("%d", &direction);
    if(direction == 1){
        printf("\nSeek time towards left is minimum so moving towards left...");
        printf("\n----------------------------------------------------------------------");
        printf("\nSeek Sequence: %d", headPosition);

        for (int i = startIndex - 1; i >= 0; i--) {
            seekTime += abs(requestQueue[i] - headPosition);
            headPosition = requestQueue[i];
            printf(" -> %d", headPosition);
        }
        seekTime += abs(minRange - headPosition);
        headPosition = minRange;
        printf(" -> %d", headPosition);
        seekTime += abs(maxRange - headPosition);
        headPosition = maxRange;
        printf(" -> %d", headPosition);
        for (int i = numRequests-1; i >= startIndex; i--) {
            seekTime += abs(requestQueue[i] - headPosition);
            headPosition = requestQueue[i];
            printf(" -> %d", headPosition);
        }
    }
    else if(direction == 2){
        printf("\nSeek time towards right is minimum or equal so moving towards right...");
        printf("\n----------------------------------------------------------------------");
        printf("\nSeek Sequence: %d", headPosition);

        for (int i = startIndex; i < numRequests; i++) {
            seekTime += abs(requestQueue[i] - headPosition);
            headPosition = requestQueue[i];
            printf(" -> %d", headPosition);
        }
        seekTime += abs(maxRange - headPosition);
        headPosition = maxRange;
        printf(" -> %d", headPosition);
        seekTime += abs(minRange - headPosition);
        headPosition = minRange;
        printf(" -> %d", headPosition);
        for (int i = 0; i <=startIndex-1; i++) {
            seekTime += abs(requestQueue[i] - headPosition);
            headPosition = requestQueue[i];
            printf(" -> %d", headPosition);
        }
    }

    printf("\nTotal number of seek operations: %d", seekTime);

    float avgSeekTime = (float)seekTime / numRequests;
    printf("\nAverage Seek Time is %.2f\n", avgSeekTime);
    printf("\n");
    return seekTime;
}

int main() {
    int choice, numRequests, initialHead, maxRange, minRange, seekTime = 0;
    cout << "Enter the maximum range of the disk: ";
    cin >> maxRange;
    cout << "Enter the minimum range of the disk: ";
    cin >> minRange;

    cout << "Enter the number of requests: ";
    cin >> numRequests;
    vector<int> requestQueue(numRequests);

    cout << "Enter the requests: ";
    for (int i = 0; i < numRequests; i++) {
        cin >> requestQueue[i];
    }

    cout << "Enter the initial head position: ";
    cin >> initialHead;

    while (true) {
        cout << "-----Disk Scheduling Algorithms-----\n";
        cout << "------------------------------------\n";
        cout << "1. FCFS\n";
        cout << "2. SSTF\n";
        cout << "3. SCAN\n";
        cout << "4. C-SCAN\n";
        cout << "5. LOOK\n";
        cout << "6. C-LOOK\n";
        cout << "7. Exit\n";
        cout << "Choose the Disk scheduling Algorithm: ";
        cin >> choice;

        if (choice == 7) {
            cout << "\nThank you for using system...\n";
            break;
        }

        switch (choice) {
            case 1:
                cout << "\n-------------------------FCFS------------------------";
                cout << "\n-----------------------------------------------------";
                seekTime = calculateTotalSeekTimeFCFS(requestQueue, initialHead);
                break;
            case 2:
                cout << "\n-------------------------SSTF------------------------";
                cout << "\n-----------------------------------------------------";
                seekTime = calculateTotalSeekTimeSSTF(requestQueue, initialHead);
                break;
            case 3:
                cout << "\n-------------------------SCAN------------------------";
                cout << "\n-----------------------------------------------------";
                seekTime = calculateTotalSeekTimeSCAN(requestQueue, numRequests, initialHead, maxRange, minRange);
                break;
            case 4:
                cout << "\n------------------------C-SCAN-----------------------";
                cout << "\n-----------------------------------------------------";
                seekTime = calculateTotalSeekTimeC_SCAN(requestQueue, numRequests, initialHead, maxRange, minRange);
                break;
            case 5:
                cout << "\n-------------------------LOOK------------------------";
                cout << "\n-----------------------------------------------------";
                seekTime = calculateTotalSeekTimeLook(requestQueue, initialHead, maxRange, minRange);
                break;
            case 6:
                cout << "\n------------------------C-LOOK------------------------";
                cout << "\n-----------------------------------------------------";
                seekTime = calculateTotalSeekTimeC_Look(requestQueue, numRequests, initialHead, maxRange, minRange);
                break;
            default:
                cout << "\nInvalid choice! Please select a valid option.\n";
                break;
        }
    }

    return 0;
}
