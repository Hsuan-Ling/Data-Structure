#include <iostream>
using namespace std;

void Move(int n, int from, int to, int another)
{
	if (n > 0)
	{
		Move(n - 1, from, another, to);
		printf("Move disk %d from tower %d to tower %d\n", n, from, to);
		Move(n - 1, another, to, from);
	}
}

int main()
{
	int N;
	cin >> N;

	Move(N, 2, 1, 3);
	system("pause");
	return 0;
}