#include "comms-Math.h"

namespace comms {
	
const cMat3 cMat3::Zero(cMat3::ZeroCtor);
const cMat3 cMat3::Identity(cMat3::IdentityCtor);

// cMat3::Determinant
float cMat3::Determinant() const {
	float d2_12_01 = m_Rows[1][0] * m_Rows[2][1] - m_Rows[1][1] * m_Rows[2][0];
	float d2_12_02 = m_Rows[1][0] * m_Rows[2][2] - m_Rows[1][2] * m_Rows[2][0];
	float d2_12_12 = m_Rows[1][1] * m_Rows[2][2] - m_Rows[1][2] * m_Rows[2][1];
	
	return m_Rows[0][0] * d2_12_12 - m_Rows[0][1] * d2_12_02 + m_Rows[0][2] * d2_12_01;
}

// cMat3::RotationX
const cMat3 cMat3::RotationX(const float Angle) {
	cAssert(cMath::IsValid(Angle));

	float Sin, Cos;
	cMath::SinCos(cMath::Rad(Angle), Sin, Cos);
	
	cMat3 Rx;
	Rx.SetRow0(1.0f, 0.0f, 0.0f);
	Rx.SetRow1(0.0f, Cos, Sin);
	Rx.SetRow2(0.0f, -Sin, Cos);

	cAssert(Rx.IsOrthonormal());

	return Rx;
}

// cMat3::RotationY
const cMat3 cMat3::RotationY(const float Angle) {
	cAssert(cMath::IsValid(Angle));

	float Sin, Cos;
	cMath::SinCos(cMath::Rad(Angle), Sin, Cos);
	
	cMat3 Ry;
	Ry.SetRow0(Cos, 0.0f, -Sin);
	Ry.SetRow1(0.0f, 1.0f, 0.0f);
	Ry.SetRow2(Sin, 0.0f, Cos);

	cAssert(Ry.IsOrthonormal());

	return Ry;
}

// cMat3::RotationZ
const cMat3 cMat3::RotationZ(const float Angle) {
	cAssert(cMath::IsValid(Angle));

	float Sin, Cos;
	cMath::SinCos(cMath::Rad(Angle), Sin, Cos);
	
	cMat3 Rz;
	Rz.SetRow0(Cos, Sin, 0.0f);
	Rz.SetRow1(-Sin, Cos, 0.0f);
	Rz.SetRow2(0.0f, 0.0f, 1.0f);

	cAssert(Rz.IsOrthonormal());

	return Rz;
}

// cMat3::RotationXYZ
const cMat3 cMat3::RotationXYZ(const float Pitch, const float Yaw, const float Roll) {
	return cMat3::RotationX(Pitch) * cMat3::RotationY(Yaw) * cMat3::RotationZ(Roll);
}

// cMat3::EulerZYX
const cMat3 cMat3::EulerZYX(const float eulerX, const float eulerY, const float eulerZ) { 

	float si, ci, sj, cj, sh, ch;
	cMath::SinCos(cMath::Rad(eulerX), si, ci);
	cMath::SinCos(cMath::Rad(eulerY), sj, cj);
	cMath::SinCos(cMath::Rad(eulerZ), sh, ch);

	float cc = ci * ch; 
	float cs = ci * sh; 
	float sc = si * ch; 
	float ss = si * sh;

	return cMat3(cj * ch, sj * sc - cs, sj * cc + ss,
				cj * sh, sj * ss + cc, sj * cs - sc, 
				-sj,      cj * si,      cj * ci);

}



//-----------------------------------------------------------------------------
// cMat3::Rotation
//-----------------------------------------------------------------------------
const cMat3 cMat3::Rotation(const cVec3 &Axis, const float Angle) {
	const float HalfAngle = cMath::Rad(Angle) * 0.5f;

	float Sin, Cos;
	cMath::SinCos(HalfAngle, Sin, Cos);
	
	const float qx = Sin * Axis.x;
	const float qy = Sin * Axis.y;
	const float qz = Sin * Axis.z;
	
	cMat3 R;
	R(0, 0) = 1.0f - 2.0f * (qy * qy + qz * qz);
	R(1, 1) = 1.0f - 2.0f * (qx * qx + qz * qz);
	R(2, 2) = 1.0f - 2.0f * (qx * qx + qy * qy);

	R(1, 0) = 2.0f * (qx * qy - Cos * qz);
	R(2, 0) = 2.0f * (qx * qz + Cos * qy);
	
	R(0, 1) = 2.0f * (qx * qy + Cos * qz);
	R(2, 1) = 2.0f * (qy * qz - Cos * qx);
	
	R(0, 2) = 2.0f * (qx * qz - Cos * qy);
	R(1, 2) = 2.0f * (qy * qz + Cos * qx);
	return R;
} // cMat3::Rotation

// cMat3::Scaling : const cMat3 (const float)
const cMat3 cMat3::Scaling(const float XYZ) {
	cMat3 S(cMat3::IdentityCtor);
	S(0, 0) = S(1, 1) = S(2, 2) = XYZ;
	return S;
}

// cMat3::Scaling : const cMat3 (const float, const float)
const cMat3 cMat3::Scaling(const float X, const float Y) {
	cMat3 S(cMat3::IdentityCtor);
	S(0, 0) = X;
	S(1, 1) = Y;
	return S;
}

// cMat3::Scaling : const cMat3 (const float, const float, const float)
const cMat3 cMat3::Scaling(const float X, const float Y, const float Z) {
	cMat3 S(cMat3::IdentityCtor);
	S(0, 0) = X;
	S(1, 1) = Y;
	S(2, 2) = Z;
	return S;
}

// cMat3::Scaling : const cMat3 (const cVec2 &)
const cMat3 cMat3::Scaling(const cVec2 &XY) {
	cMat3 S(cMat3::IdentityCtor);
	S(0, 0) = XY[0];
	S(1, 1) = XY[1];
	return S;
}

// cMat3::Scaling : const cMat3 (const cVec3 &)
const cMat3 cMat3::Scaling(const cVec3 &XYZ) {
	cMat3 S(cMat3::IdentityCtor);
	S(0, 0) = XYZ[0];
	S(1, 1) = XYZ[1];
	S(2, 2) = XYZ[2];
	return S;
}

//-----------------------------------------------------------------------------
// cMat3::ToVectors
//-----------------------------------------------------------------------------
void cMat3::ToVectors(cVec3 *Forward, cVec3 *Right, cVec3 *Up) const {
	if(Forward != NULL) {
		*Forward = -GetRow2(); // Negative Z - Axis
	}
	if(Right != NULL) {
		*Right = GetRow0(); // X - Axis
	}
	if(Up != NULL) {
		*Up = GetRow1(); // Y - Axis
	}
} // cMat3::ToVectors

// cMat3::FromVectors
const cMat3 cMat3::FromVectors(const cVec3 &Forward, const cVec3 &Right, const cVec3 &Up) {
	cMat3 R;
	R.SetRow2(-Forward);
	R.SetRow0(Right);
	R.SetRow1(Up);
	return R;
}

// cMat3::ToForward
const cVec3 cMat3::ToForward() const {
	return -GetRow2(); // Negative Z - Axis
}

// cMat3::ToRight
const cVec3 cMat3::ToRight() const {
	return GetRow0(); // X - Axis
}

// cMat3::ToUp
const cVec3 cMat3::ToUp() const {
	return GetRow1(); // Y - Axis
}

//-----------------------------------------------------------------------------
// cMat3::ToQuat
//-----------------------------------------------------------------------------
const cQuat cMat3::ToQuat() const {
	cMat3 R = *this;
	R.OrthoNormalize();

	cQuat q;

	const float Trace = R[0][0] + R[1][1] + R[2][2];
	if(Trace > 0.0f) {
		const float t = Trace + 1.0f;
		const float s = 1.0f / cMath::Sqrt(t) * 0.5f;

		q[3] = s * t;
		q[0] = (R[1][2] - R[2][1]) * s;
		q[1] = (R[2][0] - R[0][2]) * s;
		q[2] = (R[0][1] - R[1][0]) * s;
	} else {
		int i = 0;
		if(R[1][1] > R[0][0]) {
			i = 1;
		}
		if(R[2][2] > R[i][i]) {
			i = 2;
		}
		
		const int Next[3] = { 1, 2, 0 };
		int j = Next[i];
		int k = Next[j];

		const float t = (R[i][i] - (R[j][j] + R[k][k])) + 1.0f;
		const float s = 1.0f / cMath::Sqrt(t) * 0.5f;

		q[i] = s * t;
		q[3] = (R[j][k] - R[k][j]) * s;
		q[j] = (R[i][j] + R[j][i]) * s;
		q[k] = (R[i][k] + R[k][i]) * s;
	}
	return q;
} // cMat3::ToQuat

//--------------------------------------------------------------------------------------
// cMat3::Invert : bool (const cMat3 &, cMat3 *)
//--------------------------------------------------------------------------------------
bool cMat3::Invert(const cMat3 &Fm, cMat3 *To) {
	const float d2_12_01 = Fm[1][0] * Fm[2][1] - Fm[1][1] * Fm[2][0];
	const float d2_12_02 = Fm[1][0] * Fm[2][2] - Fm[1][2] * Fm[2][0];
	const float d2_12_12 = Fm[1][1] * Fm[2][2] - Fm[1][2] * Fm[2][1];
	
	const float Det =  Fm[0][0] * d2_12_12 - Fm[0][1] * d2_12_02 + Fm[0][2] * d2_12_01;

	if(cMath::IsZero(Det, cMath::MatrixInvertEpsilon)) {
		return false;
	}

	const float iDet = 1.0f / Det;

	const float d2_01_01 = Fm[0][0] * Fm[1][1] - Fm[0][1] * Fm[1][0];
	const float d2_01_02 = Fm[0][0] * Fm[1][2] - Fm[0][2] * Fm[1][0];
	const float d2_01_12 = Fm[0][1] * Fm[1][2] - Fm[0][2] * Fm[1][1];

	const float d2_02_01 = Fm[0][0] * Fm[2][1] - Fm[0][1] * Fm[2][0];
	const float d2_02_02 = Fm[0][0] * Fm[2][2] - Fm[0][2] * Fm[2][0];
	const float d2_02_12 = Fm[0][1] * Fm[2][2] - Fm[0][2] * Fm[2][1];


	To->Elem(0, 0) = + d2_12_12 * iDet;
	To->Elem(1, 0) = - d2_12_02 * iDet;
	To->Elem(2, 0) = + d2_12_01 * iDet;

	To->Elem(0, 1) = - d2_02_12 * iDet;
	To->Elem(1, 1) = + d2_02_02 * iDet;
	To->Elem(2, 1) = - d2_02_01 * iDet;

	To->Elem(0, 2) = + d2_01_12 * iDet;
	To->Elem(1, 2) = - d2_01_02 * iDet;
	To->Elem(2, 2) = + d2_01_01 * iDet;
	
	return true;
} // cMat3::Invert

//-----------------------------------------------------------------------------
// cMat3::ToAngles
//-----------------------------------------------------------------------------
const cAngles cMat3::ToAngles() const {
	//                                                       ( CY*CR           CY*SR           -SY   )
	// RotationX(Pitch) * RotationY(Yaw) * RotationZ(Roll) = ( SP*SY*CR-CP*SR  SP*SY*SR+CP*CR  SP*CY )
	//                                                       ( CP*SY*CR+SP*SR  CP*SY*SR-SP*CR  CP*CY )

	cAngles Angles;
	Angles.Yaw = cMath::Deg(cMath::ASin(-m_Rows[0][2]));
	if(Angles.Yaw < 90.0f) {
		if(Angles.Yaw > -90.0f) {
			Angles.Pitch = cMath::Deg(cMath::ATan(m_Rows[1][2], m_Rows[2][2]));
			Angles.Roll = cMath::Deg(cMath::ATan(m_Rows[0][1], m_Rows[0][0]));
		} else { // Yaw == -90.0f
			Angles.Roll = 0.0f;
			Angles.Pitch = cMath::Deg(cMath::ATan(-m_Rows[1][0], m_Rows[1][1]));
		}
	} else { // Yaw == 90.0f
		Angles.Roll = 0.0f;
		Angles.Pitch = cMath::Deg(cMath::ATan(m_Rows[1][0], m_Rows[1][1]));
	}

	return Angles;
} // cMat3::ToAngles




::std::ostream& operator<<( ::std::ostream& out, const cMat3& m ) {
    out << "[" << m( 0, 0 ) << "," << m( 0, 1 ) << "," << m( 0, 2 ) <<
          ", " << m( 1, 0 ) << "," << m( 1, 1 ) << "," << m( 1, 2 ) <<
          ", " << m( 2, 0 ) << "," << m( 2, 1 ) << "," << m( 2, 2 ) << "]";
    return out;
}


} // comms
