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

    int edges = 0;
    int mincost = 0;

    visited[0] = true; // Start from city 0

    cout << "\nEdges selected:\n";

    while (edges < n - 1)
    {
        int min = INF;
        int u = -1, v = -1;

        for (int i = 0; i < n; i++)
        {
            if (visited[i])
            {
                for (int j = 0; j < n; j++)
                {
                    if (!visited[j] && cost[i][j] < min)
                    {
                        min = cost[i][j];
                        u = i;
                        v = j;
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