#include "cv.h"  
#include "highgui.h"  
#include "cxcore.h"
#include "ml.h"		//包含CvSVM
#include "stdio.h"
using namespace std;
using namespace cv;

int svmDataTrain();
int recognition(IplImage *test);
int preProcess(char *imgPath, char *correctAnswers, int score);


int main(int argc, char* argv[])
{


	/*printf("\n--------------------手写英文字母识别程序 by 蔡德森--------------------\n"
		"|\t\t\t\t\t\t\t\t     |\n"
		"---------------------------------热键---------------------------------\n"
		"|\t\t\tT - 训练样本（Train）\t\t\t     |\n"
		"|\t\t\tR - 进行识别（Recognize）\t\t     |\n"
		"|\t\t\tQ - 退出程序（Quit）\t\t\t     |\n"
		"----------------------------------------------------------------------\n");*/

	char imgPath[128] = { 0 };
	char correctAnswers[10] = { 0 };
	printf("请先输入本次考试的正确答案：\n");
	scanf("%s", correctAnswers);
	printf("请再输入选择题单个选项的分值：\n");
	int score;
	scanf("%d", &score);
	fflush(stdin);

	for (;;)
	{

		printf("\n--------------------手写英文字母识别程序 by 蔡德森--------------------\n"
			"|\t\t\t\t\t\t\t\t     |\n"
			"---------------------------------热键---------------------------------\n"
			"|\t\t\t\t\t\t\t\t     |\n"
			"|\t\t\tT - 训练样本（Train）\t\t\t     |\n"
			"|\t\t\tR - 识别字母（Recognize）\t\t     |\n"
			"|\t\t\tQ - 退出程序（Quit）\t\t\t     |\n"
			"|\t\t\t\t\t\t\t\t     |\n"
			"----------------------------------------------------------------------\n");


		//从键盘读取操作
		char operation;
		operation = cin.get();

		if ((char)operation == 'Q')
		{
			//退出程序
			break;
		}
		if ((char)operation == 'T')
		{
			//训练样本
			svmDataTrain();
		}
		if ((char)operation == 'R')
		{
			loop:			//循环
			cin.sync();		//清理缓存
			cout << "请输入待识别图片路径（退出请按Q）：" << endl;
			cin.getline(imgPath, 128);

			string imgPathStr = imgPath;	//将字符数组转为字符串

			if (imgPathStr == "Q")
				break;

			string::size_type jpg = imgPathStr.find(".jpg");
			string::size_type jpeg = imgPathStr.find(".jpeg");
			string::size_type png = imgPathStr.find(".png");
			string::size_type bmp = imgPathStr.find(".bmp");
			string::size_type gif = imgPathStr.find(".gif");

			//如果路径中包含“.jpg”“.jpeg”“.png”“.bmp”“.gif”，则认为路径正确
			if ((jpg != string::npos) || (jpeg != string::npos) || (png != string::npos) || (bmp != string::npos) || (gif != string::npos))
			{
				//cout << "识别中..." << endl;

				//预处理：切割图片，并大小归一化
				int ret = preProcess(imgPath, correctAnswers, score);
				if (ret == -1)
				{
					printf("该图片不存在，程序自动退出...");
					_sleep(3000);
					return -1;
				}
			}
			else
			{
				cout << "路径不正确！" << endl;
				goto loop;
			}
		}

		cin.sync();		//清空缓存
	}

	waitKey(0);
	return 0;
}