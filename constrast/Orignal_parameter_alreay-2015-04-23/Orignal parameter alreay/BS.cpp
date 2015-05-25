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

void BGsubstraction(Mat &BGframe, Mat &BGmask)
{
	
	Mat mask2, mask3, mask4, mask5, mask6,mask7;

	Mat scalarRangMin1(1, 3, CV_8UC3, Scalar(0, 100, 0));
	Mat scalarRangMax1(1, 3, CV_8UC3, Scalar(120, 255, 120));
	inRange(BGframe, scalarRangMin1, scalarRangMax1, mask2);

	Mat scalarRangMin2(1, 3, CV_8UC3, Scalar(120, 200, 60));//b orignal 100 change 85 chang to 60,g from 230 chang to 200
	Mat scalarRangMax2(1, 3, CV_8UC3, Scalar(255, 255, 255));
	inRange(BGframe, scalarRangMin2, scalarRangMax2, mask3);

	Mat scalarRangMin3(1, 3, CV_8UC3, Scalar(0, 80, 0));
	Mat scalarRangMax3(1, 3, CV_8UC3, Scalar(40, 100, 50));//r orignal 31 chang to 40
	inRange(BGframe, scalarRangMin3, scalarRangMax3, mask4);

	Mat scalarRangMin4(1, 3, CV_8UC3, Scalar(0, 40, 0));//g orginal from 62 chang to 50
	Mat scalarRangMax4(1, 3, CV_8UC3, Scalar(18, 80, 20));//b orignal 20 chahe t0 50
	inRange(BGframe, scalarRangMin4, scalarRangMax4, mask5);


	//tool bar
	int _bmin = 0, _bmax = 0, _gmin = 0, _gmax = 0, _rmin = 0, _rmax = 0;
	_bmin = Bmin, _bmax = Bmax, _gmin = Gmin, _gmax = Gmax, _rmin = Gmin, _rmax = Gmax;
	Mat scalarRangMin5(1, 3, CV_8UC3, Scalar(min(_bmin, _bmax), min(_gmin, _gmax), min(_rmin, _rmax)));
	Mat scalarRangMax5(1, 3, CV_8UC3, Scalar(max(_bmin, _bmax), max(_gmin, _gmax), max(_rmin, _rmax)));
	inRange(BGframe, scalarRangMin5, scalarRangMax5, mask6);

	// test
	Mat scalarRangMin7(1, 3, CV_8UC3, Scalar(34,85, 19));
	Mat scalarRangMax7(1, 3, CV_8UC3, Scalar(210, 247, 90)); //red increase form 99 to 165
	inRange(BGframe, scalarRangMin7, scalarRangMax7, mask7);

	Mat mask8;
	Mat scalarRangMin8(1, 3, CV_8UC3, Scalar(34, 85, 237)); //RED FROM 237 TO 240
	Mat scalarRangMax8(1, 3, CV_8UC3, Scalar(210, 247, 245));
	inRange(BGframe, scalarRangMin7, scalarRangMax7, mask8);

	Mat mask9;
	Mat scalarRangMin9(1, 3, CV_8UC3, Scalar(165, 190, 90)); //RED FROM 237 TO 240
	Mat scalarRangMax9(1, 3, CV_8UC3, Scalar(223, 241, 147)); //RED CHANGE 223 TO 230
	inRange(BGframe, scalarRangMin9, scalarRangMax9, mask9);

	Mat mask10;
	Mat scalarRangMin10(1, 3, CV_8UC3, Scalar(220, 230, 140)); //RED FROM 237 TO 240
	Mat scalarRangMax10(1, 3, CV_8UC3, Scalar(250, 247, 175));
	inRange(BGframe, scalarRangMin10, scalarRangMax10, mask10);

	Mat mask11;
	Mat scalarRangMin11(1, 3, CV_8UC3, Scalar(140, 170, 80)); //RED FROM 237 TO 240
	Mat scalarRangMax11(1, 3, CV_8UC3, Scalar(209, 250, 190));
	inRange(BGframe, scalarRangMin11, scalarRangMax11, mask11);

	BGmask = mask8 + mask9+mask10+mask11;
	bitwise_not(BGmask, BGmask);
	//imshow("BGtest", BGmask);
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
		break;

	case CV_EVENT_LBUTTONUP:
		break;
	}
}

void callmouse(string winname1)
{


	if (winname1 == "B")
		cout << "Bchannel" << endl;
	else if(winname1 == "G")
		cout << "Gchannel" << endl;
	else if(winname1 == "R")
		cout << "Gchannel" << endl;
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


