#pragma once

//*****************************************************************************
// dMat3
//*****************************************************************************
class dMat3 {
public:
	enum EZeroCtor		{ ZeroCtor };
	enum EIdentityCtor	{ IdentityCtor };
	enum ERowsCtor		{ RowsCtor };
	enum EColsCtor		{ ColsCtor };
	
	dMat3();
	dMat3(const EZeroCtor);
	dMat3(const EIdentityCtor);
	dMat3(const ERowsCtor, const dVec3 &Row0, const dVec3 &Row1, const dVec3 &Row2);
	dMat3(const EColsCtor, const dVec3 &Col0, const dVec3 &Col1, const dVec3 &Col2);
	dMat3(const double _00, const double _01, const double _02,
		const double _10, const double _11, const double _12,
		const double _20, const double _21, const double _22);
	dMat3(const cMat3& m);
	
	void Copy(const double *Double9);
	void CopyTransposed(const double *Double9);

	void SetZero();
	void SetIdentity();

	const dVec3 & GetRow(const int Index) const;
	const dVec3 & GetRow0() const;
	const dVec3 & GetRow1() const;
	const dVec3 & GetRow2() const;
	
	dVec3 & Row(const int Index);
	dVec3 & Row0();
	dVec3 & Row1();
	dVec3 & Row2();

	void SetRow(const int Index, const dVec3 &);
	void SetRow0(const dVec3 &);
	void SetRow1(const dVec3 &);
	void SetRow2(const dVec3 &);

	void SetRow(const int Index, const double X, const double Y, const double Z);
	void SetRow0(const double X, const double Y, const double Z);
	void SetRow1(const double X, const double Y, const double Z);
	void SetRow2(const double X, const double Y, const double Z);

	const dVec3 GetCol(const int Index) const;
	const dVec3 GetCol0() const;
	const dVec3 GetCol1() const;
	const dVec3 GetCol2() const;

	void SetCol(const int Index, const dVec3 &);
	void SetCol0(const dVec3 &);
	void SetCol1(const dVec3 &);
	void SetCol2(const dVec3 &);

	void SetCol(const int Index, const double X, const double Y, const double Z);
	void SetCol0(const double X, const double Y, const double Z);
	void SetCol1(const double X, const double Y, const double Z);
	void SetCol2(const double X, const double Y, const double Z);
	
	void SetElem(int Row, int Col, double Value);
	double GetElem(const int Row, const int Col) const;
	double & Elem(const int Row, const int Col);

	const dVec3 & operator [] (const int Row) const;
	dVec3 & operator [] (const int Row);

	double operator () (const int Row, const int Col) const;
	double & operator () (const int Row, const int Col);
	
	double Trace() const;
	double Determinant() const;
	
	bool operator == (const dMat3 &) const;
	static bool Equals(const dMat3 &, const dMat3 &, const double Eps = cMath::MatrixEpsilon);
	
	bool IsZero(const double Eps = cMath::MatrixEpsilon) const;
	bool IsIdentity(const double Eps = cMath::MatrixEpsilon) const;
	bool IsSymmetric(const double Eps = cMath::MatrixEpsilon) const;
	bool IsOrthonormal(const double Eps = cMath::MatrixEpsilon) const;

	const dMat3 operator - () const;

	void operator += (const dMat3 &R);
	void operator -= (const dMat3 &R);
	void operator *= (const dMat3 &R);
	void operator *= (const double);
	void operator /= (const double);

	const dMat3 operator + (const dMat3 &R) const;
	const dMat3 operator - (const dMat3 &R) const;
	const dMat3 operator * (const dMat3 &R) const;
	const dMat3 operator * (const double) const;
	friend const dMat3 operator * (const double, const dMat3 &);
	const dMat3 operator / (const double) const;

	void Add(const dMat3 &R);
	void Sub(const dMat3 &R);
	void Mul(const dMat3 &R);
	void Mul(const double s);
	
	static const dMat3 Add(const dMat3 &L, const dMat3 &R);
	static const dMat3 Sub(const dMat3 &L, const dMat3 &R);
	static const dMat3 Mul(const dMat3 &L, const dMat3 &R);
	static const dMat3 Mul(const dMat3 &L, const double s);
	static const dVec3 Mul(const dMat3 &L, const dVec3 &vc);

	static const dMat3 Zero;
	static const dMat3 Identity;
	
	static const dMat3 Transpose(const dMat3 &);
	void Transpose();
	
	static bool Invert(const dMat3 &Fm, dMat3 *To);
	bool Invert() { return Invert(*this, this); }

	static const dMat3 OrthoNormalize(const dMat3 &Src);
	void OrthoNormalize();

	static const dMat3 Rotation(const dVec3 &Axis, const double Angle);
	static const dMat3 RotationX(const double Angle);
	static const dMat3 RotationY(const double Angle);
	static const dMat3 RotationZ(const double Angle);
	static const dMat3 RotationXYZ(const double Pitch, const double Yaw, const double Roll);
	static const dMat3 EulerZYX(const double eulerX, const double eulerY, const double eulerZ); 
	
	static const dMat3 Scaling(const double XYZ);
	static const dMat3 Scaling(const double X, const double Y);
	static const dMat3 Scaling(const double X, const double Y, const double Z);
	static const dMat3 Scaling(const dVec2 &XY);
	static const dMat3 Scaling(const dVec3 &XYZ);
	
	const double * ToDoublePtr() const;
	double * ToDoublePtr();
	const dMat4 ToMat4() const;
	
	void ToVectors(dVec3 *Forward, dVec3 *Right = NULL, dVec3 *Up = NULL) const;
	static const dMat3 FromVectors(const dVec3 &Forward, const dVec3 &Right, const dVec3 &Up);
	const dVec3 ToForward() const;
	const dVec3 ToRight() const;
	const dVec3 ToUp() const;

	const cAngles ToAngles() const;

private:
	dVec3 m_Rows[3];
};

// dMat3.ctor : ()
inline dMat3::dMat3() {
}
// dMat3.ctor : (const EZeroCtor)
inline dMat3::dMat3(const EZeroCtor) {
	m_Rows[0].SetZero();
	m_Rows[1].SetZero();
	m_Rows[2].SetZero();
}

// dMat3.ctor : (const EIdentityCtor)
inline dMat3::dMat3(const EIdentityCtor) {
	m_Rows[0].Set(1.0, 0.0, 0.0);
	m_Rows[1].Set(0.0, 1.0, 0.0);
	m_Rows[2].Set(0.0, 0.0, 1.0);
}

// dMat3.ctor : (const ERowsCtor, const dVec3 &, const dVec3 &, const dVec3 &)
inline dMat3::dMat3(const ERowsCtor, const dVec3 &Row0, const dVec3 &Row1, const dVec3 &Row2) {
	m_Rows[0] = Row0;
	m_Rows[1] = Row1;
	m_Rows[2] = Row2;
}

// dMat3.ctor : (const EColsCtor, const dVec3 &, const dVec3 &, const dVec3 &)
inline dMat3::dMat3(const EColsCtor, const dVec3 &Col0, const dVec3 &Col1, const dVec3 &Col2) {
	m_Rows[0].Set(Col0.x, Col1.x, Col2.x);
	m_Rows[1].Set(Col0.y, Col1.y, Col2.y);
	m_Rows[2].Set(Col0.z, Col1.z, Col2.z);
}

// dMat3.ctor
inline dMat3::dMat3(const double _00, const double _01, const double _02,
					const double _10, const double _11, const double _12,
					const double _20, const double _21, const double _22) {
	m_Rows[0].Set(_00, _01, _02);
	m_Rows[1].Set(_10, _11, _12);
	m_Rows[2].Set(_20, _21, _22);
}

// dMat3::Copy
inline void dMat3::Copy(const double *Double9) {
	m_Rows[0].Set(Double9[0], Double9[1], Double9[2]);
	m_Rows[1].Set(Double9[3], Double9[4], Double9[5]);
	m_Rows[2].Set(Double9[6], Double9[7], Double9[8]);
}

// dMat3::CopyTransposed
inline void dMat3::CopyTransposed(const double *Double9) {
	m_Rows[0].Set(Double9[0], Double9[3], Double9[6]);
	m_Rows[1].Set(Double9[1], Double9[4], Double9[7]);
	m_Rows[2].Set(Double9[2], Double9[5], Double9[8]);
}

// dMat3::SetZero
inline void dMat3::SetZero() {
	m_Rows[0].SetZero();
	m_Rows[1].SetZero();
	m_Rows[2].SetZero();
}

// dMat3::SetIdentity
inline void dMat3::SetIdentity() {
	m_Rows[0].Set(1.0, 0.0, 0.0);
	m_Rows[1].Set(0.0, 1.0, 0.0);
	m_Rows[2].Set(0.0, 0.0, 1.0);
}

// dMat3::GetRow : const dVec3 & (const int) const
inline const dVec3 & dMat3::GetRow(const int Index) const {
	cAssert(Index >= 0 && Index < 3);
	return m_Rows[Index];
}

// dMat3::GetRow0 : const dVec3 & () const
inline const dVec3 & dMat3::GetRow0() const {
	return m_Rows[0];
}

// dMat3::GetRow1 : const dVec3 & () const
inline const dVec3 & dMat3::GetRow1() const {
	return m_Rows[1];
}

// dMat3::GetRow2 : const dVec3 & () const
inline const dVec3 & dMat3::GetRow2() const {
	return m_Rows[2];
}

// dMat3::Row : dVec3 & (const int)
inline dVec3 & dMat3::Row(const int Index) {
	cAssert(Index >= 0 && Index < 3);
	return m_Rows[Index];
}

// dMat3::Row0 : dVec3 & ()
inline dVec3 & dMat3::Row0() {
	return m_Rows[0];
}

// dMat3::Row1 : dVec3 & ()
inline dVec3 & dMat3::Row1() {
	return m_Rows[1];
}

// dMat3::Row2 : dVec3 & ()
inline dVec3 & dMat3::Row2() {
	return m_Rows[2];
}

// dMat3::SetRow : void (const int, const dVec3 &)
inline void dMat3::SetRow(const int Index, const dVec3 &r) {
	cAssert(Index >= 0 && Index < 3);
	m_Rows[Index] = r;
}

// dMat3::SetRow0 : void (const dVec3 &)
inline void dMat3::SetRow0(const dVec3 &r) {
	m_Rows[0] = r;
}

// dMat3::SetRow1 : void (const dVec3 &)
inline void dMat3::SetRow1(const dVec3 &r) {
	m_Rows[1] = r;
}

// dMat3::SetRow2 : void (const dVec3 &)
inline void dMat3::SetRow2(const dVec3 &r) {
	m_Rows[2] = r;
}

// dMat3::SetRow : void (const int, const double, const double, const double)
inline void dMat3::SetRow(const int Index, const double X, const double Y, const double Z) {
	cAssert(Index >= 0 && Index < 3);
	m_Rows[Index].Set(X, Y, Z);
}

// dMat3::SetRow0 : void (const double, const double, const double)
inline void dMat3::SetRow0(const double X, const double Y, const double Z) {
	m_Rows[0].Set(X, Y, Z);
}

// dMat3::SetRow1 : void (const double, const double, const double)
inline void dMat3::SetRow1(const double X, const double Y, const double Z) {
	m_Rows[1].Set(X, Y, Z);
}

// dMat3::SetRow2 : void(const double, const double, const double)
inline void dMat3::SetRow2(const double X, const double Y, const double Z) {
	m_Rows[2].Set(X, Y, Z);
}

// dMat3::GetCol : const dVec3 (const int) const
inline const dVec3 dMat3::GetCol(const int Index) const {
	cAssert(Index >= 0 && Index < 3);
	return dVec3(m_Rows[0][Index], m_Rows[1][Index], m_Rows[2][Index]);
}

// dMat3::GetCol0 : const dVec3 () const
inline const dVec3 dMat3::GetCol0() const {
	return dVec3(m_Rows[0].x, m_Rows[1].x, m_Rows[2].x);
}

// dMat3::GetCol1 : const dVec3 () const
inline const dVec3 dMat3::GetCol1() const {
	return dVec3(m_Rows[0].y, m_Rows[1].y, m_Rows[2].y);
}

// dMat3::GetCol2 : const dVec3 () const
inline const dVec3 dMat3::GetCol2() const {
	return dVec3(m_Rows[0].z, m_Rows[1].z, m_Rows[2].z);
}

// dMat3::SetCol : void (const int, const dVec3 &)
inline void dMat3::SetCol(const int Index, const dVec3 &u) {
	cAssert(Index >= 0 && Index < 3);
	m_Rows[0][Index] = u.x;
	m_Rows[1][Index] = u.y;
	m_Rows[2][Index] = u.z;
}

// dMat3::SetCol0 : void (const dVec3 &)
inline void dMat3::SetCol0(const dVec3 &u) {
	m_Rows[0].x = u.x;
	m_Rows[1].x = u.y;
	m_Rows[2].x = u.z;
}

// dMat3::SetCol1 : void (const dVec3 &)
inline void dMat3::SetCol1(const dVec3 &u) {
	m_Rows[0].y = u.x;
	m_Rows[1].y = u.y;
	m_Rows[2].y = u.z;
}

// dMat3::SetCol2 : void (const dVec3 &)
inline void dMat3::SetCol2(const dVec3 &u) {
	m_Rows[0].z = u.x;
	m_Rows[1].z = u.y;
	m_Rows[2].z = u.z;
}

// dMat3::SetCol : void (const int, const double, const double, const double)
inline void dMat3::SetCol(const int Index, const double X, const double Y, const double Z) {
	cAssert(Index >= 0 && Index < 3);
	m_Rows[0][Index] = X;
	m_Rows[1][Index] = Y;
	m_Rows[2][Index] = Z;
}

// dMat3::SetCol0 : void (const double, const double, const double)
inline void dMat3::SetCol0(const double X, const double Y, const double Z) {
	m_Rows[0].x = X;
	m_Rows[1].x = Y;
	m_Rows[2].x = Z;
}

// dMat3::SetCol1 : void (const double, const double, const double)
inline void dMat3::SetCol1(const double X, const double Y, const double Z) {
	m_Rows[0].y = X;
	m_Rows[1].y = Y;
	m_Rows[2].y = Z;
}

// dMat3::SetCol2 : void (const double, const double, const double)
inline void dMat3::SetCol2(const double X, const double Y, const double Z) {
	m_Rows[0].z = X;
	m_Rows[1].z = Y;
	m_Rows[2].z = Z;
}

// dMat3::GetElem : double (const int, const int) const
inline void dMat3::SetElem(int Row, int Col, double Value) {
	cAssert(Row >= 0 && Row < 3);
	cAssert(Col >= 0 && Col < 3);
	m_Rows[Row][Col] = Value;
}

// dMat3::GetElem : double (const int, const int) const
inline double dMat3::GetElem(const int Row, const int Col) const {
	cAssert(Row >= 0 && Row < 3);
	cAssert(Col >= 0 && Col < 3);
	return m_Rows[Row][Col];
}

// dMat3::Elem : double & (const int, const int)
inline double & dMat3::Elem(const int Row, const int Col) {
	cAssert(Row >= 0 && Row < 3);
	cAssert(Col >= 0 && Col < 3);
	return m_Rows[Row][Col];
}

// dMat3::operator [] : const dVec3 & (const int) const
inline const dVec3 & dMat3::operator [] (const int Row) const {
	cAssert(Row >= 0 && Row < 3);
	return m_Rows[Row];
}

// dMat3::operator [] : dVec3 & (const int)
inline dVec3 & dMat3::operator [] (const int Row) {
	cAssert(Row >= 0 && Row < 3);
	return m_Rows[Row];
}

// dMat3::operator () : double (const int, const int) const
inline double dMat3::operator () (const int Row, const int Col) const {
	cAssert(Row >= 0 && Row < 3);
	cAssert(Col >= 0 && Col < 3);
	return m_Rows[Row][Col];
}

// dMat3::operator () : double & (const int, const int)
inline double & dMat3::operator () (const int Row, const int Col) {
	cAssert(Row >= 0 && Row < 3);
	cAssert(Col >= 0 && Col < 3);
	return m_Rows[Row][Col];
}

// dMat3::Trace
inline double dMat3::Trace() const {
	return m_Rows[0][0] + m_Rows[1][1] + m_Rows[2][2];
}

// dMat3::operator == : bool(const dMat3 &) const
inline bool dMat3::operator == (const dMat3 &u) const {
	return dMat3::Equals( *this, u );
}

// dMat3::Equals
inline bool dMat3::Equals(const dMat3 &P, const dMat3 &Q, const double Eps) {
	if(dVec3::Equals(P[0], Q[0]) && dVec3::Equals(P[1], Q[1]) && dVec3::Equals(P[2], Q[2])) {
		return true;
	}
	return false;
}

// dMat3::operator - : const dMat3 () const
inline const dMat3 dMat3::operator - () const {
	return Mul(*this, -1.0);
}

//-----------------------------------------------------------------------------
// dMat3::Add : void (const dMat3 &)
//-----------------------------------------------------------------------------
inline void dMat3::Add(const dMat3 &R) {
	double *l = reinterpret_cast<double *>(this);
	const double *r = reinterpret_cast<const double *>(&R);

	for(int i = 0; i < 9; i++) {
		*l++ += *r++;
	}
} // dMat3::Add

// dMat3::operator += : void (const dMat3 &)
inline void dMat3::operator += (const dMat3 &R) {
	Add(R);
}

//-----------------------------------------------------------------------------
// dMat3::Add : const dMat3 (const dMat3 &, const dMat3 &)
//-----------------------------------------------------------------------------
inline const dMat3 dMat3::Add(const dMat3 &L, const dMat3 &R) {
	const double *l = reinterpret_cast<const double *>(&L);
	const double *r = reinterpret_cast<const double *>(&R);
	dMat3 S;
	double *s = reinterpret_cast<double *>(&S);

	for(int i = 0; i < 9; i++) {
		*s++ = *l++ + *r++;
	}
	return S;
}

// dMat3::operator + : const dMat3 (const dMat3 &) const
inline const dMat3 dMat3::operator + (const dMat3 &R) const {
	return Mul(*this, R);
}

//-----------------------------------------------------------------------------
// dMat3::Sub : void (const dMat3 &)
//-----------------------------------------------------------------------------
inline void dMat3::Sub(const dMat3 &R) {
	double *l = reinterpret_cast<double *>(this);
	const double *r = reinterpret_cast<const double *>(&R);

	for(int i = 0; i < 9; i++) {
		*l++ -= *r++;
	}
} // dMat3::Sub

// dMat3::operator -= : void (const dMat3 &)
inline void dMat3::operator -= (const dMat3 &R) {
	Sub(R);
}

//-----------------------------------------------------------------------------
// dMat3::Sub : const dMat3 (const dMat3 &, const dMat3 &)
//-----------------------------------------------------------------------------
inline const dMat3 dMat3::Sub(const dMat3 &L, const dMat3 &R) {
	const double *l = reinterpret_cast<const double *>(&L);
	const double *r = reinterpret_cast<const double *>(&R);
	dMat3 D;
	double *d = reinterpret_cast<double *>(&D);

	for(int i = 0; i < 9; i++) {
		*d++ = *l++ - *r++;
	}
	return D;
} // dMat3::Sub

inline const dMat3 dMat3::operator - (const dMat3 &R) const {
	return Sub(*this, R);
}

//-----------------------------------------------------------------------------
// dMat3::Mul : void (const dMat3 &)
//-----------------------------------------------------------------------------
inline void dMat3::Mul(const dMat3 &R) {
	double *l = reinterpret_cast<double *>(this);
	const double *r = reinterpret_cast<const double *>(&R);
	
	double t[3];
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			t[j] = l[0] * r[0 * 3 + j] + l[1] * r[1 * 3 + j] + l[2] * r[2 * 3 + j];
		}
		l[0] = t[0];
		l[1] = t[1];
		l[2] = t[2];
		l += 3;
	}
} // dMat3::Mul

// dMat3::Mul : void (const double)
inline void dMat3::Mul(const double s) {
	double *l = (double *)this;
	for(int i = 0; i < 9; i++) {
		*l++ *= s;
	}
}

// dMat3::operator *= : void (const dMat3 &)
inline void dMat3::operator *= (const dMat3 &R) {
	Mul(R);
}

// dMat3::operator *= : void (const double)
inline void dMat3::operator *= (const double s) {
	Mul(s);
}

// dMat3::operator /=
inline void dMat3::operator /= (const double s) {
	double is = 1.0 / s;
	Mul(is);
}

//-----------------------------------------------------------------------------
// dMat3::Mul : const dMat3 (const dMat3 &, const dMat3 &)
//-----------------------------------------------------------------------------
inline const dMat3 dMat3::Mul(const dMat3 &L, const dMat3 &R) {
	dMat3 M;
	const double *l = reinterpret_cast<const double *>(&L);
	const double *r = reinterpret_cast<const double *>(&R);
	double *m = reinterpret_cast<double *>(&M);
	
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			*m = l[0] * r[0 * 3 + j] + l[1] * r[1 * 3 + j] + l[2] * r[2 * 3 + j];
			m++;
		}
		l += 3;
	}
	return M;
} // dMat3::Mul

// dMat3::Mul : const dMat3 (const dMat3 &, const double)
inline const dMat3 dMat3::Mul(const dMat3 &L, const double s) {
	dMat3 M;
	const double *l = (const double *)&L;
	double *m = (double *)&M;

	for(int i = 0; i < 9; i++) {
		*m++ = *l++ * s;
	}
	return M;
}

inline const dVec3 dMat3::Mul(const dMat3 &L, const dVec3 &vc){
	dVec3 res_vec;

	res_vec.x = L.m_Rows[0].x *vc.x + L.m_Rows[0].y *vc.y + L.m_Rows[0].z *vc.z;
	res_vec.y = L.m_Rows[1].x *vc.x + L.m_Rows[1].y *vc.y + L.m_Rows[1].z *vc.z;
	res_vec.z = L.m_Rows[2].x *vc.x + L.m_Rows[2].y *vc.y + L.m_Rows[2].z *vc.z;

	return res_vec;
}

// dMat3::operator * : const dMat3 (const dMat3 &) const
inline const dMat3 dMat3::operator * (const dMat3 &R) const {
	return Mul(*this, R);
}

// dMat3::operator * : const dMat3 (const double) const
inline const dMat3 dMat3::operator * (const double s) const {
	return Mul(*this, s);
}

// dMat3::operator /
inline const dMat3 dMat3::operator / (const double s) const {
	double is = 1.0 / s;
	return Mul(*this, is);
}

// operator * : const dMat3 (const double, const dMat3 &)
inline const dMat3 operator * (const double s, const dMat3 &R) {
	return dMat3::Mul(R, s);
}

// dMat3::IsZero
inline bool dMat3::IsZero(const double Eps) const {
	return Equals(*this, Zero, Eps);
}

// dMat3::IsIdentity
inline bool dMat3::IsIdentity(const double Eps) const {
	return Equals(*this, Identity, Eps);
}

// dMat3::IsSymmetric
inline bool dMat3::IsSymmetric(const double Eps) const {
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

// dMat3::IsOrthonormal
inline bool dMat3::IsOrthonormal(const double Eps) const {
	return cMath::IsOne(Determinant(), Eps);
}

// dMat3::ToDoublePtr() : const double * () const
inline const double * dMat3::ToDoublePtr() const {
	return m_Rows[0].ToDoublePtr();
}

// dMat3::ToDoublePtr() : double * ()
inline double * dMat3::ToDoublePtr() {
	return m_Rows[0].ToDoublePtr();
}

// dMat3::Transpose : const dMat3 (const dMat3 &)
inline const dMat3 dMat3::Transpose(const dMat3 &M) {
	dMat3 T;
	for(int i = 0; i < 3; i++) {
		T.SetRow(i, M.GetCol(i));
	}
	return T;
}

// dMat3::Transpose : void ()
inline void dMat3::Transpose() {
	cMath::Swap(m_Rows[0][1], m_Rows[1][0]);
	cMath::Swap(m_Rows[0][2], m_Rows[2][0]);
	cMath::Swap(m_Rows[1][2], m_Rows[2][1]);
}

// dMat3::OrthoNormalize : const dMat3 (const dMat3 &)
inline const dMat3 dMat3::OrthoNormalize(const dMat3 &Src) {
	dMat3 O = Src;
	O.m_Rows[0].Normalize();
	O.m_Rows[2] = dVec3::Cross(O.m_Rows[0], O.m_Rows[1]).ToNormal();
	O.m_Rows[1] = dVec3::Cross(O.m_Rows[2], O.m_Rows[0]).ToNormal();
	return O;
}

// dMat3::OrthoNormalize : void ()
inline void dMat3::OrthoNormalize() {
	m_Rows[0].Normalize();
	m_Rows[2] = dVec3::Cross(m_Rows[0], m_Rows[1]).ToNormal();
	m_Rows[1] = dVec3::Cross(m_Rows[2], m_Rows[0]).ToNormal();
}

//*****************************************************************************
// dVec2 & dMat3
//*****************************************************************************

// dVec2::Transform : const dVec2 (const dVec2 &, const dMat3 &)
inline const dVec2 dVec2::Transform(const dVec2 &u, const dMat3 &R) {
	dVec2 r;
	r.x = u.x * R(0, 0) + u.y * R(1, 0);
	r.y = u.x * R(0, 1) + u.y * R(1, 1);
	return r;
}

// dVec2::Transform : void (const dMat3 &)
inline void dVec2::Transform(const dMat3 &R) {
	*this = Transform(*this, R);
}

// dVec2::operator *= : void (const dMat3 &)
inline void dVec2::operator *= (const dMat3 &R) {
	*this = Transform(*this, R);
}

// dVec2::operator * : const dVec2 (const dMat3 &) const
inline const dVec2 dVec2::operator * (const dMat3 &R) const {
	return Transform(*this, R);
}

//*****************************************************************************
// dVec3 & dMat3
//*****************************************************************************

// dVec3::Transform : const dVec3 (const dVec3 &, const dMat3 &)
inline const dVec3 dVec3::Transform(const dVec3 &u, const dMat3 &R) {
	dVec3 r;
	r.x = u.x * R(0, 0) + u.y * R(1, 0) + u.z * R(2, 0);
	r.y = u.x * R(0, 1) + u.y * R(1, 1) + u.z * R(2, 1);
	r.z = u.x * R(0, 2) + u.y * R(1, 2) + u.z * R(2, 2);
	return r;
}

// dVec3::Transform : void (const dMat3 &)
inline void dVec3::Transform(const dMat3 &R) {
	*this = Transform(*this, R);
}

// dVec3::operator *= : void (const dMat3 &)
inline void dVec3::operator *= (const dMat3 &R) {
	*this = Transform(*this, R);
}


// dVec3::operator * : const dVec3 (const dMat3 &) const
inline const dVec3 dVec3::operator * (const dMat3 &R) const {
	return Transform(*this, R);
}




::std::ostream& operator<<( ::std::ostream&,  const dMat3& );
