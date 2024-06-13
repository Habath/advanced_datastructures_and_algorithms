#include<stdio.h>
#include<stdlib.h>
int size;

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
int insert(int value,int size)
{
    //create a newnode with value
    struct node *newNode = malloc(sizeof(struct node));
    newNode->data = value;
    newNode->next = NULL;
//    printf("%d",newNode->data);
    //calculate hash key
     int key;
     key= value % size;
    //check if chain[key] is empty
    if(chain[key] == NULL)
    {
        chain[key] = newNode;
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
        return 1;
    }
    return 0;
}
//search
int search(int value,int size)
{
    int key = value % size;
    struct node *temp = chain[key];
    while(temp)
    {
        if(temp->data == value)
            return 1;
        temp = temp->next;
    }
    return 0;
}

int del(int value,int size)
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
    }

    return 0;
}





void print(int size)
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
}

int main(int argc,char * argv[])
{
    int size=0;
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
    printf("\n Empty hash table before inserting......\n");
    print(size);

    for(int i=0;i<size;i++)
    {
     if(!feof(fp))
     {
       fscanf(fp,"%d",&sub);
       insert(sub,size);
     }


    }
    fclose(fp);
    //insert(100,size);
    printf("\nHash table after inserting values.........\n");
    print(size);
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
              res=search(num,size);
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
               res=insert(num,size);
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
              res=del(num,size);
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
               print(size);
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
// Operations available:
// 1: Searching
// 2:Insertion
// 3:Deletion
// 4:Print the hash table
// 5:Exit
// Enter the option to be performed:1
//
//Enter the no to be searched
//6
//The number is not present
// Enter the option to be performed:1
//
//Enter the no to be searched
//8
//The number is found
// Enter the option to be performed:2
//
//Enter the no to be inserted
//6
//
//The number is inserted successfully
// Enter the option to be performed:2
//
//Enter the no to be inserted
//8
//
//The number is inserted successfully
// Enter the option to be performed:4
//chain[0]-->0 -->NULL
//chain[1]-->26 -->51 -->NULL
//chain[2]-->27 -->NULL
//chain[3]-->3 -->NULL
//chain[4]-->NULL
//chain[5]-->5 -->NULL
//chain[6]-->6 -->NULL
//chain[7]-->57 -->7 -->NULL
//chain[8]-->8 -->8 -->NULL
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
// Enter the option to be performed:3
//
//Enter the no to be deleted
//8
//
//The number is deleted successfully
// Enter the option to be performed:4
//chain[0]-->0 -->NULL
//chain[1]-->26 -->51 -->NULL
//chain[2]-->27 -->NULL
//chain[3]-->3 -->NULL
//chain[4]-->NULL
//chain[5]-->5 -->NULL
//chain[6]-->6 -->NULL
//chain[7]-->57 -->7 -->NULL
//chain[8]-->8 -->8 -->NULL
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
























