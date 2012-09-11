/*
 * ImageDatabase.cpp
 *
 *  Created on: 07/09/2012
 *      Author: ramiro
 */

#include "ImageDatabase.h"


struct SortFaceData {
	bool operator()(const FaceData& left, const FaceData& right) const {
		//return left.valueRating * left.saturationRating >= right.valueRating * right.saturationRating;
		//return left.hueRating + left.saturationRating >= right.hueRating + right.saturationRating;
		return left.valueRating >= right.valueRating;
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
						<< data.skinValueMean << '\t'
						<< data.skinValueVariance << '\t'
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

	double hueParam;
	double saturationParam;
	double valueParam;
	switch (params.searchParam) {
	case 0:
		hueParam = 9.9463;
		saturationParam = 96.5514;
		valueParam = 173.9679;
		break;
	case 1:
		hueParam = 10.3821;
		saturationParam = 121.5932;
		valueParam = 164.4583;
		break;
	case 2:
		hueParam = 10.4487;
		saturationParam = 120.2050;
		valueParam = 156.4423;
		break;
	case 3:
		hueParam = 10.2284;
		saturationParam = 123.4169;
		valueParam = 141.6059;
		break;
	case 4:
		hueParam = 11.4062;
		saturationParam = 121.3610;
		valueParam = 116.6193;
		break;
	case 5:
		hueParam = 10.8130;
		saturationParam = 138.6054;
		valueParam = 114.3032;
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
			>> data.skinValueMean
			>> data.skinValueVariance
			>> data.path;

		//http://www.boost.org/doc/libs/1_49_0/libs/math/doc/sf_and_dist/html/math_toolkit/dist/stat_tut/weg/normal_example/normal_misc.html
		//math::normal_distribution<double> nHue(data.skinHueMean, sqrt(data.skinHueVariance));
		//math::normal_distribution<double> nSaturation(data.skinSaturationMean, sqrt(data.skinSaturationVariance) );
		math::normal_distribution<double> n; //should be used with normalized input
		data.hueRating        = math::pdf(n, (hueParam - data.skinHueMean)/sqrt(data.skinHueVariance));
		data.saturationRating = math::pdf(n, (saturationParam - data.skinSaturationMean)/sqrt(data.skinSaturationVariance));
		data.valueRating      = math::pdf(n, (valueParam - data.skinValueMean)/sqrt(data.skinValueVariance));

		results.push_back(data);
//		if (data.rating >= 0.75) {
//			results.push_back(data);
//		}
	}

	//sort return only the top 10
	results.sort(SortFaceData());

	return results;
}
