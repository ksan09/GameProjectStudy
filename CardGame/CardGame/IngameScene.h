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
	vector<Card> deckList; // ī�� ��ġ ����Ʈ <- �����
	queue<Card> deck; // ���� ī�� ��ġ <- �ΰ��ӿ�
	vector<Card> hand;
	unordered_map<string, Card> cardList;

	Card block[5];
	queue<int> blockQ;

	Turn currentTurn;
	int currentSelectCardIndex;
	int maxCardIndex;
};

