/*
 * ImageDatabase.cpp
 *
 *  Created on: 07/09/2012
 *      Author: ramiro
 */

#include "ImageDatabase.h"


ImageDatabase::ImageDatabase(string dirName) {
	database_path = fs::path(dirName);

	if ( !fs::is_directory(database_path) ) {
		throw 1; //TODO improve exception throwing
	}

	index_path = database_path / ".facefind.database";
}

ImageDatabase::~ImageDatabase() {
	// TODO Auto-generated destructor stub
}

void ImageDatabase::create() {
	if ( fs::exists( index_path ) ) {
		throw 2; //TODO improve. index file already exists
	}

	fs::ofstream idxfile(index_path);

	FaceClassifier classifier;

	fs::directory_iterator end_it; //default construction yields past-the-end
	for (fs::directory_iterator it(database_path); it != end_it; ++it) {
		if (!fs::is_directory(*it)) {
			//cout << "Reading " << it->path() << endl;

			if ( fs::equivalent(it->path(), index_path) ) {
				continue;
			}

			cv::Mat image = cv::imread(it->path().c_str());
			FaceData data = classifier.classify(image);

			//get data from the classifier to write into the index file
			if (data.faceCount == 1) {
				idxfile << it->path() << "\t"
						<< data.faceCount << "\t"
						<< data.skinHueMean << "\t"
						<< data.skinHueVariance << "\t"
						<< data.skinSaturationMean << "\t"
						<< data.skinSaturationVariance
						<< endl;
			}
		}
	}

	idxfile.close();
}

void ImageDatabase::load() {

}

list<string> ImageDatabase::search(ProgramParameters params) {
	return list<string>();
}

string ImageDatabase::getIndexFilePath() {
	return index_path.string();
}
