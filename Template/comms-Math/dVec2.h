#pragma once

template<class Type, int Dim>
struct cVec;

//*****************************************************************************
// dVec2
//*****************************************************************************
class COMMS_ALIASING dVec2 {
public:
	double x;
	double y;

	dVec2();
	explicit dVec2(const double S);
	dVec2(const double X, const double Y);

	void Copy(const double *Src);
	void SetZero();
	void SetOne();
	void Set(const double S);
	void Set(const double X, const double Y);

	double operator [] (const int index) const;
	double & operator [] (const int index);

	const dVec2 operator - () const;

	void operator += (const dVec2 &);
	void operator -= (const dVec2 &);
	void operator *= (const dVec2 &);
	void operator *= (const double);
	void operator /= (const dVec2 &);
	void operator /= (const double);

	void Transform(const dMat3 &); // (x, y, 0)
	void operator *= (const dMat3 &);
	
	void TransformCoordinate(const dMat4 &); // (x, y, 0, 1), projects the result back into w = 1
	void TransformNormal(const dMat4 &); // (x, y, 0)

	const dVec2 operator + (const dVec2 &) const;
	const dVec2 operator - (const dVec2 &) const;
	const dVec2 operator * (const dVec2 &) const;
	const dVec2 operator * (const double) const;
	friend const dVec2 operator * (const double, const dVec2 &);
	const dVec2 operator / (const dVec2 &) const;
	const dVec2 operator / (const double) const;
	friend const dVec2 operator / (const double, const dVec2 &);

	static const dVec2 Transform(const dVec2 &, const dMat3 &); // (x, y, 0)
	const dVec2 operator * (const dMat3 &) const;
	
	static const dVec4 Transform(const dVec2 &, const dMat4 &); // (x, y, 0, 1)
	static const dVec2 TransformCoordinate(const dVec2 &, const dMat4 &); // (x, y, 0, 1), projects the result back into w = 1
	static const dVec2 TransformNormal(const dVec2 &, const dMat4 &); // (x, y, 0, 0)

	bool operator == (const dVec2 &) const;
	bool operator != (const dVec2 &) const;
	static bool Equals(const dVec2 &, const dVec2 &, const double Eps = cMath::Epsilon);

	double Length() const;
	double LengthSq() const;
	double Normalize();
	double NormalizeSafe(const dVec2 &Fallback);
	bool IsValid() const;
	bool IsNormalized(const double Eps = cMath::Epsilon) const;
	bool IsZero(const double Eps = cMath::Epsilon) const;
	
	static const dVec2 Round(const dVec2 &);
	const dVec2 ToRound() const;
	void Round();

	static const dVec2 Abs(const dVec2 &);
	static double Angle(const dVec2 &, const dVec2 &);
	static double AreaSigned(const dVec2 &t0, const dVec2 &t1, const dVec2 &t2);
	static double Ccw(const dVec2 &, const dVec2 &);
	static const dVec2 Clamp(const dVec2 &Value, const dVec2 &Lo, const dVec2 &Hi);
	static double Distance(const dVec2 &, const dVec2 &);
	static double DistanceSq(const dVec2 &, const dVec2 &);
	static double Dot(const dVec2 &, const dVec2 &);
	static double Length(const dVec2 &);
	static double LengthSq(const dVec2 &);
	static const dVec2 Lerp(const dVec2 &, const dVec2 &, const double);
	static const dVec2 Lerp05(const dVec2 &, const dVec2 &);
	static const dVec2 Max(const dVec2 &, const dVec2 &);
	static const dVec2 Min(const dVec2 &, const dVec2 &);
	static const dVec2 Normalize(const dVec2 &);
	static const dVec2 NormalizeSafe(const dVec2 &Src, const dVec2 &Fallback);
	static const dVec2 PerpCw(const dVec2 &);
	static const dVec2 PerpCcw(const dVec2 &);
	static const dVec2 Reflect(const dVec2 &RayDir, const dVec2 &Normal);
	static const dVec2 Refract(const dVec2 &RayDir, const dVec2 &Normal, const double Eta);
	static const dVec2 Truncate(const dVec2 &u, const double MaxLength);
	void Truncate(const double MaxLength);
	static const dVec2 RandRange1();
	static const dVec2 RandNormal();
	static const dVec2 Rand(const dVec2 &Lo, const dVec2 &Hi);
	
	double DistanceToLineSegSq(const dVec2 &A, const dVec2 &B, double *pScale = NULL) const;
	static bool SegIntersection(const dVec2 &L0, const dVec2 &L1, const dVec2 &R0, const dVec2 &R1, double *l = NULL, double *r = NULL);
	
	static const dVec2 FromBaryCentric(const dVec2 &t0, const dVec2 &t1, const dVec2 &t2, const double u, const double v);
	static const dVec2 FromPolar(const double Radius, const double Angle);

	static const dVec2 Zero;
	static const dVec2 One;
	static const dVec2 Infinity;
	static const dVec2 AxisX;
	static const dVec2 AxisY;
	static const dVec2 AxisNegX;
	static const dVec2 AxisNegY;
	
	int GetDimension() const;

	const double * ToDoublePtr() const;
	double * ToDoublePtr();

	template<class Type>
	operator cVec<Type, 2> () const;

	void ToPolar(double *Radius, double *Angle) const;
	double ToBaryCentric(const dVec2 &t0, const dVec2 &t1, const dVec2 &t2, double &u, double &v) const;
	bool IsInsideTri(const dVec2 &t0, const dVec2 &t1, const dVec2 &t2) const;

	const cStr ToString(const int Prec = 2) const;
	friend cStr & operator << (cStr &, const dVec2 &);

	const dVec2 ToNormal() const;

	const dVec2 ToPerpCw() const;
	const dVec2 ToPerpCcw() const;
};

// dVec2.ctor : ()
inline dVec2::dVec2() {
}

// dVec2.ctor : (const double)
inline dVec2::dVec2(const double S)
: x(S), y(S) {}

// dVec2.ctor : (const double, const double)
inline dVec2::dVec2(const double X, const double Y)
: x(X), y(Y) {}

// dVec2::Copy
inline void dVec2::Copy(const double *Src) {
	cAssert(Src != NULL);
	x = Src[0];
	y = Src[1];
}

// dVec2::SetZero
inline void dVec2::SetZero() {
	x = y = 0.0f;
}

// dVec2::SetOne
inline void dVec2::SetOne() {
	x = y = 1.0f;
}

// dVec2::Set : void (const double)
inline void dVec2::Set(const double S) {
	x = y = S;
}

// dVec2::Set : void (const double, const double)
inline void dVec2::Set(const double X, const double Y) {
	x = X;
	y = Y;
}

// dVec2::operator [] : double(const int) const
inline double dVec2::operator [] (const int index) const {
	cAssert(index >= 0 && index < 2);
	return (&x)[index];
}

// dVec2::operator [] : double & (const int)
inline double & dVec2::operator [] (const int index) {
	cAssert(index >= 0 && index < 2);
	return (&x)[index];
}

// dVec2::operator - : const dVec2 () const
inline const dVec2 dVec2::operator - () const {
	return dVec2(-x, -y);
}

// dVec2::operator += : void (const dVec2 &)
inline void dVec2::operator += (const dVec2 &u) {
	x += u.x;
	y += u.y;
}

// dVec2::operator -= : void (const dVec2 &)
inline void dVec2::operator -= (const dVec2 &u) {
	x -= u.x;
	y -= u.y;
}

// dVec2::operator *= : void (const dVec2 &)
inline void dVec2::operator *= (const dVec2 &u) {
	x *= u.x;
	y *= u.y;
}

// dVec2::operator *= : void (const double)
inline void dVec2::operator *= (const double s) {
	x *= s;
	y *= s;
}

// dVec2::operator /= : void (const dVec2 &)
inline void dVec2::operator /= (const dVec2 &u) {
	x /= u.x;
	y /= u.y;
}

// dVec2::operator /= : void (const double)
inline void dVec2::operator /= (const double s) {
	double is = 1.0f / s;
	x *= is;
	y *= is;
}

// dVec2::operator + : const dVec2 (const dVec2 &) const
inline const dVec2 dVec2::operator + (const dVec2 &u) const {
	return dVec2(x + u.x, y + u.y);
}

// dVec2::operator - : const dVec2 (const dVec2 &) const
inline const dVec2 dVec2::operator - (const dVec2 &u) const {
	return dVec2(x - u.x, y - u.y);
}

// dVec2::operator * : const dVec2 (const dVec2 &) const
inline const dVec2 dVec2::operator * (const dVec2 &u) const {
	return dVec2(x * u.x, y * u.y);
}

// dVec2::operator * : const dVec2 (const double) const
inline const dVec2 dVec2::operator * (const double s) const {
	return dVec2(x * s, y * s);
}

// dVec2::friend operator * : const dVec2 (const double, const dVec2 &)
inline const dVec2 operator * (const double s, const dVec2 &u) {
	return dVec2(s * u.x, s * u.y);
}

// dVec2::operator / : const dVec2 (const dVec2 &) const
inline const dVec2 dVec2::operator / (const dVec2 &u) const {
	return dVec2(x / u.x, y / u.y);
}

// dVec2::operator / : const dVec2 (const double) const
inline const dVec2 dVec2::operator / (const double s) const {
	double is = 1.0f / s;
	return dVec2(x * is, y * is);
}

// dVec2::friend operator / : const dVec2 (const double, const dVec2 &)
inline const dVec2 operator / (const double s, const dVec2 &u) {
	return dVec2(s / u.x, s / u.y);
}

// dVec2::operator == : bool(const dVec2 &) const
inline bool dVec2::operator == (const dVec2 &u) const {
	return x == u.x && y == u.y;
}

// dVec2::operator != : bool(const dVec2 &) const
inline bool dVec2::operator != (const dVec2 &u) const {
	return x != u.x || y != u.y;
}

// dVec2::Equals : bool(const dVec2 &, const dVec2 &, const double)
inline bool dVec2::Equals(const dVec2 &u, const dVec2 &v, const double Eps) {
	if(cMath::Abs(u.x - v.x) > Eps) return false;
	if(cMath::Abs(u.y - v.y) > Eps) return false;
	return true;
}

// dVec2::Length : double() const
inline double dVec2::Length() const {
	return cMath::Sqrt(x * x + y * y);
}

// dVec2::LengthSq : double() const
inline double dVec2::LengthSq() const {
	return x * x + y * y;
}

// dVec2::Normalize : ()
inline double dVec2::Normalize() {
	const double l = Length();
	if(l > 0.0f) {
		const double il = 1.0f / l;
		x *= il;
		y *= il;
	}
	return l;
}

// dVec2::NormalizeSafe
inline double dVec2::NormalizeSafe(const dVec2 &Fallback) {
	const double l = Length();
	if(l > 0.0f) {
		const double il = 1.0f / l;
		x *= il;
		y *= il;
		cAssert(IsNormalized());
		return l;
	}
	*this = Fallback;
	cAssert(IsNormalized());
	return 0.0f;
}

// dVec2::IsValid : bool () const
inline bool dVec2::IsValid() const {
	return cMath::IsValid(x) && cMath::IsValid(y);
}

// dVec2::IsNormalized : bool(const double) const
inline bool dVec2::IsNormalized(const double Eps) const {
	return cMath::IsOne(LengthSq(), Eps);
}

// dVec2::IsZero : bool(const double) const
inline bool dVec2::IsZero(const double Eps) const {
	if(!cMath::IsZero(x, Eps)) return false;
	if(!cMath::IsZero(y, Eps)) return false;
	return true;
}

// dVec2::Normalize : const dVec2(const dVec2 &)
inline const dVec2 dVec2::Normalize(const dVec2 &u) {
	dVec2 t = u;
	t.Normalize();
	return t;
}

// dVec2::NormalizeSafe : (const dVec2 &, const dVec2 &)
inline const dVec2 dVec2::NormalizeSafe(const dVec2 &Src, const dVec2 &Fallback) {
	dVec2 t = Src;
	t.NormalizeSafe(Fallback);
	return t;
}

// dVec2::FromPolar
inline const dVec2 dVec2::FromPolar(const double Radius, const double Angle) {
	double A = cMath::Rad(Angle);
	return dVec2(Radius * cMath::Cos(A), Radius * cMath::Sin(A));
}

// dVec2::FromBaryCentric : dVec2(const dVec2 &, const dVec2 &, const dVec2 &, const double, const double)
inline const dVec2 dVec2::FromBaryCentric(const dVec2 &t0, const dVec2 &t1, const dVec2 &t2, const double u, const double v) {
	return t0 + u * (t1 - t0) + v * (t2 - t0);
}

// dVec2::Abs : const dVec2(const dVec2 &)
inline const dVec2 dVec2::Abs(const dVec2 &u) {
	return dVec2(cMath::Abs(u.x), cMath::Abs(u.y));
}

// dVec2::Round
inline const dVec2 dVec2::Round(const dVec2 &u) {
	return dVec2(cMath::Round(u.x), cMath::Round(u.y));
}

// dVec2::ToRound
inline const dVec2 dVec2::ToRound() const {
	return dVec2(cMath::Round(x), cMath::Round(y));
}

// dVec2::Round
inline void dVec2::Round() {
	x = cMath::Round(x);
	y = cMath::Round(y);
}

// dVec2::Angle : double(const dVec2 &, const dVec2 &)
inline double dVec2::Angle(const dVec2 &u, const dVec2 &v) {
	const double d = u.x * v.y - v.x * u.y;
	const double s = d != 0.0f ? cMath::Sign(d) : 1.0f;
	const double D = dVec2::Dot(u, v);
	const double ll = u.Length() * v.Length();
	return s * cMath::Deg(cMath::ACos(D / ll));
}

// dVec2::AreaSigned : double(const dVec2 &, const dVec2 &, const dVec2 &)
inline double dVec2::AreaSigned(const dVec2 &t0, const dVec2 &t1, const dVec2 &t2) {
	const dVec2 e1 = t1 - t0;
	const dVec2 e2 = t2 - t0;
	return Ccw(e1, e2) * 0.5f;
}

// dVec2::ToBaryCentric : void(const dVec2 &, const dVec2 &, const dVec2 &, double &, double &) const
inline double dVec2::ToBaryCentric(const dVec2 &t0, const dVec2 &t1, const dVec2 &t2, double &u, double &v) const {
	const double A = AreaSigned(t0, t1, t2);
	if(A != 0) {
		const double iA = 1.0f / A;
		u = AreaSigned(t0, *this, t2) * iA;
		v = AreaSigned(t0, t1, *this) * iA;
	} else {
		u = v = 0.0f;
	}
	return A;
}

// dVec2::IsInsideTri : bool(const dVec2 &, const dVec2 &, const dVec2 &) const
inline bool dVec2::IsInsideTri(const dVec2 &t0, const dVec2 &t1, const dVec2 &t2) const {
	double u, v;
	ToBaryCentric(t0, t1, t2, u, v);
	return u >= 0.0f && v >= 0.0f && 1.0f - u - v >= 0.0f;
}

// dVec2::ToPolar
inline void dVec2::ToPolar(double *Radius, double *Angle) const {
	double R = Length(), A = 0.0f;
	if(cMath::IsZero(R)) {
		R = 0.0f;
	} else {
		A = cMath::ACos(x / R);
		if(y < 0.0f) {
			A = -A;
		}
		A = cMath::Deg(cMath::AngleNormalizeTwoPi(A));
	}
	if(Radius != NULL) {
		*Radius = R;
	}
	if(Angle != NULL) {
		*Angle = A;
	}
}

// dVec2::Reflect
inline const dVec2 dVec2::Reflect(const dVec2 &RayDir, const dVec2 &Normal) {
	return RayDir - 2.0f * Dot(RayDir, Normal) * Normal;
}

// dVec2::Refract
inline const dVec2 dVec2::Refract(const dVec2 &RayDir, const dVec2 &Normal, const double Eta) {
	double k = 1.0f - Eta * Eta * (1.0f - cMath::Square(Dot(Normal, RayDir)));
	if(k < 0.0f) {
		return dVec2::Zero;
	}
	return Eta * RayDir - (Eta * Dot(Normal, RayDir) + cMath::Sqrt(k)) * Normal;
}

// dVec2::Truncate : (const double)
inline void dVec2::Truncate(const double MaxLen) {
	if(MaxLen <= 0) {
		SetZero();
		return;
	}
	double l = Length();
	if(l > MaxLen) {
		double il = MaxLen / l;
		x *= il;
		y *= il;
	}
}

// dVec2::Truncate : (const dVec2 &, ...)
inline const dVec2 dVec2::Truncate(const dVec2 &u, const double MaxLen) {
	if(MaxLen <= 0) {
		return dVec2::Zero;
	}
	double l = u.Length();
	if(l > MaxLen) {
		double il = MaxLen / l;
		return dVec2(u.x * il, u.y * il);
	}
	return u;
}

// dVec2::GetDimension : int() const
inline int dVec2::GetDimension() const {
	return 2;
}

// dVec2::ToDoublePtr : const double * () const
inline const double * dVec2::ToDoublePtr() const {
	return (const double *)&x;
}

// dVec2::ToDoublePtr : double * ()
inline double * dVec2::ToDoublePtr() {
	return (double *)&x;
}

// dVec2::operator cVec<Type, 2>
template<class Type>
dVec2::operator cVec<Type, 2> () const {
	return cVec<Type, 2>( (Type)x, (Type)y );
}

// dVec2::Max : const dVec2(const dVec2 &, const dVec2 &)
inline const dVec2 dVec2::Max(const dVec2 &u, const dVec2 &v) {
	dVec2 r;
	r.x = u.x > v.x ? u.x : v.x;
	r.y = u.y > v.y ? u.y : v.y;
	return r;
}

// dVec2::Min : const dVec2(const dVec2 &, const dVec2 &)
inline const dVec2 dVec2::Min(const dVec2 &u, const dVec2 &v) {
	dVec2 r;
	r.x = u.x < v.x ? u.x : v.x;
	r.y = u.y < v.y ? u.y : v.y;
	return r;
}

// dVec2::Ccw : double(const dVec2 &, const dVec2 &)
inline double dVec2::Ccw(const dVec2 &u, const dVec2 &v) {
	return u.x * v.y - u.y * v.x;
}

// dVec2::Clamp : const dVec2(const dVec2 &, const dVec2 &, const dVec2 &)
inline const dVec2 dVec2::Clamp(const dVec2 &Value, const dVec2 &Lo, const dVec2 &Hi) {
	dVec2 r;
	r.x = Value.x < Lo.x ? Lo.x : (Value.x > Hi.x ? Hi.x : Value.x);
	r.y = Value.y < Lo.y ? Lo.y : (Value.y > Hi.y ? Hi.y : Value.y);
	return r;
}

// dVec2::Distance : double(const dVec2 &, const dVec2 &)
inline double dVec2::Distance(const dVec2 &p0, const dVec2 &p1) {
	double dx = p0.x - p1.x;
	double dy = p0.y - p1.y;
	return cMath::Sqrt(dx * dx + dy * dy);
}

// dVec2::DistanceSq : double(const dVec2 &, const dVec2 &)
inline double dVec2::DistanceSq(const dVec2 &p0, const dVec2 &p1) {
	double dx = p0.x - p1.x;
	double dy = p0.y - p1.y;
	return dx * dx + dy * dy;
}

// dVec2::Dot : double(const dVec2 &, const dVec2 &)
inline double dVec2::Dot(const dVec2 &u, const dVec2 &v) {
	return u.x * v.x + u.y * v.y;
}

// dVec2::Length : double(const dVec2 &)
inline double dVec2::Length(const dVec2 &u) {
	return cMath::Sqrt(u.x * u.x + u.y * u.y);
}

// dVec2::LengthSq : double(const dVec2 &)
inline double dVec2::LengthSq(const dVec2 &u) {
	return u.x * u.x + u.y * u.y;
}

// dVec2::Lerp : const dVec2(const dVec2 &, const dVec2 &, const double)
inline const dVec2 dVec2::Lerp(const dVec2 &u, const dVec2 &v, const double s) {
	dVec2 r;
	r.x = u.x + s * (v.x - u.x);
	r.y = u.y + s * (v.y - u.y);
	return r;
}

// dVec2::Lerp05 : const dVec2(const dVec2 &, const dVec2 &)
inline const dVec2 dVec2::Lerp05(const dVec2 &u, const dVec2 &v) {
	dVec2 r;
	r.x = (u.x + v.x) * 0.5f;
	r.y = (u.y + v.y) * 0.5f;
	return r;
}

// dVec2::PerpCw : const dVec2(const dVec2 &)
inline const dVec2 dVec2::PerpCw(const dVec2 &u) {
	return dVec2(u.y, -u.x);
}

// dVec2::ToPerpCw : () const
inline const dVec2 dVec2::ToPerpCw() const {
	return dVec2(y, -x);
}

// dVec2::PerpCcw : const dVec2(const dVec2 &)
inline const dVec2 dVec2::PerpCcw(const dVec2 &u) {
	return dVec2(-u.y, u.x);
}

// dVec2::PerpCcw : () const
inline const dVec2 dVec2::ToPerpCcw() const {
	return dVec2(-y, x);
}

// dVec2::ToNormal : const dVec2 () const
inline const dVec2 dVec2::ToNormal() const {
	dVec2 u(*this);
	u.Normalize();
	return u;
}

// dVec2::Rand
inline const dVec2 dVec2::Rand(const dVec2 &Lo, const dVec2 &Hi) {
	return dVec2(cMath::dRand(Lo.x, Hi.x), cMath::dRand(Lo.y, Hi.y));
}
