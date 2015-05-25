#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

//void BGsubstraction(Mat BGframe, Mat *BGmask);

void BGsubstraction(Mat &BGframe,Mat&BGmask);

void find_Contour(Mat &mask1, Mat*fmask);

void creatbar();
void ChangChannel(Mat &CMx, Mat &CMframe);

void findMaxMin(Mat &fMMim, Mat fMMreal);
//test
void onMouse(int event, int x, int y, int flag, void *param);

void callmouse(string winname1);

Mat scalarMat(int bmin, int gmin, int rmin, int bmax, int gmax, int rmax, Mat BGframe);

void cacRatio(Mat &Cframe, Mat &Corignal);
void getRoiRation(Mat &Gframe, Mat &Gorignal);


class Histogram{
private:
	int histSize[1]; // number of bins
	float hrange[2]; //min and max pixle value
	const float* ranges[1];
	int channels[1]; // only 1 channel used here

public:
	Histogram()
	{
		histSize[0] = 256;
		hrange[0] = 0.0;
		hrange[1] = 255.0;
		ranges[0] = hrange;
		channels[0] = 0;
	}// initial funciton

	Mat getHistogram(Mat &image) //MatND same with Mat in last version
	{
		Mat hist;
		cv::calcHist(&image,
			1, // histogram from 1 image only
			channels, // the channel used
			cv::Mat(), // no mask is used
			hist, // the resulting histogram
			1, // it is a 1D histogram
			histSize, // number of bins
			ranges // pixel value range
			);
		return hist;
	}

	void showHist(Mat &image,int x1)
	{
		Mat histo = getHistogram(image);
		for (int i = 0; i < histSize[0]; i++)
		{
			cout << " Value " << i << " = " <<
				histo.at<float>(i)<<"\t";
		}
	}

	cv::Mat getHistogramImage(Mat &image)
	{
		Mat hist = getHistogram(image);
		double maxVal = 0;
		double minVal = 0;
		minMaxLoc(hist, &minVal, &maxVal, 0, 0);
		Mat histImage(histSize[0], histSize[0], CV_8U, cv::Scalar(255));

		int hpt = static_cast<int>(0.9*histSize[0]);
		for (int h = 0; h < histSize[0]; h++)
		{
			float binval = hist.at<float>(h);
			int intensive = binval*hpt / maxVal;
			line(histImage, Point(h, histSize[0]), Point(h, histSize[0] - intensive), Scalar::all(0));

		}
		return histImage;
	}

	void PRangehis(int x1, Mat &image1)
	{
		if (x1 > 0)
		{
			Mat temp;
			temp = getHistogram(image1);
			cout << temp.at<float>(x1) << endl << endl;

		}
	}

};

extern int Bin, Bmax, Gmin, Gmax, Rmin, Rmax;
extern Point mousepoint;
extern float Resion;
extern Mat oignalscreen;
extern bool Keepimg;
extern int ratio[3];
//extern vector<Point>KTT;