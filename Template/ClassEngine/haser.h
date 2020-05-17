#pragma once

#include <cmath>
//#pragma STDC FENV_ACCESS ON
#define  __3dcoat___

class BaseClass;

/** Uncomment the HASHDEBUG if you want to find the reason why hash changes when it should not.
 *\details In this case HashSummator will gather history of hash changes in HashSummator::History.
 *You may find on what step hash starts to differ from the previous one. Then you should set breakpoint
 *in the HashSummator::_add(const double& d) and stop when History reaches the reuired count.
 *You will see the reason of changes in the callstack.
 */

//#define HASHDEBUG

/**
 * \brief The class used to calculate hash value over the any type. Usually it is used to check if some structure state changed.\n
 * \details
 * The main properties:\n
 * 1) Small changes of input parameters lead to the small change of the hash value.\n
 * 2) It may not be directly casted to any other type (for safety), you may add values and compare if it is same or different from other hash summ.\n
 * HashSummator::ToDouble() generally converts hash to the double value. It may be used for low space cost of hash storing.\n
 * \n
 * Example:\n
 * \code
 * HashStorage H;
 * H.add(1,2.0,"string);
 * H << 23 << x;
 * if(H != OldHash){
 *	//... hash changed, do something ...
 *	OldHash = H;
 * }
 * \endcode
 */
class HashSummator {
	const double clampval = 2097152.0;
	double Value;
	double coef;
	bool Structure;
	bool Values;
	void _add(const double& d);
	void _struct(const void* ptr, int type);
#ifdef HASHDEBUG
	comms::cList<double> History;
#endif
public:

	HashSummator(bool Structural = false, bool CalculateValues = true);
	HashSummator(double H);
	HashSummator(const HashSummator& H);
	bool& Structural() {
		return Structure;
	}
	
	//template<typename T, typename... Args>
	//HashSummator(T first, Args... args);

	void operator = (const HashSummator& H);
	bool operator == (const HashSummator& H);
	bool operator != (const HashSummator& H);

	bool SameAs(const HashSummator& other, double epsilon = 0.0001);
	bool Differs(const HashSummator& other, double epsilon = 0.0001);
	void Clear();
	double ToDouble();
	bool Untouched();


	void operator += (const char* value);
	void operator += (const HashSummator& value);
	void operator += (const int& value);
	void operator += (const float& value);
	void operator += (const double& value);
	void operator += (const bool& value);
	void operator += (const char& value);
	void operator += (const unsigned char& value);
	void operator += (const DWORD& value);
#ifdef __3dcoat___
	void operator += (const comms::cVec2& value);
	void operator += (const comms::cVec3& value);
	void operator += (const comms::cVec4& value);
	void operator += (const comms::cMat3& value);
	void operator += (const comms::cMat4& value);
	void operator += (const comms::dVec2& value);
	void operator += (const comms::dVec3& value);
	void operator += (const comms::dVec4& value);
	void operator += (const comms::dMat3& value);
	void operator += (const comms::dMat4& value);
	void operator += (const cPtrDiff& value);
	void operator += (BaseClass* value);

#endif //__3dcoat___

	template <class type> HashSummator& operator << (const type& value);
	//template <class type> void operator +=(const type& v);
	
	template<typename t1>
	void add(const t1& v1);
	template<typename T, typename... Args>
	void add(T first, Args... args);
	void add(){}

};
inline HashSummator::HashSummator(bool Structural, bool Val) {
	Value = 0;
	coef = 1.0;
	Structure = Structural;
	Values = Val;
}

inline HashSummator::HashSummator(double H) : HashSummator() {
	Value = H;
#ifdef HASHDEBUG
	History.Clear();
	History.Add(H);
#endif
}

inline HashSummator::HashSummator(const HashSummator& H) {
	Value = H.Value;
	coef = H.coef;
	Structure = H.Structure;
	Values = H.Values;
#ifdef HASHDEBUG
	History.Clear();
	History = H.History;
#endif
}

inline void HashSummator::operator=(const HashSummator& H) {
	Value = H.Value;
	coef = H.coef;
	Structure = H.Structure;
	Values = H.Values;
#ifdef HASHDEBUG
	History.Clear();
	History = H.History;
#endif
}

inline bool HashSummator::operator==(const HashSummator& H) {
	return SameAs(H);
}

inline bool HashSummator::operator!=(const HashSummator& H) {
	return Differs(H);
}

inline bool HashSummator::SameAs(const HashSummator& other, double epsilon) {
	return std::abs(std::remainder(Value - other.Value, clampval)) < epsilon;
}

inline bool HashSummator::Differs(const HashSummator& other, double epsilon) {
	return !SameAs(other, epsilon);
}

inline void HashSummator::Clear() {
	Value = 0;
	coef = 1.0;
#ifdef HASHDEBUG
	History.Clear();
#endif
}

inline double HashSummator::ToDouble() {
	return Value;
}

inline bool HashSummator::Untouched() {
	return Value == 0.0;
}

inline void HashSummator::_add(const double& d) {
	if (std::isnormal(d)) {
		Value = std::fma(std::fabs(d) + d * 0.5, coef, Value);
	}
	coef = 2.0 + std::cos(coef*16.0f);
	if (Value > clampval) {
		Value -= clampval * std::floor(Value / clampval);
	}
#ifdef HASHDEBUG
	History.Add(Value);
#endif
}

inline void HashSummator::_struct(const void* ptr, int type) {
	if (Structure) {
		_add(double(cPtrDiff(ptr) & 0xFFFF));
		_add(type);
	}
}

//template <typename T, typename ... Args>
//HashSummator::HashSummator(T first, Args... args) {
//	//(*this) += first;
//	add(first, args...);
//}


template <class type>
HashSummator& HashSummator::operator<<(const type& value) {
	(*this) += value;
	return *this;
}

//template <class type>
//void HashSummator::operator+=(const type& v) {
//	_add(double(v));
//}

template <typename t1>
void HashSummator::add(const t1& v1) {
	operator += (v1);
}

template <typename T, typename ... Args>
void HashSummator::add(T first, Args... args) {
	operator += (first);
	add(args...);
}

inline void HashSummator::operator+=(const HashSummator& value) {
	_add(value.Value);
}

inline void HashSummator::operator+=(const int& value) {
	_struct(&value, 100);
	if (Values) {
		_add(double(value));
	}
}

inline void HashSummator::operator+=(const float& value) {
	_struct(&value, 101);
	if (Values) {
		_add(double(value));
	}
}

inline void HashSummator::operator+=(const double& value) {
	_struct(&value, 102);
	if (Values) {
		_add(value);
	}
}

inline void HashSummator::operator += (const bool& value) {
	_struct(&value, 103);
	if (Values) {
		_add(double(value));
	}
}

inline void HashSummator::operator += (const char& value) {
	_struct(&value, 104);
	if (Values) {
		_add(double(value));
	}
}

inline void HashSummator::operator += (const unsigned char& value) {
	_struct(&value, 105);
	if (Values) {
		_add(double(value));
	}
}

inline void HashSummator::operator += (const DWORD& value) {
	_struct(&value, 106);
	if (Values) {
		unsigned char* ps = (unsigned char*)& value;
		*this << ps[0] << ps[1] << ps[2] << ps[3];
	}
}

inline void HashSummator::operator+=(const char* value) {
	_struct(&value, 107);
	if (Values) {
		if (value) {
			for (int i = 0; value[i]; i++)_add(double(value[i]));
		}
	}
}


#ifdef __3dcoat___

inline void HashSummator::operator+=(const comms::cVec2& value) {
	_struct(&value, 3);
	if (Values) {
		_add(double(value.x));
		_add(double(value.y));
	}
}

inline void HashSummator::operator+=(const comms::cVec3& value) {
	_struct(&value, 4);
	if (Values) {
		_add(double(value.x));
		_add(double(value.y));
		_add(double(value.z));
	}
}

inline void HashSummator::operator+=(const comms::cVec4& value) {
	_struct(&value, 5);
	if (Values) {
		_add(double(value.x));
		_add(double(value.y));
		_add(double(value.z));
		_add(double(value.w));
	}
}

inline void HashSummator::operator+=(const comms::cMat3& value) {
	_struct(&value, 6);
	if (Values) {
		(*this) += value.GetRow(0);
		(*this) += value.GetRow(1);
		(*this) += value.GetRow(2);
	}
}

inline void HashSummator::operator+=(const comms::cMat4& value) {
	_struct(&value, 7);
	if (Values) {
		(*this) += value.GetRow(0);
		(*this) += value.GetRow(1);
		(*this) += value.GetRow(2);
		(*this) += value.GetRow(3);
	}
}

inline void HashSummator::operator+=(const comms::dVec2& value) {
	_struct(&value, 8);
	if (Values) {
		_add(double(value.x));
		_add(double(value.y));
	}
}

inline void HashSummator::operator+=(const comms::dVec3& value) {
	_struct(&value, 9);
	if (Values) {
		_add(double(value.x));
		_add(double(value.y));
		_add(double(value.z));
	}
}

inline void HashSummator::operator+=(const comms::dVec4& value) {
	_struct(&value, 10);
	if (Values) {
		_add(double(value.x));
		_add(double(value.y));
		_add(double(value.z));
		_add(double(value.w));
	}
}
inline void HashSummator::operator+=(const comms::dMat3& value) {
	_struct(&value, 11);
	if (Values) {
		(*this) += value.GetRow(0);
		(*this) += value.GetRow(1);
		(*this) += value.GetRow(2);
	}
}


inline void HashSummator::operator+=(const comms::dMat4& value) {
	_struct(&value, 11);
	if (Values) {
		(*this) += value.GetRow(0);
		(*this) += value.GetRow(1);
		(*this) += value.GetRow(2);
		(*this) += value.GetRow(3);
	}
}

inline void HashSummator::operator+=(const cPtrDiff& value) {
	_struct(&value, 12);
	if (Values) {
		_add(double(value & 0xFFFFF));
	}
}

#endif //__3dcoat___


