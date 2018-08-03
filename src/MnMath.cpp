#include "MnMath.h"

using namespace MNL::Math;


//-----------------------------------------------------------------------------------------------------
// MnVector3
//-----------------------------------------------------------------------------------------------------

MnVector3::MnVector3() : x(0.0f), y(0.0f), z(0.0f)
{
}

MnVector3::MnVector3(float x, float y, float z) : x(0.0f), y(0.0f), z(0.0f)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float MnVector3::Dot(const MnVector3& other)
{
	return (x * other.x) + (y * other.y) + (z * other.z);
}

MnVector3 MnVector3::Cross(const MnVector3& other)
{
	float cx = (y*other.z) - (z*other.y);
	float cy = (x*other.z) - (z*other.x);
	float cz = (x*other.y) - (y*other.x);
	return MnVector3(cx, -cy, cz);
}

void MnVector3::operator=(const MnVector3& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

MnVector3 MnVector3::operator+(const MnVector3& other)
{
	return MnVector3(x + other.x, y + other.y, z + other.z);
}

MnVector3 MnVector3::operator+(const MnVector3& other) const
{
	return MnVector3(x + other.x, y + other.y, z + other.z);
}

MnVector3 MnVector3::operator-()
{
	return MnVector3(-x, -y, -z);
}

MnVector3 MnVector3::operator-() const
{
	return MnVector3(-x, -y, -z);
}

MnVector3 MnVector3::operator-(const MnVector3& other) const
{
	return MnVector3(x - other.x, y - other.y, z - other.z);
}

MnVector3 MnVector3::operator-(const MnVector3& other)
{
	return MnVector3(x - other.x, y - other.y, z - other.z);
}

MnVector3 MnVector3::operator*(float scalar)
{
	return MnVector3(x*scalar, y*scalar, z*scalar);
}

MnVector3 MnVector3::operator*(float scalar) const
{
	return MnVector3(x*scalar, y*scalar, z*scalar);
}

MnVector3 MNL::Math::operator*(float scalar, const MnVector3& vector)
{
	return vector * scalar;
}

//-----------------------------------------------------------------------------------------------------
// MnVector2
//-----------------------------------------------------------------------------------------------------

MnVector2::MnVector2() : x(0.0f), y(0.0f)
{
}

MnVector2::MnVector2(float x, float y) : x(0.0f), y(0.0f)
{
	this->x = x;
	this->y = y;
}

float MnVector2::Dot(const MnVector2& other)
{
	return x * other.x + y * other.y;
}

void MnVector2::operator=(const MnVector2& other)
{
	this->x = other.x;
	this->y = other.y;
}

MnVector2 MnVector2::operator+(const MnVector2& other)
{
	return MnVector2(x + other.x, y + other.y);
}

MnVector2 MnVector2::operator+(const MnVector2& other) const
{
	return MnVector2(x + other.x, y + other.y);
}

MnVector2 MnVector2::operator-()
{
	return MnVector2(-x, -y);
}

MnVector2 MnVector2::operator-(const MnVector2& other)
{
	return MnVector2(x - other.x, y - other.y);
}

MnVector2 MnVector2::operator-(const MnVector2& other) const
{
	return MnVector2(x - other.x, y - other.y);
}

MnVector2 MnVector2::operator*(float scalar)
{
	return MnVector2(x*scalar, y*scalar);
}

MnVector2 MnVector2::operator*(float scalar) const
{
	return MnVector2(x*scalar, y*scalar);
}


MnVector2 MNL::Math::operator*(float scalar, const MnVector2& vector)
{
	return vector * scalar;
}


//---------------------------------------------------------------------------------------
// Math Helpers
//---------------------------------------------------------------------------------------

float MNL::Math::DegreeToRadian(float degree)
{
	return degree * PI / 180.0f;
}

float MNL::Math::RadianToDegree(float radian)
{
	return radian * 180.0f / PI;
}
