/*
 * FaceData.h
 *
 *  Created on: 08/09/2012
 *      Author: ramiro
 */

#ifndef FACEDATA_H_
#define FACEDATA_H_

#include <boost/filesystem/path.hpp>

struct FaceData {
	boost::filesystem::path path;
	int faceCount;
	double skinHueMean;
	double skinHueVariance;
	double skinSaturationMean;
	double skinSaturationVariance;
	double skinValueMean;
	double skinValueVariance;
	double hueRating;
	double saturationRating;
	double valueRating;
};


#endif /* FACEDATA_H_ */
