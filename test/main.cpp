#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main()
{
    cv::Mat bgr = cv::imread("in.jpg", 1);

    cv::resize(bgr, bgr, cv::Size(200, 200));

    cv::imwrite("out.jpg", bgr);

    // TIFF round-trip smoke test
    cv::imwrite("out.tif", bgr);
    cv::Mat tiff_bgr = cv::imread("out.tif", 1);
    if (!tiff_bgr.empty())
    {
        cv::imwrite("out2.tif", tiff_bgr);
    }

    return 0;
}
