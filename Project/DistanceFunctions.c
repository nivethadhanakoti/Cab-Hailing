// Maximum number of vertices
#define V 10

//Structure for storing the 30 places with their indices
/*typedef struct {
    char name[100];
    int index;
} Node;*/



// Function to find the vertex with the minimum distance value
int minDistance(int dist[], bool sptSet[])
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
    {
        if (sptSet[v] == false && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

// Function to print the minimum distance values
/*void printSolution(int dist[], char* pointNames[])
{
    printf("Vertex \t\t Minimum Distance\n");
    for (int i = 0; i < V; i++)
        printf("%s \t\t %d\n", pointNames[i], dist[i]);
}*/

// Function that implements Dijkstra's algorithm
void dijkstra(int graph[V][V], int src, int dest, char* pointNames[], int dist[])
{
    bool sptSet[V];

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++)
    {
        // Pick the minimum distance vertex from the set of vertices not yet processed.
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex
        for (int v = 0; v < V; v++)
        {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
        }
    }
}
