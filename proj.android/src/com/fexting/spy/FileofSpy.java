/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.fexting.spy;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import twitter4j.Status;
import twitter4j.Twitter;
import twitter4j.TwitterException;
import twitter4j.TwitterFactory;
import twitter4j.auth.RequestToken;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.DialogInterface.OnClickListener;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.StrictMode;
import android.view.WindowManager;

import com.facebook.Request;
import com.facebook.Response;
import com.facebook.Session;
import com.facebook.SessionState;
import com.facebook.model.GraphUser;

public class FileofSpy extends Cocos2dxActivity{
	
	////////////////////////////////////-Twitter
	private Twitter twitter;
	private twitter4j.auth.AccessToken acToken;
	private RequestToken rqToken;
	private Status status = null;
	
	public static Uri CALLBACK_URL = Uri.parse("wefu://twitter");
	public static String consumerkey = "1TMtSFKfYWUtUmu9FThGk55vZ";
	public static String consumersecret ="Oa5wERIOa7OGEGw8vhxeHeddV6Kym3y8ISIBMd3052DvFSKKdG";
/////////////////////////////////////////////
	public static final int CALL_GAMEEND = 1;
	public static final int CALL_TWITTER = 2;
	public static final int CALL_FACEBOOK = 3;
	
	
	private Activity ac;
	static Handler b_handler;
    protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		if (android.os.Build.VERSION.SDK_INT > 9) {
            StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder()
                    .permitAll().build();
            StrictMode.setThreadPolicy(policy);
        }
		//트위터
		 twitter = new TwitterFactory().getInstance();
	     twitter.setOAuthConsumer(consumerkey, consumersecret);
	     rqToken = null;
	        
		ac= this;
		this.getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		  final AlertDialog.Builder dia = new AlertDialog.Builder(this);
	        dia.setTitle("Are you serious?");   //인데 없어도 된다
	        dia.setMessage("Please think it again!");
	        dia.setCancelable(false);
	        dia.setPositiveButton("Nothing can stop me", new OnClickListener() {
	         @Override
	         public void onClick(DialogInterface dialog, int which) {
	        	exitGame();
	         }
	        });

	        dia.setNegativeButton("Sorry It's mistake", new OnClickListener() {
	         @Override
	         public void onClick(DialogInterface dialog, int which) {
	        
	         }
	        });    

	      
		b_handler = new Handler() {
			public void handleMessage(Message msg) {
				switch (msg.what) {
				case CALL_GAMEEND:
					  dia.show(); 
					break;
				case CALL_TWITTER:
					 try
				        {
				        	if(twitter!=null)
				            rqToken = twitter.getOAuthRequestToken();
				        }
				        catch(TwitterException e)
				        {
				            // TODO Auto-generated catch block
				            e.printStackTrace();
				        }
				        startActivity(new Intent(Intent.ACTION_VIEW, Uri.parse(rqToken.getAuthorizationURL())));
				        
					break;
				case CALL_FACEBOOK:
					Session.openActiveSession(ac, true, new Session.StatusCallback() {
			          // callback when session changes state
			          @Override
			          public void call(Session session, SessionState state, Exception exception) {
			        	  if (session.isOpened()) {
			        		Request.executeMeRequestAsync(session,new Request.GraphUserCallback() {
			        		    @Override
			        		    public void onCompleted(GraphUser user, Response response) {
			        		    	if(user!=null)
			        		    	{
			        		    		
			        		    	}
			        		    }
			        		  });		  
			        	  }
			          }
			        });
					break;
				}
			}
		};
	}

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
      super.onActivityResult(requestCode, resultCode, data);
      Session.getActiveSession().onActivityResult(this, requestCode, resultCode, data);
    }

    
    public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// FileofSpy should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	
    	return glSurfaceView;
    }

    private native void exitGame();
    public static void callDialog() {
		 b_handler.sendEmptyMessage(CALL_GAMEEND);
		 
	}
   
    public static void integrateTwitter() {
		 b_handler.sendEmptyMessage(CALL_TWITTER);
		 
	}
    public static void integrateFacebook() {
		 b_handler.sendEmptyMessage(CALL_FACEBOOK);
		 
	}
    static {
        System.loadLibrary("cocos2dcpp");
    }     
}
