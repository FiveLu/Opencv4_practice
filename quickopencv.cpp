#include <quickopencv.h>

// ɫ��ռ�ת��
void QuickDemo::colorSpace_Demo(Mat& image)
{
	Mat gray, hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	// ɫ����H�������Ͷȣ�S�������ȣ�V��
	// HSV  : H ͨ��0-180  S��V 0-255   V��ʾ���� HS ��ʾ��ɫ
	cvtColor(image, gray, COLOR_BGR2GRAY);
	imshow("hsv", hsv);
	imshow("gray", gray);
	imwrite("E:/1vs2019/ImageProcessing/practice02/hsv.png",hsv);
	imwrite("E:/1vs2019/ImageProcessing/practice02/gray.png", gray);
}

// ͼ�����Ĵ���
void QuickDemo::mat_creation_Demo(Mat& image) 
{
	Mat m1, m2;
	// ��¡�͸���  �� �������µ��ڴ�
	// ��ͨ��ֵ�� ָ��ԭ�����ڴ�
	m1 = image.clone();
	image.copyTo(m2);

	// �����հ׵�ͼ��
	//Mat m3 = Mat::zeros(Size(8, 8), CV_8UC1); // 8bit unsigned char  and 1 channel
	Mat m3 = Mat::zeros(Size(200, 200), CV_8UC3);
	m3 = Scalar(143, 82, 104);
	//std::cout << "  width: " << m3.cols << "  height: " << m3.rows << "  channels�� " << m3.channels() << std::endl;
	//std::cout << m3 << std::endl;

	imshow("iiimmage", m3);

	

	// ***
	//  ones  ����ͨ��ʱ ֻ�е�һ��channel Ϊ 1  ����������Ϊ0 
	//  m3 =127   Ҳ��ֻ�е�һ��ͨ��ȫ��127  ��������
	//  m3 = Scalar(127,127,127)

}

// ���ض�д ����ɫ����
void QuickDemo::pixel_visit_Demo(Mat& image)
{
	int w = image.cols;
	int h = image.rows;
	int dims = image.channels();

	///*�����*/
	//for (int i = 0; i < h; i++)
	//{
	//	for (int j = 0; j < w; j++)
	//	{
	//		// ��ͨ���Ҷ�ͼ
	//		if (dims==1)
	//		{
	//			int pixel_value = image.at<uchar>(i, j);
	//			image.at<uchar>(i, j) = 255 - pixel_value;
	//		}
	//		// 3ͨ����ͼ
	//		if(dims==3)
	//		{
	//			Vec3b bgr = image.at<Vec3b>(i, j);
	//			image.at<Vec3b>(i, j)[0] = 255 - bgr[0];
	//			image.at<Vec3b>(i, j)[1] = 255 - bgr[1];
	//			image.at<Vec3b>(i, j)[2] = 255 - bgr[2];
	//		}
	//	}
	//}

	 /*ָ���*/
	for (int i = 0; i < h; i++)
	{
		uchar* current_row = image.ptr<uchar>(i);
		for (int j = 0; j < w; j++)
		{
			// ��ͨ���Ҷ�ͼ
			if (dims == 1)
			{
				*current_row++ = 255 - *current_row;
			}
			// 3ͨ����ͼ
			if (dims == 3)
			{
				for (int  k = 0; k < 3; k++)
				{
					*current_row++ = 255 - *current_row;
				}
			}
		}
	}

	imshow("pixel_rw", image);
}

// ���ز���  +-*/  �ܹ�����ͼ������
void QuickDemo::pixel_operators_Demo(Mat& image)
{
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat dst2;
	uchar m = 2;
	int w = image.cols;
	int h = image.rows;
	int dims = image.channels();

	//dst = image - Scalar(50, 50, 50);
	//dst = image + Scalar(50, 50, 50);

	// ͼ��˷���  multiply 
	multiply(image, Scalar(2, 2, 2), dst2);

	// ͼ��˷� ��д��
	for (int i = 0; i < h; i++)
	{
		uchar* ptimage = image.ptr<uchar>(i);
		uchar* ptdst = dst.ptr<uchar>(i);
		for (int j = 0; j < w; j++)
		{
			*ptdst++ = saturate_cast<uchar>(m * (*ptimage++));
			*ptdst++ = saturate_cast<uchar>(m * (*ptimage++));
			*ptdst++ = saturate_cast<uchar>(m * (*ptimage++));
		}
	}
	imshow("operators", dst);
	imshow("operators2", dst2);
}

// ��������
static void on_lightness(int b,void* userdata)
{
	Mat image = *((Mat*)userdata);
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	m = Scalar(b, b, b);

	//add(image, m, dst);
	addWeighted(image, 1.0, m, 0, b, dst);
	imshow("�Աȶ�&���ȵ���", dst);
}
// �������ȺͶԱȶ�
static void on_contrast(int b, void* userdata)
{
	Mat image = *((Mat*)userdata);
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	double contrast = b / 100.0;
	m = Scalar(b, b, b);

	addWeighted(image, contrast, m, 0.0, 0, dst);
	imshow("�Աȶ�&���ȵ���", dst);
}

void QuickDemo::trackbar_Demo(Mat& image)
{

	namedWindow("�Աȶ�&���ȵ���", WINDOW_AUTOSIZE);
	int max_value = 100;
	int lightness = 50;
	int contrast_value = 100;
	
	createTrackbar("Value bar :", "�Աȶ�&���ȵ���", &lightness, max_value, on_lightness,(void*)(&image));
	createTrackbar("Contrast bar :", "�Աȶ�&���ȵ���", &contrast_value, 200, on_contrast, (void*)(&image));
	on_contrast(50, &image);
}

// �����¼�
void QuickDemo::key_Demo(Mat& image)
{
	Mat dst=Mat::zeros(image.size(),image.type());
	while (true)
	{
		int c = waitKey(100);
		switch (c)
		{
			case 27:break;
			case 49:
				cvtColor(image, dst, COLOR_BGR2GRAY);
				break;
			case 50:
				cvtColor(image, dst, COLOR_BGR2HSV);
				break;
			case 51:
				dst = Scalar(50, 50, 50);
				add(image, dst, dst);
				break;
		}
		if (27 == c) break;
		imshow("������Ӧ", dst);
	}
}

// ���չʾ
void QuickDemo::color_style_Demo(Mat& image)
{
	int color_map[] = {
	COLORMAP_AUTUMN,
	COLORMAP_BONE,
	COLORMAP_JET,
	COLORMAP_WINTER,
	COLORMAP_RAINBOW,
	COLORMAP_OCEAN,
	COLORMAP_SUMMER,
	COLORMAP_SPRING,
	COLORMAP_COOL,
	COLORMAP_HSV,
	COLORMAP_PINK,
	COLORMAP_HOT,
	COLORMAP_PARULA,
	COLORMAP_MAGMA,
	COLORMAP_INFERNO,
	COLORMAP_PLASMA,
	COLORMAP_VIRIDIS,
	COLORMAP_CIVIDIS,
	COLORMAP_TWILIGHT,
	COLORMAP_TWILIGHT_SHIFTED,
	COLORMAP_TURBO,
	COLORMAP_DEEPGREEN
	};
	int index=0;
	Mat dst = Mat::zeros(image.size(),image.type());
	while (true)
	{
		int c = waitKey(2000);
		if (c == 27) break;
		applyColorMap(image, dst, color_map[(index++)%19]);
		imshow("��ɫ���", dst);	
	}
}

// ���ز���
void QuickDemo::bitwise_Demo(Mat& image)
{
	Mat m1 = Mat::zeros(Size(256, 256), CV_8UC3);
	Mat m2 = Mat::zeros(Size(256, 256), CV_8UC3);
	rectangle(m1, Rect(100, 100, 80, 80), Scalar(255, 255, 0), -1, LINE_8, 0);// -1��ȫ����䣬 ������ʾ�߿�
	rectangle(m2, Rect(150, 150, 80, 80), Scalar(0, 255, 255), -1, LINE_8, 0);
	imshow("m1", m1);
	imshow("m2", m2);
	Mat dst;
	bitwise_or(m1, m2, dst);
	imshow("����λ����",dst);

}

// ͨ������
void QuickDemo::channels_Demo(Mat& image)
{
	std::vector<Mat> mv;
	split(image, mv);
	imshow("B", mv[0]);
	imshow("G", mv[1]);
	imshow("R", mv[2]);
	Mat dst = Mat::zeros(image.size(), image.type());
	int fromto[] = { 0,1,1,2,2,0 };
	mixChannels(&image, 1, &dst, 1, fromto, 3);
	imshow("ͨ���ϲ�", dst);
	//merge(mv, dst);
}

// ��Ĥ����
void QuickDemo::inrange_Demo(Mat& image)
{
	Mat hsv;
	// HSVɫ���ܹ�ɾѡ��ͬ��ɫ
	cvtColor(image, hsv, COLOR_BGR2HSV);
	Mat mask;
	inRange(hsv, Scalar(100,43,46), Scalar(124,255,255), mask);  // ��Ӧ��ɫ��hsv��Χ  ����ֵ��
	// ����mask��һ����ͨ����ͼ
	imshow("mask",mask);

	Mat backcolor = Mat::zeros(image.size(), image.type());
	backcolor = Scalar(40,40,200); // һ�ֺ�ɫ
	bitwise_not(mask, mask); // �ڰ׷���
	image.copyTo(backcolor, mask);
	// A.copyTo(B,mask) �÷���
	// ��mask��Ϊ�ж�����
	// �������ֵΪ1 ��A copyto B 
	// �������ֵΪ0 ��B������ԭʼ����ֵ
	imshow("roi",backcolor);
}

// �����Сֵ����ֵ����
void QuickDemo::pixel_statistic_Demo(Mat& image)
{
	// �����С˵���ԱȶȺܵͣ�Я����Ϣ�Ƚ���
	double minv, maxv;
	Point minloc, maxloc;
	std::vector<Mat> mv;
	split(image, mv);
	for (int i = 0; i < mv.size(); i++)
	{
		minMaxLoc(mv[i], &minv, &maxv, &minloc, &maxloc,Mat()); // minMaxLocֻ�ܶԵ�ͨ��������ȡ�����Сֵ
		std::cout <<"no:"<<i<< "min value: " << minv << "  max value: " << maxv << std::endl;
	}
	Mat mean, stddev;
	meanStdDev(image, mean, stddev);
	std::cout << " means:" << mean << " stddev: " << stddev << std::endl;
}

// ���Ƽ���ͼ��
void QuickDemo::drawing_geometry_Demo(Mat& image)
{
	Rect rect;
	rect.x = 40;
	rect.y = 40;
	rect.width = 150;
	rect.height = 160;

	Mat bg = Mat::zeros(image.size(), image.type());
	rectangle(bg, rect, Scalar(0, 0, 255), -1, 8, 0);
	//circle(image, Point(100, 200), 15, Scalar(255, 200, 0), 1, 8, 0);
	Mat dst;
	addWeighted(image, 0.8, bg, 0.3, 0.1, dst);

	imshow("������ʾ", bg);
}






