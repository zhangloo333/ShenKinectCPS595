//
//  rewrite2.cpp
//  test
//
//  Created by LEI ZHANG on 15/3/24.
//  Copyright (c) 2015年 ZhangYi. All rights reserved.
//

#include "BS.h"
int Bmin = 0, Bmax = 120, Gmin = 100, Gmax = 255, Rmin = 0, Rmax = 120;
Point mousepoint=(-1,-1);
int ratio[3] = {1,1,1};
bool Keepimg = false;
Mat oignalscreen;

Mat scalarMat(int bmin, int gmin, int rmin, int bmax, int gmax, int rmax,Mat BGframe)
{
	rmin += ratio[0];
	gmin += ratio[1];
	bmin += ratio[2];
	rmax += ratio[0];
	gmax += ratio[1];
	bmax += ratio[2];

	Mat mask;
	Mat scalarRangMin(1, 3, CV_8UC3, Scalar(bmin, gmin, rmin));
	Mat scalarRangMax(1, 3, CV_8UC3, Scalar(bmax, gmax, gmax));
	inRange(BGframe, scalarRangMin, scalarRangMax, mask);
	return mask;
}

void BGsubstraction(Mat &BGframe, Mat &BGmask)
{	
	Mat BGtemp[7]; 
	BGtemp[0] = scalarMat(0,100,0,120,255,120,BGframe);
	BGtemp[1] = scalarMat(120,200, 60, 255, 255, 255, BGframe);
	BGtemp[2] = scalarMat(34, 85, 237, 210, 247, 245, BGframe);
	BGtemp[3] = scalarMat(165, 190, 90, 223, 241, 147, BGframe);
	BGtemp[4] = scalarMat(220, 230, 140, 250, 247, 175, BGframe);
	BGtemp[5] = scalarMat(Bmin, Bmin, Rmin, Rmax, Gmax, Gmax, BGframe);

	BGmask = BGtemp[0] + BGtemp[1] + BGtemp[2] + BGtemp[3] + BGtemp[4] + BGtemp[5];
	bitwise_not(BGmask, BGmask);
	imshow("BGtest", BGmask);
} 

void find_Contour(Mat &mask1, Mat*fmask)
{
	int largest_area = 0;
	int largest_contour_index = 0;
	if (mask1.rows > 1 && mask1.cols > 1)
	{
		Mat scr(mask1.rows, mask1.cols, CV_8UC1);
		Mat dst(mask1.rows, mask1.cols, CV_8UC1, Scalar::all(0));
		scr = mask1;
		vector<std::vector<cv::Point> > contours;
		vector<Vec4i>hierarchy;
		contours.clear();
		hierarchy.clear();
		findContours(scr, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
		for (int i = 0; i<contours.size(); i++)
		{
			int a = contourArea(contours[i], false);
			if (a>largest_area)
			{
				largest_area = a;
				largest_contour_index = i;
			}
		}
		Scalar color(255, 255, 255);
		drawContours(dst, contours, largest_contour_index, color, CV_FILLED, 8, hierarchy);
		*fmask = dst;

	}
	else
		return;

}

//test mouse function

void onMouse(int event, int x, int y, int flags, void *param)
{
	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN:
		cout << "x= " << x << "y= " << y << endl;
		mousepoint.x = x;
		mousepoint.y = y;
		Keepimg = true;
		break;
	case CV_EVENT_LBUTTONUP:
		break;
	}
}

Mat getROI(Mat &imag, Point P)
{
	Mat ROI;
	return ROI= imag(Rect(P.x,P.y,50,50));

}

void getRoiRation(Mat &Gframe, Mat &Gorignal)
{ 
	if (mousepoint.y > 0 || mousepoint.x > 0)
	{
		Mat ROIf = getROI(Gframe, mousepoint);
		Mat ROIo = getROI(Gorignal, mousepoint);
		Mat ratio = ROIf - ROIo;
		Scalar mean1;
		Mat channel[3];
		split(ratio, channel);
		mean1=mean(ratio);
		for (int i = 0; i <3;i++)
		{
			cout << "mean[]=" << mean1[i] << endl;
		}


	}

}


void cacRatio(Mat &Cframe, Mat &Corignal)
{
	if (mousepoint.y > 0 || mousepoint.x > 0)
	{
		int a[3];
		int b[3];
		for (int i = 0; i < 3; i++)
		{
			a[i] = Cframe.at<Vec3b>(mousepoint.y, mousepoint.x)[i];

			b[i] = Corignal.at<Vec3b>(mousepoint.y, mousepoint.x)[i];
			ratio[i] = a[i] - b[i];
		}
		cout <<"coriganl=" << Corignal.at<Vec3b>(mousepoint.y, mousepoint.x)
			<< "Cframe = " << Cframe.at<Vec3b>(mousepoint.y, mousepoint.x)<<endl;
	}
}



void callmouse(string winname1)
{


	//if (winname1 == "B")
	//	//cout << "Bchannel" << endl;
	//else if(winname1 == "G")
	//	//cout << "Gchannel" << endl;
	//else if(winname1 == "R")
	//	//cout << "Gchannel" << endl;
	setMouseCallback(winname1, onMouse);

}


// up for test

void creatbar()
{
	namedWindow("bar");
	createTrackbar("Bmin", "bar", &Bmin, 255);
	createTrackbar("Bmax", "bar", &Bmax, 255);
	createTrackbar("Gmin", "bar", &Gmin, 255);
	createTrackbar("Gmax", "bar", &Gmax, 255);
	createTrackbar("Rmin", "bar", &Rmin, 255);
	createTrackbar("Rmax", "bar", &Rmax, 255);

}

void ChangChannel(Mat &CMx,Mat &CMframe )
{
	Mat channels[4];
	split(CMx, channels);
	merge(channels, 3, CMframe);

	/*test for print histogram*/
	Histogram h;
	namedWindow("B", 1);
	imshow("B", h.getHistogramImage(channels[0]));
	//h.PRangehis(x_hist, channels[0]);

	//callmouse("B");


	namedWindow("G", 2);
	imshow("G", h.getHistogramImage(channels[1]));


	namedWindow("R", 3);
	imshow("R", h.getHistogramImage(channels[2]));





	//cout << "B" << endl;
	//findMaxMin(channels[0], CMframe);
	//cout << "g" << endl;
	//findMaxMin(channels[1], CMframe);
	//cout << "r" << endl;
	//findMaxMin(channels[2], CMframe);

}

void findMaxMin(Mat &fMMim, Mat fMMreal)
{
	double minVal;
	double maxVal;
	Point minLoc;
	Point maxLoc;

	minMaxLoc(fMMim, &minVal, &maxVal, &minLoc, &maxLoc);

	cout << "min val : " << minVal << endl;
	cout << "max val: " << maxVal << endl;
	cout << "minLoc : " << minLoc << endl;
	cout << "maxloc : " << maxLoc << endl;
	cout << fMMreal.at<cv::Vec3b>(minLoc.y, minLoc.x);
	cout << fMMreal.at<cv::Vec3b>(maxLoc.y, maxLoc.x);

	cout << endl << endl;

}
