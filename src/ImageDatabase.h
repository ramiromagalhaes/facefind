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

#include <boost/filesystem/operations.hpp> // includes boost/filesystem/path.hpp
#include <boost/filesystem/fstream.hpp>   // ditto

#include <imgproc/imgproc.hpp>

#include "ProgramParameters.h"
#include "FaceClassifier.h"

using namespace std;
namespace fs = boost::filesystem;


//http://www.boost.org/doc/libs/1_51_0/libs/filesystem/doc/index.htm
class ImageDatabase {
public:
	ImageDatabase(string dirName);
	virtual ~ImageDatabase();

	void create();
	void load();
	list<string> search(ProgramParameters params);

	string getIndexFilePath();

private:
    fs::path database_path;
	fs::path index_path;

};

#endif /* IMAGEDATABASE_H_ */
