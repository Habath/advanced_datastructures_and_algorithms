#include <stdio.h>
#include <stdlib.h>
int heap [100];
int index=0;

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






void downheap(int ind)
{
    if(ind*2>index) return ;
    int left = getLeftChildIndex(ind);
    int right = getRightChildIndex(ind);
    int minimum=ind;
    if(left<=index && heap[left]< heap[minimum])
    {
        minimum=left;
    }
    if(right<=index && heap[right]< heap[minimum])
    {
        minimum=right;
    }
    if(minimum==ind)return;
    int temp=heap[ind];
    heap[ind]=heap[minimum];
    heap[minimum]=temp;

    downheap(minimum);
}
//delete
void del(int value)
{
  int ind = search(value);
  printf("\n search result is %d ",ind);
  if(ind==0)
  {
      printf("The value is not present");


  }
  else if (ind==index)
  {
      heap[ind]=-1;
      index = index-1;
      printf("\n The value is deleted successfully");

  }
  else{
      int temp=heap[ind];
      heap[ind]=heap[index];
      heap[index]=-1;
      index=index-1;
      printf("\n The value is deleted successfully");
      downheap(ind);

  }



  }


//searching
int search(int value)
{
    for (int i=1;i<=index;i++)
    {
        if(heap[i]==value)
        {
            return i;

        }

    }
    return 0;
}

//printing heap
void display(){

for(int i=1;i<=index;i++)
{
    printf("%d\t ",heap[i]);


}
printf("\n");

}

//inserting into heap
int insert(int value)
{
    index++;
    heap[index]=value;
    upheapify(index);
    return 1;
}

void heapify(int arr[], int size, int i)
{
int largest = i;
int left = 2*i + 1;
int right = 2*i + 2;

if (left < size && arr[left] >arr[largest])
largest = left;

if (right < size && arr[right] > arr[largest])
largest = right;

if (largest != i)
{
    int temp=0;
    temp = arr[i];
    arr[i]= arr[largest];
    arr[largest] = temp;
heapify(arr, size, largest);
}
}





void heapSort(int arr[], int size)
{
int i;
for (i = size / 2 - 1; i >= 0; i--)
heapify(arr, size, i);
for (i=size-1; i>=0; i--)
{
    int temp=0;
    temp = arr[0];
    arr[0]= arr[i];
    arr[i] = temp;
heapify(arr, i, 0);
}


printf("\nThe sorted heap is:\n");
display();
}

int main(int argc,char * argv[])
{
    int value=0;
    int size=0;
    int option=0;
    int num;
    int res=0;
    FILE* fp =fopen(argv[1],"r");
    if(fp!=NULL)
    {
        printf("\nFile is opened successfully\n");
    }
    else{
        printf("\n The file is not found or does not exist\n");
    }
    fscanf(fp,"%d",&size);
    printf("\nThe size of the hash table is %d \n",size);

    for(int i=0;i<size;i++)
    {
       if(!feof(fp))
     {
       fscanf(fp,"%d",&value);
       insert(value);
     }

    }
     fclose(fp);
    display();
    printf("\n Operations available:");
    printf("\n 1: Searching \n 2:Insertion \n 3:Deletion \n 4:Print the heap \n 5:Heap Sort \n 6:Exit\n");

    while(option!=6)
    {
        printf("\n Enter the option to be performed:");
        scanf("%d",&option);

        switch(option)
        {
        case 1:
              printf("\nEnter the no to be searched\n");
              scanf("%d",&num);
              res=search(num);
              if(res)
              {
                  printf("The number is found");
              }
              else{
                printf("The number is not present");
              }
              break;


        case 2:
               printf("\nEnter the no to be inserted\n");
               scanf("%d",&num);
               res=insert(num);
                if(res)
              {
                  printf("\nThe number is inserted successfully");
              }
              else
                {
                 printf("\nThe number is not inserted");
              }
               break;

        case 3:
              printf("\nEnter the no to be deleted\n");
              scanf("%d",&num);
             del(num);
//              if(res)
//              {
//                  printf("\nThe number is deleted successfully");
//              }
//              else
//                {
//                 printf("\nThe number is not deleted");
//              }
               break;

        case 4:
               display();
               break;


        case 5:
              heapSort(heap,index);
              break;

        case 6:
              exit(0);




        }
    }


    return 0;
}


//File is opened successfully
//
//The size of the hash table is 25
//0        5       3       27      8       7       11      36      34      17      9       18      84      23      22
//         44      45      51      61      57      38      46      12      65      26
//
// Operations available:
// 1: Searching
// 2:Insertion
// 3:Deletion
// 4:Print the heap
// 5:Heap Sort
// 6:Exit
//
// Enter the option to be performed:1
//
//Enter the no to be searched
//55
//The number is not present
// Enter the option to be performed:1
//
//Enter the no to be searched
//3
//The number is found
// Enter the option to be performed:2
//
//Enter the no to be inserted
//60
//
//The number is inserted successfully
// Enter the option to be performed:4
//0        5       3       27      8       7       11      36      34      17      9       18      60      23      22
//         44      45      51      61      57      38      46      12      65      26      84
//
// Enter the option to be performed:2
//
//Enter the no to be inserted
//2
//
//The number is inserted successfully
// Enter the option to be performed:4
//0        5       2       27      8       3       11      36      34      17      9       18      7       23      22
//         44      45      51      61      57      38      46      12      65      26      84      60
//
// Enter the option to be performed:3
//
//Enter the no to be deleted
//5
//
// search result is 2
// The value is deleted successfully
// Enter the option to be performed:3
//
//Enter the no to be deleted
//11
//
// search result is 7
// The value is deleted successfully
// Enter the option to be performed:4
//0        8       2       27      9       3       22      36      34      17      12      18      7       23      84
//         44      45      51      61      57      38      46      60      65      26
//
// Enter the option to be performed:5
//
//The sorted heap is:
//0        2       3       7       8       9       12      17      18      22      23      26      27      34      36
//         38      44      45      46      51      57      60      61      65      84
//
// Enter the option to be performed:
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
























































































































































































































