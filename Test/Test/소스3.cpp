#include <iostream>
#include <vector>
#include <malloc.h>
using namespace std;
// 람다: 함수 객체를 복잡하면 한 1~2분 걸리는 걸 10초짜리로 만들어주는 문법.

enum class ItemType
{
	None,
	Weapon,
	Armor,
};

class Item
{
public:
	Item() = default;
	Item(int _itemid, int _rarity, ItemType _type)
		: m_itemid(_itemid)
		, m_rarity(_rarity)
		, m_type(_type)
	{   }

public:
	int m_itemid; // 아이템 id
	int m_rarity; // 등급
	ItemType m_type; // 지금 누가 가지고있냐
};

class IsWeapon
{
public:
	bool operator()(Item& item)
	{
		return item.m_type == ItemType::Weapon;
	}
};
// 람다 표현식
// [](){}


int main()
{
	vector<Item> v;
	// 아이템 번호 1, 등급 1, 타입 없음

	Item i1, i2;
	v.push_back(i1); // LValue
	i1 = i2; // 복사 생성자 호출됨

	v.push_back(Item( 1, 1, ItemType::None )); // RValue
	v.push_back(Item( 2, 5, ItemType::Weapon )); 
	v.push_back(Item( 3, 10, ItemType::Armor )); 

	// 스마트 포인터
	// 포인터가 똑똑한 거
	unique_ptr<Item> uptr = std::make_unique<Item>();
	unique_ptr<Item> uptr2 = std::move(uptr);			// 소유권 이동

	// 매우 귀찮다
	auto finditem = std::find_if(v.begin(), v.end(), IsWeapon());
	if (finditem != v.end())
		cout << "아이템 ID: " << finditem->m_itemid << endl;

	// 람다 사용
	auto findlambda = [](Item& item) { return item.m_type == ItemType::Weapon; };
	auto finditem2 = std::find_if(v.begin(), v.end(), findlambda);

	// [] <- 캡쳐
	int id = 10;
	auto findlambda = [id](Item& item) { return item.m_itemid = id; };
}