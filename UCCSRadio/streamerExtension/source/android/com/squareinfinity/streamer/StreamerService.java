package com.squareinfinity.streamer;

import com.ideaworks3d.marmalade.ResourceUtility;
import android.app.Service;
import android.app.PendingIntent;
import android.app.Notification;
import android.content.Intent;
import android.content.Context;
import android.media.MediaPlayer;
import android.net.wifi.WifiManager;
import android.net.wifi.WifiManager.WifiLock;
import android.os.IBinder;
import android.os.PowerManager;

public class StreamerService extends Service implements MediaPlayer.OnPreparedListener, MediaPlayer.OnCompletionListener {
    MediaPlayer mMediaPlayer = null;
	WifiLock wifiLock = null;
	boolean ready = false;
	boolean playWhenReady = false;
	boolean playing = false;
	String playingurl = null;
	
	private Notification makeNotification(String mainAct){
		PendingIntent contentIntent = null;
		Notification notification = null;
		try{
			if(mainAct != null)
				contentIntent = PendingIntent.getActivity(this, 0, new Intent(this, Class.forName(mainAct)), 0);
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
			mMediaPlayer.setOnCompletionListener(this);
			mMediaPlayer.setOnPreparedListener(this);
			mMediaPlayer.setWakeMode(getApplicationContext(), PowerManager.PARTIAL_WAKE_LOCK);
			mMediaPlayer.prepareAsync(); // prepare async to not block main thread
		}catch(java.io.IOException e){e.printStackTrace();}
		stopForeground(true);
		if(wifiLock != null) wifiLock.release();
		ready = false;
		playWhenReady = false;
		playingurl = url;
	}
	
	private void play(String mainAct){
		if(mMediaPlayer == null || mMediaPlayer.isPlaying()) return;
		if(ready) mMediaPlayer.start();
		else playWhenReady = true;
		
		wifiLock = null;
		WifiManager mgr = (WifiManager)getSystemService(Context.WIFI_SERVICE);
		if(mgr != null) wifiLock = mgr.createWifiLock(WifiManager.WIFI_MODE_FULL, "streamerLock");
		if(wifiLock != null) wifiLock.acquire();
		
		Notification notif = makeNotification(mainAct);
		if(notif != null) startForeground(1, notif);
		playing = true;
	}
	
	private void pause(){
		playing = false;
		if(mMediaPlayer != null && mMediaPlayer.isPlaying()) mMediaPlayer.pause();
		stopForeground(true);
		if(wifiLock != null) wifiLock.release();
		playWhenReady = false;
	}

	@Override
    public int onStartCommand(Intent intent, int flags, int startId) {
		if(intent == null){pause(); stopSelf(); return START_NOT_STICKY;}
        String act = intent.getStringExtra("action");
		if(act != null){
			if (act.equals("init")) {
				String url = intent.getStringExtra("url");
				if(url != null) init(url);
			}else if(act.equals("start")) play(intent.getStringExtra("mainActivity"));
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
		if(playWhenReady) player.start();
		playWhenReady = false;
    }
	
	public void onCompletion(MediaPlayer mp) {
		System.out.println("mediaplayer error");
		if(playing){
			System.out.println("restarting player");
			ready = false;
			mp.reset();
			try{
				mp.setDataSource(playingurl);
				mp.prepareAsync();
				playWhenReady = true;
			}catch(java.io.IOException e){e.printStackTrace();}
		}
	}
}
