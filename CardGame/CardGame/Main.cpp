#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <conio.h>
#include <Windows.h>
#include <vector>
#include <unordered_map>
#include "Define.h"
#include "console.h"
#include "GameLogic.h"

using namespace std;

int main()
{
	vector<Card> deck;
	unordered_map<string, Card> cardList;

	Card tempCard = { CARD_TYPE::DEF, 3 };
	CardRender(3, 10, tempCard);
	tempCard = { CARD_TYPE::ATK, 14 };
	CardRender(12, 11, tempCard);
	tempCard = { CARD_TYPE::DEF, 2 };
	CardRender(21, 12, tempCard);
}