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
	int m_itemid; // 아이템 id
	int m_rarity; // 등급
	int m_userid; // 지금 누가 가지고있냐
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