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
     把 jcharArray 转成 char*
*/
char* Java2C::jcharArraychar2char(JNIEnv *env, jcharArray jstr)
{
        char* rtn = NULL;
        jmethodID mid;
        jbyteArray barr;
        jclass clsstring = env->FindClass("MaQiao/MaQiaoJNI/JNIByte");
        jstring strencode = env->NewStringUTF("utf-8");
        if(clsstring)
        mid = env->GetStaticMethodID(clsstring, "getBytes", "([C)[B");
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

