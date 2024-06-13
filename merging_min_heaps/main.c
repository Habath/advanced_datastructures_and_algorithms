#include <stdio.h>
#include <stdlib.h>
int index=0;
int heap[100];

int getParentIndex(int index)
{
    return index/2;
}
int getLeftChildIndex(int index)
{
    return index*2;

}
int getRightChildIndex(int index)
{
    return index*2+1;

}
//satisfying heap property
void upheapify(int index)
{
    if(index<=1)
        return 1;
    int parentIndex = getParentIndex(index);
    if(heap[index]<heap[parentIndex])
    {
        int temp=heap[index];
        heap[index]=heap[parentIndex];
        heap[parentIndex]=temp;
        upheapify(parentIndex);
    }

}

//inserting into heap
int insert(int value)
{
    index++;
    heap[index]=value;
    upheapify(index);
    return 1;
}

//printing heap
void display(int heap[],int size){

for(int i=1;i<=size;i++)
{
    printf("%d\t ",heap[i]);


}
printf("\n");

}

int main(int argc,char * argv[])
{
    int size1=0;
    int size2=0;
    int value=0;
    //Getting Heap 1
    FILE* fp1 =fopen(argv[1],"r");
    if(fp1!=NULL)
    {
        printf("\nFile is opened successfully\n");
    }
    else{

        printf("\n The file is not found or does not exist\n");
    }
    fscanf(fp1,"%d",&size1);
    printf("\nThe size of the first min heap is %d \n",size1);
    int heap1[size1];
  for(int i=1;i<=size1;i++)
    {
       if(!feof(fp1))
     {

         fscanf(fp1,"%d",&value);
         heap1[i]=value;


     }
    }
 fclose(fp1);

 printf("\n The first heap is :\n");
 display(heap1,size1);
//Getting Heap 2
FILE* fp2 =fopen(argv[2],"r");
if(fp2!=NULL)
    {
        printf("\nFile is opened successfully\n");
    }
    else{

        printf("\n The file is not found or does not exist\n");
    }
    fscanf(fp2,"%d",&size2);
    int heap2[size2];
    printf("\nThe size of the second min heap is %d \n",size2);
    for(int i=1;i<=size2;i++)
    {
       if(!feof(fp2))
     {
       for(int i=1;i<=size2;i++)
       {
         fscanf(fp2,"%d",&value);
         heap2[i]=value;
       }

     }

    }
 fclose(fp2);
printf("\n The second heap is:\n");
display(heap2,size2);
//Merging two heaps
int size3=size1+size2;
int merged_heap[size3];
for (int i=1;i<=size1;i++)
     merged_heap[i]=heap1[i];
for(int i=1;i<=size2;i++)
    merged_heap[size1+i]=heap2[i];

for(int i=1;i<=size3;i++)
{
    insert(merged_heap[i]);

}
printf("The merged heap is :");
display(heap,size3);




    return 0;
}
