#include<bits/stdc++.h>
using namespace std;

int knapsackSolver(vector<int> &weight, vector<int> &profit, int n, int maxWeight) {

    int dp[n+1][maxWeight+2];
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= maxWeight; j++) {
            if(i==0 || j==0) {
                dp[i][j] = 0;
            }
            else {
                dp[i][j] = 0;
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int j = i; j <= maxWeight; j++) {
            if(weight[i-1] <= j) {
                dp[i][j] = max(profit[i-1]+dp[i-1][j-weight[i-1]], dp[i-1][j]);

            } else {
                dp[i][j] = dp[i-1][j];
            }
        }
    }

    cout << "\nTabulization of the items : \n\n";
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= maxWeight; j++) {
            cout << dp[i][j] << "\t";
        }
        cout << endl;
    }

    return dp[n][maxWeight];

}

int main() {
    int n, capacity;
    cout << "Enter the number of elements : ";
    cin >> n;
    vector<int> weight;
    vector<int> profit;
    cout << "Enter the weight of the bag : ";
    cin >> capacity;
    cout << "Enter the weights of the "<<n <<" items : "<<endl;
    for(int i = 0; i < n; i++) {
        int temp;
        cin >> temp;
        weight.push_back(temp);
    }

    cout << "Enter the profits of the "<<n<<" items : "<<endl;
    for(int i = 0; i < n; i++) {
        int temp;
        cin >> temp;
        profit.push_back(temp);
    }


    int maxProfit = knapsackSolver(weight, profit, n, capacity);
    cout << "The maximum profit that can be obtained is : "<<maxProfit<<endl;
    return 0;
}