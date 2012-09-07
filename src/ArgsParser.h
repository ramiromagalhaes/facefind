/*
 * ArgsParser.h
 *
 *  Created on: 07/09/2012
 *      Author: ramiro
 */

#ifndef COMMANDLINEPARSER_H_
#define COMMANDLINEPARSER_H_

#include <boost/program_options.hpp>

#include "Operation.h"
#include "ProgramParameters.h"

using namespace std;
namespace po = boost::program_options;

class ArgsParser {
public:
	ArgsParser();
	Operation* parse(int argc, char** argv);

private:
	const char* HELP;
	const char* DBPATH;
	const char* SEARCH;
	const char* INITDB;
	const char* SINGLE_IMG_EVAL;
};

#endif /* COMMANDLINEPARSER_H_ */
