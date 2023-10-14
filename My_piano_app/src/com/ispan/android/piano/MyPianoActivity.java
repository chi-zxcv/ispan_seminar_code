package com.ispan.android.piano;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

public class MyPianoActivity extends Activity {
    private static final String TAG=MyPianoActivity.class.getSimpleName();
    public int fd=0;
    public int freq;
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        Log.d(TAG,"findView");
        findViews();
        Log.d(TAG,"Set Listenser");
        setListeners();
        
        fd = Linux_passive_buzzer.open_passive_buzzer();
        if(fd<0){
        	Log.d(TAG,"open device fall!!");
        	Toast.makeText(MyPianoActivity.this, "open device fall!!", Toast.LENGTH_SHORT).show();
        }else{
        	Log.d(TAG,"open device success!!");
        	Toast.makeText(MyPianoActivity.this, "open device success!!", Toast.LENGTH_SHORT).show();
          }
        
        
    }
    
    private Button mButton_run;
    private Button mButton_music;
    private Button mButton_exit;
    private View view_fa_minus;
    private View view_so_minus;
    private View view_la_minus;
    private View view_si_minus;
    private View view_do;
    private View view_re;
    private View view_mi;
    private View view_fa;
    private View view_so;
    private View view_la;
    private View view_si;
    
    private void findViews(){
    	mButton_run = (Button)findViewById(R.id.button_run);
    	mButton_music = (Button)findViewById(R.id.button_music);
    	mButton_exit = (Button)findViewById(R.id.button_exit);
    	view_fa_minus = (View)findViewById(R.id.buttom_fa_minus);
    	view_so_minus = (View)findViewById(R.id.buttom_so_minus);
    	view_la_minus = (View)findViewById(R.id.buttom_la_minus);
    	view_si_minus = (View)findViewById(R.id.buttom_si_minus);
    	view_do = (View)findViewById(R.id.buttom_do);
    	view_re = (View)findViewById(R.id.buttom_re);
    	view_mi = (View)findViewById(R.id.buttom_mi);
    	view_fa = (View)findViewById(R.id.buttom_fa);
    	view_so = (View)findViewById(R.id.buttom_so);
    	view_la = (View)findViewById(R.id.buttom_la);
    	view_si = (View)findViewById(R.id.buttom_si);
    }
    
    private void setListeners(){
    	Log.d(TAG,"Set Listenser");
    	mButton_run.setOnClickListener(mButton_run_listener);
    	mButton_music.setOnClickListener(mButton_music_listener);
    	mButton_exit.setOnClickListener(mButton_exit_listener);
    	view_fa_minus.setOnClickListener(view_fa_minus_listener);
    	view_so_minus.setOnClickListener(view_so_minus_listener);
    	view_la_minus.setOnClickListener(view_la_minus_listener);
    	view_si_minus.setOnClickListener(view_si_minus_listener);
    	view_do.setOnClickListener(view_do_listener);
    	view_re.setOnClickListener(view_re_listener);
    	view_mi.setOnClickListener(view_mi_listener);
    	view_fa.setOnClickListener(view_fa_listener);
    	view_so.setOnClickListener(view_so_listener);
    	view_la.setOnClickListener(view_la_listener);
    	view_si.setOnClickListener(view_si_listener);
    }
    private Button.OnClickListener mButton_run_listener=new Button.OnClickListener(){
    	public void onClick(View v){
    		try{
    			Toast.makeText(MyPianoActivity.this, "氣氛音樂",Toast.LENGTH_SHORT ).show();
    			Linux_passive_buzzer.play_run_passive_buzzer();
    		}catch(Exception e){
    			Toast.makeText(MyPianoActivity.this, "mButton_music_listener_error",Toast.LENGTH_SHORT ).show();
    		}
    	}
    };
    private Button.OnClickListener mButton_music_listener=new Button.OnClickListener(){
    	public void onClick(View v){
    		try{
    			Toast.makeText(MyPianoActivity.this, "播放歌曲",Toast.LENGTH_SHORT ).show();
    			Linux_passive_buzzer.play_music_passive_buzzer();
    		}catch(Exception e){
    			Toast.makeText(MyPianoActivity.this, "mButton_music_listener_error",Toast.LENGTH_SHORT ).show();
    		}
    	}
    };
    private Button.OnClickListener mButton_exit_listener=new Button.OnClickListener(){
    	public void onClick(View v){
    		try{
    			Toast.makeText(MyPianoActivity.this, "EXIT",Toast.LENGTH_SHORT ).show();
    			Linux_passive_buzzer.close_passive_buzzer();
    			finish();
    		}catch(Exception e){
    			Toast.makeText(MyPianoActivity.this, "mButton_music_listener_error",Toast.LENGTH_SHORT ).show();
    		}
    	}
    };
    private View.OnClickListener view_fa_minus_listener=new View.OnClickListener() {
		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
			try{
    			Toast.makeText(MyPianoActivity.this, "-Fa key",Toast.LENGTH_SHORT ).show();
    			freq = 174600; //174.6HZ
    			Linux_passive_buzzer.send_passive_buzzer(freq, 1);
    		}catch(Exception e){
    			Toast.makeText(MyPianoActivity.this, "button_fa_minus_error",Toast.LENGTH_SHORT ).show();
    		}
		}
	};
	private View.OnClickListener view_so_minus_listener=new View.OnClickListener() {
		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
			try{
    			Toast.makeText(MyPianoActivity.this, "-Sol key",Toast.LENGTH_SHORT ).show();
    			freq = 196000; //196HZ
    			Linux_passive_buzzer.send_passive_buzzer(freq, 1);
    		}catch(Exception e){
    			Toast.makeText(MyPianoActivity.this, "button_so_minus_error",Toast.LENGTH_SHORT ).show();
    		}
		}
	};
	private View.OnClickListener view_la_minus_listener=new View.OnClickListener() {
		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
			try{
    			Toast.makeText(MyPianoActivity.this, "-La key",Toast.LENGTH_SHORT ).show();
    			freq = 220000; //220HZ
    			Linux_passive_buzzer.send_passive_buzzer(freq, 1);
    		}catch(Exception e){
    			Toast.makeText(MyPianoActivity.this, "button_la_minus_error",Toast.LENGTH_SHORT ).show();
    		}
		}
	};
	private View.OnClickListener view_si_minus_listener=new View.OnClickListener() {
		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
			try{
    			Toast.makeText(MyPianoActivity.this, "-Si key",Toast.LENGTH_SHORT ).show();
    			freq = 246900; //246.9HZ
    			Linux_passive_buzzer.send_passive_buzzer(freq, 1);
    		}catch(Exception e){
    			Toast.makeText(MyPianoActivity.this, "button_si_minus_error",Toast.LENGTH_SHORT ).show();
    		}
		}
	};
    private View.OnClickListener view_do_listener=new View.OnClickListener() {
		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
			try{
    			Toast.makeText(MyPianoActivity.this, "Do key",Toast.LENGTH_SHORT ).show();
    			freq = 261600; //261.6HZ
    			Linux_passive_buzzer.send_passive_buzzer(freq, 1);
    		}catch(Exception e){
    			Toast.makeText(MyPianoActivity.this, "button_do_error",Toast.LENGTH_SHORT ).show();
    		}
		}
	};

    private View.OnClickListener view_re_listener=new View.OnClickListener() {
		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
			try{
    			Toast.makeText(MyPianoActivity.this, "Re key",Toast.LENGTH_SHORT ).show();
    			freq = 293600; //293.6HZ
    			Linux_passive_buzzer.send_passive_buzzer(freq, 1);
    		}catch(Exception e){
    			Toast.makeText(MyPianoActivity.this, "button_re_error",Toast.LENGTH_SHORT ).show();
    		}
		}
	};
	private View.OnClickListener view_mi_listener=new View.OnClickListener() {
		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
			try{
    			Toast.makeText(MyPianoActivity.this, "Mi key",Toast.LENGTH_SHORT ).show();
    			freq = 329600; //329.6HZ
    			Linux_passive_buzzer.send_passive_buzzer(freq, 1);
    		}catch(Exception e){
    			Toast.makeText(MyPianoActivity.this, "button_mi_error",Toast.LENGTH_SHORT ).show();
    		}
		}
	};
	private View.OnClickListener view_fa_listener=new View.OnClickListener() {
		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
			try{
    			Toast.makeText(MyPianoActivity.this, "Fa key",Toast.LENGTH_SHORT ).show();
    			freq = 349200; //349.2HZ
    			Linux_passive_buzzer.send_passive_buzzer(freq, 1);
    		}catch(Exception e){
    			Toast.makeText(MyPianoActivity.this, "button_fa_error",Toast.LENGTH_SHORT ).show();
    		}
		}
	};
	private View.OnClickListener view_so_listener=new View.OnClickListener() {
		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
			try{
    			Toast.makeText(MyPianoActivity.this, "Sol key",Toast.LENGTH_SHORT ).show();
    			freq = 392000; //392HZ
    			Linux_passive_buzzer.send_passive_buzzer(freq, 1);
    		}catch(Exception e){
    			Toast.makeText(MyPianoActivity.this, "button_so_error",Toast.LENGTH_SHORT ).show();
    		}
		}
	};
	private View.OnClickListener view_la_listener=new View.OnClickListener() {
		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
			try{
    			Toast.makeText(MyPianoActivity.this, "La key",Toast.LENGTH_SHORT ).show();
    			freq = 440000; //440HZ
    			Linux_passive_buzzer.send_passive_buzzer(freq, 1);
    		}catch(Exception e){
    			Toast.makeText(MyPianoActivity.this, "button_la_error",Toast.LENGTH_SHORT ).show();
    		}
		}
	};
	private View.OnClickListener view_si_listener=new View.OnClickListener() {
		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
			try{
    			Toast.makeText(MyPianoActivity.this, "Si key",Toast.LENGTH_SHORT ).show();
    			freq = 493800; //493.8HZ
    			Linux_passive_buzzer.send_passive_buzzer(freq, 1);
    		}catch(Exception e){
    			Toast.makeText(MyPianoActivity.this, "button_si_error",Toast.LENGTH_SHORT ).show();
    		}
		}
	};
    
}