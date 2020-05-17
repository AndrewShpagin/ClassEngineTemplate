#pragma once

class dSeg {
public:
	struct Result {
		double Time;
		dVec3 Normal;
		dVec3 Point;
	};

	dSeg() {}

	enum eEndsCtor	{ EndsCtor };
	enum eRayCtor	{ RayCtor };
	
	dSeg(const eEndsCtor, const dVec3 &Fm, const dVec3 &To, const double Radius = cMath::Epsilon) { SetFromEnds(Fm, To, Radius); }
	dSeg(const eRayCtor, const dVec3 &RayOrig, const dVec3 &RayDir, const double Radius = cMath::Epsilon) { SetFromRay(RayOrig, RayDir, Radius); }
	
	void SetFromEnds(const dVec3 &Fm, const dVec3 &To, const double Radius = cMath::Epsilon);
	void SetFromRay(const dVec3 &RayOrig, const dVec3 &RayDir, const double Radius = cMath::Epsilon);
	
	bool IsZero() const;

	const dVec3 & GetFm() const {
		AssertValid();
		return m_Fm;
	}
	const dVec3 & GetTo() const {
		AssertValid();
		return m_To;
	}
	double GetRadius() const {
		AssertValid();
		return m_Radius;
	}
	const dVec3 & GetNormal() const {
		AssertValid();
		return m_Normal;
	}
	double GetLength() const {
		AssertValid();
		return m_Length;
	}
	double GetInvLength() const {
		AssertValid();
		return m_InvLength;
	}

	const dVec3 GetHitPoint(const double Time) const;
	const dVec3 GetCenter() const;

	// w/o using radius:
	
	enum ConsiderAs { CLAMP_S0 = 0x10, CLAMP_S1 = 0x20, CLAMP_T0 = 0x40, CLAMP_T1 = 0x80,
		Line = 0,
		Ray = CLAMP_S0,
		Seg = CLAMP_S0 | CLAMP_S1,
		LineLine = 1,
		SegSeg = CLAMP_S0 | CLAMP_S1 | CLAMP_T0 | CLAMP_T1,
		RayRay = CLAMP_S0 | CLAMP_T0,
		SegRay = CLAMP_S0 | CLAMP_S1 | CLAMP_T0,
		LineRay = CLAMP_T0
	};
	
	const dSeg::Result ProjectPoint(const ConsiderAs To /* Line, Ray, Seg */, const dVec3 &p) const; // i.e. closest point
	// ---------------------------------
	//    Time is in  |  p is projected
	// ---------------------------------
	//	(-INF, 0.0f)  |	   before Fm
	//	[0.0f, 1.0f]  |	   inside Fm - To
	//	(1.0f, +INF)  |	   beyond To
	// ---------------------------------
	static double Distance(const ConsiderAs Fm /* Line, Ray, Seg */, const dSeg &P, const dVec3 &p);
	
	static void ClosestPoints(const ConsiderAs Between /* LineLine, SegSeg, RayRay, SegRay */, const dSeg &P, const dSeg &Q, dVec3 &p, dVec3 &q);
	static double Distance(const ConsiderAs Between /* LineLine, SegSeg, RayRay, SegRay */, const dSeg &P, const dSeg &Q);
	
	// w/ using radius:

private:
	dVec3 m_Fm;
	dVec3 m_To;
	double m_Radius;
	dVec3 m_Normal;
	double m_Length, m_InvLength;
	void AssertValid() const;
};

// dSeg::GetHitPoint
inline const dVec3 dSeg::GetHitPoint(const double Time) const {
	AssertValid();
	return dVec3::Lerp(GetFm(), GetTo(), Time);
}
// dSeg::GetCenter
inline const dVec3 dSeg::GetCenter() const {
	AssertValid();
	return dVec3::Lerp05(GetFm(), GetTo());
}
