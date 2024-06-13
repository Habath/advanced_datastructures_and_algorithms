#include<iostream>
#include<fstream>
#include<queue>
#include<math.h>
#include<bits/stdc++.h>

using namespace std;


struct Node
{
    int *point;
    int dim;
    Node *left, *right;
    float distance;
};
typedef Node* nodeptr;

class kdtree
{
    nodeptr root;
    int k;
    bool deleteflag;
    int node_count;

    nodeptr initNode(int arr[], int _dim)
    {
        nodeptr temp = new Node;
        temp->point = new int[k];

        for(int i=0; i<k; i++)
        {
            temp->point[i] = arr[i];
        }

        temp->dim = _dim;
        temp->left = temp->right = NULL;
        temp->distance = 0;
        return temp;
    }

    nodeptr insert_recursive(nodeptr root, int point[], int depth)
    {
        int dim = depth % k;

        if(root == NULL)
            return initNode(point, dim);

        if(point[dim] < (root->point[dim]))
            root->left = insert_recursive(root->left, point, depth + 1);

        else
            root->right = insert_recursive(root->right, point, depth + 1);

        return root;
    }

    bool equals(int pt1[], int pt2[])
    {
        for(int i=0; i<k; i++)
            if(pt1[i] != pt2[i])
                return false;

        return true;
    }

    bool search_recursive(nodeptr root, int point[], int depth)
    {
        if(root == NULL)
            return false;

        if(equals(root->point, point))
            return true;

        int dim = depth % k;

        if(point[dim] < (root->point[dim]))
            return search_recursive(root->left, point, depth + 1);

        else
            return search_recursive(root->right, point, depth + 1);
    }

    void copy_point(int p1[], int p2[])
    {
        for(int i=0; i<k; i++)
        {
            p1[i] = p2[i];
        }
    }

    nodeptr remove_recursive(nodeptr root, int point[], int depth)
    {
        if(root == NULL)
            return NULL;

        int dim = depth % k;

        if(equals(root->point, point))
        {
            if(root->right != NULL)
            {
                nodeptr min = findmin(root->right, dim);
                copy_point(root->point, min->point);
                root->right = remove_recursive(root->right, min->point, depth + 1);
            }

            else if(root->left != NULL)
            {
                nodeptr min = findmin(root->left, dim);
                copy_point(root->point, min->point);
                root->right = remove_recursive(root->left, min->point, depth + 1);
            }

            else
            {
                delete root;
                deleteflag = true;
                return NULL;
            }

            return root;
        }

        if(point[dim] < root->point[dim])
            root->left = remove_recursive(root->left, point, depth + 1);
        else
            root->right = remove_recursive(root->right, point, depth + 1);

        return root;
    }

    nodeptr minNode(nodeptr x, nodeptr y, nodeptr z, int d)
    {
        nodeptr res = x;

        if(y != NULL && y->point[d] < res->point[d])
            res = y;

        if(z != NULL && z->point[d] < res->point[d])
            res = z;

        return res;
    }

    nodeptr findmin_recursive(nodeptr root, int d, int depth)
    {
        if(root == NULL)
            return NULL;

        int dim = depth % k;

        if(dim == d)
        {
            if(root->left == NULL)
                return root;

            return findmin_recursive(root->left, d, depth + 1);
        }

        return minNode( root,
                        findmin_recursive(root->left, d, depth + 1),
                        findmin_recursive(root->right, d, depth + 1),
                        d );
    }

    nodeptr findmin(nodeptr root, int d)
    {
        return findmin_recursive(root, d, 0);
    }

    void k_nearest_neighbours(nodeptr node, vector<nodeptr> &closest_points, int point[], int kn)
    {
        if(node == NULL)
            return;

        float curr_dist = distance(node->point, point);
        sort(closest_points.begin(), closest_points.end(), compareDistance);

        if(closest_points[k-1]->distance > curr_dist || closest_points[k-1]->distance >= 10000)
        {
            closest_points[k-1]->distance = curr_dist;
            closest_points[k-1]->point = node->point;
        }

        if(node->point[node->dim] >= point[node->dim])
            k_nearest_neighbours(node->left, closest_points, point, kn);
        else
            k_nearest_neighbours(node->right, closest_points, point, kn);

        float range = abs(point[node->dim] - node->point[node->dim]);
        if(range > closest_points[k-1]->distance)
            return;
        if(node->point[node->dim] >= point[node->dim])
            k_nearest_neighbours(node->right, closest_points, point, kn);
        else
            k_nearest_neighbours(node->left, closest_points, point, k);

    }


    static bool compareDistance(nodeptr n1, nodeptr n2)
    {
        return (n1->distance < n2->distance);
    }

    float distance(int p1[], int p2[])
    {
        float dist = 0;
        for(int i=0; i<k; i++)
        {
            dist += pow((p1[i] - p2[i]), 2);
        }

        dist = sqrt(dist);
        return dist;
    }

    vector<nodeptr> knnprep(int kn)
    {
        int pt[k] = { 0 };
        nodeptr temp;
        vector<nodeptr> closest;

        for(int i=0; i<kn; i++)
        {
            temp = initNode(pt, 0);
            temp->distance = 10000;
            closest.push_back(temp);
        }

        return closest;
    }


    public:

    kdtree()
    {
        this->k = 1;
        root = NULL;
        deleteflag = false;
        node_count = 0;
    }

    kdtree(int k)
    {
        this->k = k;
        root = NULL;
        deleteflag = false;
        node_count = 0;
    }

    void setdim(int d)
    {
        this->k = d;
    }

    int getdim()
    {
        return this->k;
    }

    void insert(int point[])
    {
        this->root =  insert_recursive(this->root, point, 0);
        if(root != NULL)
            node_count += 1;
    }

    bool search(int point[])
    {
        return search_recursive(this->root, point, 0);
    }

    bool remove(int point[])
    {
        this->root = remove_recursive(this->root, point, 0);
        if(deleteflag)
        {
            deleteflag = false;
            node_count -= 1;
            return true;
        }

        return false;
    }

    void range_query_circle(int center[], int radius)
    {
        if(!this->root)
        {
            cout<<"Tree is Empty"<<endl;
            return;
        }

        vector<nodeptr> query_result;
        deque<nodeptr> q;
        q.push_back(this->root);

        while(true)
        {
            int count = q.size();
            if(count == 0)
                break;

            while(count > 0)
            {
                nodeptr t = q.front();
                int sum = 0;
                for(int i=0; i<k; i++)
                {
                    sum += pow((center[i] - t->point[i]), 2);
                }
                float dist = sqrt(sum);
                t->distance = dist;

                if(dist <= radius)
                    query_result.push_back(t);

                q.pop_front();

                if(t->left != NULL)
                    q.push_back(t->left);

                if(t->right != NULL)
                    q.push_back(t->right);

                count--;
            }
        }

        display_points(query_result);
    }


    float area(int p1[], int p2[], int p3[])
    {
        return abs((p1[0] * (p2[1] - p3[1]) + p2[0] * (p3[1] - p1[1]) +
                    p3[0] * (p1[1] - p2[1])) / 2.0);
    }

    bool withinBounds(int p1[], int p2[], int p3[], int p4[], int p5[])
    {
        float A = area(p1, p2, p3) + area(p1, p4, p3);
        float A1 = area(p5, p1, p2);
        float A2 = area(p5, p2, p3);
        float A3 = area(p5, p3, p4);
        float A4 = area(p5, p1, p4);

        return (A == A1 + A2 + A3 + A4);
    }


    void range_query_rect(int tl[], int tr[], int bl[], int br[])
    {
        if(!this->root)
        {
            cout<<"Tree Empty"<<endl;
            return;
        }

        if(k != 2)
        {
            cout<<"Range query implementation only for 2 dimensions."<<endl;
            return;
        }

        vector<nodeptr> query_result;
        deque<nodeptr> q;
        q.push_back(this->root);

        while(true)
        {
            int count = q.size();
            if(count == 0)
                break;

            while(count > 0)
            {
                nodeptr t = q.front();

                if(withinBounds(tl, tr, bl, br, t->point))
                    query_result.push_back(t);


                q.pop_front();

                if(t->left != NULL)
                    q.push_back(t->left);

                if(t->right != NULL)
                    q.push_back(t->right);

                count--;
            }
        }

        display_points(query_result, false);
    }

    void knn(int pt[], int k)
    {
        vector<nodeptr> closest_pts = knnprep(k);
        k_nearest_neighbours(this->root, closest_pts, pt, k);
        display_points(closest_pts);
    }

    void display_points(vector<nodeptr> closest_pts, bool show_distance = true)
    {
        for(auto &elem : closest_pts)
        {
            if(elem->distance == 10000)
                continue;

            cout<<endl;
            for(int i=0; i<k; i++)
            {
                cout<<elem->point[i];
                if(i != k-1)
                    cout<<", ";
            }

            if(show_distance)
                cout<<"\t"<<elem->distance;
        }
    }

    void buidltree(ifstream &fin)
    {
        while(!fin.eof())
        {
            int a[k];
            for(int i=0; i<k; i++)
            {
                fin>>a[i];
            }
            insert(a);
        }
    }

    void display()
    {
        if(!this->root)
        {
            cout<<"Tree Empty"<<endl;
            return;
        }

        deque<nodeptr> q;
        q.push_back(this->root);

        while(true)
        {
            int count = q.size();
            if(count == 0)
                break;

            while(count > 0)
            {
                nodeptr t = q.front();
                for(int i=0; i<k; i++)
                {
                    cout<<t->point[i];
                    if(i != k-1)
                        cout<<" ";
                }
                cout<<"\n";
                q.pop_front();

                if(t->left != NULL)
                    q.push_back(t->left);

                if(t->right != NULL)
                    q.push_back(t->right);

                count--;
            }

            cout<<endl;
        }
    }
};

int *getpoint(int k)
{
    int *pt = new int[k];
    for(int i=0; i<k; i++)
    {
        cin>>pt[i];
    }
    return pt;
}


void showpoint(int pt[], int k)
{
    for(int i=0; i<k; i++)
    {
        cout<<pt[i];
        if(i != k-1)
            cout<<", ";
    }
}


int main()
{
    int n, k, kn;
    int *pt, *pt1, *pt2, *pt3, *pt4;
    int radius, flag1=1;
    char c;
    bool FLAG_treeEmpty = true;
    ifstream fin;
    fin.open("Example");

    kdtree tree;


    fin>>k;
    pt = new int[k];
    tree.setdim(k);
    tree.buidltree(fin);
    FLAG_treeEmpty = false;

    do
    {
        	cout<<"\nWhat operation do you want to do ?\n\n";
		cout<<"1.Insert\n";
		cout<<"2.Delete\n";
		cout<<"3.Search\n";
		cout<<"4.Range query(rectangle)\n";
		cout<<"5.Range query(circle)\n";
		cout<<"6.k-neighbour\n";
		cout<<"7.Display\n";
		cout<<"8.Exit\n\n";
		cout<<"Enter the option :\n";
        	cin>>n;

        switch(n)
        {
            case 1:
                k = tree.getdim();
                cout<<endl<<"Enter the coordinates : \n";
                pt = getpoint(k);
                tree.insert(pt);
                break;


            case 2:
                if(FLAG_treeEmpty)
                {
                    cout<<endl<<"Tree is empty! \n";
                    break;
                }

                cout<<endl<<"Enter the coordinates : \n";
                k = tree.getdim();
                pt = getpoint(k);
                if(tree.remove(pt))
                    cout<<"\n";
                else
                    cout<<"Node not found\n";
                break;


            case 3:
                if(FLAG_treeEmpty)
                {
                    cout<<endl<<"Tree is empty\n";
                    break;
                }

                cout<<endl<<"Enter coordinates \n: \n";
                k = tree.getdim();
                pt = getpoint(k);
                if(tree.search(pt))
                {
                    cout<<"Node found\n";
                }
                else
                {
                    cout<<"Not found\n";
                }
                break;


            case 4:
                if(FLAG_treeEmpty)
                {
                    cout<<endl<<"Tree is empty\n";
                    break;
                }
                cout<<endl<<"Enter 4 corner coordinates of rectangle : \ntop left\n top right\n bottom right\n bottom left \n";
                k = tree.getdim();

                pt1 = getpoint(k);
                pt2 = getpoint(k);
                pt3 = getpoint(k);
                pt4 = getpoint(k);
                tree.range_query_rect(pt1, pt2, pt3, pt4);
                break;

            case 5:
                if(FLAG_treeEmpty)
                {
                    cout<<endl<<"Tree is empty\n";
                    break;
                }
                cout<<endl<<"Enter the coordinates of center of circle : \n";
                k = tree.getdim();
                pt = getpoint(k);
                cout<<endl<<"Enter radius of circle: \n";
                cin>>radius;
                tree.range_query_circle(pt, radius);
                break;

            case 6:
                if(FLAG_treeEmpty)
                {
                    cout<<endl<<"Tree is empty!\n";
                    break;
                }

                cout<<endl<<"Enter value for k \n ";
                cin>>kn;

                cout<<endl<<"Enter coordinates: \n ";
                k = tree.getdim();
                pt = getpoint(k);

                tree.knn(pt, kn);
                break;


            case 7:
                if(FLAG_treeEmpty)
                {
                    cout<<endl<<"Tree is empty";
                    break;
                }
                cout<<endl;
                tree.display();
                break;


            case 8:
                flag1=0;
		break;


            default:
                cout<<endl<<"Enter a valid option!";
        }

    } while (flag1);
    return 0;
}

