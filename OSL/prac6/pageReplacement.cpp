#include <bits/stdc++.h>
using namespace std;

int is_page_in_frame(int page, vector<int>& frame, int frame_size) {
    for (int i = 0; i < frame_size; i++) {
        if (frame[i] == page) {
            return 1; // Page is found in the frame (hit)
        }
    }
    return 0; // Page is not in the frame (miss)
}

void print_frame(vector<int>& frame, int frame_size, char hit_or_miss) {
    for (int i = 0; i < frame_size; i++) {
        if (frame[i] == -1) {
            cout << "  "; // Replace -1 with two spaces for alignment
        } else {
            cout << frame[i] << " ";
        }
    }
    cout << "| " << hit_or_miss << endl;
}

int fifo_page_replacement(int pages, vector<int>& pageArray, int frame_size) {
    vector<int> frame(frame_size, -1);
    int pageFaults = 0;
    int frameIndex = 0;

    for (int i = 0; i < pages; i++) {
        if (!is_page_in_frame(pageArray[i], frame, frame_size)) {
            pageFaults++;
            frame[frameIndex] = pageArray[i];
            print_frame(frame, frame_size, 'm');
            frameIndex = (frameIndex + 1) % frame_size;
        } else {
            print_frame(frame, frame_size, 'h');
        }
    }
    return pageFaults;
}

int get_least_recently_used_index(vector<int>& pageArray, vector<int>& frame, int frame_size, int current_index) {
    int least_recent = current_index;
    int index = -1;

    for (int i = 0; i < frame_size; i++) {
        for (int j = current_index - 1; j >= 0; j--) {
            if (frame[i] == pageArray[j]) {
                if (j < least_recent) {
                    least_recent = j;
                    index = i;
                }
                break;
            }
        }
    }

    return index;
}

int lru_page_replacement(int pages, vector<int>& pageArray, int frame_size) {
    vector<int> frame(frame_size, -1);
    int pageFaults = 0;

    for (int i = 0; i < pages; i++) {
        if (!is_page_in_frame(pageArray[i], frame, frame_size)) {
            pageFaults++;

            if (pageFaults <= frame_size) {
                for (int j = 0; j < frame_size; j++) {
                    if (frame[j] == -1) {
                        frame[j] = pageArray[i];
                        break;
                    }
                }
            } else {
                int replace_index = get_least_recently_used_index(pageArray, frame, frame_size, i);
                frame[replace_index] = pageArray[i];
            }
            print_frame(frame, frame_size, 'm');
        } else {
            print_frame(frame, frame_size, 'h');
        }
    }
    return pageFaults;
}

int get_farthest_page_in_future(vector<int>& pageArray, vector<int>& frame, int frame_size, int current_index, int pages) {
    int farthest = -1;
    int index = -1;

    for (int i = 0; i < frame_size; i++) {
        int found = 0;
        for (int j = current_index + 1; j < pages; j++) {
            if (frame[i] == pageArray[j]) {
                if (j > farthest) {
                    farthest = j;
                    index = i;
                }
                found = 1;
                break;
            }
        }
        if (found == 0) {
            return i;
        }
    }
    return index;
}

int optimal_page_replacement(int pages, vector<int>& pageArray, int frame_size) {
    vector<int> frame(frame_size, -1);
    int pageFaults = 0;

    for (int i = 0; i < pages; i++) {
        if (!is_page_in_frame(pageArray[i], frame, frame_size)) {
            pageFaults++;

            if (pageFaults <= frame_size) {
                for (int j = 0; j < frame_size; j++) {
                    if (frame[j] == -1) {
                        frame[j] = pageArray[i];
                        break;
                    }
                }
            } else {
                int replace_index = get_farthest_page_in_future(pageArray, frame, frame_size, i, pages);
                frame[replace_index] = pageArray[i];
            }
            print_frame(frame, frame_size, 'm');
        } else {
            print_frame(frame, frame_size, 'h');
        }
    }
    return pageFaults;
}

int main() {
    int pages;
    int frame_size;
    int algorithm_choice;
    int pageFaults;

    cout << "Enter the number of pages: ";
    cin >> pages;

    vector<int> pageArray(pages);
    cout << "Enter the page reference string: ";
    for (int i = 0; i < pages; i++) {
        cin >> pageArray[i];
    }

    cout << "Enter the frame size: ";
    cin >> frame_size;

    while (true) {
        cout << "Choose a page replacement algorithm:" << endl;
        cout << "1. FIFO" << endl;
        cout << "2. LRU" << endl;
        cout << "3. Optimal" << endl;
        cout << "4. Exit" << endl;
        cin >> algorithm_choice;

        if (algorithm_choice == 4) {
            cout << "Thanks for using our system !!\n";
            break;
        }

        switch (algorithm_choice) {
            case 1:
                pageFaults = fifo_page_replacement(pages, pageArray, frame_size);
                break;
            case 2:
                pageFaults = lru_page_replacement(pages, pageArray, frame_size);
                break;
            case 3:
                pageFaults = optimal_page_replacement(pages, pageArray, frame_size);
                break;
            default:
                cout << "Invalid choice" << endl;
                continue;
        }
        cout << "Total Page Faults: " << pageFaults << endl;
    }

    return 0;
}
