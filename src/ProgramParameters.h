/*
 * ProgramParameters.h
 *
 *  Created on: 08/09/2012
 *      Author: ramiro
 */

#ifndef PROGRAMPARAMETERS_H_
#define PROGRAMPARAMETERS_H_

#include <iostream>



struct ProgramParameters {
	std::string imgpath, dbpath;
	int searchParam; //0 = white, 3 = tanned, 5 = black
};



#endif /* PROGRAMPARAMETERS_H_ */
