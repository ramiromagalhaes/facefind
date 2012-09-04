#include "Histogram.h"

Histogram::Histogram(const cv::Mat *image)
{
    sourceImage = image;

    const int amount_channels = image->channels();
    hranges[0] = 0.0;
    hranges[1] = 255.0;

    channels = new int[amount_channels];
    ranges = new float*[amount_channels];
    histSize = new int[amount_channels];

    for (int i = 0; i < amount_channels; i++) {
        channels[i] = i;
        ranges[i] = hranges;
        histSize[i] = 256;
    }
}

Histogram::~Histogram()
{
    sourceImage = NULL; //we don't need to call Mat::release() here.

    delete [] histSize;
    delete [] ranges;
    delete [] channels;
}

cv::Mat Histogram::getHistogram()
{
    cv::Mat hist;
    cv::calcHist(sourceImage,       //the image
		1,                          //histogram from 1 image
		channels,                   //the channel used
		cv::Mat(),                  //no mask used
		hist,                       //the resulting histogram
		sourceImage->channels(),    //a 1D histogram
		histSize,                   //number of bins
		(const float**)ranges       //pixel value range
	);
    return hist;
}

cv::Mat Histogram::getHistogram(int channel_number)
{
    cv::Mat hist;
    cv::calcHist(sourceImage,       //the image
		1,                          //histogram from 1 image
		&channels[channel_number],  //the channel used
		cv::Mat(),                  //no mask used
		hist,                       //the resulting histogram
		1,                          //a 1 dimension histogram
		histSize,                   //number of "bins"
		(const float**)ranges       //pixel value range
	);
    return hist;
}

cv::Mat Histogram::getHistogramImage(int channel = 0)
{
    cv::Mat hist = getHistogram(channel);
	return createHistogramImageFromHistogram(hist);
}

cv::Mat Histogram::getHistogramIgnoreZero(int channel = 0)
{
	cv::Mat hist = getHistogram(channel);
	hist.at<float>(0) = 0;
	return hist;
}

cv::Mat Histogram::getHistogramImageIgnoreZero(int channel = 0)
{
	cv::Mat hist = getHistogramIgnoreZero(channel);
	return createHistogramImageFromHistogram(hist);
}

cv::Mat Histogram::createHistogramImageFromHistogram(cv::Mat hist) {
	//loads into maxVal and minVal the minimum and maximum
    double maxVal = 0;
    double minVal = 0;
    cv::minMaxLoc(hist , &minVal, &maxVal, 0, 0);

    cv::Mat histImg(histSize[0], histSize[0], CV_8U, cv::Scalar(255));

    //highest point at 90% of nbins
    int hpt = static_cast<int>(0.9 * histSize[0]);

    //draws lines for each bin
    for(int h = 0; h < histSize[0]; h++)
    {
        float binVal = hist.at<float>(h);
        int intensity = static_cast<int>(binVal*hpt/maxVal);

        cv::line(histImg, cv::Point(h, histSize[0]),
                          cv::Point(h, histSize[0] - intensity),
                          cv::Scalar::all(0) //color
                 );
    }

    return histImg;
}
