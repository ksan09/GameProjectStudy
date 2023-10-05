#pragma once
//∏≈≈©∑Œ

#define SINGLE(type)				\
									\
private:							\
	type()  {};						\
	~type() {};						\
public:								\
	static type* GetInst()			\
	{								\
		static type m_Inst;			\
		return &m_Inst;				\
	}			

#define WINDOW_CLASS_NAME L"Gampr"
#define WINDOW_WIDTH	1280
#define WINDOW_HEIGHT	720

