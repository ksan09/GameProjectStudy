#pragma once
class TimeMgr
{
	SINGLE(TimeMgr);
public:
	void Init();
	void Update();
private:
	// DT(Delta time): 1�����Ӵ� �ð�
	
	// FPS (Frame per second) : 1�ʴ� frame
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llFrequency; //��
};

