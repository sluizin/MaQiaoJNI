#ifndef MAQIAOJNI_H
#define MAQIAOJNI_H  
#include <stdio.h>
#include <jni.h>
#include <cmath>
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>
using namespace std;
namespace Java2C
{
    char* jcharArraychar2char(JNIEnv *env, jcharArray *jstr);
    char* jcharTochar(JNIEnv *env, jchar jstr);
    char* jstringTochar(JNIEnv *env, jstring jstr);
    int jstringLen(JNIEnv *env, jstring *jstr);
};
namespace C2Java
{
    jcharArray char2jcharArray(JNIEnv* env, const char* pat);
    jcharArray chars2jcharArray(JNIEnv* env,char** newArray,const int* len);
    jcharArray chars2jcharArray(JNIEnv* env,char** newArray);
    jcharArray charTojcharArray( JNIEnv *env, char* str,int len);
    jcharArray c2jsArrays(JNIEnv* env, const char* pat);
    jbyte char2jbyte(JNIEnv* env,const char* c);
    jstring CharTojstring(JNIEnv* env,char* str);
};
namespace Java2Java
{
    jcharArray jstringTojcharArray(JNIEnv *env, jstring *jstr);
};



#endif
 