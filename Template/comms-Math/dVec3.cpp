#include "comms-Math.h"

namespace comms {

const dVec3 dVec3::Zero(0.0);
const dVec3 dVec3::One(1.0);
const dVec3 dVec3::Infinity(cMath::DoubleMaxValue);
const dVec3 dVec3::AxisX(1.0, 0.0, 0.0);
const dVec3 dVec3::AxisY(0.0, 1.0, 0.0);
const dVec3 dVec3::AxisZ(0.0, 0.0, 1.0);
const dVec3 dVec3::AxisNegX(-1.0, 0.0, 0.0);
const dVec3 dVec3::AxisNegY(0.0, -1.0, 0.0);
const dVec3 dVec3::AxisNegZ(0.0, 0.0, -1.0);

dVec3::dVec3(const cVec3& v3)
	: x(v3.x), y(v3.y), z(v3.z) {}

// dVec3::ToString
const cStr dVec3::ToString(const int Prec) const {
	return cStr::ToString(ToDoublePtr(), GetDimension(), Prec);
}

//-----------------------------------------------------------------------------
// dVec3::ToAngles : cAngles() const
//-----------------------------------------------------------------------------
const cAngles dVec3::ToAngles() const {
	//                                                       ( -               -               -     )
	// RotationX(Pitch) * RotationY(Yaw) * RotationZ(0.0) = ( -               -               -     )
	//                                                       ( CP*SY           -SP             CP*CY )

	// Since forward is negative Z (row 2), then Forward = { -CP*SY, SP, -CP*CY }

	cAngles Angles;
	Angles.Roll = 0.0;
	Angles.Pitch = float(cMath::Deg(cMath::ASin(y)));

	if(Angles.Pitch < 90.0) {
		if(Angles.Pitch > -90.0) {
			Angles.Yaw = float(cMath::Deg(cMath::ATan(-x, -z)));
		} else { // Pitch == -90.0
			Angles.Yaw = 0.0;
		}
	} else { // Pitch == 90.0
		Angles.Yaw = 0.0;
	}
	return Angles;
}

//-------------------------------------------------------------------------------
// dVec3::Slerp
//-------------------------------------------------------------------------------
const dVec3 dVec3::Slerp(const dVec3 &n0, const dVec3 &n1, const double s) {
	if(s <= 0.0) {
		return n0;
	} else if(s >= 1.0) {
		return n1;
	}
	
	double Cos = dVec3::Dot(n0, n1);
	double Scale0, Scale1;
	if(1.0 - Cos > cMath::Epsilon) {
		double Angle = cMath::ACos(Cos);
		double Sin = cMath::Sin(Angle);
		Scale0 = cMath::Sin((1.0 - s) * Angle) / Sin;
		Scale1 = cMath::Sin(s * Angle) / Sin;
	} else {
		Scale0 = 1.0 - s;
		Scale1 = s;
	}
	return n0 * Scale0 + n1 * Scale1;
}

//-----------------------------------------------------------------------------
// dVec3::FixDegenerateNormal
//-----------------------------------------------------------------------------
bool dVec3::FixDegenerateNormal() {
	if(x == 0.0) {
		if(y == 0.0) {
			if(z > 0.0) {
				if(z != 1.0) {
					z = 1.0;
					return true;
				}
			} else {
				if(z != -1.0) {
					z = -1.0;
					return true;
				}
			}
			return false;
		} else if(z == 0.0) {
			if(y > 0.0) {
				if(y != 1.0) {
					y = 1.0;
					return true;
				}
			} else {
				if(y != -1.0) {
					y = -1.0;
					return true;
				}
			}
			return false;
		}
	} else if(y == 0.0) {
		if(z == 0.0) {
			if(x > 0.0) {
				if(x != 1.0) {
					x = 1.0;
					return true;
				}
			} else {
				if(x != -1.0) {
					x = -1.0;
					return true;
				}
			}
			return false;
		}
	}
	if(cMath::Abs(x) == 1.0) {
		if(y != 0.0 || z != 0.0) {
			y = z = 0.0;
			return true;
		}
		return false;
	} else if(cMath::Abs(y) == 1.0) {
		if(x != 0.0 || z != 0.0) {
			x = z = 0.0;
			return true;
		}
		return false;
	} else if(cMath::Abs(z) == 1.0) {
		if(x != 0.0 || y != 0.0) {
			x = y = 0.0;
			return true;
		}
		return false;
	}
	return false;
}

//-----------------------------------------------------------------------------
// dVec3::RandRange1
//-----------------------------------------------------------------------------
const dVec3 dVec3::RandRange1() {
	dVec3 r;
	r.x = cMath::RandRange1();
	r.y = cMath::RandRange1();
	r.z = cMath::RandRange1();
	return r;
} // dVec3::RandRange1

//-----------------------------------------------------------------------------
// dVec3::RandNormal
//-----------------------------------------------------------------------------
const dVec3 dVec3::RandNormal() {
	dVec3 r;
	double lSq;
	do {
		r = RandRange1();
		lSq = r.LengthSq();
	} while(lSq > 1.0 || lSq < cMath::Epsilon);
	double il = 1.0 / cMath::Sqrt(lSq);
	r *= il;
	return r;
} // dVec3::RandNormal

// dVec3::ToPerps
void dVec3::ToPerps(dVec3 &X, dVec3 &Y) const {
	const dVec2 v(x, z);
	const double Alpha = v.Length() != 0.0 ? dVec2::Angle(v, dVec2::AxisY) : 0.0;
	const double Beta = cMath::Deg(cMath::ASin(y / Length()));
	const dMat3 S = dMat3::RotationY(-Alpha) * dMat3::RotationX(Beta);
	X = S.GetCol0();
	Y = S.GetCol1();
}

// dVec3::ToPerp
const dVec3 dVec3::ToPerp() const {
	dVec3 X, Y;
	ToPerps(X, Y);
	return X;
}

//-----------------------------------------------------------------------------
// dVec3::FixDenormals
//-----------------------------------------------------------------------------
bool dVec3::FixDenormals() {
	bool IsDenormal = false;
	if(cMath::IsZero(x)) {
		x = 0.0;
		IsDenormal = true;
	}
	if(cMath::IsZero(y)) {
		y = 0.0;
		IsDenormal = true;
	}
	if(cMath::IsZero(z)) {
		z = 0.0;
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
} // dVec3::FixDenormals

// dVec3::TransformCoordinate : (cList<dVec3> *, ...)
void dVec3::TransformCoordinate(cList<dVec3> *S, const dMat4 &T) {
	int i;
	for(i = 0; i < S->Count(); i++) {
		dVec3 &u = S->GetAt(i);
		u.TransformCoordinate(T);
	}
}

// dVec3::TransformNormal : (cList<dVec3> *, ...)
void dVec3::TransformNormal(cList<dVec3> *S, const dMat4 &T) {
	int i;
	for(i = 0; i < S->Count(); i++) {
		dVec3 &u = S->GetAt(i);
		u.TransformNormal(T);
	}
}

// dVec3::TransformCoordinate
void dVec3::TransformCoordinate(dVec3 *Array, const int Count, const dMat4 &T) {
	int i;
	for(i = 0; i < Count; i++) {
		Array[i].TransformCoordinate(T);
	}
}

// dVec3::TransformNormal
void dVec3::TransformNormal(dVec3 *Array, const int Count, const dMat4 &T) {
	int i;
	for(i = 0; i < Count; i++) {
		Array[i].TransformNormal(T);
	}
}

// dVec3::RayTri
bool dVec3::RayTri(const dVec3 &RayOrig, const dVec3 &RayDir, const dVec3 &t0, const dVec3 &t1, const dVec3 &t2, double &u, double &v, double &t, const bool BackFaceCull) {
	static const double Eps = 1e-6f;

	const dVec3 e1 = t1 - t0;
	const dVec3 e2 = t2 - t0;

	const dVec3 p = dVec3::Cross(RayDir, e2);

	const double d = dVec3::Dot(e1, p);

	const dVec3 to = RayOrig - t0;
	const double id = 1.0 / d;

	const dVec3 q = dVec3::Cross(to, e1);

	if(d > Eps) {
		u = dVec3::Dot(to, p);
		if(u < 0.0 || u > d) {
			return false;
		}

		v = dVec3::Dot(RayDir, q);
		if(v < 0.0 || u + v > d) {
			return false;
		}
	} else if(!BackFaceCull && d < -Eps) {
		u = dVec3::Dot(to, p);
		if(u > 0.0 || u < d) {
			return false;
		}

		v = dVec3::Dot(RayDir, q);
		if(v > 0.0 || u + v < d) {
			return false;
		}
	} else {
		return false;
	}

	t = dVec3::Dot(e2, q) * id;
	u *= id;
	v *= id;
	return true;
}

// dVec3::PointInTriangle
bool dVec3::PointInTriangle(const dVec3 &p, const dVec3 &t0, const dVec3 &t1, const dVec3 &t2) {
	dVec3 e1 = t1 - t0;
	dVec3 e2 = t2 - t0;

	double a = e1.LengthSq();
	double b = dVec3::Dot(e1, e2);
	double c = e2.LengthSq();
	double ac_bb = a * c - b * b;

	dVec3 u = p - t0;
	double d = dVec3::Dot(u, e1);
	double e = dVec3::Dot(u, e2);
	double x = d * c - e * b;
	double y = e * a - d * b;
	double z = x + y - ac_bb;
	return z < 0.0 && x >= 0.0 && y >= 0.0;
}

// dVec3::operator =
const dVec3 & dVec3::operator = ( const dVec4 &orig) {
	x = orig.x / orig.w;
	y = orig.y / orig.w;
	z = orig.z / orig.w;
	return *this;
}

} // comms
