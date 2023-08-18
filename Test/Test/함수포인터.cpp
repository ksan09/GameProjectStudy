#include <iostream>
#include <vector>
using namespace std;

//�Լ� ������
//int Add(int a, int b) -> typedef int (�̸�)(int, int);
typedef int (FUNC_TYPE)(int, int);
//using FUNC_TYPE2 = int(int, int);

//�Լ� ��ü. (Functor)
// ��ü�� �Լ�ó�� ���� ���� ��
// �Լ� �������� ����: typedef ����, ������ �� ������ ��� �Ұ�
class Functor
{
public:
	void operator()(int val)
	{
		cout << "�Լ� ��ü" << endl;
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
	int m_itemid; // ������ id
	int m_rarity; // ���
	int m_userid; // ���� ���� �������ֳ�
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
		// ���� ������ ����
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
	// �Լ� �ּ� ��µ�
	//cout << Add << endl;

	// ���� �޸�
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