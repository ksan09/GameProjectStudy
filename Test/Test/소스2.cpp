#include <iostream>
#include <vector>
using namespace std;



class Item
{
public:
	Item()
		: m_itemid(0)
		, m_rarity(0)
		, m_userid(0)
	{   }
	void Test()
	{

	};

public:
	int m_itemid; // ������ id
	int m_rarity; // ���
	int m_userid; // ���� ���� �������ֳ�
};

typedef void (Item::*TEST_FUNC)();

int main()
{
	TEST_FUNC fn;
	fn = &Item::Test;

	Item i1;
	(i1.*fn)();
	Item* i2 = new Item;
	(*(i2).*fn)();
	((i2)->*fn)();

}