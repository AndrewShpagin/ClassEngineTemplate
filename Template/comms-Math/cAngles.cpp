#include "comms-Math.h"

namespace comms {

const cAngles cAngles::Zero(0.0f, 0.0f, 0.0f);

// cAngles::ToString
const cStr cAngles::ToString(const int Prec) const {
	return cStr::ToString(ToFloatPtr(), GetDimension(), Prec);
}

// cAngles::Normalize360
void cAngles::Normalize360() {
	Pitch = cMath::AngleNormalize360(Pitch);
	Yaw = cMath::AngleNormalize360(Yaw);
	Roll = cMath::AngleNormalize360(Roll);
}

// cAngles::Normalize180
void cAngles::Normalize180() {
	Pitch = cMath::AngleNormalize180(Pitch);
	Yaw = cMath::AngleNormalize180(Yaw);
	Roll = cMath::AngleNormalize180(Roll);
}


// cAngles::ToQuat
const cQuat cAngles::ToQuat() const {
	return ToMat3().ToQuat();
}

// cAngles::ToMat3
const cMat3 cAngles::ToMat3() const {
	return cMat3::RotationXYZ(Pitch, Yaw, Roll);
}

// cAngles::ToMat4
const cMat4 cAngles::ToMat4() const {
	return ToMat3().ToMat4();
}

// cAngles::ToVectors
void cAngles::ToVectors(cVec3 *Forward, cVec3 *Right, cVec3 *Up) const {
	ToMat3().ToVectors(Forward, Right, Up);
}

// cAngles::ToForward
const cVec3 cAngles::ToForward() const {
	return ToMat3().ToForward();
}

// cAngles::ToRight
const cVec3 cAngles::ToRight() const {
	return ToMat3().ToRight();
}

// cAngles::ToUp
const cVec3 cAngles::ToUp() const {
	return ToMat3().ToUp();
}

// cAngles::EnsureShortestPath
void cAngles::EnsureShortestPath(cAngles *l, cAngles *r) {
	cAssert(l != NULL);
	cAssert(r != NULL);
	cMath::AngleEnsureShortestPath180(&l->Pitch, &r->Pitch);
	cMath::AngleEnsureShortestPath180(&l->Yaw, &r->Yaw);
	cMath::AngleEnsureShortestPath180(&l->Roll, &r->Roll);
}




::std::ostream& operator<<( ::std::ostream& out, const cAngles& a ) {
    out << "[" << a.Pitch << ", " << a.Yaw << ", " << a.Roll << "]";
    return out;
}


} // comms
