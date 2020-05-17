#pragma once

//-----------------------------------------------------------------------------
// cMath
//-----------------------------------------------------------------------------
class cMath {
public:
	static const float Pi;
	static const float TwoPi;
	static const float HalfPi;
	static const float QuarterPi;

	static const float RadsPerDeg;
	static const float DegsPerRad;
	
	static const float Epsilon;
	static const float EpsilonSq;
	static const float SpaceEpsilon;

	static const float MatrixEpsilon;
	static const float MatrixInvertEpsilon;
	static const double dMatrixInvertEpsilon;

	static const double dEpsilon;

	static const float Sqrt1Over2;
	static const float Sqrt1Over3;

	static const float SecsPerMs;
	static const float MsPerSec;

	static const double DoubleMinValue; // 0x0010000000000000
	static const double DoubleMaxValue; // 0x7fefffffffffffff

	static const float FloatMinValue; // 0x00800000
	static const float FloatMaxValue; // 0x7f7fffff
	static bool IsInfinity(const float Value); // 1.#INF000 or -1.#INF000
	static bool IsPositiveInfinity(const float Value); //  1.#INF000
	static bool IsNegativeInfinity(const float Value); // -1.#INF000
	
	static const int IntMinValue; // 0x80000000
	static const int IntMaxValue; // 0x7fffffff

	/// The same as Win32 API "MulDiv"
	static int MulDiv(int Number, int Numerator, int Denominator);
	
	static float Rad(float Deg);
	static float Deg(float Rad);

	static double Rad(double Deg);
	static double Deg(double Rad);

	static float Sec(float Ms);
	static float Ms(float Sec);

	// @todo fine  Add templates.
	static bool IsZero(int, int /* Eps - unused */ );

	static bool IsZero(const float f, const float Eps = Epsilon);
	static bool IsOne(const float f, const float Eps = Epsilon);
	static bool IsOne(const double f, const double Eps = Epsilon);
	static bool IsMinusOne(const float f, const float Eps = Epsilon);
	static bool IsZeroToOneExact(const float f);
	static bool IsZeroToOneEps(const float f, const float Eps = Epsilon);
	static bool IsInRange(const int i, const int Lo, const int Hi);
	static bool IsInRangeExact(const float f, const float Lo, const float Hi);
	static bool IsInRangeEps(const float f, const float Lo, const float Hi, const float Eps = Epsilon);
	static bool Equals(const float x, const float y, const float Eps = Epsilon);
	static bool IsValid(const float f);
	static bool IsValid(const double f);

	static bool IsZero(const double d, const double Eps = dEpsilon);
	static bool Equals(const double x, const double y, const double Eps = dEpsilon);
	
	static float Clamp01(const float f);
	static float ClampRange1(const float f);
	static float ClampRange(const float f, const float l);
	static float Lerp(const float a, const float b, const float s);
	static float Cerp(const float a, const float b, const float s);
	static float Lerp05(const float a, const float b);
	static float Lerper(const float Fm, const float To, const float x);
	static float LerperClamp01(const float Lo, const float Hi, const float x);
	static float MidPointLerp(const float Start, const float Mid, const float End, const float s);

	static int Abs(int n);
	static float Abs(float x);
	static double Abs(double x);
	static float Round(float x);
	static double Round(double x);

	template<typename Type>
	static Type Round(float x);

	static float Sqrt(float x);
	static double Sqrt(double x);
	static float FastInvSqrt(float x);
	static float FastSqrt(float x);
	static float Sin(float a);
	static float Cos(float a);
	static double Sin(double a);
	static double Cos(double a);
	static void SinCos(float Angle, float &S, float &C);
	static void SinCos(double Angle, double &S, double &C);
	static float Tan(float a);
	static double Tan(double a);
	static float ASin(float x);
	static double ASin(double x);
	static float ACos(float x);
	static double ACos(double x);
	static float ATan(float x);
	static double ATan(double x);
	static float ATan(float y, float x);
	static double ATan(double y, double x);
	static float Pow(float x, float y);
	static double Pow(double x, double y);
	static float Exp(float x);
	static double Exp(double x);
	static float Ldexp(const float x, const int exp);
	static double Ldexp(const double x, const int exp);
	static float Frexp(const float x, int *exp);
	static double Frexp(const double x, int *exp);
	static float Log(float x);
	static double Log(double x);

	static float Floor(const float f);
	static float Ceil(const float f);
	static float Frac(const float f);

	static double Floor(const double d);
	static double Ceil(const double d);
	static double Frac(const double d);

	static float Periodic(const float f, const float Lo, const float Hi, int *nPeriods = NULL);
	static int IndexForInsert(const float f, const float *Array, const int nCount, const size_t Stride = 0);
	
	static float AngleNormalizeTwoPi(float Angle); // 0 <= Angle < TwoPi
	static double AngleNormalizeTwoPi(double Angle); // 0 <= Angle < TwoPi
	static float AngleNormalizePi(float Angle); // - Pi < Angle <= Pi
	static float AngleNormalize360(float Angle);
	static float AngleNormalize180(float Angle);
	static void AngleEnsureShortestPath180(float *Alpha, float *Beta);
	static float AngleDeltaRad(float Alpha, float Beta);
	static float AngleLerpRad(float Alpha, float Beta, float s);
	static float AngleDeltaDeg(float Alpha, float Beta);
	static float AngleLerpDeg(float Alpha, float Beta, float s);

	static int ClosestPowerOfTwo(const int X);
	static int UpperPowerOfTwo(const int X);
	static int LowerPowerOfTwo(const int X);
	static bool IsPowerOfTwo(const int X);

	static void Randomize(const dword Seed);
	static float Rand01();
	static float RandRange1();
	static double dRand(const double Lo, const double Hi);
	static float Rand(const float Lo, const float Hi);
	static int Rand(const int Lo, const int Hi);

	// cMath::Swap<Type> : void(Type &, Type &)
	template<class Type>
	static void Swap(Type &x, Type &y) {
		Type z = x;
		x = y;
		y = z;
	}

	// cMath::SwapChannels<Type> : void (Type *, const int, const int, const int, const int)
	template<class Type>
	static void SwapChannels(Type *Array, const int Count, const int NChannels, const int Ch0, const int Ch1) {
		for(int i = 0; i < Count; i++) {
			Swap(Array[Ch0], Array[Ch1]);
			Array += NChannels;
		}
	}
	
	// cMath::Square<Type> : Type(const Type)
	template<class Type>
	static Type Square(const Type x) {
		return x * x;
	}

	// cMath::Cube<Type> : Type(const Type)
	template<class Type>
	static Type Cube(const Type x) {
		return x * x * x;
	}

	// cMath::Sign<Type> : Type(const Type)
	template<class Type>
	static Type Sign(const Type x) {
		return x > (Type)0 ? (Type)1 : (x < (Type)0 ? -(Type)1 : (Type)0);
	}

	static int SignBitSet(const int i);
	static int SignBitNotSet(const int i);

	// cMath::Max<Type> : Type(const Type, const Type)
	template<class Type>
	static Type Max(const Type x, const Type y) {
		return x > y ? x : y;
	}

	// cMath::Min<Type> : Type(const Type, const Type)
	template<class Type>
	static Type Min(const Type x, const Type y) {
		return x < y ? x : y;
	}

	// cMath::MaxIndex<Type> : int(const Type, const Type)
	template<class Type>
	static int MaxIndex(const Type x, const Type y) {
		return x > y ? 0 : 1;
	}

	// cMath::MinIndex<Type> : int(const Type, const Type)
	template<class Type>
	static int MinIndex(const Type x, const Type y) {
		return x < y ? 0 : 1;
	}
	
	// cMath::Max<Type> : Type(const Type, const Type, const Type)
	template<class Type>
	static Type Max(const Type x, const Type y, const Type z) {
		return x > y ? (x > z ? x : z) : (y > z ? y : z);
	}

	// cMath::Min<Type> : Type(const Type, const Type, const Type)
	template<class Type>
	static Type Min(const Type x, const Type y, const Type z) {
		return x < y ? (x < z ? x : z) : (y < z ? y : z);
	}

	// cMath::MaxIndex<Type> : int(const Type, const Type, const Type)
	template<class Type>
	static int MaxIndex(const Type x, const Type y, const Type z) {
		return x > y ? (x > z ? 0 : 2) : (y > z ? 1 : 2);
	}

	// cMath::MinIndex<Type> : int(const Type, const Type, const Type)
	template<class Type>
	static int MinIndex(const Type x, const Type y, const Type z) {
		return x < y ? (x < z ? 0 : 2) : (y < z ? 1 : 2);
	}
	
	// cMath::Max<Type> : Type (const Type, const Type, const Type, const Type)
	template<class Type>
	static Type Max(const Type x, const Type y, const Type z, const Type w) {
		return x > y ? (x > z ? (x > w ? x : w) : (z > w ? z : w)) : (y > z ? (y > w ? y : w) : (z > w ? z : w));
	}

	// cMath::Min<Type> : Type (const Type, const Type, const Type, const Type)
	template<class Type>
	static Type Min(const Type x, const Type y, const Type z, const Type w) {
		return x < y ? (x < z ? (x < w ? x : w) : (z < w ? z : w)) : (y < z ? (y < w ? y : w) : (z < w ? z : w));
	}

	// cMath::MaxIndex<Type> : int (const Type, const Type, const Type, const Type)
	template<class Type>
	static int MaxIndex(const Type x, const Type y, const Type z, const Type w) {
		return x > y ? (x > z ? (x > w ? 0 : 3) : (z > w ? 2 : 3)) : (y > z ? (y > w ? 1 : 3) : (z > w ? 2 : 3));
	}

	// cMath::MinIndex<Type> : int (const Type, const Type, const Type, const Type)
	template<class Type>
	static int MinIndex(const Type x, const Type y, const Type z, const Type w) {
		return x < y ? (x < z ? (x < w ? 0 : 3) : (z < w ? 2 : 3)) : (y < z ? (y < w ? 1 : 3) : (z < w ? 2 : 3));
	}

	// Max : (const Type *, ...)
	template<class Type>
	static Type Max(const Type *Values, const int Count) {
		if(Count <= 0) {
			return (Type)0;
		}
		Type v = Values[0];
		int i;
		for(i = 1; i < Count; i++) {
			v = Max(v, Values[i]);
		}
		return v;
	}

	// Min : (const Type *, ...)
	template<class Type>
	static Type Min(const Type *Values, const int Count) {
		if(Count <= 0) {
			return (Type)0;
		}
		Type v = Values[0];
		int i;
		for(i = 1; i < Count; i++) {
			v = Min(v, Values[i]);
		}
		return v;
	}
	
	// cMath::Clamp<Type> : Type(const Type, const Type, const Type)
	template<class Type>
	static Type Clamp(const Type x, const Type Lo, const Type Hi) {
		return Min(Max(x, Lo), Hi);
	}

	// cMath::Clamp<Type>
	template <typename Type>
	static void ClampRef(Type& value, const Type& low, const Type& high) {
		value = (value < low) ? low : ((value > high) ? high : value);
	}

	// cMath::ClampLow<Type>
	template <class Type>
	static void ClampLow(Type& value, const Type& low) {
		value = (value < low) ? low : value;
	}

	// cMath::ClampHigh<Type>
	template <typename Type>
	static void ClampHigh(Type& value, const Type& high) {
		value = (value > high) ? high : value;
	}

	// cMath::Hermite<Type> : const Type(const Type &, const Type &, const Type &, const Type &, const float)
	template<class Type>
	static const Type Hermite(const Type &p0, const Type &t0, const Type &p1, const Type &t1, const float s) {
		float s2 = s * s;
		float s3 = s * s2;
		
		float c0 = 2.0f * s3 - 3.0f * s2 + 1.0f;
		float d0 = s3 - 2.0f * s2 + s;
		float c1 = - 2.0f * s3 + 3.0f * s2;
		float d1 = s3 - s2;
		
		return c0 * p0 + d0 * t0 + c1 * p1 + d1 * t1;
	}

	// cMath::Hermite1stDerivative<Type> : const Type(const Type &, const Type &, const Type &, const Type &, const float)
	template<class Type>
	static const Type Hermite1stDerivative(const Type &p0, const Type &t0, const Type &p1, const Type &t1, const float s) {
		const float s2 = s * s;
		
		float c0 = 6.0f * s2 - 6.0f * s;
		float d0 = 3.0f * s2 - 4.0f * s + 1.0f;
		float c1 = - 6.0f * s2 + 6.0f * s;
		float d1 = 3.0f * s2 - 2.0f * s;
		
		return c0 * p0 + d0 * t0 + c1 * p1 + d1 * t1;
	}

	// cMath::Hermite2ndDerivative<Type> : const Type(const Type &, const Type &, const Type &, const Type &, const float)
	template<class Type>
	static const Type Hermite2ndDerivative(const Type &p0, const Type &t0, const Type &p1, const Type &t1, const float s) {
		float c0 = 12.0f * s - 6.0f;
		float d0 = 6.0f * s - 4.0f;
		float c1 = - 12.0f * s + 6.0f;
		float d1 = 6.0f * s - 2.0f;
		
		return c0 * p0 + d0 * t0 + c1 * p1 + d1 * t1;
	}

	// cMath::Hermite3rdDerivative<Type> : const Type(const Type &, const Type &, const Type &, const Type &, const float)
	template<class Type>
	static const Type Hermite3rdDerivative(const Type &p0, const Type &t0, const Type &p1, const Type &t1, const float s) {
		return 12.0f * p0 + 6.0f * t0 - 12.0f * p1 + 6.0f * t1;
	}

	static float TCBAdjInCoeff(const float tPrev, const float tCur, const float tNext);
	static float TCBAdjOutCoeff(const float tPrev, const float tCur, const float tNext);
	
	//---------------------------------------------------------------------------------------------------------
	// cMath::TCBSetup<Type>
	//---------------------------------------------------------------------------------------------------------
	template<class Type>
	static void TCBSetup(const Type &Prev, const Type &Cur, const Type &Next, Type &CurIn, Type &CurOut,
		const float Tension = 0.0f, const float Continuity = 0.0f, const float Bias = 0.0f) {
			const float Ai = (1.0f - Tension) * (1.0f - Continuity) * (1.0f + Bias);
			const float Ao = (1.0f - Tension) * (1.0f + Continuity) * (1.0f + Bias);
			const float Bi = (1.0f - Tension) * (1.0f + Continuity) * (1.0f - Bias);
			const float Bo = (1.0f - Tension) * (1.0f - Continuity) * (1.0f - Bias);
			const Type Di = Cur - Prev;
			const Type Do = Next - Cur;
			CurIn = Bi * (Next - Cur) + Ai * Di;
			CurOut = Ao * (Cur - Prev) + Bo * Do;
	} // cMath::TCBSetup<Type>

	//---------------------------------------------------------------------------------------------------------
	// cMath::TCBSetupTimeAdj<Type>
	//---------------------------------------------------------------------------------------------------------
	template<class Type>
	static void TCBSetupTimeAdj(const Type &Prev, const Type &Cur, const Type &Next, Type &CurIn, Type &CurOut,
		const float tPrev, const float tCur, const float tNext,
		const float Tension = 0.0f, const float Continuity = 0.0f, const float Bias = 0.0f) {
			TCBSetup(Prev, Cur, Next, CurIn, CurOut, Tension, Continuity, Bias);
			CurIn *= TCBAdjInCoeff(tPrev, tCur, tNext);
			CurOut *= TCBAdjOutCoeff(tPrev, tCur, tNext);
	} // cMath::TCBSetupTimeAdj<Type>

	// cMath::TCBSetupStartOut<Type>
	template<class Type>
	static const Type TCBSetupStartOut(const Type &Start, const Type &Next,
		const float Tension = 0.0f, const float Continuity = 0.0f, const float Bias = 0.0f) {
			return (1.0f - Tension) * (1.0f - Continuity) * (1.0f - Bias) * (Next - Start);
	}

	// cMath::TCBSetupEndIn<Type>
	template<class Type>
	static const Type TCBSetupEndIn(const Type &Prev, const Type &End,
		const float Tension = 0.0f, const float Continuity = 0.0f, const float Bias = 0.0f) {
			return (1.0f - Tension) * (1.0f - Continuity) * (1.0f + Bias) * (End - Prev);
	}
	
	// TCBSetupStartOutEndIn<Type>
	template<class Type>
	static const Type TCBSetupStartOutEndIn(const Type &Start, const Type &End, const float Tension = 0.0f) {
		return (End - Start) * (1.0f - Tension);
	}
	
	static int AlignToDword(const int i);

	static dword Checksum(const void *Src, const size_t Size);
	
	static word Float2Half(const float Float);
	static float Half2Float(const word Half);
	
	// b (byte, char)
	static void * EndianSwap2(void *Src, const int Count = 1); // w (word, short)
	static void * EndianSwap4(void *Src, const int Count = 1); // d (dword, int, float)
	static void * EndianSwap8(void *Src, const int Count = 1); // q (qword, double)
	static void * EndianSwap(void *Src, const char *Format, const int Count = 1);
	// Example:
	//	struct BmpInfoHeader {
	//		dword	Size;
	//		dword	Width;
	//		dword	Height;
	//		word	Planes;
	//		word	BitCount;
	//		dword	Compression;
	//		dword	SizeImage;
	//		byte	Junk0[8];
	//		dword	ClrUsed;
	//		byte	Junk1[4]; // ClrImportant = 4 bytes
	//	};
	// EndianSwap(&t, "3d2w2d8bd4b")
	// In array of structures you should consider alignment, because compiler inserts padding.
}; // cMath

// cMath::MulDiv
inline int cMath::MulDiv(int Number, int Numerator, int Denominator) {
	if (0 == Denominator) {
		return -1;
	}
	int n = Number < 0 ? -Number : Number;
	int N = Numerator < 0 ? -Numerator : Numerator;
	int d = Denominator < 0 ? -Denominator : Denominator;
	int t = (n * N + d / 2) / d;
	int s = Number ^ Numerator ^ Denominator;
	return s < 0 ? -t : t;
}

union cMath_DwordFloat {
	dword Dword;
	float Float;
};

union cMath_QwordDouble {
	qword Qword;
	double Double;
};

// cMath::IsPositiveInfinity : (const float)
inline bool cMath::IsPositiveInfinity(const float Value) {
	cMath_DwordFloat DF;
	DF.Float = Value;
	return (0x7f800000 == DF.Dword);
}

// cMath::IsNegativeInfinity : (const float)
inline bool cMath::IsNegativeInfinity(const float Value) {
	cMath_DwordFloat DF;
	DF.Float = Value;
	return (0xff800000 == DF.Dword);
}

// cMath::IsInfinity : (const float)
inline bool cMath::IsInfinity(const float Value) {
	return IsPositiveInfinity(Value) || IsNegativeInfinity(Value);
}

// cMath::Rad : float(float)
inline float cMath::Rad(float Deg) {
	return Deg * RadsPerDeg;
}

// cMath::Deg : float(float)
inline float cMath::Deg(float Rad) {
	return Rad * DegsPerRad;
}

// cMath::Rad : double(double)
inline double cMath::Rad(double Deg) {
	return Deg * RadsPerDeg;
}

// cMath::Deg : double(double)
inline double cMath::Deg(double Rad) {
	return Rad * DegsPerRad;
}

// cMath::Sec : float(float)
inline float cMath::Sec(float Ms) {
	return Ms * SecsPerMs;
}

// cMath::Ms : float(float)
inline float cMath::Ms(float Sec) {
	return Sec * MsPerSec;
}

// cMath::IsZero : bool(int)
inline bool cMath::IsZero(int n, int) {
	return (n == 0);
}

// cMath::IsZero : bool(const float, const float)
inline bool cMath::IsZero(const float f, const float Eps) {
	return Abs(f) <= Eps;
}

// cMath::IsOne : bool(const float, const float)
inline bool cMath::IsOne(const float f, const float Eps) {
	return Abs(f - 1.0f) <= Eps;
}

// cMath::IsOne : bool(const double, const float)
inline bool cMath::IsOne(const double f, const double Eps) {
	return Abs(f - 1.0) <= Eps;
}

// cMath::IsMinusOne
inline bool cMath::IsMinusOne(const float f, const float Eps) {
	return Abs(f + 1.0f) <= Eps;
}

// cMath::IsZeroToOneExact
inline bool cMath::IsZeroToOneExact(const float f) {
	return f >= 0.0f && f <= 1.0f;
}

// cMath::IsZeroToOneEps
inline bool cMath::IsZeroToOneEps(const float f, const float Eps) {
	return f >= - Eps && f <= 1.0f + Eps;
}

// cMath::IsInRange : bool(const int, const int, const int)
inline bool cMath::IsInRange(const int i, const int Lo, const int Hi) {
	return i >= Lo && i <= Hi;
}

// cMath::IsInRangeExact
inline bool cMath::IsInRangeExact(const float f, const float Lo, const float Hi) {
	return f >= Lo && f <= Hi;
}

// cMath::IsInRangeEps
inline bool cMath::IsInRangeEps(const float f, const float Lo, const float Hi, const float Eps) {
	return f >= Lo - Eps && f <= Hi + Eps;
}

// cMath::Equals : bool(const float, const float, const float)
inline bool cMath::Equals(const float x, const float y, const float Eps) {
	return Abs(x - y) <= Eps;
}

// cMath::IsValid : bool(const float)
inline bool cMath::IsValid(const float f) {
	return f >= -FloatMaxValue && f <= FloatMaxValue;
}
// cMath::IsValid : bool(const float)
inline bool cMath::IsValid(const double f) {
	return f >= -DoubleMaxValue && f <= DoubleMaxValue;
}

// cMath::IsZero : bool(const double, const double)
inline bool cMath::IsZero(const double d, const double Eps) {
	return Abs(d) <= Eps;
}

// cMath::Equals : bool(const double, const double, const double)
inline bool cMath::Equals(const double x, const double y, const double Eps) {
	return Abs(x - y) <= Eps;
}

// cMath::Clamp01 : float(const float)
inline float cMath::Clamp01(const float s) {
	return s < 0.0f ? 0.0f : (s > 1.0f ? 1.0f : s);
}

// cMath::ClampRange1 : float(const float)
inline float cMath::ClampRange1(const float s) {
	return s < -1.0f ? -1.0f : (s > 1.0f ? 1.0f : s);
}

// cMath::ClampRange
inline float cMath::ClampRange(const float s, const float l) {
	return s < -l ? -l : (s > l ? l : s);
}

// cMath::Lerp : float(const float, const float, const float)
inline float cMath::Lerp(const float a, const float b, const float s) {
	return a + s * (b - a);
}

// cMath::Cerp
inline float cMath::Cerp(const float a, const float b, const float s) {
	float t = s * Pi;
	float l = (1.0f - Cos(t)) * 0.5f;
	return a * (1.0f - l) + b * l;
}

// cMath::Lerp05
inline float cMath::Lerp05(const float a, const float b) {
	return 0.5f * (a + b);
}

// cMath::Lerper : float(const float, const float, const float)
inline float cMath::Lerper(const float Fm, const float To, const float x) {
	return (x - Fm) / (To - Fm);
}

// cMath::LerperClamp01 : float(const float, const float, const float)
inline float cMath::LerperClamp01(const float Lo, const float Hi, const float x) {
	return Clamp01((x - Lo) / (Hi - Lo));
}

// cMath::MidPointLerp
inline float cMath::MidPointLerp(const float Start, const float Mid, const float End, const float s) {
	if(s < 0.5f) {
		return Lerp(Start, Mid, 2.0f * s);
	}
	return Lerp(Mid, End, 2.0f * (s - 0.5f));
}

// cMath::Abs : int(int)
inline int cMath::Abs(int n) {
	int s = n >> 31;
	return (n ^ s) - s;
}

union IntFloat {
    int i;
    float f;
};

// cMath::Abs : float(float)
inline float cMath::Abs(float f) {
    IntFloat u;
    u.f = f;
    u.i &= 0x7fffffff;
    return u.f;
}

// cMath::Abs : double(double)
inline double cMath::Abs(double d) {
	return fabs(d);
}

// cMath::Round : float(float)
inline float cMath::Round(float x) {
	return floorf(x + 0.5f);
}

// cMath::Round : float(double)
inline double cMath::Round(double x) {
	return floor(x + 0.5);
}

// cMath::Round : float(float)
template<typename Type>
inline Type cMath::Round(float x) {
	return static_cast< Type >( floorf(x + 0.5f) );
}

// cMath::Sqrt : float(float)
inline float cMath::Sqrt(float x) {
	return sqrtf(x);
}

// cMath::SqrtD : float(float)
inline double cMath::Sqrt(double x) {
	return sqrt(x);
}

// cMath::FastInvSqrt
inline float cMath::FastInvSqrt(float x) {
	union {
		float FloatI;
		int i;
	};
	float h = 0.5f * x;
	FloatI = x;
	i = 0x5f3759df - (i >> 1);
	x = FloatI;
	return x * (1.5f - h * x * x);
}

// cMath::FastSqrt
inline float cMath::FastSqrt(float x) {
	union {
		int tmp;
		float val;
	} u;
	u.val = x;
	u.tmp -= 1<<23; // Remove last bit so 1.0 gives 1.0
	// tmp is now an approximation to logbase2(val)
	u.tmp >>= 1; // divide by 2
	u.tmp += 1<<29; // add 64 to exponent: (e+127)/2 =(e/2)+63,
	// that represents (e/2)-64 but want e/2
	return u.val;
}

// cMath::Sin : float(float)
inline float cMath::Sin(float a) {
	return sinf(a);
}

// cMath::Sin : double(double)
inline double cMath::Sin(double a) {
	return sin(a);
}

// cMath::Cos : double(double)
inline double cMath::Cos(double a) {
	return cos(a);
}

// cMath::Cos : float(float)
inline float cMath::Cos(float a) {
	return cosf(a);
}

// cMath::SinCos : void(float, float &, float &)
inline void cMath::SinCos(float Angle, float &S, float &C) {
	S = Sin(Angle);
	C = Cos(Angle);
}

// cMath::SinCos : void(double, double &, double &)
inline void cMath::SinCos(double Angle, double &S, double &C) {
	S = Sin(Angle);
	C = Cos(Angle);
}

// cMath::Tan : double(double)
inline double cMath::Tan(double a) {
	return tan(a);
}

// cMath::Tan : float(float)
inline float cMath::Tan(float a) {
	return tanf(a);
}

// cMath::ASin : float(float)
inline float cMath::ASin(float x) {
	if(x <= -1.0f) {
		return - HalfPi;
	}
	if(x >= 1.0f) {
		return HalfPi;
	}
	return asinf(x);
}

// cMath::ASin : double(double)
inline double cMath::ASin(double x) {
	if (x <= -1.0) {
		return -HalfPi;
	}
	if (x >= 1.0) {
		return HalfPi;
	}
	return asin(x);
}

// cMath::ACos : float(float)
inline float cMath::ACos(float x) {
	if(x <= -1.0f) {
		return Pi;
	}
	if(x >= 1.0f) {
		return 0.0f;
	}
	return acosf(x);
}

// cMath::ACos : double(double)
inline double cMath::ACos(double x) {
	if (x <= -1.0) {
		return Pi;
	}
	if (x >= 1.0) {
		return 0.0f;
	}
	return acos(x);
}

// cMath::ATan : float(float)
inline float cMath::ATan(float a) {
	return atanf(a);
}

// cMath::ATan : double(double)
inline double cMath::ATan(double a) {
	return atan(a);
}

// cMath::ATan : float(float, float)
inline float cMath::ATan(float y, float x) {
	return atan2f(y, x);
}

// cMath::ATan : double(double, double)
inline double cMath::ATan(double y, double x) {
	return atan2(y, x);
}

// cMath::Pow : float(float, float)
inline float cMath::Pow(float x, float y) {
	return powf(x, y);
}

// cMath::Pow : double(double, double)
inline double cMath::Pow(double x, double y) {
	return pow(x, y);
}

// cMath::Exp : float(float)
inline float cMath::Exp(float x) {
	return expf(x);
}

// cMath::Exp : double(double)
inline double cMath::Exp(double x) {
	return exp(x);
}

// cMath::Ldexp
inline float cMath::Ldexp(const float x, const int exp) {
	return ldexpf(x, exp);
}

// cMath::Ldexp
inline double cMath::Ldexp(const double x, const int exp) {
	return ldexp(x, exp);
}

// cMath::Frexp
inline float cMath::Frexp(const float x, int *exp) {
	return frexpf(x, exp);
}

// cMath::Frexp
inline double cMath::Frexp(const double x, int *exp) {
	return frexp(x, exp);
}

// cMath::Log : float(float)
inline float cMath::Log(float x) {
	return logf(x);
}

// cMath::Log : float(float)
inline double cMath::Log(double x) {
	return log(x);
}

// cMath::Floor : float
inline float cMath::Floor(const float f) {
	return floorf(f);
}

// cMath::Floor : float
inline double cMath::Floor(const double f) {
	return floor(f);
}

// cMath::Ceil : float
inline float cMath::Ceil(const float f) {
	return ceilf(f);
}

// cMath::Ceil : double
inline double cMath::Ceil(const double f) {
	return ceil(f);
}

// cMath::Frac : float
inline float cMath::Frac(const float f) {
	return f - floorf(f);
}

// cMath::Frac : float
inline double cMath::Frac(const double f) {
	return f - floor(f);
}

// cMath::Periodic : float(const float, const float, const float, int *)
inline float cMath::Periodic(const float f, const float Lo, const float Hi, int *nPeriods) {
	const float Range = Hi - Lo;
	if(Range == 0.0f) {
		if(nPeriods) {
			*nPeriods = 0;
			return Lo;
		}
	}

	float u = f - Range * (float)cMath::Floor((double)(f - Lo) / Range);
	if(nPeriods) {
		*nPeriods = -(int)((u - f) / Range + (u > f ? 0.5f : -0.5f));
	}
	return u;
}

//----------------------------------------------------------------------------------------------------------
// cMath::IndexForInsert
//----------------------------------------------------------------------------------------------------------
inline int cMath::IndexForInsert(const float f, const float *Array, const int nCount, const size_t Stride) {
	const size_t S = cMath::Max(sizeof(float), Stride);
	const char *Ptr = reinterpret_cast<const char *>(Array);
	int N = nCount;
	int Mid = N;
	int Offset = 0, Res = 0;
	while(Mid > 0) {
		Mid = N >> 1;
		if(f == *reinterpret_cast<const float *>(Ptr + S * (Offset + Mid))) {
			return Offset + Mid;
		} else if(f > *reinterpret_cast<const float *>(Ptr + S * (Offset + Mid))) {
			Offset += Mid;
			N -= Mid;
			Res = 1;
		} else {
			N -= Mid;
			Res = 0;
		}
	}
	return Offset + Res;
}

// cMath::AngleNormalizeTwoPi : float(float)
inline float cMath::AngleNormalizeTwoPi(float Angle) { // 0 <= Angle < TwoPi
	if(Angle >= TwoPi || Angle < 0.0f) {
		Angle -= floorf(Angle / TwoPi) * TwoPi;
	}
	return Angle;
}

// cMath::AngleNormalizeTwoPi : double(double)
inline double cMath::AngleNormalizeTwoPi(double Angle) { // 0 <= Angle < TwoPi
	if (Angle >= TwoPi || Angle < 0.0) {
		Angle -= floor(Angle / TwoPi) * TwoPi;
	}
	return Angle;
}

// cMath::AngleNormalizePi : float(float)
inline float cMath::AngleNormalizePi(float Angle) { // - Pi < Angle <= Pi
	Angle = AngleNormalizeTwoPi(Angle);
	if(Angle > Pi) {
		Angle -= TwoPi;
	}
	return Angle;
}

// cMath::AngleNormalize360 : float(float)
inline float cMath::AngleNormalize360(float Angle) {
	if(Angle >= 360.0f || Angle < 0.0f) {
		Angle -= floorf(Angle / 360.0f) * 360.0f;
	}
	return Angle;
}

// cMath::AngleNormalize180 : float(float)
inline float cMath::AngleNormalize180(float Angle) {
	Angle = AngleNormalize360(Angle);
	if(Angle > 180.0f) {
		Angle -= 360.0f;
	}
	return Angle;
}

// cMath::AngleEnsureShortestPath180
inline void cMath::AngleEnsureShortestPath180(float *Alpha, float *Beta) {
	*Alpha = AngleNormalize180(*Alpha);
	*Beta = AngleNormalize180(*Beta);
	*Beta = *Alpha + AngleNormalize180(*Beta - *Alpha);
}

// cMath::AngleDeltaDeg : float(float, float)
inline float cMath::AngleDeltaDeg(float Alpha, float Beta) {
	return AngleNormalize180(Alpha - Beta);
}

// cMath::AngleLerpDeg : float(float, float, float)
inline float cMath::AngleLerpDeg(float Alpha, float Beta, float s) {
	while(Alpha > Beta + 180.0f) {
		Alpha -= 360.0f;
	}
	while(Alpha < Beta - 180.0f) {
		Alpha += 360.0f;
	}
	return Lerp(Alpha, Beta, s);
}


// cMath::AngleDeltaRad : float(float, float)
inline float cMath::AngleDeltaRad(float Alpha, float Beta) {
	return AngleNormalizePi(Alpha - Beta);
}

// cMath::AngleLerpRad : float(float, float, float)
inline float cMath::AngleLerpRad(float Alpha, float Beta, float s) {
	while(Alpha > Beta + Pi) {
		Alpha -= TwoPi;
	}
	while(Alpha < Beta - Pi) {
		Alpha += TwoPi;
	}
	return Lerp(Alpha, Beta, s);
}

// cMath::ClosestPowerOfTwo
inline int cMath::ClosestPowerOfTwo(const int X) {
	cAssert(X > 0);
	int p = 1;
	while(p < X) {
		p += p;
	}
	if(4 * X < 3 * p) {
		p >>= 1;
	}
	return p;
}

// cMath::UpperPowerOfTwo
inline int cMath::UpperPowerOfTwo(const int X) {
	int p = 1;
	while(p < X) {
		p += p;
	}
	return p;
}

// cMath::LowerPowerOfTwo
inline int cMath::LowerPowerOfTwo(const int X) {
	int p = 1;
	while(p <= X) {
		p += p;
	}
	return p >> 1;
}
	
// cMath::IsPowerOfTwo : bool(int)
inline bool cMath::IsPowerOfTwo(const int X) {
	return (X & (X - 1)) == 0 && X > 0;
}

// cMath::Rand : float(const float, const float)
inline float cMath::Rand(const float Lo, const float Hi) {
	return Lo + Rand01() * (Hi - Lo);
}

// cMath::fRand : double(const float, const float)
inline double cMath::dRand(const double Lo, const double Hi) {
	return Lo + (double)Rand01() * (Hi - Lo);
}

// cMath::Rand : int (const int, const int)
inline int cMath::Rand(const int Lo, const int Hi) {
	return (int)cMath::Floor(Rand((float)Lo, (float)Hi) + 0.5f);
}

// cMath::SignBitSet
inline int cMath::SignBitSet(const int i) {
	return ((const dword)(i)) >> 31;
}

// cMath::SignBitNotSet
inline int cMath::SignBitNotSet(const int i) {
	return (~((const dword)(i))) >> 31;
}

// cMath::TCBAdjInCoeff
inline float cMath::TCBAdjInCoeff(const float tPrev, const float tCur, const float tNext) {
	return (tCur - tPrev) / (tNext - tPrev);
}

// cMath::TCBAdjOutCoeff
inline float cMath::TCBAdjOutCoeff(const float tPrev, const float tCur, const float tNext) {
	return (tNext - tCur) / (tNext - tPrev);
}

// cMath::AlignToDword
inline int cMath::AlignToDword(const int i) {
	const int Delta = i & 3;
	return Delta == 0 ? i : i + 4 - Delta;
}
