#include <iostream>
#include <vector>

using namespace std;

int main() 
{
	int input;
	int answer1 = 0;
	int answer2 = 0;

	cin >> input;

	while (input != 0)
	{
		answer1 *= 10;
		answer1 += input % 10;
		answer2 += input % 10;
		input *= 0.1;
	}

	cout << answer1 << endl << answer2;
}