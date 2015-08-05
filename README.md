初步使用JNI 通过jni，使java数据传递给c++程序，变成c++可以识别的数据。为以后进一步操作建基础！<br/>
主要是java与c++相互传值<br/>
想通过byte传中文<br/>
哈哈，今天成功完成java与C传数组，char[]转char*(javaToC) char**转char[](CtoJava) 使用二级指针为了方便汉字的识别与输出。2015-8-4 <br/>
2015-8-5 <br/>
今天主要解决了string的导入jni的情况<br/>
注意：如果直接按byte提出String，则会遇到Unicode编码问题<br/>
所以使用String.charAt()方法一个一个提出char，保存在jcharArray中<br/>
/**
 * @author Sunjian
 * @QQ 75583378
 * @Email sluizin@sohu.com
 * @version 1.0
 * @since 1.7
 * @Datetime 2015-7-24
 */<br/>