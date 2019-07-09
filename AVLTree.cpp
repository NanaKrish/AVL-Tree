#include<iostream>
#include<iomanip>
#include<stdlib.h>
using namespace std;
 
struct Node
{
    int key;
    Node *left;
    Node *right;
    int height;
};
 
int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
 
int max(int a, int b)
{
    return (a > b)? a : b;
}

Node* newNode(int key)
{
    Node* node = new Node;
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return(node);
}

Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
    return x;
}
 
Node *leftRotate(struct Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
    return y;
}

int getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
 
Node* insert(Node* node, int key)
{
    if (node == NULL)
        return(newNode(key));
    if (key < node->key)
        node->left  = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else return node;
 
    node->height = 1 + max(height(node->left), height(node->right));
 
    int balance = getBalance(node);
    // LL Rotation
    if (balance > 1 && key < node->left->key) return rightRotate(node);
    // RR Rotation
    if (balance < -1 && key > node->right->key) return leftRotate(node);
    // LR Rotation
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // RL Rotation
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

Node * minValueNode(Node* node)
{
    Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, int key)
{
    if (root == NULL)
        return root;
    if ( key < root->key )
        root->left = deleteNode(root->left, key);
    else if( key > root->key )
        root->right = deleteNode(root->right, key);
    else
    {
        if((root->left == NULL) || (root->right == NULL))
        {
            Node *temp = root->left ? root->left : root->right;
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
             *root = *temp;
            delete temp;
        }
        else
        {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }
 
    if (root == NULL)
      return root;
    root->height = 1 + max(height(root->left),height(root->right));
    int balance = getBalance(root);
    // LL
    if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);

    // RR
    if (balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);
 
    // LR
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
  
    // RL
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

Node* createavl()
{
	Node *t=NULL;
	int n,x;
	cout<<"How many elements do you want in the tree? ";
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cout<<"Enter element "<<i<<" : ";
		cin>>x;
		t=insert(t,x);
	}
	return t;
}

void deleteavl(Node* t)
{
	if(t)
	{
		deleteavl(t->left);
    	deleteavl(t->right);
	    delete t;
	}
}


void printavl(Node* p, int indent=0)
{
    if(p != NULL) {
        if(p->right) {
            printavl(p->right, indent+4);
        }
        if (indent) {
            cout << setw(indent) << ' ';
        }
        if (p->right) cout<<" /\n" << setw(indent) << ' ';
        cout<< p->key << "\n ";
        if(p->left) {
            cout << setw(indent) << ' ' <<" \\\n";
            printavl(p->left, indent+4);
        }
    }
}


void intrav(Node* p)
{
	if(p)
	{
		intrav(p->left);
		cout<<p->key<<" ";
		intrav(p->right);
	}
}

void pretrav(Node* p)
{
	if(p)
	{
		cout<<p->key<<" ";
		pretrav(p->left);
		pretrav(p->right);
	}
}

void postrav(Node* p)
{
	if(p)
	{
		postrav(p->left);
		postrav(p->right);
		cout<<p->key<<" ";
	}
}

int main()
{
	int n,x;
	cout<<"Create an AVL tree\n";
	Node *t=createavl();
	do
	{
		cout<<"\nMENU";
		cout<<"\n1. Insert an element to the AVL tree";
		cout<<"\n2. Delete an element from the AVL tree";
		cout<<"\n3. Print the AVL tree";
		cout<<"\n4. Print the Inorder Traversal of the tree";
		cout<<"\n5. Print the Preorder Traversal of the tree";
		cout<<"\n6. Print the Postorder Traversal of the tree";
		cout<<"\nPress any of the rest to Exit";
		cout<<"\nWhat do you want to do? ";
		cin>>n;
		cout<<"\n";
		switch(n)
		{
			case 1 : cout<<"Enter the element to be inserted : ";
			         cin>>x;
			         t=insert(t,x);
			         system("PAUSE");
			         break;
			         
			case 2 : cout<<"Enter the element to be deleted : ";
			         cin>>x;
			         t=deleteNode(t,x);
			         system("PAUSE");
			         break;
			         
			case 3 : printavl(t);
			         cout<<"\nThe tree looks 90 degree rotated anticlockwise\n";
			         system("PAUSE");
			         break;
			         
			case 4 : cout<<"Inorder Traversal is ";
			         intrav(t);
			         cout<<"\n";
			         system("PAUSE");
			         break;

			case 5 : cout<<"Preorder Traversal is ";
			         pretrav(t);
			         cout<<"\n";
			         system("PAUSE");
			         break;                     

			case 6 : cout<<"Postorder Traversal is ";
			         postrav(t);
			         cout<<"\n";
			         system("PAUSE");
			         break;
					 
			default : cout<<"Program Exiting\n";
			          system("PAUSE");
					  break;
		}
	}while(n>=1&&n<=6);
	deleteavl(t);
	return 0;
}
