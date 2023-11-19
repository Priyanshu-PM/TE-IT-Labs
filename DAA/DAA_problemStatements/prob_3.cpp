// Write a program to implement Bellman-Ford Algorithm using
// Dynamic Programming and verify the time complexity

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int V;
    cout << "Enter the number of vertices : ";
    cin >> V;
    int n_edges;
    cout << "Enter the number of edges : ";
    cin >> n_edges;

    vector<vector<int>> edges(n_edges, vector<int>(3, 0));

    cout << "\nEnter the input in this format :\n";
    cout << "From |\tTo |\tWeight\n\n";
    for(int i = 0; i < n_edges; i++)
    {
        cout << "Enter the values for edge ( "<< i+1 << " ) : ";
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];   //  taking the input
    }

    //  uni
    int shortest[V];
    for(int i = 0; i < V; i++)
        shortest[i] = INT_MAX;

    shortest[0] = 0;

    //  finding the path
    vector<vector<int>> ar1;

    //  initializing the paths as 0
    for(int i = 0; i < V; i++)
    {
        vector<int> temp = {0};
        ar1.push_back(temp);
    }

    //  calculating shortest path from 0 to all vertices
    for(int i = 0; i < V - 1; i++)
    {
        for(int j = 0; j < n_edges; j++)
        {
            int u = edges[j][0] - 1;
            int v = edges[j][1] - 1;

            int weight = edges[j][2];

            if(shortest[u] != INT_MAX && shortest[u] + weight < shortest[v])
            {
                shortest[v] = shortest[u]+weight;

                // path addition
                vector<int> end = ar1[u];
                end.push_back(v);
                ar1[v] = end;

            }
        }
    }

    cout << "\nShortest paths and their distances respectively are : \n";

    for(int i = 0; i < V; i++)
    {
        cout << "Vertice:- "<<i+1 << " Distance:- "<<shortest[i]<<"\t\tPath : ";
        for(int j = 0; j < ar1[i].size(); j++)
            cout << ar1[i][j] << " ";
        cout << "\n";
    }


    return 0;
    
}