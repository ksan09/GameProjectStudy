#pragma once
class TimeMgr
{
	SINGLE(TimeMgr);
public:
	void Init();
	void Update();
public:
	const float& GetDT() const { return m_dT; }
private:
	// DT(Delta time): 1프레임당 시간
	
	// FPS (Frame per second) : 1초당 frame
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llFrequency; //빈도
	float			m_dT;
	UINT			m_framecount; // 프레임 호출 체크
	float			m_accFrameTime; // 1초 누적용
	UINT			m_fps; // fps
};

