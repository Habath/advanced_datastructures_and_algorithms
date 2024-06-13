#include <stdio.h>
#include <stdlib.h>
typedef struct node {
int data;
struct node *left;
struct node *right;
struct node *parent;
}node;

typedef struct splay_tree {
struct node *root;
}splay_tree;

node* new_node(int data) {
node *n = malloc(sizeof(node));
n->data = data;
n->parent = NULL;
n->right = NULL;
n->left = NULL;

return n;
}

splay_tree* new_splay_tree() {
splay_tree *t = malloc(sizeof(splay_tree));
t->root = NULL;

return t;
}

node* maximum(splay_tree *t, node *x) {
while(x->right != NULL)
  x = x->right;
return x;
}
int maxi(splay_tree *t, node *x) {
while(x->right != NULL)
  x = x->right;
return x->data;
}

int minimum(splay_tree *t, node *x) {
while(x->left != NULL)
    x = x->left;
return x->data;
}

void left_rotate(splay_tree *t, node *x) {
node *y = x->right;
x->right = y->left;
if(y->left != NULL) {
  y->left->parent = x;
}
y->parent = x->parent;
if(x->parent == NULL) { //x is root
  t->root = y;
}
else if(x == x->parent->left) { //x is left child
  x->parent->left = y;
}
else { //x is right child
  x->parent->right = y;
}
y->left = x;
x->parent = y;
}

void right_rotate(splay_tree *t, node *x) {
node *y = x->left;
x->left = y->right;
if(y->right != NULL) {
  y->right->parent = x;
}
y->parent = x->parent;
if(x->parent == NULL) { //x is root
  t->root = y;
}
else if(x == x->parent->right) { //x is left child
  x->parent->right = y;
}
else { //x is right child
  x->parent->left = y;
}
y->right = x;
x->parent = y;
}

void splay(splay_tree *t, node *n) {
while(n->parent != NULL) { //node is not root
  if(n->parent == t->root) { //node is child of root, one rotation
    if(n == n->parent->left) {
      right_rotate(t, n->parent);
    }
    else {
      left_rotate(t, n->parent);
    }
  }
  else {
    node *p = n->parent;
    node *g = p->parent; //grandparent

    if(n->parent->left == n && p->parent->left == p) { //both are left children
      right_rotate(t, g);
      right_rotate(t, p);
    }
    else if(n->parent->right == n && p->parent->right == p) { //both are right children
      left_rotate(t, g);
      left_rotate(t, p);
    }
    else if(n->parent->right == n && p->parent->left == p) {
      left_rotate(t, p);
      right_rotate(t, g);
    }
    else if(n->parent->left == n && p->parent->right == p) {
      right_rotate(t, p);
      left_rotate(t, g);
    }
  }
}
}

int insert(splay_tree *t, node *n) {
node *y = NULL;
node *temp = t->root;
while(temp != NULL) {
  y = temp;
  if(n->data < temp->data){
    temp = temp->left;

  }
  else{
    temp = temp->right;

}
}
n->parent = y;

if(t->root == NULL) //newly added node is root
  t->root = n;
else if(n->data < y->data)
  y->left = n;
else
  y->right = n;

splay(t, n);
return 1;
}

node* search(splay_tree *t, node *n, int x) {
if(x == n->data) {
  splay(t, n);
  return n;
}
else if(x < n->data && n->left!=NULL)
  return search(t, n->left, x);
else if(x > n->data && n->right!=NULL)
  return search(t, n->right, x);
else
  return NULL;
}

void delete(splay_tree *t, node *n) {
splay(t, n);

splay_tree *left_subtree = new_splay_tree();
left_subtree->root = t->root->left;
if(left_subtree->root != NULL)
  left_subtree->root->parent = NULL;

splay_tree *right_subtree = new_splay_tree();
right_subtree->root = t->root->right;
if(right_subtree->root != NULL)
  right_subtree->root->parent = NULL;


free(n);

if(left_subtree->root != NULL) {
  node *m = maximum(left_subtree, left_subtree->root);
  splay(left_subtree, m);
  left_subtree->root->right = right_subtree->root;
  t->root = left_subtree->root;
}
else {
  t->root = right_subtree->root;
}


}

void display(splay_tree *t, node *n) {
if(n != NULL) {
        printf("%d-->", n->data);
  display(t, n->left);

  display(t, n->right);
}
}

int main(int argc,char * argv[])
{
    splay_tree *t = new_splay_tree();
    int size;
    int value=0;
    node *a;
    int option=0;
    int res=0;
    int num=0;
    int max=0;
    int min=0;
    FILE* fp =fopen(argv[1],"r");
    if(fp!=NULL)
    {
        printf("\nFile is opened successfully\n");
    }
    else{
        printf("\n The file is not found or does not exist\n");
    }
    fscanf(fp,"%d",&size);
    printf("\nThe size of the splay tree is %d \n",size);

    for(int i=1;i<=size;i++)
    {
       if(!feof(fp))
     {
       fscanf(fp,"%d",&value);
       a=new_node(value);
       insert(t,a);
     }
     else{
        printf("The End");
     }

    }
     fclose(fp);
     display(t, t->root);
    printf("\n Operations available:");
    printf("\n 1: Searching \n 2:Insertion \n 3:Deletion \n 4:Print the inorder traversal of splay tree \n 5:Find maximum \n 6: Find minimum \n 7:Exit\n");

    while(option!=7)
    {
        printf("\n Enter the option to be performed:");
        scanf("%d",&option);

        switch(option)
        {
        case 1:
              printf("\nEnter the no to be searched\n");
              scanf("%d",&num);
              res=search(t, t->root,num);
              if(res!=NULL)
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
               a=new_node(num);
               res=insert(t,a);
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
              a=search(t, t->root,num);
              delete(t,a);

               break;

        case 4:
               display(t, t->root);
               break;


        case 5:
               max=maxi(t,t->root);
               printf("The maximum element is %d",max);
               break;

        case 6:
              min=minimum(t,t->root);
              printf("The minimum element is %d",min);
              break;


        case 7:
              exit(0);




        }
    }



 return 0;
}
