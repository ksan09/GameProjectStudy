#include <iostream>
#include <vector>

using namespace std;

int main()
{
    srand((unsigned int)time(NULL));

    vector<int> numList;

    // 배열 안에 1~10까지의 값을 넣어준다
    for (int i = 0; i < 10; i++) {
        numList.push_back(i + 1);
    }

    for (int i = 0; i < numList.size(); i++) {
        int randomIndex = rand() % (numList.size() - i) + i;

        int temp = numList[i];
        numList[i] = numList[randomIndex];
        numList[randomIndex] = temp;
    }

    for (int i = 0; i < 3; i++) {
        cout << numList[i] << "\n";
    }

}