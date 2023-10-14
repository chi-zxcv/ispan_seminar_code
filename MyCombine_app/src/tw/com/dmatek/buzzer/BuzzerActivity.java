package tw.com.dmatek.buzzer;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Message;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class BuzzerActivity extends Activity {
	private static final String TAG = BuzzerActivity.class.getSimpleName();
	public int state1=0, state2=0;
	public int buzzer_on = 1;
	public int buzzer_off = 3;
	public int fd = 0;
	
	private Handler mThreadHandler;
	private HandlerThread mThread;
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        Log.d(TAG,"find View");
        findViews();
        Log.d(TAG,"Set Listener");
        setListeners();
        
        fd = Linux_buzzer.openbuzzer();
        if(fd<0){
        	 Log.d(TAG,"open device fail!");
        	 Toast.makeText(BuzzerActivity.this, "open device fail!",Toast.LENGTH_SHORT ).show();
        	 //finish();
        	}else{
        		Toast.makeText(BuzzerActivity.this, "open device success!",Toast.LENGTH_SHORT ).show();
        		Log.d(TAG,"open device success!");
        	}
        
        fd = Linux_infrared.openinfrared();
        if(fd<0){
        	 Log.d(TAG,"open infrared device fail!");
        	 Toast.makeText(BuzzerActivity.this, "open infrared device fail!",Toast.LENGTH_SHORT ).show();
        	 //finish();
        	}else{
        		Toast.makeText(BuzzerActivity.this, "open infrared device success!",Toast.LENGTH_SHORT ).show();
        		Log.d(TAG,"open device success!");
        	}
        //view_welcome.setSelected(true);
        
        
        //let Worker standby, and wait for mission
        mThread = new HandlerThread("name");
        //start detection 
        mThread.start();
        mThreadHandler = new Handler(mThread.getLooper());
      
        
    }
  
  private Handler mUI_Handler = new Handler(){
	public void habdlerMessage(Message msg){
		super.handleMessage(msg);
		//mmtxt_infrared.setText("read data=",Integer.toString(msg.getData().getInt("read",0)));
		mmtxt_infrared.setText(String.valueOf(Linux_infrared.read_infrared()));
	}
  };
    
    
  private static boolean top = false;
  private Runnable r1 = new Runnable(){
	  public void run(){
		  while(!top){
				 try {
					 Message msg = new Message();
					 
					 int read_value = Linux_infrared.read_infrared();
					 Bundle readBundle = new Bundle();
					 readBundle.putInt("read", read_value);
					 msg.setData(readBundle);
					 mUI_Handler.sendMessage(msg);
					 
					 //Toast.makeText(Buzzer_Control_Activity.this, Integer.toString(msg.getData().getInt("read",0)),Toast.LENGTH_SHORT ).show();
		    			
					 if(read_value ==0 && getTitle()=="Warming Sensor Start!!!"){
						 int i;
							for(i=0;i<5;i++){
								Linux_buzzer.send(1,buzzer_on);
								Linux_buzzer.send(2,buzzer_on);
				  				Thread.sleep(100);
				  				Linux_buzzer.send(1,buzzer_off);
				  				Linux_buzzer.send(2,buzzer_off);
				  				Thread.sleep(100);
							}
					 }
					 Thread.sleep(2000);
					  
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
			  }
	  }
  };
    
    
    
    
    
    private Button mbutton1;
    private Button mbutton2;
    private Button mbutton3;
    private Button mbutton4;
    private Button mbutton5;
    private TextView view_welcome;
    private Button mmyButton_WARMING;
    private Button mmyButton_PARTY;
    private Button mmyButton_RESET;
    private TextView mmtxt_infrared;
  //取得畫面的按鈕物件的控制權
    private void findViews(){
    	mbutton1 = (Button) findViewById(R.id.myButton1);
    	mbutton2 = (Button) findViewById(R.id.myButton1_1);
    	mbutton3 = (Button) findViewById(R.id.myButton2);
    	mbutton4 = (Button) findViewById(R.id.myButton2_1);
    	mbutton5 = (Button) findViewById(R.id.myButton3);
    	mmyButton_WARMING = (Button)findViewById(R.id.myButton_WARMING);
    	mmyButton_PARTY = (Button)findViewById(R.id.myButton_PARTY);
    	mmyButton_RESET = (Button)findViewById(R.id.myButton_reset);
    	view_welcome = (TextView) findViewById(R.id.text);
    	mmtxt_infrared = (TextView)findViewById(R.id.textView_infrared);
    }
  //Listen for button clicks
    private void setListeners(){
    	mbutton1.setOnClickListener(button1_listener);
    	mbutton2.setOnClickListener(button2_listener);
    	mbutton3.setOnClickListener(button3_listener);
    	mbutton4.setOnClickListener(button4_listener);
    	mbutton5.setOnClickListener(button5_listener);
    	mmyButton_WARMING.setOnClickListener(mmyButton_WARMING_listener);
    	mmyButton_PARTY.setOnClickListener(mmyButton_PARTY_listener);
    	mmyButton_RESET.setOnClickListener(mmyButton_RESET_listensr);
    }
    
    private Button.OnClickListener mmyButton_WARMING_listener=new Button.OnClickListener(){
    	public void onClick(View v){
    		try{
    			Toast.makeText(BuzzerActivity.this, "mmyButton_WARMING_listener",Toast.LENGTH_SHORT ).show();
    			Linux_infrared.ioctl_infrared(0);
    			Linux_infrared.ioctl_infrared(0);
    			setTitle("Warming Sensor Start!!!");
    			top=false;
    			mThreadHandler.post(r1);
    		}catch(Exception e){
    			Toast.makeText(BuzzerActivity.this, "input_error",Toast.LENGTH_SHORT ).show();
    		}
    		//mThreadHandler.post(r1); 	
    		/*
    		Linux_infrared_and_led.read_infrared();
    		try {
    			int i;
    			for(i=0;i<5;i++){
    				Linux_buzzer.send(1,buzzer_on);
    				Linux_buzzer.send(2,buzzer_on);
      				Thread.sleep(100);
      				Linux_buzzer.send(1,buzzer_off);
      				Linux_buzzer.send(2,buzzer_off);
      				Thread.sleep(100);
    				}
    		} catch (InterruptedException e) {
    			// TODO Auto-generated catch block
    			e.printStackTrace();
    		}
    		*/
    	}
    };
    
    private Button.OnClickListener mmyButton_PARTY_listener=new Button.OnClickListener(){
    	public void onClick(View v){
    		try{
    			Toast.makeText(BuzzerActivity.this, "mmyButton_PARTY_listener",Toast.LENGTH_SHORT ).show();
    			//Linux_infrared_and_led.ioctl_infrared(3);
    			Linux_infrared.ioctl_infrared(1);
    			Linux_infrared.ioctl_infrared(1);
    			setTitle("PARTY Sensor Start!!!");
    			top=false;
    			mThreadHandler.post(r1);
    			
    		}catch(Exception e){
    			Toast.makeText(BuzzerActivity.this, "input_error",Toast.LENGTH_SHORT ).show();
    		}
    		
    		//mThreadHandler.post(r1); 
    			
    	}
    };
    private Button.OnClickListener mmyButton_RESET_listensr=new Button.OnClickListener(){
    	public void onClick(View v){
    		try{
    			Toast.makeText(BuzzerActivity.this, "mmyButton_RESET_listensr",Toast.LENGTH_SHORT ).show();
    			Linux_infrared.ioctl_infrared(3);//close all
    			setTitle("Sensor Stop!!!");
    			top=true;
    		}catch(Exception e){
    			Toast.makeText(BuzzerActivity.this, "input_error",Toast.LENGTH_SHORT ).show();
    		}
    		
    	}
    };
    
    private Button.OnClickListener button1_listener=new Button.OnClickListener(){
    	public void onClick(View v){
    		try{
    			Toast.makeText(BuzzerActivity.this, "button1_listener",Toast.LENGTH_SHORT ).show();
    			Linux_buzzer.send(1,buzzer_on);
    		}catch(Exception e){
    			Toast.makeText(BuzzerActivity.this, "input_error",Toast.LENGTH_SHORT ).show();
    		}
    	}
    };
    private Button.OnClickListener button2_listener=new Button.OnClickListener(){
    	public void onClick(View v){
    		try{
    			Toast.makeText(BuzzerActivity.this, "button2_listener",Toast.LENGTH_SHORT ).show();
    			Linux_buzzer.send(1,buzzer_off);
    		}catch(Exception e){
    			Toast.makeText(BuzzerActivity.this, "input_error",Toast.LENGTH_SHORT ).show();
    		}
    	}
    };
    private Button.OnClickListener button3_listener=new Button.OnClickListener(){
    	public void onClick(View v){
    		try{
    			Toast.makeText(BuzzerActivity.this, "button3_listener",Toast.LENGTH_SHORT ).show();
    			Linux_buzzer.send(2,buzzer_off);
    		}catch(Exception e){
    			Toast.makeText(BuzzerActivity.this, "input_error",Toast.LENGTH_SHORT ).show();
    		}
    	}
    };
    private Button.OnClickListener button4_listener=new Button.OnClickListener(){
    	public void onClick(View v){
    		try{
    			Toast.makeText(BuzzerActivity.this, "button4_listener",Toast.LENGTH_SHORT ).show();
    			Linux_buzzer.send(2,buzzer_on);
    		}catch(Exception e){
    			Toast.makeText(BuzzerActivity.this, "input_error",Toast.LENGTH_SHORT ).show();
    		}
    	}
    };
    private Button.OnClickListener button5_listener=new Button.OnClickListener(){
    	public void onClick(View v){
    		try{
    			Toast.makeText(BuzzerActivity.this, "button5_listener",Toast.LENGTH_SHORT ).show();
    			Linux_buzzer.closebuzzer();
    			top=true;
    			if(mThreadHandler != null){
    				mThreadHandler.removeCallbacks(r1);
    			}
    			if(mThread != null){
    				mThread.quit();
    			}
    			finish();
    		}catch(Exception e){
    			Toast.makeText(BuzzerActivity.this, "input_error",Toast.LENGTH_SHORT ).show();
    		}
    	}
    };
    
    private void openOptionDiaglog(){
    	Toast.makeText(BuzzerActivity.this, "about Buzzer",Toast.LENGTH_SHORT ).show();
    	//to create warming box
    	new AlertDialog.Builder(BuzzerActivity.this)
    	.setTitle(R.string.about_title)
    	.setMessage(R.string.about_msg)
    	.setPositiveButton("Confirm", new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface dialoginterface,int i){}
		})
    	.setNegativeButton(R.string.homepage_lebel, new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface dialog, int which) {
				// TODO Auto-generated method stub
				//Homepage
				Uri uri = Uri.parse("http://tw.yahoo.com/");
				Intent intent = new Intent(Intent.ACTION_VIEW,uri);
				startActivity(intent);
			}
		})
    	.show();
    	
    }
    
    
    protected static final int MENU_ABOUT = Menu.FIRST;
    protected static final int MENU_QUIT = Menu.FIRST+1;
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// TODO Auto-generated method stub
		menu.add(0,MENU_ABOUT,0,"關於").setIcon(android.R.drawable.ic_menu_help);
		menu.add(0,MENU_QUIT,0,"結束").setIcon(android.R.drawable.ic_menu_close_clear_cancel);
		return super.onCreateOptionsMenu(menu);
	}
	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// TODO Auto-generated method stub
		switch(item.getItemId()){
		case MENU_ABOUT:
			openOptionDiaglog();
		case MENU_QUIT:
			finish();
			break;
		}
		return super.onOptionsItemSelected(item);
	}
    
    
    
    
}