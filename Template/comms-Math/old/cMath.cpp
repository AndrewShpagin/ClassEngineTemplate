#include "comms-Math.h"

namespace comms {

const float cMath::Pi			= 3.14159265358979323846f;
const float cMath::TwoPi		= 2.0f * cMath::Pi;
const float cMath::HalfPi		= 0.5f * cMath::Pi;
const float cMath::QuarterPi	= 0.25f * cMath::Pi;

const float cMath::RadsPerDeg = cMath::Pi / 180.0f;
const float cMath::DegsPerRad = 180.0f / cMath::Pi;

const float cMath::SecsPerMs = 0.001f;
const float cMath::MsPerSec = 1000.0f;

const float cMath::Epsilon = 0.001f;
const float cMath::EpsilonSq = cMath::Epsilon * cMath::Epsilon;
const float cMath::SpaceEpsilon = 0.1f;

const float cMath::MatrixEpsilon = 1e-6f;
const float cMath::MatrixInvertEpsilon = 1e-14f;
const double cMath::dMatrixInvertEpsilon = 1e-24f;

const double cMath::dEpsilon = 1.0e-6;

const float cMath::Sqrt1Over2 = 0.70710678118654752440f;
const float cMath::Sqrt1Over3 = 0.57735026918962576450f;

const double cMath::DoubleMinValue = double(2.2250738585072014e-308);
const double cMath::DoubleMaxValue = double(1.7976931348623158e+308);

const float cMath::FloatMaxValue = 3.402823466e+38f;
const float cMath::FloatMinValue = 1.175494351e-38f;

const int cMath::IntMinValue = int(0x80000000);
const int cMath::IntMaxValue = int(0x7fffffff);

static dword s_RandSeed = 0;
static const dword IEEE_ONE = 0x3f800000;
static const dword IEEE_MASK = 0x007fffff;

// cMath::Randomize
void cMath::Randomize(const dword Seed) {
	s_RandSeed = Seed;
}

union DwordFloat {
    dword d;
    float f;
};

// cMath::Rand01
float cMath::Rand01() { // [0.0f, 1.0f]
    s_RandSeed = 1664525L * s_RandSeed + 1013904223L;
    DwordFloat u;
    u.d = IEEE_ONE | (s_RandSeed & IEEE_MASK);
    return (u.f - 1.0f);
}

// cMath::RandRange1
float cMath::RandRange1() { // [-1.0f, 1.0f]
    s_RandSeed = 1664525L * s_RandSeed + 1013904223L;
    DwordFloat u;
    u.d = IEEE_ONE | (s_RandSeed & IEEE_MASK);
    return (2.0f * u.f - 3.0f);
}

//-----------------------------------------------------------------------------
// cMath::Checksum
//-----------------------------------------------------------------------------
dword cMath::Checksum(const void *Src, const size_t Size) {
	static const dword StartValue = 0xffffffff;
	static const dword XorValue = 0xffffffff;
	static const dword MagicNumber = 0xdebb20e3;
	static cList<dword> Table;
	
	int i, j;
	dword c, CrcValue;
	const byte *Bytes = (const byte *)Src;

	// Fill table of Crc32's for single - byte values using magic number during first call
	if(Table.IsEmpty()) {
		for(i = 0; i < 256; i++) {
			c = (dword)i;
			for(j = 0; j < 8; j++) {
				c = (c & 1) ? MagicNumber ^ (c >> 1) : (c >> 1);
			}
			Table.Add(c);
		}
	}
	
	// Start
	CrcValue = StartValue;

	// Update
	for(i = 0; i < (int)Size; i++) {
		c = Bytes[i];
		CrcValue = Table[(CrcValue ^ c) & 0xff] ^ (CrcValue >> 8);
	}

	// End
	CrcValue ^= XorValue;

	return CrcValue;
} // cMath::Checksum

//-----------------------------------------------------------------------------
// cMath::Float2Half
//-----------------------------------------------------------------------------
word cMath::Float2Half(const float Float) {
	union {
		float FloatI;
		dword i;
	};
	
	FloatI = Float;
	int e = ((i >> 23) & 0xff) - 112;
	int m = i & 0x007fffff;

	word Half = (word)((i >> 16) & 0x8000);
	if(e <= 0) {
		// Denorm
		m = ((m | 0x00800000) >> (1 - e)) + 0x1000;
		Half |= (m >> 13);
	} else if(143 == e) {
		Half |= 0x7c00;
		if(m != 0) {
			// NaN
			m >>= 13;
			Half |= m | (0 == m);
		}
	} else {
		m += 0x1000;
		if(m & 0x00800000) {
			// Mantissa overflow
			m = 0;
			e++;
		}
		if(e >= 31) {
			// Exponent overflow
			Half |= 0x7c00;
		} else {
			Half |= (e << 10) | (m >> 13);
		}
	}
	return Half;
} // cMath::Float2Half

//-----------------------------------------------------------------------------
// cMath::Half2Float
//-----------------------------------------------------------------------------
float cMath::Half2Float(const word Half) {
	union {
		dword s;
		float F;
	};

	s = (Half & 0x8000) << 16;
	dword e = (Half >> 10) & 0x1f;
	dword m = Half & 0x03ff;

	if(0 == e) {
		// +/- 0
		if(0 == m) {
			return F;
		}

		// Denorm
		while((m & 0x0400) == 0) {
			m += m;
			e--;
		}
		e++;
		m &= ~0x0400;
	} else if(31 == e) {
		// Inf / NaN
		s |= 0x7f800000 | (m << 13);
		return F;
	}
	s |= ((e + 112) << 23) | (m << 13);
	return F;
} // cMath::Half2Float

//-----------------------------------------------------------------------------
// cRandom
//-----------------------------------------------------------------------------
class cRandom {
public:
	cRandom() {
		m_Seed = 0;
	}
	void SetSeed(const dword Seed) {
		m_Seed = Seed;
	}
	float Rand01() { // [0.0f, 1.0f]
		m_Seed = 1664525L * m_Seed + 1013904223L;
		cMath_DwordFloat df;
		df.Dword = IEEE_ONE | (m_Seed & IEEE_MASK);
		return (df.Float - 1.0f);
	}
	float RandRange1() { // [-1.0f, 1.0f]
		m_Seed = 1664525L * m_Seed + 1013904223L;
		cMath_DwordFloat df;
		df.Dword = IEEE_ONE | (m_Seed & IEEE_MASK);
		return (2.0f * df.Float - 3.0f);
	}
private:
	dword m_Seed;

	static const dword IEEE_ONE = 0x3f800000;
	static const dword IEEE_MASK = 0x007fffff;
};


// cMath::EndianSwap2
void * cMath::EndianSwap2(void *Src, const int Count) {
	word *Ptr = (word *)Src;
	int i;
	for(i = 0; i < Count; i++) {
		byte *b = (byte *)Ptr;
		cMath::Swap(b[0], b[1]);
		Ptr++;
	}
	return Ptr;
}

// cMath::EndianSwap4
void * cMath::EndianSwap4(void *Src, const int Count) {
	dword *Ptr = (dword *)Src;
	int i;
	for(i = 0; i < Count; i++) {
		byte *b = (byte *)Ptr;
		cMath::Swap(b[0], b[3]);
		cMath::Swap(b[1], b[2]);
		Ptr++;
	}
	return Ptr;
}

// cMath::EndianSwap8
void * cMath::EndianSwap8(void *Src, const int Count) {
	qword *Ptr = (qword *)Src;
	int i;
	for(i = 0; i < Count; i++) {
		byte *b = (byte *)Ptr;
		cMath::Swap(b[0], b[7]);
		cMath::Swap(b[1], b[6]);
		cMath::Swap(b[2], b[5]);
		cMath::Swap(b[3], b[4]);
		Ptr++;
	}
	return Ptr;
}

// EndianSwap_Size
static size_t EndianSwap_Size(const char c) {
	if('b' == c) {
		return 1;
	} else if('w' == c) {
		return 2;
	} else if('d' == c) {
		return 4;
	} else if('q' == c) {
		return 8;
	} else {
		cAssert(0);
		return 0;
	}
}

//-----------------------------------------------------------------------------
// cMath::EndianSwap
//-----------------------------------------------------------------------------
void * cMath::EndianSwap(void *Src, const char *Format, const int Count) {
	cAssert(Format != NULL);
	if(NULL == Format) {
		return Src;
	}
	// Decode format
	cStr F;
	const char *c = Format;
	int r;
	size_t S = 0;
	while(*c != '\0') {
		r = 1;
		if(cStr::CharIsNumeric(*c)) {
			r = 0;
			while(cStr::CharIsNumeric(*c)) {
				r = 10 * r + (*c - '0');
				c++;
			}
			if('\0' == *c) {
				break;
			}
		}
		F.Append(*c, r);
		S += EndianSwap_Size(*c) * r;
		c++;
	}
	// Swap
	int i, j;
	char t;
	for(i = 0; i < Count; i++) {
		for(j = 0; j < F.Length(); j++) {
			t = F[j];
			if('b' == t) {
				Src = (byte *)Src + 1;
			} else if('w' == t) {
				Src = EndianSwap2(Src, 1);
			} else if('d' == t) {
				Src = EndianSwap4(Src, 1);
			} else if('q' == t) {
				Src = EndianSwap8(Src, 1);
			} else {
				cAssert(0);
			}
		}
	}
	return Src;
} // cMath::EndianSwap

} // comms
