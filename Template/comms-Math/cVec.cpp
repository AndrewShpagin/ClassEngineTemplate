#include "comms-Math.h"

// @test
#if 0
#include "stdafx.h"
#include <iostream>
#include <fstream>
void doCVecAndExit() {
	// redirect output to the file
	const comms::cStr  testFile = "test.doCVecAndExit.log";
	FILE*  file = freopen( testFile.ToCharPtr(), "w", stdout );
	assert( file );

	// test output
	typedef comms::cVec< int, 4 >  node_t;
	node_t  node( 1, -2, 3, -4 );
	std::cout << node;

	exit( 0 );
}

CallItLater  startCVec( &doCVecAndExit, BASIC_TOOL );
#endif
