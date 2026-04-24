#include <iostream>
using namespace std;

#define MAX 10
#define INF 9999

int main()
{
    int n; // number of offices (cities)
    int cost[MAX][MAX]; // adjacency matrix
    bool visited[MAX] = {false};

    cout << "Enter number of offices (cities): ";
    cin >> n;

    cout << "Enter cost adjacency matrix:\n";

    // Input matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> cost[i][j];

            // If no connection, mark as INF
            if (cost[i][j] == 0)
                cost[i][j] = INF;
        }
    }

    int edges = 0; //Counts how many connections we added    For n cities → MST has (n - 1) edges
    int mincost = 0;  //Stores total cost

    visited[0] = true; // Start from city 0

    cout << "\nEdges selected:\n";

    while (edges < n - 1)
    {
            //Find smallest connection from visited to unvisited city
        int min = INF;
        int u = -1, v = -1;


        //What is the cheapest edge that connects
        // a visited city to an unvisited city?”
        for (int i = 0; i < n; i++)  //Let me check every city one by one”
        {
            if (visited[i]) //Only consider cities that are already connected”
            //We are building a tree step by step
            {
                for (int j = 0; j < n; j++)
                //For each valid city i, check all other cities j
                // Think:
                // 👉 “From city i, where can I go?”
                {
                        //City j should NOT be visited and Is this edge cheaper than what I found before?”
                    if (!visited[j] && cost[i][j] < min)
                    {
                        min = cost[i][j];
                        u = i; //Start city
                        v = j; //End city
                    }
                }
            }
        }

        if (u != -1 && v != -1)
        {
            cout << "City " << u << " -> City " << v << "  Cost = " << min << endl;

            mincost += min;
            visited[v] = true;
            edges++;
        }
    }

    cout << "\nMinimum total cost = " << mincost << endl;

    return 0;
}