#pragma once
namespace St3_Function
{
	template<typename T> //����Ʈ Ÿ�� �Ÿ�����
	float Distance(T* _dst,T* _src)
	{
		float Width = (_src->x - _src->x);
		float Height = (_src->y - _dst->y);

		return sqrt(Width * Width + Height * Height);
	}

}