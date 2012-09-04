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

class SearchParameters {
	public:
		SearchParameters();
		void load(int argc, char** argv);

		int skin() const;
		int eyes() const;

	private:
		int skinParam, eyesParam;
};

#endif /* SEARCHPARAMETERS_H_ */
