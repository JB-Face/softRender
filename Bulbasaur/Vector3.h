
class Vector3
{
public:
	float x;
	float y;
	float z;
	static Vector3 one;
	Vector3();
	Vector3(float x, float y, float z);
	Vector3(float x);
	~Vector3();


	//

	friend Vector3 operator*(double lhs, const Vector3& rhs);
	
};
