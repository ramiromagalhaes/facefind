//============================================================================
// Name        : facefind.cpp
// Author      : Ramiro Pereira de Magalhães <ramiro.p.magalhaes@gmail.com>
// Version     :
// Copyright   : 
// Description : ...
//============================================================================

#include <iostream>

#include <imgproc/imgproc.hpp>
#include <highgui/highgui.hpp>

#include "SearchParameters.h"
#include "FaceClassifier.h"

using namespace std;

int main(int argc, char** argv) {

	SearchParameters params;

	try {
		params.load(argc, argv);
	} catch (int error) {
		return error;
	}

	FaceClassifier finder;

	cv::Mat img;
	//img = cv::imread("/home/ramiro/Imagens/IMG_6370.jpg", CV_LOAD_IMAGE_COLOR);
	//img = cv::imread("/home/ramiro/Imagens/Laren Galloway baby.jpg", CV_LOAD_IMAGE_COLOR);
	img = cv::imread("/home/ramiro/Imagens/blue eyes black man.jpg", CV_LOAD_IMAGE_COLOR);
	//img = cv::imread("/home/ramiro/Imagens/naomi.jpg", CV_LOAD_IMAGE_COLOR);
	//img = cv::imread("/home/ramiro/Imagens/photo.jpg", CV_LOAD_IMAGE_COLOR);
	//img = cv::imread("/home/ramiro/Imagens/WILD-NEGRO-KILLER.jpg", CV_LOAD_IMAGE_COLOR);
    if (!img.data)
    {
        cout << "No file found.";
        return 1;
    }

	finder.find(img, params);


	return 0;
}
