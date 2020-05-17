#include "comms-Math.h"

namespace comms {

const cVec3 cVec3::Zero(0.0f);
const cVec3 cVec3::One(1.0f);
const cVec3 cVec3::Infinity(cMath::FloatMaxValue);
const cVec3 cVec3::AxisX(1.0f, 0.0f, 0.0f);
const cVec3 cVec3::AxisY(0.0f, 1.0f, 0.0f);
const cVec3 cVec3::AxisZ(0.0f, 0.0f, 1.0f);
const cVec3 cVec3::AxisNegX(-1.0f, 0.0f, 0.0f);
const cVec3 cVec3::AxisNegY(0.0f, -1.0f, 0.0f);
const cVec3 cVec3::AxisNegZ(0.0f, 0.0f, -1.0f);

// cVec3::ToString
const cStr cVec3::ToString(const int Prec) const {
	return cStr::ToString(ToFloatPtr(), GetDimension(), Prec);
}

//-----------------------------------------------------------------------------
// cVec3::ToAngles : cAngles() const
//-----------------------------------------------------------------------------
const cAngles cVec3::ToAngles() const {
	//                                                       ( -               -               -     )
	// RotationX(Pitch) * RotationY(Yaw) * RotationZ(0.0f) = ( -               -               -     )
	//                                                       ( CP*SY           -SP             CP*CY )

	// Since forward is negative Z (row 2), then Forward = { -CP*SY, SP, -CP*CY }

	cAngles Angles;
	Angles.Roll = 0.0f;
	Angles.Pitch = cMath::Deg(cMath::ASin(y));

	if(Angles.Pitch < 90.0f) {
		if(Angles.Pitch > -90.0f) {
			Angles.Yaw = cMath::Deg(cMath::ATan(-x, -z));
		} else { // Pitch == -90.0f
			Angles.Yaw = 0.0f;
		}
	} else { // Pitch == 90.0f
		Angles.Yaw = 0.0f;
	}
	return Angles;
}

//-------------------------------------------------------------------------------
// cVec3::Slerp
//-------------------------------------------------------------------------------
const cVec3 cVec3::Slerp(const cVec3 &n0, const cVec3 &n1, const float s) {
	if(s <= 0.0f) {
		return n0;
	} else if(s >= 1.0f) {
		return n1;
	}
	
	float Cos = cVec3::Dot(n0, n1);
	float Scale0, Scale1;
	if(1.0f - Cos > cMath::Epsilon) {
		float Angle = cMath::ACos(Cos);
		float Sin = cMath::Sin(Angle);
		Scale0 = cMath::Sin((1.0f - s) * Angle) / Sin;
		Scale1 = cMath::Sin(s * Angle) / Sin;
	} else {
		Scale0 = 1.0f - s;
		Scale1 = s;
	}
	return n0 * Scale0 + n1 * Scale1;
}

//-----------------------------------------------------------------------------
// cVec3::FixDegenerateNormal
//-----------------------------------------------------------------------------
bool cVec3::FixDegenerateNormal() {
	if(x == 0.0f) {
		if(y == 0.0f) {
			if(z > 0.0f) {
				if(z != 1.0f) {
					z = 1.0f;
					return true;
				}
			} else {
				if(z != -1.0f) {
					z = -1.0f;
					return true;
				}
			}
			return false;
		} else if(z == 0.0f) {
			if(y > 0.0f) {
				if(y != 1.0f) {
					y = 1.0f;
					return true;
				}
			} else {
				if(y != -1.0f) {
					y = -1.0f;
					return true;
				}
			}
			return false;
		}
	} else if(y == 0.0f) {
		if(z == 0.0f) {
			if(x > 0.0f) {
				if(x != 1.0f) {
					x = 1.0f;
					return true;
				}
			} else {
				if(x != -1.0f) {
					x = -1.0f;
					return true;
				}
			}
			return false;
		}
	}
	if(cMath::Abs(x) == 1.0f) {
		if(y != 0.0f || z != 0.0f) {
			y = z = 0.0f;
			return true;
		}
		return false;
	} else if(cMath::Abs(y) == 1.0f) {
		if(x != 0.0f || z != 0.0f) {
			x = z = 0.0f;
			return true;
		}
		return false;
	} else if(cMath::Abs(z) == 1.0f) {
		if(x != 0.0f || y != 0.0f) {
			x = y = 0.0f;
			return true;
		}
		return false;
	}
	return false;
}

//-----------------------------------------------------------------------------
// cVec3::RandRange1
//-----------------------------------------------------------------------------
const cVec3 cVec3::RandRange1() {
	cVec3 r;
	r.x = cMath::RandRange1();
	r.y = cMath::RandRange1();
	r.z = cMath::RandRange1();
	return r;
} // cVec3::RandRange1

//-----------------------------------------------------------------------------
// cVec3::RandNormal
//-----------------------------------------------------------------------------
const cVec3 cVec3::RandNormal() {
	cVec3 r;
	float lSq;
	do {
		r = RandRange1();
		lSq = r.LengthSq();
	} while(lSq > 1.0f || lSq < cMath::Epsilon);
	float il = 1.0f / cMath::Sqrt(lSq);
	r *= il;
	return r;
} // cVec3::RandNormal

// cVec3::ToPerps
void cVec3::ToPerps(cVec3 &X, cVec3 &Y) const {
	const cVec2 v(x, z);
	const float Alpha = v.Length() != 0.0f ? cVec2::Angle(v, cVec2::AxisY) : 0.0f;
	const float Beta = cMath::Deg(cMath::ASin(y / Length()));
	const cMat3 S = cMat3::RotationY(-Alpha) * cMat3::RotationX(Beta);
	X = S.GetCol0();
	Y = S.GetCol1();
}

// cVec3::ToPerp
const cVec3 cVec3::ToPerp() const {
	cVec3 X, Y;
	ToPerps(X, Y);
	return X;
}

//-----------------------------------------------------------------------------
// cVec3::FixDenormals
//-----------------------------------------------------------------------------
bool cVec3::FixDenormals() {
	bool IsDenormal = false;
	if(cMath::IsZero(x)) {
		x = 0.0f;
		IsDenormal = true;
	}
	if(cMath::IsZero(y)) {
		y = 0.0f;
		IsDenormal = true;
	}
	if(cMath::IsZero(z)) {
		z = 0.0f;
		IsDenormal = true;
	}
	if(cMath::IsOne(x)) {
		x = cMath::Sign(x);
		IsDenormal = true;
	}
	if(cMath::IsOne(y)) {
		y = cMath::Sign(y);
		IsDenormal = true;
	}
	if(cMath::IsOne(z)) {
		z = cMath::Sign(z);
		IsDenormal = true;
	}
	return IsDenormal;
} // cVec3::FixDenormals

// cVec3::TransformCoordinate : (cList<cVec3> *, ...)
void cVec3::TransformCoordinate(cList<cVec3> *S, const cMat4 &T) {
	int i;
	for(i = 0; i < S->Count(); i++) {
		cVec3 &u = S->GetAt(i);
		u.TransformCoordinate(T);
	}
}

// cVec3::TransformNormal : (cList<cVec3> *, ...)
void cVec3::TransformNormal(cList<cVec3> *S, const cMat4 &T) {
	int i;
	for(i = 0; i < S->Count(); i++) {
		cVec3 &u = S->GetAt(i);
		u.TransformNormal(T);
	}
}

// cVec3::TransformCoordinate
void cVec3::TransformCoordinate(cVec3 *Array, const int Count, const cMat4 &T) {
	int i;
	for(i = 0; i < Count; i++) {
		Array[i].TransformCoordinate(T);
	}
}

// cVec3::TransformNormal
void cVec3::TransformNormal(cVec3 *Array, const int Count, const cMat4 &T) {
	int i;
	for(i = 0; i < Count; i++) {
		Array[i].TransformNormal(T);
	}
}

// cVec3::RayTri
bool cVec3::RayTri(const cVec3 &RayOrig, const cVec3 &RayDir, const cVec3 &t0, const cVec3 &t1, const cVec3 &t2, float &u, float &v, float &t, const bool BackFaceCull) {
	static const float Eps = 1e-6f;

	const cVec3 e1 = t1 - t0;
	const cVec3 e2 = t2 - t0;

	const cVec3 p = cVec3::Cross(RayDir, e2);

	const float d = cVec3::Dot(e1, p);

	const cVec3 to = RayOrig - t0;
	const float id = 1.0f / d;

	const cVec3 q = cVec3::Cross(to, e1);

	if(d > Eps) {
		u = cVec3::Dot(to, p);
		if(u < 0.0f || u > d) {
			return false;
		}

		v = cVec3::Dot(RayDir, q);
		if(v < 0.0f || u + v > d) {
			return false;
		}
	} else if(!BackFaceCull && d < -Eps) {
		u = cVec3::Dot(to, p);
		if(u > 0.0f || u < d) {
			return false;
		}

		v = cVec3::Dot(RayDir, q);
		if(v > 0.0f || u + v < d) {
			return false;
		}
	} else {
		return false;
	}

	t = cVec3::Dot(e2, q) * id;
	u *= id;
	v *= id;
	return true;
}

// cVec3::PointInTriangle
bool cVec3::PointInTriangle(const cVec3 &p, const cVec3 &t0, const cVec3 &t1, const cVec3 &t2) {
	cVec3 e1 = t1 - t0;
	cVec3 e2 = t2 - t0;

	float a = e1.LengthSq();
	float b = cVec3::Dot(e1, e2);
	float c = e2.LengthSq();
	float ac_bb = a * c - b * b;

	cVec3 u = p - t0;
	float d = cVec3::Dot(u, e1);
	float e = cVec3::Dot(u, e2);
	float x = d * c - e * b;
	float y = e * a - d * b;
	float z = x + y - ac_bb;
	return z < 0.0f && x >= 0.0f && y >= 0.0f;
}

// cVec3::operator =
const cVec3 & cVec3::operator = ( const cVec4 &orig) {
	x = orig.x / orig.w;
	y = orig.y / orig.w;
	z = orig.z / orig.w;
	return *this;
}
cVec3::cVec3(const dVec3& v){
	x = (float)v.x;
	y = (float)v.y;
	z = (float)v.z;
}
} // comms
