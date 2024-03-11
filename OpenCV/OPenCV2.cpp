#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include<opencv2/objdetect.hpp>

#include <iostream>
#include <string>
#include <vector>

#include <chrono>
#include <thread>



//Photo//
/*
int main()
{

	std::string path = "Surs/Sigma.jpg";
	cv::Mat img = cv::imread(path);
	cv::Mat imgGreay, imgBlur;


	cv::cvtColor(img, imgGreay, cv::COLOR_BGR2GRAY);
	cv::GaussianBlur(img, imgBlur, cv::Size(9,9 ), 5, 0);

	//imshow("Image", img);
	//imshow("Image Gray", imgGreay);
	imshow("Image Blur", imgBlur);

	cv::waitKey(0);
}

*/

//Video//
/*
int main()
{
	cv::Mat img;

	std::string path = "Surs/video.mp4";
	cv::VideoCapture cap(path);


	for (;;) {

		cap.read(img);
		cv::imshow("Image", img);
		cv::waitKey(8);

		int key = cv::waitKey(1);
		if (key == 'q' || key == 27) {
			break;
		}
	}

}
*/



//VEBCAM//
/*
int main()
{
	cv::Mat img;

	cv::VideoCapture cap(0);


	for (;;) {

		cap.read(img);
		cv::flip(img, img, 1);
		cv::imshow("Image", img);

		int key = cv::waitKey(1);
		if (key == 'q' || key == 27) {
			break;
		}
	}

}
*/

/*
cv::Mat imgHSV, mask , imgColor;
int hmin = 0, smin = 0, vmin = 0;
int hmax = 255, smax = 255, vmax = 255;

cv::VideoCapture cap(0);
cv::Mat img;

int main() {
	cv::namedWindow("Trackbars", (640, 200));
	cv::createTrackbar("Hue Min", "Trackbars", &hmin, 179);
	cv::createTrackbar("Hue Max", "Trackbars", &hmax, 179);
	cv::createTrackbar("Sat Min", "Trackbars", &smin, 255);
	cv::createTrackbar("Sat Max", "Trackbars", &smax, 255);
	cv::createTrackbar("Val Min", "Trackbars", &vmin, 255);
	cv::createTrackbar("Val Max", "Trackbars", &vmax, 255);

	for (;;) 
	{
		cap.read(img);
		cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);

		cv::Scalar lower(hmin, smin, vmin);
		cv::Scalar upper(hmax, smax, vmax);


		cv::inRange(imgHSV, lower, upper, mask);

		std::cout << hmin << "," << smin << "," << vmin << "," << hmax << "," << smax << "," << vmin << "\n";
		cv::imshow("Image", img);
		cv::imshow("Mask", mask);
		cv::waitKey(1);

		int key = cv::waitKey(1);
		if (key == 'q' || key == 27) {
			break;
		}

	}

}

*/
/*
void getContours(cv::Mat imgDil, cv::Mat img) {

	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarcgh;

														// потыкать этот параметр
	cv::findContours(imgDil, contours, hierarcgh, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	std::vector <std::vector<cv::Point>> conPoly(contours.size());
	std::vector <cv::Rect>boundRect(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{

		int area = cv::contourArea(contours[i]);
		std::cout << area <<"\n";
		if (area > 1000) 
		{
			float peri = cv::arcLength(contours[i], true);
			cv::approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			cv::drawContours(img, conPoly, i, cv::Scalar(255, 0, 255), 3);
			std::cout << conPoly[i].size() << "\n";
			boundRect[i] = boundingRect(conPoly[i]);
			cv::rectangle(img, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0, 255, 0), 3);
		}

	}

}

int main() {
	cv::Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

	std::string path = "Surs/figur.jpg";
	cv::Mat img = cv::imread(path);

	//cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
	cv::GaussianBlur(img, imgBlur, cv::Size(3, 3), 3, 4);
	cv::Canny(imgBlur, imgCanny, 25, 72); //25 ,75
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	cv::dilate(imgCanny, imgDil, kernel);

	//cv::erode(imgDil, imgErode, kernel);

	getContours(imgDil, img);

	cv::imshow("Image", img);
	//cv::imshow("Image Blur", imgBlur);
	//cv::imshow("Image Canny", imgCanny);
	//cv::imshow("Image Dil", imgDil);
	cv::waitKey(0);
	return 0;
}
*/




