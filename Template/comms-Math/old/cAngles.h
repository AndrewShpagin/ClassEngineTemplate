#pragma once

//*****************************************************************************
// cAngles
//*****************************************************************************
class cAngles {
public:
	float Pitch;	// X, Up / Down
	float Yaw;		// Y, Left / Right
	float Roll;		// Z, Fall over
	
	cAngles();
	cAngles(const float Pitch, const float Yaw, const float Roll);
	
	void Set(const float Pitch, const float Yaw, const float Roll);
	void SetZero();
	void Copy(const float *Src);

	float & operator [] (const int Index);
	float operator [] (const int Index) const;

	const cAngles operator - () const;

	void operator += (const cAngles &);
	void operator -= (const cAngles &);
	void operator *= (const float);
	void operator /= (const float);
	
	const cAngles operator + (const cAngles &) const;
	const cAngles operator - (const cAngles &) const;
	const cAngles operator * (const float) const;
	friend const cAngles operator * (const float, const cAngles &);
	const cAngles operator / (const float) const;

	bool operator == (const cAngles &) const;
	bool operator != (const cAngles &) const;
	static bool Equals(const cAngles &, const cAngles &, const float Eps = cMath::Epsilon);
	
	float Length() const;
	float LengthSq() const;
	
	void Normalize360();
	void Normalize180();
	void Round();
	
	static cAngles Clamp(const cAngles &u, const cAngles &Min, const cAngles &Max);
	static cAngles Rand(const cAngles &Range);
	static float Angle(const cAngles &l, const cAngles &r);
	static float Distance(const cAngles &l, const cAngles &r) {
		return Angle(l, r);
	}
	
	static const cAngles Zero;
	
	void ToVectors(cVec3 *Forward, cVec3 *Right = NULL, cVec3 *Up = NULL) const;
	const cVec3 ToForward() const;
	const cVec3 ToRight() const;
	const cVec3 ToUp() const;

	const cMat3 ToMat3() const;
	const cMat4 ToMat4() const;
	
	const cQuat ToQuat() const;
//	cRotation ToRotation() const;

	
	//	cVec3 ToAngularVelocity() const;

	int GetDimension() const {
		return 3;
	}

	const float * ToFloatPtr() const;
	float * ToFloatPtr();

	const cStr ToString(const int Prec = 2) const;

	static void EnsureShortestPath(cAngles *l, cAngles *r);
	static const cAngles Lerp(const cAngles &l, const cAngles &r, const float s);
};

// cAngles.ctor : ()
inline cAngles::cAngles() {
}

// cAngles.ctor : (const float, ...)
inline cAngles::cAngles(const float Pitch, const float Yaw, const float Roll)
: Pitch(Pitch), Yaw(Yaw), Roll(Roll) {}

// cAngles::Set
inline void cAngles::Set(const float Pitch, const float Yaw, const float Roll) {
	this->Pitch = Pitch;
	this->Yaw = Yaw;
	this->Roll = Roll;
}

// cAngles::SetZero
inline void cAngles::SetZero() {
	Pitch = Yaw = Roll = 0.0f;
}

// cAngles::operator [] : float & (...)
inline float & cAngles::operator [] (const int Index) {
	cAssert(Index >= 0 && Index < 3);
	return (&Pitch)[Index];
}

// cAngles::operator [] : float (...) const
inline float cAngles::operator [] (const int Index) const {
	cAssert(Index >= 0 && Index < 3);
	return (&Pitch)[Index];
}

// cAngles::operator -
inline const cAngles cAngles::operator - () const {
	return cAngles(-Pitch, -Yaw, -Roll);
}

// cAngles::operator +=
inline void cAngles::operator += (const cAngles &r) {
	Pitch += r.Pitch;
	Yaw += r.Yaw;
	Roll += r.Roll;
}

// cAngles::operator -=
inline void cAngles::operator -= (const cAngles &r) {
	Pitch -= r.Pitch;
	Yaw -= r.Yaw;
	Roll -= r.Roll;
}

// cAngles::operator *=
inline void cAngles::operator *= (const float s) {
	Pitch *= s;
	Yaw *= s;
	Roll *= s;
}

// cAngles::operator /=
inline void cAngles::operator /= (const float s) {
	const float is = 1.0f / s;
	Pitch *= is;
	Yaw *= is;
	Roll *= is;
}

// cAngles::operator + : const cAngles (const cAngles &) const
inline const cAngles cAngles::operator + (const cAngles &r) const {
	return cAngles(Pitch + r.Pitch, Yaw + r.Yaw, Roll + r.Roll);
}

// cAngles::operator - : const cAngles (const cAngles &) const
inline const cAngles cAngles::operator - (const cAngles &r) const {
	return cAngles(Pitch - r.Pitch, Yaw - r.Yaw, Roll - r.Roll);
}

// cAngles::operator * : const cAngles (const float) const
inline const cAngles cAngles::operator * (const float s) const {
	return cAngles(Pitch * s, Yaw * s, Roll * s);
}

// cAngles::friend operator * : const cAngles (const float, const cAngles &)
inline const cAngles operator * (const float s, const cAngles &r) {
	return cAngles(s * r.Pitch, s * r.Yaw, s * r.Roll);
}

// cAngles::operator / : const cAngles (const float) const
inline const cAngles cAngles::operator / (const float s) const {
	const float is = 1.0f / s;
	return cAngles(Pitch * is, Yaw * is, Roll * is);
}

// cAngles::operator == : bool (const cAngles &) const
inline bool cAngles::operator == (const cAngles &r) const {
	return Pitch == r.Pitch && Yaw == r.Yaw && Roll == r.Roll;
}

// cAngles::operator != : bool (const cAngles &) const
inline bool cAngles::operator != (const cAngles &r) const {
	return Pitch != r.Pitch || Yaw != r.Yaw || Roll != r.Roll;
}

// cAngles::Equals : bool(const cAngles &, const cAngles &, const float)
inline bool cAngles::Equals(const cAngles &l, const cAngles &r, const float Eps) {
	if(cMath::Abs(l.Pitch - r.Pitch) > Eps) {
		return false;
	}
	if(cMath::Abs(l.Yaw - r.Yaw) > Eps) {
		return false;
	}
	if(cMath::Abs(l.Roll - r.Roll) > Eps) {
		return false;
	}
	return true;
}

// cAngles::Length : float() const
inline float cAngles::Length() const {
	return cMath::Sqrt(Pitch * Pitch + Yaw * Yaw + Roll * Roll);
}

// cAngles::LengthSq : float() const
inline float cAngles::LengthSq() const {
	return Pitch * Pitch + Yaw * Yaw + Roll * Roll;
}

// cAngles::Round : ()
inline void cAngles::Round() {
	Pitch = cMath::Round(Pitch);
	Yaw = cMath::Round(Yaw);
	Roll = cMath::Round(Roll);
}

// cAngles::Clamp : cAngles(const cAngles &, const cAngles &, const cAngles &) const
inline cAngles cAngles::Clamp(const cAngles &u, const cAngles &Min, const cAngles &Max) {
	cAngles r;
	r.Pitch = u.Pitch < Min.Pitch ? Min.Pitch : (u.Pitch > Max.Pitch ? Max.Pitch : u.Pitch);
	r.Yaw = u.Yaw < Min.Yaw ? Min.Yaw : (u.Yaw > Max.Yaw ? Max.Yaw : u.Yaw);
	r.Roll = u.Roll < Min.Roll ? Min.Roll : (u.Roll > Max.Roll ? Max.Roll : u.Roll);
	return r;
}

// cAngles::Rand : cAngles(const cAngles &)
inline cAngles cAngles::Rand(const cAngles &Range) {
	float Pitch = Range.Pitch * cMath::RandRange1();
	float Yaw = Range.Yaw * cMath::RandRange1();
	float Roll = Range.Roll * cMath::RandRange1();
	return cAngles(Pitch, Yaw, Roll);
}

// cAngles::Angle : float (const cAngles &, const cAngles &)
inline float cAngles::Angle(const cAngles &l, const cAngles &r) {
	return cVec3::Angle(l.ToForward(), r.ToForward());
}

// cAngles::ToFloatPtr : const float * () const
inline const float * cAngles::ToFloatPtr() const {
	return &Pitch;
}

// cAngles::ToFloatPtr : float * ()
inline float * cAngles::ToFloatPtr() {
	return &Pitch;
}
// cAngles::Copy
inline void cAngles::Copy(const float *Src) {
	cAssert(Src != NULL);
	Pitch = Src[0];
	Yaw = Src[1];
	Roll = Src[2];
}

// cAngles::Lerp
inline const cAngles cAngles::Lerp(const cAngles &l, const cAngles &r, const float s) {
	cAngles L;
	L.Pitch = cMath::Lerp(l.Pitch, r.Pitch, s);
	L.Yaw = cMath::Lerp(l.Yaw, r.Yaw, s);
	L.Roll = cMath::Lerp(l.Roll, r.Roll, s);
	return L;
}




::std::ostream& operator<<( ::std::ostream&,  const cAngles& );
