#include <iostream>
#include <vector>
#include <string>
using namespace std;
 
class Node
{
public:
    int data;
	int height;
    Node *left;
    Node *right;
};
 
int height(Node *N)
{
    if (N == NULL) return 0;
    return N->height;
}
 
int max(int a, int b)
{
    return (a > b) ? a : b;
}
 
Node* newNode(int data)
{
    Node* node = new Node();
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; 
    return(node);
}
 
 
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;
 
    // Perform rotation  
    x->right = y;
    y->left = T2;
 
    // Update heights  
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
 
    // Return new root  
    return x;
}
 
Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;
 
    // Perform rotation  
    y->left = x;
    x->right = T2;
 
    // Update heights  
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
 
    // Return new root  
    return y;
}
 
int getBalance(Node *N)
{
    if (N == NULL) return 0;
    return height(N->left) - height(N->right);
}
 
Node* insert(Node* node, int value)
{
    if (node == NULL) return(newNode(value));

    if (value < node->data)
        node->left = insert(node->left, value);
    else if (value > node->data)
        node->right = insert(node->right, value);
    else
        return node;
 
    node->height = 1 + max(height(node->left), height(node->right));
 
    int balance = getBalance(node);
 
    // Left Left Case  
    if (balance > 1 && value < node->left->data)
        return rightRotate(node);
    // Right Right Case  
    if (balance < -1 && value > node->right->data)
        return leftRotate(node);
    // Left Right Case  
    if (balance > 1 && value > node->left->data)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // Right Left Case  
    if (balance < -1 && value < node->right->data)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
}
 
Node * maxValueNode(Node* node)
{
    Node* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->right != NULL)
        current = current->right;
 
    return current;
}
 
Node* remove(Node* node, int value)
{
	if (node == NULL) return node;

    if (value < node->data)
		node->left = remove(node->left, value);
    else if (value > node->data)
		node->right = remove(node->right, value);
 
    else
    {
        // node with only one child or no child  
        if ((node->left == NULL) || (node->right == NULL))
        {
            Node *temp = node->left ? node->left : node->right;
 
            // No child case  
            if (temp == NULL)
            {
                temp = node;
				node = NULL;
            }
            else // One child case  
                *node = *temp; // Copy the contents of  
                               // the non-empty child  
            free(temp);
        }
        else
        {
            Node* temp = maxValueNode(node->left);
 
			node->data = temp->data;
			node->left = remove(node->left, temp->data);
        }
    }
 
    if (node == NULL) return node;
 
	node->height = 1 + max(height(node->left), height(node->right));
  
    int balance = getBalance(node);
 
    // Left Left Case  
    if (balance > 1 && getBalance(node->left) >= 0)
        return rightRotate(node);
 
    // Left Right Case  
    if (balance > 1 && getBalance(node->left) < 0)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
 
    // Right Right Case  
    if (balance < -1 && getBalance(node->right) <= 0)
        return leftRotate(node);
 
    // Right Left Case  
    if (balance < -1 && getBalance(node->right) > 0)
    {
		node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    return node;
}
 
void showPreoder(Node *root)
{
    if (root != NULL)
    {
        cout << "," << root->data;
        showPreoder(root->left);
        showPreoder(root->right);
    }
}
 
 
// Driver Code 
int main() {
    int value;
    string action;
    Node *root = NULL;
 
    while (cin >> action) {
        if (action == "INSERT" || action == "REMOVE") cin >> value;
        if (action == "INSERT") root = insert(root, value);
        else if (action == "REMOVE") root = remove(root, value);
        else if (action == "PRINT")
        {
            cout << root->data;
            showPreoder(root->left);
            if (root->right) showPreoder(root->right);
            cout << endl;
        }
    }
 
    return 0;
}