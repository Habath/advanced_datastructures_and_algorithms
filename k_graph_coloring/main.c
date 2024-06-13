#include <stdbool.h>
#include <stdio.h>

// Number of vertices in the graph
int V=10;

void print(int color[]);

bool check(
	int v, bool graph[V][V],
	int color[], int c)
{
	for (int i = 0; i < V; i++)
		if (
			graph[v][i] && c == color[i])
			return false;
	return true;
}

/* A recursive utility function
to solve k coloring problem */
bool graphColoringUtil(
	bool graph[V][V], int m,
	int color[], int v)
{
	if (v == V)
		return true;
	for (int c = 1; c <= m; c++) {

		if (check(
				v, graph, color, c)) {
			color[v] = c;

			if (
				graphColoringUtil(
					graph, m, color, v + 1)
				== true)
				return true;

			color[v] = 0;
		}
	}


	return false;
}


bool graphColoring(
	bool graph[V][V], int m)
{

	int color[V];
	for (int i = 0; i < V; i++)
		color[i] = 0;

	if (
		graphColoringUtil(
			graph, m, color, 0)
		== false) {
		printf("\nSolution is not possible\n");
		return false;
	}

	print(color);
	return true;
}

void print(int color[])
{
	printf(
		"Solution possible:"
		" Following are the assigned colors \n");
	for (int i = 0; i < V; i++)
		printf(" %d ", color[i]);
	printf("\n");
}


int main()
{
    int k=0;
    int V=0;
   FILE *file = fopen("E:\\graphcolouring_input.txt", "r");//Kindly provide the correct location of the file.
   fscanf(file,"%d",&V);
   printf("The no of vertices is:%d\n",V);
	bool graph[V][V];
	 while (!feof(file))
    {
        for ( int i = 0; i < V; i++)
        {
            for ( int j = 0; j < V; j++)
            {
                fscanf(file,"%d",&graph[i][j]);

            }
        }
    }
    fclose(file);

    //Printing the graph
   for(int i=0;i< V;i++)
   {
     for(int j=0;j< V;j++)
     {
      printf("%d\t",graph[i][j]);
     }
     printf("\n");
   }
   int colArr[]={2,3,4,5,6};

	for (int i=0;i<5;i++)
    {
        printf("\nFor no of colours = %d",colArr[i]);
        printf("\n");
       graphColoring(graph,colArr[i]);
    }
  printf("\nNOTE: The algorithm stops as soon as the graph coloring is achieved , so it produces same solution for k=4,5, 6,etc ");
  printf("\n");


	return 0;
}
