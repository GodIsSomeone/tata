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

/*Their headers are different, however, and making a modification using any of them will affect all the other ones as well*/
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
第三个参数 存储元素的数据类型和每个矩阵点的信道数：CV_[The number of bits per item][Signed or Unsigned][Type Prefix]C[The channel number]
第四个参数是 four element short vector
*/
Mat M(2,2, CV_8UC3, Scalar(0,0,255));
M.create(4,4, CV_8UC(2));

```

