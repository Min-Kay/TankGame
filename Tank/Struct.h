#pragma once

typedef struct tagInfo
{
	float		X;	// 내가 그리고자 하는 물체의 중점 x
	float		Y; // 내가 그리고자 하는 물체의 중점 y

	float		Width; // 가로 사이즈
	float		Height; // 세로 사이즈

	int		Att;
	int		Max_Hp;
	int		Hp;

}INFO;

class CDeleteObj
{
public:
	CDeleteObj() {}
	~CDeleteObj() {}

public:
	template<typename T>
	void operator()(T& Temp)
	{
		if (nullptr != Temp)
		{
			delete Temp;
			Temp = nullptr;
		}
	}
};
