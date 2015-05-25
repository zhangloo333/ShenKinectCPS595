
#include "BS.h"
using namespace cv;
int main()
{
	Mat frame;
	Mat mask(frame.size(), CV_8UC1);
	char c = waitKey(1);

	VideoCapture cap(0);

	if (!cap.isOpened())
	{
		cout << "Cannot open the video file" << endl;
		return -1;
	}

	while (1)
	{
 		cap >> frame;

 		if (frame.cols > 0 && frame.rows > 0)
			{	
				imshow("frame", frame);
				callmouse("frame");
				if (103 == waitKey(1))
				{
					cout << "shabi" << endl;
					frame.copyTo(oignalscreen);


				}
				if (oignalscreen.data != NULL && Keepimg)
				{
					cacRatio(frame, oignalscreen);
					getRoiRation(frame, oignalscreen);

					cout << "Hello word" << endl;
					cout << "ratio[0]=" << ratio[0]
						<< "ratio[1]=" << ratio[1]
						<< "ratio[2]=" << ratio[2] << endl;
				}

				callmouse("B");
				callmouse("G");
				callmouse("R");
				//ChangChannel(x, frame);
				BGsubstraction(frame, mask);
				find_Contour(mask, &mask);
				creatbar();
				imshow("frame", frame);
				namedWindow("mask");
				imshow("mask", mask);
				callmouse("BGtest");
				//if (mousepoint.x > 0 && mousepoint.y > 0)
				//{
				//	cout << "test white point " << frame.at<Vec3b>(mousepoint.y, mousepoint.x);
				//	//mousepoint.x = mousepoint.y = -1;
				//}


				if (c == 27)
					break;

			}
				
		if (27 == waitKey(1))
			break;
	}
	//system("pause");
	return 0;
}