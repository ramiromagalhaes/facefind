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

Operation::~Operation() {}



SingleImageEval::SingleImageEval(ProgramParameters params) : Operation(params) {}
void SingleImageEval::execute() const {
	FaceClassifier classifier;
	cv::Mat img = cv::imread(params.imgpath, CV_LOAD_IMAGE_COLOR);

	if (!img.data) {
		cout << "No file found.";
		return throw 10;
	}

	FaceData data = classifier.classify(img, true);
	cout << "Face count              : " << data.faceCount << endl
	     << "Skin hue mean           : " <<  data.skinHueMean << endl
	     << "Skin hue variance       : " << data.skinHueVariance << endl
	     << "Skin saturation mean    : " << data.skinSaturationMean << endl
	     << "Skin saturation variance: " << data.skinSaturationVariance << endl
	     << "Skin value mean         : " << data.skinValueMean << endl
	     << "Skin value variance     : " << data.skinValueVariance << endl;

	cv::imshow("Face", img);
	cv::waitKey();
}



InitializeDatabase::InitializeDatabase(ProgramParameters params) : Operation(params) {}
void InitializeDatabase::execute() const {
	ImageDatabase db(params.dbpath);
	try {
		db.create();
		cout << "Done creating database index file at '" << db.getIndexFilePath() << "'." << endl;
	} catch (int e) {
		cout << "Index file found at '" << db.getIndexFilePath()
			<< "'. If you want to recreate it you must manually remove it first." << endl;
	}
}



SearchDatabase::SearchDatabase(ProgramParameters params) : Operation(params) {}
void SearchDatabase::execute() const {
	ImageDatabase db(params.dbpath);
	list<FaceData> results = db.search(params);
	SearchOutputWriter().writeOutput(results);
}
