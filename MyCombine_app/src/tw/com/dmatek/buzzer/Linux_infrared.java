package tw.com.dmatek.buzzer;

import android.util.Log;

public class Linux_infrared {
	static{
		try{
			Log.i("JNI", "Try to load libinfared.so");
			
			System.loadLibrary("infared");
		}catch(UnsatisfiedLinkError ule){
			Log.i("JNI", "Warming: Could not load libinfared.so");
		}}
	
   public static native int openinfrared();
   public static native int closeinfrared();
	public static native int ioctl_infrared(int condition_num);
	public static native int read_infrared();
}
