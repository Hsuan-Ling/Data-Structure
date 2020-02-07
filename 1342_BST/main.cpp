#include <vector>
#include <iostream>
using namespace std;

class Node {
public:
	Node* right;
	Node* left;
	int value;
	Node(int value) :right(nullptr), left(nullptr), value(value) {}
};

class Tree {
private:
	Node** find(int value, Node** tree) {
		if (*tree) {
			if ((*tree)->value == value) return tree;
			else return find(value, &((value < ((*tree)->value)) ? (*tree)->left : (*tree)->right));
		}
		else return tree;
	}
	Node** smallest(Node** tree) {
		if ((*tree) && (*tree)->left) return smallest(&((*tree)->left));
		else return tree;
	}
	int getSize(Node **tree) {
		int sum = 0;
		if (*tree) sum = getSize(&((*tree)->left)) + getSize(&((*tree)->right)) + 1;
		return sum;
	}
	int getDepth(Node* node, Node* tree) {
		if (tree) {
			if (tree == node) return 1;
			else return getDepth(node, (node->value < (tree->value)) ? tree->left : tree->right) + 1;
		}
		else  return -1;
	}
	void showInorder(Node* tree) {
		if (tree) {
			showInorder(tree->left);
			cout << tree->value << " ";
			showInorder(tree->right);
		}
	}
	void showPreorder(Node* tree) {
		if (tree) {
			cout << tree->value << " ";
			showPreorder(tree->left);
			showPreorder(tree->right);
		}
	}
	void showPostorder(Node* tree) {
		if (tree) {
			showPostorder(tree->left);
			showPostorder(tree->right);
			cout << tree->value << " ";
		}
	}
	void rank(Node* tree, vector<int>& mRank) {
		if (tree) {
			rank(tree->left, mRank);
			mRank.push_back(tree->value);
			rank(tree->right, mRank);
		}
	}
public:
	Node* tree;
	Tree() :tree(nullptr) {}

	void insertNode(int value) {
		Node** newNode = find(value, &tree);
		if (*newNode) cout << "Duplicate data.";
		else {
			*newNode = new Node(value);
			cout << "[INSERT SUCCESS]";
		}
	}
	
	void deleteNode(int value) {
		Node** delNode = find(value, &tree);
		if ((*delNode)) {
			Node** change;
			if ((change = smallest(&((*delNode)->right))) && (*change)) {
				(*delNode)->value = (*change)->value;
				(*change) = nullptr;
			}
			else {
				*delNode = (*delNode)->left;
			}
			cout << "[DELETE SUCCESS]";
		}
		else cout << "No such value to delete.";
	}
	void searchByValue(int value) {
		Node** node = find(value, &tree);
		if (*node) {
			cout << "LeftSize = " << getSize(&((*node)->left)) + 1 << ", Depth = " << getDepth(*node, tree);
		}
		else cout << "No such value.";
	}
	void searchByRank(int value) {
		vector<int> mRank;
		rank(tree, mRank);
		if (value <= mRank.size()) cout << "The " << value << "th smallest is " << mRank[value - 1];
		else cout << "No such value.";
	}
	void showInorder() { showInorder(tree); }
	void showPreorder() { showPreorder(tree); }
	void showPostorder() { showPostorder(tree); }
};

int main() {
	int action, value;
	Tree tree;
	while (cin >> action) {
		if (action <= 4) cin >> value;
		if (action == 1) tree.insertNode(value);
		else if (action == 2) tree.deleteNode(value);
		else if (action == 3) tree.searchByValue(value);
		else if (action == 4) tree.searchByRank(value);
		else if (action == 5) tree.showInorder();
		else if (action == 6) tree.showPreorder();
		else if (action == 7) tree.showPostorder();
		cout << endl;
	}
}