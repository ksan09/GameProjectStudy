#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <conio.h>
#include <Windows.h>
#include <vector>
#include <queue>
#include <unordered_map>
#include "Define.h"
#include "console.h"
#include "GameLogic.h"

using namespace std;

int main()
{
	vector<Card> deckList; // 카드 뭉치 리스트 <- 저장용
	queue<Card> deck; // 현재 카드 뭉치 <- 인게임용
	vector<Card> hand;
	unordered_map<string, Card> cardList;
	
	Init(deckList, cardList);

	while (true)
	{
		Update(deckList, deck, hand);
		Render(hand);
		Event();
	}
}