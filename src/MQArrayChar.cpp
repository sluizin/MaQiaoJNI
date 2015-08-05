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
#include "MaQiaoJNI.h"
#define ARRAY_LENGTH 5 
using namespace std; 
//using namespace MAQIAOJNI_H;
JNIEXPORT jcharArray JNICALL Java_MaQiao_MaQiaoJNI_MQJNIArrayChar_coupling___3C
  (JNIEnv*  env, jclass c, jcharArray array){
   int len =(int)env->GetArrayLength(array); // byte数组的长度
   jchar* char_arr=env->GetCharArrayElements(array,0);
   //int len = (int)arraylen;
   //wchar_t *widebuff=new wchar_t[len];
   char* charArray= Java2C::jcharArraychar2char(env,&array);
   cout<<"charArray[jcharToWindows(env,array)]:"<<charArray<<endl;
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
    //cout<<"->count:"<<count<<endl;
    if(count==0)return NULL;
    //char** newArray= (char**)malloc(count);   wrong //这只能分配一级指针
    char** newArray= (char**)calloc(count, sizeof(char*));//这里才是分配二级指针
    int point=0;
    char* ch = NULL;
    for (i = 0; i < len; i++, repeats = 0) {
    	for (ii = 0; ii < i; ii++)
    	if (char_arr[i] == char_arr[ii])
              if ((++repeats) == 2) break;
    	if (repeats == 1)
                {
                //提取某个字符。可以是单字符格式或双字符汉字类格式
                ch = (Java2C::jcharTochar(env,char_arr[i]));
                //判断此字符长度，为1，则为标准字母，为2则为汉字类双字节字符
                //printf("size:%d \n",strlen(ch));
                //得到某个字符的jchar 字符为:a(97),中(20013)
                //cout<<"char_arr["<<i<<"]:"<<char_arr[i]<<endl;
                //cout<<"charArray["<<i<<"]:"<<charArray[i]<<endl;
                //输出这个字符以char* C的字符指针的形式输出:a(a),中(-N)
                //cout<<"char * ch:"<< ch <<endl;
                //强制截断这个字符，如果双字节，以单字节输出
                //cout<<"(char)c:"<<(char)c<<endl;
                //newArray[point++]= ch;
                *(newArray+point)= ch;
                point++;
                //cout<<"------------------"<<endl;
                }
   }
   //for(int i=0;i<count;i++)
   //cout<<"->-newArray-"<<i<<"--:"<<*(newArray+i)<<endl;
   /*
   结束计算
   */
   delete[] char_arr; //释放数组空间
   env->DeleteLocalRef(array);
   jcharArray jchararray = C2Java::chars2jcharArray(env,newArray,&count);
   //尝试得到二级指针的长度[失败]
   //jcharArray jchararray = C2Java::chars2jcharArray(env,newArray);
   free(newArray); //释放二级指针空间
   return jchararray;
}
JNIEXPORT jcharArray JNICALL Java_MaQiao_MaQiaoJNI_MQJNIArrayChar_coupling__Ljava_lang_String_2
  (JNIEnv* env, jclass c, jstring str){
        //char* chara=jstringToWindows(env,str);
        //cout<<chara<<endl;
        //char * chars = Java2C::jstringTochar(env,str);
        //int len = strlen(chars);
        //cout<<"str:"<<str<<endl;
        //cout<<"chars:"<<chars<<endl;
        //cout<<"len:"<<len<<endl;
        //for(int i=0;i<len;i++)
        //cout<<"chars["<<i<<"]:"<<chars[i]<<endl;
        jcharArray jchararray = Java2Java::jstringTojcharArray(env,&str);
        return jchararray;
}

