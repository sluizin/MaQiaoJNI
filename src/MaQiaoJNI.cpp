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
     �� jcharArray ת�� char* [�Ѿ��ɹ�����]
     ͨ������Java�е�ĳ�������� jcharArray ת��  jbyte ��ͨ����̬�����ڴ�ת�� char*
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
        //�Ƿ�Ҫ�ͷ���Դ
        free(barr);    
        free(clsstring);
        free(mid);
        free(strencode); 
        free(ba);
        return rtn;
};
/*
     �� jchar ת�� char*
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
     �� jstring ת�� char*
     ������Unicode��������(һ������ռ3���ֽ�)
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
        �õ�ĳ��String�ĳ��ȣ�ʹ��java/lang/String��length()����  [�Ѿ��ɹ�����]
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
     �� char* ת�� jcharArray
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
        �� char** ת��jcharArray(��Ҫ���漰�����ֵ�˫�ֽڵ��ַ�) [�Ѿ��ɹ�����]
        ע�⣺����ָ����ʱ�޷��õ�����(strlen,sizeof)��ֻ��ͨ����ֵ�ķ�ʽ���볤��
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
        �� char** ת�� jcharArray(���Զ�ȡ����ָ��ĳ���)[ʧ��]
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
        �� char* ת�� jcharArray(��ʱδ��)
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
        �� char* ת�� jcharArray(��ʱδ��)
*/
jcharArray C2Java::c2jsArrays(JNIEnv* env, const char* pat)
{
        int len=sizeof(pat);
        jcharArray chars = 0;
        if(len==0)return chars;
        BYTE *pbytes = (BYTE*) pat;
        //nOutSize��BYTE����ĳ��� BYTE pData[]
        int nOutSize = len;
        //int nOutSize=((strlen(pbytes)-1) / sizeof(BYTE));
        jbyte *jbytes = (jbyte*)pbytes;
        jbyteArray jarray = env->NewByteArray(nOutSize);
        env->SetByteArrayRegion(jarray,0, nOutSize, jbytes);
        return chars;
}
/*
        �� char* ת�� jbyte(��ʱδ��)
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
     �� jstring ת�� jcharArray    [�Ѿ��ɹ�����]
     ע�⣺���ֱ�Ӱ�byte���String���������Unicode��������
     ����ʹ��String.charAt()����һ��һ�����char��������jcharArray��
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


