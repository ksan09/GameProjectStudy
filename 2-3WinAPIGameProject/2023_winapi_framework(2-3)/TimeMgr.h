#pragma once
class TimeMgr
{
	SINGLE(TimeMgr);
public:
	void Init();
	void Update();
private:
	// DT(Delta time): 1프레임당 시간
	
	// FPS (Frame per second) : 1초당 frame
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llFrequency; //빈도
};

