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

SingleImageEval::SingleImageEval(ProgramParameters params) : Operation(params) {
}

void SingleImageEval::execute() const {
	cout << "SingleImageEval " << params.imgpath << endl;

	FaceClassifier classifier;
	cv::Mat img = cv::imread(params.imgpath, CV_LOAD_IMAGE_COLOR);
	classifier.classify(img);
}

InitializeDatabase::InitializeDatabase(ProgramParameters params) : Operation(params) {
}

void InitializeDatabase::execute() const {
	cout << "InitializeDatabase " << params.dbpath << endl;
}

SearchDatabase::SearchDatabase(ProgramParameters params) : Operation(params) {
}

void SearchDatabase::execute() const {
	cout << "SearchDatabase " << params.dbpath << " for " << params.searchParam << endl;
}
