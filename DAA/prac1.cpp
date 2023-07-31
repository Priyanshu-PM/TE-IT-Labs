// knapsack problem with fractional component

#include <bits/stdc++.h>
#include <iostream>
using namespace std;

// creating the structure for storing the profit and weight of the objects
struct Object {

    int profit, weight;

    Object(int profit, int weight)
    {
        this->profit = profit;
        this->weight = weight;
    }
};


// comparator function on the basis of which the sorting is performed
static bool compare(struct Object obj1, struct Object obj2)
{

    // comparing the sequential object
    double r1 = (double)obj1.profit / (double)obj1.weight;
    double r2 = (double)obj2.profit / (double)obj2.weight;

    return r1 > r2;
}


// knapsack solver
double knapSackSolver(int w, struct Object arr[], int n)
{
    double finalProfit = 0.0;   //  final profit

    sort(arr, arr+n, compare);  //  sorting the objects on the basis of profit/weight ratio

    for(int i = 0; i < n; i++)
    {
        // if space is available then take the whole item
        if(arr[i].weight <= w)
        {
            cout << "The item chosen is : Profit = "<<arr[i].profit << " | weight = "<<arr[i].weight<<endl;
            w -= arr[i].weight;
            finalProfit += arr[i].profit;
        }
        // if the bag is full, then don't add anything
        else if(w == 0)
        {
            cout << "The sack is now full and cannot contain any more items !!"<<endl;
        }
        // if space is limited, then take the fractional part of the item along with the fractional profit
        else
        {
            cout << "The sack is almost full "<<endl;
            cout << "The fractional part taken is : weight = "<<(double)w/arr[i].weight<< " | profit is = "<< arr[i].weight * (double)w/arr[i].profit<<endl;
            finalProfit += arr[i].weight * (double)w/arr[i].profit;
            break;
        }
    }

    return finalProfit; //  returning the final profit
}

int main()  //  driver code
{

    int w = 10; //  declaring the sack
    Object arr[] = {{5, 1}, {4, 3}, {10, 3}, {5, 1}, {6, 2}, {15, 5}};
    int n = sizeof(arr)/sizeof(Object);
    cout <<endl;
    double output = knapSackSolver(w, arr, n);
    cout << "The maximum profit that can be made is : "<<output<<endl;
    return 0;
}