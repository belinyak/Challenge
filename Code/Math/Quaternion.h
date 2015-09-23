#ifndef CHALLENGE_QUATERNION_H
#define CHALLENGE_QUATERNION_H

#include <Math/Vector3.h>
#include <Math/Matrix4.h>
#include <Math/Angle.h>
#include <Math/Constants.h>

   struct Quaternion
   {
      Quaternion();
      Quaternion(float _x, float _y, float _z, float _w);
      Quaternion(const Vector3& _v, float _s);

      inline const float operator[](std::size_t _index) const {
	 return(data[_index]);
      }
      inline float& operator[](std::size_t _index) {
	 return(data[_index]);
      }

      Quaternion operator-() const;

      Quaternion operator+(const Quaternion& _other) const;
      Quaternion operator-(const Quaternion& _other) const;
      Quaternion operator*(const Quaternion& _other) const;

      Quaternion operator*(float _s) const;
      Quaternion operator/(float _s) const;

      bool operator==(const Quaternion& _other) const;
      bool operator!=(const Quaternion& _other) const;

      Vector3 vector() const;
      Vector3& vector();

      float scalar() const;
      float& scalar();

      float lengthSquared() const;
      float length() const;

      union
      {
	 float data[4];
	 struct
	 {
	    float x, y, z, w;
	 };
      };
   };

   inline Quaternion operator*(float _s, const Quaternion& _other)
   {
      return(_s * _other);
   }
   inline float dot(const Quaternion& _q1, const Quaternion& _q2)
   {
      return(dot(_q1.vector(), _q2.vector() + _q1.w * _q2.w));
   }
   inline Quaternion cross(const Quaternion& _q1, const Quaternion& _q2)
   {
      return (Quaternion(_q1.w * _q2.x + _q1.x * _q2.w + _q1.y * _q2.z - _q1.z * _q2.y,
			 _q1.w * _q2.y + _q1.y * _q2.w + _q1.z * _q2.x - _q1.x * _q2.z,
			 _q1.w * _q2.z + _q1.z * _q2.w + _q1.x * _q2.y - _q1.y * _q2.x,
			 _q1.w * _q2.w - _q1.x * _q2.x - _q1.y * _q2.y - _q1.z * _q2.z));
   }



   inline Quaternion normalize(const Quaternion& _q)
   {
      return(_q * (1.0f / _q.length()));
   }
   inline Quaternion conjugate(const Quaternion& _q)
   {
      Quaternion value(-_q.vector(), _q.w);
      return(value);
   }
   inline Quaternion inverse(const Quaternion& _q)
   {
      Quaternion value = conjugate(_q) / dot(_q, _q);
   }

   inline Vector3 operator*(const Quaternion& _q, const Vector3& _v)
   {
      Vector3 value = 2.0f * cross(_q.vector(), _v);
      return (_v + _q.w * value + cross(_q.vector(), value));

   }

   inline float angle(const Quaternion& _q)
   {
      return (2.0f * std::acos(_q.w));
   }

   inline Vector3 axis(const Quaternion& _q)
   {
      float s2 = 1.0f - _q.w * _q.w;

      if (s2 <= 0.0f) {
	 return Vector3(0, 0, 1);
      }

      float invs2 = 1.0f / std::sqrt(s2);

      return _q.vector() * invs2;
   }

   //NOTE(mate): sets transform rotation to rotate _angle degrees around _axis
   inline Quaternion angleAxis(const float& _angle, const Vector3& _axis)
   {
      Quaternion value;

      const Vector3 a = normalize(_axis);

      const float s = std::sin((float)(0.5f * _angle));

      value.vector() = a * s;
      value.w = std::cos((float)(0.5f * _angle));

      return(value);
   }
   //NOTE(mate): https://en.wikipedia.org/wiki/Euler_angles
/*
   struct EulerAngles
   {
      float pitch;
      float yaw;
      float roll;
   };

   inline float roll(const Quaternion& _q)
   {
      return float(
	 std::atan2(2.0f * _q[0] * _q[1] + _q[2] * _q[3],
		    _q[0] * _q[0] + _q[3] * _q[3] - _q[1] * _q[1] - _q[2] * _q[2]));
   }
   inline float pitch(const Quaternion& _q)
   {
      return float(
	 std::atan2(2.0f * _q[1] * _q[2] + _q[3] * _q[0],
		    _q[3] * _q[3] - _q[0] * _q[0] - _q[1] * _q[1] + _q[2] * _q[2]));
   }
   inline float yaw(const Quaternion& _q)
   {
      return float(std::asin(-2.0f * (_q[0] * _q[2] - _q[3] * _q[1])));
   }

   inline EulerAngles quaternionToEulerAngles(const Quaternion& _q)
   {
      return{ pitch(_q), yaw(_q), roll(_q) };
   }
*/
   inline Matrix4 quaternionToMatrix4(const Quaternion& _q)
   {
      Matrix4 mat(1);
      Quaternion a = normalize(_q);

      const float xx = a.x * a.x;
      const float yy = a.y * a.y;
      const float zz = a.z * a.z;
      const float xy = a.x * a.y;
      const float xz = a.x * a.z;
      const float yz = a.y * a.z;
      const float wx = a.w * a.x;
      const float wy = a.w * a.y;
      const float wz = a.w * a.z;

      mat[0][0] = 1.0f - 2.0f * (yy + zz);
      mat[0][1] = 2.0f * (xy + wz);
      mat[0][2] = 2.0f * (xz - wy);

      mat[1][0] = 2.0f * (xy - wz);
      mat[1][1] = 1.0f - 2.0f * (xx + zz);
      mat[1][2] = 2.0f * (yz + wx);

      mat[2][0] = 2.0f * (xz + wy);
      mat[2][1] = 2.0f * (yz - wx);
      mat[2][2] = 1.0f - 2.0f * (xx + yy);

      return(mat);
   }

   inline Quaternion matrix4ToQuaternion(const Matrix4& m)
   {
      float fourXSquaredMinus1 = m[0][0] - m[1][1] - m[2][2];
      float fourYSquaredMinus1 = m[1][1] - m[0][0] - m[2][2];
      float fourZSquaredMinus1 = m[2][2] - m[0][0] - m[1][1];
      float fourWSquaredMinus1 = m[0][0] + m[1][1] + m[2][2];

      int biggestIndex = 0;
      float fourBiggestSquaredMinus1 = fourWSquaredMinus1;
      if (fourXSquaredMinus1 > fourBiggestSquaredMinus1)
      {
	 fourBiggestSquaredMinus1 = fourXSquaredMinus1;
	 biggestIndex = 1;
      }
      if (fourYSquaredMinus1 > fourBiggestSquaredMinus1)
      {
	 fourBiggestSquaredMinus1 = fourYSquaredMinus1;
	 biggestIndex = 2;
      }
      if (fourZSquaredMinus1 > fourBiggestSquaredMinus1)
      {
	 fourBiggestSquaredMinus1 = fourZSquaredMinus1;
	 biggestIndex = 3;
      }

      float biggestVal = std::sqrt(fourBiggestSquaredMinus1 + 1.0f) * 0.5f;
      float mult = 0.25f / biggestVal;

      Quaternion q;

      switch (biggestIndex)
      {
      case 0:
      {
	 q.w = biggestVal;
	 q.x = (m[1][2] - m[2][1]) * mult;
	 q.y = (m[2][0] - m[0][2]) * mult;
	 q.z = (m[0][1] - m[1][0]) * mult;
      }
      break;
      case 1:
      {
	 q.w = (m[1][2] - m[2][1]) * mult;
	 q.x = biggestVal;
	 q.y = (m[0][1] + m[1][0]) * mult;
	 q.z = (m[2][0] + m[0][2]) * mult;
      }
      break;
      case 2:
      {
	 q.w = (m[2][0] - m[0][2]) * mult;
	 q.x = (m[0][1] + m[1][0]) * mult;
	 q.y = biggestVal;
	 q.z = (m[1][2] + m[2][1]) * mult;
      }
      break;
      case 3:
      {
	 q.w = (m[0][1] - m[1][0]) * mult;
	 q.x = (m[2][0] + m[0][2]) * mult;
	 q.y = (m[1][2] + m[2][1]) * mult;
	 q.z = biggestVal;
      }
      break;
      default: // Should never actually get here. Just for sanities sake.
      {
	 //assert(false);
      }
      break;
      }

      return q;
   }

#endif // !#define CHALLENGE_QUATERNION_H
