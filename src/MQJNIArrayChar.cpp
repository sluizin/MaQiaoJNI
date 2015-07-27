//---------------------------------------------------------------------------
              
#include "MaQiao_MaQiaoJNI_MQJNIArrayChar.h" 
#include <stdio.h>
#include <jni.h>
//---------------------------------------------------------------------------
//   Important note about DLL memory management when your DLL uses the
//   static version of the RunTime Library:
//
//   If your DLL exports any functions that pass String objects (or structs/
//   classes containing nested Strings) as parameter or function results,
//   you will need to add the library MEMMGR.LIB to both the DLL project and
//   any other projects that use the DLL.  You will also need to use MEMMGR.LIB
//   if any other projects which use the DLL will be performing new or delete
//   operations on any non-TObject-derived classes which are exported from the
//   DLL. Adding MEMMGR.LIB to your project will change the DLL and its calling
//   EXE's to use the BORLNDMM.DLL as their memory manager.  In these cases,
//   the file BORLNDMM.DLL should be deployed along with your DLL.
//
//   To avoid using BORLNDMM.DLL, pass string information using "char *" or
//   ShortString parameters.
//
//   If your DLL uses the dynamic version of the RTL, you do not need to
//   explicitly add MEMMGR.LIB as this will be done implicitly for you
//---------------------------------------------------------------------------
#include <cmath>
#include <string.h>  
#include <stdio.h> 
#include <windows.h>
#include <iostream>    
#define ARRAY_LENGTH 5 
using namespace std;
char* jcharToWindows( JNIEnv *env, jchar jstr); //声明函数
char* jstringToWindows( JNIEnv *env, jstring jstr);//声明函数
char* jcharToWindows( JNIEnv *env, jcharArray jstr);//声明函数
char* jcharToWindows_change( JNIEnv *env, jchar jcstr );//声明函数

jcharArray WindowsTojchar( JNIEnv *env, char* str,int len);//声明函数
jcharArray c2js(JNIEnv* env, const char* pat);//声明函数

wchar_t * UTF8ToUnicode( const char* str);    //声明函数

JNIEXPORT jcharArray JNICALL Java_MaQiao_MaQiaoJNI_MQJNIArrayChar_coupling___3C
  (JNIEnv*  env, jclass c, jcharArray array){
   jsize arraylen =env->GetArrayLength(array); // byte数组的长度
   jchar* char_arr=env->GetCharArrayElements(array,0);
   int len = (int)arraylen;
   //char* k;
   //wchar_t *widebuff=new wchar_t[len];
   char* charArray= jcharToWindows(env,array);
   //cout<<"array[jcharArray]:"<<array<<endl;
   cout<<"charArray[jcharToWindows(env,array)]:"<<charArray<<endl;
   //for(int i=0;i<len;i++)
    //{
        //arraychar[i] = jcharToWindows(env,array[i]);//(char)(char_arr[i]);
        //char* c=jcharToWindows(env,char_arr[i]);
        //k= char_arr[i];
        //cout<<i<<":"<<(char)(char_arr[i])<<endl;
        //char * cc=jcharToWindows_change(env,char_arr[i]);
        //cout<<i<<"->to1:"<<cc<<endl;
        //k= jcharToWindows(env,char_arr[i]);
        //cout<<i<<"->to2:"<<(k)<<endl;
    //}
   /*
   开始计算
   */
    int count = 0;
    int i, ii, repeats=0;
    for (i = 0; i < len; i++, repeats = 0) {
    	for (ii = 0; ii < i; ii++)
    	if (char_arr[i] == char_arr[ii])
              if ((++repeats) == 2) {break;}
    	if (repeats == 1)
        count++;
    }
    //计算出总数
    cout<<"->count:"<<count<<endl;
   char* newArray= (char*)malloc(count + 1);
   int p=0;
   for (i = 0; i < len; i++, repeats = 0) {
    	for (ii = 0; ii < i; ii++)
    	if (char_arr[i] == char_arr[ii])
              if ((++repeats) == 2) {break;}
    	if (repeats == 1)
                {  
                cout<<"->aa:"<<charArray[i]<<endl;
                cout<<"->bb:"<<jcharToWindows(env,charArray[i])<<endl;
                cout<<"->cc:"<<(char)jcharToWindows(env,charArray[i])<<endl;
                newArray[p++]=charArray[i];
                //widebuff[p++]=charArray[i];
                }
        //(*newArray)[p++] =(char *)jcharToWindows(env,char_arr[i]);
        //memcpy(newArray[p++], jcharToWindows(env,char_arr[i]), i);
        //newArray[p++]= jcharToWindows(env,char_arr[i]);
   } 
  // for(i=0;i<=count;i++){
   // cout<<"->widebuff["<<i<<"]:"<<widebuff[i]<<endl;
   //}
  // for(i=0;i<=count;i++){
    //cout<<"->newArray["<<i<<"]:"<<newArray[i]<<endl;
  // }
   cout<<"newArray[jcharToWindows(env,array)]:"<<newArray<<endl;
   /*
   结束计算
   */
   //delete[] char_arr; //释放数组空间
   env->DeleteLocalRef(array);
  // jcharArray jchararray=NULL;//  WindowsTojchar(env,newArray,count);
  // char* charArray2=NULL;// jcharToWindows(env,jchararray);
   jcharArray jchararray = c2js(env,newArray);
   //cout<<"charArray2[WindowsTojchar(env,array)]:"<<charArray2<<endl;


   
   //jcharArray jchararray=env->NewCharArray(count);
   //env->SetByteArrayRegion(jchararray,0,count,);
   return jchararray;
  }
JNIEXPORT jcharArray JNICALL Java_MaQiao_MaQiaoJNI_MQJNIArrayChar_coupling__Ljava_lang_String_2
  (JNIEnv* env, jclass c, jstring str){
        char* chara=jstringToWindows(env,str);
        cout<<chara<<endl;


         jcharArray jchararray;
         return      jchararray;
}

//---------------------------------------------------------------------------

//              通用方法

//---------------------------------------------------------------------------
   char* jstringToWindows( JNIEnv *env, jstring jstr)
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
 //---------------------------------------------------------------------------

//              通用方法   jcharArray jchar 转成char*

//---------------------------------------------------------------------------
   char* jcharToWindows( JNIEnv *env, jcharArray jstr)
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
        }




        
jcharArray WindowsTojchar( JNIEnv *env, char* str,int len)
        {
        //int len=0;
        //len=strlen(str);
        cout<<"->----[len]:"<<len<<endl;
        jcharArray jcharnewArray= env->NewCharArray(len);
        //unsigned short * buffer = 0;
        jchar *chars = env->GetCharArrayElements(jcharnewArray, 0);
        for(int i=0;i<len;i++)   
        cout<<"->----["<<i<<"]:"<< str[i]<<endl;

        // for ( int i = 0; i < sizeof( pAdapterInfo->Address ); i++ )
        //{
               // chars[ i ] = pAdapterInfo->Address[ i ];
        //}
        env->SetCharArrayRegion(jcharnewArray, 0, len, chars );  
        return jcharnewArray;
        }
 jcharArray c2js(JNIEnv* env, const char* pat)
{
   jclass clsstring = env->FindClass("MaQiao/MaQiaoJNI/JNIChar");   
   jmethodID mid = env->GetStaticMethodID(clsstring, "getChar", "([B)[C");
   jcharArray chars = env->NewCharArray(strlen(pat));  
   env->SetCharArrayRegion(chars, 0, strlen(pat), (jchar*)pat);    
   jstring encoding = env->NewStringUTF("utf-8");  
   return (jcharArray)env->NewObject(clsstring, mid, chars, encoding);  
}












   char* jcharToWindows( JNIEnv *env, jchar jstr)
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
        //----------------------------------------------
char* jcharToWindows_change( JNIEnv *env, jchar jcstr )
	{ //UTF8/16转换成gb2312
	  char* rtn = (char*)malloc( 2 );
	  int size = 0;
	  size = WideCharToMultiByte( CP_ACP, 0, (LPCWSTR)jcstr, 1, rtn,2, NULL, NULL );
	  if( size <= 0 )
	    return NULL;
	  //(env)->ReleaseChars(jcstr );
	  rtn[size] = 0;
	  return rtn;
	}
wchar_t * UTF8ToUnicode( const char* str )
{
     int textlen ;
     wchar_t * result;
     textlen = MultiByteToWideChar( CP_UTF8, 0, str,-1, NULL,0 ); 
     result = (wchar_t *)malloc((textlen+1)*sizeof(wchar_t)); 
     memset(result,0,(textlen+1)*sizeof(wchar_t)); 
     MultiByteToWideChar(CP_UTF8, 0,str,-1,(LPWSTR)result,textlen ); 
     return result; 
}
