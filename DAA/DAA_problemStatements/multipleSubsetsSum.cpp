// multiple solutions

#include <bits/stdc++.h>
using namespace std;

void findSubsetSum(vector<vector<int>>& solutions, vector<int>& nums, int index, int k, int n, vector<int>& ans) {

    if(index >= n) {
        if(k == 0) {
            solutions.push_back(ans);
        }
        return;
    }
    
    ans.push_back(nums[index]);

    cout << "\nAdded the element : " << nums[index] << "\n\n"; 
    // take

    cout << "\n checking that the remaining element : " << k - nums[index] <<  " can be formed from the list : \n\n";
    findSubsetSum(solutions, nums, index+1, k - nums[index], n, ans);

    cout << "\n\nRemoving the element : " << nums[index] << " from the list !!\n\n";
    // not take
    ans.pop_back();

    cout << "\n\nChecking if the required number " << k << " can be formed from the list  !!\n\n";
    findSubsetSum(solutions, nums, index+1, k, n, ans);

}

void findSubset(vector<int>& nums, int k) {

    vector<vector<int>> solutions;
    vector<int> ans;
    int n = nums.size();
    int index = 0;

    findSubsetSum(solutions, nums, index, k, n, ans);

    if(solutions.size() > 0) {
        int i = 1;
        cout << "\nThe required subset that sum up to " << k << " are : \n";
        for(vector<int> subset: solutions)
        {
            cout << "[ ";
            for(int ele: subset)
                cout << ele << ", ";
            cout << "]\n"; 
        }
        cout << "\n\n";
    }
    else {
        cout << "The subset does not exist !!" << endl;
        return;
    }
}

int main()
{
    vector<int> nums = {1, 5, 4, 2, 3, 6, 8};
    findSubset(nums, 10);

    return 0;
}