#pragma once
#ifndef COREMODULE_H
#define COREMODULE_H
#include <iostream> // for standard I/O
#include <string>   // for strings
#include <iomanip>  // for controlling float print precision
#include <sstream>  // string to number conversion
#include <opencv2/core.hpp>     // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/imgproc.hpp>  // Gaussian Blur
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>  // OpenCV window I/O
using namespace std;
using namespace cv;

/*操作像素点，进行掩膜处理*/
void Sharpen(Mat& inputMat, Mat& outputMat)
{
    CV_Assert(inputMat.depth() == CV_8U); //接收u8类型的char
    const int nChannels = inputMat.channels();
    /*We create an output image with the same size and the same type as our input*/
    outputMat.create(inputMat.size(), inputMat.type());
    for (int i = 1; i<inputMat.rows-1; ++i)
    {
        const uchar* pre = inputMat.ptr<uchar>(i - 1);
        const uchar* cur = inputMat.ptr<uchar>(i    );
        const uchar* nxt = inputMat.ptr<uchar>(i + 1);
        uchar* output = outputMat.ptr<uchar>(i);
        for (int j = nChannels; j < nChannels*(inputMat.cols - 1); ++j)
        {
            *output++ = saturate_cast<uchar>(5 * cur[j] - cur[j - nChannels] -
                                            cur[j + nChannels] - pre[j] - nxt[j]);
        }
        /*边界处理，直接赋值为0*/
        outputMat.row(0).setTo(Scalar(0));
        outputMat.row(outputMat.rows - 1).setTo(Scalar(0));
        outputMat.col(0).setTo(Scalar(0));
        outputMat.col(outputMat.cols - 1).setTo(Scalar(0));
    }
}
/*掩膜处理*/
void MaskOperator()
{
    do 
    {
        const string filename = "../data/lena.jpg";
        Mat srcMat;
        const string srcWindow = "srcWindow";
        srcMat = imread(filename, IMREAD_COLOR);

        if (srcMat.empty())
        {
            cout << "can't open the image: " << filename << endl;
            break;
        }
        namedWindow(srcWindow, WINDOW_AUTOSIZE);
        //namedWindow("srcWindow", WINDOW_AUTOSIZE);
        imshow(srcWindow, srcMat);

        Mat dstMat;
        const string dstWindow = "dstWindow";
        namedWindow(dstWindow, WINDOW_AUTOSIZE);
        Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0,
                                          -1, 5, -1,
                                           0, -1, 0);

        /*使用原有的库，计算处理时间*/
        double time = (double)getTickCount();
        filter2D(srcMat, dstMat, srcMat.depth(), kernel);
        time = ((double)getTickCount() - time) / getTickFrequency();
        cout << "Built-in filter2D time passed inseconds: " << time << endl;
        imshow(dstWindow, dstMat);

        /*自己处理像素点，计算处理时间*/
        time = (double)getTickCount();
        Mat sharpenMat;
        const string sharpenWindow = "sharpenWindow";
        namedWindow(sharpenWindow, WINDOW_AUTOSIZE);
        Sharpen(srcMat, sharpenMat);
        time = ((double)getTickCount() - time) / getTickFrequency();
        cout << "Built-in sharpen time passed inseconds: " << time << endl;
        imshow(sharpenWindow, sharpenMat);
    } while (0);

    waitKey();
    return;
}


void Fourier()
{
    do 
    {
        const string filename = "../data/lena.jpg";
        Mat I = imread(filename, IMREAD_GRAYSCALE);
        if (I.empty()) {
            cout << "Error opening image" << endl;
            break;
        }

        Mat padded;                            //expand input image to optimal size
        /*
        当图像的大小是2、3、5 的倍数的时候，DFT的性能最优
        getOptimalDFTSize，顾名思义
        copyMakeBorder 卷积边界。把目标图像放在中间或者上下左右，简化边界处理
        copyMakeBorder(InputArray src, OutputArray dst,
                                 int top, int bottom, int left, int right,
                                 int borderType, const Scalar& value = Scalar() );
        */
        int m = getOptimalDFTSize(I.rows);
        int n = getOptimalDFTSize(I.cols); // on the border add zero values
        copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));
        /*
        计算复杂值，合并。
        count 图像的维度
        merge(const Mat* mv, size_t count, OutputArray dst);
        */
        Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
        Mat complexI;
        merge(planes, 2, complexI);   // Add to the expanded another plane with zeros

        /*傅里叶变换*/
        dft(complexI, complexI);  // this way the result may fit in the source matrix
        // compute the magnitude and switch to logarithmic scale
        // => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
        /*转换幅度值*/
        split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
        magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
        /*切换到对数*/
        Mat magI = planes[0];
        magI += Scalar::all(1);                    // switch to logarithmic scale
        log(magI, magI);
        /*第一步的时候对图像进行expand，这一步恢复 Crop and rearrange*/
        // crop the spectrum, if it has an odd number of rows or columns
        magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));
        // rearrange the quadrants of Fourier image  so that the origin is at the image center
        int cx = magI.cols / 2;
        int cy = magI.rows / 2;
        Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
        Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
        Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
        Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right
        Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
        q0.copyTo(tmp);
        q3.copyTo(q0);
        tmp.copyTo(q3);
        q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
        q2.copyTo(q1);
        tmp.copyTo(q2);
        normalize(magI, magI, 0, 1, NORM_MINMAX); // Transform the matrix with float values into a
                                                // viewable image form (float between values 0 and 1).
        imshow("Input Image", I);    // Show the result
        imshow("spectrum magnitude", magI);
    } while (0);

    waitKey();
    return;
}

#endif
