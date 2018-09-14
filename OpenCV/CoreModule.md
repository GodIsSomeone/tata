## Mat 
### Mat初始化
刚开始的时候OpenCV不是用的Mat，而是用的IPLIMage，使用C写的，但是存在一些内存问题，需要自己申请自己释放，后来有了C++，就用了Mat，内部不知道是怎么实现的。
Mat包含两个部分：矩阵头和矩阵中的像素值
具体初始化方式
```
/*the copy operators will only copy the headers and the pointer to the large matrix, not the data itself*/
Mat A, C;                          // creates just the header parts
A = imread(argv[1], IMREAD_COLOR); // here we'll know the method used (allocate matrix)
Mat B(A);                                 // Use the copy constructor
C = A;  

/*Their headers are different, however, and making a modification
 *using any of them will affect all the other ones as well*/
/*只是拷贝了对应的地址，实际数据并没有发生变化*/
Mat D (A, Rect(10, 10, 100, 100) ); // using a rectangle
Mat E = A(Range::all(), Range(1,3)); // using row and column boundaries

/*深拷贝*/
Mat F = A.clone();
Mat G;
A.copyTo(G);
```
### Mat的存储方式
存储方式，就是色彩体系    
1. RGB，但是在OpenCV内部使用的是BGR。   
2. HSV and HLS 方式   
3. YCrCb is used by the popular JPEG image format.
4. CIE L*a*b* is a perceptually uniform color space（好像用的不多啊）

### Mat的创建

```
/*二维图像，前面两个参数是行列计数，
第三个参数 存储元素的数据类型和每个矩阵点的信道数：
          CV_[The number of bits per item][Signed or Unsigned][Type Prefix]C[The channel number]
          CV_8UC3就是u8类型，每隔像素点有三个channel。（这个地方官网有一个语法错误，this are  哈哈哈。）
          The cv::Scalar is four element short vector
第四个参数是 four element short vector
*/
Mat M(2,2, CV_8UC3, Scalar(0,0,255));
M.create(4,4, CV_8UC(2));

```

## 掩膜处理
### Mask的作用
1. 抠图，把需要显示的部分设置成1，其他设置成0 ，保留想要保留的，删除不想保留德就行了。
2. 凸显某些特征信息，比重设置的大一点就行了
### Mask的参数
filter2D，其实从函数名称也可以看出来，并不包含Mask，而是二维过滤的意思。
```
CV_EXPORTS_W void filter2D( InputArray src, OutputArray dst, int ddepth,
                            InputArray kernel, Point anchor = Point(-1,-1),
                            double delta = 0, int borderType = BORDER_DEFAULT );
参数三：目标图像的期望深度。也即dstDepth
参数四：过滤处理内核
参数五：内核的锚点，锚点的作用暂时搞不清楚
参数六：内核处理完之后的像素值，再加上delta。
参数七：像素外推准则。也不太清楚。图像边框类型。
```
## 图像操作
### 获取像素值
```
/*Here is an example for a single channel grey scale image (type 8UC1) and pixel coordinates x and y*/
Scalar intensity = img.at<uchar>(y, x); // 获取某一坐标的强度值
Scalar intensity = img.at<uchar>(Point(x, y)); //

/*Now let us consider a 3 channel image with BGR color ordering */
Vec3b intensity = img.at<Vec3b>(y, x);
uchar blue = intensity.val[0];
uchar green = intensity.val[1];
uchar red = intensity.val[2];
/*浮点型的*/
Vec3f intensity = img.at<Vec3f>(y, x);
float blue = intensity.val[0];
float green = intensity.val[1];
float red = intensity.val[2];

/*3D模型*/
vector<Point2f> points;
//... fill the array
Mat pointsMat = Mat(points);
```

### 内存操作
```
/*只是引用，并不是直接拷贝内存，所以points的内存要比pointsMat长！*/
std::vector<Point3f> points;
Mat pointsMat = Mat(points).reshape(1);// .. fill the array
/*拷贝内存*/
Mat img = imread("image.jpg");
Mat img1 = img.clone();
/*处理图像时，如果是空，接口会申请内存*/
Mat img = imread("image.jpg");
Mat sobelx;
Sobel(img, sobelx, CV_32F, 1, 0);
```

### 申请图像
```
img = Scalar(0);//得到一个黑色的图像

/*和以前的接口转换*/
Mat img = imread("image.jpg");
IplImage img1 = img;
CvMat m = img;

/*RGB转灰度图*/
Mat img = imread("image.jpg"); // loading a 8UC3 image
Mat grey;
cvtColor(img, grey, COLOR_BGR2GRAY);

/*Change image type from 8UC1 to 32FC1*/
src.convertTo(dst, CV_32F)
```
### 图像可视化
```
/*f32类型的show，要转换成u8类型*/
Mat img = imread("image.jpg");
Mat grey;
cvtColor(img, grey, COLOR_BGR2GRAY);
Mat sobelx;
Sobel(grey, sobelx, CV_32F, 1, 0);
double minVal, maxVal;
minMaxLoc(sobelx, &minVal, &maxVal); //find minimum and maximum intensities
Mat draw;
sobelx.convertTo(draw, CV_8U, 255.0/(maxVal - minVal), -minVal * 255.0/(maxVal - minVal));
namedWindow("image", WINDOW_AUTOSIZE);
imshow("image", draw);
waitKey();
```

## 图像融合
```
/*
dst(I)=saturate(src1(I)∗alpha+src2(I)∗beta+gamma)
type dst的深度值，当src1 和src2都有深度的时候，为-1，就是src1的深度值。
*/
beta = ( 1.0 - alpha );
addWeighted( src1, alpha, src2, beta, gamma, type);
```

## 改变图像亮度

对每隔像素点进行操作计算，两种基本的增强图像的方法，不能用于栅格图像
```
/*线性增强，改变直方图*/
for( int y = 0; y < image.rows; y++ ) {
          for( int x = 0; x < image.cols; x++ ) {
            for( int c = 0; c < 3; c++ ) {
                new_image.at<Vec3b>(y,x)[c] =
                  saturate_cast<uchar>( alpha*( image.at<Vec3b>(y,x)[c] ) + beta );
            }
          }
}
/*伽马校正*/
    Mat lookUpTable(1, 256, CV_8U);
    uchar* p = lookUpTable.ptr();
    for( int i = 0; i < 256; ++i)
        p[i] = saturate_cast<uchar>(pow(i / 255.0, gamma_) * 255.0);
    Mat res = img.clone();
    LUT(img, lookUpTable, res);
```
## 接下来的两章是教你怎么画图的，暂时先不看   

## 傅里叶变换，具体什么用处，暂时没看到

```
//1. Expand the image to an optimal size
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

//2. Make place for both the complex and the real values
/*
计算复杂值，合并。
count 图像的维度
merge(const Mat* mv, size_t count, OutputArray dst);
*/
Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
Mat complexI;
merge(planes, 2, complexI);   // Add to the expanded another plane with zeros
//3.傅里叶变化
/*傅里叶变换*/
dft(complexI, complexI);  // this way the result may fit in the source matrix
//4.Transform the real and complex values to magnitude
/*转换幅度值*/
split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
Mat magI = planes[0];
//5. 切换到对数刻度
/*切换到对数*/
magI += Scalar::all(1);                    // switch to logarithmic scale
log(magI, magI);
//6. 第一步的时候对图像进行expand，这一步恢复 Crop and rearrange
// crop the spectrum, if it has an odd number of rows or columns
magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));
// rearrange the quadrants of Fourier image  so that the origin is at the image center
/*.......*/
//7. normalize 标准化转换，中间的参数是转换的比例系数。
 normalize(magI, magI, 0, 1, NORM_MINMAX);
```
## XML和YAML的读写 ，没看

## OpenCV版本变化
