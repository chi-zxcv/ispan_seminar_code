package tw.com.dmatek.buzzer;

import android.util.Log;

public class Linux_buzzer {
	static{
		try{
			Log.i("JNI", "Try to load libbuzzer.so");
			
			System.loadLibrary("buzzer");
		}catch(UnsatisfiedLinkError ule){
			Log.i("JNI", "Warming: Could not load libbuzzer.so");
		}}
	/*public static boolean init(){	
		Log.i("buzzerService", "Go to get BUZZER Stub...");
		return _init();
	}
	

    
     * Mokoid buzzer native methods.
     
    public static boolean setOn(int buzzer) {
        Log.i("MokoidPlatform", "buzzer On");
        return _set_on(buzzer);
    }

    public static boolean setOff(int buzzer) {
        Log.i("MokoidPlatform", "buzzer Off");
        return _set_off(buzzer);
    }*/

    //private static native boolean _init();
    //private static native boolean _set_on(int buzzer);
    //private static native boolean _set_off(int buzzer);
   public static native int openbuzzer();
   public static native int closebuzzer();
	public static native int send(int buzzer_num, int on_off);
}
