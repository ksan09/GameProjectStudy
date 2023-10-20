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
	// DT(Delta time): 1�����Ӵ� �ð�
	
	// FPS (Frame per second) : 1�ʴ� frame
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llFrequency; //��
	float			m_dT;
	UINT			m_framecount; // ������ ȣ�� üũ
	float			m_accFrameTime; // 1�� ������
	UINT			m_fps; // fps
};

