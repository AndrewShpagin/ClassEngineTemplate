#include "comms-Math.h"

namespace comms {

const cVec2 cVec2::Zero(0.0f);
const cVec2 cVec2::One(1.0f, 1.0f);
const cVec2 cVec2::Infinity(cMath::FloatMaxValue);
const cVec2 cVec2::AxisX(1.0f, 0.0f);
const cVec2 cVec2::AxisY(0.0f, 1.0f);
const cVec2 cVec2::AxisNegX(-1.0f, 0.0f);
const cVec2 cVec2::AxisNegY(0.0f, -1.0f);

// cVec2::ToString
const cStr cVec2::ToString(const int Prec) const {
	return cStr::ToString(ToFloatPtr(), GetDimension(), Prec);
}

// cStr::friend operator << : (cStr &, const cVec2 &)
cStr & operator << (cStr &Str, const cVec2 &u) {
	Str += u.ToString();
	return Str;
}


//----------------------------------------------------------------------------------------------
// cVec2::DistanceToLineSegSq : float(const cVec2 &, const cVec2 &, float *)
//----------------------------------------------------------------------------------------------
float cVec2::DistanceToLineSegSq(const cVec2 &A, const cVec2 &B, float *pScale) const {
	const cVec2 Ap = *this - A;
	const cVec2 AB = B - A;
	const float l2 = AB.LengthSq();
	float Scale;
	if(l2 < cMath::Epsilon) {
		Scale = 0.5f;
	} else {
		Scale = cVec2::Dot(Ap, AB) / l2;
	}
	if(pScale) {
		*pScale = Scale;
	}
	if(Scale <= 0.0f) {
		return cVec2::DistanceSq(*this, A);
	}
	if(Scale >= 1.0f) {
		return cVec2::DistanceSq(*this, B);
	}
	return cVec2::DistanceSq(*this, A + AB * Scale);
}

// cVec2::RandRange1
const cVec2 cVec2::RandRange1() {
	cVec2 r;
	r.x = cMath::RandRange1();
	r.y = cMath::RandRange1();
	return r;
}

// cVec2::RandNormal
const cVec2 cVec2::RandNormal() {
	cVec2 r;
	float lSq;
	do {
		r = RandRange1();
		lSq = r.LengthSq();
	} while(lSq > 1.0f || lSq < cMath::Epsilon);
	float il = 1.0f / cMath::Sqrt(lSq);
	r *= il;
	return r;
}

// cVec2::SegIntersection
bool cVec2::SegIntersection(const cVec2 &L0, const cVec2 &L1, const cVec2 &R0, const cVec2 &R1, float *_l, float *_r) {
	float d = (L1.x - L0.x) * (R1.y - R0.y) - (L1.y - L0.y) * (R1.x - R0.x);
	if(0.0f == d) {
		return false;
	}
	float t = (L0.y - R0.y) * (R1.x - R0.x) - (L0.x - R0.x) * (R1.y - R0.y);
	float n = (L0.y - R0.y) * (L1.x - L0.x) - (L0.x - R0.x) * (L1.y - L0.y);
	float l = t / d;
	float r = n / d;
	if(l < 0.0f || l > 1.0f || r < 0.0f || r > 1.0f) {
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
