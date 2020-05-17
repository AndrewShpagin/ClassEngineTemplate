#include "comms-Math.h"

namespace comms {

const dVec2 dVec2::Zero(0.0);
const dVec2 dVec2::One(1.0, 1.0);
const dVec2 dVec2::Infinity(cMath::DoubleMaxValue);
const dVec2 dVec2::AxisX(1.0, 0.0);
const dVec2 dVec2::AxisY(0.0, 1.0);
const dVec2 dVec2::AxisNegX(-1.0, 0.0);
const dVec2 dVec2::AxisNegY(0.0, -1.0);

// dVec2::ToString
const cStr dVec2::ToString(const int Prec) const {
	return cStr::ToString(ToDoublePtr(), GetDimension(), Prec);
}

// cStr::friend operator << : (cStr &, const dVec2 &)
cStr & operator << (cStr &Str, const dVec2 &u) {
	Str += u.ToString();
	return Str;
}


//----------------------------------------------------------------------------------------------
// dVec2::DistanceToLineSegSq : double(const dVec2 &, const dVec2 &, double *)
//----------------------------------------------------------------------------------------------
double dVec2::DistanceToLineSegSq(const dVec2 &A, const dVec2 &B, double *pScale) const {
	const dVec2 Ap = *this - A;
	const dVec2 AB = B - A;
	const double l2 = AB.LengthSq();
	double Scale;
	if(l2 < cMath::Epsilon) {
		Scale = 0.5f;
	} else {
		Scale = dVec2::Dot(Ap, AB) / l2;
	}
	if(pScale) {
		*pScale = Scale;
	}
	if(Scale <= 0.0) {
		return dVec2::DistanceSq(*this, A);
	}
	if(Scale >= 1.0) {
		return dVec2::DistanceSq(*this, B);
	}
	return dVec2::DistanceSq(*this, A + AB * Scale);
}

// dVec2::RandRange1
const dVec2 dVec2::RandRange1() {
	dVec2 r;
	r.x = cMath::RandRange1();
	r.y = cMath::RandRange1();
	return r;
}

// dVec2::RandNormal
const dVec2 dVec2::RandNormal() {
	dVec2 r;
	double lSq;
	do {
		r = RandRange1();
		lSq = r.LengthSq();
	} while(lSq > 1.0 || lSq < cMath::Epsilon);
	double il = 1.0 / cMath::Sqrt(lSq);
	r *= il;
	return r;
}

// dVec2::SegIntersection
bool dVec2::SegIntersection(const dVec2 &L0, const dVec2 &L1, const dVec2 &R0, const dVec2 &R1, double *_l, double *_r) {
	double d = (L1.x - L0.x) * (R1.y - R0.y) - (L1.y - L0.y) * (R1.x - R0.x);
	if(0.0 == d) {
		return false;
	}
	double t = (L0.y - R0.y) * (R1.x - R0.x) - (L0.x - R0.x) * (R1.y - R0.y);
	double n = (L0.y - R0.y) * (L1.x - L0.x) - (L0.x - R0.x) * (L1.y - L0.y);
	double l = t / d;
	double r = n / d;
	if(l < 0.0 || l > 1.0 || r < 0.0 || r > 1.0) {
		return false;
	}
	if(_l != NULL) {
		*_l = l;
	}
	if(_r != NULL) {
		*_r = r;
	}
	return true;
}


} // comms
