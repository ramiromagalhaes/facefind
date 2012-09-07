/*
 * FaceDetector.h
 *
 *  Created on: 03/09/2012
 *      Author: ramiro
 */

#ifndef FACEDETECTOR_H_
#define FACEDETECTOR_H_

#include <iostream>
#include <numeric>

#include <imgproc/imgproc.hpp>
#include <objdetect/objdetect.hpp>
#include <highgui/highgui.hpp>

#include "SearchParameters.h"

using namespace std;

//http://opencv.willowgarage.com/wiki/FaceDetection
//http://en.wikipedia.org/wiki/Haar-like_features
//http://stackoverflow.com/questions/10458692/opencv-face-detection-where-to-place-the-haarcascade-frontalface-alt-xml
//http://answers.opencv.org/question/556/how-was-haarcascade_frontalface_altxml-trained/
//http://docs.opencv.org/doc/tutorials/objdetect/cascade_classifier/cascade_classifier.html
//http://docs.opencv.org/modules/objdetect/doc/cascade_classification.html?highlight=cascadeclassifier#CascadeClassifier
//http://forum.openframeworks.cc/index.php?topic=2006.0 << INTERESTING!
class FaceClassifier {
	public:
		FaceClassifier();
		virtual ~FaceClassifier();

		void find(cv::Mat image, SearchParameters& params);
	private:
		const char* face_cascade_name;
		const char* eyes_cascade_name;
		cv::CascadeClassifier face_cascade;
		cv::CascadeClassifier eyes_cascade;

		cv::Mat applyMaskToFace(cv::Mat image);
		cv::Scalar nonZeroMeanHueSaturation(cv::Mat image); //returns a Scalar with 2 elements

};

#endif /* FACEDETECTOR_H_ */
