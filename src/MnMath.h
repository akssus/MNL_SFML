#pragma once


namespace MNL
{
	namespace Math
	{
		//---------------------------------------------------------------------------------------
		// Vectors
		//---------------------------------------------------------------------------------------

		class MnVector3
		{
		public:
			MnVector3();
			MnVector3(float x, float y, float z);

			float Dot(const MnVector3& other);
			MnVector3 Cross(const MnVector3& other);

			//---------------
			//연산자
			//---------------
			void operator=(const MnVector3& other);
			MnVector3 operator+(const MnVector3& other);
			MnVector3 operator+(const MnVector3& other) const;
			MnVector3 operator-();
			MnVector3 operator-() const;
			MnVector3 operator-(const MnVector3& other);
			MnVector3 operator-(const MnVector3& other) const;
			MnVector3 operator*(float scalar);
			MnVector3 operator*(float scalar) const;
			friend MnVector3 operator*(float scalar, const MnVector3& vector);

			//---------------
			//멤버 변수
			//---------------
			float x, y, z;
		};

		class MnVector2
		{
		public:
			MnVector2();
			MnVector2(float x, float y);

			float Dot(const MnVector2& other);

			//---------------
			//연산자
			//---------------
			void operator=(const MnVector2& other);
			MnVector2 operator+(const MnVector2& other);
			MnVector2 operator+(const MnVector2& other) const;
			MnVector2 operator-();
			MnVector2 operator-() const;
			MnVector2 operator-(const MnVector2& other);
			MnVector2 operator-(const MnVector2& other) const;
			MnVector2 operator*(float scalar);
			MnVector2 operator*(float scalar) const;
			friend MnVector2 operator*(float scalar, const MnVector2& vector);

			//---------------
			//멤버 변수
			//---------------
			float x, y;
		};


		//---------------------------------------------------------------------------------------
		// Math Helpers
		//---------------------------------------------------------------------------------------

		const float PI = 3.14f;
		float DegreeToRadian(float degree);
		float RadianToDegree(float radian);

	}
}