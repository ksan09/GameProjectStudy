#pragma once
#include "pch.h"
#include "Scene.h"
#include "GameLogic.h"

enum class Turn 
{
	Draw = 0,
	Main,
	Battle,
	End,
};

class IngameScene : public Scene
{
public:
	IngameScene();
	virtual ~IngameScene();

public:
	void Init()				override;
	void Update(float dt)	override;
	void Render()			override;

private:
	vector<Card> deckList; // 카드 뭉치 리스트 <- 저장용
	queue<Card> deck; // 현재 카드 뭉치 <- 인게임용
	vector<Card> hand;
	unordered_map<string, Card> cardList;

	Card block[5];
	queue<int> blockQ;

	Turn currentTurn;
	int currentSelectCardIndex;
	int maxCardIndex;
};

