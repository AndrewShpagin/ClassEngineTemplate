// Template.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <functional>
#include <mutex>
#include "comms-Math/comms-Math.h"
#include "ClassEngine/classengine.h"

class Tt:public BaseClass {
public:
	void test() {
		
	}
	int Xx;
	SERIALIZE() {
		REG_AUTO(Xx);
		FUNCTION_CALL(test);
	}
};

int main()
{
	TagsList T;
	T.AddSubTag("tag", "tag");
	Tt X;
	X.Save(T, &X);
	comms::cStr s;
	T.PutTagsIntoString(&s);
    std::cout << s << "\n";
}

#include "ClassEngine/implementation.h"