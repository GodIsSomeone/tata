## 图像平滑
图像平滑的目的是取出一些特殊的噪声。使用滤波去燥，使得图像更为平滑一些。
1. blur() 均值去噪声

2. GaussianBlur()高斯滤波        

3. medianBlur()中值滤波

4. bilateralFilter()双边滤波


## 膨胀和腐蚀
### dilation
也是用一个内核kernel 去改变archer的值。不过此处的Archer取整个内核的最大值。然后就会扩大。   
```
/*
参数同下，为什么同下，因为我先写的下面
*/
CV_EXPORTS_W void dilate( InputArray src, OutputArray dst, InputArray kernel,
                          Point anchor = Point(-1,-1), int iterations = 1,
                          int borderType = BORDER_CONSTANT,
                          const Scalar& borderValue = morphologyDefaultBorderValue() );
```
### erosion
相反的，此处取的是最小值。
```
/*获取kernel单元
getStructuringElement(int shape, Size ksize, Point anchor = Point(-1,-1));
shape，形状，圆或方，大小，锚点位置，（-1，-1）指的是中间
*/
    Mat element = getStructuringElement(erosion_type,
        Size(2 * erosion_size + 1, 2 * erosion_size + 1),
        Point(erosion_size, erosion_size));
/*
CV_EXPORTS_W void erode( InputArray src, OutputArray dst, InputArray kernel,
                         Point anchor = Point(-1,-1), int iterations = 1,
                         int borderType = BORDER_CONSTANT,
                         const Scalar& borderValue = morphologyDefaultBorderValue() );
 iterations 迭代的次数。
 borderType 老面孔了……
borderValue 边界值
*/
    erode(src, erosion_dst, element);
```
## 其他形态学变换
无非是dilate和erode的反复应用。
### Opening
open = dilate（erode(image)）
### Closing 
close = erode(dilate(image))
### Morphological Fradient
morph = dilate - erode
### top hat
tophat = src - open
### black hat
blackhat = close - src
```
/*
op : operator ,也就是说选择哪种处理方式
*/
CV_EXPORTS_W void morphologyEx( InputArray src, OutputArray dst,
                                int op, InputArray kernel,
                                Point anchor = Point(-1,-1), int iterations = 1,
                                int borderType = BORDER_CONSTANT,
                                const Scalar& borderValue = morphologyDefaultBorderValue() );
```
## Hit-or_Miss
1. Erode src image A with kernel B1;
2. Erode the complement of A (A 的补集)with B2
3. 上述1和2的结果求并集。
```
/*
op的参数变成MORPH_HITMISS
*/
 morphologyEx(input_image, output_image, MORPH_HITMISS, kernel);
```
## Extract horizontal and vertical lines by using morphological operations
1. Load Image 加载图片 imread
2. Grayscale 灰度化
```
cvtColor(src, gray, CV_BGR2GRAY);
```
3. 灰度图转二值图
```
    // Apply adaptiveThreshold at the bitwise_not of gray, notice the ~ symbol
    adaptiveThreshold(~gray, bw, 255, CV_ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);
```
4. 提取操作
```
/*提取horizontal*/
    // Specify size on horizontal axis
    int horizontal_size = horizontal.cols / 30;
    // Create structure element for extracting horizontal lines through morphology operations
    Mat horizontalStructure = getStructuringElement(MORPH_RECT, Size(horizontal_size, 1));
    // Apply morphology operations
    erode(horizontal, horizontal, horizontalStructure, Point(-1, -1));
    dilate(horizontal, horizontal, horizontalStructure, Point(-1, -1));
    
/*提取vertical*/
    // Specify size on vertical axis
    int vertical_size = vertical.rows / 30;
    // Create structure element for extracting vertical lines through morphology operations
    Mat verticalStructure = getStructuringElement(MORPH_RECT, Size(1, vertical_size));
    // Apply morphology operations
    erode(vertical, vertical, verticalStructure, Point(-1, -1));
    dilate(vertical, vertical, verticalStructure, Point(-1, -1));
```

## 图像金字塔
多分辨率表达图像信息
```
/*
@param dstsize size of the output image.
@param borderType Pixel extrapolation method
下同
 */
CV_EXPORTS_W void pyrUp( InputArray src, OutputArray dst,
                         const Size& dstsize = Size(), int borderType = BORDER_DEFAULT );
*/
        else if( c == 'i' )
        { pyrUp( src, src, Size( src.cols*2, src.rows*2 ) );
            printf( "** Zoom In: Image x 2 \n" );
        }
        else if( c == 'o' )
        { pyrDown( src, src, Size( src.cols/2, src.rows/2 ) );
            printf( "** Zoom Out: Image / 2 \n" );
        }
```
## 简单的阈值操作
也即大于某一个值或者在某个范围内即保存，其他情况下赋值为0；就是针对像素值的操作。   
因为是对像素值直接进行比较，所以是对灰度值进行操作。   
```
/*
@param thresh threshold value.
@param maxval maximum value to use with the THRESH_BINARY and THRESH_BINARY_INV thresholding types.
@param type thresholding type (see the cv::ThresholdTypes).
*/
 threshold( src_gray, dst, threshold_value, max_BINARY_value,threshold_type );
```
更为复杂的，上述是对像素进行操作，如果是对RGB进行操作，同样的道理设定RGB的范围，然后进行截取
```
/*
@param lowerb inclusive lower boundary array or a scalar.
@param upperb inclusive upper boundary array or a scalar.
*/
CV_EXPORTS_W void inRange(InputArray src, InputArray lowerb,
                          InputArray upperb, OutputArray dst);
```
## 自定义过滤器进行图像过滤
```

    // Initialize arguments for the filter
    anchor = Point( -1, -1 );
    delta = 0;
    ddepth = -1;
    // Loop - Will filter the image with different kernel sizes each 0.5 seconds
    int ind = 0;
    for(;;)
    {
        // Update kernel size for a normalized box filter
        kernel_size = 3 + 2*( ind%5 );
        kernel = Mat::ones( kernel_size, kernel_size, CV_32F )/ (float)(kernel_size*kernel_size);
        // Apply filter
        filter2D(src, dst, ddepth , kernel, anchor, delta, BORDER_DEFAULT );
        imshow( window_name, dst );
        char c = (char)waitKey(500);
        // Press 'ESC' to exit the program
        if( c == 27 )
        { break; }
        ind++;
    }
```
## 为图像添加花边
属于边缘型功能，后续再看。

## sobel边缘检测算子
其原理是图像在边界处，灰度会发生变化，周围的导数会发生重大变化，随意通过求出导数变化大的地方保留，就得到了边缘。
1. 加载图片，去燥，转变成灰度图
2. sobel操作
```
/*
@param ddepth output image depth, see @ref filter_depths "combinations"; in the case of
    8-bit input images it will result in truncated derivatives.
@param dx order of the derivative x.也就是X方向，
@param dy order of the derivative y.或者是Y方向，
@param ksize size of the extended Sobel kernel; it must be 1, 3, 5, or 7.
@param scale optional scale factor for the computed derivative values; by default, no scaling is
applied (see cv::getDerivKernels for details).
@param delta optional delta value that is added to the results prior to storing them in dst.
@param borderType pixel extrapolation method, see cv::BorderTypes
@sa  Scharr, Laplacian, sepFilter2D, filter2D, GaussianBlur, cartToPolar
 */
CV_EXPORTS_W void Sobel( InputArray src, OutputArray dst, int ddepth,
                         int dx, int dy, int ksize = 3,
                         double scale = 1, double delta = 0,
                         int borderType = BORDER_DEFAULT );
```
3. 转换成CV_8U图像
```
/*
@param alpha optional scale factor.
@param beta optional delta added to the scaled values.
@sa  Mat::convertTo, cv::abs(const Mat&)
*/
CV_EXPORTS_W void convertScaleAbs(InputArray src, OutputArray dst,
                                  double alpha = 1, double beta = 0);
```
4. 增加梯度
```
  addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
```

## laplace算子
因为sobel算子在面对一些左右求导为0的情况，不能很好地识别边缘检测，因此使用laplace算子。
1. 加载图片，高斯去噪声，转变成灰度图，这一步和sobel算子是一样的。
2. laplace操作，具体参数和sobel算子是一样的
```
 Laplacian( src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT );
```
3. 转变成灰度图，显示，这一步和laplace也是一样的。

## canny边缘检测
相较于sobel算子，进行细化，得到更加细化的边缘。
步骤：
1. 高斯模糊，取出噪声，降低伪边缘的识别；但是图像的边缘信息也是高频信号，高斯模糊的半径选择很重要，过大的半径容易让一些弱边缘检测不到。
2. 计算梯度幅值和方向。使用sobel算子计算。边缘粗大明亮。
3. 非最大值抑制。边缘细化。保留局部最大梯度抑制所有其他梯度值，只保留梯度变化中最锐利的位置。（1）比较当前点的梯度强度和政府梯度方向点的梯度强度，（2）如果当前点的梯度和同方向的其他点的梯度强度比较是最大，保留。否则设为0；——————这部分看不太懂。
4. 双阈值。高阈值和低阈值。大于高阈值保留为强边缘点，小于则置为0；之间的点，为弱边缘点。
5. 滞后边界跟踪，如果弱边缘点的8联通领域像素，只要有强边缘点存在，那么这个弱边缘点被认为是边缘保留下来。
代码过程：
1. 加载图片，转换成灰度图，滤波。和sobel边缘检测是一样的过程。
2. Canny检测
```
@param image 8-bit input image.
@param edges output edge map; single channels 8-bit image, which has the same size as image .
@param threshold1 first threshold for the hysteresis procedure.低阈值
@param threshold2 second threshold for the hysteresis procedure.高阈值
@param apertureSize aperture size for the Sobel operator.内核大小
@param L2gradient a flag,梯度设置 ).
 */
CV_EXPORTS_W void Canny( InputArray image, OutputArray edges,
                         double threshold1, double threshold2,
                         int apertureSize = 3, bool L2gradient = false );
```
3. 拷贝图像，显示
```
 dst = Scalar::all(0);
 src.copyTo( dst, detected_edges);
```
## Hough变换，霍夫变换
对于检测标准的规则图形有很大的优势，对于圆，直线等图形，检测效果应该比较好。具体算法没看太懂。
1. 加载图片，灰度图。
2. Canny检测
3. HoughLines基本检测
```
    // Standard Hough Line Transform
  vector<Vec2f> lines; // will hold the results of the detection
  HoughLines(dst, lines, 1, CV_PI/180, 150, 0, 0 ); // runs the actual detection

@param rho. 图像计算分辨率。
@param theta。弧度分辨率。
@param threshold。可以投票的线的阈值
CV_EXPORTS_W void HoughLines( InputArray image, OutputArray lines,
                              double rho, double theta, int threshold,
                              double srn = 0, double stn = 0,
                              double min_theta = 0, double max_theta = CV_PI );
```
4. Probabilistic Hough Line Transform，概率Hough线变换
```
// Probabilistic Line Transform
vector<Vec4i> linesP; // will hold the results of the detection
HoughLinesP(dst, linesP, 1, CV_PI/180, 50, 50, 10 ); // runs the actual detection
    
@minLinLength: The minimum number of points that can form a line.
               Lines with less than this number of points are disregarded.
@maxLineGap: The maximum gap between two points to be considered in the same line.
CV_EXPORTS_W void HoughLinesP( InputArray image, OutputArray lines,
                               double rho, double theta, int threshold,
                               double minLineLength = 0, double maxLineGap = 0 );
```
5. 显示图像。
 
## Hough Circle Transform  圆检测，和直线检测差不多。


## Remapping 
对图像进行翻转，重映射，可能不是点到点的映射，中间或许会经过插值变化。
```


```
## Affine Transformation 仿射变换
在几何中，一个向量空间进行一次线性变换并街上一个平移，变换成另一个向量空间。
也是变换图像的一种，不过可以更加自由变形，当时学的线性代数都还给老师了……

## Histogram 直方图
根据划分的区间，建立直方图。达到均衡的目的。
### 直方图均衡化
这种方法通常用来增加许多图像的全局对比度，尤其是当图像的有用数据的对比度相当接近的时候。通过这种方法，亮度可以更好地在直方图上分布。这样就可以用于增强局部的对比度而不影响整体的对比度，直方图均衡化通过有效地扩展常用的亮度来实现这种功能。
看了半天维基百科终于看懂了
直方图均衡化需要对灰度图进行处理。
```
    src = imread("../data/lena.jpg", IMREAD_COLOR);
    cvtColor(src, src, COLOR_BGR2GRAY);
    equalizeHist(src, dst);
```

### 直方图计算
1. 读入jpg图像，因为是对RGB进行分析，因此需要读入RGB属性。
2. Separate the source image in its three R,G and B planes。
```
vector<Mat> bgr_planes;
/** @overload
@param m input multi-channel array.
@param mv output vector of arrays; the arrays themselves are reallocated, if needed.
*/
CV_EXPORTS_W void split(InputArray m, OutputArrayOfArrays mv);
split( src, bgr_planes );
```
3. 针对RGB分别进行计算直方图
```
    int histSize = 256; // 设立最大值，此处最好设置成宏
    float range[] = { 0, 256 };
    const float* histRange = { range };
    bool uniform = true; bool accumulate = false;
    Mat b_hist, g_hist, r_hist;

    calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

CV_EXPORTS void calcHist( const Mat* images, int nimages,
                          const int* channels, InputArray mask,
                          OutputArray hist, int dims, const int* histSize,
                          const float** ranges, bool uniform = true, bool accumulate = false );
```
4. 展示直方图
```
/*创建展示图像*/
// Draw the histograms for R, G and B
int hist_w = 512; int hist_h = 400;
int bin_w = cvRound( (double) hist_w/histSize );
Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
/*标准化，确保直方图的值都在范围内*/
normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
/*绘画直方图*/
for( int i = 1; i < histSize; i++ )
{
    line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
                     Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
                     Scalar( 255, 0, 0), 2, 8, 0  );
  }
  /*展示*/
  imshow();
```
### 直方图对比
对比两个图像的直方图匹配程度。

## 反向投影
计算一个图形的直方图模型，对比图像特征。

