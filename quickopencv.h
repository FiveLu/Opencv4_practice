#pragma once

#include <opencv2/opencv.hpp>
using namespace cv;

class QuickDemo
{
public:
	void colorSpace_Demo(Mat& image);
	void mat_creation_Demo(Mat& image);
	void pixel_visit_Demo(Mat& image);
	void pixel_operators_Demo(Mat& image);
	void trackbar_Demo(Mat& image);
	void key_Demo(Mat& image);
	void color_style_Demo(Mat& image);
	void bitwise_Demo(Mat& image);
	void channels_Demo(Mat& image);
	void inrange_Demo(Mat& image);
	void pixel_statistic_Demo(Mat& image);
	void drawing_geometry_Demo(Mat& image);
};

