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

list<string> ImageDatabase::search(ProgramParameters params) {
	if ( !fs::exists( index_path ) ) {
		throw 4; //TODO improve. index file doesn't exists
	}

	fs::ifstream idxfile(index_path);

	fs::path img_path;
	FaceData data;

	//idxfile.setf(ios::skipws);

	while (idxfile) {
		idxfile
			>> data.faceCount
			>> data.skinHueMean
			>> data.skinHueVariance
			>> data.skinSaturationMean
			>> data.skinSaturationVariance
			>> img_path;

		//http://www.boost.org/doc/libs/1_49_0/libs/math/doc/sf_and_dist/html/math_toolkit/dist/stat_tut/weg/normal_example/normal_misc.html
		//boost's normal distribution gets std. deviation instead of variance as argument
		math::normal_distribution<double> nHue(data.skinHueMean, data.skinHueVariance);
		math::normal_distribution<double> nSaturation(data.skinSaturationMean, data.skinSaturationVariance);
		math::pdf(nHue, params.searchParam);
		math::pdf(nSaturation, params.searchParam);

		cout << img_path << '\t'
			<< math::pdf(nHue, params.searchParam) << '\t'
			<< math::pdf(nSaturation, params.searchParam) << '\t'
			<< endl;

		/*
		cout << data.faceCount << '\t'
				<< data.skinHueMean << '\t'
				<< data.skinHueVariance << '\t'
				<< data.skinSaturationMean << '\t'
				<< data.skinSaturationVariance << '\t'
				<< img_path
				<< endl;
		*/
	}

	return list<string>();
}
