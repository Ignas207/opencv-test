#include "display.hpp"
#include "colour-edge-detection.hpp"
#include <filesystem>

#define INITIAL_IMAGE "Initial image"
#define GRAYSCALE_IMG "Grayscale image"

static void FindContours(cv::Mat &image, cv::OutputArrayOfArrays &contours, cv::OutputArray &hierarchy);
static void OpenImg(cv::Mat &image, const char* fileName, uint32_t maxX, uint32_t maxY);

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    printf("Path: %s\n", argv[1]);
    
    cv::Mat image;
    image = cv::imread(argv[1], cv::IMREAD_COLOR);
    if (!image.data)
    {
        printf("No image data \n");
        return -1;
    }

    // printf("image size: (%d, %d)\n", image.rows, image.cols);
    cv::Size size1;
    cv::resize(image, image, size1, 0.3F, 0.3F, cv::INTER_LANCZOS4);
    printf("image size: (%d, %d)\n", image.rows, image.cols);

    ShowImage(image, INITIAL_IMAGE);
    // cv::waitKey(1000);

    Detect_colour_edges(image);

    /*
    cv::Mat imageGrayscale;

    cv::cvtColor(image, imageGrayscale, cv::COLOR_BGR2GRAY);

    // ShowImage(imageGrayscale, GRAYSCALE_IMG);
    // cv::waitKey(0);

    cv::Mat image_gausian;
    cv::Size sz;
    cv::GaussianBlur(image, image_gausian, sz, 5, 5, cv::BORDER_REPLICATE);
    ShowImage(image_gausian, "Gausian blur");

    cv::Mat imgCanny;
    cv::Canny(imageGrayscale, imgCanny, 0.0F, 1.0F, 3, true);
    ShowImage(imgCanny, "Canny edge");

    
    cv::Mat dilateImg;
    cv::Mat dilateKernel;
    dilateKernel.ones(5, 5, 0);
    cv::Point anchor = cv::Point(-1,-1);
    cv::dilate(imgCanny, dilateImg, dilateKernel, anchor, 3);
    

    // ShowImage(dilateImg, "Dilated image");

    cv::Mat erodedImg;
    cv::erode(dilateImg, erodedImg, dilateKernel, anchor, 2);

    // ShowImage(erodedImg, "Eroded image");

    // cv::findContours()

    cv::OutputArrayOfArrays contours = {};
    cv::OutputArray contour_hierarchy = {};
    // FindContours(image_gausian, contours, contour_hierarchy);
    */
    cv::waitKey(0);
    return 0;
}

static void OpenImg(cv::Mat &image, const char* fileName, uint32_t maxX, uint32_t maxY)
{
    image = cv::imread(fileName, cv::IMREAD_COLOR);
    // if(image.rows )
}

static void GetFinalContours(cv::OutputArrayOfArrays &contours)
{
    auto amount = contours.getSz().area();
    for (size_t i = 0; i < amount; i++)
    {
        
    }
    
    
}

static void FindContours(cv::Mat &image, cv::OutputArrayOfArrays &contours, cv::OutputArray &hierarchy)
{
    cv::findContours(image, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
}

void ShowImage(cv::Mat &image, const char* imageName)
{
    cv::namedWindow(imageName, cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO | cv::WINDOW_GUI_EXPANDED);
    cv::imshow(imageName, image);
}