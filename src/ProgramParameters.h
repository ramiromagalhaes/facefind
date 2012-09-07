/*
 * SearchParameters.h
 *
 *  Created on: 03/09/2012
 *      Author: ramiro
 */

#ifndef SEARCHPARAMETERS_H_
#define SEARCHPARAMETERS_H_

#include <iostream>
#include <boost/program_options.hpp>

using namespace std;
namespace po = boost::program_options;

class ProgramParameters {
	public:
		string imgpath, dbpath;
		int searchParam; //0 = white, 3 = tanned, 5 = black
};

#endif /* SEARCHPARAMETERS_H_ */
