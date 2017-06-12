#include "cv.h"
#include "highgui.h"
#include "cxcore.h"
#include "ml.h"		//包含CvSVM
#include <string>

using namespace cv;
using namespace std;

string recognition(IplImage *test);
string resultStr;

int preProcess(char* imgPath, char *correctAnswers, int score)
{
	//cout << imgPath << endl;
	//IplImage *srcImage = cvLoadImage("D:\\testImg\\exam.jpg", CV_LOAD_IMAGE_COLOR);	//读取图片
	IplImage *srcImage = cvLoadImage(imgPath, CV_LOAD_IMAGE_COLOR);	//读取图片
	if (srcImage == NULL)
	{
		return -1;
	}

	cout << "识别中..." << endl;

	printf("图片的宽和高分别为：%d,%d\n", cvGetSize(srcImage).width, cvGetSize(srcImage).height);

	IplImage* grayImage = cvCreateImage(cvGetSize(srcImage), 8, 1);
	cvCvtColor(srcImage, grayImage, CV_BGR2GRAY);
	cvSaveImage("grayImage.jpg", grayImage);

	//IplImage *sobelImage = cvCreateImage(cvGetSize(srcImage), 8, 1);
	IplImage *binaryImage = cvCreateImage(cvGetSize(srcImage), 8, 1);

	//1. Sobel算子，x方向求梯度
	//cvSobel(grayImage, sobelImage, 1, 0, 3);

	//2. 二值化
	cvThreshold(grayImage, binaryImage, 110, 255, CV_THRESH_BINARY_INV);
	cvNamedWindow("二值化后的图像", CV_WINDOW_NORMAL);
	cvShowImage("二值化后的图像", binaryImage);
	cvSaveImage("binaryImage.jpg", binaryImage);

	//3. 膨胀和腐蚀操作的核函数
	//Mat dilateElement = getStructuringElement(MORPH_RECT, Size(30, 9));	//膨胀
	//Mat erodeElement = getStructuringElement(MORPH_RECT, Size(24, 6));	//腐蚀
	//IplConvKernel *dilateElement = cvCreateStructuringElementEx(30, 9, 0, 0, CV_SHAPE_RECT, NULL);
	//IplConvKernel *erodeElement = cvCreateStructuringElementEx(24, 6, 0, 0, CV_SHAPE_RECT, NULL);

	////4. 膨胀一次，让轮廓突出
	//IplImage *dilateImage = cvCreateImage(cvGetSize(srcImage), 8, 1);	//膨胀图像
	//cvDilate(binaryImage, dilateImage, dilateElement, 1);

	//5. 腐蚀一次，去掉细节，如表格线等。注意这里去掉的是竖直的线
	//IplImage *erodeImage = cvCreateImage(cvGetSize(srcImage), 8, 1);	//膨胀图像
	//cvErode(dilateImage, erodeImage, dilateElement, 1);

	////6. 再次膨胀，让轮廓明显一些
	////IplImage *dilateImage02 = cvCreateImage(cvGetSize(srcImage), 8, 1);	//膨胀图像
	////cvDilate(erodeImage, dilateImage02, dilateElement, 3);

	////7. 存储中间图片
	//cvSaveImage("binaryImage.jpg", binaryImage);
	//cvSaveImage("dilateImage.jpg", dilateImage);
	//cvSaveImage("erodeImage.jpg", erodeImage);
	//cvSaveImage("dilateImage02.jpg", dilateImage02);


	//表格分割
	int imgID = 0;
	char imgName[56] = { 0 };

	for (int i = 0; i < 10; i++)	//10个表格，遍历
	{
		//cvDrawRect(srcImage, cvPoint(0, 0), cvPoint(0 + 530 * i, 0), CV_RGB(255, 0, 0));
		//cvSetImageROI(binaryImage, cvRect(1000 + 420 * i, 600, 320, 350));
		cvSetImageROI(binaryImage, cvRect(615 + 305 * i, 330, 270, 280));

		IplImage* gridImage = cvCreateImage(cvGetSize(binaryImage), 8, 1);
		cvCopy(binaryImage, gridImage);
		cvResetImageROI(binaryImage);

		sprintf(imgName, "分割后的图片_%d", imgID++);
		cvNamedWindow(imgName, CV_WINDOW_NORMAL);
		cvShowImage(imgName, gridImage);


		//识别：分别对每张切割出来的图片进行识别
		resultStr = recognition(gridImage);
	}







	//IplImage* srcImage = cvLoadImage(".\\TestData\\test.jpg", CV_LOAD_IMAGE_COLOR);	//读取图片

	////IplImage* imgDst = new IplImage[50];
	//cvSmooth(srcImage, srcImage, CV_BLUR);
	//IplImage* afterThresholdImg = cvCreateImage(cvGetSize(srcImage), 8, 1);		//创建图像
	//IplImage* grayImg = cvCreateImage(cvGetSize(srcImage), 8, 1);		//创建图像

	//cvCvtColor(srcImage, grayImg, CV_BGR2GRAY);									//转换为灰度图，grayImg必须是单通道图
	//cvThreshold(grayImg, afterThresholdImg, 110, 255, CV_THRESH_BINARY_INV);	//CV_THRESH_BINARY_INV使得背景为黑色，字符为白色，这样找到的最外层才是字符的最外层
	//cvNamedWindow("二值化后的图像", CV_WINDOW_NORMAL);
	//cvShowImage("二值化后的图像", afterThresholdImg);		//显示二值化后的图像

	//CvSeq* contours = NULL;		//创建边框序列
	//CvMemStorage* storage = cvCreateMemStorage(0);

	//int count = cvFindContours(afterThresholdImg, storage, &contours, sizeof(CvContour), CV_RETR_EXTERNAL);
	//printf("轮廓个数：%d\n", count);
	//int idx = 0;
	//char szName[56] = { 0 };

	//int normalizedNameIdx = 0;
	//char normalizedName[56] = { 0 };
	////int tempCount = 0;  
	//
	//for (CvSeq* c = contours; c != NULL; c = c->h_next) {
	//	CvRect rc = cvBoundingRect(c, 0);
	//	if (rc.height * rc.width < 64)
	//	{
	//		continue;     //这里根据轮廓的大小进行筛选  
	//	}
	//	cvDrawRect(grayImg, cvPoint(rc.x, rc.y), cvPoint(rc.x + rc.width, rc.y + rc.height), CV_RGB(255, 0, 0));
	//	IplImage* imgNo = cvCreateImage(cvSize(rc.width, rc.height), 8, 1);
	//	cvSetImageROI(grayImg, rc);
	//	cvCopyImage(grayImg, imgNo);
	//	cvResetImageROI(grayImg);
	//	sprintf(szName, "wnd_%d", idx++);
	//	cvNamedWindow(szName, CV_WINDOW_NORMAL);
	//	cvShowImage(szName, imgNo); //如果想切割出来的图像从左到右排序，或从上到下，可以比较rc.x,rc.y;  

	//	//大小归一化
	//	IplImage* newSizeImg = cvCreateImage(cvSize(32, 32), 8, 1);
	//	//newSizeImg = cvCreateImage(cvSize(32, 32), 8, 1);
	//	cvResize(imgNo, newSizeImg, CV_INTER_LINEAR);

	//	sprintf(normalizedName, "归一化后的灰度图像_%d", normalizedNameIdx++);
	//	cvNamedWindow(normalizedName, CV_WINDOW_NORMAL);
	//	cvShowImage(normalizedName, newSizeImg);

	//	//识别：分别对每张切割出来的图片进行识别
	//	resultStr = recognition(newSizeImg);

	//	//释放资源
	//	cvReleaseImage(&imgNo);
	//	//cvReleaseImage(&newSizeImg);
	//}
	//reverse(resultStr.begin(), resultStr.end());	//翻转结果字符串
	printf("\n识别结果：%s\n", resultStr.c_str());

	string correctAnswersStr = correctAnswers;
	int totalScore = 0;
	for (int i = 0; i < 10; i++)
	{
		if (resultStr[i] == correctAnswersStr[i])
			totalScore += score;
	}
	printf("该同学选择题总分为：%d分\n", totalScore);
	return 0;
}