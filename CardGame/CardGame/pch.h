#pragma once

// 각종 Header
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <conio.h>
#include <windows.h>
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

using namespace std;


// 각종 Define
#define PI				3.14159265f

// 싱글톤 디파인
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