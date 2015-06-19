#ifndef CHALLENGE_MATH_MATRIX4_H
#define CHALLENGE_MATH_MATRIX4_H

#include <Math/Vector4.h>

#include <array>

namespace Challenge
{
class Matrix4
{
public:
	Matrix4();
	explicit Matrix4(float x);
	explicit Matrix4(const Vector4& v0,
						  const Vector4& v1,
						  const Vector4& v2,
						  const Vector4& v3);

	Matrix4(const Matrix4& _other) = default;

	Vector4& operator[](std::size_t index) {
		return(data[index]);
	}
	const Vector4& operator[](std::size_t index) const {
		return(data[index]);
	}

	bool operator==(const Matrix4& m2) const;
	bool operator!=(const Matrix4& m2) const;
	
	
	Matrix4& operator=(const Matrix4& other) = default;

	Matrix4 operator+(const Matrix4& other) const;
	Matrix4 operator-(const Matrix4& other) const;
	
	Matrix4 operator*(const Matrix4& m2) const;
	Vector4 operator*(const Vector4& v) const;
	Matrix4 operator*(float scalar) const;
	
	Matrix4 operator/(float scalar) const;
	Matrix4& operator+=(const Matrix4& other);
	Matrix4& operator-=(const Matrix4& other);
	Matrix4& operator*=(const Matrix4& other);


	inline Matrix4 transpose() const
	{
		Matrix4 result;

		for (std::size_t i = 0; i < 4; i++) {
			for (std::size_t j = 0; j < 4; j++) {
				result[i][j] = data[j][i];
			}
		}
		return(result);
	}

	float determinant() const;
	Matrix4 inverse() const;

	std::array<Vector4, 4> data;
};

inline Matrix4 operator*(float scalar, const Matrix4& m)
{
	return(m * scalar);
}

inline Matrix4 transpose(const Matrix4& m)
{
	return(m.transpose());
}

inline float determinant(const Matrix4& m)
{
	return(m.determinant());
}

inline Matrix4 inverse(const Matrix4& m)
{
	m.inverse();
}

inline Matrix4 hadamardProduct(const Matrix4& a, const Matrix4& b)
{
	Matrix4 result;

	for (std::size_t i = 0; i < 4; i++) {
		result[i] = a[i] * b[i];
	}
	return(result);
}

inline std::ostream& operator<<(std::ostream& os, const Matrix4& m)
{
	os << "Matrix4(";
	for (std::size_t i = 0; i < 4; i++) {
		os << "\n\t" << m[i];
	}
	os << "\n)";
	return(os);
}

} // !namespace Challenge
#endif