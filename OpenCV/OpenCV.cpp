#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <string>
#include <vector>


cv::Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;
//Генирация точек

const std::vector<std::vector<int>> handColorDetectionDark{ {0,14,49,38,255,49} };
const std::vector<std::vector<int>> handColorDetectionLightin{ {2,15,86,22,255,87} };

std::vector<cv::Scalar> handColorDetectionValuesDark{ {255,228,200} };
std::vector<cv::Scalar> handColorDetectionValuesLightin{ {255,228,200} };



void findColor(cv::Mat img, bool dark)
{
	cv::Scalar lower, upper;
	cv::Mat imgHSV;
	cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);

	for (int i = 0; i < handColorDetectionLightin.size(); i++)
	{
		if (!dark)
		{
			cv::Scalar lower(handColorDetectionLightin[i][0], handColorDetectionLightin[i][1], handColorDetectionLightin[i][2]);
			cv::Scalar upper(handColorDetectionLightin[i][3], handColorDetectionLightin[i][4], handColorDetectionLightin[i][5]);
			cv::Mat mask;
			cv::inRange(imgHSV, lower, upper, mask);
			cv::imshow(std::to_string(i), mask);
			break;
		}
		else
		{

			cv::Scalar lower(handColorDetectionDark[i][0], handColorDetectionDark[i][1], handColorDetectionDark[i][2]);
			cv::Scalar upper(handColorDetectionDark[i][3], handColorDetectionDark[i][4], handColorDetectionDark[i][5]);
			cv::Mat mask;
			cv::inRange(imgHSV, lower, upper, mask);
			cv::imshow(std::to_string(i), mask);
			break;
		}
	}


}


void getContours(cv::Mat imgDil, cv::Mat img) {

	// какаято хуйня творится
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarcgh;

	cv::findContours(imgDil, contours, hierarcgh, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE); //передает даные 
	cv::drawContours(img, contours, -1, cv::Scalar(255, 0, 255), 1);

	std::vector <std::vector<cv::Point>> conPoly(contours.size());
	std::vector <cv::Rect>boundRect(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{

		int area = cv::contourArea(contours[i]);
		std::cout << area << "\n";
		if (area < 20)break;

		else if (area >20)
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

int main()
{
	cv::Mat img;
	cv::flip(img, img, 1);
	cv::VideoCapture cap(0);

	std::string roomType;
	std::cout << "Is it dark or light in the room? (dark/light)" << "\n";
	std::cin >> roomType;


	if (!cap.isOpened())
	{
		std::cerr << "Error: Could not initialize capturing..." << "\n";
		return -1;
	}

	while (true)
	{
		cap.read(img);
		// обычное изображение
		//cv::imshow("Image", img);

		// точки + запуск
		if (roomType == "d")
		{
			findColor(img, true);
			// обыч изображение
			cv::imshow("Image52", img);
		}
		else if (roomType == "l")
		{
			findColor(img, false);
			cv::imshow("Image52", img);
		}
		else
		{
			std::cout << "Invalid input. Please enter 'dark' or 'light'." << "\n";
			break;
		}

		//Линии трекинга
		cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
		cv::GaussianBlur(img, imgBlur, cv::Size(3, 3), 3, 4);
		cv::Canny(imgBlur, imgCanny, 25, 72);
		cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(1, 1));
		cv::dilate(imgCanny, imgDil, kernel);

		// принемает даные и какаято хуйня
		getContours(imgDil, img);
		// изображении линии
		cv::imshow("Image Dil", imgDil);
		// изображение с фиол линиями
		cv::imshow("Image", img);


		//cv::waitKey(30);

		int key = cv::waitKey(1);
		if (key == 'q' || key == 27)
		{
			break;
		}

	}

	return 0;
}