#pragma once

#include<SDL.h>
#include<string>

class Vector2D {
public:
	// 2D vector constructor.
	Vector2D(float x = 0.0f, float y = 0.0f);

	// 2D vector addition operation.
	Vector2D operator+(Vector2D v2) const {
		return Vector2D(X + v2.X, Y + v2.Y);
	}

	// 2D vector subtraction operation.
	Vector2D operator-(Vector2D v2) const {
		return Vector2D(X - v2.X, Y - v2.Y);
	}

	// 2D vector multiply operation by a scalar.
	Vector2D operator*(const float scalar) const {
		return Vector2D(X * scalar, Y * scalar);
	}

	// 2D vector cross product operation
	// If v2 is on the left hand side of v1, the cross product is negative;
	// If v2 is on the right hand side of v1, the cross product is positive;
	// If v2 is parallel to v1, the cross product is 0;
	// Useful when calculating sin.
	float Cross(Vector2D v2) const {
		return (X * v2.Y - Y * v2.X);
	}

	// 2D vector dot product operation
	// If v2 is diagonal to v1, the dot product is 0.
	// Useful when calculating cos.
	float Dot(Vector2D v2) const {
		return (X * v2.X + Y * v2.Y);
	}
	
	void LogVector(std::string message);

	// The x and y values on the cordinator
	float X, Y;
};