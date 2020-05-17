#include "comms-Math.h"

namespace comms {

dMat4::dMat4(const cMat4& m){
	for (int i = 0; i < 4; i++){
		m_Rows[i] = dVec4(m.GetRow(i));
	}
}

const dMat4 dMat4::Zero(dMat4::ZeroCtor);
const dMat4 dMat4::Identity(dMat4::IdentityCtor);

// dMat4::ToString
const cStr dMat4::ToString(const int Prec) const {
	return cStr::ToString(ToFloatPtr(), 16, Prec);
}

// dMat4::ToNormalMatrix
const dMat3 dMat4::ToNormalMatrix() const {
	dMat3 N = ToMat3();
	if(!dMat3::Invert(N, &N)) {
		N.SetIdentity();
	} else {
		N.Transpose();
	}
	return N;
}

// dMat4::SetRotation
void dMat4::SetRotation( const cAngles& r ) {
    const dMat3  ro = r.ToMat3();
    const dVec3  tr = GetTranslation();
    *this = dMat4( ro, tr );
}

// dMat4::GetRotation
cAngles dMat4::GetRotation() const {
    return ToMat3().ToAngles();
}

//-------------------------------------------------------------------------------------
// dMat4::Perspective
//-------------------------------------------------------------------------------------
const dMat4 dMat4::Perspective(double YFov, double AspectWtoH, double Znear, double Zfar) {
	dMat4 P(dMat4::ZeroCtor);

	const double h = cMath::Tan(0.5f * cMath::Rad(YFov));
	const double w = h * AspectWtoH;
	
	P(0, 0) = 1.0 / w;
	P(1, 1) = 1.0 / h;
	P(2, 2) = (Zfar + Znear) / (Znear - Zfar);
	P(2, 3) = -1.0;
	P(3, 2) = 2.0 * Znear * Zfar / (Znear - Zfar);
	
	return P;
} // dMat4::Perspective

//----------------------------------------------------------------------------------------------
// dMat4::PerspectiveInf
//----------------------------------------------------------------------------------------------
const dMat4 dMat4::PerspectiveInf(const double YFov, const double AspectWtoH, const double Znear) {
	dMat4 P(dMat4::ZeroCtor);

	const double h = cMath::Tan(0.5f * cMath::Rad(YFov));
	const double w = h * AspectWtoH;
	
	P(0, 0) = 1.0 / w;
	P(1, 1) = 1.0 / h;
	P(2, 2) = cMath::Epsilon - 1.0;
	P(2, 3) = -1.0;
	P(3, 2) = Znear * (cMath::Epsilon - 2.0);
	
	return P;
} // dMat4::PerspectiveInf

// dMat4::Translation : const dMat4 (const double, const double)
const dMat4 dMat4::Translation(const double X, const double Y) {
	dMat4 T(dMat4::IdentityCtor);
	T.SetRow3(X, Y, 0.0, 1.0);
	return T;
}

// dMat4::Translation : const dMat4 (const double, const double, const double)
const dMat4 dMat4::Translation(const double X, const double Y, const double Z) {
	dMat4 T(dMat4::IdentityCtor);
	T.SetRow3(X, Y, Z, 1.0);
	return T;
}

// dMat4::Translation : const dMat4 (const dVec2 &)
const dMat4 dMat4::Translation(const dVec2 &XY) {
	dMat4 T(dMat4::IdentityCtor);
	T.SetRow3(XY[0], XY[1], 0.0, 1.0);
	return T;
}

// dMat4::Translation : const dMat4 (const dVec3 &)
const dMat4 dMat4::Translation(const dVec3 &XYZ) {
	dMat4 T(dMat4::IdentityCtor);
	T.SetRow3(XYZ[0], XYZ[1], XYZ[2], 1.0);
	return T;
}

// dMat4::Rotation
const dMat4 dMat4::Rotation(const dVec3 &Axis, const double Angle) {
	return dMat3::Rotation(Axis, Angle).ToMat4();
}

// dMat4::RotationX
const dMat4 dMat4::RotationX(const double Angle) {
	return dMat3::RotationX(Angle).ToMat4();
}

// dMat4::RotationY
const dMat4 dMat4::RotationY(const double Angle) {
	return dMat3::RotationY(Angle).ToMat4();
}

// dMat4::RotationZ
const dMat4 dMat4::RotationZ(const double Angle) {
	return dMat3::RotationZ(Angle).ToMat4();
}

// dMat4::RotationXYZ
const dMat4 dMat4::RotationXYZ(const double Pitch, const double Yaw, const double Roll) {
	return dMat3::RotationXYZ(Pitch, Yaw, Roll).ToMat4();
}

// dMat4::EulerZYX
const dMat4 dMat4::EulerZYX(const double eulerX, const double eulerY, const double eulerZ) {
	return dMat3::EulerZYX(eulerX, eulerY, eulerZ).ToMat4();
}

// dMat4::RotationAt : const dMat4 (const dVec2 &, const double)
const dMat4 dMat4::RotationAt(const dVec2 &Orig, const double Angle) {
	return RotationAt(dVec3(Orig, 0.0), dVec3::AxisZ, Angle);
}

// dMat4::RotationAt : const dMat4 (const dVec3 &, const dVec3 &, const double)
const dMat4 dMat4::RotationAt(const dVec3 &Orig, const dVec3 &Axis, const double Angle) {
	return Mul(Mul(Translation(-Orig), dMat4::Rotation(Axis, Angle)), Translation(Orig));
}

// dMat4::Scaling : const dMat4 (const double)
const dMat4 dMat4::Scaling(const double XYZ) {
	dMat4 S(dMat4::IdentityCtor);
	S(0, 0) = S(1, 1) = S(2, 2) = XYZ;
	return S;
}

// dMat4::Scaling : const dMat4 (const double, const double)
const dMat4 dMat4::Scaling(const double X, const double Y) {
	dMat4 S(dMat4::IdentityCtor);
	S(0, 0) = X;
	S(1, 1) = Y;
	return S;
}

// dMat4::Scaling : const dMat4 (const double, const double, const double)
const dMat4 dMat4::Scaling(const double X, const double Y, const double Z) {
	dMat4 S(dMat4::IdentityCtor);
	S(0, 0) = X;
	S(1, 1) = Y;
	S(2, 2) = Z;
	return S;
}

// dMat4::Scaling : const dMat4 (const dVec2 &)
const dMat4 dMat4::Scaling(const dVec2 &XY) {
	dMat4 S(dMat4::IdentityCtor);
	S(0, 0) = XY[0];
	S(1, 1) = XY[1];
	return S;
}

// dMat4::Scaling : const dMat4 (const dVec3 &)
const dMat4 dMat4::Scaling(const dVec3 &XYZ) {
	dMat4 S(dMat4::IdentityCtor);
	S(0, 0) = XYZ[0];
	S(1, 1) = XYZ[1];
	S(2, 2) = XYZ[2];
	return S;
}

// dMat4::ScalingAt : const dMat4 (const double, const double, const double)
const dMat4 dMat4::ScalingAt(const double OrigX, const double OrigY, const double ScaleXY) {
	return ScalingAt(dVec3(OrigX, OrigY, 0.0), dVec3(ScaleXY, ScaleXY, 1.0));
}

// dMat4::ScalingAt : const dMat4 (const double, const double, const double, const double)
const dMat4 dMat4::ScalingAt(const double OrigX, const double OrigY, const double ScaleX, const double ScaleY) {
	return ScalingAt(dVec3(OrigX, OrigY, 0.0), dVec3(ScaleX, ScaleY, 1.0));
}

// dMat4::ScalingAt : const dMat4 (const dVec2 &, const double)
const dMat4 dMat4::ScalingAt(const dVec2 &Orig, const double ScaleXY) {
	return ScalingAt(dVec3(Orig, 0.0), dVec3(ScaleXY, ScaleXY, 1.0));
}

// dMat4::ScalingAt : const dMat4 (const dVec2 &, const double, const double)
const dMat4 dMat4::ScalingAt(const dVec2 &Orig, const double ScaleX, const double ScaleY) {
	return ScalingAt(dVec3(Orig, 0.0), dVec3(ScaleX, ScaleY, 1.0));
}

// dMat4::ScalingAt : const dMat4 (const dVec2 &, const dVec2 &)
const dMat4 dMat4::ScalingAt(const dVec2 &Orig, const dVec2 &Scale) {
	return ScalingAt(dVec3(Orig, 0.0), dVec3(Scale, 1.0));
}

// dMat4::ScalingAt : const dMat4 (const dVec3 &, const double)
const dMat4 dMat4::ScalingAt(const dVec3 &Orig, const double ScaleXYZ) {
	return ScalingAt(Orig, dVec3(ScaleXYZ));
}

// dMat4::ScalingAt : const dMat4 (const dVec3 &, const double, const double, const double)
const dMat4 dMat4::ScalingAt(const dVec3 &Orig, const double ScaleX, const double ScaleY, const double ScaleZ) {
	return ScalingAt(Orig, dVec3(ScaleX, ScaleY, ScaleZ));
}

// dMat4::ScalingAt : const dMat4 (const dVec3 &, const dVec3 &)
const dMat4 dMat4::ScalingAt(const dVec3 &Orig, const dVec3 &S) {
	return Mul(Mul(Translation(-Orig), Scaling(S)), Translation(Orig));
}
// dMat4::ScalingAt : const dMat4 ScalingAt(const dVec3 &, const dVec3 &, double);
const dMat4 dMat4::ScalingAt(const dVec3 &Orig, const dVec3 &Dir, double Scale){
	//v1=v+Dir*(v-Orig).dot(Dir)*(Scale-1);
	//x1.x=v.x+(Scale-1.0)*Dir.x*((v.x-Orig.x)*Dir.x+(v.y-Orig.y)*Dir.y+(v.z-Orig.z)*Dir.z)
	//....
	double sc = Scale-1.0;
	dMat4 m = dMat4::Identity;
	double dp = Dir.Dot( Orig );
	
	m(0,0)=1.0+sc*Dir.x*Dir.x;  
	m(1,0)=sc*Dir.x*Dir.y;
	m(2,0)=sc*Dir.x*Dir.z;
	m(3,0)=-sc*Dir.x*dp;

	m(0,1)=sc*Dir.y*Dir.x;  
	m(1,1)=1.0+sc*Dir.y*Dir.y;
	m(2,1)=sc*Dir.y*Dir.z;
	m(3,1)=-sc*Dir.y*dp;

	m(0,2)=sc*Dir.z*Dir.x;  
	m(1,2)=sc*Dir.z*Dir.y;
	m(2,2)=1.0+sc*Dir.z*Dir.z;
	m(3,2)=-sc*Dir.z*dp;

	return m;
}

//-----------------------------------------------------------------------------
// dMat4::Determinant
//-----------------------------------------------------------------------------
double dMat4::Determinant() const {
	double d2_01_01 = m_Rows[0][0] * m_Rows[1][1] - m_Rows[0][1] * m_Rows[1][0];
	double d2_01_02 = m_Rows[0][0] * m_Rows[1][2] - m_Rows[0][2] * m_Rows[1][0];
	double d2_01_03 = m_Rows[0][0] * m_Rows[1][3] - m_Rows[0][3] * m_Rows[1][0];
	double d2_01_12 = m_Rows[0][1] * m_Rows[1][2] - m_Rows[0][2] * m_Rows[1][1];
	double d2_01_13 = m_Rows[0][1] * m_Rows[1][3] - m_Rows[0][3] * m_Rows[1][1];
	double d2_01_23 = m_Rows[0][2] * m_Rows[1][3] - m_Rows[0][3] * m_Rows[1][2];
	
	double d3_012_012 = m_Rows[2][0] * d2_01_12 - m_Rows[2][1] * d2_01_02 + m_Rows[2][2] * d2_01_01;
	double d3_012_013 = m_Rows[2][0] * d2_01_13 - m_Rows[2][1] * d2_01_03 + m_Rows[2][3] * d2_01_01;
	double d3_012_023 = m_Rows[2][0] * d2_01_23 - m_Rows[2][2] * d2_01_03 + m_Rows[2][3] * d2_01_02;
	double d3_012_123 = m_Rows[2][1] * d2_01_23 - m_Rows[2][2] * d2_01_13 + m_Rows[2][3] * d2_01_12;
	
	const double Det = -m_Rows[3][0] * d3_012_123 + m_Rows[3][1] * d3_012_023 - m_Rows[3][2] * d3_012_013 + m_Rows[3][3] * d3_012_012;
	return (double)Det;
} // dMat4::Determinant

//-----------------------------------------------------------------------------
// dMat4::Invert : bool (const dMat4, dMat4 *)
//-----------------------------------------------------------------------------
bool dMat4::Invert(const dMat4 &Fm, dMat4 *To) {
	const double d2_01_01 = Fm[0][0] * Fm[1][1] - Fm[0][1] * Fm[1][0];
	const double d2_01_02 = Fm[0][0] * Fm[1][2] - Fm[0][2] * Fm[1][0];
	const double d2_01_03 = Fm[0][0] * Fm[1][3] - Fm[0][3] * Fm[1][0];
	const double d2_01_12 = Fm[0][1] * Fm[1][2] - Fm[0][2] * Fm[1][1];
	const double d2_01_13 = Fm[0][1] * Fm[1][3] - Fm[0][3] * Fm[1][1];
	const double d2_01_23 = Fm[0][2] * Fm[1][3] - Fm[0][3] * Fm[1][2];
	
	const double d3_012_012 = Fm[2][0] * d2_01_12 - Fm[2][1] * d2_01_02 + Fm[2][2] * d2_01_01;
	const double d3_012_013 = Fm[2][0] * d2_01_13 - Fm[2][1] * d2_01_03 + Fm[2][3] * d2_01_01;
	const double d3_012_023 = Fm[2][0] * d2_01_23 - Fm[2][2] * d2_01_03 + Fm[2][3] * d2_01_02;
	const double d3_012_123 = Fm[2][1] * d2_01_23 - Fm[2][2] * d2_01_13 + Fm[2][3] * d2_01_12;
	
	const double Det = -Fm[3][0] * d3_012_123 + Fm[3][1] * d3_012_023 - Fm[3][2] * d3_012_013 + Fm[3][3] * d3_012_012;
	
	if(cMath::IsZero(Det, (double)cMath::MatrixInvertEpsilon)) {
		return false;
	}

	const double iDet = 1.0 / Det;
	
	const double d2_03_01 = Fm[0][0] * Fm[3][1] - Fm[0][1] * Fm[3][0];
	const double d2_03_02 = Fm[0][0] * Fm[3][2] - Fm[0][2] * Fm[3][0];
	const double d2_03_03 = Fm[0][0] * Fm[3][3] - Fm[0][3] * Fm[3][0];
	const double d2_03_12 = Fm[0][1] * Fm[3][2] - Fm[0][2] * Fm[3][1];
	const double d2_03_13 = Fm[0][1] * Fm[3][3] - Fm[0][3] * Fm[3][1];
	const double d2_03_23 = Fm[0][2] * Fm[3][3] - Fm[0][3] * Fm[3][2];
	
	const double d2_13_01 = Fm[1][0] * Fm[3][1] - Fm[1][1] * Fm[3][0];
	const double d2_13_02 = Fm[1][0] * Fm[3][2] - Fm[1][2] * Fm[3][0];
	const double d2_13_03 = Fm[1][0] * Fm[3][3] - Fm[1][3] * Fm[3][0];
	const double d2_13_12 = Fm[1][1] * Fm[3][2] - Fm[1][2] * Fm[3][1];
	const double d2_13_13 = Fm[1][1] * Fm[3][3] - Fm[1][3] * Fm[3][1];
	const double d2_13_23 = Fm[1][2] * Fm[3][3] - Fm[1][3] * Fm[3][2];
	
	const double d3_023_012 = Fm[2][0] * d2_03_12 - Fm[2][1] * d2_03_02 + Fm[2][2] * d2_03_01;
	const double d3_023_013 = Fm[2][0] * d2_03_13 - Fm[2][1] * d2_03_03 + Fm[2][3] * d2_03_01;
	const double d3_023_023 = Fm[2][0] * d2_03_23 - Fm[2][2] * d2_03_03 + Fm[2][3] * d2_03_02;
	const double d3_023_123 = Fm[2][1] * d2_03_23 - Fm[2][2] * d2_03_13 + Fm[2][3] * d2_03_12;

	const double d3_123_012 = Fm[2][0] * d2_13_12 - Fm[2][1] * d2_13_02 + Fm[2][2] * d2_13_01;
	const double d3_123_013 = Fm[2][0] * d2_13_13 - Fm[2][1] * d2_13_03 + Fm[2][3] * d2_13_01;
	const double d3_123_023 = Fm[2][0] * d2_13_23 - Fm[2][2] * d2_13_03 + Fm[2][3] * d2_13_02;
	const double d3_123_123 = Fm[2][1] * d2_13_23 - Fm[2][2] * d2_13_13 + Fm[2][3] * d2_13_12;

	const double d3_013_012 = Fm[3][0] * d2_01_12 - Fm[3][1] * d2_01_02 + Fm[3][2] * d2_01_01;
	const double d3_013_013 = Fm[3][0] * d2_01_13 - Fm[3][1] * d2_01_03 + Fm[3][3] * d2_01_01;
	const double d3_013_023 = Fm[3][0] * d2_01_23 - Fm[3][2] * d2_01_03 + Fm[3][3] * d2_01_02;
	const double d3_013_123 = Fm[3][1] * d2_01_23 - Fm[3][2] * d2_01_13 + Fm[3][3] * d2_01_12;

	To->Elem(0,0) = (double)(-d3_123_123 * iDet);
	To->Elem(1,0) = (double)(d3_123_023 * iDet);
	To->Elem(2,0) = (double)(-d3_123_013 * iDet);
	To->Elem(3,0) = (double)(d3_123_012 * iDet);
	
	To->Elem(0,1) = (double)(d3_023_123 * iDet);
	To->Elem(1,1) = (double)(-d3_023_023 * iDet);
	To->Elem(2,1) = (double)(d3_023_013 * iDet);
	To->Elem(3,1) = (double)(-d3_023_012 * iDet);
	
	To->Elem(0,2) = (double)(d3_013_123 * iDet);
	To->Elem(1,2) = (double)(-d3_013_023 * iDet);
	To->Elem(2,2) = (double)(d3_013_013 * iDet);
	To->Elem(3,2) = (double)(-d3_013_012 * iDet);
	
	To->Elem(0,3) = (double)(-d3_012_123 * iDet);
	To->Elem(1,3) = (double)(d3_012_023 * iDet);
	To->Elem(2,3) = (double)(-d3_012_013 * iDet);
	To->Elem(3,3) = (double)(d3_012_012 * iDet);
	
	return true;
} // dMat4::Invert

// dMat4::Ortho
const dMat4 dMat4::Ortho(const double Width, const double Height, const double Znear, const double Zfar) {
	dMat4 T(dMat4::IdentityCtor);
	T(0, 0) = 2.0 / Width;
	T(1, 1) = 2.0 / Height;
	T(2, 2) = 1.0 / (Znear - Zfar);
	T(3, 2) = Znear / (Znear - Zfar);
	return T;
}

// dMat4::Ortho
const dMat4 dMat4::Ortho(const double Left, const double Right, const double Bottom, const double Top, const double Znear, const double Zfar) {
	dMat4 T(dMat4::IdentityCtor);
	T(0, 0) = 2.0 / (Right - Left);
	T(1, 1) = 2.0 / (Top - Bottom);
	T(2, 2) = 1.0 / (Znear - Zfar);
	T(3, 0) = (Left + Right) / (Left - Right);
	T(3, 1) = (Top + Bottom) / (Bottom - Top);
	T(3, 2) = Znear / (Znear - Zfar);
	return T;
}

// dMat4::Ortho : (const cBounds &)
const dMat4 dMat4::Ortho(const cBounds &B) {
	return Ortho(B.GetMin().x, B.GetMax().x, B.GetMin().y, B.GetMax().y, -B.GetMax().z, -B.GetMin().z);
}

//-------------------------------------------------------------------------------------------
// dMat4::CubeViewProjection
//-------------------------------------------------------------------------------------------
const dMat4 dMat4::CubeViewProjection(const dVec3 &Pos, const int Side, const double Radius, const bool GL) {
	static const dMat3 CubeOrientGL[6] = {
		// +X, -X, +Y, -Y, +Z, -Z
		dMat3(dMat3::RowsCtor, dVec3(0.0, 0.0, -1.0), dVec3(0.0, -1.0, 0.0), dVec3(-1.0, 0.0, 0.0)),
		dMat3(dMat3::RowsCtor, dVec3(0.0, 0.0, 1.0), dVec3(0.0, -1.0, 0.0), dVec3(1.0, 0.0, 0.0)),
		dMat3(dMat3::RowsCtor, dVec3(1.0, 0.0, 0.0), dVec3(0.0, 0.0, 1.0), dVec3(0.0, -1.0, 0.0)),
		dMat3(dMat3::RowsCtor, dVec3(1.0, 0.0, 0.0), dVec3(0.0, 0.0, -1.0), dVec3(0.0, 1.0, 0.0)),
		dMat3(dMat3::RowsCtor, dVec3(1.0, 0.0, 0.0), dVec3(0.0, -1.0, 0.0), dVec3(0.0, 0.0, -1.0)),
		dMat3(dMat3::RowsCtor, dVec3(-1.0, 0.0, 0.0), dVec3(0.0, -1.0, 0.0), dVec3(0.0, 0.0, 1.0))
	};
	static const dMat3 CubeOrientDX[6] = {
		dMat3(dMat3::RowsCtor, dVec3(0.0, 0.0, 1.0), dVec3(0.0, -1.0, 0.0), dVec3(1.0, 0.0, 0.0)),
		dMat3(dMat3::RowsCtor, dVec3(0.0, 0.0, -1.0), dVec3(0.0, -1.0, 0.0), dVec3(-1.0, 0.0, 0.0)),
		dMat3(dMat3::RowsCtor, dVec3(-1.0, 0.0, 0.0), dVec3(0.0, 0.0, 1.0), dVec3(0.0, 1.0, 0.0)),
		dMat3(dMat3::RowsCtor, dVec3(-1.0, 0.0, 0.0), dVec3(0.0, 0.0, -1.0), dVec3(0.0, -1.0, 0.0)),
		dMat3(dMat3::RowsCtor, dVec3(-1.0, 0.0, 0.0), dVec3(0.0, -1.0, 0.0), dVec3(0.0, 0.0, 1.0)),
		dMat3(dMat3::RowsCtor, dVec3(1.0, 0.0, 0.0), dVec3(0.0, -1.0, 0.0), dVec3(0.0, 0.0, -1.0))
	};
	cAssert(Side >= 0 && Side < 6);

	dMat3 O = GL ? CubeOrientGL[Side] : CubeOrientDX[Side];
	dVec3 F, R, U;
	O.ToVectors(&F, &R, &U);
	
	dMat4 W2V;
	W2V.SetIdentity();
	W2V.SetCol0(dVec4(R, -dVec3::Dot(R, Pos)));
	W2V.SetCol1(dVec4(U, -dVec3::Dot(U, Pos)));
	W2V.SetCol2(dVec4(-F, -dVec3::Dot(-F, Pos)));
	dMat4 V2P = Perspective(90.0, 1.0, 0.01f, Radius);
	return Mul(W2V, V2P);
} // dMat4::CubeViewProjection

//------------------------------------------------------------------------------------------------------------------------------------------------------------------
// dMat4::LookAtViewProjection
//------------------------------------------------------------------------------------------------------------------------------------------------------------------
const dMat4 dMat4::LookAtViewProjection(const dVec3 &LookFrom, const dVec3 &LookAt, const double FovY, const double AspectWtoH, const double Znear, const double Zfar) {
	dVec3 F = dVec3::Normalize(LookAt - LookFrom);
	dVec3 R = dVec3::Cross(F, dVec3::AxisY).ToNormal();
	dVec3 U = dVec3::Cross(R, F).ToNormal();
	
	dMat4 W2V;
	W2V.SetIdentity();
	W2V.SetCol0(dVec4(R, -dVec3::Dot(R, LookFrom)));
	W2V.SetCol1(dVec4(U, -dVec3::Dot(U, LookFrom)));
	W2V.SetCol2(dVec4(-F, -dVec3::Dot(-F, LookFrom)));
	dMat4 V2P = Perspective(FovY, AspectWtoH, Znear, Zfar);
	return Mul(W2V, V2P);
} // dMat4::LookAtViewProjection




::std::ostream& operator<<( ::std::ostream& out, const dMat4& m ) {
    out << "[" << m( 0, 0 ) << "," << m( 0, 1 ) << "," << m( 0, 2 ) << "," << m( 0, 3 ) <<
          ", " << m( 1, 0 ) << "," << m( 1, 1 ) << "," << m( 1, 2 ) << "," << m( 1, 3 ) <<
          ", " << m( 2, 0 ) << "," << m( 2, 1 ) << "," << m( 2, 2 ) << "," << m( 2, 3 ) <<
          ", " << m( 3, 0 ) << "," << m( 3, 1 ) << "," << m( 3, 2 ) << "," << m( 3, 3 ) << "]";
    return out;
}


} // comms
