#include "Common.h"
#include "kColor.h"
#include "BS.h"
using namespace cv;
int main()
{
	Mat x;
	kColor c;
	Mat frame;
	Mat mask(frame.size(), CV_8UC1);




	c.InitializeDefaultSensor();

	VideoCapture cap(0);
	if (!cap.isOpened())
	{
		cout << "Cannot open the video file" << endl;
		return -1;
	}



	while (1){
		int z = c.Update(x);
		if (z >= 0)
		{
			
			if (x.cols > 0 && x.rows > 0)
			{
				imshow("Co", x);
				callmouse("B");
				callmouse("G");
				callmouse("R");
				ChangChannel(x, frame);
				BGsubstraction(frame, mask);
				find_Contour(mask, &mask);
				creatbar();
				namedWindow("mask");
				imshow("mask", mask);
				callmouse("BGtest");
				if (mousepoint.x > 0 && mousepoint.y > 0)
				{
					cout << "test white point " << frame.at<Vec3b>(mousepoint.y, mousepoint.x);
					mousepoint.x = mousepoint.y = -1;
				}

				char c = waitKey(1);
				if (c == 27)
					break;

			}
				
		}
		if (27 == waitKey(1))
			break;
	}
	//system("pause");
	return 0;
}