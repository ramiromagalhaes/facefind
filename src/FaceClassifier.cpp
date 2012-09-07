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

void FaceClassifier::classify(cv::Mat image) {
	cv::Mat gray_image;
	cv::cvtColor(image, gray_image, CV_BGR2GRAY);
	cv::equalizeHist(gray_image, gray_image);

	vector<cv::Rect> faces;
	face_cascade.detectMultiScale(
			gray_image,	           //detect stuff on this image
			faces,                 //store results here
			1.1,                   //???
			2,                     //???
			0|CV_HAAR_SCALE_IMAGE, //???
			cv::Size(30,30)        //???
	);

	for(vector<cv::Rect>::iterator it = faces.begin(); it != faces.end(); ++it) {
		//Draw a rectangle around a face
		//cv::rectangle(image, *it, cv::Scalar(255, 0, 255), 4, 8, 0);

		//gets the face part of the image
	    cv::Mat face(image, *it);
	    //convert the image color scheme to HSV
		cv::cvtColor(face, face, CV_BGR2HSV);

		//get only the face's skin
		face = applyMaskToFace(face);

		//Histogram h( (cv::Mat const*)&face );
		//cv::Mat hueHistogram = h.getHistogramIgnoreZero(0);
		//cv::Mat saturationHistogram = h.getHistogramIgnoreZero(1);
		//cv::Mat h.getHistogramIgnoreZero(2);

		//cout << hueHistogram.channels();
		//cout << saturationHistogram.channels();

		/*
		//Cálculo de matriz de covariância
		//http://stackoverflow.com/questions/9795634/calccovarmatrix-in-multichannel-image-and-unresolved-assertion-error
		cv::vector<cv::Mat> faceChannels;
	    cv::split(face, faceChannels);
	    cv::Mat covar, mean;
		cv::calcCovarMatrix(faceChannels[0], covar, mean, CV_COVAR_NORMAL | CV_COVAR_ROWS, CV_8U);
		cout << "Hue covariance: " << covar << endl << endl;
		cout << "Covar Mtx mean: " << mean << endl;
		*/

		cv::Scalar means = nonZeroMeanHueSaturation(face);
		cout << "Hue mean: " << means[0] << endl << endl;
		cout << "Saturation mean: " << means[1] << endl;

/*
    	{
			Histogram h( (cv::Mat const*)&face );

			cv::imshow("Histograma H", h.getHistogramImageIgnoreZero(0));
			cv::imshow("Histograma S", h.getHistogramImageIgnoreZero(1));
			cv::imshow("Histograma V", h.getHistogramImageIgnoreZero(2));

			cv::cvtColor(face, face, CV_HSV2BGR);
			cv::imshow("Face", face);
    	}
*/
	}

	cv::waitKey();
}


/*
 * Input should be a HSV image.
 */
cv::Mat FaceClassifier::applyMaskToFace(cv::Mat face) {
	//TODO is there a way to do the same thing I did bellow without splitting and merging?

	//split the HSV face image in its 3 channels
	cv::vector<cv::Mat> faceChannels;
    cv::split(face, faceChannels);

    //apply a threshold to the hue channel. With that I expect to get only the skin from the person's face.

    //Next, Create a mask of what we think is likelly to be a person skin color and applies the mask to each channel
    //http://dsp.stackexchange.com/questions/1625/basic-hsb-skin-detection-neon-illumination/1634#1634
    //Skin Colour Analysis - by Jamie Sherrah and Shaogang Gong - http://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=4&cad=rja&ved=0CDcQFjAD&url=http%3A%2F%2Fist.ksc.kwansei.ac.jp%2F~kono%2FLecture%2FCV%2FProtected%2FRejume%2FSkin.pdf&ei=lFhGUOyrH-Tv0gHkr4HICw&usg=AFQjCNFNz6j-RksTSKw5MN4qVuRB1N6KJg&sig2=gNrLxN_tzXgErqRAoRPA1A
	//http://www-cs-students.stanford.edu/~robles/ee368/skincolor.html
	//http://ilab.cs.ucsb.edu/index.php/component/content/article/12/31
	//http://docs.opencv.org/modules/imgproc/doc/miscellaneous_transformations.html#threshold
    //http://www.shervinemami.info/blobs.html
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

cv::Scalar FaceClassifier::nonZeroMeanHueSaturation(cv::Mat face) {
	/*This big (bad) block of code calculates the average hue and saturation of the face,
	 * but ignores all zeroed pixels while doing this. This is necessary because the mask
	 * we applied zeroed all non-face pixels.
	 */

	//split the HSV face image in its 3 channels
	cv::vector<cv::Mat> faceChannels;
    cv::split(face, faceChannels);

	float meanHue = 0;
    float meanSaturation = 0;
    { //special mean
		int sumHue = 0;
		int countHue = 0;
		int sumSaturation = 0;
		int countSaturation = 0;
		int nRows = face.rows;
		int nCols = face.cols;
		for( int i = 0; i < nRows; ++i) {
			uchar* p_h = faceChannels[0].ptr<uchar>(i);
			uchar* p_s = faceChannels[1].ptr<uchar>(i);
			for ( int j = 0; j < nCols; ++j) {
				if ( p_h[j] ) {
					sumHue += p_h[j];
					countHue++;
				}
				if ( p_s[j] ) {
					sumSaturation += p_s[j];
					countSaturation++;
				}
			}
		}
		meanHue = (float)sumHue / (float)countHue;
		meanSaturation = (float)sumSaturation / (float)countSaturation;
    }

    cv::Scalar_<float> returnVal;
    returnVal[0] = meanHue;
    returnVal[1] = meanSaturation;

    return  returnVal;
}
