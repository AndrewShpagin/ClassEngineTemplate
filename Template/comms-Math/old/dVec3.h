#pragma once

template<class Type, int Dim>
struct cVec;

//*****************************************************************************
// dVec3
//*****************************************************************************
class COMMS_ALIASING dVec3 {
public:
	double x;
	double y;
	double z;

	dVec3();
	explicit dVec3(const double S);
	dVec3(const double X, const double Y, const double Z);
	dVec3(const dVec2 &XY, const double Z);
	dVec3(const cVec3& v3);

	void Copy(const double *Src);
	void SetZero();
	void SetOne();
	void Set(const double S);
	void Set(const double X, const double Y, const double Z);
	void Set(const dVec2 &XY, const double Z);

	double & operator [] (const int Index);
	double operator [] (const int Index) const;

	const dVec3 operator - () const;

	void operator += (const dVec3 &);
	void operator -= (const dVec3 &);
	void operator *= (const dVec3 &);
	void operator *= (const double);
	void operator /= (const dVec3 &);
	void operator /= (const double);
	
	void TransformCoordinate(const dMat4 &);
	void TransformNormal(const dMat4 &);
	void TransformNormalTransposed(const dMat4 &);

	void Transform(const dMat3 &);
	void operator *= (const dMat3 &);

	void Rotate(const cQuat &);
	void operator *= (const cQuat &);
	
	void Rotate(const cRotation &);
	void operator *= (const cRotation &);
	
	const dVec3 & operator = ( const dVec4 &);
	inline double distance(const dVec3 &u) const {
		double dx = u.x - x;
		double dy = u.y - y;
		double dz = u.z - z;
		return cMath::Sqrt(dx * dx + dy * dy + dz * dz);
	}
	inline double distanceSq(const dVec3 &u) const {
		double dx = u.x - x;
		double dy = u.y - y;
		double dz = u.z - z;
		return dx * dx + dy * dy + dz * dz;
	}
	double dot(const dVec3 &u) const {
		return u.x * x + u.y * y + u.z * z;
	}
	void cross(const dVec3 &u, const dVec3 &v) {
		*this=dVec3(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
	}
	const dVec3 operator + (const dVec3 &) const;
	const dVec3 operator - (const dVec3 &) const;
	const dVec3 operator * (const dVec3 &) const;
	const dVec3 operator * (const double) const;
	friend const dVec3 operator * (const double, const dVec3 &);
	const dVec3 operator / (const dVec3 &) const;
	const dVec3 operator / (const double) const;

	static const dVec3 Transform(const dVec3 &, const dMat3 &);
	const dVec3 operator * (const dMat3 &) const;

	static const dVec4 Transform(const dVec3 &, const dMat4 &); // (x, y, z, 1)
	static const dVec3 TransformCoordinate(const dVec3 &, const dMat4 &);
	static const dVec3 TransformNormal(const dVec3 &, const dMat4 &);
	static void TransformCoordinate(cList<dVec3> *, const dMat4 &);
	static void TransformNormal(cList<dVec3> *, const dMat4 &);
	static void TransformCoordinate(dVec3 *Array, const int Count, const dMat4 &T);
	static void TransformNormal(dVec3 *Array, const int Count, const dMat4 &T);
	
	static const dVec3 Rotate(const dVec3 &, const cQuat &);
	const dVec3 operator * (const cQuat &) const;
	
	static const dVec3 Rotate(const dVec3 &, const cRotation &);
	const dVec3 operator * (const cRotation &) const;

	bool operator == (const dVec3 &) const;
	bool operator != (const dVec3 &) const;
	static bool Equals(const dVec3 &, const dVec3 &, const double Eps = cMath::Epsilon);

	double Length() const;
	double LengthSq() const;
	double LengthM() const; //Manhattan distance
	double Normalize();
	double NormalizeSafe(const dVec3 &Fallback = dVec3::AxisZ);
	bool FixDegenerateNormal();
	bool FixDenormals();
	bool IsValid() const;
	bool IsNormalized(double Eps = cMath::Epsilon) const;
	bool IsZero(double Eps = cMath::Epsilon) const;
	void Round();

	static const dVec3 Abs(const dVec3 &);
	static double Angle(const dVec3 &, const dVec3 &);
	static double AreaSigned(const dVec3 &t0, const dVec3 &t1, const dVec3 &t2);
	static const dVec3 BaryCentric(const dVec3 &t0, const dVec3 &t1, const dVec3 &t2, const double f, const double g);
	static const dVec3 Clamp(const dVec3 &, const dVec3 &, const dVec3 &);
	static const dVec3 Cross(const dVec3 &, const dVec3 &);
	void SetCross(const dVec3 &, const dVec3 &);
	static double Distance(const dVec3 &, const dVec3 &);
	double Distance(const dVec3 &) const;
	static double DistanceSq(const dVec3 &, const dVec3 &);
	static double Dot(const dVec3 &, const dVec3 &);
	double Dot(const dVec3 &) const;
	static double Length(const dVec3 &);
	static double LengthSq(const dVec3 &);
	static const dVec3 Lerp(const dVec3 &, const dVec3 &, const double);
	static const dVec3 Lerp05(const dVec3 &, const dVec3 &);
	static const dVec3 Max(const dVec3 &, const dVec3 &);
	static const dVec3 Min(const dVec3 &, const dVec3 &);
	static const dVec3 Normalize(const dVec3 &);
	static const dVec3 Reflect(const dVec3 &RayDir, const dVec3 &Normal);
	// @param Eta  Ratio of indices of refraction at the surface interface.
	static const dVec3 Refract(const dVec3 &RayDir, const dVec3 &Normal, const double Eta);
	static const dVec3 Slerp(const dVec3 &n0, const dVec3 &n1, const double s);
	static const dVec3 Truncate(const dVec3 &u, const double MaxLen);
	void Truncate(const double MaxLen);
	static const dVec3 RandRange1();
	static const dVec3 RandNormal();
	static const dVec3 Rand(const dVec3 &Lo, const dVec3 &Hi);
	static const dVec3 Project(const dVec3 &v1, const dVec3 &v2);
	static const dVec3 Perpendicular(const dVec3 &v1);
	double TriProjectionSolidAngle(const dVec3 &a, const dVec3 &b, const dVec3 &c) const;
	
	static const dVec3 Zero;
	static const dVec3 One;
	static const dVec3 Infinity;
	static const dVec3 AxisX;
	static const dVec3 AxisY;
	static const dVec3 AxisZ;
	static const dVec3 AxisNegX;
	static const dVec3 AxisNegY;
	static const dVec3 AxisNegZ;
	
	int GetDimension() const;

	const double * ToDoublePtr() const;
	double * ToDoublePtr();

	const dVec2 & ToVec2() const;
	dVec2 & ToVec2();

	template<class Type>
	operator cVec<Type, 3> () const;
	
	const cStr ToString(const int Prec = 2) const;

	const cAngles ToAngles() const;
	
	void ToPolarXZ(double *Radius, double *Angle) const;
	static const dVec3 FromPolarXZ(const double Radius, const double Angle);
	double ToBaryCentric(const dVec3 &t0, const dVec3 &t1, const dVec3 &t2, double &f, double &g) const;

	const dVec3 ToNormal() const;
	void ToPerps(dVec3 &X, dVec3 &Y) const;
	const dVec3 ToPerp() const;

	static bool RayTri(const dVec3 &RayOrig, const dVec3 &RayDir, const dVec3 &t0, const dVec3 &t1, const dVec3 &t2, double &u, double &v, double &t, const bool BackFaceCull = false);
	static bool PointInTriangle(const dVec3 &p, const dVec3 &t0, const dVec3 &t1, const dVec3 &t2);
};

// dVec3.ctor : ()
inline dVec3::dVec3() {
}
// dVec3.ctor : (const double)
inline dVec3::dVec3(const double S)
: x(S), y(S), z(S) {}

// dVec3.ctor : (const double, const double, const double)
inline dVec3::dVec3(const double X, const double Y, const double Z)
: x(X), y(Y), z(Z) {}

// dVec3.ctor : (const dVec2 &, const double)
inline dVec3::dVec3(const dVec2 &XY, const double Z)
: x(XY.x), y(XY.y), z(Z) {}

// dVec3::SetZero
inline void dVec3::SetZero() {
	x = y = z = 0.0;
}

// dVec3::SetOne
inline void dVec3::SetOne() {
	x = y = z = 1.0;
}

// dVec3::Set : void (const double)
inline void dVec3::Set(const double S) {
	x = y = z = S;
}

// dVec3::Set : void (const double, const double, const double)
inline void dVec3::Set(const double X, const double Y, const double Z) {
	x = X;
	y = Y;
	z = Z;
}

// dVec3::Set : void (const dVec2 &, const double)
inline void dVec3::Set(const dVec2 &XY, const double Z) {
	x = XY.x;
	y = XY.y;
	z = Z;
}

// dVec3::Copy
inline void dVec3::Copy(const double *Src) {
	cAssert(Src != NULL);
	x = Src[0];
	y = Src[1];
	z = Src[2];
}

// dVec3::operator [] : double & (const int)
inline double & dVec3::operator [] (const int Index) {
	cAssert(Index >= 0 && Index < 3);
	return (&x)[Index];
}

// dVec3::operator [] : double(const int) const
inline double dVec3::operator [] (const int Index) const {
	cAssert(Index >= 0 && Index < 3);
	return (&x)[Index];
}

// dVec3::operator - : const dVec3() const
inline const dVec3 dVec3::operator - () const {
	return dVec3(-x, -y, -z);
}

// dVec3::operator += : void (const dVec3 &)
inline void dVec3::operator += (const dVec3 &u) {
	x += u.x;
	y += u.y;
	z += u.z;
}

// dVec3::operator -= : void (const dVec3 &)
inline void dVec3::operator -= (const dVec3 &u) {
	x -= u.x;
	y -= u.y;
	z -= u.z;
}

// dVec3::operator *= : void (const dVec3 &)
inline void dVec3::operator *= (const dVec3 &u) {
	x *= u.x;
	y *= u.y;
	z *= u.z;
}

// dVec3::operator *= : void (const double)
inline void dVec3::operator *= (const double s) {
	x *= s;
	y *= s;
	z *= s;
}

// dVec3::operator /= : void (const dVec3 &)
inline void dVec3::operator /= (const dVec3 &u) {
	x /= u.x;
	y /= u.y;
	z /= u.z;
}

// dVec3::operator /= : void (const double)
inline void dVec3::operator /= (const double s) {
	const double is = 1.0 / s;
	x *= is;
	y *= is;
	z *= is;
}

// dVec3::operator + : const dVec3(const dVec3 &) const
inline const dVec3 dVec3::operator + (const dVec3 &u) const {
	return dVec3(x + u.x, y + u.y, z + u.z);
}

// dVec3::operator - : const dVec3(const dVec3 &) const
inline const dVec3 dVec3::operator - (const dVec3 &u) const {
	return dVec3(x - u.x, y - u.y, z - u.z);
}

// dVec3::operator * : const dVec3(const dVec3 &) const
inline const dVec3 dVec3::operator * (const dVec3 &u) const {
	return dVec3(x * u.x, y * u.y, z * u.z);
}

// dVec3::operator * : const dVec3(const double) const
inline const dVec3 dVec3::operator * (const double s) const {
	return dVec3(x * s, y * s, z * s);
}

// dVec3::friend operator * : const dVec3(const double, const dVec3 &)
inline const dVec3 operator * (const double s, const dVec3 &u) {
	return dVec3(s * u.x, s * u.y, s * u.z);
}

// dVec3::operator / : const dVec3(const dVec3 &) const
inline const dVec3 dVec3::operator / (const dVec3 &u) const {
	return dVec3(x / u.x, y / u.y, z / u.z);
}

// dVec3::operator / : const dVec3(const double) const
inline const dVec3 dVec3::operator / (const double s) const {
	const double is = 1.0 / s;
	return dVec3(x * is, y * is, z * is);
}

// dVec3::friend operator / : const dVec3 (const double, const dVec3 &)
inline const dVec3 operator / (const double s, const dVec3 &u) {
	return dVec3(s / u.x, s / u.y, s / u.z);
}

// @todo stability  Verify and fixed operator==() for other class with double data.
// dVec3::operator == : bool(const dVec3 &) const
inline bool dVec3::operator == (const dVec3 &u) const {
	return dVec3::Equals( *this, u );
}

// dVec3::operator != : bool(const dVec3 &) const
inline bool dVec3::operator != (const dVec3 &u) const {
	return !dVec3::Equals( *this, u );
}

// dVec3::Equals : bool(const dVec3 &, const dVec3 &, const double)
inline bool dVec3::Equals(const dVec3 &u, const dVec3 &v, const double Eps) {
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

// dVec3::Length : double() const
inline double dVec3::Length() const {
	return cMath::Sqrt(x * x + y * y + z * z);	
}

// dVec3::LengthM
inline double dVec3::LengthM() const {	
	return cMath::Abs(x)+cMath::Abs(y)+cMath::Abs(z);	
}

// dVec3::LengthSq : double() const
inline double dVec3::LengthSq() const {
	return x * x + y * y + z * z;
}

// dVec3::Normalize : double()
inline double dVec3::Normalize() {
	const double l = Length();
	if(l > 0.0) {
		const double il = 1.0 / l;
		x *= il;
		y *= il;
		z *= il;
	}
	return l;
}

// dVec3::NormalizeSafe
inline double dVec3::NormalizeSafe(const dVec3 &Fallback) {
	const double l = Length();
	if(l > cMath::EpsilonSq) {
		const double il = 1.0 / l;
		x *= il;
		y *= il;
		z *= il;
		cAssert(IsNormalized());
		return l;
	}
	
	*this = Fallback;
	cAssert(IsNormalized());
	return 0.0;
}

// dVec3::IsValid : bool () const
inline bool dVec3::IsValid() const {
	return cMath::IsValid(x) && cMath::IsValid(y) && cMath::IsValid(z);
}

// dVec3::IsNormalized : bool(const double) const
inline bool dVec3::IsNormalized(const double Eps) const {
	return cMath::IsOne(LengthSq(), Eps);
}

// dVec3::IsZero : bool(const double) const
inline bool dVec3::IsZero(const double Eps) const {
	if(!cMath::IsZero(x, Eps)) return false;
	if(!cMath::IsZero(y, Eps)) return false;
	if(!cMath::IsZero(z, Eps)) return false;
	return true;
}

// dVec3::Round : ()
inline void dVec3::Round() {
	x = cMath::Round(x);
	y = cMath::Round(y);
	z = cMath::Round(z);
}

// dVec3::Abs : const dVec3(const dVec3 &)
inline const dVec3 dVec3::Abs(const dVec3 &u) {
	return dVec3(cMath::Abs(u.x), cMath::Abs(u.y), cMath::Abs(u.z));
}

// dVec3::Angle : double(const dVec3 &, const dVec3 &)
inline double dVec3::Angle(const dVec3 &u, const dVec3 &v) {
	const double D = dVec3::Dot(u, v);
	double ll = u.Length() * v.Length();
	return cMath::Deg(cMath::ACos(D / ll));
}

// dVec3::AreaSigned
inline double dVec3::AreaSigned(const dVec3 &t0, const dVec3 &t1, const dVec3 &t2) {
	const dVec3 e1 = t1 - t0;
	const dVec3 e2 = t2 - t0;
	return Length(Cross(e1, e2)) * 0.5f;
}

// dVec3::BaryCentric
inline const dVec3 dVec3::BaryCentric(const dVec3 &t0, const dVec3 &t1, const dVec3 &t2, const double f, const double g) {
	const dVec3 e1 = t1 - t0;
	const dVec3 e2 = t2 - t0;
	return t0 + f * e1 + g * e2;
}

// dVec3::ToPolarXZ
inline void dVec3::ToPolarXZ(double *Radius, double *Angle) const {
	dVec2 t(x, -z);
	t.ToPolar(Radius, Angle);
}

// dVec3::FromPolarXZ
inline const dVec3 dVec3::FromPolarXZ(const double Radius, const double Angle) {
	dVec2 t = dVec2::FromPolar(Radius, Angle);
	return dVec3(t.x, 0.0, -t.y);
}

// dVec3::ToBaryCentric
inline double dVec3::ToBaryCentric(const dVec3 &t0, const dVec3 &t1, const dVec3 &t2, double &f, double &g) const {
	const double A = AreaSigned(t0, t1, t2);
	if(A != 0) {
		const double iA = 1.0 / A;
		f = AreaSigned(t0, *this, t2) * iA;
		g = AreaSigned(t0, t1, *this) * iA;
	} else {
		f = g = 0.0;
	}
	return A;
}

// dVec3::Clamp
inline const dVec3 dVec3::Clamp(const dVec3 &u, const dVec3 &bbMin, const dVec3 &bbMax) {
	dVec3 r;
	r.x = u.x < bbMin.x ? bbMin.x : (u.x > bbMax.x ? bbMax.x : u.x);
	r.y = u.y < bbMin.y ? bbMin.y : (u.y > bbMax.y ? bbMax.y : u.y);
	r.z = u.z < bbMin.z ? bbMin.z : (u.z > bbMax.z ? bbMax.z : u.z);
	return r;
}

// dVec3::Cross
inline const dVec3 dVec3::Cross(const dVec3 &u, const dVec3 &v) {
	return dVec3(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
}
// dVec3::SetCross
inline void dVec3::SetCross(const dVec3 &u, const dVec3 &v) {
	*this = dVec3(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
}

// dVec3::DistanceSq : double(const dVec3 &, const dVec3 &)
inline double dVec3::DistanceSq(const dVec3 &u, const dVec3 &v) {
	double dx = u.x - v.x;
	double dy = u.y - v.y;
	double dz = u.z - v.z;
	return dx * dx + dy * dy + dz * dz;
}

// dVec3::Distance : double(const dVec3 &, const dVec3 &)
inline double dVec3::Distance(const dVec3 &u, const dVec3 &v) {
	double dx = u.x - v.x;
	double dy = u.y - v.y;
	double dz = u.z - v.z;
	return cMath::Sqrt(dx * dx + dy * dy + dz * dz);
}

// dVec3::Distance : double(const dVec3 &)
inline double dVec3::Distance(const dVec3 &u) const {
	double dx = u.x - x;
	double dy = u.y - y;
	double dz = u.z - z;
	return cMath::Sqrt(dx * dx + dy * dy + dz * dz);
}

// dVec3::Dot : double(const dVec3 &, const dVec3 &)
inline double dVec3::Dot(const dVec3 &u, const dVec3 &v) {
	return u.x * v.x + u.y * v.y + u.z * v.z;
}

// dVec3::Dot : double(const dVec3 &)
inline double dVec3::Dot(const dVec3 &u) const {
	return u.x * x + u.y * y + u.z * z;
}

// dVec3::Length : double(const dVec3 &)
inline double dVec3::Length(const dVec3 &u) {
	return cMath::Sqrt(u.x * u.x + u.y * u.y + u.z * u.z);
}

// dVec3::LengthSq : double(const dVec3 &)
inline double dVec3::LengthSq(const dVec3 &u) {
	return u.x * u.x + u.y * u.y + u.z * u.z;
}

// dVec3::Lerp
inline const dVec3 dVec3::Lerp(const dVec3 &u, const dVec3 &v, const double s) {
	dVec3 r;
	r.x = u.x + s * (v.x - u.x);
	r.y = u.y + s * (v.y - u.y);
	r.z = u.z + s * (v.z - u.z);
	return r;
}

// dVec3::Lerp05 : const dVec3(const dVec3 &, const dVec3 &)
inline const dVec3 dVec3::Lerp05(const dVec3 &u, const dVec3 &v) {
	dVec3 r;
	r.x = 0.5f * (u.x + v.x);
	r.y = 0.5f * (u.y + v.y);
	r.z = 0.5f * (u.z + v.z);
	return r;
}

// dVec3::Max : const dVec3(const dVec3 &, const dVec3 &)
inline const dVec3 dVec3::Max(const dVec3 &u, const dVec3 &v) {
	dVec3 r;
	r.x = u.x > v.x ? u.x : v.x;
	r.y = u.y > v.y ? u.y : v.y;
	r.z = u.z > v.z ? u.z : v.z;
	return r;
}

// dVec3::Min : const dVec3(const dVec3 &, const dVec3 &)
inline const dVec3 dVec3::Min(const dVec3 &u, const dVec3 &v) {
	dVec3 r;
	r.x = u.x < v.x ? u.x : v.x;
	r.y = u.y < v.y ? u.y : v.y;
	r.z = u.z < v.z ? u.z : v.z;
	return r;
}

// dVec3::Normalize
inline const dVec3 dVec3::Normalize(const dVec3 &u) {
	double l = cMath::Sqrt(u.x * u.x + u.y * u.y + u.z * u.z);
	if(l > 0.0) {
		double il = 1.0 / l;
		return dVec3(u.x * il, u.y * il, u.z * il);
	}
	return u;
}

// dVec3::Reflect
inline const dVec3 dVec3::Reflect(const dVec3 &RayDir, const dVec3 &Normal) {
	return RayDir - 2.0 * Dot(RayDir, Normal) * Normal;
}

// dVec3::Refract
inline const dVec3 dVec3::Refract(const dVec3 &RayDir, const dVec3 &Normal, const double Eta) {
	double k = 1.0 - Eta * Eta * (1.0 - cMath::Square(Dot(Normal, RayDir)));
	if(k < 0.0) return dVec3::Zero;
	return Eta * RayDir - (Eta * Dot(Normal, RayDir) + cMath::Sqrt(k)) * Normal;
}

// dVec3::Truncate : (const double)
inline void dVec3::Truncate(const double MaxLen) {
	if(MaxLen <= 0) {
		SetZero();
		return;
	}
	double l = Length();
	if(l > MaxLen) {
		double il = MaxLen / l;
		x *= il;
		y *= il;
		z *= il;
	}
}

// dVec3::Truncate : (const dVec3 &, ...)
inline const dVec3 dVec3::Truncate(const dVec3 &u, const double MaxLen) {
	if(MaxLen <= 0) {
		return dVec3::Zero;
	}
	double l = u.Length();
	if(l > MaxLen) {
		double il = MaxLen / l;
		return dVec3(u.x * il, u.y * il, u.z * il);
	}
	return u;
}

// dVec3::GetDimension : int() const
inline int dVec3::GetDimension() const {
	return 3;
}

// dVec3::ToDoublePtr : const double * () const
inline const double * dVec3::ToDoublePtr() const {
	return (const double *)&x;
}

// dVec3::ToDoublePtr : double * ()
inline double * dVec3::ToDoublePtr() {
	return (double *)&x;
}

// dVec3::ToVec2 : const dVec2 & () const
inline const dVec2 & dVec3::ToVec2() const {
	return *reinterpret_cast<const dVec2 *>(this);
}

// dVec3::ToVec2 : dVec2 & ()
inline dVec2 & dVec3::ToVec2() {
	return *reinterpret_cast<dVec2 *>(this);
}

// dVec3::operator cVec<Type, 3>
template<class Type>
dVec3::operator cVec<Type, 3> () const {
	return cVec<Type, 3>( (Type)x, (Type)y, (Type)z );
}

// dVec3::ToNormal : const dVec2 () const
inline const dVec3 dVec3::ToNormal() const {
	dVec3 u(*this);
	u.Normalize();
	return u;
}

// dVec3::Rand
inline const dVec3 dVec3::Rand(const dVec3 &Lo, const dVec3 &Hi) {
	return dVec3(cMath::dRand(Lo.x, Hi.x), cMath::dRand(Lo.y, Hi.y), cMath::dRand(Lo.z, Hi.z));
}

// dVec3::Project
inline const dVec3 dVec3::Project(const dVec3 &v1, const dVec3 &v2) {
	double mul;
	mul = dVec3::Dot(v1, v2) / dVec3::Dot(v2, v2);
	return dVec3(mul * v2.x, mul * v2.y, mul * v2.z);
}

inline double dVec3::TriProjectionSolidAngle(const dVec3 &v1, const dVec3 &v2, const dVec3 &v3) const {
	dVec3 u(*this);
	dVec3 a = v1 - u;
	dVec3 b = v2 - u;
	dVec3 c = v3 - u;
	double det = cMath::Abs(a.Dot(Cross(b,c)));
	
	double al = a.Length();
	double bl = b.Length(b);
	double cl = c.Length(c);
	
	double div = al*bl*cl + a.Dot(b)*cl + a.Dot(c)*bl + b.Dot(c)*al;
	double at = cMath::ATan(det, div);
	if(at < 0) {
		at += cMath::Pi; // If det>0 && div<0 atan2 returns < 0, so add pi.
	}
	double omega = 2.0 * at;
	return omega;
}

// dVec3::Perpendicular
inline const dVec3 dVec3::Perpendicular(const dVec3 &v1) {
	double X = cMath::Abs(v1.x);
	double Y = cMath::Abs(v1.y);
	double Z = cMath::Abs(v1.z);
	if(X>Y && X>Z) {
		return dVec3::Cross(v1,dVec3(1,0,0));
	} else if(Y>X && Y>Z) {
		return dVec3::Cross(v1,dVec3(0,1,0));
	} else {
		return dVec3::Cross(v1,dVec3(0,0,1));
	}
}
