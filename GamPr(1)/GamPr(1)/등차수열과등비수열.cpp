#include <iostream>

using namespace std;

int ArithmeticSeq(int r, int a1, int n);

int GeometricSeq(int r, int a1, int n);


int main() {
	int r, a1, n;
	cout << "��Ģ r, ���� �� a1, ã�� �� n�� ���ʴ�� 3���� ���ڸ� ��������: ";
	cin >> r >> a1 >> n;
	cout << "�������� ��: " << ArithmeticSeq(r, a1, n) << "\n";
	cout << "������ ��: " << GeometricSeq(r, a1, n) << "\n";
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