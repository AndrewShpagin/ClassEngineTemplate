#pragma once

//*****************************************************************************
// cMat3
//*****************************************************************************
class cMat3 {
public:
	enum EZeroCtor		{ ZeroCtor };
	enum EIdentityCtor	{ IdentityCtor };
	enum ERowsCtor		{ RowsCtor };
	enum EColsCtor		{ ColsCtor };
	
	cMat3();
	cMat3(const EZeroCtor);
	cMat3(const EIdentityCtor);
	cMat3(const ERowsCtor, const cVec3 &Row0, const cVec3 &Row1, const cVec3 &Row2);
	cMat3(const EColsCtor, const cVec3 &Col0, const cVec3 &Col1, const cVec3 &Col2);
	cMat3(const float _00, const float _01, const float _02,
		const float _10, const float _11, const float _12,
		const float _20, const float _21, const float _22);
	
	void Copy(const float *Float9);
	void CopyTransposed(const float *Float9);

	void SetZero();
	void SetIdentity();

	const cVec3 & GetRow(const int Index) const;
	const cVec3 & GetRow0() const;
	const cVec3 & GetRow1() const;
	const cVec3 & GetRow2() const;
	
	cVec3 & Row(const int Index);
	cVec3 & Row0();
	cVec3 & Row1();
	cVec3 & Row2();

	void SetRow(const int Index, const cVec3 &);
	void SetRow0(const cVec3 &);
	void SetRow1(const cVec3 &);
	void SetRow2(const cVec3 &);

	void SetRow(const int Index, const float X, const float Y, const float Z);
	void SetRow0(const float X, const float Y, const float Z);
	void SetRow1(const float X, const float Y, const float Z);
	void SetRow2(const float X, const float Y, const float Z);

	const cVec3 GetCol(const int Index) const;
	const cVec3 GetCol0() const;
	const cVec3 GetCol1() const;
	const cVec3 GetCol2() const;

	void SetCol(const int Index, const cVec3 &);
	void SetCol0(const cVec3 &);
	void SetCol1(const cVec3 &);
	void SetCol2(const cVec3 &);

	void SetCol(const int Index, const float X, const float Y, const float Z);
	void SetCol0(const float X, const float Y, const float Z);
	void SetCol1(const float X, const float Y, const float Z);
	void SetCol2(const float X, const float Y, const float Z);
	
	void SetElem(int Row, int Col, float Value);
	float GetElem(const int Row, const int Col) const;
	float & Elem(const int Row, const int Col);

	const cVec3 & operator [] (const int Row) const;
	cVec3 & operator [] (const int Row);

	float operator () (const int Row, const int Col) const;
	float & operator () (const int Row, const int Col);
	
	float Trace() const;
	float Determinant() const;
	
	bool operator == (const cMat3 &) const;
	static bool Equals(const cMat3 &, const cMat3 &, const float Eps = cMath::MatrixEpsilon);
	
	bool IsZero(const float Eps = cMath::MatrixEpsilon) const;
	bool IsIdentity(const float Eps = cMath::MatrixEpsilon) const;
	bool IsSymmetric(const float Eps = cMath::MatrixEpsilon) const;
	bool IsOrthonormal(const float Eps = cMath::MatrixEpsilon) const;

	const cMat3 operator - () const;

	void operator += (const cMat3 &R);
	void operator -= (const cMat3 &R);
	void operator *= (const cMat3 &R);
	void operator *= (const float);
	void operator /= (const float);

	const cMat3 operator + (const cMat3 &R) const;
	const cMat3 operator - (const cMat3 &R) const;
	const cMat3 operator * (const cMat3 &R) const;
	const cMat3 operator * (const float) const;
	friend const cMat3 operator * (const float, const cMat3 &);
	const cMat3 operator / (const float) const;

	void Add(const cMat3 &R);
	void Sub(const cMat3 &R);
	void Mul(const cMat3 &R);
	void Mul(const float s);
	
	static const cMat3 Add(const cMat3 &L, const cMat3 &R);
	static const cMat3 Sub(const cMat3 &L, const cMat3 &R);
	static const cMat3 Mul(const cMat3 &L, const cMat3 &R);
	static const cMat3 Mul(const cMat3 &L, const float s);
	static const cVec3 Mul(const cMat3 &L, const cVec3 &vc);

	static const cMat3 Zero;
	static const cMat3 Identity;
	
	static const cMat3 Transpose(const cMat3 &);
	void Transpose();
	
	static bool Invert(const cMat3 &Fm, cMat3 *To);
	bool Invert() { return Invert(*this, this); }

	static const cMat3 OrthoNormalize(const cMat3 &Src);
	void OrthoNormalize();

	static const cMat3 Rotation(const cVec3 &Axis, const float Angle);
	static const cMat3 RotationX(const float Angle);
	static const cMat3 RotationY(const float Angle);
	static const cMat3 RotationZ(const float Angle);
	static const cMat3 RotationXYZ(const float Pitch, const float Yaw, const float Roll);
	static const cMat3 EulerZYX(const float eulerX, const float eulerY, const float eulerZ); 
	
	static const cMat3 Scaling(const float XYZ);
	static const cMat3 Scaling(const float X, const float Y);
	static const cMat3 Scaling(const float X, const float Y, const float Z);
	static const cMat3 Scaling(const cVec2 &XY);
	static const cMat3 Scaling(const cVec3 &XYZ);
	
	const float * ToFloatPtr() const;
	float * ToFloatPtr();
	const cMat4 ToMat4() const;
	const cQuat ToQuat() const;

	void ToVectors(cVec3 *Forward, cVec3 *Right = NULL, cVec3 *Up = NULL) const;
	static const cMat3 FromVectors(const cVec3 &Forward, const cVec3 &Right, const cVec3 &Up);
	const cVec3 ToForward() const;
	const cVec3 ToRight() const;
	const cVec3 ToUp() const;

	const cAngles ToAngles() const;

private:
	cVec3 m_Rows[3];
};

// cMat3.ctor : ()
inline cMat3::cMat3() {
}

// cMat3.ctor : (const EZeroCtor)
inline cMat3::cMat3(const EZeroCtor) {
	m_Rows[0].SetZero();
	m_Rows[1].SetZero();
	m_Rows[2].SetZero();
}

// cMat3.ctor : (const EIdentityCtor)
inline cMat3::cMat3(const EIdentityCtor) {
	m_Rows[0].Set(1.0f, 0.0f, 0.0f);
	m_Rows[1].Set(0.0f, 1.0f, 0.0f);
	m_Rows[2].Set(0.0f, 0.0f, 1.0f);
}

// cMat3.ctor : (const ERowsCtor, const cVec3 &, const cVec3 &, const cVec3 &)
inline cMat3::cMat3(const ERowsCtor, const cVec3 &Row0, const cVec3 &Row1, const cVec3 &Row2) {
	m_Rows[0] = Row0;
	m_Rows[1] = Row1;
	m_Rows[2] = Row2;
}

// cMat3.ctor : (const EColsCtor, const cVec3 &, const cVec3 &, const cVec3 &)
inline cMat3::cMat3(const EColsCtor, const cVec3 &Col0, const cVec3 &Col1, const cVec3 &Col2) {
	m_Rows[0].Set(Col0.x, Col1.x, Col2.x);
	m_Rows[1].Set(Col0.y, Col1.y, Col2.y);
	m_Rows[2].Set(Col0.z, Col1.z, Col2.z);
}

// cMat3.ctor
inline cMat3::cMat3(const float _00, const float _01, const float _02,
					const float _10, const float _11, const float _12,
					const float _20, const float _21, const float _22) {
	m_Rows[0].Set(_00, _01, _02);
	m_Rows[1].Set(_10, _11, _12);
	m_Rows[2].Set(_20, _21, _22);
}

// cMat3::Copy
inline void cMat3::Copy(const float *Float9) {
	m_Rows[0].Set(Float9[0], Float9[1], Float9[2]);
	m_Rows[1].Set(Float9[3], Float9[4], Float9[5]);
	m_Rows[2].Set(Float9[6], Float9[7], Float9[8]);
}

// cMat3::CopyTransposed
inline void cMat3::CopyTransposed(const float *Float9) {
	m_Rows[0].Set(Float9[0], Float9[3], Float9[6]);
	m_Rows[1].Set(Float9[1], Float9[4], Float9[7]);
	m_Rows[2].Set(Float9[2], Float9[5], Float9[8]);
}

// cMat3::SetZero
inline void cMat3::SetZero() {
	m_Rows[0].SetZero();
	m_Rows[1].SetZero();
	m_Rows[2].SetZero();
}

// cMat3::SetIdentity
inline void cMat3::SetIdentity() {
	m_Rows[0].Set(1.0f, 0.0f, 0.0f);
	m_Rows[1].Set(0.0f, 1.0f, 0.0f);
	m_Rows[2].Set(0.0f, 0.0f, 1.0f);
}

// cMat3::GetRow : const cVec3 & (const int) const
inline const cVec3 & cMat3::GetRow(const int Index) const {
	cAssert(Index >= 0 && Index < 3);
	return m_Rows[Index];
}

// cMat3::GetRow0 : const cVec3 & () const
inline const cVec3 & cMat3::GetRow0() const {
	return m_Rows[0];
}

// cMat3::GetRow1 : const cVec3 & () const
inline const cVec3 & cMat3::GetRow1() const {
	return m_Rows[1];
}

// cMat3::GetRow2 : const cVec3 & () const
inline const cVec3 & cMat3::GetRow2() const {
	return m_Rows[2];
}

// cMat3::Row : cVec3 & (const int)
inline cVec3 & cMat3::Row(const int Index) {
	cAssert(Index >= 0 && Index < 3);
	return m_Rows[Index];
}

// cMat3::Row0 : cVec3 & ()
inline cVec3 & cMat3::Row0() {
	return m_Rows[0];
}

// cMat3::Row1 : cVec3 & ()
inline cVec3 & cMat3::Row1() {
	return m_Rows[1];
}

// cMat3::Row2 : cVec3 & ()
inline cVec3 & cMat3::Row2() {
	return m_Rows[2];
}

// cMat3::SetRow : void (const int, const cVec3 &)
inline void cMat3::SetRow(const int Index, const cVec3 &r) {
	cAssert(Index >= 0 && Index < 3);
	m_Rows[Index] = r;
}

// cMat3::SetRow0 : void (const cVec3 &)
inline void cMat3::SetRow0(const cVec3 &r) {
	m_Rows[0] = r;
}

// cMat3::SetRow1 : void (const cVec3 &)
inline void cMat3::SetRow1(const cVec3 &r) {
	m_Rows[1] = r;
}

// cMat3::SetRow2 : void (const cVec3 &)
inline void cMat3::SetRow2(const cVec3 &r) {
	m_Rows[2] = r;
}

// cMat3::SetRow : void (const int, const float, const float, const float)
inline void cMat3::SetRow(const int Index, const float X, const float Y, const float Z) {
	cAssert(Index >= 0 && Index < 3);
	m_Rows[Index].Set(X, Y, Z);
}

// cMat3::SetRow0 : void (const float, const float, const float)
inline void cMat3::SetRow0(const float X, const float Y, const float Z) {
	m_Rows[0].Set(X, Y, Z);
}

// cMat3::SetRow1 : void (const float, const float, const float)
inline void cMat3::SetRow1(const float X, const float Y, const float Z) {
	m_Rows[1].Set(X, Y, Z);
}

// cMat3::SetRow2 : void(const float, const float, const float)
inline void cMat3::SetRow2(const float X, const float Y, const float Z) {
	m_Rows[2].Set(X, Y, Z);
}

// cMat3::GetCol : const cVec3 (const int) const
inline const cVec3 cMat3::GetCol(const int Index) const {
	cAssert(Index >= 0 && Index < 3);
	return cVec3(m_Rows[0][Index], m_Rows[1][Index], m_Rows[2][Index]);
}

// cMat3::GetCol0 : const cVec3 () const
inline const cVec3 cMat3::GetCol0() const {
	return cVec3(m_Rows[0].x, m_Rows[1].x, m_Rows[2].x);
}

// cMat3::GetCol1 : const cVec3 () const
inline const cVec3 cMat3::GetCol1() const {
	return cVec3(m_Rows[0].y, m_Rows[1].y, m_Rows[2].y);
}

// cMat3::GetCol2 : const cVec3 () const
inline const cVec3 cMat3::GetCol2() const {
	return cVec3(m_Rows[0].z, m_Rows[1].z, m_Rows[2].z);
}

// cMat3::SetCol : void (const int, const cVec3 &)
inline void cMat3::SetCol(const int Index, const cVec3 &u) {
	cAssert(Index >= 0 && Index < 3);
	m_Rows[0][Index] = u.x;
	m_Rows[1][Index] = u.y;
	m_Rows[2][Index] = u.z;
}

// cMat3::SetCol0 : void (const cVec3 &)
inline void cMat3::SetCol0(const cVec3 &u) {
	m_Rows[0].x = u.x;
	m_Rows[1].x = u.y;
	m_Rows[2].x = u.z;
}

// cMat3::SetCol1 : void (const cVec3 &)
inline void cMat3::SetCol1(const cVec3 &u) {
	m_Rows[0].y = u.x;
	m_Rows[1].y = u.y;
	m_Rows[2].y = u.z;
}

// cMat3::SetCol2 : void (const cVec3 &)
inline void cMat3::SetCol2(const cVec3 &u) {
	m_Rows[0].z = u.x;
	m_Rows[1].z = u.y;
	m_Rows[2].z = u.z;
}

// cMat3::SetCol : void (const int, const float, const float, const float)
inline void cMat3::SetCol(const int Index, const float X, const float Y, const float Z) {
	cAssert(Index >= 0 && Index < 3);
	m_Rows[0][Index] = X;
	m_Rows[1][Index] = Y;
	m_Rows[2][Index] = Z;
}

// cMat3::SetCol0 : void (const float, const float, const float)
inline void cMat3::SetCol0(const float X, const float Y, const float Z) {
	m_Rows[0].x = X;
	m_Rows[1].x = Y;
	m_Rows[2].x = Z;
}

// cMat3::SetCol1 : void (const float, const float, const float)
inline void cMat3::SetCol1(const float X, const float Y, const float Z) {
	m_Rows[0].y = X;
	m_Rows[1].y = Y;
	m_Rows[2].y = Z;
}

// cMat3::SetCol2 : void (const float, const float, const float)
inline void cMat3::SetCol2(const float X, const float Y, const float Z) {
	m_Rows[0].z = X;
	m_Rows[1].z = Y;
	m_Rows[2].z = Z;
}

// cMat3::GetElem : float (const int, const int) const
inline void cMat3::SetElem(int Row, int Col, float Value) {
	cAssert(Row >= 0 && Row < 3);
	cAssert(Col >= 0 && Col < 3);
	m_Rows[Row][Col] = Value;
}

// cMat3::GetElem : float (const int, const int) const
inline float cMat3::GetElem(const int Row, const int Col) const {
	cAssert(Row >= 0 && Row < 3);
	cAssert(Col >= 0 && Col < 3);
	return m_Rows[Row][Col];
}

// cMat3::Elem : float & (const int, const int)
inline float & cMat3::Elem(const int Row, const int Col) {
	cAssert(Row >= 0 && Row < 3);
	cAssert(Col >= 0 && Col < 3);
	return m_Rows[Row][Col];
}

// cMat3::operator [] : const cVec3 & (const int) const
inline const cVec3 & cMat3::operator [] (const int Row) const {
	cAssert(Row >= 0 && Row < 3);
	return m_Rows[Row];
}

// cMat3::operator [] : cVec3 & (const int)
inline cVec3 & cMat3::operator [] (const int Row) {
	cAssert(Row >= 0 && Row < 3);
	return m_Rows[Row];
}

// cMat3::operator () : float (const int, const int) const
inline float cMat3::operator () (const int Row, const int Col) const {
	cAssert(Row >= 0 && Row < 3);
	cAssert(Col >= 0 && Col < 3);
	return m_Rows[Row][Col];
}

// cMat3::operator () : float & (const int, const int)
inline float & cMat3::operator () (const int Row, const int Col) {
	cAssert(Row >= 0 && Row < 3);
	cAssert(Col >= 0 && Col < 3);
	return m_Rows[Row][Col];
}

// cMat3::Trace
inline float cMat3::Trace() const {
	return m_Rows[0][0] + m_Rows[1][1] + m_Rows[2][2];
}

// cMat3::operator == : bool(const cMat3 &) const
inline bool cMat3::operator == (const cMat3 &u) const {
	return cMat3::Equals( *this, u );
}

// cMat3::Equals
inline bool cMat3::Equals(const cMat3 &P, const cMat3 &Q, const float Eps) {
	if(cVec3::Equals(P[0], Q[0]) && cVec3::Equals(P[1], Q[1]) && cVec3::Equals(P[2], Q[2])) {
		return true;
	}
	return false;
}

// cMat3::operator - : const cMat3 () const
inline const cMat3 cMat3::operator - () const {
	return Mul(*this, -1.0f);
}

//-----------------------------------------------------------------------------
// cMat3::Add : void (const cMat3 &)
//-----------------------------------------------------------------------------
inline void cMat3::Add(const cMat3 &R) {
	float *l = reinterpret_cast<float *>(this);
	const float *r = reinterpret_cast<const float *>(&R);

	for(int i = 0; i < 9; i++) {
		*l++ += *r++;
	}
} // cMat3::Add

// cMat3::operator += : void (const cMat3 &)
inline void cMat3::operator += (const cMat3 &R) {
	Add(R);
}

//-----------------------------------------------------------------------------
// cMat3::Add : const cMat3 (const cMat3 &, const cMat3 &)
//-----------------------------------------------------------------------------
inline const cMat3 cMat3::Add(const cMat3 &L, const cMat3 &R) {
	const float *l = reinterpret_cast<const float *>(&L);
	const float *r = reinterpret_cast<const float *>(&R);
	cMat3 S;
	float *s = reinterpret_cast<float *>(&S);

	for(int i = 0; i < 9; i++) {
		*s++ = *l++ + *r++;
	}
	return S;
}

// cMat3::operator + : const cMat3 (const cMat3 &) const
inline const cMat3 cMat3::operator + (const cMat3 &R) const {
	return Mul(*this, R);
}

//-----------------------------------------------------------------------------
// cMat3::Sub : void (const cMat3 &)
//-----------------------------------------------------------------------------
inline void cMat3::Sub(const cMat3 &R) {
	float *l = reinterpret_cast<float *>(this);
	const float *r = reinterpret_cast<const float *>(&R);

	for(int i = 0; i < 9; i++) {
		*l++ -= *r++;
	}
} // cMat3::Sub

// cMat3::operator -= : void (const cMat3 &)
inline void cMat3::operator -= (const cMat3 &R) {
	Sub(R);
}

//-----------------------------------------------------------------------------
// cMat3::Sub : const cMat3 (const cMat3 &, const cMat3 &)
//-----------------------------------------------------------------------------
inline const cMat3 cMat3::Sub(const cMat3 &L, const cMat3 &R) {
	const float *l = reinterpret_cast<const float *>(&L);
	const float *r = reinterpret_cast<const float *>(&R);
	cMat3 D;
	float *d = reinterpret_cast<float *>(&D);

	for(int i = 0; i < 9; i++) {
		*d++ = *l++ - *r++;
	}
	return D;
} // cMat3::Sub

inline const cMat3 cMat3::operator - (const cMat3 &R) const {
	return Sub(*this, R);
}

//-----------------------------------------------------------------------------
// cMat3::Mul : void (const cMat3 &)
//-----------------------------------------------------------------------------
inline void cMat3::Mul(const cMat3 &R) {
	float *l = reinterpret_cast<float *>(this);
	const float *r = reinterpret_cast<const float *>(&R);
	
	float t[3];
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			t[j] = l[0] * r[0 * 3 + j] + l[1] * r[1 * 3 + j] + l[2] * r[2 * 3 + j];
		}
		l[0] = t[0];
		l[1] = t[1];
		l[2] = t[2];
		l += 3;
	}
} // cMat3::Mul

// cMat3::Mul : void (const float)
inline void cMat3::Mul(const float s) {
	float *l = (float *)this;
	for(int i = 0; i < 9; i++) {
		*l++ *= s;
	}
}

// cMat3::operator *= : void (const cMat3 &)
inline void cMat3::operator *= (const cMat3 &R) {
	Mul(R);
}

// cMat3::operator *= : void (const float)
inline void cMat3::operator *= (const float s) {
	Mul(s);
}

// cMat3::operator /=
inline void cMat3::operator /= (const float s) {
	float is = 1.0f / s;
	Mul(is);
}

//-----------------------------------------------------------------------------
// cMat3::Mul : const cMat3 (const cMat3 &, const cMat3 &)
//-----------------------------------------------------------------------------
inline const cMat3 cMat3::Mul(const cMat3 &L, const cMat3 &R) {
	cMat3 M;
	const float *l = reinterpret_cast<const float *>(&L);
	const float *r = reinterpret_cast<const float *>(&R);
	float *m = reinterpret_cast<float *>(&M);
	
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			*m = l[0] * r[0 * 3 + j] + l[1] * r[1 * 3 + j] + l[2] * r[2 * 3 + j];
			m++;
		}
		l += 3;
	}
	return M;
} // cMat3::Mul

// cMat3::Mul : const cMat3 (const cMat3 &, const float)
inline const cMat3 cMat3::Mul(const cMat3 &L, const float s) {
	cMat3 M;
	const float *l = (const float *)&L;
	float *m = (float *)&M;

	for(int i = 0; i < 9; i++) {
		*m++ = *l++ * s;
	}
	return M;
}

inline const cVec3 cMat3::Mul(const cMat3 &L, const cVec3 &vc){
	cVec3 res_vec;

	res_vec.x = L.m_Rows[0].x *vc.x + L.m_Rows[0].y *vc.y + L.m_Rows[0].z *vc.z;
	res_vec.y = L.m_Rows[1].x *vc.x + L.m_Rows[1].y *vc.y + L.m_Rows[1].z *vc.z;
	res_vec.z = L.m_Rows[2].x *vc.x + L.m_Rows[2].y *vc.y + L.m_Rows[2].z *vc.z;

	return res_vec;
}

// cMat3::operator * : const cMat3 (const cMat3 &) const
inline const cMat3 cMat3::operator * (const cMat3 &R) const {
	return Mul(*this, R);
}

// cMat3::operator * : const cMat3 (const float) const
inline const cMat3 cMat3::operator * (const float s) const {
	return Mul(*this, s);
}

// cMat3::operator /
inline const cMat3 cMat3::operator / (const float s) const {
	float is = 1.0f / s;
	return Mul(*this, is);
}

// operator * : const cMat3 (const float, const cMat3 &)
inline const cMat3 operator * (const float s, const cMat3 &R) {
	return cMat3::Mul(R, s);
}

// cMat3::IsZero
inline bool cMat3::IsZero(const float Eps) const {
	return Equals(*this, Zero, Eps);
}

// cMat3::IsIdentity
inline bool cMat3::IsIdentity(const float Eps) const {
	return Equals(*this, Identity, Eps);
}

// cMat3::IsSymmetric
inline bool cMat3::IsSymmetric(const float Eps) const {
	if(!cMath::Equals(m_Rows[2][0], m_Rows[0][2], Eps)) {
		return false;
	}
	if(!cMath::Equals(m_Rows[2][1], m_Rows[1][2], Eps)) {
		return false;
	}
	if(!cMath::Equals(m_Rows[1][0], m_Rows[0][1], Eps)) {
		return false;
	}
	return true;
}

// cMat3::IsOrthonormal
inline bool cMat3::IsOrthonormal(const float Eps) const {
	return cMath::IsOne(Determinant(), Eps);
}

// cMat3::ToFloatPtr() : const float * () const
inline const float * cMat3::ToFloatPtr() const {
	return m_Rows[0].ToFloatPtr();
}

// cMat3::ToFloatPtr() : float * ()
inline float * cMat3::ToFloatPtr() {
	return m_Rows[0].ToFloatPtr();
}

// cMat3::Transpose : const cMat3 (const cMat3 &)
inline const cMat3 cMat3::Transpose(const cMat3 &M) {
	cMat3 T;
	for(int i = 0; i < 3; i++) {
		T.SetRow(i, M.GetCol(i));
	}
	return T;
}

// cMat3::Transpose : void ()
inline void cMat3::Transpose() {
	cMath::Swap(m_Rows[0][1], m_Rows[1][0]);
	cMath::Swap(m_Rows[0][2], m_Rows[2][0]);
	cMath::Swap(m_Rows[1][2], m_Rows[2][1]);
}

// cMat3::OrthoNormalize : const cMat3 (const cMat3 &)
inline const cMat3 cMat3::OrthoNormalize(const cMat3 &Src) {
	cMat3 O = Src;
	O.m_Rows[0].Normalize();
	O.m_Rows[2] = cVec3::Cross(O.m_Rows[0], O.m_Rows[1]).ToNormal();
	O.m_Rows[1] = cVec3::Cross(O.m_Rows[2], O.m_Rows[0]).ToNormal();
	return O;
}

// cMat3::OrthoNormalize : void ()
inline void cMat3::OrthoNormalize() {
	m_Rows[0].Normalize();
	m_Rows[2] = cVec3::Cross(m_Rows[0], m_Rows[1]).ToNormal();
	m_Rows[1] = cVec3::Cross(m_Rows[2], m_Rows[0]).ToNormal();
}

//*****************************************************************************
// cVec2 & cMat3
//*****************************************************************************

// cVec2::Transform : const cVec2 (const cVec2 &, const cMat3 &)
inline const cVec2 cVec2::Transform(const cVec2 &u, const cMat3 &R) {
	cVec2 r;
	r.x = u.x * R(0, 0) + u.y * R(1, 0);
	r.y = u.x * R(0, 1) + u.y * R(1, 1);
	return r;
}

// cVec2::Transform : void (const cMat3 &)
inline void cVec2::Transform(const cMat3 &R) {
	*this = Transform(*this, R);
}

// cVec2::operator *= : void (const cMat3 &)
inline void cVec2::operator *= (const cMat3 &R) {
	*this = Transform(*this, R);
}

// cVec2::operator * : const cVec2 (const cMat3 &) const
inline const cVec2 cVec2::operator * (const cMat3 &R) const {
	return Transform(*this, R);
}

//*****************************************************************************
// cVec3 & cMat3
//*****************************************************************************

// cVec3::Transform : const cVec3 (const cVec3 &, const cMat3 &)
inline const cVec3 cVec3::Transform(const cVec3 &u, const cMat3 &R) {
	cVec3 r;
	r.x = u.x * R(0, 0) + u.y * R(1, 0) + u.z * R(2, 0);
	r.y = u.x * R(0, 1) + u.y * R(1, 1) + u.z * R(2, 1);
	r.z = u.x * R(0, 2) + u.y * R(1, 2) + u.z * R(2, 2);
	return r;
}

// cVec3::Transform : void (const cMat3 &)
inline void cVec3::Transform(const cMat3 &R) {
	*this = Transform(*this, R);
}

// cVec3::operator *= : void (const cMat3 &)
inline void cVec3::operator *= (const cMat3 &R) {
	*this = Transform(*this, R);
}


// cVec3::operator * : const cVec3 (const cMat3 &) const
inline const cVec3 cVec3::operator * (const cMat3 &R) const {
	return Transform(*this, R);
}




::std::ostream& operator<<( ::std::ostream&,  const cMat3& );
