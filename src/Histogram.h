#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>

//Inspired from page 90
class Histogram
{
    public:
        Histogram(const cv::Mat *image);
        ~Histogram();
        cv::Mat getHistogram();
        cv::Mat getHistogram(int channel);
        cv::Mat getHistogramImage(int channel);
        cv::Mat getHistogramIgnoreZero(int channel);
        cv::Mat getHistogramImageIgnoreZero(int channel);

    private:
        const cv::Mat *sourceImage;

        float hranges[2]; //hranges[0] = 0, hranges[1] = 255

        int* histSize;  //all elements = 256
        float** ranges;
        int* channels;

        cv::Mat createHistogramImageFromHistogram(cv::Mat hist);
};

#endif // HISTOGRAM1D_H
