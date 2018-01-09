#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <ctime>
#include <stdlib.h>

constexpr float PI = 3.14159265f;
constexpr double PI_D = 3.1415926535897932;

int Random_Int(int min, int max);


template <typename T>
inline auto sq(const T& x)
{
	return x * x;
}

template<typename T>
inline T wrap_angle(T theta)
{
	const T modded = fmod(theta, (T)2.0 * (T)PI_D);
	return (modded > (T)PI_D) ?
		(modded - (T)2.0 * (T)PI_D) :
		modded;
}

template<typename T>
inline T interpolate(const T& src, const T& dst, float alpha)
{
	return src + (dst - src) * alpha;
}

template <typename T>
class _Vec2
{
public:
	_Vec2()
	{}
	_Vec2(T x, T y)
		:
		x(x),
		y(y)
	{}
	_Vec2(const _Vec2& vect)
		:
		_Vec2(vect.x, vect.y)
	{}
	template <typename T2>
	explicit operator _Vec2<T2>() const
	{
		return{ (T2)x,(T2)y };
	}
	T		LenSq() const
	{
		return sq(*this);
	}
	T		Len() const
	{
		return sqrt(LenSq());
	}
	_Vec2&	Normalize()
	{
		const T length = Len();
		x /= length;
		y /= length;
		return *this;
	}
	_Vec2	GetNormalized() const
	{
		_Vec2 norm = *this;
		norm.Normalize();
		return norm;
	}
	_Vec2	operator-() const
	{
		return _Vec2(-x, -y);
	}
	_Vec2&	operator=(const _Vec2 &rhs)
	{
		x = rhs.x;
		y = rhs.y;
		return *this;
	}
	_Vec2&	operator+=(const _Vec2 &rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
	_Vec2&	operator-=(const _Vec2 &rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}
	T		operator*(const _Vec2 &rhs) const
	{
		return x * rhs.x + y * rhs.y;
	}
	_Vec2	operator+(const _Vec2 &rhs) const
	{
		return _Vec2(*this) += rhs;
	}
	_Vec2	operator-(const _Vec2 &rhs) const
	{
		return _Vec2(*this) -= rhs;
	}
	_Vec2&	operator*=(const T &rhs)
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}
	_Vec2	operator*(const T &rhs) const
	{
		return _Vec2(*this) *= rhs;
	}
	_Vec2&	operator/=(const T &rhs)
	{
		x /= rhs;
		y /= rhs;
		return *this;
	}
	_Vec2	operator/(const T &rhs) const
	{
		return _Vec2(*this) /= rhs;
	}
	bool	operator==(const _Vec2 &rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}
	bool	operator!=(const _Vec2 &rhs) const
	{
		return !(*this == rhs);
	}
public:
	T x;
	T y;
};

typedef _Vec2<float> Vec2;
typedef _Vec2<double> Ved2;
typedef _Vec2<int> Vei2;
typedef _Vec2<float> Vector2;

template < typename T >
struct _Rect
{
public:
	inline	_Rect() {}
	inline	_Rect(T top, T bottom, T left, T right)
		:
		top(top),
		bottom(bottom),
		left(left),
		right(right)
	{}
	inline	_Rect(const _Rect& rect)
		:
		top(rect.top),
		bottom(rect.bottom),
		left(rect.left),
		right(rect.right)
	{}
	inline	_Rect(_Vec2<T> p0, _Vec2<T> p1)
		:
		_Rect(min(p0.y, p1.y),
			max(p0.y, p1.y),
			min(p0.x, p1.x),
			max(p0.x, p1.x))
	{}
	inline	void Translate(_Vec2<T> d)
	{
		Translate(d.x, d.y);
	}
	inline	void Translate(T dx, T dy)
	{
		top += dy;
		bottom += dy;
		left += dx;
		right += dx;
	}
	template <typename T2>
	inline	operator _Rect<T2>() const
	{
		return { (T2)top,(T2)bottom,(T2)left,(T2)right };
	}
	inline	void ClipTo(const _Rect& rect)
	{
		top = std::max(top, rect.top);
		bottom = std::min(bottom, rect.bottom);
		left = std::max(left, rect.left);
		right = std::min(right, rect.right);
	}
	inline	T GetWidth() const
	{
		return right - left;
	}
	inline	T GetHeight() const
	{
		return bottom - top;
	}
	inline	bool Overlaps(const _Rect& rect) const
	{
		return top < rect.bottom && bottom > rect.top &&
			left < rect.right && right > rect.left;
	}
	template <typename T2>
	inline	bool Contains(_Vec2<T2> p) const
	{
		return p.y >= top && p.y <= bottom && p.x >= left && p.x <= right;
	}
	template <typename T2>
	inline	bool Contains(_Rect<T2> p) const
	{
		return p.top >= top && p.bottom <= bottom && p.left >= left && p.right <= right;
	}
public:
	T top;
	T bottom;
	T left;
	T right;
};

typedef _Rect< int > Rect;
typedef _Rect< float > RectF;



struct ARGB
{
public:
	ARGB(unsigned long Alpha = 255, unsigned long Red = 255, unsigned long Green = 255, unsigned long Blue = 255);
	bool operator==(const ARGB &other) const;
public:
	unsigned long Alpha, Red, Green, Blue;
};

struct Transform
{
public:
	Transform();
	Transform(const Vec2& position, float rotation = 0, const Vec2& scale = Vec2(1.0f, 1.0f));
	bool operator==(const Transform &other) const;
public:
	Vec2 position;
	float rotation;
	Vec2 scale;
};

