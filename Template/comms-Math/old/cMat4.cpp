#include "comms-Math.h"

namespace comms {

const cMat4 cMat4::Zero(cMat4::ZeroCtor);
const cMat4 cMat4::Identity(cMat4::IdentityCtor);

// cMat4::ToString
const cStr cMat4::ToString(const int Prec) const {
	return cStr::ToString(ToFloatPtr(), 16, Prec);
}

// cMat4::ToQuat
const cQuat cMat4::ToQuat() const {
	return ToMat3().ToQuat();
}

// cMat4::ToNormalMatrix
const cMat3 cMat4::ToNormalMatrix() const {
	cMat3 N = ToMat3();
	if(!cMat3::Invert(N, &N)) {
		N.SetIdentity();
	} else {
		N.Transpose();
	}
	return N;
}

// cMat4::SetRotation
void cMat4::SetRotation( const cAngles& r ) {
    const cMat3  ro = r.ToMat3();
    const cVec3  tr = GetTranslation();
    *this = cMat4( ro, tr );
}

// cMat4::GetRotation
cAngles cMat4::GetRotation() const {
    return ToMat3().ToAngles();
}

//-------------------------------------------------------------------------------------
// cMat4::Perspective
//-------------------------------------------------------------------------------------
const cMat4 cMat4::Perspective(float YFov, float AspectWtoH, float Znear, float Zfar) {
	cMat4 P(cMat4::ZeroCtor);

	const float h = cMath::Tan(0.5f * cMath::Rad(YFov));
	const float w = h * AspectWtoH;
	
	P(0, 0) = 1.0f / w;
	P(1, 1) = 1.0f / h;
	P(2, 2) = (Zfar + Znear) / (Znear - Zfar);
	P(2, 3) = -1.0f;
	P(3, 2) = 2.0f * Znear * Zfar / (Znear - Zfar);
	
	return P;
} // cMat4::Perspective

//----------------------------------------------------------------------------------------------
// cMat4::PerspectiveInf
//----------------------------------------------------------------------------------------------
const cMat4 cMat4::PerspectiveInf(const float YFov, const float AspectWtoH, const float Znear) {
	cMat4 P(cMat4::ZeroCtor);

	const float h = cMath::Tan(0.5f * cMath::Rad(YFov));
	const float w = h * AspectWtoH;
	
	P(0, 0) = 1.0f / w;
	P(1, 1) = 1.0f / h;
	P(2, 2) = cMath::Epsilon - 1.0f;
	P(2, 3) = -1.0f;
	P(3, 2) = Znear * (cMath::Epsilon - 2.0f);
	
	return P;
} // cMat4::PerspectiveInf

// cMat4::Translation : const cMat4 (const float, const float)
const cMat4 cMat4::Translation(const float X, const float Y) {
	cMat4 T(cMat4::IdentityCtor);
	T.SetRow3(X, Y, 0.0f, 1.0f);
	return T;
}

// cMat4::Translation : const cMat4 (const float, const float, const float)
const cMat4 cMat4::Translation(const float X, const float Y, const float Z) {
	cMat4 T(cMat4::IdentityCtor);
	T.SetRow3(X, Y, Z, 1.0f);
	return T;
}

// cMat4::Translation : const cMat4 (const cVec2 &)
const cMat4 cMat4::Translation(const cVec2 &XY) {
	cMat4 T(cMat4::IdentityCtor);
	T.SetRow3(XY[0], XY[1], 0.0f, 1.0f);
	return T;
}

// cMat4::Translation : const cMat4 (const cVec3 &)
const cMat4 cMat4::Translation(const cVec3 &XYZ) {
	cMat4 T(cMat4::IdentityCtor);
	T.SetRow3(XYZ[0], XYZ[1], XYZ[2], 1.0f);
	return T;
}

// cMat4::Rotation
const cMat4 cMat4::Rotation(const cVec3 &Axis, const float Angle) {
	return cMat3::Rotation(Axis, Angle).ToMat4();
}

// cMat4::RotationX
const cMat4 cMat4::RotationX(const float Angle) {
	return cMat3::RotationX(Angle).ToMat4();
}

// cMat4::RotationY
const cMat4 cMat4::RotationY(const float Angle) {
	return cMat3::RotationY(Angle).ToMat4();
}

// cMat4::RotationZ
const cMat4 cMat4::RotationZ(const float Angle) {
	return cMat3::RotationZ(Angle).ToMat4();
}

// cMat4::RotationXYZ
const cMat4 cMat4::RotationXYZ(const float Pitch, const float Yaw, const float Roll) {
	return cMat3::RotationXYZ(Pitch, Yaw, Roll).ToMat4();
}

// cMat4::EulerZYX
const cMat4 cMat4::EulerZYX(const float eulerX, const float eulerY, const float eulerZ) {
	return cMat3::EulerZYX(eulerX, eulerY, eulerZ).ToMat4();
}

// cMat4::RotationAt : const cMat4 (const cVec2 &, const float)
const cMat4 cMat4::RotationAt(const cVec2 &Orig, const float Angle) {
	return RotationAt(cVec3(Orig, 0.0f), cVec3::AxisZ, Angle);
}

// cMat4::RotationAt : const cMat4 (const cVec3 &, const cVec3 &, const float)
const cMat4 cMat4::RotationAt(const cVec3 &Orig, const cVec3 &Axis, const float Angle) {
	return Mul(Mul(Translation(-Orig), cMat4::Rotation(Axis, Angle)), Translation(Orig));
}

// cMat4::Scaling : const cMat4 (const float)
const cMat4 cMat4::Scaling(const float XYZ) {
	cMat4 S(cMat4::IdentityCtor);
	S(0, 0) = S(1, 1) = S(2, 2) = XYZ;
	return S;
}

// cMat4::Scaling : const cMat4 (const float, const float)
const cMat4 cMat4::Scaling(const float X, const float Y) {
	cMat4 S(cMat4::IdentityCtor);
	S(0, 0) = X;
	S(1, 1) = Y;
	return S;
}

// cMat4::Scaling : const cMat4 (const float, const float, const float)
const cMat4 cMat4::Scaling(const float X, const float Y, const float Z) {
	cMat4 S(cMat4::IdentityCtor);
	S(0, 0) = X;
	S(1, 1) = Y;
	S(2, 2) = Z;
	return S;
}

// cMat4::Scaling : const cMat4 (const cVec2 &)
const cMat4 cMat4::Scaling(const cVec2 &XY) {
	cMat4 S(cMat4::IdentityCtor);
	S(0, 0) = XY[0];
	S(1, 1) = XY[1];
	return S;
}

// cMat4::Scaling : const cMat4 (const cVec3 &)
const cMat4 cMat4::Scaling(const cVec3 &XYZ) {
	cMat4 S(cMat4::IdentityCtor);
	S(0, 0) = XYZ[0];
	S(1, 1) = XYZ[1];
	S(2, 2) = XYZ[2];
	return S;
}

// cMat4::ScalingAt : const cMat4 (const float, const float, const float)
const cMat4 cMat4::ScalingAt(const float OrigX, const float OrigY, const float ScaleXY) {
	return ScalingAt(cVec3(OrigX, OrigY, 0.0f), cVec3(ScaleXY, ScaleXY, 1.0f));
}

// cMat4::ScalingAt : const cMat4 (const float, const float, const float, const float)
const cMat4 cMat4::ScalingAt(const float OrigX, const float OrigY, const float ScaleX, const float ScaleY) {
	return ScalingAt(cVec3(OrigX, OrigY, 0.0f), cVec3(ScaleX, ScaleY, 1.0f));
}

// cMat4::ScalingAt : const cMat4 (const cVec2 &, const float)
const cMat4 cMat4::ScalingAt(const cVec2 &Orig, const float ScaleXY) {
	return ScalingAt(cVec3(Orig, 0.0f), cVec3(ScaleXY, ScaleXY, 1.0f));
}

// cMat4::ScalingAt : const cMat4 (const cVec2 &, const float, const float)
const cMat4 cMat4::ScalingAt(const cVec2 &Orig, const float ScaleX, const float ScaleY) {
	return ScalingAt(cVec3(Orig, 0.0f), cVec3(ScaleX, ScaleY, 1.0f));
}

// cMat4::ScalingAt : const cMat4 (const cVec2 &, const cVec2 &)
const cMat4 cMat4::ScalingAt(const cVec2 &Orig, const cVec2 &Scale) {
	return ScalingAt(cVec3(Orig, 0.0f), cVec3(Scale, 1.0f));
}

// cMat4::ScalingAt : const cMat4 (const cVec3 &, const float)
const cMat4 cMat4::ScalingAt(const cVec3 &Orig, const float ScaleXYZ) {
	return ScalingAt(Orig, cVec3(ScaleXYZ));
}

// cMat4::ScalingAt : const cMat4 (const cVec3 &, const float, const float, const float)
const cMat4 cMat4::ScalingAt(const cVec3 &Orig, const float ScaleX, const float ScaleY, const float ScaleZ) {
	return ScalingAt(Orig, cVec3(ScaleX, ScaleY, ScaleZ));
}

// cMat4::ScalingAt : const cMat4 (const cVec3 &, const cVec3 &)
const cMat4 cMat4::ScalingAt(const cVec3 &Orig, const cVec3 &S) {
	return Mul(Mul(Translation(-Orig), Scaling(S)), Translation(Orig));
}
// cMat4::ScalingAt : const cMat4 ScalingAt(const cVec3 &, const cVec3 &, float);
const cMat4 cMat4::ScalingAt(const cVec3 &Orig, const cVec3 &Dir, float Scale){
	//v1=v+Dir*(v-Orig).dot(Dir)*(Scale-1);
	//x1.x=v.x+(Scale-1.0)*Dir.x*((v.x-Orig.x)*Dir.x+(v.y-Orig.y)*Dir.y+(v.z-Orig.z)*Dir.z)
	//....
	float sc = Scale-1.0f;
	cMat4 m = cMat4::Identity;
	float dp = Dir.Dot( Orig );
	
	m(0,0)=1.0f+sc*Dir.x*Dir.x;  
	m(1,0)=sc*Dir.x*Dir.y;
	m(2,0)=sc*Dir.x*Dir.z;
	m(3,0)=-sc*Dir.x*dp;

	m(0,1)=sc*Dir.y*Dir.x;  
	m(1,1)=1.0f+sc*Dir.y*Dir.y;
	m(2,1)=sc*Dir.y*Dir.z;
	m(3,1)=-sc*Dir.y*dp;

	m(0,2)=sc*Dir.z*Dir.x;  
	m(1,2)=sc*Dir.z*Dir.y;
	m(2,2)=1.0f+sc*Dir.z*Dir.z;
	m(3,2)=-sc*Dir.z*dp;

	return m;
}

//-----------------------------------------------------------------------------
// cMat4::Determinant
//-----------------------------------------------------------------------------
float cMat4::Determinant() const {
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
	return (float)Det;
} // cMat4::Determinant

//-----------------------------------------------------------------------------
// cMat4::Invert : bool (const cMat4, cMat4 *)
//-----------------------------------------------------------------------------
bool cMat4::Invert(const cMat4 &Fm, cMat4 *To) {
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

	To->Elem(0,0) = (float)(-d3_123_123 * iDet);
	To->Elem(1,0) = (float)(d3_123_023 * iDet);
	To->Elem(2,0) = (float)(-d3_123_013 * iDet);
	To->Elem(3,0) = (float)(d3_123_012 * iDet);
	
	To->Elem(0,1) = (float)(d3_023_123 * iDet);
	To->Elem(1,1) = (float)(-d3_023_023 * iDet);
	To->Elem(2,1) = (float)(d3_023_013 * iDet);
	To->Elem(3,1) = (float)(-d3_023_012 * iDet);
	
	To->Elem(0,2) = (float)(d3_013_123 * iDet);
	To->Elem(1,2) = (float)(-d3_013_023 * iDet);
	To->Elem(2,2) = (float)(d3_013_013 * iDet);
	To->Elem(3,2) = (float)(-d3_013_012 * iDet);
	
	To->Elem(0,3) = (float)(-d3_012_123 * iDet);
	To->Elem(1,3) = (float)(d3_012_023 * iDet);
	To->Elem(2,3) = (float)(-d3_012_013 * iDet);
	To->Elem(3,3) = (float)(d3_012_012 * iDet);
	
	return true;
} // cMat4::Invert

// cMat4::Ortho
const cMat4 cMat4::Ortho(const float Width, const float Height, const float Znear, const float Zfar) {
	cMat4 T(cMat4::IdentityCtor);
	T(0, 0) = 2.0f / Width;
	T(1, 1) = 2.0f / Height;
	T(2, 2) = 1.0f / (Znear - Zfar);
	T(3, 2) = Znear / (Znear - Zfar);
	return T;
}

// cMat4::Ortho
const cMat4 cMat4::Ortho(const float Left, const float Right, const float Bottom, const float Top, const float Znear, const float Zfar) {
	cMat4 T(cMat4::IdentityCtor);
	T(0, 0) = 2.0f / (Right - Left);
	T(1, 1) = 2.0f / (Top - Bottom);
	T(2, 2) = 1.0f / (Znear - Zfar);
	T(3, 0) = (Left + Right) / (Left - Right);
	T(3, 1) = (Top + Bottom) / (Bottom - Top);
	T(3, 2) = Znear / (Znear - Zfar);
	return T;
}

// cMat4::Ortho : (const cBounds &)
const cMat4 cMat4::Ortho(const cBounds &B) {
	return Ortho(B.GetMin().x, B.GetMax().x, B.GetMin().y, B.GetMax().y, -B.GetMax().z, -B.GetMin().z);
}

//-------------------------------------------------------------------------------------------
// cMat4::CubeViewProjection
//-------------------------------------------------------------------------------------------
const cMat4 cMat4::CubeViewProjection(const cVec3 &Pos, const int Side, const float Radius, const bool GL) {
	static const cMat3 CubeOrientGL[6] = {
		// +X, -X, +Y, -Y, +Z, -Z
		cMat3(cMat3::RowsCtor, cVec3(0.0f, 0.0f, -1.0f), cVec3(0.0f, -1.0f, 0.0f), cVec3(-1.0f, 0.0f, 0.0f)),
		cMat3(cMat3::RowsCtor, cVec3(0.0f, 0.0f, 1.0f), cVec3(0.0f, -1.0f, 0.0f), cVec3(1.0f, 0.0f, 0.0f)),
		cMat3(cMat3::RowsCtor, cVec3(1.0f, 0.0f, 0.0f), cVec3(0.0f, 0.0f, 1.0f), cVec3(0.0f, -1.0f, 0.0f)),
		cMat3(cMat3::RowsCtor, cVec3(1.0f, 0.0f, 0.0f), cVec3(0.0f, 0.0f, -1.0f), cVec3(0.0f, 1.0f, 0.0f)),
		cMat3(cMat3::RowsCtor, cVec3(1.0f, 0.0f, 0.0f), cVec3(0.0f, -1.0f, 0.0f), cVec3(0.0f, 0.0f, -1.0f)),
		cMat3(cMat3::RowsCtor, cVec3(-1.0f, 0.0f, 0.0f), cVec3(0.0f, -1.0f, 0.0f), cVec3(0.0f, 0.0f, 1.0f))
	};
	static const cMat3 CubeOrientDX[6] = {
		cMat3(cMat3::RowsCtor, cVec3(0.0f, 0.0f, 1.0f), cVec3(0.0f, -1.0f, 0.0f), cVec3(1.0f, 0.0f, 0.0f)),
		cMat3(cMat3::RowsCtor, cVec3(0.0f, 0.0f, -1.0f), cVec3(0.0f, -1.0f, 0.0f), cVec3(-1.0f, 0.0f, 0.0f)),
		cMat3(cMat3::RowsCtor, cVec3(-1.0f, 0.0f, 0.0f), cVec3(0.0f, 0.0f, 1.0f), cVec3(0.0f, 1.0f, 0.0f)),
		cMat3(cMat3::RowsCtor, cVec3(-1.0f, 0.0f, 0.0f), cVec3(0.0f, 0.0f, -1.0f), cVec3(0.0f, -1.0f, 0.0f)),
		cMat3(cMat3::RowsCtor, cVec3(-1.0f, 0.0f, 0.0f), cVec3(0.0f, -1.0f, 0.0f), cVec3(0.0f, 0.0f, 1.0f)),
		cMat3(cMat3::RowsCtor, cVec3(1.0f, 0.0f, 0.0f), cVec3(0.0f, -1.0f, 0.0f), cVec3(0.0f, 0.0f, -1.0f))
	};
	cAssert(Side >= 0 && Side < 6);

	cMat3 O = GL ? CubeOrientGL[Side] : CubeOrientDX[Side];
	cVec3 F, R, U;
	O.ToVectors(&F, &R, &U);
	
	cMat4 W2V;
	W2V.SetIdentity();
	W2V.SetCol0(cVec4(R, -cVec3::Dot(R, Pos)));
	W2V.SetCol1(cVec4(U, -cVec3::Dot(U, Pos)));
	W2V.SetCol2(cVec4(-F, -cVec3::Dot(-F, Pos)));
	cMat4 V2P = Perspective(90.0f, 1.0f, 0.01f, Radius);
	return Mul(W2V, V2P);
} // cMat4::CubeViewProjection

//------------------------------------------------------------------------------------------------------------------------------------------------------------------
// cMat4::LookAtViewProjection
//------------------------------------------------------------------------------------------------------------------------------------------------------------------
const cMat4 cMat4::LookAtViewProjection(const cVec3 &LookFrom, const cVec3 &LookAt, const float FovY, const float AspectWtoH, const float Znear, const float Zfar) {
	cVec3 F = cVec3::Normalize(LookAt - LookFrom);
	cVec3 R = cVec3::Cross(F, cVec3::AxisY).ToNormal();
	cVec3 U = cVec3::Cross(R, F).ToNormal();
	
	cMat4 W2V;
	W2V.SetIdentity();
	W2V.SetCol0(cVec4(R, -cVec3::Dot(R, LookFrom)));
	W2V.SetCol1(cVec4(U, -cVec3::Dot(U, LookFrom)));
	W2V.SetCol2(cVec4(-F, -cVec3::Dot(-F, LookFrom)));
	cMat4 V2P = Perspective(FovY, AspectWtoH, Znear, Zfar);
	return Mul(W2V, V2P);
} // cMat4::LookAtViewProjection




::std::ostream& operator<<( ::std::ostream& out, const cMat4& m ) {
    out << "[" << m( 0, 0 ) << "," << m( 0, 1 ) << "," << m( 0, 2 ) << "," << m( 0, 3 ) <<
          ", " << m( 1, 0 ) << "," << m( 1, 1 ) << "," << m( 1, 2 ) << "," << m( 1, 3 ) <<
          ", " << m( 2, 0 ) << "," << m( 2, 1 ) << "," << m( 2, 2 ) << "," << m( 2, 3 ) <<
          ", " << m( 3, 0 ) << "," << m( 3, 1 ) << "," << m( 3, 2 ) << "," << m( 3, 3 ) << "]";
    return out;
}


} // comms
