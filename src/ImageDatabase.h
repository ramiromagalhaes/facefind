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


class ImageDatabase {
public:
	ImageDatabase(string dirName);
	virtual ~ImageDatabase();

	void create();
	void load();
	list<string> search(ProgramParameters params);

private:
    list<string> files;
    fs::path database_dir;
	fs::path index_file;

};

#endif /* IMAGEDATABASE_H_ */
