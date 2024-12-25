#pragma once

namespace waki
{
	template<typename _Ty>
	struct Vector2DBase
	{
		_Ty y;
		_Ty x;
	};

	template<typename _Ty>
	inline bool operator==(const Vector2DBase<_Ty>& left, const Vector2DBase<_Ty>& right)
	{
		return left.y == right.y && left.x == right.x;
	}

	template<typename _Ty>
	inline bool operator!=(const Vector2DBase<_Ty>& left, const Vector2DBase<_Ty>& right)
	{
		return left.y != right.y && left.x != right.x;
	}

	template<typename _Ty>
	inline Vector2DBase<_Ty>& operator++(Vector2DBase<_Ty>& vector2D)
	{
		++vector2D.y;
		++vector2D.x;
		return vector2D;
	}

	template<typename _Ty>
	inline Vector2DBase<_Ty> operator++(Vector2DBase<_Ty>& vector2D, int)
	{
		Vector2DBase<_Ty> temp(vector2D);
		++vector2D.y;
		++vector2D.x;
		return temp;
	}

	template<typename _Ty>
	inline  Vector2DBase<_Ty>& operator--(Vector2DBase<_Ty>& vector2D)
	{
		--vector2D.y;
		--vector2D.x;
		return vector2D;
	}

	template<typename _Ty>
	inline  Vector2DBase<_Ty> operator--(Vector2DBase<_Ty>& vector2D, int)
	{
		Vector2DBase<_Ty> temp(vector2D);
		--vector2D.y;
		--vector2D.x;
		return temp;
	}

	using Vector2D = Vector2DBase<unsigned>;
	using Vector2DI = Vector2DBase<int>;
	using Vector2DS = Vector2DBase<short>;
	using Vector2DD = Vector2DBase<double>;
	using Vector2DF = Vector2DBase<float>;
}