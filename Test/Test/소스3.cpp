#include <iostream>
#include <vector>
#include <malloc.h>
using namespace std;
// ����: �Լ� ��ü�� �����ϸ� �� 1~2�� �ɸ��� �� 10��¥���� ������ִ� ����.

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
	int m_itemid; // ������ id
	int m_rarity; // ���
	ItemType m_type; // ���� ���� �������ֳ�
};

class IsWeapon
{
public:
	bool operator()(Item& item)
	{
		return item.m_type == ItemType::Weapon;
	}
};
// ���� ǥ����
// [](){}


int main()
{
	vector<Item> v;
	// ������ ��ȣ 1, ��� 1, Ÿ�� ����

	Item i1, i2;
	v.push_back(i1); // LValue
	i1 = i2; // ���� ������ ȣ���

	v.push_back(Item( 1, 1, ItemType::None )); // RValue
	v.push_back(Item( 2, 5, ItemType::Weapon )); 
	v.push_back(Item( 3, 10, ItemType::Armor )); 

	// ����Ʈ ������
	// �����Ͱ� �ȶ��� ��
	unique_ptr<Item> uptr = std::make_unique<Item>();
	unique_ptr<Item> uptr2 = std::move(uptr);			// ������ �̵�

	// �ſ� ������
	auto finditem = std::find_if(v.begin(), v.end(), IsWeapon());
	if (finditem != v.end())
		cout << "������ ID: " << finditem->m_itemid << endl;

	// ���� ���
	auto findlambda = [](Item& item) { return item.m_type == ItemType::Weapon; };
	auto finditem2 = std::find_if(v.begin(), v.end(), findlambda);

	// [] <- ĸ��
	int id = 10;
	auto findlambda = [id](Item& item) { return item.m_itemid = id; };
}