#include "Vector3.h"
#include <math.h>

const Engine::Vector3 Engine::Vector3::Zero(0.0, 0.0, 0.0);

Engine::Vector3::Vector3(double X, double Y, double Z) {
	this->X = X;
	this->Y = Y;
	this->Z = Z;
}

Engine::Vector3::~Vector3() {

}

double Engine::Vector3::Magnitude() {
	return sqrt(MagnitudeSquared());
}

double Engine::Vector3::MagnitudeSquared() {
	return X*X + Y*Y + Z*Z;
}

Engine::Vector3& Engine::Vector3::Normalize() {
	double mag = Magnitude();
	X /= mag;
	Y /= mag;
	Z /= mag;

	return *this;
}

Engine::Vector3 Engine::Vector3::Cross(const Vector3& Vector) const {
	return Vector3(
		Y * Vector.Z - Z * Vector.Y,
		Z * Vector.X - X * Vector.Z,
		X * Vector.Y - Y * Vector.X
	);
}

Engine::Vector3 Engine::Vector3::Dot(const Vector3& Vector) const {
	return Vector3(
		X * Vector.X, 
		Y * Vector.Y, 
		Z * Vector.Z
	);
}

Engine::Vector3 Engine::Vector3::operator+(const Vector3& Vector) const {
	return Vector3(X + Vector.X, Y + Vector.Y, Z + Vector.Z);
}

Engine::Vector3& Engine::Vector3::operator+=(const Vector3& Vector) {
	X += Vector.X;
	Y += Vector.Y;
	Z += Vector.Z;
	return *this;
}

Engine::Vector3 Engine::Vector3::operator-(const Vector3& Vector) const {
	return Vector3(X - Vector.X, Y - Vector.Y, Z - Vector.Z);
}

Engine::Vector3& Engine::Vector3::operator-=(const Vector3& Vector) {
	X -= Vector.X;
	Y -= Vector.Y;
	Z -= Vector.Z;
	return *this;
}

Engine::Vector3 Engine::Vector3::operator*(double Scalar) const {
	return Vector3(X * Scalar, Y * Scalar, Z * Scalar);
}

Engine::Vector3& Engine::Vector3::operator*=(double Scalar) {
	X *= Scalar;
	Y *= Scalar;
	Z *= Scalar;
	return *this;
}

Engine::Vector3 Engine::Vector3::operator/(double Scalar) const {
	return Vector3(X / Scalar, Y / Scalar, Z / Scalar);
}

Engine::Vector3& Engine::Vector3::operator/=(double Scalar) {
	X /= Scalar;
	Y /= Scalar;
	Z /= Scalar;
	return *this;
}

bool Engine::Vector3::operator==(const Vector3& Vector) {
	return (X != Vector.X) ? false : (Y != Vector.Y) ? false : (Z != Vector.Z) ? false : true;
}

bool Engine::Vector3::operator!=(const Vector3& Vector) {
	return (X == Vector.X) ? false : (Y == Vector.Y) ? false : (Z == Vector.Z) ? false : true;
}
