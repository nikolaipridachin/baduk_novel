//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc.hpp>
#include <iostream>
#include "Game.h"
//#include "base64.h"

int main() {
	/*
	std::string image_path = "megavolt.jpg";
	cv::Mat image = imread(image_path, cv::IMREAD_COLOR);
	resize(image, image, {256, 256}, 0, 0, cv::INTER_LINEAR);
	cv::imwrite("megavolt_small.jpg", image);

	std::vector<uchar> buffer;
	cv::imencode(".jpg", image, buffer);
	std::string encodedData = base64_encode(&buffer[0], buffer.size() * sizeof(uchar));

	std::cout << encodedData << std::endl;

	std::vector<BYTE> decodedData = base64_decode(encodedData);
	cv::Mat image2 = cv::imdecode(decodedData, cv::IMREAD_COLOR);

	cv::imwrite("megavolt_DECODED.jpg", image2);
	*/
	Game game;
	while (game.running()) {
		game.Update();
		game.Render();
	}
	return 0;
}