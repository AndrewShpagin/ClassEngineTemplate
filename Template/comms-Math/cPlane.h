#pragma once

//-----------------------------------------------------------------------------
// cPlane
//-----------------------------------------------------------------------------
class cPlane {
public:
	float a, b, c, d;

	cPlane();
	cPlane(const float A, const float B, const float C, const float D);
	cPlane(const cVec3 &t0, const cVec3 &t1, const cVec3 &t2); // From points
	cPlane(const cVec3 &Pt, const cVec3 &Normal); // From point and normal
	cPlane(const cVec3 &Normal, const float Offset); // From normal and distance to origin

	void SetNormalize(const float A, const float B, const float C, const float D);

	const cVec3 & GetNormal() const;
	void SetNormal(const cVec3 &);
	void SetOffset(const float Offset) { // i.e. distance to origin
		d = -Offset;
	}
	float GetOffset() const { // Signed distance to origin
		return -d;
	}
	cVec3 & MutableNormal();


	float SetFromPoints(const cVec3 &t0, const cVec3 &t1, const cVec3 &t2);
	void SetFromPointAndNormal(const cVec3 &Pt, const cVec3 &Normal);
	
	void MoveToPoint(const cVec3 &p);
	
	float Distance(const cVec3 &p) const { // Signed distance to point
		return cVec3::Dot(GetNormal(), p) + d;
	}
	
	enum eSide {
		S_FRONT, S_BACK, S_CROSS, S_ON
	};
	
	const cVec3 ProjectPoint(const cVec3 &p) const;
	const cVec3 ProjectVector(const cVec3 &u) const;
	const cVec3 MirrorPoint(const cVec3 &p) const;
	const cVec3 MirrorVector(const cVec3 &u) const;
	const cQuat MirrorOrient(const cQuat &q) const;
	void FlipNormal();
	
	// Returns "true" if all vertices of the bounds are on negative side of this plane
	bool BelowPlane(const cBounds &B, const cMat4 &T) const;

	eSide ClassifyPoint(const cVec3 &p, const float Eps = cMath::SpaceEpsilon) const;
	eSide ClassifySphere(const cSphere &S, const float Eps = cMath::SpaceEpsilon) const;

	bool IsFrontFacingTo(const cVec3 &Dir) const;
	bool RayIntersection(const cVec3 &RayOrig, const cVec3 &RayDir, float *pScale = NULL, cVec3 *pCross = NULL) const;
	bool SegIntersection(const cVec3 &S0, const cVec3 &S1, cVec3 *pCross = NULL) const;
	bool PlaneIntersection(const cPlane &P, cVec3 *pCross = NULL, cVec3 *pDir = NULL) const;

	float * ToPtr();
	const float * ToPtr() const;

	cVec4 & ToVec4();
	const cVec4 & ToVec4() const;

	const cStr ToStr(const int nPrec = 2) const;
}; // cPlane

// .ctor : ()
inline cPlane::cPlane() {
}

// .ctor : (const float, const float, const float, const float)
inline cPlane::cPlane(const float A, const float B, const float C, const float D)
: a(A), b(B), c(C), d(D) {}

// .ctor : (const cVec3 &, const cVec3 &, const cVec3 &)
inline cPlane::cPlane(const cVec3 &t0, const cVec3 &t1, const cVec3 &t2) {
	SetFromPoints(t0, t1, t2);
}

// .ctor : (const cVec3 &, const cVec3 &)
inline cPlane::cPlane(const cVec3 &Pt, const cVec3 &Normal) {
	SetFromPointAndNormal(Pt, Normal);
}

// .ctor : (const cVec3 &, const float)
inline cPlane::cPlane(const cVec3 &Normal, const float Offset)
: a(Normal.x), b(Normal.y), c(Normal.z), d(-Offset) {}

// cPlane::SetNormalize
inline void cPlane::SetNormalize(const float A, const float B, const float C, const float D) {
	float div = cMath::Sqrt(A*A + B*B + C*C);
	if (div == 0.0f) div = 1.0f;
	a = A / div;
	b = B / div;
	c = C / div;
	d = D / div;
}

// cPlane::GetNormal : const cVec3 & () const
inline const cVec3 & cPlane::GetNormal() const {
	return *reinterpret_cast<const cVec3 *>(&a);
}

// cPlane::SetNormal : void(const cVec3 &)
inline void cPlane::SetNormal(const cVec3 &Normal) {
	a = Normal.x;
	b = Normal.y;
	c = Normal.z;
}

// cPlane::MutableNormal : cVec3 & ()
inline cVec3 & cPlane::MutableNormal() {
	return *reinterpret_cast<cVec3 *>(&a);
}

// cPlane::SetFromPoints : float(const cVec3 &, const cVec3 &, const cVec3 &)
inline float cPlane::SetFromPoints(const cVec3 &t0, const cVec3 &t1, const cVec3 &t2) {
	SetNormal(cVec3::Cross(t1 - t0, t2 - t0));
	const float AreaSq = GetNormal().LengthSq();
	if(AreaSq < cMath::EpsilonSq) {
		a = b = c = d = 0.0f;
		return 0.0f;
	} else {
		const float Area = cMath::Sqrt(AreaSq);
		MutableNormal() *= 1.0f / Area;
		d = -cVec3::Dot(GetNormal(), t0);
		return Area;
	}
}

// cPlane::SetFromPointAndNormal : void(const cVec3 &, const cVec3 &)
inline void cPlane::SetFromPointAndNormal(const cVec3 &Pt, const cVec3 &Normal) {
	SetNormal(Normal);
	d = -cVec3::Dot(Normal, Pt);
}

// cPlane::MoveToPoint
inline void cPlane::MoveToPoint(const cVec3 &p) {
	d = -cVec3::Dot(GetNormal(), p);
}

// cPlane::ProjectPoint
inline const cVec3 cPlane::ProjectPoint(const cVec3 &p) const {
	return p - Distance(p) * GetNormal();
}

// cPlane::ProjectVector
inline const cVec3 cPlane::ProjectVector(const cVec3 &u) const {
	return u - cVec3::Dot(u, GetNormal()) * GetNormal();
}

// cPlane::MirrorPoint
inline const cVec3 cPlane::MirrorPoint(const cVec3 &p) const {
	return p - 2.0f * Distance(p) * GetNormal();
}

// cPlane::MirrorVector
inline const cVec3 cPlane::MirrorVector(const cVec3 &u) const {
	return u - 2.0f * cVec3::Dot(u, GetNormal()) * GetNormal();
}
// cPlane::FlipNormal
inline void cPlane::FlipNormal(){
	a=-a;
	b=-b;
	c=-c;
	d=-d;
}
// cPlane::IsFrontFacingTo : bool(const cVec3 &) const
inline bool cPlane::IsFrontFacingTo(const cVec3 &Dir) const {
	return cVec3::Dot(GetNormal(), Dir) <= 0.0f;
}

// cPlane::RayIntersection : bool(const cVec3 &, const cVec3 &, float *, cVec3 *) const
inline bool cPlane::RayIntersection(const cVec3 &RayOrig, const cVec3 &RayDir, float *pScale, cVec3 *pCross) const {
	float d1 = cVec3::Dot(GetNormal(), RayOrig) + d;
	float d2 = cVec3::Dot(GetNormal(), RayDir);

	if(0.0f == d2) {
		return false;
	}
	float Scale = - d1 / d2;
	if(pScale != NULL) {
		*pScale = Scale;
	}
	if(pCross != NULL) {
		*pCross = RayOrig + Scale * RayDir;
	}
	return true;
}

//------------------------------------------------------------------------------------------
// cPlane::SegIntersection
//------------------------------------------------------------------------------------------
inline bool cPlane::SegIntersection(const cVec3 &S0, const cVec3 &S1, cVec3 *pCross) const {
	float d0 = cVec3::Dot(GetNormal(), S0) + d;
	float d1 = cVec3::Dot(GetNormal(), S1) + d;
	
	if(d0 > 0.0f && d1 > 0.0f) {
		return false;
	}
	if(d0 < 0.0f && d1 < 0.0f) {
		return false;
	}
	float fr = d0 / (d0 - d1);
	if(fr >= 0.0f && fr <= 1.0f) {
		if(pCross != NULL) {
			*pCross = cVec3::Lerp(S0, S1, fr);
		}
		return true;
	}
	return false;
} // cPlane::SegIntersection

//--------------------------------------------------------------------------------------
// cPlane::PlaneIntersection
//--------------------------------------------------------------------------------------
inline bool cPlane::PlaneIntersection(const cPlane &P, cVec3 *pCross, cVec3 *pDir) const {
	double n00 = GetNormal().LengthSq();
	double n01 = cVec3::Dot(GetNormal(), P.GetNormal());
	double n11 = P.GetNormal().LengthSq();
	double Det = n00 * n11 - n01 * n01;
	
	if(cMath::IsZero(Det)) {
		return false;
	}
	
	if(pDir) {
		*pDir = cVec3::Cross(GetNormal(), P.GetNormal());
	}
	if(pCross) {
		double iDet = 1.0 / Det;
		float f0 = float((n01 * P.d - n11 * d) * iDet);
		float f1 = float((n01 * d - n00 * P.d) * iDet);
		
		*pCross = f0 * GetNormal() + f1 * P.GetNormal();
	}
	return true;
}

//------------------------------------------------------------------------------------
// cPlane::ClassifyPoint : cPlane::eSide(const cVec3 &, const float) const
//------------------------------------------------------------------------------------
inline cPlane::eSide cPlane::ClassifyPoint(const cVec3 &p, const float Eps) const {
	float d = Distance(p);
	if(d > Eps) {
		return S_FRONT;
	}
	if(d < - Eps) {
		return S_BACK;
	}
	return S_ON;
}

//------------------------------------------------------------------------------------
// cPlane::ClassifySphere : cPlane::eSide(const cSphere &, const float) const
//------------------------------------------------------------------------------------
inline cPlane::eSide cPlane::ClassifySphere(const cSphere &S, const float Eps) const {
	float d = Distance(S.GetCenter());
	if(d > S.GetRadius() + Eps) {
		return S_FRONT;
	}
	if(d < - S.GetRadius() - Eps) {
		return S_BACK;
	}
	return S_CROSS;
}

// cPlane::ToVec4 : const cVec4 & () const
inline const cVec4 & cPlane::ToVec4() const {
	return *reinterpret_cast<const cVec4 *>(&a);
}

// cPlane::ToVec4 : cVec4 & ()
inline cVec4 & cPlane::ToVec4() {
	return *reinterpret_cast<cVec4 *>(&a);
}

// cPlane::ToPtr : const float * () const
inline const float * cPlane::ToPtr() const {
	return reinterpret_cast<const float *>(&a);
}

// cPlane::ToPtr : float * ()
inline float * cPlane::ToPtr() {
	return reinterpret_cast<float *>(&a);
}
