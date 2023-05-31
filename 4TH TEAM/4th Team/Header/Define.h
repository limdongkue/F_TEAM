#pragma once


#define		WINCX		800
#define		WINCY		600

#define		OBJ_NOEVENT		0
#define		OBJ_DEAD		1

#define		VK_MAX			0xff

#define		TILECX			64
#define		TILECY			32

#define		TILEX			30
#define		TILEY			50

#define		MIN_STR			64
#define		MAX_STR			256

#define		RUBY			0x01		// -> 0001
#define		DIAMOND			0x02		// -> 0010
#define		SAPPHIRE		0x04		// -> 0100

#define		BACK_COLOR			RGB(212,192,212)


#define ERR_MSG(message)								\
::MessageBox(nullptr, message, L"error", MB_OK)

#define NO_COPY(ClassName)								\
ClassName(const ClassName&) = delete;					\
ClassName& operator=(const ClassName&) = delete;


#define SINGLETON(type)\
public:\
	static type* Get_Instance()\
	{\
		static type manager;\
		return &manager;\
	}\
private:\
	type();\
	~type();

extern HWND g_hWnd;



// 선언과 동시에 초기화 불가능, 먼저 선언된 전역변수와 자료형, 변수명까지 일치하는 상태에서만 사용 가능