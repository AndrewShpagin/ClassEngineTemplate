#pragma once

//*****************************************************************************
// dMat4
//*****************************************************************************
class dMat4 {
public:
	enum EZeroCtor		{ ZeroCtor };
	enum EIdentityCtor	{ IdentityCtor };
	enum ERowsCtor		{ RowsCtor };
	enum EColsCtor		{ ColsCtor };

	dMat4();
	dMat4(const EZeroCtor);
	dMat4(const EIdentityCtor);
	dMat4(const ERowsCtor, const dVec4 &Row0, const dVec4 &Row1, const dVec4 &Row2, const dVec4 &Row3);
	dMat4(const EColsCtor, const dVec4 &Col0, const dVec4 &Col1, const dVec4 &Col2, const dVec4 &Col3);
	dMat4(const dMat3 &Rotation, const dVec3 &Translation);
	dMat4(const dVec3 &Scaling, const dVec3 &Translation);
	dMat4(const double _00, const double _01, const double _02, const double _03,
		const double _10, const double _11, const double _12, const double _13,
		const double _20, const double _21, const double _22, const double _23,
		const double _30, const double _31, const double _32, const double _33);
	dMat4(const cMat4& m);
	
	void Copy(const double *Double16);
	void CopyTransposed(const double *Double16);
	
	void SetZero();
	void SetIdentity();

	const dVec4 & GetRow(const int Index) const;
	const dVec4 & GetRow0() const;
	const dVec4 & GetRow1() const;
	const dVec4 & GetRow2() const;
	const dVec4 & GetRow3() const;

	dVec4 & Row(const int Index);
	dVec4 & Row0();
	dVec4 & Row1();
	dVec4 & Row2();
	dVec4 & Row3();

	void SetRow(const int Index, const dVec4 &);
	void SetRow0(const dVec4 &);
	void SetRow1(const dVec4 &);
	void SetRow2(const dVec4 &);
	void SetRow3(const dVec4 &);

	void SetRow(const int Index, const double X, const double Y, const double Z, const double W);
	void SetRow0(const double X, const double Y, const double Z, const double W);
	void SetRow1(const double X, const double Y, const double Z, const double W);
	void SetRow2(const double X, const double Y, const double Z, const double W);
	void SetRow3(const double X, const double Y, const double Z, const double W);

	const dVec4 GetCol(const int Index) const;
	const dVec4 GetCol0() const;
	const dVec4 GetCol1() const;
	const dVec4 GetCol2() const;
	const dVec4 GetCol3() const;

	void SetCol(const int Index, const dVec4 &);
	void SetCol0(const dVec4 &);
	void SetCol1(const dVec4 &);
	void SetCol2(const dVec4 &);
	void SetCol3(const dVec4 &);

	void SetCol(const int Index, const double X, const double Y, const double Z, const double W);
	void SetCol0(const double X, const double Y, const double Z, const double W);
	void SetCol1(const double X, const double Y, const double Z, const double W);
	void SetCol2(const double X, const double Y, const double Z, const double W);
	void SetCol3(const double X, const double Y, const double Z, const double W);

	void SetElem(int Row, int Col, double Value);
	double GetElem(const int Row, const int Col) const;
	double & Elem(const int Row, const int Col);

	const dVec4 & operator [] (const int Row) const;
	dVec4 & operator [] (const int Row);

	double operator () (const int Row, const int Col) const;
	double & operator () (const int Row, const int Col);

	double Trace() const;
	double Determinant() const;

	bool operator == (const dMat4 &) const;
	static bool Equals(const dMat4 &, const dMat4 &, const double Eps = cMath::MatrixEpsilon);
	
	bool IsZero(double Eps = cMath::MatrixEpsilon) const;
	bool IsIdentity(double Eps = cMath::MatrixEpsilon) const;
    bool IsSymmetric( double Eps = cMath::MatrixEpsilon ) const;
    bool IsOrthonormal( double Eps = cMath::MatrixEpsilon ) const;

	const dMat4 operator - () const;

	void operator += (const dMat4 &R);
	void operator -= (const dMat4 &R);
	void operator *= (const dMat4 &R);
	void operator *= (const double);
	void operator /= (const double);

	const dMat4 operator + (const dMat4 &R) const;
	const dMat4 operator - (const dMat4 &R) const;
	const dMat4 operator * (const dMat4 &R) const;
	const dMat4 operator * (const double) const;
	friend const dMat4 operator * (const double, const dMat4 &);
	const dMat4 operator / (const double) const;

	void Add(const dMat4 &R);
	void Sub(const dMat4 &R);
	void Mul(const dMat4 &R);
	void Mul(const double s);
	
	static const dMat4 Add(const dMat4 &L, const dMat4 &R);
	static const dMat4 Sub(const dMat4 &L, const dMat4 &R);
	static const dMat4 Mul(const dMat4 &L, const dMat4 &R);
	static const dMat4 Mul(const dMat4 &L, const double s);

	const double * ToFloatPtr() const;
	double * ToFloatPtr();
	
	const cStr ToString(const int Prec = 2) const;

	const dMat3 ToMat3() const;
	const dMat3 ToNormalMatrix() const;
	
    const dVec3 GetTranslation() const;
    void SetTranslation( const dVec3 & );

	const dVec3 GetScaling() const;
    void SetScaling( const dVec3 & );

    cAngles GetRotation() const;
    void SetRotation( const cAngles & );

	static const dMat4 Transpose(const dMat4 &);
	void Transpose();

	static bool Invert(const dMat4 &Fm, dMat4 *To);
	bool Invert() { return Invert(*this, this); }
	
	static const dMat4 Zero;
	static const dMat4 Identity;
	
	static const dMat4 Translation(const double X, const double Y);
	static const dMat4 Translation(const double X, const double Y, const double Z);
	static const dMat4 Translation(const dVec2 &XY);
	static const dMat4 Translation(const dVec3 &XYZ);

	static const dMat4 Rotation(const dVec3 &Axis, const double Angle);
	static const dMat4 RotationX(const double Angle);
	static const dMat4 RotationY(const double Angle);
	static const dMat4 RotationZ(const double Angle);
	static const dMat4 RotationXYZ(const double Pitch, const double Yaw, const double Roll);
	static const dMat4 EulerZYX(const double eulerX, const double eulerY, const double eulerZ);
	
	static const dMat4 RotationAt(const dVec2 &Orig, const double Angle);
	static const dMat4 RotationAt(const dVec3 &Orig, const dVec3 &Axis, const double Angle);
	
	static const dMat4 Scaling(const double XYZ);
	static const dMat4 Scaling(const double X, const double Y);
	static const dMat4 Scaling(const double X, const double Y, const double Z);
	static const dMat4 Scaling(const dVec2 &XY);
	static const dMat4 Scaling(const dVec3 &XYZ);
	
	static const dMat4 ScalingAt(const double OrigX, const double OrigY, const double ScaleXY);
	static const dMat4 ScalingAt(const double OrigX, const double OrigY, const double ScaleX, const double ScaleY);

	static const dMat4 ScalingAt(const dVec2 &Orig, const double ScaleXY);
	static const dMat4 ScalingAt(const dVec2 &Orig, const double ScaleX, const double ScaleY);
	static const dMat4 ScalingAt(const dVec2 &Orig, const dVec2 &Scale);

	static const dMat4 ScalingAt(const dVec3 &Orig, const double ScaleXYZ);
	static const dMat4 ScalingAt(const dVec3 &Orig, const double ScaleX, const double ScaleY, const double ScaleZ);
	static const dMat4 ScalingAt(const dVec3 &Orig, const dVec3 &Scale);
	static const dMat4 ScalingAt(const dVec3 &Orig, const dVec3 &Dir, double Scale);

	static const dMat4 Perspective(double YFov, double AspectWtoH, double Znear, double Zfar);
	static const dMat4 PerspectiveInf(const double YFov, const double AspectWtoH, const double Znear);
	
	static const dMat4 Ortho(const double Width, const double Height, const double Znear, const double Zfar);
	static const dMat4 Ortho(const double Left, const double Right, const double Bottom, const double Top, const double Znear, const double Zfar);
	static const dMat4 Ortho(const cBounds &B);

	//---------------
	// Side		Axis
	//---------------
	// 0		+X
	// 1		-X
	// 2		+Y
	// 3		-Y
	// 4		+Z
	// 5		-Z
	//---------------
	static const dMat4 CubeViewProjection(const dVec3 &Pos, const int Side, const double Radius, const bool GL);
	static const dMat4 LookAtViewProjection(const dVec3 &LookFrom, const dVec3 &LookAt, const double FovY, const double AspectYtoH, const double Znear, const double Zfar);
private:
	dVec4 m_Rows[4];
};

// dMat4.ctor : ()
inline dMat4::dMat4() {
}

// dMat4.ctor : (const ERowsCtor, const dVec4 &, const dVec4 &, const dVec4 &, const dVec4 &)
inline dMat4::dMat4(const ERowsCtor, const dVec4 &Row0, const dVec4 &Row1, const dVec4 &Row2, const dVec4 &Row3) {
	m_Rows[0] = Row0;
	m_Rows[1] = Row1;
	m_Rows[2] = Row2;
	m_Rows[3] = Row3;
}

// dMat4.ctor : (const EColsCtor, const dVec4 &, const dVec4 &, const dVec4 &, const dVec4 &)
inline dMat4::dMat4(const EColsCtor, const dVec4 &Col0, const dVec4 &Col1, const dVec4 &Col2, const dVec4 &Col3) {
	m_Rows[0].Set(Col0.x, Col1.x, Col2.x, Col3.x);
	m_Rows[1].Set(Col0.y, Col1.y, Col2.y, Col3.y);
	m_Rows[2].Set(Col0.z, Col1.z, Col2.z, Col3.z);
	m_Rows[3].Set(Col0.w, Col1.w, Col2.w, Col3.w);
}

// dMat4.ctor : (const EZeroCtor)
inline dMat4::dMat4(const EZeroCtor) {
	m_Rows[0].SetZero();
	m_Rows[1].SetZero();
	m_Rows[2].SetZero();
	m_Rows[3].SetZero();
}

// dMat4.ctor : (const EIdentityCtor)
inline dMat4::dMat4(const EIdentityCtor) {
	m_Rows[0].Set(1.0, 0.0, 0.0, 0.0);
	m_Rows[1].Set(0.0, 1.0, 0.0, 0.0);
	m_Rows[2].Set(0.0, 0.0, 1.0, 0.0);
	m_Rows[3].Set(0.0, 0.0, 0.0, 1.0);
}

// dMat4.ctor : (const dMat3 &, const dVec3 &)
inline dMat4::dMat4(const dMat3 &Rotation, const dVec3 &Translation) {
	m_Rows[0].Set(Rotation.GetRow0(), 0.0);
	m_Rows[1].Set(Rotation.GetRow1(), 0.0);
	m_Rows[2].Set(Rotation.GetRow2(), 0.0);
	m_Rows[3].Set(Translation, 1.0);
}

// dMat4.ctor : (const dVec3 &, const dVec3 &)
inline dMat4::dMat4(const dVec3 &Scaling, const dVec3 &Translation) {
	m_Rows[0].Set(Scaling[0], 0.0, 0.0, 0.0);
	m_Rows[1].Set(0.0, Scaling[1], 0.0, 0.0);
	m_Rows[2].Set(0.0, 0.0, Scaling[2], 0.0);
	m_Rows[3].Set(Translation, 1.0);
}

// dMat4.ctor
inline dMat4::dMat4(const double _00, const double _01, const double _02, const double _03,
					const double _10, const double _11, const double _12, const double _13,
					const double _20, const double _21, const double _22, const double _23,
					const double _30, const double _31, const double _32, const double _33) {
	m_Rows[0].Set(_00, _01, _02, _03);
	m_Rows[1].Set(_10, _11, _12, _13);
	m_Rows[2].Set(_20, _21, _22, _23);
	m_Rows[3].Set(_30, _31, _32, _33);
}

// dMat4::Copy
inline void dMat4::Copy(const double *Double16) {
	m_Rows[0].Set(Double16[0], Double16[1], Double16[2], Double16[3]);
	m_Rows[1].Set(Double16[4], Double16[5], Double16[6], Double16[7]);
	m_Rows[2].Set(Double16[8], Double16[9], Double16[10], Double16[11]);
	m_Rows[3].Set(Double16[12], Double16[13], Double16[14], Double16[15]);
}

// dMat4::CopyTransposed
inline void dMat4::CopyTransposed(const double *Double16) {
	m_Rows[0].Set(Double16[0], Double16[4], Double16[8], Double16[12]);
	m_Rows[1].Set(Double16[1], Double16[5], Double16[9], Double16[13]);
	m_Rows[2].Set(Double16[2], Double16[6], Double16[10], Double16[14]);
	m_Rows[3].Set(Double16[3], Double16[7], Double16[11], Double16[15]);
}

// dMat4::SetZero
inline void dMat4::SetZero() {
	m_Rows[0].SetZero();
	m_Rows[1].SetZero();
	m_Rows[2].SetZero();
	m_Rows[3].SetZero();
}

// dMat4::SetIdentity
inline void dMat4::SetIdentity() {
	m_Rows[0].Set(1.0, 0.0, 0.0, 0.0);
	m_Rows[1].Set(0.0, 1.0, 0.0, 0.0);
	m_Rows[2].Set(0.0, 0.0, 1.0, 0.0);
	m_Rows[3].Set(0.0, 0.0, 0.0, 1.0);
}

// dMat4::GetRow : const dVec4 & (const int) const
inline const dVec4 & dMat4::GetRow(const int Index) const {
	cAssert(Index >= 0 && Index < 4);
	return m_Rows[Index];
}

// dMat4::GetRow0 : const dVec4 & () const
inline const dVec4 & dMat4::GetRow0() const {
	return m_Rows[0];
}

// dMat4::GetRow1 : const dVec4 & () const
inline const dVec4 & dMat4::GetRow1() const {
	return m_Rows[1];
}

// dMat4::GetRow2 : const dVec4 & () const
inline const dVec4 & dMat4::GetRow2() const {
	return m_Rows[2];
}

// dMat4::GetRow3 : const dVec4 & () const
inline const dVec4 & dMat4::GetRow3() const {
	return m_Rows[3];
}

// dMat4::Row : dVec4 & (const int)
inline dVec4 & dMat4::Row(const int Index) {
	cAssert(Index >= 0 && Index < 4);
	return m_Rows[Index];
}

// dMat4::Row0 : dVec4 & ()
inline dVec4 & dMat4::Row0() {
	return m_Rows[0];
}

// dMat4::Row1 : dVec4 & ()
inline dVec4 & dMat4::Row1() {
	return m_Rows[1];
}

// dMat4::Row2 : dVec4 & ()
inline dVec4 & dMat4::Row2() {
	return m_Rows[2];
}

// dMat4::Row3 : dVec4 & ()
inline dVec4 & dMat4::Row3() {
	return m_Rows[3];
}

// dMat4::SetRow : void (const int, const dVec4 &)
inline void dMat4::SetRow(const int Index, const dVec4 &r) {
	cAssert(Index >= 0 && Index < 4);
	m_Rows[Index] = r;
}

// dMat4::SetRow0 : void (const dVec4 &)
inline void dMat4::SetRow0(const dVec4 &r) {
	m_Rows[0] = r;
}

// dMat4::SetRow1 : void (const dVec4 &)
inline void dMat4::SetRow1(const dVec4 &r) {
	m_Rows[1] = r;
}

// dMat4::SetRow2 : void (const dVec4 &)
inline void dMat4::SetRow2(const dVec4 &r) {
	m_Rows[2] = r;
}

// dMat4::SetRow3 : void (const dVec4 &)
inline void dMat4::SetRow3(const dVec4 &r) {
	m_Rows[3] = r;
}

// dMat4::SetRow : void (const int, const double, const double, const double, const double)
inline void dMat4::SetRow(const int Index, const double X, const double Y, const double Z, const double W) {
	cAssert(Index >= 0 && Index < 4);
	m_Rows[Index].Set(X, Y, Z, W);
}

// dMat4::SetRow0 : void (const double, const double, const double, const double)
inline void dMat4::SetRow0(const double X, const double Y, const double Z, const double W) {
	m_Rows[0].Set(X, Y, Z, W);
}

// dMat4::SetRow1 : void (const double, const double, const double, const double)
inline void dMat4::SetRow1(const double X, const double Y, const double Z, const double W) {
	m_Rows[1].Set(X, Y, Z, W);
}

// dMat4::SetRow2 : void (const double, const double, const double, const double)
inline void dMat4::SetRow2(const double X, const double Y, const double Z, const double W) {
	m_Rows[2].Set(X, Y, Z, W);
}

// dMat4::SetRow3 : void (const double, const double, const double, const double)
inline void dMat4::SetRow3(const double X, const double Y, const double Z, const double W) {
	m_Rows[3].Set(X, Y, Z, W);
}

// dMat4::GetCol
inline const dVec4 dMat4::GetCol(const int Index) const {
	cAssert(Index >= 0 && Index < 4);
	return dVec4(m_Rows[0][Index], m_Rows[1][Index], m_Rows[2][Index], m_Rows[3][Index]);
}

// dMat4::GetCol0
inline const dVec4 dMat4::GetCol0() const {
	return dVec4(m_Rows[0].x, m_Rows[1].x, m_Rows[2].x, m_Rows[3].x);
}

// dMat4::GetCol1
inline const dVec4 dMat4::GetCol1() const {
	return dVec4(m_Rows[0].y, m_Rows[1].y, m_Rows[2].y, m_Rows[3].y);
}

// dMat4::GetCol2
inline const dVec4 dMat4::GetCol2() const {
	return dVec4(m_Rows[0].z, m_Rows[1].z, m_Rows[2].z, m_Rows[3].z);
}

// dMat4::GetCol3
inline const dVec4 dMat4::GetCol3() const {
	return dVec4(m_Rows[0].w, m_Rows[1].w, m_Rows[2].w, m_Rows[3].w);
}

// dMat4::SetCol : void (const int, const dVec4 &)
inline void dMat4::SetCol(const int Index, const dVec4 &u) {
	cAssert(Index >= 0 && Index < 4);
	m_Rows[0][Index] = u.x;
	m_Rows[1][Index] = u.y;
	m_Rows[2][Index] = u.z;
	m_Rows[3][Index] = u.w;
}

// dMat4::SetCol0 : void (const dVec4 &)
inline void dMat4::SetCol0(const dVec4 &u) {
	m_Rows[0].x = u.x;
	m_Rows[1].x = u.y;
	m_Rows[2].x = u.z;
	m_Rows[3].x = u.w;
}

// dMat4::SetCol1 : void (const dVec4 &)
inline void dMat4::SetCol1(const dVec4 &u) {
	m_Rows[0].y = u.x;
	m_Rows[1].y = u.y;
	m_Rows[2].y = u.z;
	m_Rows[3].y = u.w;
}

// dMat4::SetCol2 : void (const dVec4 &)
inline void dMat4::SetCol2(const dVec4 &u) {
	m_Rows[0].z = u.x;
	m_Rows[1].z = u.y;
	m_Rows[2].z = u.z;
	m_Rows[3].z = u.w;
}

// dMat4::SetCol3 : void (const dVec4 &)
inline void dMat4::SetCol3(const dVec4 &u) {
	m_Rows[0].w = u.x;
	m_Rows[1].w = u.y;
	m_Rows[2].w = u.z;
	m_Rows[3].w = u.w;
}

// dMat4::SetCol : void (const int, const double, const double, const double, const double)
inline void dMat4::SetCol(const int Index, const double X, const double Y, const double Z, const double W) {
	cAssert(Index >= 0 && Index < 4);
	m_Rows[0][Index] = X;
	m_Rows[1][Index] = Y;
	m_Rows[2][Index] = Z;
	m_Rows[3][Index] = W;
}

// dMat4::SetCol0 : void (const double, const double, const double, const double)
inline void dMat4::SetCol0(const double X, const double Y, const double Z, const double W) {
	m_Rows[0].x = X;
	m_Rows[1].x = Y;
	m_Rows[2].x = Z;
	m_Rows[3].x = W;
}

// dMat4::SetCol1 : void (const double, const double, const double, const double)
inline void dMat4::SetCol1(const double X, const double Y, const double Z, const double W) {
	m_Rows[0].y = X;
	m_Rows[1].y = Y;
	m_Rows[2].y = Z;
	m_Rows[3].y = W;
}

// dMat4::SetCol2 : void (const double, const double, const double, const double)
inline void dMat4::SetCol2(const double X, const double Y, const double Z, const double W) {
	m_Rows[0].z = X;
	m_Rows[1].z = Y;
	m_Rows[2].z = Z;
	m_Rows[3].z = W;
}

// dMat4::SetCol3 : void (const double, const double, const double, const double)
inline void dMat4::SetCol3(const double X, const double Y, const double Z, const double W) {
	m_Rows[0].w = X;
	m_Rows[1].w = Y;
	m_Rows[2].w = Z;
	m_Rows[3].w = W;
}

// dMat4::SetElem : double (int, int, double)
inline void dMat4::SetElem(int Row, int Col, double Value) {
	cAssert(Row >= 0 && Row < 4);
	cAssert(Col >= 0 && Col < 4);
	m_Rows[Row][Col] = Value;
}

// dMat4::GetElem : double (const int, const int) const
inline double dMat4::GetElem(const int Row, const int Col) const {
	cAssert(Row >= 0 && Row < 4);
	cAssert(Col >= 0 && Col < 4);
	return m_Rows[Row][Col];
}

// dMat4::Elem : double & (const int, const int)
inline double & dMat4::Elem(const int Row, const int Col) {
	cAssert(Row >= 0 && Row < 4);
	cAssert(Col >= 0 && Col < 4);
	return m_Rows[Row][Col];
}

// dMat4::operator [] : dVec4 & (const int)
inline dVec4 & dMat4::operator [] (const int Row) {
	cAssert(Row >= 0 && Row < 4);
	return m_Rows[Row];
}

// dMat4::operator [] : const dVec4 & (const int) const
inline const dVec4 & dMat4::operator [] (const int Row) const {
	cAssert(Row >= 0 && Row < 4);
	return m_Rows[Row];
}

// dMat4::operator () : double & (const int, const int)
inline double & dMat4::operator () (const int Row, const int Col) {
	cAssert(Row >= 0 && Row < 4 && Col >= 0 && Col < 4);
	return m_Rows[Row][Col];
}

// dMat4::operator () : double(const int, const int) const
inline double dMat4::operator () (const int Row, const int Col) const {
	cAssert(Row >= 0 && Row < 4 && Col >= 0 && Col < 4);
	return m_Rows[Row][Col];
}

// dMat4::operator - : const dMat4 () const
inline const dMat4 dMat4::operator - () const {
	return Mul(*this, -1.0);
}

// dMat4::Add : void (const dMat4 &)
inline void dMat4::Add(const dMat4 &R) {
	double *l = (double *)this;
	const double *r = (const double *)&R;

	for(int i = 0; i < 16; i++) {
		*l++ += *r++;
	}
}

// dMat4::operator +=
inline void dMat4::operator += (const dMat4 &R) {
	Add(R);
}

// dMat4::Add : const dMat4 (const dMat4 &, const dMat4 &)
inline const dMat4 dMat4::Add(const dMat4 &L, const dMat4 &R) {
	const double *l = (const double *)&L;
	const double *r = (const double *)&R;

	dMat4 S;
	double *s = (double *)&S;

	for(int i = 0; i < 16; i++) {
		*s++ = *l++ + *r++;
	}

	return S;
}

// dMat4::operator +
inline const dMat4 dMat4::operator + (const dMat4 &R) const {
	return Add(*this, R);
}

// dMat4::Sub : void (const dMat4 &)
inline void dMat4::Sub(const dMat4 &R) {
	double *l = (double *)this;
	const double *r = (const double *)&R;

	for(int i = 0; i < 16; i++) {
		*l++ -= *r++;
	}
}

// dMat4::operator -=
inline void dMat4::operator -= (const dMat4 &R) {
	Sub(R);
}

// dMat4::Sub : const dMat4 (const dMat4 &, const dMat4 &)
inline const dMat4 dMat4::Sub(const dMat4 &L, const dMat4 &R) {
	const double *l = (const double *)&L;
	const double *r = (const double *)&R;
	
	dMat4 D;
	double *d = (double *)&D;

	for(int i = 0; i < 16; i++) {
		*d++ = *l++ - *r++;
	}
	return D;
}

// dMat4::operator -
inline const dMat4 dMat4::operator - (const dMat4 &R) const {
	return Sub(*this, R);
}

// dMat4::Mul : void (const dMat4 &)
inline void dMat4::Mul(const dMat4 &R) {
	double *l = reinterpret_cast<double *>(this);
	const double *r = reinterpret_cast<const double *>(&R);
	
	double t[4];
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			t[j] = l[0] * r[0 * 4 + j] + l[1] * r[1 * 4 + j] + l[2] * r[2 * 4 + j] + l[3] * r[3 * 4 + j];
		}
		l[0] = t[0];
		l[1] = t[1];
		l[2] = t[2];
		l[3] = t[3];
		l += 4;
	}
}

// dMat4::operator *=
inline void dMat4::operator *= (const dMat4 &R) {
	Mul(R);
}

// dMat4::Mul : void (const double)
inline void dMat4::Mul(const double s) {
	double *l = (double *)this;
	for(int i = 0; i < 16; i++) {
		*l++ *= s;
	}
}

// dMat4::operator *= : void (const double)
inline void dMat4::operator *= (const double s) {
	Mul(s);
}

// dMat4::operator /= : void (const double)
inline void dMat4::operator /= (const double s) {
	double is = 1.0 / s;
	Mul(is);
}

//-----------------------------------------------------------------------------
// dMat4::Mul : const dMat4 (const dMat4 &, const dMat4 &)
//-----------------------------------------------------------------------------
inline const dMat4 dMat4::Mul(const dMat4 &L, const dMat4 &R) {
	const double *l = reinterpret_cast<const double *>(&L);
	const double *r = reinterpret_cast<const double *>(&R);
	dMat4 M;
	double *m = reinterpret_cast<double *>(&M);
	
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			*m = l[0] * r[0 * 4 + j] + l[1] * r[1 * 4 + j] + l[2] * r[2 * 4 + j] + l[3] * r[3 * 4 + j];
			m++;
		}
		l += 4;
	}
	return M;
} // dMat4::Mul

// dMat4::operator * : const dMat4 (const dMat4 &) const
inline const dMat4 dMat4::operator * (const dMat4 &R) const {
	return Mul(*this, R);
}

// dMat4::Mul : const dMat4 (const dMat4 &, const double)
inline const dMat4 dMat4::Mul(const dMat4 &L, const double s) {
	dMat4 M;
	double *m = (double *)&M;
	const double *l = (const double *)&L;

	for(int i = 0; i < 16; i++) {
		*m++ = *l++ * s;
	}
	return M;
}

// dMat4::operator * : const dMat4 (const double) const
inline const dMat4 dMat4::operator * (const double s) const {
	return Mul(*this, s);
}

// operator * : const dMat4 (const double, const dMat4 &)
inline const dMat4 operator * (const double s, const dMat4 &R) {
	return dMat4::Mul(R, s);
}

// dMat4::operator / : const dMat4 (const double) const
inline const dMat4 dMat4::operator / (const double s) const {
	double is = 1.0 / s;
	return Mul(*this, is);
}

// dMat4::Trace
inline double dMat4::Trace() const {
	return m_Rows[0][0] + m_Rows[1][1] + m_Rows[2][2] + m_Rows[3][3];
}

// dMat4::operator == : bool(const dMat4 &) const
inline bool dMat4::operator == (const dMat4 &u) const {
	return dMat4::Equals( *this, u );
}

// dMat4::Equals
inline bool dMat4::Equals(const dMat4 &P, const dMat4 &Q, const double Eps) {
	if(dVec4::Equals(P[0], Q[0], Eps) && dVec4::Equals(P[1], Q[1], Eps) && dVec4::Equals(P[2], Q[2], Eps) && dVec4::Equals(P[3], Q[3], Eps)) {
		return true;
	}
	return false;
}

// dMat4::IsZero
inline bool dMat4::IsZero(double Eps) const {
	return Equals(*this, Zero, Eps);
}

// dMat4::IsIdentity
inline bool dMat4::IsIdentity(double Eps) const {
	return Equals(*this, Identity, Eps);
}

// dMat4::IsSymmetric
inline bool dMat4::IsSymmetric( double Eps ) const {
    if ( !cMath::Equals( m_Rows[ 0 ][ 1 ], m_Rows[ 1 ][ 0 ], Eps ) ) {
        return false;
    }
    if ( !cMath::Equals( m_Rows[ 0 ][ 2 ], m_Rows[ 2 ][ 0 ], Eps ) ) {
        return false;
    }
    if ( !cMath::Equals( m_Rows[ 1 ][ 2 ], m_Rows[ 2 ][ 1 ], Eps ) ) {
        return false;
    }
    if ( !cMath::Equals( m_Rows[ 0 ][ 3 ], m_Rows[ 3 ][ 0 ], Eps ) ) {
        return false;
    }
    if ( !cMath::Equals( m_Rows[ 1 ][ 3 ], m_Rows[ 3 ][ 1 ], Eps ) ) {
        return false;
    }
    if ( !cMath::Equals( m_Rows[ 2 ][ 3 ], m_Rows[ 3 ][ 2 ], Eps ) ) {
        return false;
    }
    return true;
}

// dMat4::IsOrthonormal
inline bool dMat4::IsOrthonormal( double Eps ) const {
    return cMath::IsOne( Determinant(), Eps );
}

// dMat4::ToFloatPtr : const double * () const
inline const double * dMat4::ToFloatPtr() const {
	return m_Rows[0].ToFloatPtr();
}

// dMat4::ToFloatPtr : double * ()
inline double * dMat4::ToFloatPtr() {
	return m_Rows[0].ToFloatPtr();
}

// dMat4::GetTranslation
inline const dVec3 dMat4::GetTranslation() const {
	return m_Rows[3].ToVec3();
}

// dMat4::SetTranslation
inline void dMat4::SetTranslation( const dVec3& c ) {
    m_Rows[ 3 ].x = c.x;
    m_Rows[ 3 ].y = c.y;
    m_Rows[ 3 ].z = c.z;
}

// dMat4::GetScaling
inline const dVec3 dMat4::GetScaling() const {
	return dVec3(m_Rows[0].ToVec3().Length(), m_Rows[1].ToVec3().Length(), m_Rows[2].ToVec3().Length());
}

// dMat4::SetScaling
inline void dMat4::SetScaling( const dVec3& s ) {
    m_Rows[ 0 ].x = s.x;
    m_Rows[ 1 ].y = s.y;
    m_Rows[ 2 ].z = s.z;
}

// dMat4::Transpose : const dMat4 (const dMat4 &)
inline const dMat4 dMat4::Transpose(const dMat4 &M) {
	dMat4 T;
	for(int i = 0; i < 4; i++) {
		T.SetRow(i, M.GetCol(i));
	}
	return T;
}

// dMat4::Transpose : void ()
inline void dMat4::Transpose() {
	cMath::Swap(m_Rows[0][1], m_Rows[1][0]);
	cMath::Swap(m_Rows[0][2], m_Rows[2][0]);
	cMath::Swap(m_Rows[1][2], m_Rows[2][1]);
	cMath::Swap(m_Rows[0][3], m_Rows[3][0]);
	cMath::Swap(m_Rows[1][3], m_Rows[3][1]);
	cMath::Swap(m_Rows[2][3], m_Rows[3][2]);
}

//*****************************************************************************
// dVec2 & dMat4
//*****************************************************************************

// dVec2::Transform : const dVec4 (const dVec2 &, const dMat4 &)
inline const dVec4 dVec2::Transform(const dVec2 &u, const dMat4 &T) {
	dVec4 r;
	r.x = u.x * T(0, 0) + u.y * T(1, 0) + T(3, 0);
	r.y = u.x * T(0, 1) + u.y * T(1, 1) + T(3, 1);
	r.z = u.x * T(0, 2) + u.y * T(1, 2) + T(3, 2);
	r.w = u.x * T(0, 3) + u.y * T(1, 3) + T(3, 3);
	return r;
}

// dVec2::TransformCoordinate : const dVec2 (const dVec2 &, const dMat4 &)
inline const dVec2 dVec2::TransformCoordinate(const dVec2 &u, const dMat4 &T) {
	dVec2 r;
	r.x = u.x * T(0, 0) + u.y * T(1, 0) + T(3, 0);
	r.y = u.x * T(0, 1) + u.y * T(1, 1) + T(3, 1);
	double w = u.x * T(0, 3) + u.y * T(1, 3) + T(3, 3);
	if(w != 1.0) {
		double iw = 1.0 / w;
		r.x *= iw;
		r.y *= iw;
	}
	return r;
}

// dVec2::TransformCoordinate : void (const dMat4 &)
inline void dVec2::TransformCoordinate(const dMat4 &T) {
	*this = TransformCoordinate(*this, T);
}

// dVec2::TransformNormal : const dVec2 (const dVec2 &, const dMat4 &)
inline const dVec2 dVec2::TransformNormal(const dVec2 &u, const dMat4 &T) {
	dVec2 r;
	r.x = u.x * T(0, 0) + u.y * T(1, 0);
	r.y = u.x * T(0, 1) + u.y * T(1, 1);
	return r;
}

// dVec2::TransformNormal : void (const dMat4 &)
inline void dVec2::TransformNormal(const dMat4 &T) {
	*this = TransformNormal(*this, T);
}

//*****************************************************************************
// dVec3 & dMat4
//*****************************************************************************

// dVec3::Transform
inline const dVec4 dVec3::Transform(const dVec3 &u, const dMat4 &M) {
	dVec4 t;
	t.x = u.x * M[0][0] + u.y * M[1][0] + u.z * M[2][0] + M[3][0];
	t.y = u.x * M[0][1] + u.y * M[1][1] + u.z * M[2][1] + M[3][1];
	t.z = u.x * M[0][2] + u.y * M[1][2] + u.z * M[2][2] + M[3][2];
	t.w = u.x * M[0][3] + u.y * M[1][3] + u.z * M[2][3] + M[3][3];
	return t;
}

// dVec3::TransformCoordinate : const dVec3 (const dVec3 &, const dMat4 &)
inline const dVec3 dVec3::TransformCoordinate(const dVec3 &u, const dMat4 &T) {
	dVec3 r;
	r.x = u.x * T(0, 0) + u.y * T(1, 0) + u.z * T(2, 0) + T(3, 0);
	r.y = u.x * T(0, 1) + u.y * T(1, 1) + u.z * T(2, 1) + T(3, 1);
	r.z = u.x * T(0, 2) + u.y * T(1, 2) + u.z * T(2, 2) + T(3, 2);
	double w = u.x * T(0, 3) + u.y * T(1, 3) + u.z * T(2, 3) + T(3, 3);
	if(w != 1.0) {
		double iw = 1.0 / w;
		r.x *= iw;
		r.y *= iw;
		r.z *= iw;
	}
	return r;
}

// dVec3::TransformCoordinate : void (const dMat4 &)
inline void dVec3::TransformCoordinate(const dMat4 &T) {
	*this = TransformCoordinate(*this, T);
}

// dVec3::TransformNormal
inline const dVec3 dVec3::TransformNormal(const dVec3 &u, const dMat4 &T) {
	dVec3 r;
	r.x = u.x * T(0, 0) + u.y * T(1, 0) + u.z * T(2, 0);
	r.y = u.x * T(0, 1) + u.y * T(1, 1) + u.z * T(2, 1);
	r.z = u.x * T(0, 2) + u.y * T(1, 2) + u.z * T(2, 2);
	return r;
}

// dVec3::TransformNormal
inline void dVec3::TransformNormal(const dMat4 &T) {
	*this = TransformNormal(*this, T);
}

// dVec3::TransformNormalTransposed
inline void dVec3::TransformNormalTransposed(const dMat4 &T) {
	dVec3 u = *this;
	x = u.x * T(0, 0) + u.y * T(0, 1) + u.z * T(0, 2);
	y = u.x * T(1, 0) + u.y * T(1, 1) + u.z * T(1, 2);
	z = u.x * T(2, 0) + u.y * T(2, 1) + u.z * T(2, 2);
}

//*****************************************************************************
// dVec4 & dMat4
//*****************************************************************************

// dVec4::Transform : const dVec4 (const dVec4 &, const dMat4 &)
inline const dVec4 dVec4::Transform(const dVec4 &u, const dMat4 &T) {
	dVec4 r;
	r.x = u.x * T(0, 0) + u.y * T(1, 0) + u.z * T(2, 0) + u.w * T(3, 0);
	r.y = u.x * T(0, 1) + u.y * T(1, 1) + u.z * T(2, 1) + u.w * T(3, 1);
	r.z = u.x * T(0, 2) + u.y * T(1, 2) + u.z * T(2, 2) + u.w * T(3, 2);
	r.w = u.x * T(0, 3) + u.y * T(1, 3) + u.z * T(2, 3) + u.w * T(3, 3);
	return r;
}

// dVec4::Transform : void (const dMat4 &)
inline void dVec4::Transform(const dMat4 &T) {
	*this = Transform(*this, T);
}

// dVec4::operator *= : void (const dMat4 &)
inline void dVec4::operator *= (const dMat4 &T) {
	*this = Transform(*this, T);
}

// dVec4::operator * : const dVec4 (const dMat4 &) const
inline const dVec4 dVec4::operator * (const dMat4 &T) const {
	return Transform(*this, T);
}

//*****************************************************************************
// dMat3 & dMat4
//*****************************************************************************

// dMat3::ToMat4
inline const dMat4 dMat3::ToMat4() const {
	return dMat4(*this, dVec3::Zero);
}

// dMat4::ToMat3
inline const dMat3 dMat4::ToMat3() const {
	return dMat3(dMat3::RowsCtor, m_Rows[0].ToVec3(), m_Rows[1].ToVec3(), m_Rows[2].ToVec3());
}




::std::ostream& operator<<( ::std::ostream&,  const dMat4& );
