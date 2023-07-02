#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <stdint.h>

int main(int argc, char **argv);
void ShowImage(cv::Mat &image, const char* imageName);

#endif