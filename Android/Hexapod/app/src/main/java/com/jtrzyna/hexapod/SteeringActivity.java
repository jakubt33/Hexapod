package com.jtrzyna.hexapod;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.ContentUris;
import android.content.Intent;
import android.gesture.GesturePoint;
import android.os.Bundle;
import android.os.CountDownTimer;
import android.os.Handler;
import android.os.Message;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.ProgressBar;
import android.widget.RadioButton;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ToggleButton;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.Serializable;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.Set;
import java.util.UUID;


public class SteeringActivity extends Activity implements View.OnTouchListener {

    public static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
    ConnectedThread connectedThread;
    ConnectThread connect;
    BluetoothAdapter btAdapter;
    ArrayList<BluetoothDevice> devices;
    Set<BluetoothDevice> devicesArray;
    BluetoothDevice selectedDevice;

    ToggleButton power;
    ToggleButton singleLegMode;
    ToggleButton basePosition;
    TextView btTargetName;
    TextView messageReceived;
    ProgressBar progressBar;
    ProgressBar batteryBar;
    ImageView steeringWheel;

    //byte[] buffer = new byte[2];
    boolean startGatheringData = false;
    int tempCommand[] = new int[2];
    byte[] command = new byte[2];
    int[] img_coordinates = new int[2];
    int Curve, Direction;
    boolean moving = false;
    //Curve - left, right, 0-15
    //Direction, forth, back, 0-15

    CountDownTimer messageHandler;
    CountDownTimer waitForConnection;

    protected static final int MESSAGE_READ = 1;
    protected static final int SUCCESS_CONNECT = 2;

    Handler mHandler = new Handler() {
        public void handleMessage(Message msg) {
            // TODO Auto-generated method stub
            super.handleMessage(msg);
            switch (msg.what) {
                case SUCCESS_CONNECT:
                    connectedThread = new ConnectedThread((BluetoothSocket)msg.obj);
                    mainLoop();//works,
                    break;

                case MESSAGE_READ:
                    byte[] readBuf = (byte[]) msg.obj;

                    if(readBuf[0] != 0) {
                        //batteryBar.setProgress((readBuf[0] + 128) / 3);
                    }
                    break;
            }
        }
    };

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_steering);

        init();

        String getData;
        btAdapter = BluetoothAdapter.getDefaultAdapter();

        devicesArray = btAdapter.getBondedDevices();
        devices.addAll(devicesArray);

        Intent myIntent = getIntent();
        Bundle b = myIntent.getExtras();
        if(b.containsKey("deviceName") ) {
            getData = b.getString("deviceName");
            int foundFlag = 0;
            for (int i=0; i<devices.size(); i++) {
                if(devices.get(i).getName().equals(getData)){
                    selectedDevice = devices.get(i);
                    btTargetName.setText("connected to: " + selectedDevice.getName());
                    foundFlag = 1;

                    break;
                }
            }
            if(foundFlag == 1) {
                connect = new ConnectThread(selectedDevice);
                connect.start();
            }
            else {
                finish();
            }

        }
    }

    private void init(){

        progressBar = (ProgressBar)findViewById(R.id.progressBar);
        batteryBar = (ProgressBar)findViewById(R.id.batteryBar);
        devices = new ArrayList<BluetoothDevice>();
        btTargetName = (TextView)findViewById(R.id.textState);
        messageReceived = (TextView)findViewById(R.id.textReceived);
        power = (ToggleButton)findViewById(R.id.bPower);
        singleLegMode = (ToggleButton)findViewById(R.id.bSingleLeg);
        basePosition = (ToggleButton)findViewById(R.id.bBasePosition);
        steeringWheel = (ImageView)findViewById(R.id.imageView);
        steeringWheel.setOnTouchListener(this);


        waitForConnection = new CountDownTimer(2500,25) {
            public void onTick(long millisUntilFinished) {
                progressBar.setProgress(100-(int)millisUntilFinished/25);
            }

            public void onFinish() {
                progressBar.setVisibility(View.INVISIBLE);
                Toast.makeText(getApplicationContext(), "Connection ready!", Toast.LENGTH_SHORT).show();

                messageHandler.start();
            }
        };

        messageHandler = new CountDownTimer(1000,25) {
            public void onTick(long millisUntilFinished) {
                startGatheringData = false;

                tempCommand[0] = 64; //start message
                tempCommand[1] = 192; //message indicator

                if(power.isChecked()){
                    tempCommand[1] += 1;
                }

                if(!basePosition.isPressed()) {

                    //dead zone-------------------------
                    if (Curve > 0) Curve--;
                    else if (Curve < 0) Curve++;
                    if (Direction > 0) Direction--;
                    else if (Direction < 0) Direction++;

                    if (Direction >= 16) Direction = 15;
                    if (Direction <= -16) Direction = -15;
                    if (Curve >= 15) Curve = 14;
                    if (Curve <= -15) Curve = -14;
                    //----------------------------------

                    if ((Curve <= 14 && Curve >= -14) && (Direction <= 15 && Direction >= -15)) {
                        if (Direction > 0) {
                            tempCommand[0] += 1;
                        } else if (Direction < 0) {
                            tempCommand[0] += 2;
                        }
                        tempCommand[0] += 4 * (int) ((Curve + 14) / 2);
                        int speed = (int) Math.sqrt(Curve * Curve + Direction * Direction);
                        tempCommand[1] += speed * 2; //speed
                        tempCommand[1] += (Curve % 2) * 32;
                        //-----------------------------------
                    }
                    //xPosition.setText(Integer.toString((int)millisUntilFinished));
                    //yPosition.setText("comm: " + command[0] + " " + command[1] );
                }
                else{
                    tempCommand[0] = 67;
                }

                command[0] = (byte) tempCommand[0];
                command[1] = (byte) tempCommand[1];
                connectedThread.write(command);

                startGatheringData = true;
            }

            public void onFinish() {

                start();
            }
        };
    }

    private void mainLoop(){
        waitForConnection.start();
    }

    public void onBasePositionClicked(View v){

    }
    public void onPowerClicked(View v){

    }
    public void onSingleLegClicked(View v){

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.steering, menu);
        return true;
    }

    @Override
    protected void onPause(){
        connectedThread.cancel();
        connect.cancel();
    }
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

    @Override
    public boolean onTouch(View view, MotionEvent motionEvent) {
        float maxX, maxY = 0;
        maxX = steeringWheel.getWidth()/2;
        maxY = steeringWheel.getHeight()/2;


        switch (motionEvent.getAction()) {
            case MotionEvent.ACTION_DOWN:
                moving = true;
                break;
            case MotionEvent.ACTION_MOVE:
                if( moving && startGatheringData ) {
                    img_coordinates[0] = 0;
                    img_coordinates[1] = 0;

                    steeringWheel.getLocationOnScreen(img_coordinates);

                    Curve = (int) ((motionEvent.getRawX() - (img_coordinates[0] + steeringWheel.getWidth() / 2)) / maxX * 21);
                    Direction = (int) ((img_coordinates[1] + steeringWheel.getHeight() / 2 - motionEvent.getRawY()) / maxY * 21);

                }
                break;
            case MotionEvent.ACTION_UP:
                Curve = 0;
                Direction = 0;
                moving = false;
                break;
        }

        return true;
    }

    private class ConnectedThread extends Thread {
        private final BluetoothSocket mmSocket;
        private final InputStream mmInStream;
        private final OutputStream mmOutStream;

        public ConnectedThread(BluetoothSocket socket) {
            mmSocket = socket;
            InputStream tmpIn = null;
            OutputStream tmpOut = null;

            // Get the input and output streams, using temp objects because
            // member streams are final
            try {
                tmpIn = socket.getInputStream();
                tmpOut = socket.getOutputStream();
            } catch (IOException e) {
                e.printStackTrace();
            }

            mmInStream = tmpIn;
            mmOutStream = tmpOut;
        }


        public void run() {
            /*byte buffer[] = new byte[1000];  // buffer store for the stream
            int bytes; // bytes returned from read()

            try {
                // Read from the InputStream
                //buffer[0] = 0;
                bytes = mmInStream.read(buffer);
                // Send the obtained bytes to the UI activity
                mHandler.obtainMessage(MESSAGE_READ, bytes, -1, buffer).sendToTarget();

            } catch (IOException e) {
                e.printStackTrace();
            }*/

        }

        /* Call this from the main activity to send data to the remote device */
        public void write(byte[] bytes) {
            try {
                mmOutStream.write(bytes);
                //mmOutStream.flush();
            } catch (IOException e) {
            e.printStackTrace();
            }
        }

        /* Call this from the main activity to shutdown the connection */
        public void cancel() {
            try {
                mmSocket.close();
            } catch (IOException e) {
            e.printStackTrace();
            }
        }
    }

    private class ConnectThread extends Thread {
        private final BluetoothSocket mmSocket;
        private final BluetoothDevice mmDevice;

        public ConnectThread(BluetoothDevice device) {
            // Use a temporary object that is later assigned to mmSocket,
            // because mmSocket is final
            BluetoothSocket tmp = null;
            mmDevice = device;

            // Get a BluetoothSocket to connect with the given BluetoothDevice
            try {
                // MY_UUID is the app's UUID string, also used by the server code
                tmp = device.createRfcommSocketToServiceRecord(MY_UUID);
            } catch (IOException e) {
                e.printStackTrace();
            }
            mmSocket = tmp;
        }

        public void run() {
            // Cancel discovery because it will slow down the connection
            btAdapter.cancelDiscovery();

            try {
                // Connect the device through the socket. This will block
                // until it succeeds or throws an exception
                mmSocket.connect();
            } catch (IOException connectException) {
                // Unable to connect; close the socket and get out
                try {
                    mmSocket.close();
                } catch (IOException closeException) {
                    closeException.printStackTrace();
                }
                return;
            }
            mHandler.obtainMessage(SUCCESS_CONNECT, mmSocket).sendToTarget();
        }

        /**
         * Will cancel an in-progress connection, and close the socket
         */
        public void cancel() {
            try {
                mmSocket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

}