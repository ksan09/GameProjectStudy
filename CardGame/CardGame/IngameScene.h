#pragma once
#include "pch.h"
#include "Scene.h"
#include "GameLogic.h"

enum class Turn 
{
	Draw = 0,
	Main,
	Battle,
	Animation,
	End,
};
enum class PlayerState
{
	None,
	MonsterDEF,
	Damaged,
	ATK,
	DEF,
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
	void RegisterMob(string name, int hp, int cardCnt, wstring mobImage[15]);

private:
	vector<Card> deckList; // ī�� ��ġ ����Ʈ <- �����
	queue<Card> deck; // ���� ī�� ��ġ <- �ΰ��ӿ�

	vector<Card> hand;
	unordered_map<string, Card> cardList;

	Monster currentMonster;
	vector<string> mobNameList;
	string systemText;
	unordered_map<string, Monster> mobList;

	Card block[5];
	queue<int> blockQ;

	PlayerState p_state;
	Turn currentTurn;
	int currentSelectCardIndex;
	int maxCardIndex;

	int battleBlock;
	float battleTime;
	int playerHP;
	int playerMaxHP;
};

