#pragma once

// ﾃﾝﾌﾟﾚｰﾄ使用
// float,intなにが来ても使用可能なように
template<typename T>
struct Vector2
{
	Vector2() :x(0), y(0) {};
	Vector2(T inx, T iny) :x(inx), y(iny) {};
	T x, y;

	void operator+=(const Vector2<T>& vec)
	{
		x += vec.x;
		y += vec.y;
	}
	void operator-=(const Vector2<T>& vec)
	{
		x -= vec.x;
		y -= vec.y;
	}
	void operator*=(int scale)
	{
		x *= scale;
		y *= scale;
	}

	Vector2<T> operator*(int scale) const
	{
		return Vector2<T>(x * scale, y * scale);
	}

	Vector2<T> operator-(void) const
	{
		return Vector2<T>(-x, -y);
	}
};
template<typename T>
Vector2<T> operator+(const Vector2<T>& vec1, const Vector2<T>& vec2)
{
	return Vector2<T>((vec1.x + vec2.x), (vec1.y + vec2.y));
}
template<typename T>
Vector2<T> operator-(const Vector2<T>& vec1, const Vector2<T>& vec2)
{
	return Vector2<T>((vec1.x - vec2.x), (vec1.y - vec2.y));
}
template<typename T>
Vector2<T> operator/(const Vector2<T>& vec1, const Vector2<T>& vec2)
{
	return Vector2<T>((vec1.x / vec2.x), (vec1.y / vec2.y));
}

using Vector2I = Vector2<int>;
using Vector2F = Vector2<float>;

template<typename T>
struct Vector3
{
	Vector3() :x(0), y(0), z(0) {};
	Vector3(T inx, T iny, T inz) :x(inx), y(iny), z(inz) {};

	T x, y, z;
	void operator+=(Vector3<T>& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
	}
	void operator-=(Vector3<T>& vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
	}
	void operator*=(int scale)
	{
		x *= scale;
		y *= scale;
		z *= scale;
	}

	Vector3 operator*(int scale) const
	{
		return Vector3(x * scale, y * scale, z * scale);
	}

	Vector3 operator-(void) const
	{
		return Vector3(-x, -y, -z);
	}
};

template<typename T>
Vector3<T> operator+(const Vector3<T>& vec1, const Vector3<T>& vec2)
{
	return Vector3<T>((vec1.x + vec2.x),
		(vec1.y + vec2.y),
		(vec1.z + vec2.z));
}

template<typename T>
Vector3<T> operator-(const Vector3<T>& vec1, const Vector3<T>& vec2)
{
	return Vector3<T>((vec1.x - vec2.x),
		(vec1.y - vec2.y),
		(vec1.z - vec2.z));
}

using Vector3I = Vector3<int>;
using Vector3F = Vector3<float>;

// 当たり判定用ﾎﾞｯｸｽ構造体
struct BoxRect
{
	// ｻｲｽﾞ
	Vector3I size_;
	// ﾎﾟｼﾞｼｮﾝ
	Vector3F pos_;
};

struct Rect
{
	Vector2F pos2D_;
	int w, h;

	Rect(int x, int y, int inw, int inh) :
		pos2D_(x, y), w(inw), h(inh) {};

	void SetCenter(const Vector3F inpos)
	{
		pos2D_.x = inpos.x;
		pos2D_.y = inpos.y;
	}

	const Vector2F Center(void) const
	{
		return pos2D_;
	}

	float Left(void) const
	{
		return (float)(pos2D_.x - w / 2);
	}

	float Right(void) const
	{
		return (float)(pos2D_.x + w / 2);
	}
	float Top(void) const
	{
		return (float)(pos2D_.y - h / 2);
	}
	float Bottom(void) const
	{
		return (float)(pos2D_.y + h / 2);
	}

	//自分の矩形を描画
	void Draw(void) const;
};

