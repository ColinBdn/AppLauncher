#pragma once

struct Vec3
{
	float x, y, z;

	void operator=(const Vec3& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}

	bool operator==(const Vec3& other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}

	void operator+=(const Vec3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
	}

	Vec3 operator+(const Vec3& other) const
	{
		return { x + other.x, y + other.y, z + other.z };
	}

	void operator-=(const Vec3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
	}

	Vec3 operator-(const Vec3& other) const
	{
		return { x - other.x, y - other.y, z - other.z };
	}

	void operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
	}

	Vec3 operator*(float scalar) const
	{
		return { x * scalar, y * scalar, z * scalar };
	}

	void operator/=(float scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
	}

	Vec3 operator/(float scalar) const
	{
		return { x / scalar, y / scalar, z / scalar };
	}
};

struct Vec2
{
	float x, y;

	void operator=(const Vec2& other)
	{
		x = other.x;
		y = other.y;
	}

	bool operator==(const Vec2& other) const
	{
		return x == other.x && y == other.y;
	}

	void operator+=(const Vec2& other)
	{
		x += other.x;
		y += other.y;
	}

	Vec2 operator+(const Vec2& other) const
	{
		return { x + other.x, y + other.y };
	}

	void operator-=(const Vec2& other)
	{
		x -= other.x;
		y -= other.y;
	}

	Vec2 operator-(const Vec2& other) const
	{
		return { x - other.x, y - other.y };
	}


	void operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
	}

	Vec2 operator*(float scalar) const
	{
		return { x * scalar, y * scalar };
	}


	void operator/=(float scalar)
	{
		x /= scalar;
		y /= scalar;
	}

	Vec2 operator/(float scalar) const
	{
		return { x / scalar, y / scalar };
	}
};
