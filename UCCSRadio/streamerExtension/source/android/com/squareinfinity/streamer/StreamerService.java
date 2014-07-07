package com.squareinfinity.streamer;
import android.app.Service;
import android.content.Intent;
import android.app.PendingIntent;
import android.media.MediaPlayer;
import java.io.IOException;
import android.app.Notification;
import android.app.NotificationManager;
import android.content.Context;
import com.ideaworks3d.marmalade.ResourceUtility;
import android.os.PowerManager;
import android.os.PowerManager.WakeLock;
import android.net.wifi.WifiManager;
import android.net.wifi.WifiManager.WifiLock;
import android.os.IBinder;

public class StreamerService extends Service implements MediaPlayer.OnPreparedListener {
    MediaPlayer mMediaPlayer = null;
	WifiLock wifiLock = null;
	boolean ready = false;
	
	private Notification makeNotification(){
		PendingIntent contentIntent = null;
		Notification notification = null;
		try{
			contentIntent = PendingIntent.getActivity(this, 0, new Intent(this, Class.forName("com.SquareInfinity.UCCSRadio.Main")), 0);
			notification = new Notification();
			notification.tickerText = "";
			notification.icon = ResourceUtility.getResId("drawable", "icon");
			notification.flags |= Notification.FLAG_ONGOING_EVENT;
			notification.setLatestEventInfo(getApplicationContext(), "UCCS Radio", "Playing Radio", contentIntent);
		}catch(java.lang.ClassNotFoundException e){e.printStackTrace();}
		catch(java.lang.Exception e){e.printStackTrace(); return null;}
		return notification;
	}
	
	private void init(String url){
		try{
			mMediaPlayer = new MediaPlayer();
			mMediaPlayer.setDataSource(url);
			mMediaPlayer.setOnPreparedListener(this);
			mMediaPlayer.setWakeMode(getApplicationContext(), PowerManager.PARTIAL_WAKE_LOCK);
			mMediaPlayer.prepareAsync(); // prepare async to not block main thread
		}catch(IOException e){e.printStackTrace();}
		stopForeground(true);
		if(wifiLock != null) wifiLock.release();
	}
	
	private void play(){
		if(!ready || mMediaPlayer == null || mMediaPlayer.isPlaying()) return;
		System.out.println("AAA playing");
		mMediaPlayer.start();
		
		System.out.println("AAA getting wifilock");
		wifiLock = null;
		WifiManager mgr = (WifiManager)getSystemService(Context.WIFI_SERVICE);
		if(mgr != null) wifiLock = mgr.createWifiLock(WifiManager.WIFI_MODE_FULL, "streamerLock");
		if(wifiLock != null) wifiLock.acquire();
		System.out.println("AAA wifilock done");
		
		Notification notif = makeNotification();
		if(notif != null) startForeground(1, notif);
		System.out.println("AAA started foreground");
	}
	
	private void pause(){
		if(mMediaPlayer != null && mMediaPlayer.isPlaying()) mMediaPlayer.pause();
		stopForeground(true);
		if(wifiLock != null) wifiLock.release();
	}

	@Override
    public int onStartCommand(Intent intent, int flags, int startId) {
		if(intent == null){pause(); stopSelf(); return START_NOT_STICKY;}
        String act = intent.getStringExtra("action");
		if(act != null){
			if (act.equals("init")) {
				String url = intent.getStringExtra("url");
				if(url != null) init(url);
			}else if(act.equals("start")) play();
			else if(act.equals("pause")) pause();
			else if(act.equals("stop")){ pause(); stopSelf();}
		}
		return START_NOT_STICKY;
    }
	
	@Override
	public IBinder onBind(Intent intent){
		return null;
	}
	
	@Override
	public void onCreate() {
		super.onCreate();
		stopForeground(true);
		if(wifiLock != null) wifiLock.release();
	}
	
	@Override
	public void onDestroy() {
		pause();
		ready = false;
		if (mMediaPlayer != null){mMediaPlayer.release(); mMediaPlayer = null;}
		super.onDestroy();
	}

    /** Called when MediaPlayer is ready */
    public void onPrepared(MediaPlayer player) {
		ready = true;
    }
}
