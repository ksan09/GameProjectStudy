#pragma once
#include "define.h"
#include "Object.h"
/*
* 싱글톤: 객체의 인스턴스가 오직 1개만 생성되는 패턴
* - 모든 곳에서 참조가 가능해야 함
* 
* 다이나믹 싱글톤: 
* 장점) 내가 원할 때 생성하고 지움, 필요할 때 생성함.
* 단점) 메모리가 힙에 상주함, 직접 지워줘야함
* 
* 정적 싱글톤
* 장점) 메모리가 데이터에 있음, 직접 안지워도 됨
* 단점) 원하지 않아도 생성
*/

class Core // GameManager
{
	SINGLE(Core);
public:
	bool Init(HWND _hWnd, POINT _ptResolution);
	void GameLoop();
	void Release();
public:
	const HWND& GetHWnd() const
	{
		return m_hWnd;
	}
private:
	void Update();
	void Render();
private:
	HWND m_hWnd;			// 메인 윈도우 핸들
	HDC m_hDC;				// 메인 윈도우 DC
	HDC m_hBackDC;			// 백 버퍼 DC
	HBITMAP m_hBackbit;		// 백 비트맵
	POINT m_ptResolution;
	Object m_obj;
};

