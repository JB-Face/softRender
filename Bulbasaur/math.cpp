#include "math.h"



float Clamp(float x, float min, float max)
{
	if (x > max)
		return max;
	if (x < min)
		return min;
	return x;
}

Vector2::Vector2()
{
}

Vector2::Vector2(float _x, float _y) {
	x = _x;
	y = _y;
}

Vector2::Vector2(double _x, double _y) {
	x = _x;
	y = _y;
}

Vector2::Vector2(int _x, int _y) {
	x = _x;
	y = _y;
}

Vector2::~Vector2()
{
}

static inline float Dot(const Vector3& v1, const Vector3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}


static inline Vector3 Cross(const Vector3& v1, const Vector3& v2)
{
	return Vector3((v1.y * v2.z) - (v1.z * v2.y),
		(v1.z * v2.x) - (v1.x * v2.z),
		(v1.x * v2.y) - (v1.y * v2.x));
}










Vector4& Vector4::operator/=(float a)
{
	float oneOverA = 1.0f / a;
	x *= oneOverA; y *= oneOverA; z *= oneOverA;
	return *this;
}

Vector4 Vector4::operator/(float a) const
{
	float oneOverA = 1.0f / a;
	return Vector4(x * oneOverA, y * oneOverA, z * oneOverA);
}

Vector4& Vector4::operator+=(const Vector4& a)
{
	x += a.x; y += a.y; z += a.z;
	return *this;
}

Vector4 Vector4::operator+(const Vector4& a) const
{
	return Vector4(x + a.x, y + a.y, z + a.z);
}

bool Vector4::operator!=(const Vector4& a) const
{
	return x != a.x || y != a.y || z != a.z || w != a.w;
}


bool Vector4::operator==(const Vector4& a) const
{
	return x == a.x && y == a.y && z == a.z && w == a.w;
}

void Vector4::zero()
{
	x = y = z = 0.0f;
}

Vector4& Vector4::operator-=(const Vector4& a)
{
	x -= a.x; y -= a.y; z -= a.z;
	return *this;
}

Vector4 Vector4::operator-(const Vector4& a) const
{
	return Vector4(x - a.x, y - a.y, z - a.z);
}

Vector4 Vector4::operator-() const
{
	return Vector4(-x, -y, -z);
}

Vector4& Vector4::operator*=(float a)
{
	x *= a; y *= a; z *= a;
	return *this;
}

Vector4 Vector4::operator*(float a) const
{
	return Vector4(x * a, y * a, z * a);
}

void Vector4::normalize()
{
	float length = Magnitude(*this);
	if (length != 0.0f) {
		float inv = 1.0f / length;
		x *= inv;
		y *= inv;
		z *= inv;
	}
}

float Vector4::operator*(const Vector4& a) const
{
	return x * a.x + y * a.y + z * a.z;
}



//
// Non-Member Functions
//
Vector4 operator*(float k, const Vector4& v)
{
	return Vector4(k * v.x, k * v.y, k * v.z);
}

Matrix4x4::Matrix4x4() {

}

Matrix4x4::Matrix4x4(float f)
{
	m[0] = f; m[1] = f; m[2] = f; m[3] = f;
	m[4] = f; m[5] = f; m[6] = f; m[7] = f;
	m[8] = f; m[9] = f; m[10] = f; m[11] = f;
	m[12] = f; m[13] = f; m[14] = f; m[15] = f;
}

Matrix4x4::Matrix4x4(float f01, float f02, float f03, float f04, float f11, float f12, float f13, float f14, float f21, float f22, float f23, float f24, float f31, float f32, float f33, float f34)
{
	m[0] = f01; m[1] = f02; m[2] = f03; m[3] = f04;
	m[4] = f11; m[5] = f12; m[6] = f13; m[7] = f14;
	m[8] = f21; m[9] = f22; m[10] = f23; m[11] = f24;
	m[12] = f31; m[13] = f32; m[14] = f33; m[15] = f34;
}

float Matrix4x4::operator[](int index) const
{
	return m[index];
}

Matrix4x4& Matrix4x4::transpose()
{
	std::swap(m[1], m[4]);
	std::swap(m[2], m[8]);
	std::swap(m[3], m[12]);
	std::swap(m[6], m[9]);
	std::swap(m[7], m[13]);
	std::swap(m[11], m[14]);

	return *this;
}

inline Matrix4x4 Matrix4x4::operator*(const Matrix4x4& n) const
{
	return Matrix4x4(m[0] * n[0] + m[4] * n[1] + m[8] * n[2] + m[12] * n[3], m[1] * n[0] + m[5] * n[1] + m[9] * n[2] + m[13] * n[3], m[2] * n[0] + m[6] * n[1] + m[10] * n[2] + m[14] * n[3], m[3] * n[0] + m[7] * n[1] + m[11] * n[2] + m[15] * n[3],
		m[0] * n[4] + m[4] * n[5] + m[8] * n[6] + m[12] * n[7], m[1] * n[4] + m[5] * n[5] + m[9] * n[6] + m[13] * n[7], m[2] * n[4] + m[6] * n[5] + m[10] * n[6] + m[14] * n[7], m[3] * n[4] + m[7] * n[5] + m[11] * n[6] + m[15] * n[7],
		m[0] * n[8] + m[4] * n[9] + m[8] * n[10] + m[12] * n[11], m[1] * n[8] + m[5] * n[9] + m[9] * n[10] + m[13] * n[11], m[2] * n[8] + m[6] * n[9] + m[10] * n[10] + m[14] * n[11], m[3] * n[8] + m[7] * n[9] + m[11] * n[10] + m[15] * n[11],
		m[0] * n[12] + m[4] * n[13] + m[8] * n[14] + m[12] * n[15], m[1] * n[12] + m[5] * n[13] + m[9] * n[14] + m[13] * n[15], m[2] * n[12] + m[6] * n[13] + m[10] * n[14] + m[14] * n[15], m[3] * n[12] + m[7] * n[13] + m[11] * n[14] + m[15] * n[15]);
}

void Matrix4x4::debug()
{
	for (int i = 0; i < 15; i++)
	{
		std::cout << m[i];
	}
}

Matrix4x4::~Matrix4x4()
{
}


#include "Quaternion.h"




Quaternion::Quaternion()
{
	Quaternion(0, 0, 0, 1);
}

Quaternion::Quaternion(float _x, float _y, float _z, float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
	Quaternion::setEulerAngle(x, y, z, w);
}

Quaternion::Quaternion(float _yaw, float _pitch, float _roll)
{
	yaw = _yaw;
	pitch = _pitch;
	roll = _roll;
	Quaternion::setQuaternion(yaw, pitch, roll);
}



Quaternion::~Quaternion()
{
}

Matrix4x4 Quaternion::GetRotMatrix()
{
	const float n = 1.0f / sqrt(x * x + y * y + z * z + w * w);
	x *= n;
	y *= n;
	z *= n;
	w *= n;

	return Matrix4x4(
		1.0f - 2.0f * y * y - 2.0f * z * z, 2.0f * x * y - 2.0f * z * w, 2.0f * x * z + 2.0f * y * w, 0.0f,
		2.0f * x * y + 2.0f * z * w, 1.0f - 2.0f * x * x - 2.0f * z * z, 2.0f * y * z - 2.0f * x * w, 0.0f,
		2.0f * x * z - 2.0f * y * w, 2.0f * y * z + 2.0f * x * w, 1.0f - 2.0f * x * x - 2.0f * y * y, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	).transpose();
}

void Quaternion::debug()
{
	std::cout << x << "," << y << "," << z << "," << w << std::endl;
	std::cout << yaw << "," << pitch << "," << roll << std::endl;
}

void Quaternion::setQuaternion(float yaw, float pitch, float rolll) {
	float  angle;
	float  sinRoll, sinPitch, sinYaw, cosRoll, cosPitch, cosYaw;

	angle = yaw * 0.5f;
	sinYaw = sin(angle);
	cosYaw = cos(angle);

	angle = pitch * 0.5f;
	sinPitch = sin(angle);
	cosPitch = cos(angle);

	angle = roll * 0.5f;
	sinRoll = sin(angle);
	cosRoll = cos(angle);

	float _y = cosRoll * sinPitch * cosYaw + sinRoll * cosPitch * sinYaw;
	float _x = cosRoll * cosPitch * sinYaw - sinRoll * sinPitch * cosYaw;
	float _z = sinRoll * cosPitch * cosYaw - cosRoll * sinPitch * sinYaw;
	float _w = cosRoll * cosPitch * cosYaw + sinRoll * sinPitch * sinYaw;

	float mag = _x * _x + _y * _y + _z * _z + _w * _w;
	x = _x / mag;
	y = _y / mag;
	z = _z / mag;
	w = _w / mag;
}


void Quaternion::setEulerAngle(float x, float y, float z, float w) {
	yaw = atan2(2 * (w * x + z * y), 1 - 2 * (x * x + y * y));
	pitch = asin(Clamp(2 * (w * y - x * z), -1.0f, 1.0f));
	roll = atan2(2 * (w * z + x * y), 1 - 2 * (z * z + y * y));

	yaw *= Rad2Deg;
	pitch *= Rad2Deg;
	roll *= Rad2Deg;


}

float Quaternion::Dot(const Quaternion& lhs, Quaternion& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}

Quaternion Quaternion::Lerp(const Quaternion& lhs, Quaternion& rhs, float f)
{
	return Quaternion((1 - f) * lhs.x + f * rhs.x,
		(1 - f) * lhs.y + f * rhs.y,
		(1 - f) * lhs.z + f * rhs.z,
		(1 - f) * lhs.w + f * rhs.w);
}

Quaternion Quaternion::slerp(const Quaternion& lhs, Quaternion& rhs, float f)
{
	return Quaternion();
}

//Matrix4x4 Quaternion::GetRotMatrix() const
//{
//	return Matrix4x4(10);
//}





Quaternion Quaternion::Inverse() const
{
	return Quaternion(-x, -y, -z, -w);
}


//Matrix4x4 Quaternion::GetRotMatrix() {
//	const float n = 1.0f / sqrt(x * x + y * y + z * z + w * w);
//	x *= n;
//	y *= n;
//	z *= n;
//	w *= n;
//
//	return Matrix4x4(
//		1.0f - 2.0f * y * y - 2.0f * z * z, 2.0f * x * y - 2.0f * z * w, 2.0f * x * z + 2.0f * y * w, 0.0f,
//		2.0f * x * y + 2.0f * z * w, 1.0f - 2.0f * x * x - 2.0f * z * z, 2.0f * y * z - 2.0f * x * w, 0.0f,
//		2.0f * x * z - 2.0f * y * w, 2.0f * y * z + 2.0f * x * w, 1.0f - 2.0f * x * x - 2.0f * y * y, 0.0f,
//		0.0f, 0.0f, 0.0f, 1.0f
//	).transpose();
//}

Vector3::Vector3()
{
	x = y = z = 1;
}

Vector3::Vector3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

Vector3::~Vector3()
{
}

Vector3 Vector3::one(1, 1, 1);

Vector3 operator*(double lhs, const Vector3& rhs)
{
	return Vector3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
}
