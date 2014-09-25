package com.jtrzyna.hexapod;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Set;
import java.util.UUID;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.Toast;
import android.widget.Button;


public class ConnectionActivity extends Activity implements OnItemClickListener {

    Button Scan;
    ArrayAdapter<String> devicesInfo;
    ListView listView;
    BluetoothAdapter btAdapter;
    ArrayList<BluetoothDevice> devices;
    public static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_connection);
        init();
        if(btAdapter==null){
            Toast.makeText(getApplicationContext(), "No bluetooth detected", Toast.LENGTH_SHORT).show();
            finish();
        }
        else{
            if(!btAdapter.isEnabled()){
                turnOnBT();
            }
        }
    }


    private void init() {

        Scan = (Button) findViewById(R.id.bScan);
        listView = (ListView) findViewById(R.id.listView);
        listView.setOnItemClickListener(this);
        devicesInfo = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1, 0);
        listView.setAdapter(devicesInfo);
        btAdapter = BluetoothAdapter.getDefaultAdapter();
        devices = new ArrayList<BluetoothDevice>();

        BroadcastReceiver mReceiver = new BroadcastReceiver() {
            public void onReceive(Context context, Intent intent) {
                String action = intent.getAction();
                // When discovery finds a device
                if (BluetoothDevice.ACTION_FOUND.equals(action)) {
                    Toast.makeText(getApplicationContext(), "found", Toast.LENGTH_SHORT).show();
                    // Get the BluetoothDevice object from the Intent
                    BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
                    devices.add(device);
                    // Add the name and address to an array adapter to show in a ListView
                    devicesInfo.add(device.getName() + "\n" + device.getAddress());
                }

                else if(BluetoothAdapter.ACTION_DISCOVERY_STARTED.equals(action)){
                    Toast.makeText(getApplicationContext(), "Discovery started", Toast.LENGTH_SHORT).show();
                }

                else if(BluetoothAdapter.ACTION_DISCOVERY_FINISHED.equals(action)){
                    Toast.makeText(getApplicationContext(), "Discovery finished", Toast.LENGTH_SHORT).show();
                }

                else if(BluetoothAdapter.ACTION_STATE_CHANGED.equals(action)){
                    if(btAdapter.getState() == btAdapter.STATE_OFF){
                        turnOnBT();
                    }
                }
            }
        };

        IntentFilter filter = new IntentFilter(BluetoothDevice.ACTION_FOUND);
        registerReceiver(mReceiver, filter);
        filter = new IntentFilter(BluetoothAdapter.ACTION_DISCOVERY_STARTED);
        registerReceiver(mReceiver, filter);
        filter = new IntentFilter(BluetoothAdapter.ACTION_DISCOVERY_FINISHED);
        registerReceiver(mReceiver, filter);

    }

    public void onScanClicked(View V){
        startDiscovery();
    }
    private void startDiscovery() {
        btAdapter.cancelDiscovery();
        btAdapter.startDiscovery();
    }


    private void turnOnBT() {
        Intent intent =new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
        startActivityForResult(intent, 1);
    }


    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        // TODO Auto-generated method stub
        super.onActivityResult(requestCode, resultCode, data);
        if(resultCode ==  RESULT_CANCELED){
            Toast.makeText(getApplicationContext(), "Bluetooth must be enabled to continue", Toast.LENGTH_SHORT).show();
            finish();
        }
    }
    public void onItemClick(AdapterView<?> arg0, View arg1, int arg2, long arg3) {
    }


}
