0. 开宗明义，本文是记录一些平时模棱两可的知识点，不求甚解，不可学。

1. 编译和连接

2. 动态库和静态库

    (1)lib是编译时需要的，dll是运行时需要的。如果要完成源代码的编译，有lib就够了。如果也使动态连接的程序运行起来，有dll就够了。在开发和调试阶段，当然最好都有。        
    (2) 一般的动态库程序有lib文件和dll文件。lib文件是必须在编译期就连接到应用程序中的，而dll文件是运行期才会被调用的。如果有dll文件，那么对应的lib文件一般是一些索引信息，具体的实现在dll文件中。如果只有lib文件，那么这个lib文件是静态编译出来的，索引和实现都在其中。 静态编译的lib文件有好处：给用户安装时就不需要再挂动态库了。但也有缺点，就是导致应用程序比较大，而且失去了动态库的灵活性，在版本升级时，同时要发布新的应用程序才行。        
    (3)在动态库的情况下，有两个文件，一个是引入库（.LIB）文件(实际上也算是一个静态库,只是在链接时只能把函数在DLL的入口链接到exe中,而不像真正静态链接库那样将函数体真正链接到exe中 ,通过lib进行的动态链接实际上也使用了静态链接来实现 )，一个是DLL文件，引入库文件包含被DLL导出的函数的名称和位置，DLL包含实际的函数和数据，应用程序使用LIB文件链接到所需要使用的DLL文件，库中的函数和数据并不复制到可执行文件中，因此在应用程序的可执行文件中，存放的不是被调用的函数代码，而是DLL中所要调用的函数的内存地址，这样当一个或多个应用程序运行是再把程序代码和被调用的函数代码链接起来，从而节省了内存资源。从上面的说明可以看出，DLL和.LIB文件必须随应用程序一起发行，否则应用程序将会产生错误。        


