#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int FRAME_SIZE = 3;

int main()
{
    int pages[] = {1, 3, 0, 3, 5, 6, 3};
    int n = sizeof(pages) / sizeof(pages[0]);
    queue<int> q;
    int pageFaults = 0;

    for (int i = 0; i < n; i++)
    {
        int page = pages[i];
        bool found = false;

        // Check if the page is already in the queue
        queue<int> temp;
        while (!q.empty())
        {
            int p = q.front();
            if (p == page)
            {
                found = true;
            }
            else
            {
                temp.push(p);
            }
            q.pop();
        }

        while (!temp.empty())
        {
            q.push(temp.front());
            temp.pop();
        }

        if (!found)
        {
            if (q.size() >= FRAME_SIZE)
            {
                q.pop();
            }
            q.push(page);
            pageFaults++;
        }
    }

    cout << "LRU Page Faults: " << pageFaults << endl;

    return 0;
}
