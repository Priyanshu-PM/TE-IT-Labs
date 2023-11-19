//  Travelling Salesman Problem

// Write a program to solve the travelling salesman problem and to
// print the path and the cost using LC Branch and Bound.
//  A B C D 
// A 0 4 2 1
// B 4 0 13 9
// C 2 13 0 8
// D 1 9 8 0


#include <bits/stdc++.h>
#define inf INT_MAX
using namespace std;

// printing the line
void line(int l)
{
    for(int i = 0; i < l; i++)
        cout << "_";
    cout << "\n";
}

// printing the cost matrix
void print_cost(vector<vector<int>>& cost, int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(cost[i][j] == inf)
                cout << "X\t";
            else
                cout << cost[i][j] << "\t";
        }
    }
    cout << "\n";
}

void fillInf(vector<vector<int>>& cost, vector<int>& trav, int n, int src, int dest)
{
    //  making destination to source to infinity
    cost[dest][src] = inf;

    //  making distance to all previously visited nodes to infinity
    //  so that, they don't get in calculation
    for(int t: trav)
        cost[dest][t] = inf;

    for(int i = 0; i < n; i++)
    {
        //  making the particular row and column to infinity
        //  so that, they don't get in calculation
        cost[i][dest] = inf;
        cost[src][i] = inf;
    }

}

int reduce(vector<vector<int>>& cost, int n)
{
    int r = 0;

    //  finding the minimum in row
    for(int i = 0; i < n; i++)
    {
        int row_min = cost[i][0];
        for(int j = 1; j < n; j++)
        {
            row_min = min(row_min, cost[i][j]);
        }

        if(row_min != inf)
        {
            r += row_min;

            for(int j = 0; j < n; j++)
            {
                if(cost[i][j] != inf)
                {
                    cost[i][j] -= row_min;
                }
            }
        }
    }

    //  finding the minimum in column
    for(int i = 0; i < n; i++)
    {
        int col_min = cost[i][0];

        for(int j = 0; j < n; j++)
            col_min = min(col_min, cost[i][j]);

        if(col_min != inf)
        {
            r += col_min;
            for(int j = 0; j < n; j++)
            {
                if(cost[i][j] != inf)
                {
                    cost[i][j] -= col_min;
                }
            }
        }
    }

    return r;
}

void TSP(vector<vector<int>>& source, int n, int start)
{

    line(50);
    cout << "\n\n\nTravelling Salesman Problem\nTotal locations = " << n << "\nStarting location = "<< start << "\n\n\n";
    line(50);
    int s = start;
    vector<int> trav;

    // first time reduction in cost
    int tcost = reduce(source, n);

    while(trav.size() != n)
    {
        int d = s;
        int min_cost = inf;
        vector<vector<int>> new_source = source;
        cout << "Current location = " << s << "\tCost = "<<tcost << "\n";

        for(int i = 0; i < n; i++)
        {
            //  skipping the current node and the previously traversed nodes
            if(i == s || count(trav.begin(), trav.end(), i))
                continue;

            vector<vector<int>> dest = source;
            fillInf(dest, trav, n, s, i);

            //  reduction in cost
            int r = reduce(dest, n);

            //  C (parentCost) + C(src, indexnode) + reduction cost
            int c = tcost + source[s][i] + r;

            print_cost(dest, n);

            cout << "\nLocation = " << i << "\tCost" << " = " << tcost << " + " << source[s][i] + " + " << r << " = " << c << endl;
            line(50);

            if(min_cost > c)
            {
                d = i;
                min_cost = c;
                new_source = dest;
            } 
        }

        if(s == d)
            d = start;

        cout << "Travelled to Location = " << d << "\tCost = " << tcost << endl;

        line(50);

        s = d;
        
        //  updating the parent cost
        if(min_cost != inf)
            tcost = min_cost; 

        source = new_source;

    }

    cout << "Solution : \nCost\t" << tcost << "\nPath\t";
    for(int t: trav)
        cout << t << " => ";

    cout << start << "\n";
}

int main()
{
    int n, start = 0;
    cout << "Enter the number of location => ";
    cin >> n;
    vector<vector<int>> source(n, vector<int>(n, inf));
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i != j)
                cin >> source[i][j];
        }
    }

    while(start >= 0 && start < n)
    {
        line(50);
        cout << "Enter starting location => ";
        cin >> start;
        TSP(source, n, start);
    }


    return 0;
}