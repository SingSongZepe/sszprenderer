#ifndef __GEOMETRY_H_
#define __GEOMETRY_H_

#include <cmath>
#include <iostream> 
#include <vector>

template <class t>
struct Vec2
{
	union {
		struct { t u, v; };
		struct { t x, y; };
		t raw[2];
	};	

	Vec2() : u(0), v(0) {}
	Vec2(t _u, t _v) : u(_u), v(_v) {}

	Vec2 operator+(const Vec2& v) const { return Vec2(u + v.u, v + v.v); }
	Vec2 operator-(const Vec2& v) const { return Vec2(u - v.u, v - v.v); }
	Vec2 operator-() const { return Vec2(-x, -y); };
	Vec2 operator*(float s) const { return Vec2(u * s, v * s); }

	friend std::ostream& operator<<(std::ostream& s, Vec2& v) {
		s << "(" << v.x << ", " << v.y << ")\n";
		return s;
	}
};

template <typename t>
struct Vec4;

template <typename t>
struct Vec3
{
	union {
		struct { t u, v, w; };
		struct { t x, y, z; };
		t raw[3];
	};

	Vec3() : u(0), v(0), w(0) {}
	Vec3(t _u, t _v, t _w) : u(_u), v(_v), w(_w) {}

	Vec3 operator+(const Vec3& v) const { return Vec3(u + v.u, v + v.v, w + v.w); }
	Vec3 operator-(const Vec3& v) const { return Vec3(u - v.u, v - v.v, w - v.w); }
	Vec3 operator-() const { return Vec3(-x, -y, -z); };
	Vec3 operator*(float s) const { return Vec3(u * s, v * s, w * s); };

	Vec3 normalized()
	{
		float norm = std::sqrt(this->dot_product(*this));
		if (norm == 0) return Vec3();
		return Vec3(x / norm, y / norm, z / norm);
	}

	friend std::ostream& operator<<(std::ostream& s, Vec3& v) 
	{
		s << "(" << v.x << ", " << v.y << ", " << v.z << ")\n";
		return s;
	}
	
	Vec3 cross_product(const Vec3& v2) 
	{
		return Vec3(y * v2.z - z * v2.y, z * v2.x - x * v2.z, x * v2.y - y * v2.x);
	}
	float dot_product(const Vec3& v2)
	{
		return x * v2.x + y * v2.y + z * v2.z;
	}

	Vec4<t> to_homogeneous_point()
	{
		return Vec4(x, y, z, t{ 1. });
	}
	Vec4<t> to_homogeneous_vector()
	{
		return Vec4(x, y, z, t{ 0. });
	}

};

// the w_ is always be the fourth term of a homogeneous coordinate of a point / vector
template <typename t>
struct Vec4
{
	union {
		struct { t u, v, w, w_; };
		struct { t x, y, z, w_; };
		t raw[4];
	};

	Vec4() : u(0), v(0), w(0), w_(0) {}
	Vec4(t _u, t _v, t _w, t _w_) : u(_u), v(_v), w(_w), w_(_w_) {}

	Vec4 operator+(const Vec4& v) const { return Vec4(u + v.u, v + v.v, w + v.w, w_ + v.w_); }
	Vec4 operator-(const Vec4& v) const { return Vec4(u - v.u, v - v.v, w - v.w, w_ - v.w_); }
	Vec4 operator*(float s) const { return Vec4(u * s, v * s, w * s, w_ * s); }

	friend std::ostream& operator<<(std::ostream& s, Vec4& v) {
		s << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w_ << ")\n";
		return s;
	}

	Vec3<t> homogenized()
	{
		if (w_ == 0)
		{
			return Vec3{ u, v, w };
		}
		else
		{
			return Vec3{ u / w_, v / w_, w / w_ };
		}
	}
};

template <typename t, int nr, int nc>
struct Mat
{

	typedef Mat<float, 4, 4> Mat4f;

	std::vector<std::vector<t>> matrix;

	Mat() : matrix(nr, std::vector<t>(nc)) {}

	template <typename u, int n>
	static Mat<t, n, n> zeros()
	{
		Mat<t, n, n> mat;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				mat.matrix[i][j] = 0.;
			}
		}
		return mat;
	}

	template <typename u, int n>
	static Mat<t, n, n> identity()
	{
		Mat<t, n, n> mat;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (i == j)
				{
					mat.matrix[i][j] = t{ 1. };
				}
				else
				{
					mat.matrix[i][j] = t{ 0. };
				}
			}
		}
		return mat;
	}

	friend std::ostream& operator<<(std::ostream& s, const Mat<t, nr, nc>& mat)
	{
		s << "[";
		for (int i = 0; i < nr; i++)
		{
			s << "[";
			for (int j = 0; j < nc; j++)
			{
				s << mat.matrix[i][j];
				if (j < nc - 1) s << ", ";
			}
			s << "]";
			if (i < nr - 1) s << ",\n";
		}
		s << "]";
		return s;
	}
	
	void set(int i, int j, t value)
	{
		matrix[i][j] = value;
	}

	Vec4<t> operator*(const Vec4<t>& vec4)
	{
		Vec4<t> v = Vec4<t>{};
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				v.raw[i] += matrix[i][j] * vec4.raw[j];
			}
		}
		return v;
	}

	template <typename u, int nr2, int nc2>
	Mat<t, nr, nc2> operator*(const Mat<u, nr2, nc2>& mat2)
	{
		if (nc != nr2)
		{
			throw std::runtime_error("matrix dimensions do not match for multiplication");
		}

		Mat<t, nr, nc2> res;

		for (int i = 0; i < nr; i++)
		{
			for (int j = 0; j < nc2; j++)
			{
				res.matrix[i][j] = t{};
				for (int k = 0; k < nc; k++)
				{
					res.matrix[i][j] += matrix[i][k] * mat2.matrix[k][j];
				}
			}
		}

		return res;
	}
};

typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;
typedef Vec3<float> Vec3f;
typedef Vec3<int> Vec3i;
typedef Vec4<float> Vec4f;
typedef Vec4<int> Vec4i;

typedef Mat<float, 4, 4> Mat4f;

#endif //__GEOMETRY_H__