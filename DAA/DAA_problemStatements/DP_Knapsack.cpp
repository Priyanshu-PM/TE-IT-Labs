// Write a program to implement 0/1 knapsack using dynamic 
// programming and also find the maximum profit.
// Number of objects n = 4, Knapsack Capacity M = 5, Weights (W1, 
// W2, W3, W4) = (2, 3, 4, 5) and profits (P1, P2, P3, P4) = (3, 4, 5, 6).

#include <bits/stdc++.h>
using namespace std;

void dynamic_knapsack(vector<int>& weight, vector<int>& profit, int n, int maxWeight)
{
    vector<vector<int>> dp(n+1, vector<int>(maxWeight+1, 0));

    for(int i = 1; i <= n; i++)
    {
        for(int w = 1; w <= maxWeight; w++)
        {
            if(weight[i-1] <= w)
            {
                dp[i][w] = max(profit[i-1] + dp[i-1][w - weight[i-1]], dp[i-1][w]);
            }
            else
            {
                dp[i][w] = dp[i-1][w];
            }
        }
    }

    int i = n;
    int w = maxWeight;
    vector<int> selectedItems;
    while(i > 0 && w > 0)
    {
        if(dp[i][w] != dp[i-1][w])
        {
            selectedItems.push_back(i);
            w -= weight[i-1];
        }
        i--;
    }

    cout << "\nSelected items are : \n";
    for(int i = selectedItems.size()-1; i >= 0; i--)
    {
        cout << selectedItems[i] << " ";
    }

    cout << "\nThe maximum value that can be accumulated is : "<< dp[n][maxWeight] << "\n";

}

int main()
{
    int n, maxWeight;
    cout << "Enter the number of items in knapsack : ";
    cin >> n;
    cout << "Enter the maxweight of the knapsack : ";
    cin >> maxWeight;

    vector<int> weight, profit;
    for(int i = 0; i < n; i++)
    {
        int w, p;
        cout << "Enter the weight and profit of the item ( "<<i+1 << " ) : ";
        cin >> w >> p;
        weight.push_back(w);
        profit.push_back(p);
    }
    
    cout << "\nThe input data is : \n\nItem No.\tWeight\t\tProfit\n";
    for(int i = 0; i < n; i++)
    {
        cout << i+1 << "\t\t" << weight[i] << "\t\t" << profit[i] << "\n";
    }
    cout << "\n";

    dynamic_knapsack(weight, profit, n, maxWeight);
    return 0;
}