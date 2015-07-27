package MaQiao.MaQiaoJNI;

import java.io.UnsupportedEncodingException;
//import java.nio.ByteBuffer;
//import java.nio.CharBuffer;
//import java.nio.charset.Charset;

import sun.io.ByteToCharConverter;
import sun.io.MalformedInputException;



@SuppressWarnings("deprecation")
public final class JNIChar {
	public static final char[] getChar(final byte[] bytes) throws UnsupportedEncodingException, MalformedInputException{
	     // Charset cs = Charset.forName ("UTF-8");
	      //ByteBuffer bb = ByteBuffer.allocate (bytes.length);
	     // bb.put(bytes);
	     // bb.flip ();
	      //CharBuffer cb = cs.decode (bb);	
		ByteToCharConverter converter = ByteToCharConverter.getConverter("gb2312"); 
	   return converter.convertAll(bytes); //cb.array();
	}
	
}
