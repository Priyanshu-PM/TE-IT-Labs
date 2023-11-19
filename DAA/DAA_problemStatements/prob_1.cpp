// Write a program to implement Fractional knapsack using Greedy algorithm 
// and also find the maximum profit
// Given items I= (I1,I2,I3,I4,I5), Weight w=(5,10,20,30,40) and Profit 
// p=(30,20,100,90,160). Let us consider that the capacity of the knapsack W = 60. Find 
// the maximum profit

#include <bits/stdc++.h>
using namespace std;

void greedyKnapsack(vector<int>& weight, vector<int>& profit, int n, int maxWeight)
{

    int maxProfit = 0;

    vector<pair<float, pair<int, int>>> items;
    for(int i = 0; i < n; i++)
    {
        float ratio = (float)profit[i]/ (float)weight[i];
        items.push_back({ratio, {weight[i], profit[i]}});
    }

    sort(items.rbegin(), items.rend());
    for(int i = 0; i < n; i++)
    {
        int weight = items[i].second.first;
        if(weight <= maxWeight)
        {
            cout << "The item taken is : weight = " << weight << " profit = "<< items[i].second.second << "\n";
            maxProfit += items[i].second.second;
            maxWeight -= weight;
        }
        else
            break;
    }

    cout << "The maximum profit that can be made is : " << maxProfit << "\n\n";

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
    
    cout << "\nThe input data is : \n\nWeight\t\tProfit\n";
    for(int i = 0; i < n; i++)
    {
        cout << weight[i] << "\t\t" << profit[i] << "\n";
    }
    cout << "\n";

    greedyKnapsack(weight, profit, n, maxWeight);

    return 0;
}