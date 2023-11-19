#include <bits/stdc++.h>
using namespace std;

bool findSubsetSum(vector<int>& nums, int index, int k, int n, vector<int>& ans) {

    if(index >= n) {
        if(k == 0) {

            cout << "\n\nfound the solution !!\n\n";
            return true;
        }
        return false;
    }
    
    ans.push_back(nums[index]);

    cout << "\nAdded the element : " << nums[index] << "\n\n"; 
    // take

    cout << "\n checking that the remaining element : " << k - nums[index] <<  " can be formed from the list : \n\n";
    if(findSubsetSum(nums, index+1, k - nums[index], n, ans)) {

        return true;
    }

    cout << "\n\nRemoving the element : " << nums[index] << " from the list !!\n\n";
    // not take
    ans.pop_back();

    cout << "\n\nChecking if the required number " << k << " can be formed from the list  !!\n\n";
    if(findSubsetSum(nums, index+1, k, n, ans)) {
        return true;
    }

    return false;
}

void findSubset(vector<int>& nums, int k) {

    vector<int> ans;
    int n = nums.size();
    int index = 0;
    if(findSubsetSum(nums, index, k, n, ans)) {
        cout << "\nThe required subset is : \n";
        for(int ele: ans) {
            cout << ele << " ";
        }
        cout << endl;
        return;
    }
    else {
        cout << "The subset does not exist !!" << endl;
        return;
    }
}

int main() {

    vector<int> nums = {1, 5, 4, 2, 3, 6, 8};
    findSubset(nums, 10);
    return 0;
}