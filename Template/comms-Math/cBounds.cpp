#include "comms-Math.h"

namespace comms {

const cBounds cBounds::Zero(cVec3(0.0f), cVec3(0.0f));
const cBounds cBounds::Empty(cVec3(cMath::FloatMaxValue), cVec3(-cMath::FloatMaxValue));
const cBounds cBounds::One(-cVec3(1.0f), cVec3(1.0f));

// cBounds::FromPoints : (const cVec2 *, ...)
const cBounds cBounds::FromPoints(const cVec2 *pPoints, const int nCount) {
	cAssert(pPoints);
	cAssert(nCount > 0);

	cVec2 bMin(pPoints[0]), bMax(pPoints[0]);
	for(int i = 1; i < nCount; i++) {
		bMin = cVec2::Min(bMin, pPoints[i]);
		bMax = cVec2::Max(bMax, pPoints[i]);
	}

	return cBounds(cVec3(bMin, 0.0f), cVec3(bMax, 0.0f));
}

// cBounds::FromPoints : (const cVec3 *, ...)
const cBounds cBounds::FromPoints(const cVec3 *pPoints, const int nCount) {
	cAssert(pPoints);
	cAssert(nCount > 0);

	cVec3 bMin(pPoints[0]), bMax(pPoints[0]);
	for(int i = 1; i < nCount; i++) {
		bMin = cVec3::Min(bMin, pPoints[i]);
		bMax = cVec3::Max(bMax, pPoints[i]);
	}

	return cBounds(bMin, bMax);
}

// cBounds::FromPoints
const cBounds cBounds::FromPoints(const cList<cVec3> &Points) {
	return FromPoints(Points.ToPtr(), Points.Count());
}

//-----------------------------------------------------------------------------
// cBounds::DistanceToPointSq : float(const cVec2 &) const
//-----------------------------------------------------------------------------
float cBounds::DistanceToPointSq(const cVec2 &p) const {
	if(ContainsPoint(p)) {
		return 0.0f;
	}

	float d2 = 0.0f;
	int i;
	for(i = 0; i < 2; i++) {
		if(p[i] < m_Min[i]) {
			d2 += cMath::Square(m_Min[i] - p[i]);
		} else if(p[i] > m_Max[i]) {
			d2 += cMath::Square(p[i] - m_Max[i]);
		}
	}
	return d2;
}

//-----------------------------------------------------------------------------
// cBounds::DistanceToPointSq : float(const cVec3 &) const
//-----------------------------------------------------------------------------
float cBounds::DistanceToPointSq(const cVec3 &p) const {
	if(ContainsPoint(p)) {
		return 0.0f;
	}

	float d2 = 0.0f;
	int i;
	for(i = 0; i < 3; i++) {
		if(p[i] < m_Min[i]) {
			d2 += cMath::Square(m_Min[i] - p[i]);
		} else if(p[i] > m_Max[i]) {
			d2 += cMath::Square(p[i] - m_Max[i]);
		}
	}
	return d2;
}

// cBounds::ToPoints
void cBounds::ToPoints(cVec3 *P8) const {
	const cVec3 *Bounds = &m_Min;
	int i, X, Y, Z;
	for(i = 0; i < 8; i++) {
		X = ((i ^ (i >> 1)) + 1) & 1;
		Y = (i >> 1) & 1;
		Z = (i >> 2) & 1;
		P8[i].x = Bounds[X].x;
		P8[i].y = Bounds[Y].y;
		P8[i].z = Bounds[Z].z;
	}
}

//---------------------------------------------------------------------------------------------
// cBounds::RayIntersection
//---------------------------------------------------------------------------------------------
bool cBounds::RayIntersection(const cVec3 &RayOrig, const cVec3 &RayDir, float &Scale ) const {
	int i, ax0, ax1, ax2, side, inside;
	float f;
	cVec3 hit;
	float epsilon = (m_Max - m_Min).Length2() / 1024.0f;
	
	ax0 = -1;
	inside = 0;
	for(i = 0; i < 3; i++) {
		if(RayOrig[i] < m_Min[i]) {
			side = 0;
		} else if(RayOrig[i] > m_Max[i]) {
			side = 1;
		} else {
			inside++;
			continue;
		}
		if(RayDir[i] == 0.0f) {
			continue;
		}
		f = (RayOrig[i] - (0 == side ? m_Min[i] : m_Max[i]));
		if(ax0 < 0 || cMath::Abs( f ) > cMath::Abs(Scale * RayDir[i])) {
			Scale = -(f / RayDir[i]);
			ax0 = i;
		}
	}
	
	if(ax0 < 0) {
		Scale = 0.0f;
		return inside == 3; // Returns "true" if "RayOrig" is inside the bounds
	}
	
	ax1 = (ax0 + 1) % 3;
	ax2 = (ax0 + 2) % 3;
	hit[ax1] = RayOrig[ax1] + Scale * RayDir[ax1];
	hit[ax2] = RayOrig[ax2] + Scale * RayDir[ax2];
	
	return hit[ax1] >= m_Min[ax1] - epsilon && hit[ax1] <= m_Max[ax1] + epsilon &&
		hit[ax2] >= m_Min[ax2] - epsilon && hit[ax2] <= m_Max[ax2] + epsilon;
} // cBounds::RayIntersection

// cBounds::Transform
const cBounds cBounds::Transform(const cBounds &B, const cMat4 &T) {
	if(B.IsEmpty()) {
		return cBounds::Empty;
	}
	cVec3 P[8];
	B.ToPoints(P);
	cVec3::TransformCoordinate(P, 8, T);
	return FromPoints(P, 8);
}

// cBounds::Transform
void cBounds::Transform(const cMat4 &T) {
	*this = Transform(*this, T);
}




// ----------------------------------------------------------------------------
template< typename Type, size_t Dim >
inline bool
Bounds< Type, Dim >::ContainsPoint( const coord_t& p ) const {
	for (int i = 0; i < Dim; ++i) {
		if ( (p[ i ] < Min[ i ]) || (p[ i ] > Max[ i ]) ) {
			return false;
		}
	}
	// true when not empty
	return !IsEmpty();
}


template bool
Bounds< int, 2 >::ContainsPoint( const coord_t& ) const;

template bool
Bounds< int, 3 >::ContainsPoint( const coord_t& ) const;

template bool
Bounds< float, 2 >::ContainsPoint( const coord_t& ) const;

template bool
Bounds< float, 3 >::ContainsPoint( const coord_t& ) const;


template< typename Type, size_t Dim >
inline bool
Bounds< Type, Dim >::ContainsLine( const coordInt2_t& a, const coordInt2_t& b ) const {
	const coordFloat2_t  pa((float)a[0], (float)a[1]);
	const coordFloat2_t  pb((float)b[0], (float)b[1]);
	return ContainsLine( pa, pb );
}




template< typename Type, size_t Dim >
inline bool
Bounds< Type, Dim >::ContainsLine( const coordInt3_t& a, const coordInt3_t& b ) const {
	const coordFloat3_t  pa((float)a[0], (float)a[1], (float)a[2]);
	const coordFloat3_t  pb((float)b[0], (float)b[1], (float)b[2]);
	return ContainsLine( pa, pb );
}




template< typename Type, size_t Dim >
inline bool
Bounds< Type, Dim >::ContainsLine( const coordFloat2_t& a, const coordFloat2_t& b ) const {

	cAssertM( 2 == Dim, "Mismatch dimensions." );

	// @source http://stackoverflow.com/a/18292964/963948

	// completely outside?
	if ( ((a[ 0 ] <= Min[ 0 ]) && (b[ 0 ] <= Min[ 0 ]))
	  || ((a[ 1 ] <= Min[ 1 ]) && (b[ 1 ] <= Min[ 1 ]))
	  || ((a[ 0 ] >= Max[ 0 ]) && (b[ 0 ] >= Max[ 0 ]))
	  || ((a[ 1 ] >= Max[ 1 ]) && (b[ 1 ] >= Max[ 1 ]))
	) {
		return false;
	}

	const float  m = (b[ 1 ] - a[ 1 ]) / (b[ 0 ] - a[ 0 ]);
	{
		float  y = m * (Min[ 0 ] - a[ 0 ]) + a[ 1 ];
		if ((y > Min[ 1 ]) && (y < Max[ 1 ])) { return true; }
		y = m * (Max[ 0 ] - a[ 0 ]) + a[ 1 ];
		if ((y > Min[ 1 ]) && (y < Max[ 1 ])) { return true; }
	}
	{
		float  x = (Min[ 1 ] - a[ 1 ]) / m + a[ 0 ];
		if ((x > Min[ 0 ]) && (x < Max[ 0 ])) { return true; }
		x = (Max[ 1 ] - a[ 1 ]) / m + a[ 0 ];
		if ((x > Min[ 0 ]) && (x < Max[ 0 ])) { return true; }
	}

	return false;
}


template<typename Type, size_t Dim>
const typename Bounds<Type, Dim>::fcoord_t
coord_t_to_fcoord_t(const typename Bounds<Type, Dim>::coord_t &c) {
	typename Bounds<Type, Dim>::fcoord_t f;
	for(int i = 0; i < Dim; i++) {
		f[i] = (float)c[i];
	}
	return f;
}

template< typename Type, size_t Dim >
inline bool
Bounds< Type, Dim >::ContainsLine( const coordFloat3_t& a, const coordFloat3_t& b ) const {

	cAssertM( 3 == Dim, "Mismatch dimensions." );

	// @source http://gamedev.net/topic/338987-aabb---line-segment-intersection-test/?view=findpost&p=3209917
	const fcoord_t  d = static_cast< fcoord_t >(b - a) / 2.0f;
	const fcoord_t  absD = fcoord_t::Abs( d );
	const fcoord_t  e = coord_t_to_fcoord_t<Type, Dim>(Max - Min) / 2.0f;
	const fcoord_t  c =
		static_cast< fcoord_t >( a ) + d -
		coord_t_to_fcoord_t<Type, Dim>(Min + Max) / 2.0f;

	for (int i = 0; i < Dim; ++i) {
		if (cMath::Abs( c[ i ] ) > (e[ i ] + absD[ i ])) { return false; }
	}

	// line has cross with Dim-axis
	// # Optimized for 3-Dim.
	static const typename fcoord_t::value_type  EPSILON =
		::std::numeric_limits< typename fcoord_t::value_type >::epsilon();

	if (cMath::Abs( d[ 1 ] * c[ 2 ] - d[ 2 ] * c[ 1 ] ) >
		(e[ 1 ] * absD[ 2 ] + e[ 2 ] * absD[ 1 ] + EPSILON)) { return false; }

	if (cMath::Abs( d[ 2 ] * c[ 0 ] - d[ 0 ] * c[ 2 ] ) >
		(e[ 2 ] * absD[ 0 ] + e[ 0 ] * absD[ 2 ] + EPSILON)) { return false; }

	if (cMath::Abs( d[ 0 ] * c[ 1 ] - d[ 1 ] * c[ 0 ] ) >
		(e[ 0 ] * absD[ 1 ] + e[ 1 ] * absD[ 0 ] + EPSILON)) { return false; }

	return true;
}


template bool
Bounds< int, 2 >::ContainsLine( const cVec< int, 2 >&,  const cVec< int, 2 >& ) const;

template bool
Bounds< int, 3 >::ContainsLine( const cVec< int, 3 >&,  const cVec< int, 3 >& ) const;

template bool
Bounds< float, 2 >::ContainsLine( const cVec< float, 2 >&,  const cVec< float, 2 >& ) const;

template bool
Bounds< float, 3 >::ContainsLine( const cVec< float, 3 >&,  const cVec< float, 3 >& ) const;



} // comms
