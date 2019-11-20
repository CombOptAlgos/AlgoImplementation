// an weighted undirected graph
#include<iostream>
#include<utility>
#include<set>

using namespace std;

// Define the number of runs for the test data
// generated
#define RUN 1

// Define the maximum number of vertices of the graph
#define MAX_VERTICES 5

// Define the maximum number of edges
#define MAX_EDGES 10

// Define the maximum weight of edges
#define MAXWEIGHT 5

int main()
{
    set<pair<int, int>> container;
    set<pair<int, int>>::iterator it;

    // Uncomment the below line to store
    // the test data in a file
    // freopen("Test_Cases_Undirected_Weighted_Graph.in",
    //          "w", stdout);

    //For random values every time
    srand(time(NULL));

    int NUM;    // Number of Vertices
    int NUMEDGE; // Number of Edges

    for (int i=1; i<=RUN; i++)
    {
        NUM = 1 + rand() % MAX_VERTICES;

        // Define the maximum number of edges of the graph
        // Since the most dense graph can have N*(N-1)/2 edges
        // where N =  nnumber of vertices in the graph
        NUMEDGE = 1 + rand() % MAX_EDGES;
        
        // Create spannning tree

        

    }

    // Uncomment the below line to store
    // the test data in a file
    // fclose(stdout);
    return(0);
}
