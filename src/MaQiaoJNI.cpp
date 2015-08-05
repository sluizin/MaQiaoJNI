#include <stdio.h>
#include <jni.h>
#include <cmath>
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include "MaQiaoJNI.h"
using namespace std;   
/*
===============================================================================

                        Java2C

===============================================================================
*/
/*
     把 jcharArray 转成 char* [已经成功测试]
     通过调用Java中的某个方法把 jcharArray 转成  jbyte 再通过动态分配内存转成 char*
*/
char* Java2C::jcharArraychar2char(JNIEnv *env, jcharArray *jstr)
{
        char* rtn = NULL;
        jmethodID mid;
        jbyteArray barr;
        jclass clsstring = env->FindClass("MaQiao/MaQiaoJNI/JNIByte");
        jstring strencode = env->NewStringUTF("utf-8");
        if(clsstring)
        mid = env->GetStaticMethodID(clsstring, "getBytes", "([C)[B");
        if(mid)
        barr= (jbyteArray)env->CallStaticObjectMethod(clsstring, mid,*jstr,strencode);
        else
        barr = (jbyteArray)env->NewStringUTF((const char*)NULL);
        jsize alen = env->GetArrayLength(barr);
        jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
        if (alen > 0)
        {
                rtn = (char*)malloc(alen + 1);
                memcpy(rtn, ba, alen);
                rtn[alen] = 0;
        }
        env->ReleaseByteArrayElements(barr, ba, 0);
        //是否要释放资源
        free(barr);    
        free(clsstring);
        free(mid);
        free(strencode); 
        free(ba);
        return rtn;
};
/*
     把 jchar 转成 char*
*/
char* Java2C::jcharTochar(JNIEnv *env, jchar jstr)
{
        char* rtn = NULL;
        jmethodID mid;
        jbyteArray barr;
        jclass clsstring = env->FindClass("MaQiao/MaQiaoJNI/JNIByte");
        jstring strencode = env->NewStringUTF("utf-8");
        if(clsstring)
        mid = env->GetStaticMethodID(clsstring, "getBytes", "(C)[B");
        if(mid)
        barr= (jbyteArray)env->CallStaticObjectMethod(clsstring, mid,jstr,strencode);
        else
        barr = (jbyteArray)env->NewStringUTF((const char*)NULL);
        jsize alen = env->GetArrayLength(barr);
        jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
        if (alen > 0)
        {
                rtn = (char*)malloc(alen + 1);
                memcpy(rtn, ba, alen);
                rtn[alen] = 0;
        }
        env->ReleaseByteArrayElements(barr, ba, 0);
        return rtn;
}
/*
     把 jstring 转成 char*
     会遇到Unicode编码问题(一个中文占3个字节)
*/
char* Java2C::jstringTochar(JNIEnv *env, jstring jstr)
{
        char* rtn = NULL;
        jclass clsstring = env->FindClass("java/lang/String");
        jstring strencode = env->NewStringUTF("utf-8");
        jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
        jbyteArray barr= (jbyteArray)env->CallObjectMethod(jstr, mid, strencode);
        jsize alen = env->GetArrayLength(barr);
        jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
        if (alen > 0)
        {
                rtn = (char*)malloc(alen + 1);
                memcpy(rtn, ba, alen);
                rtn[alen] = 0;
        }
        env->ReleaseByteArrayElements(barr, ba, 0);
        return rtn;
}
/*
        得到某个String的长度，使用java/lang/String的length()方法  [已经成功测试]
*/
int Java2C::jstringLen(JNIEnv *env, jstring *jstr)
{
        
        jclass clsstring = env->FindClass("java/lang/String");
        jmethodID mid = env->GetMethodID(clsstring, "length", "()I");
        int len=(int)env->CallIntMethod(*jstr,mid);
        free(mid);
        free(clsstring);
        return len;
}





/*
===============================================================================

                        C2Java

===============================================================================
*/
/*
     把 char* 转成 jcharArray
*/
jcharArray C2Java::char2jcharArray(JNIEnv* env, const char* pat)
{  
   jclass clsstring = env->FindClass("MaQiao/MaQiaoJNI/JNIChar");
   jmethodID mid = env->GetStaticMethodID(clsstring, "getChars", "([B)[C");
   //cout<<"->----[strlen(pat)]:"<<sizeof(pat)<<endl;
   jcharArray chars = env->NewCharArray(strlen(pat));
   env->SetCharArrayRegion(chars, 0, strlen(pat), (jchar*)pat);    
   jstring encoding = env->NewStringUTF("utf-8");  
   return (jcharArray)env->NewObject(clsstring, mid, chars, encoding);  
}
/*
        把 char** 转成jcharArray(主要是涉及到汉字等双字节的字符) [已经成功测试]
        注意：二级指针暂时无法得到长度(strlen,sizeof)，只能通过传值的方式传入长度
*/
jcharArray C2Java::chars2jcharArray(JNIEnv* env,char** newArray,const int* len)
{
        if(*len==0)return env->NewCharArray(0);
        jcharArray charArray = env->NewCharArray(*len);
        for(int i=0;i<*len;i++)
           env->SetCharArrayRegion(charArray,i,1,(jchar*)newArray[i]);
        return charArray;
}
/*
        把 char** 转成 jcharArray(尝试读取二级指针的长度)[失败]
*/
jcharArray C2Java::chars2jcharArray(JNIEnv* env,char** newArray)
{
        
        //int len=sizeof(newArray);
        char *k= *newArray;
        int len=strlen(k);
        cout<<"->len:"<<len<<endl;
        if(len==0)return env->NewCharArray(0);
        jcharArray charArray = env->NewCharArray(len);
        for(int i=0;i<len;i++)
           env->SetCharArrayRegion(charArray,(jsize)i,(jsize)1,(jchar*)newArray[i]);
        return charArray;
}
/*
        把 char* 转成 jcharArray(暂时未测)
*/
jcharArray C2Java::charTojcharArray( JNIEnv *env, char* str,int len)
{
        jcharArray jcharnewArray= env->NewCharArray(len);
        //unsigned short * buffer = 0;
        jchar *chars = env->GetCharArrayElements(jcharnewArray, 0);
        env->SetCharArrayRegion(jcharnewArray, 0, len, chars );
        return jcharnewArray;
} 
/*
        把 char* 转成 jcharArray(暂时未测)
*/
jcharArray C2Java::c2jsArrays(JNIEnv* env, const char* pat)
{
        int len=sizeof(pat);
        jcharArray chars = 0;
        if(len==0)return chars;
        BYTE *pbytes = (BYTE*) pat;
        //nOutSize是BYTE数组的长度 BYTE pData[]
        int nOutSize = len;
        //int nOutSize=((strlen(pbytes)-1) / sizeof(BYTE));
        jbyte *jbytes = (jbyte*)pbytes;
        jbyteArray jarray = env->NewByteArray(nOutSize);
        env->SetByteArrayRegion(jarray,0, nOutSize, jbytes);
        return chars;
}
/*
        把 char* 转成 jbyte(暂时未测)
*/
jbyte C2Java::char2jbyte(JNIEnv* env,const char* c)
{
        jbyte ch=NULL;
        BYTE * lpBuffer = (BYTE *)c;
        ch=(jbyte)lpBuffer;
        return ch;
}
jstring  C2Java::CharTojstring(JNIEnv* env,char* str)
{
	jsize   len   =   strlen(str);
	jclass   clsstring   =   env->FindClass("java/lang/String");
	jstring   strencode   =   env->NewStringUTF("utf-8");
	jmethodID   mid   =   env->GetMethodID(clsstring,   "<init>",   "([BLjava/lang/String;)V");
	jbyteArray   barr   =   env-> NewByteArray(len);

	env-> SetByteArrayRegion(barr,0,len,(jbyte*)str);
	return (jstring)env-> NewObject(clsstring,mid,barr,strencode);
}













/*
===============================================================================

                        Java2Java

===============================================================================
*/


/*
     把 jstring 转成 jcharArray    [已经成功测试]
     注意：如果直接按byte提出String，则会遇到Unicode编码问题
     所以使用String.charAt()方法一个一个提出char，保存在jcharArray中
*/
jcharArray Java2Java::jstringTojcharArray(JNIEnv *env, jstring *jstr)
{                                                          
        jclass clsstring = env->FindClass("java/lang/String");
        jmethodID mid = env->GetMethodID(clsstring, "charAt", "(I)C");
        const int len=Java2C::jstringLen(env,jstr);   
        jcharArray charArray = env->NewCharArray(len);
        for(int i=0;i<len;i++){
                jchar c=env->CallCharMethod(*jstr,mid,i);
                env->SetCharArrayRegion(charArray,(jsize)i,(jsize)1,&c);
        }
        free(mid);
        free(clsstring);
        //cout<<"1jstr:"<<jstr<<endl;
        //cout<<"1charArray:"<<charArray<<endl;
        //cout<<"1len:"<<len<<endl;
        return charArray;
}


