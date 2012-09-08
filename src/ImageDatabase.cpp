/*
 * ImageDatabase.cpp
 *
 *  Created on: 07/09/2012
 *      Author: ramiro
 */

#include "ImageDatabase.h"


struct SortFaceData {
	bool operator()(const FaceData& left, const FaceData& right) const {
		return left.rating >= right.rating;
	}
};



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

string ImageDatabase::getIndexFilePath() {
	return index_path.string();
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
				idxfile << data.faceCount << '\t'
						<< data.skinHueMean << '\t'
						<< data.skinHueVariance << '\t'
						<< data.skinSaturationMean << '\t'
						<< data.skinSaturationVariance << '\t'
						<< it->path()
						<< endl;
			}
		}
	}

	idxfile.close();
}

list<FaceData> ImageDatabase::search(ProgramParameters params) {
	if ( !fs::exists( index_path ) ) {
		throw 4; //TODO improve. index file doesn't exists
	}

	int hueParam;
	int satParam;
	switch (params.searchParam) {
	case 0:
		hueParam = 10.2184;
		satParam = 100.9641;
		break;
	case 1:
		hueParam = 10.1850;
		satParam = 103.8542;
		break;
	case 2:
		hueParam = 8.6670;
		satParam = 120.3788;
		break;
	case 3:
		hueParam = 10.3557;
		satParam = 137.4917;
		break;
	case 4:
		hueParam = 10.1593;
		satParam = 126.0256;
		break;
	case 5:
		hueParam = 10.8195;
		satParam = 109.5845;
		break;
	default:
		throw 20; //TODO improve. invalid parameter
	}

	fs::ifstream idxfile(index_path);

	FaceData data;
	list<FaceData> results;

	while (idxfile) {
		idxfile
			>> data.faceCount
			>> data.skinHueMean
			>> data.skinHueVariance
			>> data.skinSaturationMean
			>> data.skinSaturationVariance
			>> data.path;

		//http://www.boost.org/doc/libs/1_49_0/libs/math/doc/sf_and_dist/html/math_toolkit/dist/stat_tut/weg/normal_example/normal_misc.html
		math::normal_distribution<double> nHue(data.skinHueMean, sqrt(data.skinHueVariance));
		math::normal_distribution<double> nSaturation(data.skinSaturationMean, sqrt(data.skinSaturationVariance) );

		data.rating = math::pdf(nHue, hueParam) +
			          math::pdf(nSaturation, satParam)*100;

		results.push_back(data);
	}

	//sort return only the top 10
	results.sort(SortFaceData());
	results.resize(10);

	return results;
}
