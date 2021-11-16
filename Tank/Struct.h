#pragma once

typedef struct tagInfo
{
	float		X;	// ���� �׸����� �ϴ� ��ü�� ���� x
	float		Y; // ���� �׸����� �ϴ� ��ü�� ���� y

	float		Width; // ���� ������
	float		Height; // ���� ������

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
