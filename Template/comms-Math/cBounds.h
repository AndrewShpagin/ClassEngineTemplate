#pragma once

//-----------------------------------------------------------------------------
// cBounds
//-----------------------------------------------------------------------------
class cBounds {
public:
	cBounds();
	explicit cBounds(const cVec3 &p);
	cBounds(const cVec3 &bMin, const cVec3 &bMax);
    virtual ~cBounds();

	const cVec3 & GetMin() const;
	const cVec3 & GetMax() const;

	cVec3 & GetMin();
	cVec3 & GetMax();

	void Set(const cVec3 &Min, const cVec3 &Max);
	void SetMin(const cVec3 &);
	void SetMax(const cVec3 &);
	
	const cVec3 GetSize() const;
	float GetSizeX() const;
	float GetSizeY() const;
	float GetSizeZ() const;
	float GetDiagonal() const;
	
	cVec3 GetCenter() const;

	int GetLargestAxis() const;

	void SetEmpty();
	void SetZero();
	bool IsEmpty() const;

	static const cBounds Empty;
	static const cBounds Zero;
	static const cBounds One; // m_Min = -cVec3::One, m_Max = cVec3::One
	
	bool AddPoint(const cVec3 &);
	bool AddBounds(const cBounds &);

	void Inflate(const float DeltaX, const float DeltaY, const float DeltaZ);
	void Inflate(const float DeltaXYZ) {
		Inflate(DeltaXYZ, DeltaXYZ, DeltaXYZ);
	}
	void Inflate(const cVec3 &Delta) {
		Inflate(Delta.x, Delta.y, Delta.z);
	}

	void Translate(const cVec2 &);
	void Translate(const cVec3 &);
	
	float DistanceToPointSq(const cVec2 &p) const; // 0.0f for inside
	float DistanceToPointSq(const cVec3 &p) const; // 0.0f for inside

	bool ContainsPoint(const cVec2 &) const;
	bool ContainsCircle(const cVec2 &Center, const float Radius) const;
	bool ContainsPoint(const cVec3 &) const;
	bool ContainsBounds(const cBounds &) const;
	bool IntersectsBounds(const cBounds &) const;
//	bool LineIntersection(const cVec3 &A, const cVec3 &B) const;

	// Returns "true" if the ray intersects the bounds.
	// The ray can intersect the bounds in both directions from the start point.
	// If "RayOrig" is inside the bounds it is considered an intersection with "Scale == 0".
	// Intersection point is "RayOrig + RayDir * Scale"
	bool RayIntersection(const cVec3 &RayOrig, const cVec3 &RayDir, float &Scale) const;
	bool RayIntersection(const cVec3 &RayOrig, const cVec3 &RayDir, cVec3 *Cross = NULL) const {
		float S;
		bool r = RayIntersection(RayOrig, RayDir, S);
		if(r && Cross != NULL) {
			*Cross = RayOrig + RayDir * S;
		}
		return r;
	}

	static const cBounds FromPoints(const cVec2 *pPoints, const int nCount);
	static const cBounds FromPoints(const cVec3 *pPoints, const int nCount);
	static const cBounds FromPoints(const cList<cVec3> &Points);

	void ToPoints(cVec3 *P8) const; // Order is ready for "cFrustum" construction
	const cSphere ToSphere() const;

	static const cBounds Lerp(const cBounds &l, const cBounds &r, const float s);

	static const cBounds Transform(const cBounds &B, const cMat4 &T);
	void Transform(const cMat4 &T);

	const cRect ToRect() const;
private:
	cVec3 m_Min;
	cVec3 m_Max;
}; // cBounds

// cBounds.ctor
inline cBounds::cBounds() {
}

// cBounds.cotr : (const cVec3 &)
inline cBounds::cBounds(const cVec3 &p)
: m_Min(p), m_Max(p) {}

// cBounds.ctor : (const cVec3 &, const cVec3 &)
inline cBounds::cBounds(const cVec3 &bMin, const cVec3 &bMax)
: m_Min(bMin), m_Max(bMax) {}

// cBounds.dtor
inline cBounds::~cBounds() {
}

// cBounds::Set
inline void cBounds::Set(const cVec3 &Min, const cVec3 &Max) {
	m_Min = Min;
	m_Max = Max;
}

// cBounds::GetMin : const cVec3 & () const
inline const cVec3 & cBounds::GetMin() const {
	return m_Min;
}

// cBounds::GetMax : const cVec3 & () const
inline const cVec3 & cBounds::GetMax() const {
	return m_Max;
}

// cBounds::SetMin : void(const cVec3 &)
inline void cBounds::SetMin(const cVec3 &bMin) {
	m_Min = bMin;
}

// cBounds::SetMax : void(const cVec3 &)
inline void cBounds::SetMax(const cVec3 &bMax) {
	m_Max = bMax;
}

// cBounds::GetMin : cVec3 & ()
inline cVec3 & cBounds::GetMin() {
	return m_Min;
}

// cBounds::GetMax : cVec3 & ()
inline cVec3 & cBounds::GetMax() {
	return m_Max;
}

// cBounds::SetEmpty
inline void cBounds::SetEmpty() {
	m_Min.Set(cMath::FloatMaxValue);
	m_Max.Set(-cMath::FloatMaxValue);
}

// cBounds::IsEmpty
inline bool cBounds::IsEmpty() const {
	return m_Min.x > m_Max.x || m_Min.y > m_Max.y;
}

// cBounds::SetZero
inline void cBounds::SetZero() {
	m_Min.SetZero();
	m_Max.SetZero();
}

// cBounds::GetSize
inline const cVec3 cBounds::GetSize() const {
	return m_Max - m_Min;
}

// cBounds::GetSizeX : float() const
inline float cBounds::GetSizeX() const {
	return m_Max.x - m_Min.x;
}

// cBounds::GetSizeY : float() const
inline float cBounds::GetSizeY() const {
	return m_Max.y - m_Min.y;
}

// cBounds::GetSizeZ : float() const
inline float cBounds::GetSizeZ() const {
	return m_Max.z - m_Min.z;
}

// cBounds::GetDiagonal : float() const
inline float cBounds::GetDiagonal() const {
	return cVec3::Distance(m_Max, m_Min);
}

// cBounds::GetCenter : cVec3() const
inline cVec3 cBounds::GetCenter() const {
	return 0.5f * (m_Max + m_Min);
}

// cBounds::GetLargestAxis : int() const
inline int cBounds::GetLargestAxis() const {
	cVec3 d = m_Max - m_Min;
	if(d.x > d.y && d.x > d.z) {
		return 0;
	} else if(d.y > d.x && d.y > d.z) {
		return 1;
	} else {
		return 2;
	}
}

// cBounds::AddPoint : bool(const cVec3 &)
inline bool cBounds::AddPoint(const cVec3 &p) {
	bool IsExpanded = false;
	if(p.x < m_Min.x) {
		m_Min.x = p.x;
		IsExpanded = true;
	}
	if(p.y < m_Min.y) {
		m_Min.y = p.y;
		IsExpanded = true;
	}
	if(p.z < m_Min.z) {
		m_Min.z = p.z;
		IsExpanded = true;
	}
	if(p.x > m_Max.x) {
		m_Max.x = p.x;
		IsExpanded = true;
	}
	if(p.y > m_Max.y) {
		m_Max.y = p.y;
		IsExpanded = true;
	}
	if(p.z > m_Max.z) {
		m_Max.z = p.z;
		IsExpanded = true;
	}
	return IsExpanded;
}

// cBounds::AddBounds : bool(const cBounds &)
inline bool cBounds::AddBounds(const cBounds &B) {
	bool IsExpanded = false;
	if(B.m_Min.x < m_Min.x) {
		m_Min.x = B.m_Min.x;
		IsExpanded = true;
	}
	if(B.m_Min.y < m_Min.y) {
		m_Min.y = B.m_Min.y;
		IsExpanded = true;
	}
	if(B.m_Min.z < m_Min.z) {
		m_Min.z = B.m_Min.z;
		IsExpanded = true;
	}
	if(B.m_Max.x > m_Max.x) {
		m_Max.x = B.m_Max.x;
		IsExpanded = true;
	}
	if(B.m_Max.y > m_Max.y) {
		m_Max.y = B.m_Max.y;
		IsExpanded = true;
	}
	if(B.m_Max.z > m_Max.z) {
		m_Max.z = B.m_Max.z;
		IsExpanded = true;
	}
	return IsExpanded;
}

// cBounds::Translate : void(const cVec2 &)
inline void cBounds::Translate(const cVec2 &t) {
	m_Min += cVec3(t, 0.0f);
	m_Max += cVec3(t, 0.0f);
}

// cBounds::Translate : void(const cVec3 &)
inline void cBounds::Translate(const cVec3 &t) {
	m_Min += t;
	m_Max += t;
}

// cBounds::ContainsPoint : bool(const cVec2 &) const
inline bool cBounds::ContainsPoint(const cVec2 &p) const {
	return p.x >= m_Min.x && p.x <= m_Max.x &&
		p.y >= m_Min.y && p.y <= m_Max.y;
}

// cBounds::ContainsCircle
inline bool cBounds::ContainsCircle(const cVec2 &Center, const float Radius) const {
	cVec2 c = cVec2::Clamp(Center, m_Min.ToVec2(), m_Max.ToVec2());
	float d = cVec2::DistanceSq(c, Center);
	float r2 = Radius * Radius;
	return d <= r2;
}

// cBounds::ContainsPoint : bool(const cVec3 &) const
inline bool cBounds::ContainsPoint(const cVec3 &p) const {
	return p.x >= m_Min.x && p.x <= m_Max.x &&
		p.y >= m_Min.y && p.y <= m_Max.y &&
		p.z >= m_Min.z && p.z <= m_Max.z;
}

// cBounds::ContainsBounds : bool(const cBounds &) const
inline bool cBounds::ContainsBounds(const cBounds &B) const {
	return B.m_Min.x >= m_Min.x && B.m_Max.x <= m_Max.x &&
		B.m_Min.y >= m_Min.y && B.m_Max.y <= m_Max.y &&
		B.m_Min.z >= m_Min.z && B.m_Max.z <= m_Max.z;
}

// cBounds::IntersectsBounds : bool(const cBounds &) const
inline bool cBounds::IntersectsBounds(const cBounds &B) const {
	return B.m_Min.x <= m_Max.x && B.m_Max.x >= m_Min.x &&
		B.m_Min.y <= m_Max.y && B.m_Max.y >= m_Min.y &&
		B.m_Min.z <= m_Max.z && B.m_Max.z >= m_Min.z;
}

// cBounds::ToSphere
inline const cSphere cBounds::ToSphere() const {
	cSphere S;
	S.SetCenter((m_Min + m_Max) * 0.5f);
	S.SetRadius((m_Max - S.GetCenter()).Length());
	return S;
}

// cBounds::Lerp
inline const cBounds cBounds::Lerp(const cBounds &l, const cBounds &r, const float s) {
	if(l.IsEmpty()) {
		return r;
	} else if(r.IsEmpty()) {
		return l;
	}
	cBounds b;
	b.m_Min = cVec3::Lerp(l.m_Min, r.m_Min, s);
	b.m_Max = cVec3::Lerp(l.m_Max, r.m_Max, s);
	return b;
}

// cBounds::ToRect
inline const cRect cBounds::ToRect() const {
	return cRect(cRect::SetCtor, m_Min.ToVec2(), m_Max.ToVec2());
}

// cBounds::Inflate
inline void cBounds::Inflate(const float DeltaX, const float DeltaY, const float DeltaZ) {
	m_Min.x -= DeltaX;
	m_Min.y -= DeltaY;
	m_Min.z -= DeltaZ;

	m_Max.x += DeltaX;
	m_Max.y += DeltaY;
	m_Max.z += DeltaZ;
}




// ----------------------------------------------------------------------------
// Templated 'cBounds'.
// @todo fine  Change 'cBounds' to 'Bounds' into the project.
template< typename Type, size_t Dim >
class Bounds {
public:
	typedef cVec< Type, Dim >   coord_t;
	typedef coord_t             corner_t;
	typedef cVec< Type, Dim >   bsize_t;
	// for sharp calc when 'Type' is int
	typedef cVec< float, Dim >  fcoord_t;

	// specialize type for ContainsLine()
	typedef cVec< int,   2>  coordInt2_t;
	typedef cVec< int,   3>  coordInt3_t;
	typedef cVec< float, 2>  coordFloat2_t;
	typedef cVec< float, 3>  coordFloat3_t;

public:
	Bounds();
	Bounds( const corner_t& Min, const corner_t& Max );
	virtual ~Bounds() {}

	const corner_t& GetMin() const { return Min;  }
	const corner_t& GetMax() const { return Max;  }
	const bsize_t& GetSize() const { return Size; }

	bool IsEmpty() const { return Size.IsZero(); }

	bool operator==( const Bounds& ) const;

	// Extend the bounds when point is out of border.
	// @return true when bounds are expanded.
	bool AddPoint( const coord_t& );

    void Transform( const comms::cMat4& );

	bool ContainsPoint( const coord_t& ) const;

	// @todo fine  Release as partial template specialization in VS2013.
	bool ContainsLine( const coordInt2_t&   a,  const coordInt2_t& b   ) const;
	bool ContainsLine( const coordInt3_t&   a,  const coordInt3_t& b   ) const;
	bool ContainsLine( const coordFloat2_t& a,  const coordFloat2_t& b ) const;
	bool ContainsLine( const coordFloat3_t& a,  const coordFloat3_t& b ) const;

	static const Bounds&  ZERO();

private:
	corner_t  Min;
	corner_t  Max;
	bsize_t   Size;
};




template< typename Type, size_t Dim >
inline
Bounds< Type, Dim >::Bounds() :
	Min( corner_t::ZERO() ),
	Max( corner_t::ZERO() ),
	Size( bsize_t::ZERO() )
{
}




template< typename Type, size_t Dim >
inline
Bounds< Type, Dim >::Bounds( const corner_t& Min, const corner_t& Max ) :
	Min( Min ),
	Max( Max ),
	Size( Max - Min )
{
	for (size_t i = 0; i < Dim; ++i) {
		cAssertM( Min[ i ] <= Max[ i ], "Incorrect bounds." );
	}
}




template< typename Type, size_t Dim >
inline bool
Bounds< Type, Dim >::operator==( const Bounds& bounds ) const {
	for (size_t i = 0; i < Dim; ++i) {
		if ( (bounds.GetMin() != Min) || (bounds.GetMax() != Max) ) {
			return false;
		}
	}
	return true;
}




template< typename Type, size_t Dim >
inline bool
Bounds< Type, Dim >::AddPoint( const coord_t& p ) {
	bool  expanded = false;
	for (size_t i = 0; i < Dim; ++i) {
		if (p[ i ] < Min[ i ]) {
			Min[ i ] = p[ i ];
			expanded = true;
		}
		if (p[ i ] > Max[ i ]) {
			Max[ i ] = p[ i ];
			expanded = true;
		}
	}
    if ( expanded ) {
        Size = Max - Min;
    }
	return expanded;
}




template< typename Type, size_t Dim >
inline void
Bounds< Type, Dim >::Transform( const cMat4& m ) {
    Min.TransformCoordinate( m );
    Max.TransformCoordinate( m );
    Size = Max - Min;
}




template< typename Type, size_t Dim >
inline const Bounds< Type, Dim >&
Bounds< Type, Dim >::ZERO() {
    static const Bounds< Type, Dim >  r;
	return r;
}




template< typename Type, size_t Dim >
::std::ostream& operator<<( ::std::ostream& out,  const Bounds< Type, Dim >& bb ) {
    out << "[" << bb.GetMin() << ", " << bb.GetMax() << "]";
    return out;
}
