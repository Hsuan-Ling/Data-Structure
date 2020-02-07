#include <iostream>
#include <string>
using namespace std;
#define STRARR new string[2]{}

class Hash {
public:
	string** table;
	int p;
	int size;
	Hash() :table(new string*[4]{ STRARR, STRARR, STRARR, STRARR }), p(2), size(4) {}
	void get(int index) {
		if (index >= size) cout << "Out of range.";
		else if (table[index][0].empty()) cout << "The bucket is empty.";
		else {
			cout << table[index][0];
			if (!table[index][1].empty()) cout << " " << table[index][1];
		}
		cout << endl;
	}

	int h(string s, int size) {
		if(size >= 8) return((s[0] - 'A' + 4) % (size / 8)) * 8 + (s[1] - '0') % size;
		else return (s[1] - '0') % size;
	}

	int put(string s) {
		int hash = h(s, size);
		if (table[hash][0].empty()) table[hash][0] = s;
		else if (table[hash][1].empty()) table[hash][1] = s;
		else {
			string* arr = table[hash];
			int* arrHash = new int[2]{ h(arr[0], size), h(arr[1], size) };
			int idx = 0;

			for (int i = 0; i < 2; i++) {
				if (arrHash[i] == hash)  arr[idx++] = arr[i];
				else {
					if (table[arrHash[i]] == arr) table[arrHash[i]] = new string[2]{ arr[i] };
					else table[arrHash[i]][1] = arr[i];
				}
			}
			if (idx == 2) {
				string** newTable = new string*[size * 2]{};
				for (int i = 0; i < size; i++) newTable[i] = newTable[i + size] = table[i];
				delete[] table;
				table = newTable;
				size *= 2;
				return put(s);
			}
			if (!idx) table[hash][1].clear();
			table[hash][idx] = s;
		}
		return hash;
	}
};

int main()
{
	string cmd;
	Hash h;
	while (cin >> cmd) {
		if (cmd == "put") {
			string key;
			cin >> key;
			cout << h.put(key) << endl;
		}
		else if (cmd == "get") {
			int index;
			cin >> index;
			h.get(index);
		}
		else return 0;
	}
}