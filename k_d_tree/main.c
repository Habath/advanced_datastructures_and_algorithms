#include <cstdio>//.....................................................printf()
#include "y_kd_tree.h"//.................................................yKDTree
inline void PrintNode(//<=======================PRINTS THE COORDINATES OF A NODE
 yKDTree::NODE<int>*N){//<---------------------------------------------A NODE
 N?printf("(%d,%d) ",N->r[0],N->r[1]):printf("(X,X) ");
}//~~~~~~YAGENAUT@GMAIL.COM~~~~~~~~~~~~~~~~~~~~~~~~~LAST~UPDATED~15JUL2014~~~~~~
int main(){//<=====================A SIMPLE EXAMPLE FOR THE NewKDTree() FUNCTION
 int*A[5],B[5][3]={4,1,0 , 4,3,1 , 6,2,2 , 2,4,3 , 8,4,4};
 printf("TABULATED DATA:\n");
 for(int i=0;i<5;++i)printf("%13d,%d,%d\n",B[i][0],B[i][1],B[i][2]);
 printf("\n\nKD TREE:\n");
 for(int i=0;i<5;++i)A[i]=B[i];
 yKDTree::NODE<int>*N=yKDTree::NewTree(A,A+5,2);
 printf(" "),PrintNode(N);//.........................root node (k=0)
 printf("\n / \\\n ");
 PrintNode(N->a),printf(" ");PrintNode(N->b);//....2nd-level nodes (k=1)
 printf("\n / \\ / \\\n");
 PrintNode(N->a->a),PrintNode(N->a->b),PrintNode(N->b->a),PrintNode(N->b->b);
 printf("\n\n"),yKDTree::DeleteTree(N);
}
