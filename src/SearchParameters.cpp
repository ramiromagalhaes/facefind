/*
 * SearchParameters.cpp
 *
 *  Created on: 03/09/2012
 *      Author: ramiro
 */

#include "SearchParameters.h"

SearchParameters::SearchParameters() {
	skinParam = eyesParam = 0;
}

void SearchParameters::load(int argc, char** argv) {
    po::options_description desc("You must provide at least one of the following search parameters");
    desc.add_options()
        ("skin", po::value<int>(), "The skin color.")
        ("eyes", po::value<int>(), "The eyes color.")
    ; //a bizarre usage of operator parentheses

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if ( vm.count("skin") || vm.count("eyes") ) {
    	cout << desc;
    	throw 1;
    }

    if ( vm.count("skin") ) skinParam = vm["skin"].as<int>();
    if ( vm.count("eyes") ) eyesParam = vm["eyes"].as<int>();

}

int SearchParameters::skin() const {
	return skinParam; //black, white
}

int SearchParameters::eyes() const {
	return eyesParam; //blue, green, brown, black
}
