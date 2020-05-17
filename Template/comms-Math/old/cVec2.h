#pragma once

template<class Type, int Dim>
struct cVec;

//*****************************************************************************
// cVec2
//*****************************************************************************
class COMMS_ALIASING cVec2 {
public:
	float x;
	float y;

	cVec2();
	explicit cVec2(const float S);
	cVec2(const float X, const float Y);

	void Copy(const float *Src);
	void SetZero();
	void SetOne();
	void Set(const float S);
	void Set(const float X, const float Y);

	float operator [] (const int index) const;
	float & operator [] (const int index);

	const cVec2 operator - () const;

	void operator += (const cVec2 &);
	void operator -= (const cVec2 &);
	void operator *= (const cVec2 &);
	void operator *= (const float);
	void operator /= (const cVec2 &);
	void operator /= (const float);

	void Transform(const cMat3 &); // (x, y, 0)
	void operator *= (const cMat3 &);
	
	void TransformCoordinate(const cMat4 &); // (x, y, 0, 1), projects the result back into w = 1
	void TransformNormal(const cMat4 &); // (x, y, 0)

	const cVec2 operator + (const cVec2 &) const;
	const cVec2 operator - (const cVec2 &) const;
	const cVec2 operator * (const cVec2 &) const;
	const cVec2 operator * (const float) const;
	friend const cVec2 operator * (const float, const cVec2 &);
	const cVec2 operator / (const cVec2 &) const;
	const cVec2 operator / (const float) const;
	friend const cVec2 operator / (const float, const cVec2 &);

	static const cVec2 Transform(const cVec2 &, const cMat3 &); // (x, y, 0)
	const cVec2 operator * (const cMat3 &) const;
	
	static const cVec4 Transform(const cVec2 &, const cMat4 &); // (x, y, 0, 1)
	static const cVec2 TransformCoordinate(const cVec2 &, const cMat4 &); // (x, y, 0, 1), projects the result back into w = 1
	static const cVec2 TransformNormal(const cVec2 &, const cMat4 &); // (x, y, 0, 0)

	bool operator == (const cVec2 &) const;
	bool operator != (const cVec2 &) const;
	static bool Equals(const cVec2 &, const cVec2 &, const float Eps = cMath::Epsilon);

	float Length() const;
	float LengthSq() const;
	float Normalize();
	float NormalizeSafe(const cVec2 &Fallback);
	bool IsValid() const;
	bool IsNormalized(const float Eps = cMath::Epsilon) const;
	bool IsZero(const float Eps = cMath::Epsilon) const;
	
	static const cVec2 Round(const cVec2 &);
	const cVec2 ToRound() const;
	void Round();

	static const cVec2 Abs(const cVec2 &);
	static float Angle(const cVec2 &, const cVec2 &);
	static float AreaSigned(const cVec2 &t0, const cVec2 &t1, const cVec2 &t2);
	static float Ccw(const cVec2 &, const cVec2 &);
	static const cVec2 Clamp(const cVec2 &Value, const cVec2 &Lo, const cVec2 &Hi);
	static float Distance(const cVec2 &, const cVec2 &);
	static float DistanceSq(const cVec2 &, const cVec2 &);
	static float Dot(const cVec2 &, const cVec2 &);
	static float Length(const cVec2 &);
	static float LengthSq(const cVec2 &);
	static const cVec2 Lerp(const cVec2 &, const cVec2 &, const float);
	static const cVec2 Lerp05(const cVec2 &, const cVec2 &);
	static const cVec2 Max(const cVec2 &, const cVec2 &);
	static const cVec2 Min(const cVec2 &, const cVec2 &);
	static const cVec2 Normalize(const cVec2 &);
	static const cVec2 NormalizeSafe(const cVec2 &Src, const cVec2 &Fallback);
	static const cVec2 PerpCw(const cVec2 &);
	static const cVec2 PerpCcw(const cVec2 &);
	static const cVec2 Reflect(const cVec2 &RayDir, const cVec2 &Normal);
	static const cVec2 Refract(const cVec2 &RayDir, const cVec2 &Normal, const float Eta);
	static const cVec2 Truncate(const cVec2 &u, const float MaxLength);
	void Truncate(const float MaxLength);
	static const cVec2 RandRange1();
	static const cVec2 RandNormal();
	static const cVec2 Rand(const cVec2 &Lo, const cVec2 &Hi);
	__inline float distance2(const cVec2&);
	__inline float distance(const cVec2&);
	
	float DistanceToLineSegSq(const cVec2 &A, const cVec2 &B, float *pScale = NULL) const;
	static bool SegIntersection(const cVec2 &L0, const cVec2 &L1, const cVec2 &R0, const cVec2 &R1, float *l = NULL, float *r = NULL);
	
	static const cVec2 FromBaryCentric(const cVec2 &t0, const cVec2 &t1, const cVec2 &t2, const float u, const float v);
	static const cVec2 FromPolar(const float Radius, const float Angle);

	static const cVec2 Zero;
	static const cVec2 One;
	static const cVec2 Infinity;
	static const cVec2 AxisX;
	static const cVec2 AxisY;
	static const cVec2 AxisNegX;
	static const cVec2 AxisNegY;
	
	int GetDimension() const;

	const float * ToFloatPtr() const;
	float * ToFloatPtr();

	template<class Type>
	operator cVec<Type, 2> () const;

	void ToPolar(float *Radius, float *Angle) const;
	float ToBaryCentric(const cVec2 &t0, const cVec2 &t1, const cVec2 &t2, float &u, float &v) const;
	bool IsInsideTri(const cVec2 &t0, const cVec2 &t1, const cVec2 &t2) const;

	const cStr ToString(const int Prec = 2) const;
	friend cStr & operator << (cStr &, const cVec2 &);

	const cVec2 ToNormal() const;

	const cVec2 ToPerpCw() const;
	const cVec2 ToPerpCcw() const;
};

// cVec2.ctor : ()
inline cVec2::cVec2() {
}

// cVec2.ctor : (const float)
inline cVec2::cVec2(const float S)
: x(S), y(S) {}

// cVec2.ctor : (const float, const float)
inline cVec2::cVec2(const float X, const float Y)
: x(X), y(Y) {}

// cVec2::Copy
inline void cVec2::Copy(const float *Src) {
	cAssert(Src != NULL);
	x = Src[0];
	y = Src[1];
}

// cVec2::SetZero
inline void cVec2::SetZero() {
	x = y = 0.0f;
}

// cVec2::SetOne
inline void cVec2::SetOne() {
	x = y = 1.0f;
}

// cVec2::Set : void (const float)
inline void cVec2::Set(const float S) {
	x = y = S;
}

// cVec2::Set : void (const float, const float)
inline void cVec2::Set(const float X, const float Y) {
	x = X;
	y = Y;
}

// cVec2::operator [] : float(const int) const
inline float cVec2::operator [] (const int index) const {
	cAssert(index >= 0 && index < 2);
	return (&x)[index];
}

// cVec2::operator [] : float & (const int)
inline float & cVec2::operator [] (const int index) {
	cAssert(index >= 0 && index < 2);
	return (&x)[index];
}

// cVec2::operator - : const cVec2 () const
inline const cVec2 cVec2::operator - () const {
	return cVec2(-x, -y);
}

// cVec2::operator += : void (const cVec2 &)
inline void cVec2::operator += (const cVec2 &u) {
	x += u.x;
	y += u.y;
}

// cVec2::operator -= : void (const cVec2 &)
inline void cVec2::operator -= (const cVec2 &u) {
	x -= u.x;
	y -= u.y;
}

// cVec2::operator *= : void (const cVec2 &)
inline void cVec2::operator *= (const cVec2 &u) {
	x *= u.x;
	y *= u.y;
}

// cVec2::operator *= : void (const float)
inline void cVec2::operator *= (const float s) {
	x *= s;
	y *= s;
}

// cVec2::operator /= : void (const cVec2 &)
inline void cVec2::operator /= (const cVec2 &u) {
	x /= u.x;
	y /= u.y;
}

// cVec2::operator /= : void (const float)
inline void cVec2::operator /= (const float s) {
	float is = 1.0f / s;
	x *= is;
	y *= is;
}

// cVec2::operator + : const cVec2 (const cVec2 &) const
inline const cVec2 cVec2::operator + (const cVec2 &u) const {
	return cVec2(x + u.x, y + u.y);
}

// cVec2::operator - : const cVec2 (const cVec2 &) const
inline const cVec2 cVec2::operator - (const cVec2 &u) const {
	return cVec2(x - u.x, y - u.y);
}

// cVec2::operator * : const cVec2 (const cVec2 &) const
inline const cVec2 cVec2::operator * (const cVec2 &u) const {
	return cVec2(x * u.x, y * u.y);
}

// cVec2::operator * : const cVec2 (const float) const
inline const cVec2 cVec2::operator * (const float s) const {
	return cVec2(x * s, y * s);
}

// cVec2::friend operator * : const cVec2 (const float, const cVec2 &)
inline const cVec2 operator * (const float s, const cVec2 &u) {
	return cVec2(s * u.x, s * u.y);
}

// cVec2::operator / : const cVec2 (const cVec2 &) const
inline const cVec2 cVec2::operator / (const cVec2 &u) const {
	return cVec2(x / u.x, y / u.y);
}

// cVec2::operator / : const cVec2 (const float) const
inline const cVec2 cVec2::operator / (const float s) const {
	float is = 1.0f / s;
	return cVec2(x * is, y * is);
}

// cVec2::friend operator / : const cVec2 (const float, const cVec2 &)
inline const cVec2 operator / (const float s, const cVec2 &u) {
	return cVec2(s / u.x, s / u.y);
}

// cVec2::operator == : bool(const cVec2 &) const
inline bool cVec2::operator == (const cVec2 &u) const {
	return x == u.x && y == u.y;
}

// cVec2::operator != : bool(const cVec2 &) const
inline bool cVec2::operator != (const cVec2 &u) const {
	return x != u.x || y != u.y;
}

// cVec2::Equals : bool(const cVec2 &, const cVec2 &, const float)
inline bool cVec2::Equals(const cVec2 &u, const cVec2 &v, const float Eps) {
	if(cMath::Abs(u.x - v.x) > Eps) return false;
	if(cMath::Abs(u.y - v.y) > Eps) return false;
	return true;
}

// cVec2::Length : float() const
inline float cVec2::Length() const {
	return cMath::Sqrt(x * x + y * y);
}

// cVec2::LengthSq : float() const
inline float cVec2::LengthSq() const {
	return x * x + y * y;
}

// cVec2::Normalize : ()
inline float cVec2::Normalize() {
	const float l = Length();
	if(l > 0.0f) {
		const float il = 1.0f / l;
		x *= il;
		y *= il;
	}
	return l;
}

// cVec2::NormalizeSafe
inline float cVec2::NormalizeSafe(const cVec2 &Fallback) {
	const float l = Length();
	if(l > 0.0f) {
		const float il = 1.0f / l;
		x *= il;
		y *= il;
		cAssert(IsNormalized());
		return l;
	}
	*this = Fallback;
	cAssert(IsNormalized());
	return 0.0f;
}

// cVec2::IsValid : bool () const
inline bool cVec2::IsValid() const {
	return cMath::IsValid(x) && cMath::IsValid(y);
}

// cVec2::IsNormalized : bool(const float) const
inline bool cVec2::IsNormalized(const float Eps) const {
	return cMath::IsOne(LengthSq(), Eps);
}

// cVec2::IsZero : bool(const float) const
inline bool cVec2::IsZero(const float Eps) const {
	if(!cMath::IsZero(x, Eps)) return false;
	if(!cMath::IsZero(y, Eps)) return false;
	return true;
}

// cVec2::Normalize : const cVec2(const cVec2 &)
inline const cVec2 cVec2::Normalize(const cVec2 &u) {
	cVec2 t = u;
	t.Normalize();
	return t;
}

// cVec2::NormalizeSafe : (const cVec2 &, const cVec2 &)
inline const cVec2 cVec2::NormalizeSafe(const cVec2 &Src, const cVec2 &Fallback) {
	cVec2 t = Src;
	t.NormalizeSafe(Fallback);
	return t;
}

// cVec2::FromPolar
inline const cVec2 cVec2::FromPolar(const float Radius, const float Angle) {
	float A = cMath::Rad(Angle);
	return cVec2(Radius * cMath::Cos(A), Radius * cMath::Sin(A));
}

// cVec2::FromBaryCentric : cVec2(const cVec2 &, const cVec2 &, const cVec2 &, const float, const float)
inline const cVec2 cVec2::FromBaryCentric(const cVec2 &t0, const cVec2 &t1, const cVec2 &t2, const float u, const float v) {
	return t0 + u * (t1 - t0) + v * (t2 - t0);
}

// cVec2::Abs : const cVec2(const cVec2 &)
inline const cVec2 cVec2::Abs(const cVec2 &u) {
	return cVec2(cMath::Abs(u.x), cMath::Abs(u.y));
}

// cVec2::Round
inline const cVec2 cVec2::Round(const cVec2 &u) {
	return cVec2(cMath::Round(u.x), cMath::Round(u.y));
}

// cVec2::ToRound
inline const cVec2 cVec2::ToRound() const {
	return cVec2(cMath::Round(x), cMath::Round(y));
}

// cVec2::Round
inline void cVec2::Round() {
	x = cMath::Round(x);
	y = cMath::Round(y);
}

// cVec2::Angle : float(const cVec2 &, const cVec2 &)
inline float cVec2::Angle(const cVec2 &u, const cVec2 &v) {
	const float d = u.x * v.y - v.x * u.y;
	const float s = d != 0.0f ? cMath::Sign(d) : 1.0f;
	const float D = cVec2::Dot(u, v);
	const float ll = u.Length() * v.Length();
	return s * cMath::Deg(cMath::ACos(D / ll));
}

// cVec2::AreaSigned : float(const cVec2 &, const cVec2 &, const cVec2 &)
inline float cVec2::AreaSigned(const cVec2 &t0, const cVec2 &t1, const cVec2 &t2) {
	const cVec2 e1 = t1 - t0;
	const cVec2 e2 = t2 - t0;
	return Ccw(e1, e2) * 0.5f;
}

// cVec2::ToBaryCentric : void(const cVec2 &, const cVec2 &, const cVec2 &, float &, float &) const
inline float cVec2::ToBaryCentric(const cVec2 &t0, const cVec2 &t1, const cVec2 &t2, float &u, float &v) const {
	const float A = AreaSigned(t0, t1, t2);
	if(A != 0) {
		const float iA = 1.0f / A;
		u = AreaSigned(t0, *this, t2) * iA;
		v = AreaSigned(t0, t1, *this) * iA;
	} else {
		u = v = 0.0f;
	}
	return A;
}

// cVec2::IsInsideTri : bool(const cVec2 &, const cVec2 &, const cVec2 &) const
inline bool cVec2::IsInsideTri(const cVec2 &t0, const cVec2 &t1, const cVec2 &t2) const {
	float u, v;
	ToBaryCentric(t0, t1, t2, u, v);
	return u >= 0.0f && v >= 0.0f && 1.0f - u - v >= 0.0f;
}

// cVec2::ToPolar
inline void cVec2::ToPolar(float *Radius, float *Angle) const {
	float R = Length(), A = 0.0f;
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

// cVec2::Reflect
inline const cVec2 cVec2::Reflect(const cVec2 &RayDir, const cVec2 &Normal) {
	return RayDir - 2.0f * Dot(RayDir, Normal) * Normal;
}

// cVec2::Refract
inline const cVec2 cVec2::Refract(const cVec2 &RayDir, const cVec2 &Normal, const float Eta) {
	float k = 1.0f - Eta * Eta * (1.0f - cMath::Square(Dot(Normal, RayDir)));
	if(k < 0.0f) {
		return cVec2::Zero;
	}
	return Eta * RayDir - (Eta * Dot(Normal, RayDir) + cMath::Sqrt(k)) * Normal;
}

// cVec2::Truncate : (const float)
inline void cVec2::Truncate(const float MaxLen) {
	if(MaxLen <= 0) {
		SetZero();
		return;
	}
	float l = Length();
	if(l > MaxLen) {
		float il = MaxLen / l;
		x *= il;
		y *= il;
	}
}

// cVec2::Truncate : (const cVec2 &, ...)
inline const cVec2 cVec2::Truncate(const cVec2 &u, const float MaxLen) {
	if(MaxLen <= 0) {
		return cVec2::Zero;
	}
	float l = u.Length();
	if(l > MaxLen) {
		float il = MaxLen / l;
		return cVec2(u.x * il, u.y * il);
	}
	return u;
}

// cVec2::GetDimension : int() const
inline int cVec2::GetDimension() const {
	return 2;
}

// cVec2::ToFloatPtr : const float * () const
inline const float * cVec2::ToFloatPtr() const {
	return (const float *)&x;
}

// cVec2::ToFloatPtr : float * ()
inline float * cVec2::ToFloatPtr() {
	return (float *)&x;
}

// cVec2::operator cVec<Type, 2>
template<class Type>
cVec2::operator cVec<Type, 2> () const {
	return cVec<Type, 2>( (Type)x, (Type)y );
}

// cVec2::Max : const cVec2(const cVec2 &, const cVec2 &)
inline const cVec2 cVec2::Max(const cVec2 &u, const cVec2 &v) {
	cVec2 r;
	r.x = u.x > v.x ? u.x : v.x;
	r.y = u.y > v.y ? u.y : v.y;
	return r;
}

// cVec2::Min : const cVec2(const cVec2 &, const cVec2 &)
inline const cVec2 cVec2::Min(const cVec2 &u, const cVec2 &v) {
	cVec2 r;
	r.x = u.x < v.x ? u.x : v.x;
	r.y = u.y < v.y ? u.y : v.y;
	return r;
}

// cVec2::Ccw : float(const cVec2 &, const cVec2 &)
inline float cVec2::Ccw(const cVec2 &u, const cVec2 &v) {
	return u.x * v.y - u.y * v.x;
}

// cVec2::Clamp : const cVec2(const cVec2 &, const cVec2 &, const cVec2 &)
inline const cVec2 cVec2::Clamp(const cVec2 &Value, const cVec2 &Lo, const cVec2 &Hi) {
	cVec2 r;
	r.x = Value.x < Lo.x ? Lo.x : (Value.x > Hi.x ? Hi.x : Value.x);
	r.y = Value.y < Lo.y ? Lo.y : (Value.y > Hi.y ? Hi.y : Value.y);
	return r;
}

// cVec2::Distance : float(const cVec2 &, const cVec2 &)
inline float cVec2::Distance(const cVec2 &p0, const cVec2 &p1) {
	float dx = p0.x - p1.x;
	float dy = p0.y - p1.y;
	return cMath::Sqrt(dx * dx + dy * dy);
}
float cVec2::distance2(const cVec2& pt) {
	return DistanceSq(*this, pt);
}
float cVec2::distance(const cVec2& pt) {
	return Distance(*this, pt);
}
// cVec2::DistanceSq : float(const cVec2 &, const cVec2 &)
inline float cVec2::DistanceSq(const cVec2 &p0, const cVec2 &p1) {
	float dx = p0.x - p1.x;
	float dy = p0.y - p1.y;
	return dx * dx + dy * dy;
}

// cVec2::Dot : float(const cVec2 &, const cVec2 &)
inline float cVec2::Dot(const cVec2 &u, const cVec2 &v) {
	return u.x * v.x + u.y * v.y;
}

// cVec2::Length : float(const cVec2 &)
inline float cVec2::Length(const cVec2 &u) {
	return cMath::Sqrt(u.x * u.x + u.y * u.y);
}

// cVec2::LengthSq : float(const cVec2 &)
inline float cVec2::LengthSq(const cVec2 &u) {
	return u.x * u.x + u.y * u.y;
}

// cVec2::Lerp : const cVec2(const cVec2 &, const cVec2 &, const float)
inline const cVec2 cVec2::Lerp(const cVec2 &u, const cVec2 &v, const float s) {
	cVec2 r;
	r.x = u.x + s * (v.x - u.x);
	r.y = u.y + s * (v.y - u.y);
	return r;
}

// cVec2::Lerp05 : const cVec2(const cVec2 &, const cVec2 &)
inline const cVec2 cVec2::Lerp05(const cVec2 &u, const cVec2 &v) {
	cVec2 r;
	r.x = (u.x + v.x) * 0.5f;
	r.y = (u.y + v.y) * 0.5f;
	return r;
}

// cVec2::PerpCw : const cVec2(const cVec2 &)
inline const cVec2 cVec2::PerpCw(const cVec2 &u) {
	return cVec2(u.y, -u.x);
}

// cVec2::ToPerpCw : () const
inline const cVec2 cVec2::ToPerpCw() const {
	return cVec2(y, -x);
}

// cVec2::PerpCcw : const cVec2(const cVec2 &)
inline const cVec2 cVec2::PerpCcw(const cVec2 &u) {
	return cVec2(-u.y, u.x);
}

// cVec2::PerpCcw : () const
inline const cVec2 cVec2::ToPerpCcw() const {
	return cVec2(-y, x);
}

// cVec2::ToNormal : const cVec2 () const
inline const cVec2 cVec2::ToNormal() const {
	cVec2 u(*this);
	u.Normalize();
	return u;
}

// cVec2::Rand
inline const cVec2 cVec2::Rand(const cVec2 &Lo, const cVec2 &Hi) {
	return cVec2(cMath::Rand(Lo.x, Hi.x), cMath::Rand(Lo.y, Hi.y));
}
