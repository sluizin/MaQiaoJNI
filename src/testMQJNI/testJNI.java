package testMQJNI;
import java.util.ArrayList;
import java.util.List;
import org.junit.Test;
import MaQiao.MaQiaoJNI.MQJNIArrayChar;
@SuppressWarnings({ "unused" })
public class testJNI {
	@Test
	public void test1() {
		System.out.println("java.library.path:"+System.getProperty("java.library.path"));
		{
			//System.out.println(MQArrayChar.count("ab".toCharArray(), "abc".toCharArray(), "aebc".toCharArray(), "ab".toCharArray(), "ab".toCharArray()));
			{
				char[] array=MQJNIArrayChar.coupling("a国b中cb人中c".toCharArray());
			}
			{
				//char[] array=MQJNIArrayChar.coupling("a国b中cb人中c");
//				if(array!=null){
//					for(int i=0;i<array.length;i++)
//						System.out.println(array[i]);
//				}
			}
//			for(int i=0;i<array.length;i++){
//				System.out.println(array[i]);
//			}
		}
}

    public static char getChar(byte[] bytes)
    {
        return (char) ((0xff & bytes[0]) | (0xff00 & (bytes[1] << 8)));
    }
}