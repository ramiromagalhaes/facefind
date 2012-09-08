//============================================================================
// Name        : facefind.cpp
// Author      : Ramiro Pereira de Magalhães <ramiro.p.magalhaes@gmail.com>
// Version     :
// Copyright   : 
// Description : ...
//============================================================================

#include <iostream>

#include <imgproc/imgproc.hpp>
#include <highgui/highgui.hpp>

#include "ArgsParser.h"
#include "ProgramParameters.h"
#include "FaceClassifier.h"

using namespace std;

int main(int argc, char** argv) {

	try {
		ArgsParser parser;
		parser.parse(argc, argv)->execute();
	} catch (int error) { //TODO wtf should I catch?
		return error;
	}

	return 0;
}
