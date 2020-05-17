#include "comms-Math.h"

namespace comms {
	
const dMat3 dMat3::Zero(dMat3::ZeroCtor);
const dMat3 dMat3::Identity(dMat3::IdentityCtor);
dMat3::dMat3(const cMat3& m){
	for (int i = 0; i < 4; i++){
		m_Rows[i] = dVec3(m.GetRow(i));
	}
}

// dMat3::Determinant
double dMat3::Determinant() const {
	double d2_12_01 = m_Rows[1][0] * m_Rows[2][1] - m_Rows[1][1] * m_Rows[2][0];
	double d2_12_02 = m_Rows[1][0] * m_Rows[2][2] - m_Rows[1][2] * m_Rows[2][0];
	double d2_12_12 = m_Rows[1][1] * m_Rows[2][2] - m_Rows[1][2] * m_Rows[2][1];
	
	return m_Rows[0][0] * d2_12_12 - m_Rows[0][1] * d2_12_02 + m_Rows[0][2] * d2_12_01;
}

// dMat3::RotationX
const dMat3 dMat3::RotationX(const double Angle) {
	cAssert(cMath::IsValid(Angle));

	double Sin, Cos;
	cMath::SinCos(cMath::Rad(Angle), Sin, Cos);
	
	dMat3 Rx;
	Rx.SetRow0(1.0, 0.0, 0.0);
	Rx.SetRow1(0.0, Cos, Sin);
	Rx.SetRow2(0.0, -Sin, Cos);

	cAssert(Rx.IsOrthonormal());

	return Rx;
}

// dMat3::RotationY
const dMat3 dMat3::RotationY(const double Angle) {
	cAssert(cMath::IsValid(Angle));

	double Sin, Cos;
	cMath::SinCos(cMath::Rad(Angle), Sin, Cos);
	
	dMat3 Ry;
	Ry.SetRow0(Cos, 0.0, -Sin);
	Ry.SetRow1(0.0, 1.0, 0.0);
	Ry.SetRow2(Sin, 0.0, Cos);

	cAssert(Ry.IsOrthonormal());

	return Ry;
}

// dMat3::RotationZ
const dMat3 dMat3::RotationZ(const double Angle) {
	cAssert(cMath::IsValid(Angle));

	double Sin, Cos;
	cMath::SinCos(cMath::Rad(Angle), Sin, Cos);
	
	dMat3 Rz;
	Rz.SetRow0(Cos, Sin, 0.0);
	Rz.SetRow1(-Sin, Cos, 0.0);
	Rz.SetRow2(0.0, 0.0, 1.0);

	cAssert(Rz.IsOrthonormal());

	return Rz;
}

// dMat3::RotationXYZ
const dMat3 dMat3::RotationXYZ(const double Pitch, const double Yaw, const double Roll) {
	return dMat3::RotationX(Pitch) * dMat3::RotationY(Yaw) * dMat3::RotationZ(Roll);
}

// dMat3::EulerZYX
const dMat3 dMat3::EulerZYX(const double eulerX, const double eulerY, const double eulerZ) { 

	double si, ci, sj, cj, sh, ch;
	cMath::SinCos(cMath::Rad(eulerX), si, ci);
	cMath::SinCos(cMath::Rad(eulerY), sj, cj);
	cMath::SinCos(cMath::Rad(eulerZ), sh, ch);

	double cc = ci * ch; 
	double cs = ci * sh; 
	double sc = si * ch; 
	double ss = si * sh;

	return dMat3(cj * ch, sj * sc - cs, sj * cc + ss,
				cj * sh, sj * ss + cc, sj * cs - sc, 
				-sj,      cj * si,      cj * ci);

}



//-----------------------------------------------------------------------------
// dMat3::Rotation
//-----------------------------------------------------------------------------
const dMat3 dMat3::Rotation(const dVec3 &Axis, const double Angle) {
	const double HalfAngle = cMath::Rad(Angle) * 0.5f;

	double Sin, Cos;
	cMath::SinCos(HalfAngle, Sin, Cos);
	
	const double qx = Sin * Axis.x;
	const double qy = Sin * Axis.y;
	const double qz = Sin * Axis.z;
	
	dMat3 R;
	R(0, 0) = 1.0 - 2.0 * (qy * qy + qz * qz);
	R(1, 1) = 1.0 - 2.0 * (qx * qx + qz * qz);
	R(2, 2) = 1.0 - 2.0 * (qx * qx + qy * qy);

	R(1, 0) = 2.0 * (qx * qy - Cos * qz);
	R(2, 0) = 2.0 * (qx * qz + Cos * qy);
	
	R(0, 1) = 2.0 * (qx * qy + Cos * qz);
	R(2, 1) = 2.0 * (qy * qz - Cos * qx);
	
	R(0, 2) = 2.0 * (qx * qz - Cos * qy);
	R(1, 2) = 2.0 * (qy * qz + Cos * qx);
	return R;
} // dMat3::Rotation

// dMat3::Scaling : const dMat3 (const double)
const dMat3 dMat3::Scaling(const double XYZ) {
	dMat3 S(dMat3::IdentityCtor);
	S(0, 0) = S(1, 1) = S(2, 2) = XYZ;
	return S;
}

// dMat3::Scaling : const dMat3 (const double, const double)
const dMat3 dMat3::Scaling(const double X, const double Y) {
	dMat3 S(dMat3::IdentityCtor);
	S(0, 0) = X;
	S(1, 1) = Y;
	return S;
}

// dMat3::Scaling : const dMat3 (const double, const double, const double)
const dMat3 dMat3::Scaling(const double X, const double Y, const double Z) {
	dMat3 S(dMat3::IdentityCtor);
	S(0, 0) = X;
	S(1, 1) = Y;
	S(2, 2) = Z;
	return S;
}

// dMat3::Scaling : const dMat3 (const dVec2 &)
const dMat3 dMat3::Scaling(const dVec2 &XY) {
	dMat3 S(dMat3::IdentityCtor);
	S(0, 0) = XY[0];
	S(1, 1) = XY[1];
	return S;
}

// dMat3::Scaling : const dMat3 (const dVec3 &)
const dMat3 dMat3::Scaling(const dVec3 &XYZ) {
	dMat3 S(dMat3::IdentityCtor);
	S(0, 0) = XYZ[0];
	S(1, 1) = XYZ[1];
	S(2, 2) = XYZ[2];
	return S;
}

//-----------------------------------------------------------------------------
// dMat3::ToVectors
//-----------------------------------------------------------------------------
void dMat3::ToVectors(dVec3 *Forward, dVec3 *Right, dVec3 *Up) const {
	if(Forward != NULL) {
		*Forward = -GetRow2(); // Negative Z - Axis
	}
	if(Right != NULL) {
		*Right = GetRow0(); // X - Axis
	}
	if(Up != NULL) {
		*Up = GetRow1(); // Y - Axis
	}
} // dMat3::ToVectors

// dMat3::FromVectors
const dMat3 dMat3::FromVectors(const dVec3 &Forward, const dVec3 &Right, const dVec3 &Up) {
	dMat3 R;
	R.SetRow2(-Forward);
	R.SetRow0(Right);
	R.SetRow1(Up);
	return R;
}

// dMat3::ToForward
const dVec3 dMat3::ToForward() const {
	return -GetRow2(); // Negative Z - Axis
}

// dMat3::ToRight
const dVec3 dMat3::ToRight() const {
	return GetRow0(); // X - Axis
}

// dMat3::ToUp
const dVec3 dMat3::ToUp() const {
	return GetRow1(); // Y - Axis
}

//--------------------------------------------------------------------------------------
// dMat3::Invert : bool (const dMat3 &, dMat3 *)
//--------------------------------------------------------------------------------------
bool dMat3::Invert(const dMat3 &Fm, dMat3 *To) {
	const double d2_12_01 = Fm[1][0] * Fm[2][1] - Fm[1][1] * Fm[2][0];
	const double d2_12_02 = Fm[1][0] * Fm[2][2] - Fm[1][2] * Fm[2][0];
	const double d2_12_12 = Fm[1][1] * Fm[2][2] - Fm[1][2] * Fm[2][1];
	
	const double Det =  Fm[0][0] * d2_12_12 - Fm[0][1] * d2_12_02 + Fm[0][2] * d2_12_01;

	if(cMath::IsZero(Det, cMath::dMatrixInvertEpsilon)) {
		return false;
	}

	const double iDet = 1.0 / Det;

	const double d2_01_01 = Fm[0][0] * Fm[1][1] - Fm[0][1] * Fm[1][0];
	const double d2_01_02 = Fm[0][0] * Fm[1][2] - Fm[0][2] * Fm[1][0];
	const double d2_01_12 = Fm[0][1] * Fm[1][2] - Fm[0][2] * Fm[1][1];

	const double d2_02_01 = Fm[0][0] * Fm[2][1] - Fm[0][1] * Fm[2][0];
	const double d2_02_02 = Fm[0][0] * Fm[2][2] - Fm[0][2] * Fm[2][0];
	const double d2_02_12 = Fm[0][1] * Fm[2][2] - Fm[0][2] * Fm[2][1];


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
} // dMat3::Invert

//-----------------------------------------------------------------------------
// dMat3::ToAngles
//-----------------------------------------------------------------------------
const cAngles dMat3::ToAngles() const {
	//                                                       ( CY*CR           CY*SR           -SY   )
	// RotationX(Pitch) * RotationY(Yaw) * RotationZ(Roll) = ( SP*SY*CR-CP*SR  SP*SY*SR+CP*CR  SP*CY )
	//                                                       ( CP*SY*CR+SP*SR  CP*SY*SR-SP*CR  CP*CY )

	cAngles Angles;
	Angles.Yaw = float(cMath::Deg(cMath::ASin(-m_Rows[0][2])));
	if(Angles.Yaw < 90.0) {
		if(Angles.Yaw > -90.0) {
			Angles.Pitch = float(cMath::Deg(cMath::ATan(m_Rows[1][2], m_Rows[2][2])));
			Angles.Roll = float(cMath::Deg(cMath::ATan(m_Rows[0][1], m_Rows[0][0])));
		} else { // Yaw == -90.0
			Angles.Roll = 0.0;
			Angles.Pitch = float(cMath::Deg(cMath::ATan(-m_Rows[1][0], m_Rows[1][1])));
		}
	} else { // Yaw == 90.0
		Angles.Roll = 0.0;
		Angles.Pitch = float(cMath::Deg(cMath::ATan(m_Rows[1][0], m_Rows[1][1])));
	}

	return Angles;
} // dMat3::ToAngles




::std::ostream& operator<<( ::std::ostream& out, const dMat3& m ) {
    out << "[" << m( 0, 0 ) << "," << m( 0, 1 ) << "," << m( 0, 2 ) <<
          ", " << m( 1, 0 ) << "," << m( 1, 1 ) << "," << m( 1, 2 ) <<
          ", " << m( 2, 0 ) << "," << m( 2, 1 ) << "," << m( 2, 2 ) << "]";
    return out;
}


} // comms
