#include <iostream>
using namespace std;

class MatrixNode {
public:
	int value;
	MatrixNode* down;
	MatrixNode* right;
	int row, column;
	bool head;
	MatrixNode(bool head = false, int row = 0, int column = 0, int value = 0)
		:head(head), right(this), down(this), row(row), column(column), value(value) {
	}
	MatrixNode(const MatrixNode& a) :head(a.head), right(this), down(this), row(a.row), column(a.column), value(a.value) {
	}
	void transpose() {
		int tmp = row;
		row = column;
		column = tmp;
		MatrixNode* tmpPtr = right;
		right = down;
		down = tmpPtr;
	}
};

class Matrix {
public:
	MatrixNode* headNode;
	int row;
	int column;
	Matrix(int row = 0, int column = 0) :headNode(nullptr), row(row), column(column) {}

	Matrix(const Matrix& a) {
		operator=(a);
	}

	void newMatrix() {
		headNode = new MatrixNode(false);
		if (row && column) {
			MatrixNode* headRow = new MatrixNode(true);
			MatrixNode* headColumn = new MatrixNode(true);
			headNode->down = headRow;
			headNode->right = headColumn;
			for (int i = 1; i < row; i++) {
				headRow->down = new MatrixNode(true);
				headRow->down->row = i;
				headRow = headRow->down;
			}
			headRow->down = headNode;
			for (int i = 1; i < column; i++) {
				headColumn->right = new MatrixNode(true);
				headColumn->right->column = i;
				headColumn = headColumn->right;
			}
			headColumn->right = headNode;
		}
	}

	void insertNode(MatrixNode* node) {
		MatrixNode* headRow = headNode->down;
		MatrixNode* headColumn = headNode->right;
		for (int i = 0; i < node->row; i++) headRow = headRow->down;
		for (int i = 0; i < node->column; i++) headColumn = headColumn->right;

		MatrixNode * left = headRow->right;
		MatrixNode * up = headColumn->down;
		while (!left->right->head && left->right->column < node->column) left = left->right;
		while (!up->down->head && up->down->row < node->row) up = up->down;

		node->right = left->right;
		left->right = node;
		node->down = up->down;
		up->down = node;
	}

	void changeNode(MatrixNode* node, int value) {
		MatrixNode* tmpNode = operator[](std::pair<int, int>(node->row, node->column));
		if (tmpNode) tmpNode->value += value;
		else {
			if (value) {
				MatrixNode* newNode = new MatrixNode(*node);
				newNode->value = value;
				insertNode(newNode);
			}
		}
	}

	MatrixNode * operator[](std::pair<int, int> node) const
	{
		MatrixNode* headRow = headNode->down;
		for (int i = 0; i < node.first; i++) headRow = headRow->down;

		MatrixNode * findNode = headRow->right;
		while (!findNode->head && findNode->column != node.second) findNode = findNode->right;

		return findNode->head ? nullptr : findNode;
	}

	const Matrix & operator=(const Matrix & a)
	{
		row = a.row;
		column = a.column;
		if (a.row && a.column) {
			newMatrix();

			MatrixNode* aheadRow = a.headNode->down;
			while (aheadRow->head) {
				MatrixNode* aNode = aheadRow->right;
				while (!aNode->head) {
					MatrixNode* node = new MatrixNode(false);
					node->row = aNode->row;
					node->column = aNode->column;
					node->value = aNode->value;
					insertNode(node);
					aNode = aNode->right;
				}
				aheadRow = aheadRow->down;
			}
		}
		return *this;
	}

	Matrix operator+(const Matrix & a) const {
		if (a.column != column || a.row != row) return Matrix();
		Matrix * tmp = new Matrix(*this);
		MatrixNode * aheadRow = a.headNode->down;
		MatrixNode * aheadColumn = a.headNode->right;
		while (aheadRow->head) {
			MatrixNode* aNode = aheadRow->right;
			while (!aNode->head) {
				tmp->changeNode(aNode, aNode->value);
				aNode = aNode->right;
			}
			aheadRow = aheadRow->down;
		}
		return *tmp;
	}

	Matrix operator-(const Matrix & a) const {
		if (a.column != column || a.row != row) return Matrix();
		Matrix * tmp = new Matrix(*this);
		MatrixNode * aheadRow = a.headNode->down;
		MatrixNode * aheadColumn = a.headNode->right;
		while (aheadRow->head) {
			MatrixNode* aNode = aheadRow->right;
			while (!aNode->head) {
				tmp->changeNode(aNode, -aNode->value);
				aNode = aNode->right;
			}
			aheadRow = aheadRow->down;
		}
		return *tmp;
	}

	Matrix operator*(const Matrix & b) const {
		if (column != b.row) Matrix();
		Matrix* tmp = new Matrix(row, b.column);
		tmp->newMatrix();
		for (int i = 0; i < tmp->row; i++) {
			for (int j = 0; j < tmp->column; j++) {
				int value = 0;
				for (int k = 0; k < column; k++) {
					MatrixNode* node1 = operator[](pair<int, int>(i, k));
					MatrixNode* node2 = b.operator[](pair<int, int>(k, j));
					if (node1 && node2) value += node1->value * node2->value;
				}
				if (value) tmp->insertNode(new MatrixNode(false, i, j, value));
			}
		}
		return *tmp;
	}

	Matrix Transpose() const {
		Matrix* tmp = new Matrix(*this);
		MatrixNode* headRow = tmp->headNode->down, *headColumn = tmp->headNode->right;
		while (headRow->head) {
			MatrixNode* node = headRow->right;
			while (!node->head) {
				node->transpose();
				node = node->down;
			}
			headRow->transpose();
			headRow = headRow->right;
		}
		while (headColumn->head) {
			headColumn->transpose();
			headColumn = headColumn->down;
		}
		tmp->headNode->transpose();
		int tmpNum = tmp->column;
		tmp->column = tmp->row;
		tmp->row = tmpNum;
		return *tmp;
	}

	~Matrix() {
		if (headNode) {
			MatrixNode* headRow = headNode->down;
			MatrixNode* headColumn = headNode->right;
			MatrixNode* nextRow, *nextColumn;
			while (headRow->head) {
				nextRow = headRow->down;
				MatrixNode* node = headRow->right;
				MatrixNode* nextNode;
				while (!node->head) {
					nextNode = node->right;
					delete node;
					node = nextNode;
				}
				delete headRow;
				headRow = nextRow;
			}
			while (headColumn != headNode) {
				nextColumn = headColumn->right;
				delete headColumn;
				headColumn = nextColumn;
			}
			delete headNode;
		}
	}
};

istream& operator>>(istream& is, Matrix& m) {
	int line;
	is >> m.row >> m.column >> line;
	m.headNode = new MatrixNode(false);
	if (m.row && m.column) {
		m.newMatrix();
		while (line--) {
			MatrixNode* node = new MatrixNode(false);
			is >> node->row >> node->column >> node->value;
			m.insertNode(node);
		}
	}
	return is;
}

ostream& operator<<(ostream& os, const Matrix& m) {
	if (m.headNode)
	{
		MatrixNode* headRow = m.headNode->down;
		while (headRow->head) {
			MatrixNode* node = headRow->right;
			while (!node->head) {
				if (node->value) os << node->row << " " << node->column << " " << node->value << endl;
				node = node->right;
			}
			headRow = headRow->down;
		}
	}
	else {
		cout << "Error dimensions!" << endl;
	}
	return os;
}

int main() {
	char action;
	while (cin >> action) {
		if (action == '+') {
			Matrix matrix1, matrix2;
			cin >> matrix1 >> matrix2;
			Matrix matrix3 = matrix1 + matrix2;
			cout << matrix3;
		}
		else if (action == '-') {
			Matrix matrix1, matrix2;
			cin >> matrix1 >> matrix2;
			Matrix matrix3 = matrix1 - matrix2;
			cout << matrix3;
		}
		else if (action == '*') {
			Matrix matrix1, matrix2;
			cin >> matrix1 >> matrix2;
			Matrix matrix3 = matrix1 * matrix2;
			cout << matrix3;
		}
		else if (action == 'T') {
			Matrix matrix1;
			cin >> matrix1;
			Matrix matrix3 = matrix1.Transpose();
			cout << matrix3;
		}
	}
}