#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

bool check = true;   // check for checking the bipartiteness of the graph
vector<int> vertice; // a vector array to store conflict causing vertices

void SettingValues(int i, int c, int vertices, int **adjMat, int *color) // checking the adjacent vertices of a vertice that are they having different values from the the vertice they are adjacent to
{
    color[i] = c;
    for (int v = 0; v < vertices; v++)
    {
        if (adjMat[i][v])
        {
            if (color[v] == c)
            {
                check = false;        // if any vertice found adjacent having same colour then set the value of check to false and push back that specific
                vertice.push_back(v); // conflict causing vertice in vector array for showing conflict causing vertices at the end
                return;
            }
            if (color[v] == 0)
            {
                SettingValues(v, -c, vertices, adjMat, color); // recursively calling this function to carry out depth first search in vertices and assigning values 1 or -1 according to their adjancency with other vertices
            }
        }
    }
}

int main()
{
    // sample inputs :
    // Bipartite Graph: 1 2,2 3,3 4, 4 1
    // Non-Bipartite Graph:  1 2,2 3,3 1

    string input;
    cout << "Enter pairs of vertices separated by a comma (\",\"): ";
    getline(cin, input); // taking the edges in the form of a single string seperated with commas
    int vertices = 0;
    stringstream ss(input);
    string pair;
    while (getline(ss, pair, ','))
    { // taking a substring on the basis of encountering a comma from larger string provided by the user
        stringstream ss_pair(pair);
        int x, y;
        ss_pair >> x >> y;                   // seperating the x and y values(or vertices) for further use
        vertices = max(vertices, max(x, y)); // as the vertices from which we need to form a graph, are sequence wise so taking the vertices which has a max count
    }
    int **adjMat = new int *[vertices]; // 2 D pointer array of adjancency matrix
    for (int i = 0; i < vertices; i++)
    {
        adjMat[i] = new int[vertices]; // assigning each element of row of adjancency matrix a new pointer array
    }
    int *color = new int[vertices]; // 1 D pointer array for setting the values of vertices either 1 or -1 to check the bipartiteness
    for (int i = 0; i < vertices; i++)
    {
        color[i] = 0; // initially setting values to zero
        for (int j = 0; j < vertices; j++)
        {
            adjMat[i][j] = 0; // initially setting values to zero
        }
    }
    int edges = 0;
    stringstream ss2(input);
    while (getline(ss2, pair, ','))
    {
        stringstream ss_pair(pair);
        int x, y;
        ss_pair >> x >> y;
        adjMat[x - 1][y - 1] = 1; // as the graph is undirected then setting same values for x,y and y,x
        adjMat[x - 1][y - 1] = 1;
        adjMat[y - 1][x - 1] = 1;
        adjMat[y - 1][x - 1] = 1;
        edges++;
    }
    for (int i = 0; i < vertices; i++)
    {
        if (color[i] == 0)
        {
            SettingValues(i, 1, vertices, adjMat, color); // giving the colours or values to the vertices
        }
    }
    if (check)
    {
        cout << "The graph is bipartite with adjencency matrix: " << endl; // if graph is bipartite then printing the adjencency matrix
        for (int i = 0; i < vertices; i++)
        {
            cout << "| ";
            for (int j = 0; j < vertices; j++)
            {
                cout << adjMat[i][j] << " ";
            }
            cout << "|\n";
        }
    }
    else
    {
        cout << "The vertices causing conflict are: "; // Mentioning the vertices causing conflict if check is return false
        for (int i = 0; i < vertice.size(); i++)
        {
            cout << vertice[i] + 1 << " ";
        }
        cout << endl;
        cout << "The graph is not bipartite.Its adjency matrix is : " << endl; // if graph is not bipartite then printing the adjencency matrix
        for (int i = 0; i < vertices; i++)
        {
            cout << "| ";
            for (int j = 0; j < vertices; j++)
            {
                cout << adjMat[i][j] << " ";
            }
            cout << "|\n";
        }
    }
    system("pause>0");
    return 0;
}