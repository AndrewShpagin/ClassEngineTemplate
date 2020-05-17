#pragma once

template<class Type, int Dim>
struct cVec;

//*****************************************************************************
// dVec4
//*****************************************************************************
class dVec4 {
public:
	double x;
	double y;
	double z;
	double w;

	dVec4();
	explicit dVec4(const double S);
	dVec4(const double X, const double Y, const double Z, const double W);
	dVec4(const dVec2 &XY, const double Z, const double W);
	dVec4(const dVec2 &XY, const dVec2 &ZW);
	dVec4(const dVec3 &XYZ, const double W);
	dVec4(const cVec4& v4);

	void SetZero();
	void Set(const double S);
	void Set(const double X, const double Y, const double Z, const double W);
	void Set(const dVec2 &XY, const double Z, const double W);
	void Set(const dVec2 &XY, const dVec2 &ZW);
	void Set(const dVec3 &XYZ, const double W);

	void Copy(const double *pSrc);
	
	double & operator [] (const int index);
	double operator [] (const int index) const;
	
	const dVec4 operator - () const;

	void operator += (const dVec4 &);
	void operator -= (const dVec4 &);
	void operator *= (const dVec4 &);
	void operator *= (const double);
	void operator /= (const dVec4 &);
	void operator /= (const double);

	void Transform(const dMat4 &);
	void operator *= (const dMat4 &);

	const dVec4 & operator = (const dVec3 &);
	const dVec4 operator + (const dVec4 &) const;
	const dVec4 operator - (const dVec4 &) const;
	const dVec4 operator * (const dVec4 &) const;
	const dVec4 operator * (const double) const;
	friend const dVec4 operator * (const double, const dVec4 &);
	const dVec4 operator / (const dVec4 &) const;
	const dVec4 operator / (const double) const;
	friend const dVec4 operator / (const double, const dVec4 &);
	
	static const dVec4 Transform(const dVec4 &, const dMat4 &);
	const dVec4 operator * (const dMat4 &) const;

	bool operator == (const dVec4 &) const;
	bool operator != (const dVec4 &) const;
	static bool Equals(const dVec4 &, const dVec4 &, const double Eps = cMath::Epsilon);

	double Length() const;
	double LengthSq() const;
	double Normalize();
	double NormalizeSafe(const dVec4 &Fallback = dVec4::AxisW);
	bool IsNormalized(const double Eps = cMath::Epsilon) const;
	bool IsZero(const double Eps = cMath::Epsilon) const;

	static const dVec4 Abs(const dVec4 &);
	static double Dot(const dVec4 &, const dVec4 &);
//	static dVec4 BaryCentric(const dVec4 &, const dVec4 &, const dVec4 &, const double, const double);
//	static dVec4 Clamp(const dVec4 &, const dVec4 &, const dVec4 &);
//	static dVec4 Cross(const dVec4 &, const dVec4 &, const dVec4 &);
	static double Length(const dVec4 &);
	static double LengthSq(const dVec4 &);
	static const dVec4 Lerp(const dVec4 &, const dVec4 &, const double);
	static const dVec4 Max(const dVec4 &, const dVec4 &);
	static const dVec4 Min(const dVec4 &, const dVec4 &);
	static const dVec4 Normalize(const dVec4 &);

	static const dVec4 Zero;
	static const dVec4 One;
	static const dVec4 Infinity;
	static const dVec4 AxisX;
	static const dVec4 AxisY;
	static const dVec4 AxisZ;
	static const dVec4 AxisW;
	static const dVec4 AxisNegX;
	static const dVec4 AxisNegY;
	static const dVec4 AxisNegZ;
	static const dVec4 AxisNegW;
	
	const double * ToFloatPtr() const;
	double * ToFloatPtr();

	const dVec2 & ToVec2() const;
	dVec2 & ToVec2();
	
	const dVec3 & ToVec3() const;
	dVec3 & ToVec3();

    template<class Type>
    operator cVec<Type, 4>() const;

	int GetDimension() const;
	const cStr ToString(const int Prec = 2) const;
};

// dVec4.ctor : ()
inline dVec4::dVec4() {
}

inline dVec4::dVec4(const cVec4& v4)
:x(v4.x), y(v4.y), z(v4.z), w(v4.w){}

// dVec4.ctor : (const double)
inline dVec4::dVec4(const double S)
: x(S), y(S), z(S), w(S) {}

// dVec4.ctor : (const double, const double, const double, const double)
inline dVec4::dVec4(const double X, const double Y, const double Z, const double W)
: x(X), y(Y), z(Z), w(W) {}

// dVec4.ctor : (const dVec2 &, const double, const double)
inline dVec4::dVec4(const dVec2 &XY, const double Z, const double W)
: x(XY.x), y(XY.y), z(Z), w(W) {}

// dVec4.ctor : (const dVec2 &, const dVec2 &)
inline dVec4::dVec4(const dVec2 &XY, const dVec2 &ZW)
: x(XY.x), y(XY.y), z(ZW.x), w(ZW.y) {}

// dVec4.ctor : (const dVec3 &, const double)
inline dVec4::dVec4(const dVec3 &XYZ, const double W)
: x(XYZ.x), y(XYZ.y), z(XYZ.z), w(W) {}

// dVec4::SetZero : void ()
inline void dVec4::SetZero() {
	x = y = z = w = 0.0;
}

// dVec4::Set : void (const double)
inline void dVec4::Set(const double S) {
	x = y = z = w = S;
}

// dVec4::Set : void (const double, const double, const double, const double)
inline void dVec4::Set(const double X, const double Y, const double Z, const double W) {
	x = X;
	y = Y;
	z = Z;
	w = W;
}

// dVec4::Set : void (const dVec2 &, const double, const double)
inline void dVec4::Set(const dVec2 &XY, const double Z, const double W) {
	x = XY.x;
	y = XY.y;
	z = Z;
	w = W;
}

// dVec4::Set : (const dVec2 &, const dVec2 &)
inline void dVec4::Set(const dVec2 &XY, const dVec2 &ZW) {
	x = XY.x;
	y = XY.y;
	z = ZW.x;
	w = ZW.y;
}

// dVec4::Set : void (const dVec3 &, const double)
inline void dVec4::Set(const dVec3 &XYZ, const double W) {
	x = XYZ.x;
	y = XYZ.y;
	z = XYZ.z;
	w = W;
}

// dVec4::Copy : void (const double *)
inline void dVec4::Copy(const double *pSrc) {
	cAssert(pSrc);
	x = pSrc[0];
	y = pSrc[1];
	z = pSrc[2];
	w = pSrc[3];
}

// dVec4::operator [] : double & (const int)
inline double & dVec4::operator [] (const int index) {
	cAssert(index >= 0 && index < 4);
	return (&x)[index];
}

// dVec4::operator [] : double (const int) const
inline double dVec4::operator [] (const int index) const {
	cAssert(index >= 0 && index < 4);
	return (&x)[index];
}

// dVec4::operator - : const dVec4 () const
inline const dVec4 dVec4::operator - () const {
	return dVec4(-x, -y, -z, -w);
}

// dVec4::operator += : void (const dVec4 &)
inline void dVec4::operator += (const dVec4 &u) {
	x += u.x;
	y += u.y;
	z += u.z;
	w += u.w;
}

// dVec4::operator -= : void (const dVec4 &)
inline void dVec4::operator -= (const dVec4 &u) {
	x -= u.x;
	y -= u.y;
	z -= u.z;
	w -= u.w;
}

// dVec4::operator *= : void (const dVec4 &)
inline void dVec4::operator *= (const dVec4 &u) {
	x *= u.x;
	y *= u.y;
	z *= u.z;
	w *= u.w;
}

// dVec4::operator *= : void (const double)
inline void dVec4::operator *= (const double s) {
	x *= s;
	y *= s;
	z *= s;
	w *= s;
}

// dVec4::operator /= : void (const dVec4 &)
inline void dVec4::operator /= (const dVec4 &u) {
	x /= u.x;
	y /= u.y;
	z /= u.z;
	w /= u.w;
}

// dVec4::operator /= : void (const double)
inline void dVec4::operator /= (const double s) {
	double is = 1.0 / s;
	x *= is;
	y *= is;
	z *= is;
	w *= is;
}

// dVec4::operator + : const dVec4 (const dVec4 &) const
inline const dVec4 dVec4::operator + (const dVec4 &u) const {
	return dVec4(x + u.x, y + u.y, z + u.z, w + u.w);
}

// dVec4::operator - : const dVec4 (const dVec4 &) const
inline const dVec4 dVec4::operator - (const dVec4 &u) const {
	return dVec4(x - u.x, y - u.y, z - u.z, w - u.w);
}

// dVec4::operator * : const dVec4 (const dVec4 &) const
inline const dVec4 dVec4::operator * (const dVec4 &u) const {
	return dVec4(x * u.x, y * u.y, z * u.z, w * u.w);
}

// dVec4::operator * : const dVec4 (const double) const
inline const dVec4 dVec4::operator * (const double s) const {
	return dVec4(x * s, y * s, z * s, w * s);
}

// dVec4::friend operator * : const dVec4 (const double, const dVec4 &)
inline const dVec4 operator * (const double s, const dVec4 &u) {
	return dVec4(s * u.x, s * u.y, s * u.z, s * u.w);
}

// dVec4::operator / : const dVec4 (const dVec4 &) const
inline const dVec4 dVec4::operator / (const dVec4 &u) const {
	return dVec4(x / u.x, y / u.y, z / u.z, w / u.w);
}

// dVec4::operator / : const dVec4 (const double) const
inline const dVec4 dVec4::operator / (const double s) const {
	double is = 1.0 / s;
	return dVec4(x * is, y * is, z * is, w * is);
}

// dVec4::friend operator / : const dVec4 (const double, const dVec4 &)
inline const dVec4 operator / (const double s, const dVec4 &u) {
	return dVec4(s / u.x, s / u.y, s / u.z, s / u.w);
}

// dVec4::operator == : bool (const dVec4 &) const
inline bool dVec4::operator == (const dVec4 &u) const {
	return x == u.x && y == u.y && z == u.z && w == u.w;
}

// dVec4::operator != : bool (const dVec4 &) const
inline bool dVec4::operator != (const dVec4 &u) const {
	return x != u.x || y != u.y || z != u.z || w != u.w;
}

// dVec4::Equals : bool (const dVec4 &, const dVec4 &, const double)
inline bool dVec4::Equals(const dVec4 &u, const dVec4 &v, const double Eps /*= cMath::Epsilon*/) {
	if(cMath::Abs(u.x - v.x) > Eps) {
		return false;
	}
	if(cMath::Abs(u.y - v.y) > Eps) {
		return false;
	}
	if(cMath::Abs(u.z - v.z) > Eps) {
		return false;
	}
	if(cMath::Abs(u.w - v.w) > Eps) {
		return false;
	}
	return true;
}

// dVec4::Length : double () const
inline double dVec4::Length() const {
	return sqrt(x * x + y * y + z * z + w * w);
}

// dVec4::LengthSq : double () const
inline double dVec4::LengthSq() const {
	return x * x + y * y + z * z + w * w;
}

// dVec4::Normalize : double ()
inline double dVec4::Normalize() {
	const double l = Length();
	if(l > 0.0) {
		(*this) /= l;
	}
	return l;
}

// dVec4::NormalizeSafe : double (const dVec4 &)
inline double dVec4::NormalizeSafe(const dVec4 &Fallback /*= dVec4::wAxis*/) {
	const double l = Length();
	if(l < cMath::Epsilon) {
		*this = Fallback;
		cAssert(IsNormalized());
		return 0.0;
	} else {
		(*this) /= l;
		cAssert(IsNormalized());
		return l;
	}
}

// dVec4::IsNormalized : bool (const double) const
inline bool dVec4::IsNormalized(const double Eps) const {
	return cMath::IsOne(LengthSq(), Eps);
}

// dVec4::IsZero : bool(const double) const
inline bool dVec4::IsZero(const double Eps) const {
	if(!cMath::IsZero(x, Eps)) {
		return false;
	}
	if(!cMath::IsZero(y, Eps)) {
		return false;
	}
	if(!cMath::IsZero(z, Eps)) {
		return false;
	}
	if(!cMath::IsZero(w, Eps)) {
		return false;
	}
	return true;
}

// dVec4::Abs : const dVec4 (const dVec4 &)
inline const dVec4 dVec4::Abs(const dVec4 &u) {
	return dVec4(cMath::Abs(u.x), cMath::Abs(u.y), cMath::Abs(u.z), cMath::Abs(u.w));
}

// dVec4::Dot : double (const dVec4 &, const dVec4 &)
inline double dVec4::Dot(const dVec4 &u, const dVec4 &v) {
	return u.x * v.x + u.y * v.y + u.z * v.z + u.w * v.w;
}

// dVec4::Length : double (const dVec4 &)
inline double dVec4::Length(const dVec4 &u) {
	return cMath::Sqrt(u.x * u.x + u.y * u.y + u.z * u.z + u.w * u.w);
}

// dVec4::LengthSq : double (const dVec4 &)
inline double dVec4::LengthSq(const dVec4 &u) {
	return u.x * u.x + u.y * u.y + u.z * u.z + u.w * u.w;
}

// dVec4::Lerp : const dVec4 (const dVec4 &, const dVec4 &, const double)
inline const dVec4 dVec4::Lerp(const dVec4 &u, const dVec4 &v, const double s) {
	dVec4 r;
	r.x = u.x + s * (v.x - u.x);
	r.y = u.y + s * (v.y - u.y);
	r.z = u.z + s * (v.z - u.z);
	r.w = u.w + s * (v.w - u.w);
	return r;
}

// dVec4::Max : const dVec4 (const dVec4 &, const dVec4 &)
inline const dVec4 dVec4::Max(const dVec4 &u, const dVec4 &v) {
	dVec4 r;
	r.x = u.x > v.x ? u.x : v.x;
	r.y = u.y > v.y ? u.y : v.y;
	r.z = u.z > v.z ? u.z : v.z;
	r.w = u.w > v.w ? u.w : v.w;
	return r;
}

// dVec4::Min : const dVec4 (const dVec4 &, const dVec4 &)
inline const dVec4 dVec4::Min(const dVec4 &u, const dVec4 &v) {
	dVec4 r;
	r.x = u.x < v.x ? u.x : v.x;
	r.y = u.y < v.y ? u.y : v.y;
	r.z = u.z < v.z ? u.z : v.z;
	r.w = u.w < v.w ? u.w : v.w;
	return r;
}

// dVec4::Normalize : const dVec4 (const dVec4 &)
inline const dVec4 dVec4::Normalize(const dVec4 &u) {
	const double l = cMath::Sqrt(u.x * u.x + u.y * u.y + u.z * u.z + u.w * u.w);
	if(l > 0.0) {
		const double il = 1.0 / l;
		return dVec4(u.x * il, u.y * il, u.z * il, u.w * il);
	}
	return u;
}

// dVec4::ToFloatPtr : const double * () const
inline const double * dVec4::ToFloatPtr() const {
	return (const double *)&x;
}

// dVec4::ToFloatPtr : double * ()
inline double * dVec4::ToFloatPtr() {
	return (double *)&x;
}

// dVec4::ToVec2 : const dVec2 & () const
inline const dVec2 & dVec4::ToVec2() const {
	return *reinterpret_cast<const dVec2 *>(this);
}

// dVec4::ToVec2 : dVec2 & ()
inline dVec2 & dVec4::ToVec2() {
	return *reinterpret_cast<dVec2 *>(this);
}

// dVec4::ToVec3 : const dVec3 & () const
inline const dVec3 & dVec4::ToVec3() const {
	return *reinterpret_cast<const dVec3 *>(this);
}

// dVec4::ToVec3 : dVec3 & ()
inline dVec3 & dVec4::ToVec3() {
	return *reinterpret_cast<dVec3 *>(this);
}

// dVec3::operator cVec<Type, 4>
template<class Type>
dVec4::operator cVec<Type, 4>() const {
    return cVec<Type, 4>( ( Type )x, ( Type )y, ( Type )z, ( Type )w );
}

// dVec4::GetDimension : int() const
inline int dVec4::GetDimension() const {
	return 4;
}
