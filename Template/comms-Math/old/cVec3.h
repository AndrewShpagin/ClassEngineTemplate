#pragma once

template<class Type, int Dim>
struct cVec;
class dVec3;

//*****************************************************************************
// cVec3
//*****************************************************************************
class COMMS_ALIASING cVec3 {
public:
	float x;
	float y;
	float z;

	cVec3();
	explicit cVec3(const float S);
	cVec3(const float X, const float Y, const float Z);
	cVec3(const cVec2 &XY, const float Z);
	cVec3(const dVec3& v);

	void Copy(const float *Src);
	void SetZero();
	void SetOne();
	void Set(const float S);
	void Set(const float X, const float Y, const float Z);
	void Set(const cVec2 &XY, const float Z);

	float & operator [] (const int Index);
	float operator [] (const int Index) const;

	const cVec3 operator - () const;

	void operator += (const cVec3 &);
	void operator -= (const cVec3 &);
	void operator *= (const cVec3 &);
	void operator *= (const float);
	void operator /= (const cVec3 &);
	void operator /= (const float);
	
	void TransformCoordinate(const cMat4 &);
	void TransformNormal(const cMat4 &);
	void TransformNormalTransposed(const cMat4 &);

	void Transform(const cMat3 &);
	void operator *= (const cMat3 &);

	void Rotate(const cQuat &);
	void operator *= (const cQuat &);
	
	void Rotate(const cRotation &);
	void operator *= (const cRotation &);
	
	const cVec3 & operator = ( const cVec4 &);
	inline float distance(const cVec3 &u) const {
		float dx = u.x - x;
		float dy = u.y - y;
		float dz = u.z - z;
		return cMath::Sqrt(dx * dx + dy * dy + dz * dz);
	}
	inline float distanceSq(const cVec3 &u) const {
		float dx = u.x - x;
		float dy = u.y - y;
		float dz = u.z - z;
		return dx * dx + dy * dy + dz * dz;
	}
	float dot(const cVec3 &u) const {
		return u.x * x + u.y * y + u.z * z;
	}
	void cross(const cVec3 &u, const cVec3 &v) {
		*this=cVec3(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
	}
	const cVec3 operator + (const cVec3 &) const;
	const cVec3 operator - (const cVec3 &) const;
	const cVec3 operator * (const cVec3 &) const;
	const cVec3 operator * (const float) const;
	friend const cVec3 operator * (const float, const cVec3 &);
	const cVec3 operator / (const cVec3 &) const;
	const cVec3 operator / (const float) const;

	static const cVec3 Transform(const cVec3 &, const cMat3 &);
	const cVec3 operator * (const cMat3 &) const;

	static const cVec4 Transform(const cVec3 &, const cMat4 &); // (x, y, z, 1)
	static const cVec3 TransformCoordinate(const cVec3 &, const cMat4 &);
	static const cVec3 TransformNormal(const cVec3 &, const cMat4 &);
	static void TransformCoordinate(cList<cVec3> *, const cMat4 &);
	static void TransformNormal(cList<cVec3> *, const cMat4 &);
	static void TransformCoordinate(cVec3 *Array, const int Count, const cMat4 &T);
	static void TransformNormal(cVec3 *Array, const int Count, const cMat4 &T);
	
	static const cVec3 Rotate(const cVec3 &, const cQuat &);
	const cVec3 operator * (const cQuat &) const;
	
	static const cVec3 Rotate(const cVec3 &, const cRotation &);
	const cVec3 operator * (const cRotation &) const;

	bool operator == (const cVec3 &) const;
	bool operator != (const cVec3 &) const;
	static bool Equals(const cVec3 &, const cVec3 &, const float Eps = cMath::Epsilon);

	float Length() const;
	float Length2() const;
	float LengthSq() const;
	float LengthM() const; //Manhattan distance
	float Normalize();
	float Normalize2();
	float NormalizeSafe(const cVec3 &Fallback = cVec3::AxisZ);
	bool FixDegenerateNormal();
	bool FixDenormals();
	bool IsValid() const;
	bool IsNormalized(float Eps = cMath::Epsilon) const;
	bool IsZero(float Eps = cMath::Epsilon) const;
	void Round();

	static const cVec3 Abs(const cVec3 &);
	static float Angle(const cVec3 &, const cVec3 &);
	static float AreaSigned(const cVec3 &t0, const cVec3 &t1, const cVec3 &t2);
	static const cVec3 BaryCentric(const cVec3 &t0, const cVec3 &t1, const cVec3 &t2, const float f, const float g);
	static const cVec3 Clamp(const cVec3 &, const cVec3 &, const cVec3 &);
	static const cVec3 Cross(const cVec3 &, const cVec3 &);
	void SetCross(const cVec3 &, const cVec3 &);
	static float Distance(const cVec3 &, const cVec3 &);
	static float Distance2(const cVec3 &, const cVec3 &);
	float Distance(const cVec3 &) const;
	float Distance2(const cVec3 &) const;
	static float DistanceSq(const cVec3 &, const cVec3 &);
	static float Dot(const cVec3 &, const cVec3 &);
	float Dot(const cVec3 &) const;
	static float Length(const cVec3 &);
	static float LengthSq(const cVec3 &);
	static const cVec3 Lerp(const cVec3 &, const cVec3 &, const float);
	static const cVec3 Lerp05(const cVec3 &, const cVec3 &);
	static const cVec3 Max(const cVec3 &, const cVec3 &);
	static const cVec3 Min(const cVec3 &, const cVec3 &);
	static const cVec3 Normalize(const cVec3 &);
	static const cVec3 Normalize2(const cVec3 &);
	static const cVec3 Reflect(const cVec3 &RayDir, const cVec3 &Normal);
	// @param Eta  Ratio of indices of refraction at the surface interface.
	static const cVec3 Refract(const cVec3 &RayDir, const cVec3 &Normal, const float Eta);
	static const cVec3 Slerp(const cVec3 &n0, const cVec3 &n1, const float s);
	static const cVec3 Truncate(const cVec3 &u, const float MaxLen);
	void Truncate(const float MaxLen);
	static const cVec3 RandRange1();
	static const cVec3 RandNormal();
	static const cVec3 Rand(const cVec3 &Lo, const cVec3 &Hi);
	static const cVec3 Project(const cVec3 &v1, const cVec3 &v2);
	static const cVec3 Perpendicular(const cVec3 &v1);
	float TriProjectionSolidAngle(const cVec3 &a, const cVec3 &b, const cVec3 &c) const;
	
	static const cVec3 Zero;
	static const cVec3 One;
	static const cVec3 Infinity;
	static const cVec3 AxisX;
	static const cVec3 AxisY;
	static const cVec3 AxisZ;
	static const cVec3 AxisNegX;
	static const cVec3 AxisNegY;
	static const cVec3 AxisNegZ;
	
	int GetDimension() const;

	const float * ToFloatPtr() const;
	float * ToFloatPtr();

	const cVec2 & ToVec2() const;
	cVec2 & ToVec2();

	template<class Type>
	operator cVec<Type, 3> () const;
	
	const cStr ToString(const int Prec = 2) const;

	const cAngles ToAngles() const;
	
	void ToPolarXZ(float *Radius, float *Angle) const;
	static const cVec3 FromPolarXZ(const float Radius, const float Angle);
	float ToBaryCentric(const cVec3 &t0, const cVec3 &t1, const cVec3 &t2, float &f, float &g) const;

	const cVec3 ToNormal() const;
	void ToPerps(cVec3 &X, cVec3 &Y) const;
	const cVec3 ToPerp() const;

	static bool RayTri(const cVec3 &RayOrig, const cVec3 &RayDir, const cVec3 &t0, const cVec3 &t1, const cVec3 &t2, float &u, float &v, float &t, const bool BackFaceCull = false);
	static bool PointInTriangle(const cVec3 &p, const cVec3 &t0, const cVec3 &t1, const cVec3 &t2);
};

// cVec3.ctor : ()
inline cVec3::cVec3() {
}

// cVec3.ctor : (const float)
inline cVec3::cVec3(const float S)
: x(S), y(S), z(S) {}

// cVec3.ctor : (const float, const float, const float)
inline cVec3::cVec3(const float X, const float Y, const float Z)
: x(X), y(Y), z(Z) {}

// cVec3.ctor : (const cVec2 &, const float)
inline cVec3::cVec3(const cVec2 &XY, const float Z)
: x(XY.x), y(XY.y), z(Z) {}

// cVec3::SetZero
inline void cVec3::SetZero() {
	x = y = z = 0.0f;
}

// cVec3::SetOne
inline void cVec3::SetOne() {
	x = y = z = 1.0f;
}

// cVec3::Set : void (const float)
inline void cVec3::Set(const float S) {
	x = y = z = S;
}

// cVec3::Set : void (const float, const float, const float)
inline void cVec3::Set(const float X, const float Y, const float Z) {
	x = X;
	y = Y;
	z = Z;
}

// cVec3::Set : void (const cVec2 &, const float)
inline void cVec3::Set(const cVec2 &XY, const float Z) {
	x = XY.x;
	y = XY.y;
	z = Z;
}

// cVec3::Copy
inline void cVec3::Copy(const float *Src) {
	cAssert(Src != NULL);
	x = Src[0];
	y = Src[1];
	z = Src[2];
}

// cVec3::operator [] : float & (const int)
inline float & cVec3::operator [] (const int Index) {
	cAssert(Index >= 0 && Index < 3);
	return (&x)[Index];
}

// cVec3::operator [] : float(const int) const
inline float cVec3::operator [] (const int Index) const {
	cAssert(Index >= 0 && Index < 3);
	return (&x)[Index];
}

// cVec3::operator - : const cVec3() const
inline const cVec3 cVec3::operator - () const {
	return cVec3(-x, -y, -z);
}

// cVec3::operator += : void (const cVec3 &)
inline void cVec3::operator += (const cVec3 &u) {
	x += u.x;
	y += u.y;
	z += u.z;
}

// cVec3::operator -= : void (const cVec3 &)
inline void cVec3::operator -= (const cVec3 &u) {
	x -= u.x;
	y -= u.y;
	z -= u.z;
}

// cVec3::operator *= : void (const cVec3 &)
inline void cVec3::operator *= (const cVec3 &u) {
	x *= u.x;
	y *= u.y;
	z *= u.z;
}

// cVec3::operator *= : void (const float)
inline void cVec3::operator *= (const float s) {
	x *= s;
	y *= s;
	z *= s;
}

// cVec3::operator /= : void (const cVec3 &)
inline void cVec3::operator /= (const cVec3 &u) {
	x /= u.x;
	y /= u.y;
	z /= u.z;
}

// cVec3::operator /= : void (const float)
inline void cVec3::operator /= (const float s) {
	const float is = 1.0f / s;
	x *= is;
	y *= is;
	z *= is;
}

// cVec3::operator + : const cVec3(const cVec3 &) const
inline const cVec3 cVec3::operator + (const cVec3 &u) const {
	return cVec3(x + u.x, y + u.y, z + u.z);
}

// cVec3::operator - : const cVec3(const cVec3 &) const
inline const cVec3 cVec3::operator - (const cVec3 &u) const {
	return cVec3(x - u.x, y - u.y, z - u.z);
}

// cVec3::operator * : const cVec3(const cVec3 &) const
inline const cVec3 cVec3::operator * (const cVec3 &u) const {
	return cVec3(x * u.x, y * u.y, z * u.z);
}

// cVec3::operator * : const cVec3(const float) const
inline const cVec3 cVec3::operator * (const float s) const {
	return cVec3(x * s, y * s, z * s);
}

// cVec3::friend operator * : const cVec3(const float, const cVec3 &)
inline const cVec3 operator * (const float s, const cVec3 &u) {
	return cVec3(s * u.x, s * u.y, s * u.z);
}

// cVec3::operator / : const cVec3(const cVec3 &) const
inline const cVec3 cVec3::operator / (const cVec3 &u) const {
	return cVec3(x / u.x, y / u.y, z / u.z);
}

// cVec3::operator / : const cVec3(const float) const
inline const cVec3 cVec3::operator / (const float s) const {
	const float is = 1.0f / s;
	return cVec3(x * is, y * is, z * is);
}

// cVec3::friend operator / : const cVec3 (const float, const cVec3 &)
inline const cVec3 operator / (const float s, const cVec3 &u) {
	return cVec3(s / u.x, s / u.y, s / u.z);
}

// @todo stability  Verify and fixed operator==() for other class with float data.
// cVec3::operator == : bool(const cVec3 &) const
inline bool cVec3::operator == (const cVec3 &u) const {
	return cVec3::Equals( *this, u );
}

// cVec3::operator != : bool(const cVec3 &) const
inline bool cVec3::operator != (const cVec3 &u) const {
	return !cVec3::Equals( *this, u );
}

// cVec3::Equals : bool(const cVec3 &, const cVec3 &, const float)
inline bool cVec3::Equals(const cVec3 &u, const cVec3 &v, const float Eps) {
	if(cMath::Abs(u.x - v.x) > Eps) {
		return false;
	}
	if(cMath::Abs(u.y - v.y) > Eps) {
		return false;
	}
	if(cMath::Abs(u.z - v.z) > Eps) {
		return false;
	}
	return true;
}

// cVec3::Length : float() const
inline float cVec3::Length() const {
	return cMath::Sqrt(x * x + y * y + z * z);	
}

// cVec3::Length2
inline float cVec3::Length2() const {
	return cMath::FastSqrt(x * x + y * y + z * z);
}

// cVec3::LengthM
inline float cVec3::LengthM() const {	
	return cMath::Abs(x)+cMath::Abs(y)+cMath::Abs(z);	
}

// cVec3::LengthSq : float() const
inline float cVec3::LengthSq() const {
	return x * x + y * y + z * z;
}

// cVec3::Normalize : float()
inline float cVec3::Normalize() {
	const float l = Length();
	if(l > 0.0f) {
		const float il = 1.0f / l;
		x *= il;
		y *= il;
		z *= il;
	}
	return l;
}

// cVec3::Normalize2
inline float cVec3::Normalize2() {
	const float l = x * x + y * y + z * z;
	if(l > 0.0f) {
		const float il = cMath::FastInvSqrt(l);
		x *= il;
		y *= il;
		z *= il;
	}
	return l;
}

// cVec3::NormalizeSafe
inline float cVec3::NormalizeSafe(const cVec3 &Fallback) {
	const float l = Length();
	if(l > cMath::EpsilonSq) {
		const float il = 1.0f / l;
		x *= il;
		y *= il;
		z *= il;
		cAssert(IsNormalized());
		return l;
	}
	
	*this = Fallback;
	cAssert(IsNormalized());
	return 0.0f;
}

// cVec3::IsValid : bool () const
inline bool cVec3::IsValid() const {
	return cMath::IsValid(x) && cMath::IsValid(y) && cMath::IsValid(z);
}

// cVec3::IsNormalized : bool(const float) const
inline bool cVec3::IsNormalized(const float Eps) const {
	return cMath::IsOne(LengthSq(), Eps);
}

// cVec3::IsZero : bool(const float) const
inline bool cVec3::IsZero(const float Eps) const {
	if(!cMath::IsZero(x, Eps)) return false;
	if(!cMath::IsZero(y, Eps)) return false;
	if(!cMath::IsZero(z, Eps)) return false;
	return true;
}

// cVec3::Round : ()
inline void cVec3::Round() {
	x = cMath::Round(x);
	y = cMath::Round(y);
	z = cMath::Round(z);
}

// cVec3::Abs : const cVec3(const cVec3 &)
inline const cVec3 cVec3::Abs(const cVec3 &u) {
	return cVec3(cMath::Abs(u.x), cMath::Abs(u.y), cMath::Abs(u.z));
}

// cVec3::Angle : float(const cVec3 &, const cVec3 &)
inline float cVec3::Angle(const cVec3 &u, const cVec3 &v) {
	const float D = cVec3::Dot(u, v);
	float ll = u.Length() * v.Length();
	return cMath::Deg(cMath::ACos(D / ll));
}

// cVec3::AreaSigned
inline float cVec3::AreaSigned(const cVec3 &t0, const cVec3 &t1, const cVec3 &t2) {
	const cVec3 e1 = t1 - t0;
	const cVec3 e2 = t2 - t0;
	return Length(Cross(e1, e2)) * 0.5f;
}

// cVec3::BaryCentric
inline const cVec3 cVec3::BaryCentric(const cVec3 &t0, const cVec3 &t1, const cVec3 &t2, const float f, const float g) {
	const cVec3 e1 = t1 - t0;
	const cVec3 e2 = t2 - t0;
	return t0 + f * e1 + g * e2;
}

// cVec3::ToPolarXZ
inline void cVec3::ToPolarXZ(float *Radius, float *Angle) const {
	cVec2 t(x, -z);
	t.ToPolar(Radius, Angle);
}

// cVec3::FromPolarXZ
inline const cVec3 cVec3::FromPolarXZ(const float Radius, const float Angle) {
	cVec2 t = cVec2::FromPolar(Radius, Angle);
	return cVec3(t.x, 0.0f, -t.y);
}

// cVec3::ToBaryCentric
inline float cVec3::ToBaryCentric(const cVec3 &t0, const cVec3 &t1, const cVec3 &t2, float &f, float &g) const {
	const float A = AreaSigned(t0, t1, t2);
	if(A != 0) {
		const float iA = 1.0f / A;
		f = AreaSigned(t0, *this, t2) * iA;
		g = AreaSigned(t0, t1, *this) * iA;
	} else {
		f = g = 0.0f;
	}
	return A;
}

// cVec3::Clamp
inline const cVec3 cVec3::Clamp(const cVec3 &u, const cVec3 &bbMin, const cVec3 &bbMax) {
	cVec3 r;
	r.x = u.x < bbMin.x ? bbMin.x : (u.x > bbMax.x ? bbMax.x : u.x);
	r.y = u.y < bbMin.y ? bbMin.y : (u.y > bbMax.y ? bbMax.y : u.y);
	r.z = u.z < bbMin.z ? bbMin.z : (u.z > bbMax.z ? bbMax.z : u.z);
	return r;
}

// cVec3::Cross
inline const cVec3 cVec3::Cross(const cVec3 &u, const cVec3 &v) {
	return cVec3(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
}
// cVec3::SetCross
inline void cVec3::SetCross(const cVec3 &u, const cVec3 &v) {
	*this = cVec3(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
}

// cVec3::DistanceSq : float(const cVec3 &, const cVec3 &)
inline float cVec3::DistanceSq(const cVec3 &u, const cVec3 &v) {
	float dx = u.x - v.x;
	float dy = u.y - v.y;
	float dz = u.z - v.z;
	return dx * dx + dy * dy + dz * dz;
}

// cVec3::Distance : float(const cVec3 &, const cVec3 &)
inline float cVec3::Distance(const cVec3 &u, const cVec3 &v) {
	float dx = u.x - v.x;
	float dy = u.y - v.y;
	float dz = u.z - v.z;
	return cMath::Sqrt(dx * dx + dy * dy + dz * dz);
}
inline float cVec3::Distance2(const cVec3 &u, const cVec3 &v) {
	float dx = u.x - v.x;
	float dy = u.y - v.y;
	float dz = u.z - v.z;
	return cMath::FastSqrt(dx * dx + dy * dy + dz * dz);
}


// cVec3::Distance : float(const cVec3 &)
inline float cVec3::Distance(const cVec3 &u) const {
	float dx = u.x - x;
	float dy = u.y - y;
	float dz = u.z - z;
	return cMath::Sqrt(dx * dx + dy * dy + dz * dz);
}
inline float cVec3::Distance2(const cVec3 &u) const {
	float dx = u.x - x;
	float dy = u.y - y;
	float dz = u.z - z;
	return cMath::FastSqrt(dx * dx + dy * dy + dz * dz);
}

// cVec3::Dot : float(const cVec3 &, const cVec3 &)
inline float cVec3::Dot(const cVec3 &u, const cVec3 &v) {
	return u.x * v.x + u.y * v.y + u.z * v.z;
}

// cVec3::Dot : float(const cVec3 &)
inline float cVec3::Dot(const cVec3 &u) const {
	return u.x * x + u.y * y + u.z * z;
}

// cVec3::Length : float(const cVec3 &)
inline float cVec3::Length(const cVec3 &u) {
	return cMath::Sqrt(u.x * u.x + u.y * u.y + u.z * u.z);
}

// cVec3::LengthSq : float(const cVec3 &)
inline float cVec3::LengthSq(const cVec3 &u) {
	return u.x * u.x + u.y * u.y + u.z * u.z;
}

// cVec3::Lerp
inline const cVec3 cVec3::Lerp(const cVec3 &u, const cVec3 &v, const float s) {
	cVec3 r;
	r.x = u.x + s * (v.x - u.x);
	r.y = u.y + s * (v.y - u.y);
	r.z = u.z + s * (v.z - u.z);
	return r;
}

// cVec3::Lerp05 : const cVec3(const cVec3 &, const cVec3 &)
inline const cVec3 cVec3::Lerp05(const cVec3 &u, const cVec3 &v) {
	cVec3 r;
	r.x = 0.5f * (u.x + v.x);
	r.y = 0.5f * (u.y + v.y);
	r.z = 0.5f * (u.z + v.z);
	return r;
}

// cVec3::Max : const cVec3(const cVec3 &, const cVec3 &)
inline const cVec3 cVec3::Max(const cVec3 &u, const cVec3 &v) {
	cVec3 r;
	r.x = u.x > v.x ? u.x : v.x;
	r.y = u.y > v.y ? u.y : v.y;
	r.z = u.z > v.z ? u.z : v.z;
	return r;
}

// cVec3::Min : const cVec3(const cVec3 &, const cVec3 &)
inline const cVec3 cVec3::Min(const cVec3 &u, const cVec3 &v) {
	cVec3 r;
	r.x = u.x < v.x ? u.x : v.x;
	r.y = u.y < v.y ? u.y : v.y;
	r.z = u.z < v.z ? u.z : v.z;
	return r;
}

// cVec3::Normalize
inline const cVec3 cVec3::Normalize(const cVec3 &u) {
	float l = cMath::Sqrt(u.x * u.x + u.y * u.y + u.z * u.z);
	if(l > 0.0f) {
		float il = 1.0f / l;
		return cVec3(u.x * il, u.y * il, u.z * il);
	}
	return u;
}
// cVec3::Normalize
inline const cVec3 cVec3::Normalize2(const cVec3 &u) {
	float l = u.x * u.x + u.y * u.y + u.z * u.z;
	if(l > 0.0f){
		float il = cMath::FastInvSqrt(l);
		return cVec3(u.x * il, u.y * il, u.z * il);
	}
	return u;
}

// cVec3::Reflect
inline const cVec3 cVec3::Reflect(const cVec3 &RayDir, const cVec3 &Normal) {
	return RayDir - 2.0f * Dot(RayDir, Normal) * Normal;
}

// cVec3::Refract
inline const cVec3 cVec3::Refract(const cVec3 &RayDir, const cVec3 &Normal, const float Eta) {
	float k = 1.0f - Eta * Eta * (1.0f - cMath::Square(Dot(Normal, RayDir)));
	if(k < 0.0f) return cVec3::Zero;
	return Eta * RayDir - (Eta * Dot(Normal, RayDir) + cMath::Sqrt(k)) * Normal;
}

// cVec3::Truncate : (const float)
inline void cVec3::Truncate(const float MaxLen) {
	if(MaxLen <= 0) {
		SetZero();
		return;
	}
	float l = Length();
	if(l > MaxLen) {
		float il = MaxLen / l;
		x *= il;
		y *= il;
		z *= il;
	}
}

// cVec3::Truncate : (const cVec3 &, ...)
inline const cVec3 cVec3::Truncate(const cVec3 &u, const float MaxLen) {
	if(MaxLen <= 0) {
		return cVec3::Zero;
	}
	float l = u.Length();
	if(l > MaxLen) {
		float il = MaxLen / l;
		return cVec3(u.x * il, u.y * il, u.z * il);
	}
	return u;
}

// cVec3::GetDimension : int() const
inline int cVec3::GetDimension() const {
	return 3;
}

// cVec3::ToFloatPtr : const float * () const
inline const float * cVec3::ToFloatPtr() const {
	return (const float *)&x;
}

// cVec3::ToFloatPtr : float * ()
inline float * cVec3::ToFloatPtr() {
	return (float *)&x;
}

// cVec3::ToVec2 : const cVec2 & () const
inline const cVec2 & cVec3::ToVec2() const {
	return *reinterpret_cast<const cVec2 *>(this);
}

// cVec3::ToVec2 : cVec2 & ()
inline cVec2 & cVec3::ToVec2() {
	return *reinterpret_cast<cVec2 *>(this);
}

// cVec3::operator cVec<Type, 3>
template<class Type>
cVec3::operator cVec<Type, 3> () const {
	return cVec<Type, 3>( (Type)x, (Type)y, (Type)z );
}

// cVec3::ToNormal : const cVec2 () const
inline const cVec3 cVec3::ToNormal() const {
	cVec3 u(*this);
	u.Normalize();
	return u;
}

// cVec3::Rand
inline const cVec3 cVec3::Rand(const cVec3 &Lo, const cVec3 &Hi) {
	return cVec3(cMath::Rand(Lo.x, Hi.x), cMath::Rand(Lo.y, Hi.y), cMath::Rand(Lo.z, Hi.z));
}

// cVec3::Project
inline const cVec3 cVec3::Project(const cVec3 &v1, const cVec3 &v2) {
	float mul;
	mul = cVec3::Dot(v1, v2) / cVec3::Dot(v2, v2);
	return cVec3(mul * v2.x, mul * v2.y, mul * v2.z);
}

inline float cVec3::TriProjectionSolidAngle(const cVec3 &v1, const cVec3 &v2, const cVec3 &v3) const {
	cVec3 u(*this);
	cVec3 a = v1 - u;
	cVec3 b = v2 - u;
	cVec3 c = v3 - u;
	float det = cMath::Abs(a.Dot(Cross(b,c)));
	
	float al = a.Length();
	float bl = b.Length(b);
	float cl = c.Length(c);
	
	float div = al*bl*cl + a.Dot(b)*cl + a.Dot(c)*bl + b.Dot(c)*al;
	float at = cMath::ATan(det, div);
	if(at < 0) {
		at += cMath::Pi; // If det>0 && div<0 atan2 returns < 0, so add pi.
	}
	float omega = 2.0f * at;
	return omega;
}

// cVec3::Perpendicular
inline const cVec3 cVec3::Perpendicular(const cVec3 &v1) {
	float X = cMath::Abs(v1.x);
	float Y = cMath::Abs(v1.y);
	float Z = cMath::Abs(v1.z);
	if(X>Y && X>Z) {
		return cVec3::Cross(v1,cVec3(1,0,0));
	} else if(Y>X && Y>Z) {
		return cVec3::Cross(v1,cVec3(0,1,0));
	} else {
		return cVec3::Cross(v1,cVec3(0,0,1));
	}
}
