#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Maze
{
private:
	vector <vector<int> > directionPath;

public:
	void output();
	void findPath(vector <vector <int> > board, int x, int y, vector <int> path);
	void reset() { directionPath.clear(); }

};

void Maze::output()
{
	if (directionPath.size() == 0)
	{
		cout << "No path" << endl;
		return;
	}

	for (int i = 0; i < directionPath.size(); i++)
	{
		int x = 0;
		int y = 0;
		cout << "(0,0)";

		for (int j = 0; j < directionPath[i].size(); j++)
		{
			if (directionPath[i][j] == 0) x = x - 1; //left
			else if (directionPath[i][j] == 1) y = y - 1; //up
			else if (directionPath[i][j] == 2) y = y + 1; //down
			else if (directionPath[i][j] == 3) x = x + 1; //right

			cout << ",(" << x << "," << y << ")";
		}
	}
}

void Maze::findPath(vector <vector <int> > board, int x, int y, vector <int> path)
{
	if (x == board.size() - 1 && y == board.size[x]() - 1)
	{
		directionPath.push_back(path);
		return;
	}

	board[x][y] = 1;

	if (x != 0 && board[x - 1][y] == 0) //left
	{
		x = x - 1;
		path.push_back(0);
		findPath(board, x, y, path);
		path.pop_back();
		x = x + 1;
	}
	if (y != 0 && board[x][y-1] == 0) //up
	{
		y = y - 1;
		path.push_back(1);
		findPath(board, x, y, path);
		path.pop_back();
		y = y + 1;
	}
	if (y != board[x].size() - 1 && board[x][y + 1] == 0) //down
	{
		y = y + 1;
		path.push_back(1);
		findPath(board, x, y, path);
		path.pop_back();
		y = y - 1;
	}
	if (x != board.size()-1 && board[x + 1][y] == 0) //right
	{
		x = x + 1;
		path.push_back(4);
		findPath(board, x, y, path);
		path.pop_back();
		x = x - 1;
	}
}

int main()
{
	Maze manager;
	int m, n;
	cin >> m >> n;
	vector <vector <int> > board;
	
	for (int i = 0; i < m; i++)
	{
		string tmp;
		cin >> tmp;

		for (int j = 0; j < n; j++)
		{
			board[i][j] = tmp[j] - '0';
		}
	}

	
	board[0][0] = 0;
	
}