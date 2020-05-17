#include "comms-Math.h"

namespace comms {

// cPlane::MirrorOrient
const cQuat cPlane::MirrorOrient(const cQuat &q) const {
	cVec3 F, R, U;
	q.ToMat3().ToVectors(&F, &R, &U);
	F = MirrorVector(F);
	R = MirrorVector(R);
	U = MirrorVector(U);
	return cMat3::FromVectors(F, -R, U).ToQuat();
}

// cPlane::BelowPlane
bool cPlane::BelowPlane(const cBounds &B, const cMat4 &T) const {
	cVec3 P[8];
	B.ToPoints(P);
	cVec3::TransformCoordinate(P, 8, T);
	int i;
	for(i = 0; i < 8; i++) {
		if(Distance(P[i]) > 0.0f) {
			return false;
		}
	}
	return true;
}

} // comms
