#include "comms-Math.h"

namespace comms {

const cQuat cQuat::Identity(0.0f, 0.0f, 0.0f, 1.0f);
const cQuat cQuat::Zero(0.0f, 0.0f, 0.0f, 0.0f);

//-----------------------------------------------------------------------------
// cQuat::ToAngles : const cAngles () const
//-----------------------------------------------------------------------------
const cAngles cQuat::ToAngles() const {
	return ToMat3().ToAngles();
}

//-----------------------------------------------------------------------------
// cQuat::ToRotation : const cRotation () const
//-----------------------------------------------------------------------------
const cRotation cQuat::ToRotation() const {
	cVec3 Axis(x, y, z);
	float Angle = cMath::ACos(w);

	if(Angle == 0.0f) {
		Axis = cVec3::AxisZ;
	} else {
		Axis.Normalize();
		Axis.FixDegenerateNormal();
		Angle *= 2.0f * cMath::DegsPerRad;
	}
	return cRotation(cVec3::Zero, Axis, Angle);
}

//-----------------------------------------------------------------------------
// cQuat::ToMat3() : const cMat3 () const
//-----------------------------------------------------------------------------
const cMat3 cQuat::ToMat3() const {
	cMat3 R;

	float ww = w * w;
	float xx = x * x;
	float yy = y * y;
	float zz = z * z;

	float s = 2.0f / (ww + xx + yy + zz);

	float xy = x * y;
	float xz = x * z;
	float yz = y * z;
	float wx = w * x;
	float wy = w * y;
	float wz = w * z;

	R(0, 0) = 1.0f - s * (yy + zz);
	R(1, 0) = s * (xy - wz);
	R(2, 0) = s * (xz + wy);

	R(0, 1) = s * (xy + wz);
	R(1, 1) = 1.0f - s * (xx + zz);
	R(2, 1) = s * (yz - wx);

	R(0, 2) = s * (xz - wy);
	R(1, 2) = s * (yz + wx);
	R(2, 2) = 1.0f - s * (xx + yy);
	
	return R;
} // cQuat::ToMat3

//-----------------------------------------------------------------------------
// cQuat::ToMat4 : const cMat4 () const
//-----------------------------------------------------------------------------
const cMat4 cQuat::ToMat4() const {
	return ToMat3().ToMat4();
}

//-----------------------------------------------------------------------------
// cQuat::ToAngularVelocity : const cVec3 () const
//-----------------------------------------------------------------------------
const cVec3 cQuat::ToAngularVelocity() const {
	return cVec3::Normalize(cVec3(x, y, z)) * cMath::ACos(w);
}

//-----------------------------------------------------------------------------
// cQuat::ToStr : const cStr (const int) const
//-----------------------------------------------------------------------------
const cStr cQuat::ToStr(const int nPrec) const {
	return cStr::ToString(ToFloatPtr(), GetDimension(), nPrec);
}

//-------------------------------------------------------------------------------------------------
// cQuat::Lerp : const cQuat (const cQuat &, const cQuat &, const float, const bool)
//-------------------------------------------------------------------------------------------------
const cQuat cQuat::Lerp(const cQuat &q0, const cQuat &q1, const float s, const bool ShortestPath) {
	float Cos = Dot(q0, q1);

	cQuat p1;
	if(Cos < 0.0f && ShortestPath) {
		p1 = -q1;
	} else {
		p1 = q1;
	}
	return Normalize(q0 + s * (p1 - q0));
}

//--------------------------------------------------------------------------------------------------
// cQuat::Slerp : const cQuat (const cQuat &, const cQuat &, const float, const bool)
//--------------------------------------------------------------------------------------------------
const cQuat cQuat::Slerp(const cQuat &q0, const cQuat &q1, const float s, const bool ShortestPath) {
	float Cos = Dot(q0, q1);
	cQuat t;
	if(Cos < 0.0f) {
		t = -q1;
		Cos = -Cos;
	} else {
		t = q1;
	}
	float Scale0, Scale1;
        if(1.0f - Cos > 1e-6f) {
                float Angle = cMath::ACos(Cos);
		float iSin = 1.0f / cMath::Sin(Angle);
		Scale0 = cMath::Sin((1.0f - s) * Angle) * iSin;
		Scale1 = cMath::Sin(s * Angle) * iSin;
	} else {
		Scale0 = 1.0f - s;
		Scale1 = s;
	}
	return Scale0 * q0 + Scale1 * t;
}

//------------------------------------------------------------------------------------------------------------------------
// cQuat::SquadSetup : void (const cQuat &, const cQuat &, const cQuat &, const cQuat &, cQuat &, cQuat &, cQuat &)
//------------------------------------------------------------------------------------------------------------------------
void cQuat::SquadSetup(const cQuat &q0, const cQuat &q1, const cQuat &q2, const cQuat &q3, cQuat &A, cQuat &B, cQuat &C) {
	cQuat p0 = Dot(q0, q1) >= 0.0f ? q0 : -q0;
	cQuat p2 = Dot(q1, q2) >= 0.0f ? q2 : -q2;
	cQuat p3 = Dot(p2, q3) >= 0.0f ? q3 : -q3;

	A = q1 * Exp(-0.25f * (LnDif(q1, p2) + LnDif(q1, p0)));
	B = p2 * Exp(-0.25f * (LnDif(p2, p3) + LnDif(p2, q1)));
	C = p2;
}

//--------------------------------------------------------------------------------------------------------
// cQuat::Squad : const cQuat (const cQuat &, const cQuat &, const cQuat &, const cQuat &, const float)
//--------------------------------------------------------------------------------------------------------
const cQuat cQuat::Squad(const cQuat &q1, const cQuat &A, const cQuat &B, const cQuat &C, const float s) {
	return Slerp(Slerp(q1, C, s), Slerp(A, B, s), 2.0f * s * (1.0f - s));
}

//-----------------------------------------------------------------------------
// cQuat::Exp : const cQuat (const cQuat &)
//-----------------------------------------------------------------------------
const cQuat cQuat::Exp(const cQuat &q) {
	const float Angle = cMath::Sqrt(q.x * q.x + q.y * q.y + q.z * q.z);
	float Cos = cMath::Cos(Angle);
	
	if(Angle == 0.0f) {
		return cQuat(0.0f, 0.0f, 0.0f, Cos);
	} else {
		float s = cMath::Sin(Angle) / Angle;
		return cQuat(s * q.x, s * q.y, s * q.z, Cos);
	}
}

//-----------------------------------------------------------------------------
// cQuat::Ln : const cQuat (const cQuat &)
//-----------------------------------------------------------------------------
const cQuat cQuat::Ln(const cQuat &q) {
	const float lPure = cMath::Sqrt(q.x * q.x + q.y * q.y + q.z * q.z);
	if ( cMath::IsZero( lPure ) ) {
		return cQuat::Zero;
	} else {
		float s = cMath::ATan(lPure, q.w) / lPure;
		return cQuat(s * q.x, s * q.y, s * q.z, 0.0f);
	}
}

//-----------------------------------------------------------------------------
// cQuat::LnDif : const cQuat(const cQuat &, const cQuat &)
//-----------------------------------------------------------------------------
const cQuat cQuat::LnDif (const cQuat &q0, const cQuat &q1) {
	cQuat Dif = Invert(q0) * q1;
	cAssert(Dif.IsNormalized());
	return Ln(Dif);
}




::std::ostream& operator<<( ::std::ostream& out, const cQuat& q ) {
    out << "[" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << "]";
    return out;
}


} // comms
