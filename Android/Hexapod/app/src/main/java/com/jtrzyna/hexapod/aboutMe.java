package com.jtrzyna.hexapod;

import android.app.AlertDialog;
import android.app.Dialog;
import android.app.DialogFragment;
import android.content.DialogInterface;
import android.os.Bundle;

/**
 * Created by Jakub Trzyna on 2014-12-03.
 */
public class aboutMe extends DialogFragment {

    String message = "created by Jakub Trzyna\n'MKMN Synergia'\nWroclaw University of Technology";

    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        // Use the Builder class for convenient dialog construction
        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
        builder.setMessage(message)
                .setPositiveButton("ok", new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int id) {
                        //do nothing
                    }
                });
        // Create the AlertDialog object and return it
        return builder.create();
    }
}