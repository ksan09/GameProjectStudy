#include <iostream>
#include <vector>
using namespace std;

//함수 포인터
//int Add(int a, int b) -> typedef int (이름)(int, int);
typedef int (FUNC_TYPE)(int, int);
//using FUNC_TYPE2 = int(int, int);

//함수 객체. (Functor)
// 객체를 함수처럼 쓰고 싶은 것
// 함수 포인터의 단점: typedef 귀찮, 형식이 안 맞으면 사용 불가
class Functor
{
public:
	void operator()(int val)
	{
		cout << "함수 객체" << endl;
		m_val += val;
		cout << m_val << endl;
	}

public:
	int m_val = 0;
};

int Add(int a, int b) { return a + b; }
typedef int (FUNC2)(int, int);

class Item
{
public:
	Item()
		: m_itemid(0)
		, m_rarity(0)
		, m_userid(0)
	{   }
	void Upgrade(int _val)
	{
		m_rarity += 1;
	}

public:
	int m_itemid; // 아이템 id
	int m_rarity; // 등급
	int m_userid; // 지금 누가 가지고있냐
};

typedef bool (SELECTOR)(Item*, int);

bool IsRareitem(Item* _item)
{
	return (_item->m_rarity >= 2);
}
bool IsUseritem(Item* _item, int _userid)
{
	return _item->m_userid == _userid;
}

Item* Finditem(Item _items[], int _itemcnt, SELECTOR* _select)
{
	for (int i = 0; i < _itemcnt; i++)
	{
		// 조건 성립시 리턴
		Item* item = &_items[i];

		if (_select(item, 5))
			return item;
	}
	return nullptr;
}

int main()
{

	Functor func;
	func(10);
	func(10);

	//Item items[5] = { };
	//items[1].m_rarity = 3;
	//items[2].m_userid = 5;
	//Item* findItem = Finditem(items, 5, IsUseritem);
	//cout << findItem->m_rarity << endl;


	//cout << Add(1, 2) << endl;
	// 함수 주소 출력됨
	//cout << Add << endl;

	// 스택 메모리
	//int a;
	//float b; 
	//FUNC_TYPE* t;
	//t = Add;
	//t(3, 4);
	//int result = t(1, 2);
	//int result2 = (*t)(1, 2);
	//cout << result << endl;
	//cout << result2 << endl;
	
	
	//int test = 0;
}