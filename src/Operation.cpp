/*
 * Operation.cpp
 *
 *  Created on: 07/09/2012
 *      Author: ramiro
 */

#include "Operation.h"

Operation::Operation(ProgramParameters params) {
	this->params = params;
}

Operation::~Operation() {
	//TODO what? really?
}

SingleImageEval::SingleImageEval(ProgramParameters params) : Operation(params) {}

void SingleImageEval::execute() const {
	FaceClassifier classifier;
	cv::Mat img = cv::imread(params.imgpath, CV_LOAD_IMAGE_COLOR);

    if (!img.data) {
        cout << "No file found.";
        return throw 10;
    }

	FaceData data = classifier.classify(img);
	cout << data.faceCount << endl;
	cout << data.skinHueMean << endl;
	cout << data.skinHueVariance << endl;
	cout << data.skinSaturationMean << endl;
	cout << data.skinSaturationVariance << endl;
}

InitializeDatabase::InitializeDatabase(ProgramParameters params) : Operation(params) {}

void InitializeDatabase::execute() const {
	//cout << "Creating index file from images located at '" << params.dbpath << "'." << endl;

	ImageDatabase db(params.dbpath);
	db.create();

	cout << "Done creating database index file at '" << db.getIndexFilePath() << "'." << endl;
}

SearchDatabase::SearchDatabase(ProgramParameters params) : Operation(params) {}

void SearchDatabase::execute() const {
	cout << "SearchDatabase " << params.dbpath << " for " << params.searchParam << endl;
}
