#include<stdio.h>
#include<stdlib.h>
int size;
int bucket_size;

struct node
{
    int data;
    struct node *next;
};
struct node* chain[50];
void init()
{
    int i;
    for(i = 0; i < size; i++)
        chain[i] = NULL;
}
//insertion
int insert(int value,int size,int bucket[],int overflow[],int bucket_size)
{
    struct node *newNode = malloc(sizeof(struct node));
    newNode->data = value;
    newNode->next = NULL;
//    printf("%d",newNode->data);
    //calculate hash key
     int key;
     key= value % size;
     if(bucket[key]!=5)
     {

    if(chain[key] == NULL)
    {
        chain[key] = newNode;

        bucket[key]=1;
        printf("\nbucket value for %d is %d\n",key,bucket[key]);
        return 1;
    }

    //collision
    else
    {
        //add the node at the end of chain[key].
        struct node *temp = chain[key];
        while(temp->next)
        {
            temp = temp->next;
        }

        temp->next = newNode;

        bucket[key]=bucket[key]+1;
        printf("\nbucket value for %d is %d\n",key,bucket[key]);
         return 1;
    }
     }
     else{
          int count=0;
          for (int z=0;z<bucket_size;z++)
          {
              if(overflow[z]==0)
              {
                  overflow[z]=value;
                  count++;
                  break;

              }

          }
          if (count==0)
          {
              printf("\n The hash table is full so not inserted");
              return 0;

          }
          else{
             return 1;
          }


     }



    return 0;
}
//search
int search(int value,int size,int bucket[],int overflow[])
{
    int key = value % size;
    struct node *temp = chain[key];
    while(temp)
    {
        if(temp->data == value)
            return 1;
        temp = temp->next;
    }
    for(int i=0;i<bucket_size;i++)
    {
        if (overflow[i]==value)
        {
            return 1;
        }
    }
    return 0;
}

int del(int value,int size,int bucket[],int overflow[])
{
    int key = value % size;
    struct node *temp = chain[key], *dealloc;
    if(temp != NULL)
    {
        if(temp->data == value)
        {
            dealloc = temp;
            temp = temp->next;
            free(dealloc);
            return 1;
        }
        else
        {
            while(temp->next)
            {
                if(temp->next->data == value)
                {
                    dealloc = temp->next;
                    temp->next = temp->next->next;
                    free(dealloc);
                    return 1;
                }
                temp = temp->next;
            }
        }
        for(int i=0;i<bucket_size;i++)
        {
            if(overflow[i]==value)
            {
              overflow[i]=-1;
              return 1;

            }

        }
    }

    return 0;
}





void print(int size,int overflow[])
{
    int i;

    for(i = 0; i < size; i++)
    {
        struct node *temp = chain[i];
        printf("chain[%d]-->",i);
        while(temp)
        {
            printf("%d -->",temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
    printf("\nThe overflow buffer values\n");
    for(i=0;i<bucket_size;i++)
    {
        printf("%d\t",overflow[i]);

    }
}

int main(int argc,char * argv[])
{
    int sub=0;
    int option=0;
    int num;
    int res;
    init();
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
    fscanf(fp,"%d",&bucket_size);
    printf("\n The size of the bucket is %d \n",bucket_size);


    int bucket[size];
    int overflow[bucket_size];

    for(int i=0;i<size;i++)
    {
        bucket[i]=0;

    }
    for(int i=0;i<bucket_size;i++)
    {
        overflow[i]=0;

    }
    printf("\n Empty hash table before inserting......\n");
    print(size,overflow);
    for(int i=0;i<size;i++)
    {
     if(!feof(fp))
     {
       fscanf(fp,"%d",&sub);
       insert(sub,size,bucket,overflow,bucket_size);
     }


    }
    fclose(fp);
    //insert(100,size);
    printf("\nHash table after inserting values.........\n");
    print(size,overflow);
    printf("\n Operations available:");
    printf("\n 1: Searching \n 2:Insertion \n 3:Deletion \n 4:Print the hash table \n 5:Exit");

    while(option!=5)
    {
        printf("\n Enter the option to be performed:");
        scanf("%d",&option);

        switch(option)
        {
        case 1:
              printf("\nEnter the no to be searched\n");
              scanf("%d",&num);
              res=search(num,size,bucket,overflow);
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
               res=insert(num,size,bucket,overflow,bucket_size);
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
              res=del(num,size,bucket,overflow);
              if(res)
              {
                  printf("\nThe number is deleted successfully");
              }
              else
                {
                 printf("\nThe number is not deleted");
              }
               break;

        case 4:
               print(size,overflow);
               break;
        case 5:
              exit(0);




        }
    }


    return 0;
}


//File is opened successfully
//
//The size of the hash table is 25
//
// The size of the bucket is 5
//
// Empty hash table before inserting......
//chain[0]-->NULL
//chain[1]-->NULL
//chain[2]-->NULL
//chain[3]-->NULL
//chain[4]-->NULL
//chain[5]-->NULL
//chain[6]-->NULL
//chain[7]-->NULL
//chain[8]-->NULL
//chain[9]-->NULL
//chain[10]-->NULL
//chain[11]-->NULL
//chain[12]-->NULL
//chain[13]-->NULL
//chain[14]-->NULL
//chain[15]-->NULL
//chain[16]-->NULL
//chain[17]-->NULL
//chain[18]-->NULL
//chain[19]-->NULL
//chain[20]-->NULL
//chain[21]-->NULL
//chain[22]-->NULL
//chain[23]-->NULL
//chain[24]-->NULL
//
//The overflow buffer values
//0       0       0       0       0
//bucket value for 12 is 1
//
//bucket value for 9 is 1
//
//bucket value for 22 is 1
//
//bucket value for 11 is 1
//
//bucket value for 7 is 1
//
//bucket value for 1 is 1
//
//bucket value for 18 is 1
//
//bucket value for 17 is 1
//
//bucket value for 1 is 2
//
//bucket value for 21 is 1
//
//bucket value for 3 is 1
//
//bucket value for 0 is 1
//
//bucket value for 9 is 2
//
//bucket value for 23 is 1
//
//bucket value for 11 is 2
//
//bucket value for 19 is 1
//
//bucket value for 20 is 1
//
//bucket value for 2 is 1
//
//bucket value for 11 is 3
//
//bucket value for 13 is 1
//
//bucket value for 9 is 3
//
//bucket value for 5 is 1
//
//bucket value for 8 is 1
//
//bucket value for 15 is 1
//
//bucket value for 7 is 2
//
//Hash table after inserting values.........
//chain[0]-->0 -->NULL
//chain[1]-->26 -->51 -->NULL
//chain[2]-->27 -->NULL
//chain[3]-->3 -->NULL
//chain[4]-->NULL
//chain[5]-->5 -->NULL
//chain[6]-->NULL
//chain[7]-->57 -->7 -->NULL
//chain[8]-->8 -->NULL
//chain[9]-->34 -->84 -->9 -->NULL
//chain[10]-->NULL
//chain[11]-->36 -->11 -->61 -->NULL
//chain[12]-->12 -->NULL
//chain[13]-->38 -->NULL
//chain[14]-->NULL
//chain[15]-->65 -->NULL
//chain[16]-->NULL
//chain[17]-->17 -->NULL
//chain[18]-->18 -->NULL
//chain[19]-->44 -->NULL
//chain[20]-->45 -->NULL
//chain[21]-->46 -->NULL
//chain[22]-->22 -->NULL
//chain[23]-->23 -->NULL
//chain[24]-->NULL
//
//The overflow buffer values
//0       0       0       0       0
// Operations available:
// 1: Searching
// 2:Insertion
// 3:Deletion
// 4:Print the hash table
// 5:Exit
// Enter the option to be performed:1
//
//Enter the no to be searched
//4
//The number is not present
// Enter the option to be performed:1
//
//Enter the no to be searched
//77
//The number is not present
// Enter the option to be performed:1
//
//Enter the no to be searched
//5
//The number is found
// Enter the option to be performed:2
//
//Enter the no to be inserted
//50
//
//bucket value for 0 is 2
//
//The number is inserted successfully
// Enter the option to be performed:2
//
//Enter the no to be inserted
//600
//
//bucket value for 0 is 3
//
//The number is inserted successfully
// Enter the option to be performed:2
//
//Enter the no to be inserted
//700
//
//bucket value for 0 is 4
//
//The number is inserted successfully
// Enter the option to be performed:2
//
//Enter the no to be inserted
//800
//
//bucket value for 0 is 5
//
//The number is inserted successfully
// Enter the option to be performed:2
//
//Enter the no to be inserted
//300
//
//The number is inserted successfully
// Enter the option to be performed:4
//chain[0]-->0 -->50 -->600 -->700 -->800 -->NULL
//chain[1]-->26 -->51 -->NULL
//chain[2]-->27 -->NULL
//chain[3]-->3 -->NULL
//chain[4]-->NULL
//chain[5]-->5 -->NULL
//chain[6]-->NULL
//chain[7]-->57 -->7 -->NULL
//chain[8]-->8 -->NULL
//chain[9]-->34 -->84 -->9 -->NULL
//chain[10]-->NULL
//chain[11]-->36 -->11 -->61 -->NULL
//chain[12]-->12 -->NULL
//chain[13]-->38 -->NULL
//chain[14]-->NULL
//chain[15]-->65 -->NULL
//chain[16]-->NULL
//chain[17]-->17 -->NULL
//chain[18]-->18 -->NULL
//chain[19]-->44 -->NULL
//chain[20]-->45 -->NULL
//chain[21]-->46 -->NULL
//chain[22]-->22 -->NULL
//chain[23]-->23 -->NULL
//chain[24]-->NULL
//
//The overflow buffer values
//300     0       0       0       0
// Enter the option to be performed:

