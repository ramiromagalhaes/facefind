/*
 * FaceDetector.cpp
 *
 *  Created on: 03/09/2012
 *      Author: ramiro
 */

#include "FaceClassifier.h"
#include "Histogram.h"

FaceClassifier::FaceClassifier() {
	face_cascade_name = "haarcascade_frontalface_alt.xml";
	eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
	face_cascade.load( face_cascade_name );
	eyes_cascade.load( eyes_cascade_name );
}

FaceClassifier::~FaceClassifier() {
	// TODO Auto-generated destructor stub
}

FaceData FaceClassifier::classify(cv::Mat image, bool display) {
	FaceData data;
	vector<cv::Rect> faces;

	{
		cv::Mat gray_image;
		cv::cvtColor(image, gray_image, CV_BGR2GRAY);
		cv::equalizeHist(gray_image, gray_image);

		face_cascade.detectMultiScale(
				gray_image,	           //detect stuff on this image
				faces,                 //store results here
				1.1,                   //TODO learn
				2,                     //TODO learn
				0|CV_HAAR_SCALE_IMAGE, //TODO learn
				cv::Size(30,30)        //TODO learn
		);
	}

	data.faceCount = faces.size();

	for(vector<cv::Rect>::iterator it = faces.begin(); it != faces.end(); ++it) {
		//Draw a rectangle around a face
		if (display) {
			cv::rectangle(image, *it, cv::Scalar(255, 0, 255), 4, 8, 0);
		}

		cv::Mat face(image, *it); //gets the face part of the image
		cv::cvtColor(face, face, CV_BGR2HSV); //convert the image color scheme to HSV
		face = applyMaskToFace(face); //get only the face's skin
		nonZeroHueSaturationStatistics(face, data); //get statistics about the skin and place them into data
	}

	if (display) {
		cv::imshow("Face", image);
	}

	return data;
}

//Input should be a HSV image.
cv::Mat FaceClassifier::applyMaskToFace(cv::Mat face) {
	//split the HSV face image in its 3 channels
	cv::vector<cv::Mat> faceChannels;
    cv::split(face, faceChannels);

    //Create a mask of what we think is likelly to be a person skin color and applies the mask to each channel.
    //http://dsp.stackexchange.com/questions/1625/basic-hsb-skin-detection-neon-illumination/1634#1634
    //Skin Colour Analysis - by Jamie Sherrah and Shaogang Gong - http://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=4&cad=rja&ved=0CDcQFjAD&url=http%3A%2F%2Fist.ksc.kwansei.ac.jp%2F~kono%2FLecture%2FCV%2FProtected%2FRejume%2FSkin.pdf&ei=lFhGUOyrH-Tv0gHkr4HICw&usg=AFQjCNFNz6j-RksTSKw5MN4qVuRB1N6KJg&sig2=gNrLxN_tzXgErqRAoRPA1A
	//http://www-cs-students.stanford.edu/~robles/ee368/skincolor.html
	//http://ilab.cs.ucsb.edu/index.php/component/content/article/12/31
	//http://docs.opencv.org/modules/imgproc/doc/miscellaneous_transformations.html#threshold
    //http://www.shervinemami.info/blobs.html
	//TODO is there a way to do all that without splitting and merging?
    cv::Mat mask;
    {
		cv::Mat mask1, mask2;
		cv::threshold(faceChannels[0], mask1,         3, 255, cv::THRESH_BINARY);
		cv::threshold(faceChannels[0], mask2,        17, 255, cv::THRESH_BINARY_INV);
		cv::bitwise_and(mask1, mask2, mask);
		cv::threshold(faceChannels[1], mask1, 256 * 0.9, 255, cv::THRESH_BINARY_INV);
		cv::bitwise_and(mask1, mask, mask);
		cv::threshold(faceChannels[2], mask1, 256 * 0.05, 255, cv::THRESH_BINARY);
		cv::threshold(faceChannels[2], mask2, 256 * 0.95, 255, cv::THRESH_BINARY_INV);
		cv::bitwise_and(mask1, mask2, mask1);

		cv::bitwise_and(mask1, mask, mask);
    }

    //applies the mask to each channel
    cv::bitwise_and(faceChannels[0], mask, faceChannels[0]);
    cv::bitwise_and(faceChannels[1], mask, faceChannels[1]);
    cv::bitwise_and(faceChannels[2], mask, faceChannels[2]);

    //merge the channels back to the face image
	cv::merge(faceChannels, face);

	return face;
}

void FaceClassifier::nonZeroHueSaturationStatistics(cv::Mat face, FaceData &data) {
	/* Calculates the average hue and saturation of the face's skin, ignoring
	 * all zeroed pixels while doing this. This is necessary because the mask
	 * we applied zeroed all non-face pixels.
	 */

	//split the HSV face image in its 3 channels
	cv::vector<cv::Mat> faceChannels;
    cv::split(face, faceChannels);

    acc::accumulator_set< double, acc::stats<acc::tag::variance> > hue; //accumulates hue
    acc::accumulator_set< double, acc::stats<acc::tag::variance> > sat; //accumulates saturation

    {
		const int nRows = face.rows;
		const int nCols = face.cols;
		for( int i = 0; i < nRows; ++i) {
			uchar* p_h = faceChannels[0].ptr<uchar>(i);
			uchar* p_s = faceChannels[1].ptr<uchar>(i);
			for ( int j = 0; j < nCols; ++j) {
				if ( p_h[j] ) hue( p_h[j] );
				if ( p_s[j] ) sat( p_s[j] );
			}
		}
    }

	data.skinHueMean = acc::mean(hue);
	data.skinHueVariance = acc::variance(hue);
	data.skinSaturationMean = acc::mean(sat);
	data.skinSaturationVariance = acc::variance(sat);
}
