#include <iostream>
#include <string>
using namespace std;

class heap{
public:
	int *data;
	int n;
	int current;
	heap(int n) :data(new int[n + 1]), n(n), current(1) {}
	void adjust(){
		for (int i = n / 2; i > 0; i--)	{
			heapify(i);
		}
	}
	void heapify(int i){
		if (i * 2 > n) return;
		int leftValue = data[i * 2];
		int rightValue = (i * 2 + 1) <= n ? data[i * 2 + 1] : -1;
		int maxIndex = (leftValue > rightValue) ? i * 2 : i * 2 + 1;
		if (data[maxIndex] > data[i]){
			int tmp = data[maxIndex];
			data[maxIndex] = data[i];
			data[i] = tmp;
			heapify(maxIndex);
		}
	}
	void show() { cout << data[current] << endl; }
	void right(){
		current = current * 2 + 1;
		show();
	}
	void left(){
		current = current * 2;
		show();
	}
	void doHeap(){
		data[1] = data[n--];
		adjust();
		current = 1;
	}
	int& operator[] (int index) { return data[index]; }
};

void operator >> (istream& is, heap h){
	for (int i = 1; i <= h.n; i++) cin >> h[i];
	h.adjust();
}

int main(){
	int n;
	cin >> n;
	heap h(n);
	cin >> h;

	string cmd;
	while (cin >> cmd) {
		if (cmd[0] == 's') h.show();
		else if (cmd[0] == 'l') h.left();
		else if (cmd[0] == 'r') h.right();
		else if (cmd[0] == 'h') h.doHeap();
	}
}