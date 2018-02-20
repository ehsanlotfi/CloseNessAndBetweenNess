#include<stdio.h>
#include <omp.h>

#define V 4
#define INF 99999

void printSolution(int dist[][V],int betweenness[V]);
void getCloseNess(int dist[][V]);

void floydWarshall (int graph[][V])
{
    /*  output matrix */
    int dist[V][V], i, j, k,betweenness[V];

   #pragma omp for
   for (i = 0; i < V; i++){
       betweenness[i] = 0;
   }


    /* shortest distances are base shortest paths  */
    #pragma omp for
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = graph[i][j];
 
    /* Add all vertices one by one to the set of intermediate vertices.*/
    #pragma omp for
    for (k = 0; k < V; k++)
    {
        // Pick all vertices as source one by one
        for (i = 0; i < V; i++)
        {
            // Pick all vertices as destination for the
            for (j = 0; j < V; j++)
            {
                // If vertex k is on the shortest path from
                // i to j, then update the value of dist[i][j]
                if (dist[i][k] + dist[k][j] < dist[i][j]){
                     dist[i][j] = dist[i][k] + dist[k][j];
                       ++betweenness[k];
                }
            }
        }
    }
 
    // Print the shortest distance matrix
     printSolution(dist,betweenness);
      getCloseNess(dist);
}
 

/*// Print function the shortest distance matrix */
void printSolution(int dist[][V],int betweenness[V])
{
    printf("\n\n");
    printf ("output matrix: \n");
    #pragma omp for
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf ("%7d", dist[i][j]);
        }
        printf("\n");
    }
     printf("\n");
    int maxbetweenness[2];
    maxbetweenness[1] = -1;

    #pragma omp for
    for (int i = 0; i < V; i++){
        if(betweenness[i] > maxbetweenness[1]){
             maxbetweenness[0] = i;
             maxbetweenness[1] = betweenness[i];
        }
       }
      printf ("BetweenNess Node => %d  \n", maxbetweenness[0] );

}
 

 void getCloseNess(int dist[][V]){

     int closeness[V];

    #pragma omp for
     for (int i = 0; i < V; i++){
            closeness[i] = 0;
      }

    #pragma omp for
     for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++){
             if(dist[i][j] != INF)
                closeness[i] += dist[i][j];
             else {
                  closeness[i] = INF;
                    break;
             }
        }
        int minCloseNess[2];
        minCloseNess[1] = INF;

        #pragma omp for
        for (int i = 0; i < V; i++){
            if( closeness[i] < minCloseNess[1]){
                minCloseNess[1] = closeness[i];
                minCloseNess[0] = i;
            }
        }
           printf ("CloseNess Node => %d  \n", minCloseNess[0] );
 }

int main()
{
    int graph[V][V] = { {0,   5,  INF, 10},
                        {2, 0,   3, 1},
                        {INF, INF, 0,   1},
                        {INF, INF, INF, INF}
                      };

    floydWarshall(graph);
    printf("\n");
    return 0;
}