#pragma once

// ���� Header
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>
#include <tchar.h>
#include <memory>
#include <string>
#include <ctime>
#include <vector>
#include <array>
#include <list>
#include <map>
#include <queue>
#include <unordered_map>

#pragma comment(lib, "winmm.lib")

using namespace std;


// ���� Define
#define PI				3.14159265f

// �̱��� ������
#define DECLARE_SINGLE(type)	\
private:						\
	type() {}					\
	~type() {}					\
public:							\
	static type* GetInstance()	\
	{							\
		static type instance;	\
		return &instance;		\
	}							\

#define GET_SINGLE(type)	type::GetInstance()