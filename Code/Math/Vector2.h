#ifndef CHALLENGE_MATH_VECTOR2_H
#define CHALLENGE_MATH_VECTOR2_H

#include <cmath>
#include <iostream>

struct Vector2
{
    Vector2();
    explicit Vector2(float _xy);
    Vector2(float _x, float _y);
    Vector2(float _xy[2]);

    inline float& operator[](std::size_t _index) {
	return(data[_index]);
    };
    inline const float& operator[](std::size_t _index) const {
	return(data[_index]);
    };

    Vector2(const Vector2& _other) = default;


    Vector2 operator-() const;

    Vector2 operator+(const Vector2& _other) const;
    Vector2 operator-(const Vector2& _other) const;
    Vector2 operator*(float _scalar) const;
    Vector2 operator/(float _scalar) const;

    Vector2& operator+=(const Vector2& _other);
    Vector2& operator-=(const Vector2& _other);
    Vector2& operator*=(float _scalar);
    Vector2& operator/=(float _scalar);

    Vector2 operator*(const Vector2& _other) const;
    Vector2 operator/(const Vector2& _other) const;
    bool operator==(const Vector2& _other) const;
    bool operator!=(const Vector2& _other) const;

    union
    {
	float data[2];
	struct
	{
	    float x, y;
	};
	struct
	{
	    float r, g;
	};
	struct
	{
	    float s, t;
	};
    };
};

inline Vector2 operator*(float _scalar, const Vector2& _vector) {
    return(_vector * _scalar);
}
inline float dot(const Vector2& _a, const Vector2& _b)
{
    return(_a.x * _b.x + _a.y * _b.y);
}
inline float lengthSquared(const Vector2& _a)
{
    return(dot(_a, _a));
}
inline float length(const Vector2& _a)
{
    return(std::sqrtf(lengthSquared(_a)));
}
inline Vector2 normalize(const Vector2& _a)
{
    return(_a  * (1.0f / length(_a)));
}

inline std::ostream& operator<<(std::ostream& _os, const Vector2& _v)
{
    return(_os << "Vector2( " << _v[0] << " " << _v[1] << " )");
}

#endif // !#define CHALLENGE_VECTOR2_H

