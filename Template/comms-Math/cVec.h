#pragma once
	
template<class Type, int Dim>
struct cVec {
	typedef Type  value_type;

	Type v[Dim];

	// # After this constructor: IsUndefined() == true.
	cVec();
	cVec(const cVec<Type, Dim> &Src);
	explicit cVec(const Type S);
	explicit cVec(const Type* S);
	cVec(const Type X, const Type Y);
	cVec(const Type X, const Type Y, const Type Z);
	cVec(const Type X, const Type Y, const Type Z, const Type W);
	cVec(const cVec<Type, 2> &XY, const Type Z);
	cVec(const cVec<Type, 2> &XY, const Type Z, const Type W);
	cVec(const cVec<Type, 3> &XYZ, const Type W);

	// Create putting aside the line 'ab' where 't' is
	// [ 0.0 (=='a');  1.0 (=='b') ].
	// 't' = 0.5? half line 'ab'
	cVec(const cVec<Type, Dim>& a, const cVec<Type, Dim>& b, float t);

	cVec<Type, Dim> & operator = (const cVec<Type, Dim> &Src);
	cVec<Type, Dim> & Copy(const Type *pSrc);
	cVec<Type, Dim> & Set(const Type S);
	cVec<Type, 2> & Set(const Type X, const Type Y);
	cVec<Type, 3> & Set(const Type X, const Type Y, const Type Z);
	cVec<Type, 4> & Set(const Type X, const Type Y, const Type Z, const Type W);
	cVec<Type, 3> & Set(const cVec<Type, 2> &XY, const Type Z);
	cVec<Type, 4> & Set(const cVec<Type, 2> &XY, const Type Z, const Type W);
	cVec<Type, 4> & Set(const cVec<Type, 3> &XYZ, const Type W);

	Type & operator [] (const int index);
	const Type & operator [] (const int index) const;

	cVec<Type, Dim> operator - () const;

	cVec<Type, Dim> & operator += (const cVec<Type, Dim> &);
	cVec<Type, Dim> & operator -= (const cVec<Type, Dim> &);
	cVec<Type, Dim> & operator *= (const cVec<Type, Dim> &);
	// @todo error Potential error when types are mismatch.
	cVec<Type, Dim> & operator *= (const Type);
	cVec<Type, Dim> & operator /= (const cVec<Type, Dim> &);
	// @todo error Potential error when types are mismatch.
	cVec<Type, Dim> & operator /= (const Type);
	
	cVec<Type, Dim> operator + (const cVec<Type, Dim> &) const;
	cVec<Type, Dim> operator - (const cVec<Type, Dim> &) const;
	cVec<Type, Dim> operator * (const cVec<Type, Dim> &) const;
	// @todo error Potential error when types are mismatch.
	cVec<Type, Dim> operator * (const Type) const;
	//friend cVec<Type, Dim> operator * (const Type, const cVec<Type, Dim> &);
	cVec<Type, Dim> operator / (const cVec<Type, Dim> &) const;
	// @todo error Potential error when types are mismatch.
	cVec<Type, Dim> operator / (const Type) const;

	bool operator == (const cVec<Type, Dim> &) const;
	bool operator != (const cVec<Type, Dim> &) const;
	static bool Equals(const cVec<Type, Dim> &, const cVec<Type, Dim> &, const Type = (Type)cMath::Epsilon);
	
	void TransformCoordinate(const cMat4&);

	Type Length() const;
	Type LengthSq() const;
	Type Normalize();
	bool IsNormalized(const Type = (Type)cMath::Epsilon) const;
	bool IsZero(const Type = (Type)cMath::Epsilon) const;
	bool IsUndefined() const;
	
	// @todo fine  Release without 'static'.
	static cVec<Type, Dim> Abs(const cVec<Type, Dim> &);
	static Type Angle(const cVec<Type, Dim> &, const cVec<Type, Dim> &);
    static cVec<Type, Dim> Round( const cVec<Type, Dim> & );
    static cVec<Type, Dim> Clamp( const cVec<Type, Dim> &, const Type, const Type );
	static cVec<Type, Dim> Clamp(const cVec<Type, Dim> &, const cVec<Type, Dim> &, const cVec<Type, Dim> &);
	static cVec<Type, 3> Cross(const cVec<Type, 3> &, const cVec<Type, 3> &);
	static Type Distance(const cVec<Type, Dim> &, const cVec<Type, Dim> &);
	static Type DistanceSq(const cVec<Type, Dim> &, const cVec<Type, Dim> &);

	template< typename RT >
	static RT Distance(const cVec<Type, Dim> &, const cVec<Type, Dim> &);

	template< typename RT >
	static RT DistanceSq(const cVec<Type, Dim> &, const cVec<Type, Dim> &);

	static Type Dot(const cVec<Type, Dim> &, const cVec<Type, Dim> &);
	static Type Length(const cVec<Type, Dim> &);
	static Type LengthSq(const cVec<Type, Dim> &);
	static cVec<Type, Dim> Lerp(const cVec<Type, Dim> &, const cVec<Type, Dim> &, Type);
	static cVec<Type, Dim> Lerp(const cVec<Type, Dim> &, const cVec<Type, Dim> &, const cVec<Type, Dim> &);
	static cVec<Type, Dim> Lerp05(const cVec<Type, Dim> &, const cVec<Type, Dim> &);
    static cVec<Type, Dim> Slerp( const cVec<Type, Dim> &, const cVec<Type, Dim> &, Type );
    static cVec<Type, Dim> Max( const cVec<Type, Dim> &, const cVec<Type, Dim> & );
    static cVec<Type, Dim> Min( const cVec<Type, Dim> &, const cVec<Type, Dim> & );
	static cVec<Type, Dim> Normalize(const cVec<Type, Dim> &);
	static cVec<Type, Dim> Reflect(const cVec<Type, Dim> &RayDir, const cVec<Type, Dim> &Normal);
	static cVec<Type, Dim> Refract(const cVec<Type, Dim> &RayDir, const cVec<Type, Dim> &Normal, Type Eta);
	static cVec<Type, Dim> Truncate(const cVec<Type, Dim> &, Type);
	Type DistanceToLineSegSq(const cVec<Type, Dim> &A, const cVec<Type, Dim> &B, Type *pScale = NULL) const;

	Type * ToPtr();
	const Type * ToPtr() const;

	int GetDimension() const;

	cVec<Type, 2> & To2();
	const cVec<Type, 2> & To2() const;
	cVec<Type, 3> & To3();
	const cVec<Type, 3> & To3() const;
	
	const cStr ToStringF(const int Prec = 2) const;
	const cStr ToStringI() const;

	// @todo fine  Add explicit-keyword when VS upgraded.
	template<typename RT>
	operator cVec< RT, Dim > () const;

	operator cVec2 () const;
	operator cVec3 () const;

	// For work as key in the 'uni_hash'.
	// @see *_DWORD
	operator dword () const;

	static const cVec< Type, Dim >&  ONE();
	static const cVec< Type, Dim >&  ZERO();
	static const cVec< Type, Dim >&  UNDEFINED();
};

typedef cVec<int, 1> cVec1i;
typedef cVec<int, 2> cVec2i;
typedef cVec<int, 3> cVec3i;
typedef cVec<int, 4> cVec4i;
typedef cVec<char, 2> cVec2c;
typedef cVec<char, 3> cVec3c;

static const int Xelt = 0;
static const int Yelt = 1;
static const int Zelt = 2;
static const int Welt = 3;

// cVec<Type, Dim>.ctor : ()
template<class Type, int Dim>
inline cVec<Type, Dim>::cVec() {
	static const Type&  U = UNDEFINED()[ 0 ];
	for(int i = 0; i < Dim; i++) {
		v[i] = U;
	}
}

// cVec<Type, Dim>.ctor : (const cVec<Type, Dim> &Src)
template<class Type, int Dim>
inline cVec<Type, Dim>::cVec(const cVec<Type, Dim> &Src) {
	for(int i = 0; i < Dim; i++) {
		v[i] = Src[i];
	}
}

// cVec<Type, Dim>.ctor : (const Type S)
template<class Type, int Dim>
inline cVec<Type, Dim>::cVec(const Type S) {
	for(int i = 0; i < Dim; i++) {
		v[i] = S;
	}
}


// cVec<Type, Dim>.ctor : (const Type* S)
template<class Type, int Dim>
inline cVec<Type, Dim>::cVec(const Type* S) {
	::std::copy( S, S + Dim, v );
}

// cVec<Type, 2>.ctor : (const Type X, const Type Y)
template<class Type, int Dim>
inline cVec<Type, Dim>::cVec(const Type X, const Type Y) {
	cAssert(Dim == 2);
	v[0] = X;
	v[1] = Y;
}

// cVec<Type, 3>.ctor : (const Type X, const Type Y, const Type Z)
template<class Type, int Dim>
inline cVec<Type, Dim>::cVec(const Type X, const Type Y, const Type Z) {
	cAssert(Dim == 3);
	v[0] = X;
	v[1] = Y;
	v[2] = Z;
}

// cVec<Type, 4>.ctor : (const Type X, const Type Y, const Type Z, const Type W)
template<class Type, int Dim>
inline cVec<Type, Dim>::cVec(const Type X, const Type Y, const Type Z, const Type W) {
	cAssert(Dim == 4);
	v[0] = X;
	v[1] = Y;
	v[2] = Z;
	v[3] = W;
}

// cVec<Type, 3>.ctor : (const cVec<Type, 2> &XY, const Type Z)
template<class Type, int Dim>
inline cVec<Type, Dim>::cVec(const cVec<Type, 2> &XY, const Type Z) {
	cAssert(Dim == 3);
	v[0] = XY[0];
	v[1] = XY[1];
	v[2] = Z;
}

// cVec<Type, 4>.ctor : (const cVec<Type, 2> &XY, const Type Z, const Type W)
template<class Type, int Dim>
inline cVec<Type, Dim>::cVec(const cVec<Type, 2> &XY, const Type Z, const Type W) {
	cAssert(Dim == 4);
	v[0] = XY[0];
	v[1] = XY[1];
	v[2] = Z;
	v[3] = W;
}

// cVec<Type, 4>.ctor : (const cVec<Type, 3> &XYZ, const Type W)
template<class Type, int Dim>
inline cVec<Type, Dim>::cVec(const cVec<Type, 3> &XYZ, const Type W) {
	cAssert(Dim == 4);
	v[0] = XYZ[0];
	v[1] = XYZ[1];
	v[2] = XYZ[2];
	v[3] = W;
}

// cVec<Type, Dim>.ctor : (const cVec<Type, Dim>& a, const cVec<Type, Dim>& b, float t);
template<class Type, int Dim>
inline cVec<Type, Dim>::cVec(const cVec<Type, Dim>& a, const cVec<Type, Dim>& b, float t) {
	cAssert((Dim == 2) || (Dim == 3));
	cAssertM((t >= 0.0f) && (t <= 1.0f), "'t' is out of range [ 0.0; 1.0 ]." );
	// # Save digits by truncate.
	const cVec<float, Dim>  r = b - a;
	const cVec<float, Dim>  sr = r * t + a;
	for(int i = 0; i < Dim; i++) {
		v[i] = static_cast<Type>( sr[i] );
	}
}

// cVec<Type, Dim>::operator = : cVec<Type, Dim> & (const cVec<Type, Dim> &Src)
template<class Type, int Dim>
inline cVec<Type, Dim> & cVec<Type, Dim>::operator = (const cVec<Type, Dim> &Src) {
	for(int i = 0; i < Dim; i++) {
		v[i] = Src[i];
	}
	return *this;
}

// cVec<Type, Dim>::Set : cVec<Type, Dim> & (const Type S)
template<class Type, int Dim>
inline cVec<Type, Dim> & cVec<Type, Dim>::Set(const Type S) {
	for(int i = 0; i < Dim; i++) {
		v[i] = S;
	}
	return *this;
}

// cVec<Type, 2>::Set : cVec<Type, 2> & (const Type X, const Type Y)
template<class Type, int Dim>
inline cVec<Type, 2> & cVec<Type, Dim>::Set(const Type X, const Type Y) {
	cAssert(Dim == 2);
	v[0] = X;
	v[1] = Y;
	return *this;
}

// cVec<Type, 3>::Set : cVec<Type, 3> & (const Type X, const Type Y, const Type Z)
template<class Type, int Dim>
inline cVec<Type, 3> & cVec<Type, Dim>::Set(const Type X, const Type Y, const Type Z) {
	cAssert(Dim == 3);
	v[0] = X;
	v[1] = Y;
	v[2] = Z;
	return *this;
}

// cVec<Type, 4>::Set : cVec<Type, 4> & (const Type X, const Type Y, const Type Z, const Type W)
template<class Type, int Dim>
inline cVec<Type, 4> & cVec<Type, Dim>::Set(const Type X, const Type Y, const Type Z, const Type W) {
	cAssert(Dim == 4);
	v[0] = X;
	v[1] = Y;
	v[2] = Z;
	v[3] = W;
	return *this;
}

// cVec<Type, 3>::Set : cVec<Type, 3> & (const cVec<Type, 2> &XY, const Type Z)
template<class Type, int Dim>
inline cVec<Type, 3> & cVec<Type, Dim>::Set(const cVec<Type, 2> &XY, const Type Z) {
	cAssert(Dim == 3);
	v[0] = XY[0];
	v[1] = XY[1];
	v[2] = Z;
	return *this;
}

// cVec<Type, 4>::Set : cVec<Type, 4> & (const cVec<Type, 2> &XY, const Type Z, const Type W)
template<class Type, int Dim>
inline cVec<Type, 4> & cVec<Type, Dim>::Set(const cVec<Type, 2> &XY, const Type Z, const Type W) {
	cAssert(Dim == 4);
	v[0] = XY[0];
	v[1] = XY[1];
	v[2] = Z;
	v[3] = W;
	return *this;
}

// cVec<Type, 4>::Set : cVec<Type, 4> & (const cVec<Type, 3> &XYZ, const Type W)
template<class Type, int Dim>
inline cVec<Type, 4> & cVec<Type, Dim>::Set(const cVec<Type, 3> &XYZ, const Type W) {
	cAssert(Dim == 4);
	v[0] = XYZ[0];
	v[1] = XYZ[1];
	v[2] = XYZ[2];
	v[3] = W;
	return *this;
}

// cVec<Type, Dim>::Copy : cVec<Type, Dim> & (const Type *pSrc)
template<class Type, int Dim>
inline cVec<Type, Dim> & cVec<Type, Dim>::Copy(const Type *pSrc) {
	cAssert(pSrc);
	for(int i = 0; i < Dim; i++) {
		v[i] = pSrc[i];
	}
	return *this;
}

// cVec<Type, Dim>::operator [] : Type & (const int index)
template<class Type, int Dim>
inline Type & cVec<Type, Dim>::operator [] (const int index) {
	cAssert(index >= 0 && index < Dim);
	return v[index];
}

// cVec<Type, Dim>::operator [] : const Type & (const int index) const
template<class Type, int Dim>
inline const Type & cVec<Type, Dim>::operator [] (const int index) const {
	cAssert(index >= 0 && index < Dim);
	return v[index];
}

// operator - : cVec<Type, Dim>(const cVec<Type, Dim> &)
template<class Type, int Dim>
inline cVec<Type, Dim> cVec<Type, Dim>::operator - () const {
	cVec<Type, Dim> r;
	for(int i = 0; i < Dim; i++) {
		r[i] = - v[i];
	}
	return r;
}

// cVec<Type, Dim>::operator += : cVec<Type, Dim> & (const cVec<Type, Dim> &)
template<class Type, int Dim>
inline cVec<Type, Dim> & cVec<Type, Dim>::operator += (const cVec<Type, Dim> &u) {
	for(int i = 0; i < Dim; i++) {
		v[i] += u[i];
	}
	return *this;
}

// cVec<Type, Dim>::operator -= : cVec<Type, Dim> & (const cVec<Type, Dim> &)
template<class Type, int Dim>
inline cVec<Type, Dim> & cVec<Type, Dim>::operator -= (const cVec<Type, Dim> &u) {
	for(int i = 0; i < Dim; i++) {
		v[i] -= u[i];
	}
	return *this;
}

// cVec<Type, Dim>::operator *= : cVec<Type, Dim> & (const cVec<Type, Dim> &)
template<class Type, int Dim>
inline cVec<Type, Dim> & cVec<Type, Dim>::operator *= (const cVec<Type, Dim> &u) {
	for(int i = 0; i < Dim; i++) {
		v[i] *= u[i];
	}
	return *this;
}

// cVec<Type, Dim>::operator *= : cVec<Type, Dim> & (const Type)
template<class Type, int Dim>
inline cVec<Type, Dim> & cVec<Type, Dim>::operator *= (const Type s) {
	for(int i = 0; i < Dim; i++) {
		v[i] *= s;
	}
	return *this;
}

// cVec<Type, Dim>::operator /= : cVec<Type, Dim> & (const cVec<Type, Dim> &)
template<class Type, int Dim>
inline cVec<Type, Dim> & cVec<Type, Dim>::operator /= (const cVec<Type, Dim> &u) {
	for(int i = 0; i < Dim; i++) {
		v[i] /= u[i];
	}
	return *this;
}

// cVec<Type, Dim>::operator /= : cVec<Type, Dim> & (const Type)
template<class Type, int Dim>
inline cVec<Type, Dim> & cVec<Type, Dim>::operator /= (const Type s) {
	for(int i = 0; i < Dim; i++) {
		v[i] /= s;
	}
	return *this;
}

// cVec<Type, Dim>::operator + : cVec<Type, Dim>(const cVec<Type, Dim> &) const
template<class Type, int Dim>
inline cVec<Type, Dim> cVec<Type, Dim>::operator + (const cVec<Type, Dim> &u) const {
	cVec<Type, Dim> r(*this);
	return r += u;
}

// cVec<Type, Dim>::operator - : cVec<Type, Dim>(const cVec<Type, Dim> &) const
template<class Type, int Dim>
inline cVec<Type, Dim> cVec<Type, Dim>::operator - (const cVec<Type, Dim> &u) const {
	cVec<Type, Dim> r(*this);
	return r -= u;
}

// cVec<Type, Dim>::operator * : cVec<Type, Dim>(const cVec<Type, Dim> &) const
template<class Type, int Dim>
inline cVec<Type, Dim> cVec<Type, Dim>::operator * (const cVec<Type, Dim> &u) const {
	cVec<Type, Dim> r(*this);
	return r *= u;
}

// cVec<Type, Dim>::operator * : cVec<Type, Dim>(const Type) const
template<class Type, int Dim>
inline cVec<Type, Dim> cVec<Type, Dim>::operator * (const Type s) const {
	cVec<Type, Dim> r(*this);
	return r *= s;
}

// operator * : cVec<Type, Dim>(const Type, const cVec<Type, Dim> &)
template<class Type, int Dim>
inline cVec<Type, Dim> operator * (const Type s, const cVec<Type, Dim> &u) {
	cVec<Type, Dim> r(u);
	return r *= s;
}

// cVec<Type, Dim>::operator / : cVec<Type, Dim>(const cVec<Type, Dim> &) const
template<class Type, int Dim>
inline cVec<Type, Dim> cVec<Type, Dim>::operator / (const cVec<Type, Dim> &u) const {
	cVec<Type, Dim> r(*this);
	return r /= u;
}

// cVec<Type, Dim>::operator / : cVec<Type, Dim>(const Type) const
template<class Type, int Dim>
inline cVec<Type, Dim> cVec<Type, Dim>::operator / (const Type s) const {
	cVec<Type, Dim> r(*this);
	return r /= s;
}

// cVec<Type, Dim>::operator == : bool(const cVec<Type, Dim> &) const
template<class Type, int Dim>
inline bool cVec<Type, Dim>::operator == (const cVec<Type, Dim> &u) const {
	return Equals( *this, u );
}

// cVec<Type, Dim>::operator != : bool(const cVec<Type, Dim> &) const
template<class Type, int Dim>
inline bool cVec<Type, Dim>::operator != (const cVec<Type, Dim> &u) const {
	return !Equals( *this, u );
}

// cVec<Type, Dim>::Equals : bool(const cVec<Type, Dim> &, const cVec<Type, Dim> &v, const Type)
template<class Type, int Dim>
inline bool cVec<Type, Dim>::Equals(const cVec<Type, Dim> &u, const cVec<Type, Dim> &v, const Type Eps) {
	cAssert(Eps >= (Type)0);
	for(int i = 0; i < Dim; i++) {
		if(cMath::Abs(u[i] - v[i]) > Eps) return false;
	}
	return true;
}

// cVec<Type, Dim>::TransformCoordinate()
template<class Type, int Dim>
inline void cVec<Type, Dim>::TransformCoordinate(const cMat4& m) {
	cVec3  r(
		v[0] * m(0, 0) + v[1] * m(1, 0) + v[2] * m(2, 0) + m(3, 0),
		v[0] * m(0, 1) + v[1] * m(1, 1) + v[2] * m(2, 1) + m(3, 1),
		v[0] * m(0, 2) + v[1] * m(1, 2) + v[2] * m(2, 2) + m(3, 2)
	);
	const float  w =
		v[0] * m(0, 3) + v[1] * m(1, 3) + v[2] * m(2, 3) + m(3, 3);
	if (w != 1.0f) {
		const float  iw = 1.0f / w;
		r.x *= iw;
		r.y *= iw;
		r.z *= iw;
	}
	v[0] = r.x;
	v[1] = r.y;
	v[2] = r.z;
}

// cVec<Type, Dim>::LengthSq : Type() const
template<class Type, int Dim>
inline Type cVec<Type, Dim>::LengthSq() const {
	Type l2(0);
	for(int i = 0; i < Dim; i++) {
		l2 += (v[i] * v[i]);
	}
	return l2;
}

// cVec<Type, Dim>::Length : Type() const
template<class Type, int Dim>
inline Type cVec<Type, Dim>::Length() const {
	return cMath::Sqrt(LengthSq());
}

// cVec<Type, Dim>::Normalize : Type()
template<class Type, int Dim>
inline Type cVec<Type, Dim>::Normalize() {
	Type l = Length();
	if(l > 0) {
		Type il = (Type)1.0 / l;
		for(int i = 0; i < Dim; i++) {
			v[i] *= il;
		}
	}
	return l;
}

// cVec<Type, Dim>::IsNormalized : bool(const Type) const
template<class Type, int Dim>
inline bool cVec<Type, Dim>::IsNormalized(const Type Eps) const {
	return cMath::IsOne(LengthSq(), Eps);
}

// cVec<Type, Dim>::IsZero : bool(const Type) const
template<class Type, int Dim>
inline bool cVec<Type, Dim>::IsZero(const Type Eps) const {
	for(int i = 0; i < Dim; i++) {
		if(!cMath::IsZero(v[i], Eps)) return false;
	}
	return true;
}

// cVec<Type, Dim>::Abs : cVec<Type, Dim>(const cVec<Type, Dim> &)
template<class Type, int Dim>
inline cVec<Type, Dim> cVec<Type, Dim>::Abs(const cVec<Type, Dim> &u) {
	cVec<Type, Dim> r;
	for(int i = 0; i < Dim; i++) {
		r[i] = cMath::Abs(u[i]);
	}
	return r;
}

// cVec<Type, Dim>::Angle : Type(const cVec<Type, Dim> &, const cVec<Type, Dim> &)
template<class Type, int Dim>
inline Type cVec<Type, Dim>::Angle(const cVec<Type, Dim> &u, const cVec<Type, Dim> &v) {
	Type d = cVec<Type, Dim>::Dot(u, v);
	Type ll = u.Length() * v.Length();
	return cMath::ACos(d / ll);
}

// cVec<Type, Dim>::Clamp : cVec<Type, Dim>(const cVec<Type, Dim> &, const Type, const Type)
template<class Type, int Dim>
inline cVec<Type, Dim> cVec<Type, Dim>::Round( const cVec<Type, Dim> &u ) {
    cVec<Type, Dim> r;
    for ( int i = 0; i < Dim; i++ ) {
        r[ i ] = cMath::Round( u[ i ] );
    }
    return r;
}

// cVec<Type, Dim>::Clamp : cVec<Type, Dim>(const cVec<Type, Dim> &, const Type, const Type)
template<class Type, int Dim>
inline cVec<Type, Dim> cVec<Type, Dim>::Clamp(const cVec<Type, Dim> &u, const Type Lo, const Type Hi) {
	cVec<Type, Dim> r;
	for(int i = 0; i < Dim; i++) {
		r[i] = u[i] < Lo ? Lo : (u[i] > Hi ? Hi : u[i]);
	}
	return r;
}

// cVec<Type, Dim>::Clamp : cVec<Type, Dim>(const cVec<Type, Dim> &, const cVec<Type, Dim> &, const cVec<Type, Dim> &)
template<class Type, int Dim>
inline cVec<Type, Dim> cVec<Type, Dim>::Clamp(const cVec<Type, Dim> &u, const cVec<Type, Dim> &Lo, const cVec<Type, Dim> &Hi) {
	cVec<Type, Dim> r;
	for(int i = 0; i < Dim; i++) {
		r[i] = u[i] < Lo[i] ? Lo[i] : (u[i] > Hi[i] ? Hi[i] : u[i]);
	}
	return r;
}

// cVec<Type, 3>::Cross : cVec<Type, 3>(const cVec<Type, 3> &, const cVec<Type, 3> &)
template<class Type, int Dim>
inline cVec<Type, 3> cVec<Type, Dim>::Cross(const cVec<Type, 3> &u, const cVec<Type, 3> &v) {
	return cVec<Type, 3>(u[1] * v[2] - u[2] * v[1], u[2] * v[0] - u[0] * v[2], u[0] * v[1] - u[1] * v[0]);
}

// cVec<Type, Dim>::DistanceSq : Type(const cVec<Type, Dim> &, const cVec<Type, Dim> &)
template<class Type, int Dim>
inline Type cVec<Type, Dim>::DistanceSq(const cVec<Type, Dim> &p, const cVec<Type, Dim> &q) {
	return DistanceSq<Type>(p, q);
}

// cVec<Type, Dim>::Distance : Type(const cVec<Type, Dim> &, const cVec<Type, Dim> &)
template<class Type, int Dim>
inline Type cVec<Type, Dim>::Distance(const cVec<Type, Dim> &p, const cVec<Type, Dim> &q) {
	return Distance<Type>(p, q);
}

// cVec<Type, Dim>::DistanceSq : Type(const cVec<Type, Dim> &, const cVec<Type, Dim> &)
template<class Type, int Dim>
template<typename RT>
inline RT cVec<Type, Dim>::DistanceSq(const cVec<Type, Dim> &p, const cVec<Type, Dim> &q) {
	RT d2(0);
	for(int i = 0; i < Dim; i++) {
		const RT  delta = (RT)p[i] - (RT)q[i];
		d2 += (delta * delta);
	}
	return d2;
}

// cVec<Type, Dim>::Distance : Type(const cVec<Type, Dim> &, const cVec<Type, Dim> &)
template<class Type, int Dim>
template<typename RT>
inline RT cVec<Type, Dim>::Distance(const cVec<Type, Dim> &p, const cVec<Type, Dim> &q) {
	return cMath::Sqrt(DistanceSq<RT>(p, q));
}

// cVec<Type, Dim>::Dot : Type(const cVec<Type, Dim> &, const cVec<Type, Dim> &)
template<class Type, int Dim>
inline Type cVec<Type, Dim>::Dot(const cVec<Type, Dim> &u, const cVec<Type, Dim> &v) {
	Type d(0);
	for(int i = 0; i < Dim; i++) {
		d += u[i] * v[i];
	}
	return d;
}

// cVec<Type, Dim>::LengthSq : Type(const cVec<Type, Dim> &)
template<class Type, int Dim>
inline Type cVec<Type, Dim>::LengthSq(const cVec<Type, Dim> &u) {
	Type l2(0);
	for(int i = 0; i < Dim; i++) {
		l2 += u[i] * u[i];
	}
	return l2;
}

// cVec<Type, Dim>::Length : Type(const cVec<Type, Dim> &)
template<class Type, int Dim>
inline Type cVec<Type, Dim>::Length(const cVec<Type, Dim> &u) {
	return cMath::Sqrt(LengthSq(u));
}

// cVec<Type, Dim>::Lerp : cVec<Type, Dim>(const cVec<Type, Dim> &, const cVec<Type, Dim> &, const Type)
template<class Type, int Dim>
inline cVec<Type, Dim> cVec<Type, Dim>::Lerp(const cVec<Type, Dim> &u, const cVec<Type, Dim> &v, Type s) {
	cVec<Type, Dim> r;
	for(int i = 0; i < Dim; i++) {
		r[i] = u[i] + s * (v[i] - u[i]);
	}
	return r;
}

// cVec<Type, Dim>::Lerp : cVec<Type, Dim>(const cVec<Type, Dim> &, const cVec<Type, Dim> &, const cVec<Type, Dim> &)
template<class Type, int Dim>
inline cVec<Type, Dim> cVec<Type, Dim>::Lerp(const cVec<Type, Dim> &u, const cVec<Type, Dim> &v, const cVec<Type, Dim> &l) {
	cVec<Type, Dim> r;
	for(int i = 0; i < Dim; i++) {
		r[i] = u[i] + l[i] * (v[i] - u[i]);
	}
	return r;
}

// cVec<Type, Dim>::Lerp05 : cVec<Type, Dim>(const cVec<Type, Dim> &, const cVec<Type, Dim> &)
template<class Type, int Dim>
inline cVec<Type, Dim> cVec<Type, Dim>::Lerp05(const cVec<Type, Dim> &u, const cVec<Type, Dim> &v) {
	cVec<Type, Dim> r;
	for(int i = 0; i < Dim; i++) {
		r[i] = (Type)0.5 * (u[i] + v[i]);
	}
	return r;
}

// cVec<Type, Dim>::Slerp : cVec<Type, Dim>(const cVec<Type, Dim> &, const cVec<Type, Dim> &, Type)
template<class Type, int Dim>
inline cVec<Type, Dim> cVec<Type, Dim>::Slerp( const cVec<Type, Dim> &u, const cVec<Type, Dim> &v, Type s ) {
    if ( s <= 0.0f ) {
        return u;
    }
    else if ( s >= 1.0f ) {
        return v;
    }

    float Cos = Dot( u, v );
    float Scale0, Scale1;
    if ( 1.0f - Cos > cMath::Epsilon ) {
        float Angle = cMath::ACos( Cos );
        float Sin = cMath::Sin( Angle );
        Scale0 = cMath::Sin( (1.0f - s) * Angle ) / Sin;
        Scale1 = cMath::Sin( s * Angle ) / Sin;
    }
    else {
        Scale0 = 1.0f - s;
        Scale1 = s;
    }
    return u * Scale0 + v * Scale1;
}

// cVec<Type, Dim>::Max : cVec<Type, Dim>(const cVec<Type, Dim> &, const cVec<Type, Dim> &)
template<class Type, int Dim>
inline cVec<Type, Dim> cVec<Type, Dim>::Max(const cVec<Type, Dim> &u, const cVec<Type, Dim> &v) {
	cVec<Type, Dim> r;
	for(int i = 0; i < Dim; i++) {
		r[i] = u[i] > v[i] ? u[i] : v[i];
	}
	return r;
}

// cVec<Type, Dim>::Min : cVec<Type, Dim>(const cVec<Type, Dim> &, const cVec<Type, Dim> &)
template<class Type, int Dim>
inline cVec<Type, Dim> cVec<Type, Dim>::Min(const cVec<Type, Dim> &u, const cVec<Type, Dim> &v) {
	cVec<Type, Dim> r;
	for(int i = 0; i < Dim; i++) {
		r[i] = u[i] < v[i] ? u[i] : v[i];
	}
	return r;
}

// cVec<Type, Dim>::Normalize : cVec<Type, Dim>(const cVec<Type, Dim> &)
template<class Type, int Dim>
inline cVec<Type, Dim> cVec<Type, Dim>::Normalize(const cVec<Type, Dim> &u) {
	Type l = u.Length();
	if(l > 0) {
		Type il = (Type)1.0 / l;
		return u * il;
	}
	return u;
}

// cVec<Type, Dim>::Reflect : cVec<Type, Dim>(const cVec<Type, Dim> &, const cVec<Type, Dim> &)
template<class Type, int Dim>
inline cVec<Type, Dim> cVec<Type, Dim>::Reflect(const cVec<Type, Dim> &RayDir, const cVec<Type, Dim> &Normal) {
	return RayDir - (Type)2.0 * cVec<Type, Dim>::Dot(RayDir, Normal) * Normal;
}

// cVec<Type, Dim>::Refract : cVec<Type, Dim>(const cVec<Type, Dim> &, const cVec<Type, Dim> &, const Type)
template<class Type, int Dim>
inline cVec<Type, Dim> cVec<Type, Dim>::Refract(const cVec<Type, Dim> &RayDir, const cVec<Type, Dim> &Normal, Type Eta) {
	Type k = (Type)1.0 - Eta * Eta * ((Type)1.0 - cMath::Square(cVec<Type, Dim>::Dot(Normal, RayDir)));
	if(k < (Type)0.0) return ZERO();
	return Eta * RayDir - (Eta * cVec<Type, Dim>::Dot(Normal, RayDir) + cMath::Sqrt(k)) * Normal;
}

// cVec<Type, Dim>::Truncate : cVec<Type, Dim>(const cVec<Type, Dim> &, const Type)
template<class Type, int Dim>
inline cVec<Type, Dim> cVec<Type, Dim>::Truncate(const cVec<Type, Dim> &u, Type MaxLen) {
	if(MaxLen <= 0) {
        return ZERO();
	}
	Type l = u.Length();
	if(l > MaxLen) {
		Type il = MaxLen / l;
		return u * il;
	}
	return u;
}

//---------------------------------------------------------------------------------------------------------------------------------
// cVec<Type, Dim>::DistanceToLineSegSq
//---------------------------------------------------------------------------------------------------------------------------------
template<class Type, int Dim>
inline Type cVec<Type, Dim>::DistanceToLineSegSq(const cVec<Type, Dim> &A, const cVec<Type, Dim> &B, Type *pScale) const {
	const cVec<Type, Dim> Ap = *this - A;
	const cVec<Type, Dim> AB = B - A;
	const Type l2 = AB.LengthSq();
	Type Scale;
	if(l2 < (Type)cMath::Epsilon) {
		Scale = (Type)0.5;
	} else {
		Scale = cVec<Type, Dim>::Dot(Ap, AB) / l2;
	}
	if(pScale) {
		*pScale = Scale;
	}
	if(Scale <= (Type)0.0) {
		return cVec<Type, Dim>::DistanceSq(*this, A);
	}
	if(Scale >= (Type)1.0) {
		return cVec<Type, Dim>::DistanceSq(*this, B);
	}
	return cVec<Type, Dim>::DistanceSq(*this, A + AB * Scale);
}

// cVec<Type, Dim>::ToPtr : Type * ()
template<class Type, int Dim>
inline Type * cVec<Type, Dim>::ToPtr() {
	return v;
}

// cVec<Type, Dim>::ToPtr : const Type * () const
template<class Type, int Dim>
inline const Type * cVec<Type, Dim>::ToPtr() const {
	return v;
}

// cVec<Type, Dim>::GetDimension : int () const
template<class Type, int Dim>
inline int cVec<Type, Dim>::GetDimension() const {
	return Dim;
}

// cVec<Type, >= 3>::To2 : cVec<Type, 2> & ()
template<class Type, int Dim>
inline cVec<Type, 2> & cVec<Type, Dim>::To2() {
	cAssert(Dim >= 3);
	return *reinterpret_cast<cVec<Type, 2> *>(this);
}

// cVec<Type, >= 3>::To2 : const cVec<Type, 2> & () const
template<class Type, int Dim>
inline const cVec<Type, 2> & cVec<Type, Dim>::To2() const {
	cAssert(Dim >= 3);
	return *reinterpret_cast<const cVec<Type, 2> *>(this);
}

// cVec<Type, >= 4>::To3 : cVec<Type, 3> & ()
template<class Type, int Dim>
inline cVec<Type, 3> & cVec<Type, Dim>::To3() {
	cAssert(Dim >= 4);
	return *reinterpret_cast<cVec<Type, 3> *>(this);
}

// cVec<Type, >= 4>::To3 : const cVec<Type, 3> & () const
template<class Type, int Dim>
inline const cVec<Type, 3> & cVec<Type, Dim>::To3() const {
	cAssert(Dim >= 4);
	return *reinterpret_cast<const cVec<Type, 3> *>(this);
}

// cVec<Type, Dim>::ToStringF
template<class Type, int Dim>
inline const cStr cVec<Type, Dim>::ToStringF(const int Prec) const {
	return cStr::ToString(ToPtr(), Dim, Prec);
}

// cVec<Type, Dim>::ToStringI
template<class Type, int Dim>
inline const cStr cVec<Type, Dim>::ToStringI() const {
	return cStr::ToString(ToPtr(), Dim);
}

// operator cVec< RT, Dim > () const
template<class Type, int Dim>
template<typename RT>
cVec<Type, Dim>::operator cVec< RT, Dim > () const {
    cVec<RT, Dim>  r;
	for(int i = 0; i < Dim; i++) {
		r[i] = static_cast< RT >( (*this)[i] );
	}
	return r;
}

// operator cVec2 () const
template<class Type, int Dim>
cVec<Type, Dim>::operator cVec2 () const {
    cVec2  r;
	for(int i = 0; i < 2; i++) {
		r[i] = (Dim < 2) ? 0.0f : static_cast< float >( (*this)[i] );
	}
	return r;
}

// operator cVec3 () const
template<class Type, int Dim>
cVec<Type, Dim>::operator cVec3 () const {
    cVec3  r;
	for(int i = 0; i < 3; i++) {
		r[i] = (Dim < 3) ? 0.0f : static_cast< float >( (*this)[i] );
	}
	return r;
}

// operator dword () const
template<class Type, int Dim>
cVec<Type, Dim>::operator dword () const {
	static const double K[] = {
		22111,  7411, 599,
		93563, 25939, 461,
		26681, 10513, 347,
		16127,  3967, 227,
	};
	cAssert(((sizeof(K) / sizeof(K[0])) >= Dim) && "Add more values for 'K'.");
    double r = static_cast< double >( (*this)[0] ) * K[0];
	for(int i = 1; i < Dim; i++) {
		r += static_cast< double >( (*this)[i] ) * K[i];
	}
	return static_cast< dword >( r );
}

// static const ONE
template<class Type, int Dim>
const cVec<Type, Dim>& cVec<Type, Dim>::ONE() {
    static const cVec<Type, Dim>  r( Type( 1 ) );
	return r;
}

// static const ZERO
template<class Type, int Dim>
const cVec<Type, Dim>& cVec<Type, Dim>::ZERO() {
    static const cVec<Type, Dim>  r( Type( 0 ) );
	return r;
}

// static const UNDEFINED
template<class Type, int Dim>
const cVec<Type, Dim>& cVec<Type, Dim>::UNDEFINED() {
// @todo fine  Remove '#undef max'.
#undef max
	static const cVec<Type, Dim>  r( ::std::numeric_limits< Type >::max() );
	return r;
}




template< class Type, int Dim >
::std::ostream& operator<<( ::std::ostream& out,  const cVec< Type, Dim >& v ) {
	out << "[";
	for (int i = 0; i < Dim; ++i) {
		const bool needSeparator = ((i + 1) != Dim);
		out << v[ i ] << (needSeparator ? ", " : "");
	}
	out << "]";
	return out;
}
