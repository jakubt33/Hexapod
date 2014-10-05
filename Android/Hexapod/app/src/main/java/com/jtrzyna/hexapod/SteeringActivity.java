package com.jtrzyna.hexapod;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
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
import java.util.ArrayList;
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

    int y= 0;
    ToggleButton power;
    ToggleButton singleLegMode;
    ToggleButton basePosition;
    TextView xPosition;
    TextView yPosition;
    TextView btTargetName;
    TextView messageReceived;
    ProgressBar progressBar;
    ImageView steeringWheel;

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
                    String string = new String(readBuf);
                    messageReceived.setText(string);
                    break;
            }
        }
    };

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_steering);

        init();

        String getData = "start";
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
                //connect = new ConnectThread(selectedDevice);
                //connect.start();
            }
            else {
                finish();
            }

        }
    }

    private void init(){

        progressBar = (ProgressBar)findViewById(R.id.progressBar);
        devices = new ArrayList<BluetoothDevice>();
        xPosition = (TextView)findViewById(R.id.xPosition);
        yPosition = (TextView)findViewById(R.id.yPosition);
        btTargetName = (TextView)findViewById(R.id.textState);
        messageReceived = (TextView)findViewById(R.id.textReceived);
        power = (ToggleButton)findViewById(R.id.bPower);
        singleLegMode = (ToggleButton)findViewById(R.id.bSingleLeg);
        basePosition = (ToggleButton)findViewById(R.id.bBasePosition);
        steeringWheel = (ImageView)findViewById(R.id.imageView);
        steeringWheel.setOnTouchListener(this);


        waitForConnection = new CountDownTimer(3000, 30) {
            public void onTick(long millisUntilFinished) {
                progressBar.setProgress(100-(int)millisUntilFinished/30);
            }

            public void onFinish() {
                progressBar.setVisibility(View.INVISIBLE);
                Toast.makeText(getApplicationContext(), "Connection ready!", Toast.LENGTH_SHORT).show();
                messageHandler.start();
            }
        };

        messageHandler = new CountDownTimer(1000, 10) {
            public void onTick(long millisUntilFinished) {
            }

            public void onFinish() {
                y++;
                connectedThread.write(Integer.toString(y).getBytes());
                connectedThread.run();
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

    boolean moving = false;
    @Override
    public boolean onTouch(View view, MotionEvent motionEvent) {

        switch (motionEvent.getAction()) {
            case MotionEvent.ACTION_DOWN:
                messageReceived.setText("touched");
                moving = true;
                break;
            case MotionEvent.ACTION_MOVE:
                if(moving) {
                    xPosition.setText(Float.toString(view.getX()));
                    yPosition.setText(Float.toString(view.getY()));
                }
                break;
            case MotionEvent.ACTION_UP:
                messageReceived.setText("untouched");
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
            } catch (IOException e) { }

            mmInStream = tmpIn;
            mmOutStream = tmpOut;
        }


        public void run() {
            byte[] buffer;  // buffer store for the stream
            int bytes; // bytes returned from read()

            try {
                // Read from the InputStream
                buffer = new byte[1024];
                bytes = mmInStream.read(buffer);
                // Send the obtained bytes to the UI activity
                mHandler.obtainMessage(MESSAGE_READ, bytes, -1, buffer)
                        .sendToTarget();

            } catch (IOException e) {
                //break;
            }

        }

        /* Call this from the main activity to send data to the remote device */
        public void write(byte[] bytes) {
            try {
                mmOutStream.write(bytes);
            } catch (IOException e) { }
        }

        /* Call this from the main activity to shutdown the connection */
        public void cancel() {
            try {
                mmSocket.close();
            } catch (IOException e) { }
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
            }
        }
    }

}