#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

const int MAX_N = 100; // Adjust the maximum number of vertices as needed

bool isWalk(int degree[MAX_N])
{
    int oddDegreeVertices = 0;
    for (int i = 0; i < MAX_N; ++i)
    {
        if (degree[i] % 2 != 0)
        {
            oddDegreeVertices++;
        }
    }
    return oddDegreeVertices == 0 || oddDegreeVertices == 2;
}

bool isClosedWalk(int degree[MAX_N], int start, int end)
{
    return degree[start] % 2 == 0 && degree[end] % 2 == 0;
}

bool isCircuit(int degree[MAX_N], int start, int end)
{
    return isClosedWalk(degree, start, end) && degree[start] > 0 && degree[end] > 0;
}

bool isSimpleCircuit(int degree[MAX_N], int adj[MAX_N][MAX_N], int n)
{
    bool visited[MAX_N] = {false};
    int currentVertex = 0;
    int visitedVertices = 0;

    for (int i = 0; i < n; ++i)
    {
        visited[currentVertex] = true;
        visitedVertices++;

        if (degree[currentVertex] != 2)
        {
            return false;
        }

        bool found = false;
        for (int j = 0; j < n; ++j)
        {
            if (!visited[j] && adj[currentVertex][j] > 0)
            {
                currentVertex = j;
                found = true;
                break;
            }
        }

        if (!found || (found && visitedVertices == n && currentVertex != 0))
        {
            return isClosedWalk(degree, 0, 0); // Check for a closed walk from and to the starting vertex
        }
    }

    return false;
}

bool isPath(int degree[MAX_N], int start, int end)
{
    if (start == end || degree[start] == 0 || degree[end] == 0)
    {
        return false; // Start and end vertices must have non-zero degree, and they must be different
    }

    int tempDegree[MAX_N];
    for (int i = 0; i < MAX_N; ++i)
    {
        tempDegree[i] = degree[i];
    }
    tempDegree[start]--;
    tempDegree[end]--;
    return isWalk(tempDegree);
}

bool isSimplePath(int degree[MAX_N], int adj[MAX_N][MAX_N], int n, int start, int end)
{
    if (start == end || degree[start] == 0 || degree[end] == 0)
    {
        return false; // Start and end vertices must have non-zero degree, and they must be different
    }

    bool visited[MAX_N] = {false};
    int currentVertex = start;

    for (int i = 0; i < n; ++i)
    {
        visited[currentVertex] = true;
        bool found = false;
        for (int j = 0; j < n; ++j)
        {
            if (!visited[j] && adj[currentVertex][j] > 0)
            {
                currentVertex = j;
                found = true;
                break;
            }
        }
        if (!found)
        {
            return currentVertex == end && degree[end] == 1; // Check if the path ends at the desired vertex with degree 1
        }
    }
    return false;
}

int main()
{
    int n, m;
    int start = -1, end;
    cout << "Enter the number of vertices: ";
    cin >> n;
    cout << "Enter the number of edges: ";
    cin >> m;
    int adj[MAX_N][MAX_N] = {0};
    int degree[MAX_N] = {0};
    cout << "Enter the edges:" << endl;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        if (start == -1)
            start = u;
        adj[u][v]++;
        adj[v][u]++;
        end = v;
        degree[u]++;
        degree[v]++;
    }

    start = 0;
    end = n - 1;

    // Example usage:
    if (isWalk(degree))
    {
        cout << "The graph is a walk." << endl;
    }

    if (isClosedWalk(degree, start, end))
    {
        cout << "The graph is a closed walk." << endl;
    }

    if (isCircuit(degree, start, end))
    {
        cout << "The graph is a circuit." << endl;
    }

    if (isSimpleCircuit(degree, adj, n))
    {
        cout << "The graph is a simple circuit." << endl;
    }

    // Example path from vertex 0 to vertex n - 1
    if (isPath(degree, start, end))
    {
        cout << "There exists a path from vertex " << start << " to vertex " << end << "." << endl;
    }

    if (isSimplePath(degree, adj, n, start, end))
    {
        cout << "There exists a simple path from vertex " << start << " to vertex " << end << "." << endl;
    }

    return 0;
}