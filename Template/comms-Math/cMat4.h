#pragma once

//*****************************************************************************
// cMat4
//*****************************************************************************
class cMat4 {
public:
	enum EZeroCtor		{ ZeroCtor };
	enum EIdentityCtor	{ IdentityCtor };
	enum ERowsCtor		{ RowsCtor };
	enum EColsCtor		{ ColsCtor };

	cMat4();
	cMat4(const EZeroCtor);
	cMat4(const EIdentityCtor);
	cMat4(const ERowsCtor, const cVec4 &Row0, const cVec4 &Row1, const cVec4 &Row2, const cVec4 &Row3);
	cMat4(const EColsCtor, const cVec4 &Col0, const cVec4 &Col1, const cVec4 &Col2, const cVec4 &Col3);
	cMat4(const cMat3 &Rotation, const cVec3 &Translation);
	cMat4(const cVec3 &Scaling, const cVec3 &Translation);
	cMat4(const float _00, const float _01, const float _02, const float _03,
		const float _10, const float _11, const float _12, const float _13,
		const float _20, const float _21, const float _22, const float _23,
		const float _30, const float _31, const float _32, const float _33);
	
	void Copy(const float *Float16);
	void CopyTransposed(const float *Float16);
	
	void SetZero();
	void SetIdentity();

	const cVec4 & GetRow(const int Index) const;
	const cVec4 & GetRow0() const;
	const cVec4 & GetRow1() const;
	const cVec4 & GetRow2() const;
	const cVec4 & GetRow3() const;

	cVec4 & Row(const int Index);
	cVec4 & Row0();
	cVec4 & Row1();
	cVec4 & Row2();
	cVec4 & Row3();

	void SetRow(const int Index, const cVec4 &);
	void SetRow0(const cVec4 &);
	void SetRow1(const cVec4 &);
	void SetRow2(const cVec4 &);
	void SetRow3(const cVec4 &);

	void SetRow(const int Index, const float X, const float Y, const float Z, const float W);
	void SetRow0(const float X, const float Y, const float Z, const float W);
	void SetRow1(const float X, const float Y, const float Z, const float W);
	void SetRow2(const float X, const float Y, const float Z, const float W);
	void SetRow3(const float X, const float Y, const float Z, const float W);

	const cVec4 GetCol(const int Index) const;
	const cVec4 GetCol0() const;
	const cVec4 GetCol1() const;
	const cVec4 GetCol2() const;
	const cVec4 GetCol3() const;

	void SetCol(const int Index, const cVec4 &);
	void SetCol0(const cVec4 &);
	void SetCol1(const cVec4 &);
	void SetCol2(const cVec4 &);
	void SetCol3(const cVec4 &);

	void SetCol(const int Index, const float X, const float Y, const float Z, const float W);
	void SetCol0(const float X, const float Y, const float Z, const float W);
	void SetCol1(const float X, const float Y, const float Z, const float W);
	void SetCol2(const float X, const float Y, const float Z, const float W);
	void SetCol3(const float X, const float Y, const float Z, const float W);

	void SetElem(int Row, int Col, float Value);
	float GetElem(const int Row, const int Col) const;
	float & Elem(const int Row, const int Col);

	const cVec4 & operator [] (const int Row) const;
	cVec4 & operator [] (const int Row);

	float operator () (const int Row, const int Col) const;
	float & operator () (const int Row, const int Col);

	float Trace() const;
	float Determinant() const;

	bool operator == (const cMat4 &) const;
	static bool Equals(const cMat4 &, const cMat4 &, const float Eps = cMath::MatrixEpsilon);
	
	bool IsZero(float Eps = cMath::MatrixEpsilon) const;
	bool IsIdentity(float Eps = cMath::MatrixEpsilon) const;
    bool IsSymmetric( float Eps = cMath::MatrixEpsilon ) const;
    bool IsOrthonormal( float Eps = cMath::MatrixEpsilon ) const;

	const cMat4 operator - () const;

	void operator += (const cMat4 &R);
	void operator -= (const cMat4 &R);
	void operator *= (const cMat4 &R);
	void operator *= (const float);
	void operator /= (const float);

	const cMat4 operator + (const cMat4 &R) const;
	const cMat4 operator - (const cMat4 &R) const;
	const cMat4 operator * (const cMat4 &R) const;
	const cMat4 operator * (const float) const;
	friend const cMat4 operator * (const float, const cMat4 &);
	const cMat4 operator / (const float) const;

	void Add(const cMat4 &R);
	void Sub(const cMat4 &R);
	void Mul(const cMat4 &R);
	void Mul(const float s);
	
	static const cMat4 Add(const cMat4 &L, const cMat4 &R);
	static const cMat4 Sub(const cMat4 &L, const cMat4 &R);
	static const cMat4 Mul(const cMat4 &L, const cMat4 &R);
	static const cMat4 Mul(const cMat4 &L, const float s);

	const float * ToFloatPtr() const;
	float * ToFloatPtr();
	
	const cStr ToString(const int Prec = 2) const;

	const cMat3 ToMat3() const;
	const cMat3 ToNormalMatrix() const;
	const cQuat ToQuat() const;
	
    const cVec3 GetTranslation() const;
    void SetTranslation( const cVec3 & );

	const cVec3 GetScaling() const;
    void SetScaling( const cVec3 & );

    cAngles GetRotation() const;
    void SetRotation( const cAngles & );

	static const cMat4 Transpose(const cMat4 &);
	void Transpose();

	static bool Invert(const cMat4 &Fm, cMat4 *To);
	bool Invert() { return Invert(*this, this); }
	
	static const cMat4 Zero;
	static const cMat4 Identity;
	
	static const cMat4 Translation(const float X, const float Y);
	static const cMat4 Translation(const float X, const float Y, const float Z);
	static const cMat4 Translation(const cVec2 &XY);
	static const cMat4 Translation(const cVec3 &XYZ);

	static const cMat4 Rotation(const cVec3 &Axis, const float Angle);
	static const cMat4 RotationX(const float Angle);
	static const cMat4 RotationY(const float Angle);
	static const cMat4 RotationZ(const float Angle);
	static const cMat4 RotationXYZ(const float Pitch, const float Yaw, const float Roll);
	static const cMat4 EulerZYX(const float eulerX, const float eulerY, const float eulerZ);
	
	static const cMat4 RotationAt(const cVec2 &Orig, const float Angle);
	static const cMat4 RotationAt(const cVec3 &Orig, const cVec3 &Axis, const float Angle);
	
	static const cMat4 Scaling(const float XYZ);
	static const cMat4 Scaling(const float X, const float Y);
	static const cMat4 Scaling(const float X, const float Y, const float Z);
	static const cMat4 Scaling(const cVec2 &XY);
	static const cMat4 Scaling(const cVec3 &XYZ);
	
	static const cMat4 ScalingAt(const float OrigX, const float OrigY, const float ScaleXY);
	static const cMat4 ScalingAt(const float OrigX, const float OrigY, const float ScaleX, const float ScaleY);

	static const cMat4 ScalingAt(const cVec2 &Orig, const float ScaleXY);
	static const cMat4 ScalingAt(const cVec2 &Orig, const float ScaleX, const float ScaleY);
	static const cMat4 ScalingAt(const cVec2 &Orig, const cVec2 &Scale);

	static const cMat4 ScalingAt(const cVec3 &Orig, const float ScaleXYZ);
	static const cMat4 ScalingAt(const cVec3 &Orig, const float ScaleX, const float ScaleY, const float ScaleZ);
	static const cMat4 ScalingAt(const cVec3 &Orig, const cVec3 &Scale);
	static const cMat4 ScalingAt(const cVec3 &Orig, const cVec3 &Dir, float Scale);

	static const cMat4 Perspective(float YFov, float AspectWtoH, float Znear, float Zfar);
	static const cMat4 PerspectiveInf(const float YFov, const float AspectWtoH, const float Znear);
	
	static const cMat4 Ortho(const float Width, const float Height, const float Znear, const float Zfar);
	static const cMat4 Ortho(const float Left, const float Right, const float Bottom, const float Top, const float Znear, const float Zfar);
	static const cMat4 Ortho(const cBounds &B);

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
	static const cMat4 CubeViewProjection(const cVec3 &Pos, const int Side, const float Radius, const bool GL);
	static const cMat4 LookAtViewProjection(const cVec3 &LookFrom, const cVec3 &LookAt, const float FovY, const float AspectYtoH, const float Znear, const float Zfar);
private:
	cVec4 m_Rows[4];
};

// cMat4.ctor : ()
inline cMat4::cMat4() {
}

// cMat4.ctor : (const ERowsCtor, const cVec4 &, const cVec4 &, const cVec4 &, const cVec4 &)
inline cMat4::cMat4(const ERowsCtor, const cVec4 &Row0, const cVec4 &Row1, const cVec4 &Row2, const cVec4 &Row3) {
	m_Rows[0] = Row0;
	m_Rows[1] = Row1;
	m_Rows[2] = Row2;
	m_Rows[3] = Row3;
}

// cMat4.ctor : (const EColsCtor, const cVec4 &, const cVec4 &, const cVec4 &, const cVec4 &)
inline cMat4::cMat4(const EColsCtor, const cVec4 &Col0, const cVec4 &Col1, const cVec4 &Col2, const cVec4 &Col3) {
	m_Rows[0].Set(Col0.x, Col1.x, Col2.x, Col3.x);
	m_Rows[1].Set(Col0.y, Col1.y, Col2.y, Col3.y);
	m_Rows[2].Set(Col0.z, Col1.z, Col2.z, Col3.z);
	m_Rows[3].Set(Col0.w, Col1.w, Col2.w, Col3.w);
}

// cMat4.ctor : (const EZeroCtor)
inline cMat4::cMat4(const EZeroCtor) {
	m_Rows[0].SetZero();
	m_Rows[1].SetZero();
	m_Rows[2].SetZero();
	m_Rows[3].SetZero();
}

// cMat4.ctor : (const EIdentityCtor)
inline cMat4::cMat4(const EIdentityCtor) {
	m_Rows[0].Set(1.0f, 0.0f, 0.0f, 0.0f);
	m_Rows[1].Set(0.0f, 1.0f, 0.0f, 0.0f);
	m_Rows[2].Set(0.0f, 0.0f, 1.0f, 0.0f);
	m_Rows[3].Set(0.0f, 0.0f, 0.0f, 1.0f);
}

// cMat4.ctor : (const cMat3 &, const cVec3 &)
inline cMat4::cMat4(const cMat3 &Rotation, const cVec3 &Translation) {
	m_Rows[0].Set(Rotation.GetRow0(), 0.0f);
	m_Rows[1].Set(Rotation.GetRow1(), 0.0f);
	m_Rows[2].Set(Rotation.GetRow2(), 0.0f);
	m_Rows[3].Set(Translation, 1.0f);
}

// cMat4.ctor : (const cVec3 &, const cVec3 &)
inline cMat4::cMat4(const cVec3 &Scaling, const cVec3 &Translation) {
	m_Rows[0].Set(Scaling[0], 0.0f, 0.0f, 0.0f);
	m_Rows[1].Set(0.0f, Scaling[1], 0.0f, 0.0f);
	m_Rows[2].Set(0.0f, 0.0f, Scaling[2], 0.0f);
	m_Rows[3].Set(Translation, 1.0f);
}

// cMat4.ctor
inline cMat4::cMat4(const float _00, const float _01, const float _02, const float _03,
					const float _10, const float _11, const float _12, const float _13,
					const float _20, const float _21, const float _22, const float _23,
					const float _30, const float _31, const float _32, const float _33) {
	m_Rows[0].Set(_00, _01, _02, _03);
	m_Rows[1].Set(_10, _11, _12, _13);
	m_Rows[2].Set(_20, _21, _22, _23);
	m_Rows[3].Set(_30, _31, _32, _33);
}

// cMat4::Copy
inline void cMat4::Copy(const float *Float16) {
	m_Rows[0].Set(Float16[0], Float16[1], Float16[2], Float16[3]);
	m_Rows[1].Set(Float16[4], Float16[5], Float16[6], Float16[7]);
	m_Rows[2].Set(Float16[8], Float16[9], Float16[10], Float16[11]);
	m_Rows[3].Set(Float16[12], Float16[13], Float16[14], Float16[15]);
}

// cMat4::CopyTransposed
inline void cMat4::CopyTransposed(const float *Float16) {
	m_Rows[0].Set(Float16[0], Float16[4], Float16[8], Float16[12]);
	m_Rows[1].Set(Float16[1], Float16[5], Float16[9], Float16[13]);
	m_Rows[2].Set(Float16[2], Float16[6], Float16[10], Float16[14]);
	m_Rows[3].Set(Float16[3], Float16[7], Float16[11], Float16[15]);
}

// cMat4::SetZero
inline void cMat4::SetZero() {
	m_Rows[0].SetZero();
	m_Rows[1].SetZero();
	m_Rows[2].SetZero();
	m_Rows[3].SetZero();
}

// cMat4::SetIdentity
inline void cMat4::SetIdentity() {
	m_Rows[0].Set(1.0f, 0.0f, 0.0f, 0.0f);
	m_Rows[1].Set(0.0f, 1.0f, 0.0f, 0.0f);
	m_Rows[2].Set(0.0f, 0.0f, 1.0f, 0.0f);
	m_Rows[3].Set(0.0f, 0.0f, 0.0f, 1.0f);
}

// cMat4::GetRow : const cVec4 & (const int) const
inline const cVec4 & cMat4::GetRow(const int Index) const {
	cAssert(Index >= 0 && Index < 4);
	return m_Rows[Index];
}

// cMat4::GetRow0 : const cVec4 & () const
inline const cVec4 & cMat4::GetRow0() const {
	return m_Rows[0];
}

// cMat4::GetRow1 : const cVec4 & () const
inline const cVec4 & cMat4::GetRow1() const {
	return m_Rows[1];
}

// cMat4::GetRow2 : const cVec4 & () const
inline const cVec4 & cMat4::GetRow2() const {
	return m_Rows[2];
}

// cMat4::GetRow3 : const cVec4 & () const
inline const cVec4 & cMat4::GetRow3() const {
	return m_Rows[3];
}

// cMat4::Row : cVec4 & (const int)
inline cVec4 & cMat4::Row(const int Index) {
	cAssert(Index >= 0 && Index < 4);
	return m_Rows[Index];
}

// cMat4::Row0 : cVec4 & ()
inline cVec4 & cMat4::Row0() {
	return m_Rows[0];
}

// cMat4::Row1 : cVec4 & ()
inline cVec4 & cMat4::Row1() {
	return m_Rows[1];
}

// cMat4::Row2 : cVec4 & ()
inline cVec4 & cMat4::Row2() {
	return m_Rows[2];
}

// cMat4::Row3 : cVec4 & ()
inline cVec4 & cMat4::Row3() {
	return m_Rows[3];
}

// cMat4::SetRow : void (const int, const cVec4 &)
inline void cMat4::SetRow(const int Index, const cVec4 &r) {
	cAssert(Index >= 0 && Index < 4);
	m_Rows[Index] = r;
}

// cMat4::SetRow0 : void (const cVec4 &)
inline void cMat4::SetRow0(const cVec4 &r) {
	m_Rows[0] = r;
}

// cMat4::SetRow1 : void (const cVec4 &)
inline void cMat4::SetRow1(const cVec4 &r) {
	m_Rows[1] = r;
}

// cMat4::SetRow2 : void (const cVec4 &)
inline void cMat4::SetRow2(const cVec4 &r) {
	m_Rows[2] = r;
}

// cMat4::SetRow3 : void (const cVec4 &)
inline void cMat4::SetRow3(const cVec4 &r) {
	m_Rows[3] = r;
}

// cMat4::SetRow : void (const int, const float, const float, const float, const float)
inline void cMat4::SetRow(const int Index, const float X, const float Y, const float Z, const float W) {
	cAssert(Index >= 0 && Index < 4);
	m_Rows[Index].Set(X, Y, Z, W);
}

// cMat4::SetRow0 : void (const float, const float, const float, const float)
inline void cMat4::SetRow0(const float X, const float Y, const float Z, const float W) {
	m_Rows[0].Set(X, Y, Z, W);
}

// cMat4::SetRow1 : void (const float, const float, const float, const float)
inline void cMat4::SetRow1(const float X, const float Y, const float Z, const float W) {
	m_Rows[1].Set(X, Y, Z, W);
}

// cMat4::SetRow2 : void (const float, const float, const float, const float)
inline void cMat4::SetRow2(const float X, const float Y, const float Z, const float W) {
	m_Rows[2].Set(X, Y, Z, W);
}

// cMat4::SetRow3 : void (const float, const float, const float, const float)
inline void cMat4::SetRow3(const float X, const float Y, const float Z, const float W) {
	m_Rows[3].Set(X, Y, Z, W);
}

// cMat4::GetCol
inline const cVec4 cMat4::GetCol(const int Index) const {
	cAssert(Index >= 0 && Index < 4);
	return cVec4(m_Rows[0][Index], m_Rows[1][Index], m_Rows[2][Index], m_Rows[3][Index]);
}

// cMat4::GetCol0
inline const cVec4 cMat4::GetCol0() const {
	return cVec4(m_Rows[0].x, m_Rows[1].x, m_Rows[2].x, m_Rows[3].x);
}

// cMat4::GetCol1
inline const cVec4 cMat4::GetCol1() const {
	return cVec4(m_Rows[0].y, m_Rows[1].y, m_Rows[2].y, m_Rows[3].y);
}

// cMat4::GetCol2
inline const cVec4 cMat4::GetCol2() const {
	return cVec4(m_Rows[0].z, m_Rows[1].z, m_Rows[2].z, m_Rows[3].z);
}

// cMat4::GetCol3
inline const cVec4 cMat4::GetCol3() const {
	return cVec4(m_Rows[0].w, m_Rows[1].w, m_Rows[2].w, m_Rows[3].w);
}

// cMat4::SetCol : void (const int, const cVec4 &)
inline void cMat4::SetCol(const int Index, const cVec4 &u) {
	cAssert(Index >= 0 && Index < 4);
	m_Rows[0][Index] = u.x;
	m_Rows[1][Index] = u.y;
	m_Rows[2][Index] = u.z;
	m_Rows[3][Index] = u.w;
}

// cMat4::SetCol0 : void (const cVec4 &)
inline void cMat4::SetCol0(const cVec4 &u) {
	m_Rows[0].x = u.x;
	m_Rows[1].x = u.y;
	m_Rows[2].x = u.z;
	m_Rows[3].x = u.w;
}

// cMat4::SetCol1 : void (const cVec4 &)
inline void cMat4::SetCol1(const cVec4 &u) {
	m_Rows[0].y = u.x;
	m_Rows[1].y = u.y;
	m_Rows[2].y = u.z;
	m_Rows[3].y = u.w;
}

// cMat4::SetCol2 : void (const cVec4 &)
inline void cMat4::SetCol2(const cVec4 &u) {
	m_Rows[0].z = u.x;
	m_Rows[1].z = u.y;
	m_Rows[2].z = u.z;
	m_Rows[3].z = u.w;
}

// cMat4::SetCol3 : void (const cVec4 &)
inline void cMat4::SetCol3(const cVec4 &u) {
	m_Rows[0].w = u.x;
	m_Rows[1].w = u.y;
	m_Rows[2].w = u.z;
	m_Rows[3].w = u.w;
}

// cMat4::SetCol : void (const int, const float, const float, const float, const float)
inline void cMat4::SetCol(const int Index, const float X, const float Y, const float Z, const float W) {
	cAssert(Index >= 0 && Index < 4);
	m_Rows[0][Index] = X;
	m_Rows[1][Index] = Y;
	m_Rows[2][Index] = Z;
	m_Rows[3][Index] = W;
}

// cMat4::SetCol0 : void (const float, const float, const float, const float)
inline void cMat4::SetCol0(const float X, const float Y, const float Z, const float W) {
	m_Rows[0].x = X;
	m_Rows[1].x = Y;
	m_Rows[2].x = Z;
	m_Rows[3].x = W;
}

// cMat4::SetCol1 : void (const float, const float, const float, const float)
inline void cMat4::SetCol1(const float X, const float Y, const float Z, const float W) {
	m_Rows[0].y = X;
	m_Rows[1].y = Y;
	m_Rows[2].y = Z;
	m_Rows[3].y = W;
}

// cMat4::SetCol2 : void (const float, const float, const float, const float)
inline void cMat4::SetCol2(const float X, const float Y, const float Z, const float W) {
	m_Rows[0].z = X;
	m_Rows[1].z = Y;
	m_Rows[2].z = Z;
	m_Rows[3].z = W;
}

// cMat4::SetCol3 : void (const float, const float, const float, const float)
inline void cMat4::SetCol3(const float X, const float Y, const float Z, const float W) {
	m_Rows[0].w = X;
	m_Rows[1].w = Y;
	m_Rows[2].w = Z;
	m_Rows[3].w = W;
}

// cMat4::SetElem : float (int, int, float)
inline void cMat4::SetElem(int Row, int Col, float Value) {
	cAssert(Row >= 0 && Row < 4);
	cAssert(Col >= 0 && Col < 4);
	m_Rows[Row][Col] = Value;
}

// cMat4::GetElem : float (const int, const int) const
inline float cMat4::GetElem(const int Row, const int Col) const {
	cAssert(Row >= 0 && Row < 4);
	cAssert(Col >= 0 && Col < 4);
	return m_Rows[Row][Col];
}

// cMat4::Elem : float & (const int, const int)
inline float & cMat4::Elem(const int Row, const int Col) {
	cAssert(Row >= 0 && Row < 4);
	cAssert(Col >= 0 && Col < 4);
	return m_Rows[Row][Col];
}

// cMat4::operator [] : cVec4 & (const int)
inline cVec4 & cMat4::operator [] (const int Row) {
	cAssert(Row >= 0 && Row < 4);
	return m_Rows[Row];
}

// cMat4::operator [] : const cVec4 & (const int) const
inline const cVec4 & cMat4::operator [] (const int Row) const {
	cAssert(Row >= 0 && Row < 4);
	return m_Rows[Row];
}

// cMat4::operator () : float & (const int, const int)
inline float & cMat4::operator () (const int Row, const int Col) {
	cAssert(Row >= 0 && Row < 4 && Col >= 0 && Col < 4);
	return m_Rows[Row][Col];
}

// cMat4::operator () : float(const int, const int) const
inline float cMat4::operator () (const int Row, const int Col) const {
	cAssert(Row >= 0 && Row < 4 && Col >= 0 && Col < 4);
	return m_Rows[Row][Col];
}

// cMat4::operator - : const cMat4 () const
inline const cMat4 cMat4::operator - () const {
	return Mul(*this, -1.0f);
}

// cMat4::Add : void (const cMat4 &)
inline void cMat4::Add(const cMat4 &R) {
	float *l = (float *)this;
	const float *r = (const float *)&R;

	for(int i = 0; i < 16; i++) {
		*l++ += *r++;
	}
}

// cMat4::operator +=
inline void cMat4::operator += (const cMat4 &R) {
	Add(R);
}

// cMat4::Add : const cMat4 (const cMat4 &, const cMat4 &)
inline const cMat4 cMat4::Add(const cMat4 &L, const cMat4 &R) {
	const float *l = (const float *)&L;
	const float *r = (const float *)&R;

	cMat4 S;
	float *s = (float *)&S;

	for(int i = 0; i < 16; i++) {
		*s++ = *l++ + *r++;
	}

	return S;
}

// cMat4::operator +
inline const cMat4 cMat4::operator + (const cMat4 &R) const {
	return Add(*this, R);
}

// cMat4::Sub : void (const cMat4 &)
inline void cMat4::Sub(const cMat4 &R) {
	float *l = (float *)this;
	const float *r = (const float *)&R;

	for(int i = 0; i < 16; i++) {
		*l++ -= *r++;
	}
}

// cMat4::operator -=
inline void cMat4::operator -= (const cMat4 &R) {
	Sub(R);
}

// cMat4::Sub : const cMat4 (const cMat4 &, const cMat4 &)
inline const cMat4 cMat4::Sub(const cMat4 &L, const cMat4 &R) {
	const float *l = (const float *)&L;
	const float *r = (const float *)&R;
	
	cMat4 D;
	float *d = (float *)&D;

	for(int i = 0; i < 16; i++) {
		*d++ = *l++ - *r++;
	}
	return D;
}

// cMat4::operator -
inline const cMat4 cMat4::operator - (const cMat4 &R) const {
	return Sub(*this, R);
}

// cMat4::Mul : void (const cMat4 &)
inline void cMat4::Mul(const cMat4 &R) {
	float *l = reinterpret_cast<float *>(this);
	const float *r = reinterpret_cast<const float *>(&R);
	
	float t[4];
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

// cMat4::operator *=
inline void cMat4::operator *= (const cMat4 &R) {
	Mul(R);
}

// cMat4::Mul : void (const float)
inline void cMat4::Mul(const float s) {
	float *l = (float *)this;
	for(int i = 0; i < 16; i++) {
		*l++ *= s;
	}
}

// cMat4::operator *= : void (const float)
inline void cMat4::operator *= (const float s) {
	Mul(s);
}

// cMat4::operator /= : void (const float)
inline void cMat4::operator /= (const float s) {
	float is = 1.0f / s;
	Mul(is);
}

//-----------------------------------------------------------------------------
// cMat4::Mul : const cMat4 (const cMat4 &, const cMat4 &)
//-----------------------------------------------------------------------------
inline const cMat4 cMat4::Mul(const cMat4 &L, const cMat4 &R) {
	const float *l = reinterpret_cast<const float *>(&L);
	const float *r = reinterpret_cast<const float *>(&R);
	cMat4 M;
	float *m = reinterpret_cast<float *>(&M);
	
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			*m = l[0] * r[0 * 4 + j] + l[1] * r[1 * 4 + j] + l[2] * r[2 * 4 + j] + l[3] * r[3 * 4 + j];
			m++;
		}
		l += 4;
	}
	return M;
} // cMat4::Mul

// cMat4::operator * : const cMat4 (const cMat4 &) const
inline const cMat4 cMat4::operator * (const cMat4 &R) const {
	return Mul(*this, R);
}

// cMat4::Mul : const cMat4 (const cMat4 &, const float)
inline const cMat4 cMat4::Mul(const cMat4 &L, const float s) {
	cMat4 M;
	float *m = (float *)&M;
	const float *l = (const float *)&L;

	for(int i = 0; i < 16; i++) {
		*m++ = *l++ * s;
	}
	return M;
}

// cMat4::operator * : const cMat4 (const float) const
inline const cMat4 cMat4::operator * (const float s) const {
	return Mul(*this, s);
}

// operator * : const cMat4 (const float, const cMat4 &)
inline const cMat4 operator * (const float s, const cMat4 &R) {
	return cMat4::Mul(R, s);
}

// cMat4::operator / : const cMat4 (const float) const
inline const cMat4 cMat4::operator / (const float s) const {
	float is = 1.0f / s;
	return Mul(*this, is);
}

// cMat4::Trace
inline float cMat4::Trace() const {
	return m_Rows[0][0] + m_Rows[1][1] + m_Rows[2][2] + m_Rows[3][3];
}

// cMat4::operator == : bool(const cMat4 &) const
inline bool cMat4::operator == (const cMat4 &u) const {
	return cMat4::Equals( *this, u );
}

// cMat4::Equals
inline bool cMat4::Equals(const cMat4 &P, const cMat4 &Q, const float Eps) {
	if(cVec4::Equals(P[0], Q[0], Eps) && cVec4::Equals(P[1], Q[1], Eps) && cVec4::Equals(P[2], Q[2], Eps) && cVec4::Equals(P[3], Q[3], Eps)) {
		return true;
	}
	return false;
}

// cMat4::IsZero
inline bool cMat4::IsZero(float Eps) const {
	return Equals(*this, Zero, Eps);
}

// cMat4::IsIdentity
inline bool cMat4::IsIdentity(float Eps) const {
	return Equals(*this, Identity, Eps);
}

// cMat4::IsSymmetric
inline bool cMat4::IsSymmetric( float Eps ) const {
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

// cMat4::IsOrthonormal
inline bool cMat4::IsOrthonormal( float Eps ) const {
    return cMath::IsOne( Determinant(), Eps );
}

// cMat4::ToFloatPtr : const float * () const
inline const float * cMat4::ToFloatPtr() const {
	return m_Rows[0].ToFloatPtr();
}

// cMat4::ToFloatPtr : float * ()
inline float * cMat4::ToFloatPtr() {
	return m_Rows[0].ToFloatPtr();
}

// cMat4::GetTranslation
inline const cVec3 cMat4::GetTranslation() const {
	return m_Rows[3].ToVec3();
}

// cMat4::SetTranslation
inline void cMat4::SetTranslation( const cVec3& c ) {
    m_Rows[ 3 ].x = c.x;
    m_Rows[ 3 ].y = c.y;
    m_Rows[ 3 ].z = c.z;
}

// cMat4::GetScaling
inline const cVec3 cMat4::GetScaling() const {
	return cVec3(m_Rows[0].ToVec3().Length(), m_Rows[1].ToVec3().Length(), m_Rows[2].ToVec3().Length());
}

// cMat4::SetScaling
inline void cMat4::SetScaling( const cVec3& s ) {
    m_Rows[ 0 ].x = s.x;
    m_Rows[ 1 ].y = s.y;
    m_Rows[ 2 ].z = s.z;
}

// cMat4::Transpose : const cMat4 (const cMat4 &)
inline const cMat4 cMat4::Transpose(const cMat4 &M) {
	cMat4 T;
	for(int i = 0; i < 4; i++) {
		T.SetRow(i, M.GetCol(i));
	}
	return T;
}

// cMat4::Transpose : void ()
inline void cMat4::Transpose() {
	cMath::Swap(m_Rows[0][1], m_Rows[1][0]);
	cMath::Swap(m_Rows[0][2], m_Rows[2][0]);
	cMath::Swap(m_Rows[1][2], m_Rows[2][1]);
	cMath::Swap(m_Rows[0][3], m_Rows[3][0]);
	cMath::Swap(m_Rows[1][3], m_Rows[3][1]);
	cMath::Swap(m_Rows[2][3], m_Rows[3][2]);
}

//*****************************************************************************
// cVec2 & cMat4
//*****************************************************************************

// cVec2::Transform : const cVec4 (const cVec2 &, const cMat4 &)
inline const cVec4 cVec2::Transform(const cVec2 &u, const cMat4 &T) {
	cVec4 r;
	r.x = u.x * T(0, 0) + u.y * T(1, 0) + T(3, 0);
	r.y = u.x * T(0, 1) + u.y * T(1, 1) + T(3, 1);
	r.z = u.x * T(0, 2) + u.y * T(1, 2) + T(3, 2);
	r.w = u.x * T(0, 3) + u.y * T(1, 3) + T(3, 3);
	return r;
}

// cVec2::TransformCoordinate : const cVec2 (const cVec2 &, const cMat4 &)
inline const cVec2 cVec2::TransformCoordinate(const cVec2 &u, const cMat4 &T) {
	cVec2 r;
	r.x = u.x * T(0, 0) + u.y * T(1, 0) + T(3, 0);
	r.y = u.x * T(0, 1) + u.y * T(1, 1) + T(3, 1);
	float w = u.x * T(0, 3) + u.y * T(1, 3) + T(3, 3);
	if(w != 1.0f) {
		float iw = 1.0f / w;
		r.x *= iw;
		r.y *= iw;
	}
	return r;
}

// cVec2::TransformCoordinate : void (const cMat4 &)
inline void cVec2::TransformCoordinate(const cMat4 &T) {
	*this = TransformCoordinate(*this, T);
}

// cVec2::TransformNormal : const cVec2 (const cVec2 &, const cMat4 &)
inline const cVec2 cVec2::TransformNormal(const cVec2 &u, const cMat4 &T) {
	cVec2 r;
	r.x = u.x * T(0, 0) + u.y * T(1, 0);
	r.y = u.x * T(0, 1) + u.y * T(1, 1);
	return r;
}

// cVec2::TransformNormal : void (const cMat4 &)
inline void cVec2::TransformNormal(const cMat4 &T) {
	*this = TransformNormal(*this, T);
}

//*****************************************************************************
// cVec3 & cMat4
//*****************************************************************************

// cVec3::Transform
inline const cVec4 cVec3::Transform(const cVec3 &u, const cMat4 &M) {
	cVec4 t;
	t.x = u.x * M[0][0] + u.y * M[1][0] + u.z * M[2][0] + M[3][0];
	t.y = u.x * M[0][1] + u.y * M[1][1] + u.z * M[2][1] + M[3][1];
	t.z = u.x * M[0][2] + u.y * M[1][2] + u.z * M[2][2] + M[3][2];
	t.w = u.x * M[0][3] + u.y * M[1][3] + u.z * M[2][3] + M[3][3];
	return t;
}

// cVec3::TransformCoordinate : const cVec3 (const cVec3 &, const cMat4 &)
inline const cVec3 cVec3::TransformCoordinate(const cVec3 &u, const cMat4 &T) {
	cVec3 r;
	r.x = u.x * T(0, 0) + u.y * T(1, 0) + u.z * T(2, 0) + T(3, 0);
	r.y = u.x * T(0, 1) + u.y * T(1, 1) + u.z * T(2, 1) + T(3, 1);
	r.z = u.x * T(0, 2) + u.y * T(1, 2) + u.z * T(2, 2) + T(3, 2);
	float w = u.x * T(0, 3) + u.y * T(1, 3) + u.z * T(2, 3) + T(3, 3);
	if(w != 1.0f) {
		float iw = 1.0f / w;
		r.x *= iw;
		r.y *= iw;
		r.z *= iw;
	}
	return r;
}

// cVec3::TransformCoordinate : void (const cMat4 &)
inline void cVec3::TransformCoordinate(const cMat4 &T) {
	*this = TransformCoordinate(*this, T);
}

// cVec3::TransformNormal
inline const cVec3 cVec3::TransformNormal(const cVec3 &u, const cMat4 &T) {
	cVec3 r;
	r.x = u.x * T(0, 0) + u.y * T(1, 0) + u.z * T(2, 0);
	r.y = u.x * T(0, 1) + u.y * T(1, 1) + u.z * T(2, 1);
	r.z = u.x * T(0, 2) + u.y * T(1, 2) + u.z * T(2, 2);
	return r;
}

// cVec3::TransformNormal
inline void cVec3::TransformNormal(const cMat4 &T) {
	*this = TransformNormal(*this, T);
}

// cVec3::TransformNormalTransposed
inline void cVec3::TransformNormalTransposed(const cMat4 &T) {
	cVec3 u = *this;
	x = u.x * T(0, 0) + u.y * T(0, 1) + u.z * T(0, 2);
	y = u.x * T(1, 0) + u.y * T(1, 1) + u.z * T(1, 2);
	z = u.x * T(2, 0) + u.y * T(2, 1) + u.z * T(2, 2);
}

//*****************************************************************************
// cVec4 & cMat4
//*****************************************************************************

// cVec4::Transform : const cVec4 (const cVec4 &, const cMat4 &)
inline const cVec4 cVec4::Transform(const cVec4 &u, const cMat4 &T) {
	cVec4 r;
	r.x = u.x * T(0, 0) + u.y * T(1, 0) + u.z * T(2, 0) + u.w * T(3, 0);
	r.y = u.x * T(0, 1) + u.y * T(1, 1) + u.z * T(2, 1) + u.w * T(3, 1);
	r.z = u.x * T(0, 2) + u.y * T(1, 2) + u.z * T(2, 2) + u.w * T(3, 2);
	r.w = u.x * T(0, 3) + u.y * T(1, 3) + u.z * T(2, 3) + u.w * T(3, 3);
	return r;
}

// cVec4::Transform : void (const cMat4 &)
inline void cVec4::Transform(const cMat4 &T) {
	*this = Transform(*this, T);
}

// cVec4::operator *= : void (const cMat4 &)
inline void cVec4::operator *= (const cMat4 &T) {
	*this = Transform(*this, T);
}

// cVec4::operator * : const cVec4 (const cMat4 &) const
inline const cVec4 cVec4::operator * (const cMat4 &T) const {
	return Transform(*this, T);
}

//*****************************************************************************
// cMat3 & cMat4
//*****************************************************************************

// cMat3::ToMat4
inline const cMat4 cMat3::ToMat4() const {
	return cMat4(*this, cVec3::Zero);
}

// cMat4::ToMat3
inline const cMat3 cMat4::ToMat3() const {
	return cMat3(cMat3::RowsCtor, m_Rows[0].ToVec3(), m_Rows[1].ToVec3(), m_Rows[2].ToVec3());
}




::std::ostream& operator<<( ::std::ostream&,  const cMat4& );
