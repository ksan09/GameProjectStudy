#include <iostream>

using namespace std;

int main() {
	int a1, a2, b1, b2;

	cin >> a1 >> a2 >> b1 >> b2;

	if (a1 > a2) {
		int temp = a1;
		a1 = a2;
		a2 = temp;
	}

	if ((a1 < b1 && b1 < a2 && (a2<b2 || a1>b2)) || (a1 < b2 && b2 < a2 && (a2<b1 || a1>b1)))
		cout << "cross";
	else
		cout << "not cross";

}