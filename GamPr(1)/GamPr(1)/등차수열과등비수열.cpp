#include <iostream>

using namespace std;

int ArithmeticSeq(int r, int a1, int n);

int GeometricSeq(int r, int a1, int n);


int main() {
	int r, a1, n;
	cout << "규칙 r, 시작 값 a1, 찾을 값 n을 차례대로 3개의 숫자를 적으세요: ";
	cin >> r >> a1 >> n;
	cout << "등차수열 값: " << ArithmeticSeq(r, a1, n) << "\n";
	cout << "등비수열 값: " << GeometricSeq(r, a1, n) << "\n";
}

int ArithmeticSeq(int r, int a1, int n) {
	if (n == 0)
		return 0;
	if (n == 1)
		return a1;
	else
		return ArithmeticSeq(r, a1, n - 1) + r;
}

int GeometricSeq(int r, int a1, int n) {
	if (n == 0)
		return 0;
	if (n == 1)
		return a1;
	else
		return ArithmeticSeq(r, a1, n - 1) * r;
}