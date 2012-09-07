/*
 * CommandLineParser.cpp
 *
 *  Created on: 07/09/2012
 *      Author: ramiro
 */

#include "ArgsParser.h"

ArgsParser::ArgsParser() {
	HELP = "help";
	DBPATH = "dbpath";
	SEARCH = "search";
	INITDB = "initdb";
	SINGLE_IMG_EVAL = "eval";
}

Operation* ArgsParser::parse(int argc, char** argv) {

	po::options_description desc("Program arguments");

	desc.add_options()
        (HELP, "This message.")
        (SINGLE_IMG_EVAL, po::value<string>(), "Evaluates a single image without adding it to the database.")
        (DBPATH, po::value<string>(), "The image database directory. This is mandatory for database operations.")
        (SEARCH, po::value<int>(), "Searches the database located at <dbpath>.")
        (INITDB, "Initializes the database with images located at <dbpath>.")
    ; //a bizarre usage of operator parentheses

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);



    ProgramParameters params;

    //if SINGLE_IMG_EVAL argument was provided, ignore all other arguments.
    if ( vm.count(SINGLE_IMG_EVAL) ) {
    	params.imgpath = vm[SINGLE_IMG_EVAL].as<string>();
    	return new SingleImageEval(params);
    }



    //from now on, dbpath is a mandatory argument.
    if ( !vm.count(DBPATH) ) {
    	cout << desc << endl;
    	throw 1;
    }

    //one of the following arguments is mandatory: initdb or search.
    if ( !(vm.count(INITDB) || vm.count(SEARCH)) ) {
    	cout << "You must choose either to initialize the database or to search it." << endl;
    	throw 2;
    }

    params.dbpath = vm[DBPATH].as<string>();

	if ( vm.count(INITDB) ) {
		return new InitializeDatabase(params);
	}

    if ( vm.count(SEARCH) ) {
    	params.searchParam = vm[SEARCH].as<int>();
    	return new SearchDatabase(params);
    }

    assert(true);

    throw -1; //should never reach this line...
}
