// Write a program to implement Bellman-Ford Algorithm using
// Dynamic Programming and verify the time complexity

#include<iostream>
#include<vector>
#include<climits>
//3 2 6 5 3 1 0 1 5 1 5 -3 1 2 -2 3 4 -2 2 4 3
using namespace std;

// void copyVec(vector<int> &v1, const vector<int> &v2){
//     for(int i = 0; i < v2.size(); i++){
//         v1.push_back(v2[i]);
//     }
//     for(int i = 0; i < v2.size();i++){
//         cout << v1[i] << " ";
//     }
//     cout << endl;
// }

void bell(int noOfEdges, int noOfVertices, vector<vector<int>> &graph, vector<int> &dist){

    vector<vector<int>> path(noOfVertices, vector<int>(1, 0));

    for(int i = 0; i < noOfVertices-1; i++){
        for(int j = 0; j < noOfEdges; j++){
            int u = graph[j][0];
            int v = graph[j][1];
            int weight = graph[j][2];
            if(dist[u] != INT_MAX && dist[u] + weight < dist[v]){
                vector<int> temp = path[u];
                // copyVec(temp, path[u]);
                temp.push_back(v);
                dist[v] = dist[u] + weight;
                // copyVec(path[v], temp);
                path[v] = temp;
            }
        }
    }

    for(auto it : path){
        for(auto i : it)
            cout << i << ' ';
        cout << endl;
    }
}



int main(){
    int noOfVertices;
    cout << "Enter number of vertices > ";
    cin >> noOfVertices;

    int noOfEdges;
    cout << "Enter number of Edges > ";
    cin >> noOfEdges;

    vector<vector<int>> graph(noOfEdges, vector<int>(3, 0));
    cout << "Enter the edges like source destination weight : " << endl;
    for(int i = 0; i < noOfEdges; i++){
        // cout << "Edge " << i << " > ";
        cin >> graph[i][0] >> graph[i][1] >> graph[i][2];
    }

    int source;
    cout << "Enter the source node > ";
    cin >> source;    

    vector<int> dist(noOfVertices, INT_MAX);
    dist[source] = 0;

    bell(noOfEdges, noOfVertices, graph, dist);

    cout << "Minimum Distance form the source vertex " << source << " is :\n";
    for(int i = 0; i < noOfVertices; i++){
        cout << "Vertex " << i << ' ' << dist[i] << endl;
    }


    return 0;
}