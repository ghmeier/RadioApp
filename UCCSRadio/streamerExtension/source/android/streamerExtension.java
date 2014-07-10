/*
java implementation of the streamer extension.

Add android-specific functionality here.

These functions are called via JNI from native code.
*/
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
import com.ideaworks3d.marmalade.LoaderAPI;
import com.ideaworks3d.marmalade.LoaderActivity;
import android.content.Intent;
import android.app.PendingIntent;
import com.squareinfinity.streamer.StreamerService;

class streamerExtension
{
	static int i = 1;
	private void sendIntent(String act, String url){
		Intent intent = new Intent(LoaderActivity.m_Activity, StreamerService.class);
		intent.putExtra("action", act);
		intent.putExtra("url", url);
		intent.putExtra("mainActivity", LoaderActivity.m_Activity.getClass().getName());
		intent.addFlags(Intent.FLAG_RECEIVER_FOREGROUND);
		try{
		PendingIntent.getService(LoaderActivity.m_Activity, i++, intent, 0).send();
		}catch(PendingIntent.CanceledException e){e.printStackTrace();}
		//LoaderActivity.m_Activity.startService(intent);
	}

	public int initAudioStream(String ip, int port)
	{
		sendIntent("init", "http://" + ip + ":" + port);
		return 0;
	}
    public int startStreamingAudio()
    {
		sendIntent("start", "");
        return 0;
    }
    public int stopStreamingAudio()
    {
		sendIntent("stop", "");
        return 0;
    }
	public int pauseStreamingAudio()
    {
		sendIntent("pause", "");
        return 0;
    }
}
