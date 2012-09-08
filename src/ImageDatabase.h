/*
 * ImageDatabase.h
 *
 *  Created on: 07/09/2012
 *      Author: ramiro
 */

#ifndef IMAGEDATABASE_H_
#define IMAGEDATABASE_H_

#include <iostream>
#include <list>
#include <map>

#include <boost/filesystem/operations.hpp> // includes boost/filesystem/path.hpp
#include <boost/filesystem/fstream.hpp>   // ditto

#include <imgproc/imgproc.hpp>

#include <boost/math/distributions/normal.hpp>

#include "FaceData.h"
#include "ProgramParameters.h"
#include "Operation.h"
#include "FaceClassifier.h"

using namespace std;
namespace fs = boost::filesystem;
namespace math = boost::math;



//http://www.boost.org/doc/libs/1_51_0/libs/filesystem/doc/index.htm
class ImageDatabase {
public:
	ImageDatabase(string dirName);
	virtual ~ImageDatabase();

	string getIndexFilePath();

	void create();
	list<FaceData> search(ProgramParameters params);

private:
    fs::path database_path;
	fs::path index_path;

};

#endif /* IMAGEDATABASE_H_ */
