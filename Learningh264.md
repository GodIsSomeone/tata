## H264的简介  
MPEG（Moving Picture Experts Group）和VCEG（Video Coding Experts Group）已经联合开发了一个比早期研发的MPEG 和H.263性能更好的视频压缩编码标准，
这就是被命名为AVC（Advanced Video Coding），也被称为ITU-T H.264建议和MPEG-4的第10 部分的标准，简称为H.264/AVC或H.264。
这个国际标准已经与2003年3月正式被ITU-T所通过并在国际上正式颁布。为适应高清视频压缩的需求，2004年又增加了FRExt部分；为适应不同码率及质量的需求，
2006年又增加了可伸缩编码 SVC。
  
  
## H264的结构  
H.264的功能分为两层：视频编码层（VCL, Video Coding Layer）和网络提取层（NAL, Network Abstraction Layer）。
VCL数据即编码处理的输出，它表示被压缩编码后的视频数据序列。在VCL数据传输或存储之前，这些编码的VCL数据，先被映射或封装进NAL单元中。
每个NAL单元包括一个原始字节序列负荷（RBSP, Raw Byte Sequence Payload）、一组对应于视频编码的NAL头信息。RBSP的基本结构是：
在原始编码数据的后面填加了结尾比特。一个bit“1”若干比特“0”，以便字节对齐。  

https://blog.csdn.net/mandagod/article/details/51174680
