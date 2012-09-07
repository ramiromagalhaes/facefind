/*
 * ImageDatabase.cpp
 *
 *  Created on: 07/09/2012
 *      Author: ramiro
 */

#include "ImageDatabase.h"


ImageDatabase::ImageDatabase(string dirName) {
	database_dir = fs::path(dirName);

	if ( !fs::is_directory(database_dir) ) {
		throw 1; //TODO improve exception throwing
	}

	index_file = database_dir / ".facefind.database";
}

ImageDatabase::~ImageDatabase() {
	// TODO Auto-generated destructor stub
}

void ImageDatabase::create() {
	if ( fs::exists( index_file ) ) {
		throw 2; //TODO improve. index file already exists
	}

	fs::ofstream idxfile(index_file);

	FaceClassifier classifier;

	fs::directory_iterator end_it; //default construction yields past-the-end
	for (fs::directory_iterator it(database_dir); it != end_it; ++it) {
		if (!fs::is_directory(*it)) {
			cout << "Reading " << it->path() << endl;
			cv::Mat image = cv::imread(it->path().c_str());
			classifier.classify(image);
			//TODO should get data from the classifier to write into the index file
			idxfile << it->path();
		}
	}

}

void ImageDatabase::load() {

}

list<string> ImageDatabase::search(ProgramParameters params) {
	return list<string>();
}
