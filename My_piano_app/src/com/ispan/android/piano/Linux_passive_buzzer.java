package com.ispan.android.piano;

import android.util.Log;

public class Linux_passive_buzzer {
	static{
		try{
			Log.i("JNI", "Try to load libpassivebuzzer.so");
			
			System.loadLibrary("passivebuzzer");
		}catch(UnsatisfiedLinkError ule){
			Log.i("JNI", "Warming: Could not load libpassivebuzzer.so");
		}}
	public static native int open_passive_buzzer();
   public static native int close_passive_buzzer();
   public static native int play_run_passive_buzzer();
   public static native int play_music_passive_buzzer();
	public static native int send_passive_buzzer(int frequence, int duration);
}
