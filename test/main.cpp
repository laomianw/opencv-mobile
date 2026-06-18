#include <cstdio>
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

#if CV_VERSION_MAJOR >= 3
    {
        cv::Mat img = cv::imread("in.jpg");
        if (!img.empty())
        {
            std::vector<cv::Mat> pages;
            pages.push_back(img);
            pages.push_back(img);

            if (cv::imwritemulti("out_multi.tif", pages))
            {
                std::vector<cv::Mat> read_pages;
                if (cv::imreadmulti("out_multi.tif", read_pages) && read_pages.size() == 2 &&
                    !read_pages[0].empty() && read_pages[0].rows == img.rows && read_pages[0].cols == img.cols && read_pages[0].channels() == img.channels())
                {
                    printf("tiff multi-page round-trip ok\n");
                }
                else
                {
                    printf("tiff multi-page read failed\n");
                }
            }
            else
            {
                printf("tiff multi-page write failed\n");
            }

#if CV_VERSION_MAJOR >= 4
            std::vector<unsigned char> buf;
            if (cv::imencodemulti(".tif", pages, buf))
            {
                std::vector<cv::Mat> decoded_pages;
                if (cv::imdecodemulti(buf, cv::IMREAD_ANYCOLOR, decoded_pages) && decoded_pages.size() == 2 &&
                    !decoded_pages[0].empty() && decoded_pages[0].rows == img.rows && decoded_pages[0].cols == img.cols && decoded_pages[0].channels() == img.channels())
                {
                    printf("tiff multi-page buffer round-trip ok\n");
                }
                else
                {
                    printf("tiff multi-page buffer decode failed\n");
                }
            }
            else
            {
                printf("tiff multi-page buffer encode failed\n");
            }
#endif
        }
    }
#endif

    return 0;
}
