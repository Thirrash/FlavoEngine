#pragma once

namespace Engine
{
	struct Vector3
	{
		/*** Constants ***/
	public:
		static const Vector3 Zero;

		/*** Ctors ***/
	public:
		Vector3(double X = 0.0, double Y = 0.0, double Z = 0.0);
		~Vector3();

		/*** Fields ***/
	public:
		double X, Y, Z;

		/*** Methods ***/
	public:
		double Magnitude();
		double MagnitudeSquared();
		Vector3& Normalize();

		Vector3 Cross(const Vector3& Vector) const;
		Vector3 Dot(const Vector3& Vector) const;

		Vector3 operator+(const Vector3& Vector) const;
		Vector3& operator+=(const Vector3& Vector);
		Vector3 operator-(const Vector3& Vector) const;
		Vector3& operator -=(const Vector3& Vector);

		Vector3 operator*(double Scalar) const;
		Vector3& operator*=(double Scalar);
		Vector3 operator/(double Scalar) const;
		Vector3& operator/=(double Scalar);

		bool operator==(const Vector3& Vector);
		bool operator!=(const Vector3& Vector);
	};
}


