package com.jtrzyna.hexapod;

import android.app.Activity;
import android.content.Intent;
import android.os.CountDownTimer;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.view.animation.AlphaAnimation;
import android.widget.AdapterView;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.AdapterView.OnItemClickListener;

public class intro extends Activity {

    ImageView logo;
    private AlphaAnimation alphaDown;
    private AlphaAnimation alphaUp;

    private void init(){
        logo = (ImageView)findViewById(R.id.logoPic);
        logo.setVisibility(View.INVISIBLE);

        alphaDown = new AlphaAnimation(1.0f, 0.0f);
        alphaUp = new AlphaAnimation(0.0f, 1.0f);

        alphaDown.setDuration(1500);
        alphaUp.setDuration(1500);
        alphaDown.setFillAfter(true);
        alphaUp.setFillAfter(true);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(R.layout.activity_intro);
        init();

         CountDownTimer timer = new CountDownTimer(5000,1) {
            public void onTick(long millisUntilFinished) {
                if(millisUntilFinished==4000){
                    logo.setVisibility(View.VISIBLE);
                    logo.startAnimation(alphaUp);
                }
                else if(millisUntilFinished==2000){
                    logo.startAnimation(alphaDown);
                }
                else if(millisUntilFinished<=500){
                    logo.setVisibility(View.INVISIBLE);
                }


            }

            public void onFinish() {
                Intent startProgram = new Intent("synergia.jakub.trzyna.CONNECTION");
                startActivity(startProgram);
            }
        };
        timer.start();

    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_intro, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
