#include "colour-edge-detection.hpp"

void Detect_colour_edges(cv::Mat &image)
{
    cv::Mat hsv_img;
    cv::cvtColor(image, hsv_img, cv::COLOR_BGR2HSV);

    std::vector<cv::Mat> channels;
    cv::split(hsv_img, channels);
    printf("Chanels count: %ld\n", channels.size());

    cv::Mat img_hue = channels[0];
    cv::Mat img_saturation = channels[1];
    cv::Mat img_value = channels[2];
    ShowImage(img_hue, "Hue");
    ShowImage(img_saturation, "Saturation");
    ShowImage(img_value, "Value");

    cv::Mat shifted;
    Shift_Colour_Values(img_hue, shifted, 25);
    ShowImage(shifted, "Hue shifted");

    // cv::Mat image_gausian;
    // cv::GaussianBlur(img_saturation, image_gausian, cv::Size(), 5, 5, cv::BORDER_REPLICATE);
    // ShowImage(image_gausian, "Gausian blur");

    cv::Mat avgImg;
    AverageImage(img_saturation, avgImg, 5);
    ShowImage(avgImg, "Averaged saturation");

    cv::Mat cannyHue;
    cv::Canny(avgImg, cannyHue, 100, 50, 3, false);
    ShowImage(cannyHue, "Canny hue");

    cv::Mat calculated_contours = image.clone();

    for (size_t i = 0; i < 0; i++)
    {
        cv::dilate(cannyHue, cannyHue, cv::Mat());
    }
    
    GetContours(cannyHue, calculated_contours, 10);
    ShowImage(calculated_contours, "Contours");
}

void AverageImage(cv::Mat &input, cv::Mat &output, const size_t multiplier)
{
    output = input.clone();
    float mult = (100 / multiplier)*0.01F;
    cv::resize(output, output, cv::Size(), mult, mult, cv::INTER_LANCZOS4);
    cv::resize(output, output, cv::Size(), multiplier, multiplier, cv::INTER_LANCZOS4);
    cv::GaussianBlur(output, output, cv::Size(), 5, 5, cv::BORDER_REPLICATE);
}

void Shift_Colour_Values(cv::Mat &input, cv::Mat &output, const int shiftedAmount)
{
    const size_t rowAmount = input.rows;
    const size_t colAmount = input.cols;
    size_t i = 0;
    size_t j = 0;
    output = input.clone();
    for  (i = 0; i < rowAmount; ++i)
    {
        for (j = 0; j < colAmount; ++j)
        {
            output.at<uint8_t>(i,j) = (input.at<uint8_t>(i,j) +shiftedAmount) % 180; 
        }
    }
}

void GetContours(cv::Mat &input, cv::Mat &output, const size_t minSize)
{
    // Extracting contours out of a canny image
    std::vector<std::vector<cv::Point>> contours4;
    std::vector<cv::Vec4i> hierachy4;
    cv::findContours(input, contours4, hierachy4, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
    // output = input.clone();
    for (size_t i = 0; i < contours4.size(); i++)
    {
        // Ignore the innner ones
        if(cv::contourArea(contours4[i]) < minSize)
            continue;

        // Ignore the outer ones
        if(hierachy4[i][3] < 0)
            continue;

        cv::drawContours(output, contours4, i, cv::Scalar(0, 0, 255), 2, 8, hierachy4, 0);
    }
       
}