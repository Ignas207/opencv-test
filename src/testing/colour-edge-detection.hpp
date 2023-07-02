#ifndef COLOUR_EDGE_DETECTION_HPP
#define COLOUR_EDGE_DETECTION_HPP

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "display.hpp"

void Detect_colour_edges(cv::Mat &image);
void Shift_Colour_Values(cv::Mat &input, cv::Mat &output, const int shiftedAmount);
void GetContours(cv::Mat &input, cv::Mat &output, const size_t minSize);
void AverageImage(cv::Mat &input, cv::Mat &output, const size_t multiplier);

#endif