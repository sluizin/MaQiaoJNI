package MaQiao.MaQiaoJNI;
public final class MQJNIArrayChar {
	static {
		System.loadLibrary("MQJNIArrayChar");// 装入动态链接库，"HelloWorldImpl"是要装入的动态链接库名称。
	}
	public static final native char[] coupling(final char... array);
	public static final native char[] coupling(final String str);
	
}
