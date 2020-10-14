
// opencv 4 - practice 02 
// 1. 色彩空间转换函数 cvtColor
// 2. 图像保存 -imwrite


#include <opencv2/opencv.hpp>
#include <quickopencv.h>
#include <iostream>

using namespace cv;
using namespace std;



int main()
{

	//Mat src = imread("E:/1vs2019/pics/b52.jpg"); // 彩图通道顺序为B G R
	Mat src = imread("C:\\Users\\dell\\Desktop\\file\\zp.jpg");
	if (src.empty())
	{
		cout << "could't load this image....\n" << endl;
		return -1;
	}
	imshow("input", src);

	QuickDemo qd;

	//qd.colorSpace_Demo(src);
	//qd.pixel_visit_Demo(src);
	//qd.pixel_operators_Demo(src);
	//qd.trackbar_Demo(src);
	//qd.key_Demo(src);
	//qd.color_style_Demo(src);
	//qd.bitwise_Demo(src);
	//qd.channels_Demo(src);
	//qd.inrange_Demo(src);
	//qd.pixel_statistic_Demo(src);
	qd.drawing_geometry_Demo(src);

	waitKey(0);
	destroyAllWindows();
	return 0;
}

