package com.qhipa.qhipa.car;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import com.qhipa.qhipa.car.api.ServiceGenerator;
import com.qhipa.qhipa.car.api.models.Motor;
import com.qhipa.qhipa.car.api.services.MotorService;

import retrofit.Call;
import retrofit.Callback;
import retrofit.Response;

public class MainActivity extends AppCompatActivity implements View.OnClickListener{

    private Button Forward;
    private Button Backward;
    private Button Left;
    private Button Right;
    private Button Stop;

    private MotorService mMotorService;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Forward = (Button)findViewById(R.id.Forward);
        Backward = (Button)findViewById(R.id.Backward);
        Left = (Button)findViewById(R.id.Left);
        Right = (Button)findViewById(R.id.Right);
        Stop = (Button)findViewById(R.id.Stop);

        Forward.setOnClickListener(this);
        Backward.setOnClickListener(this);
        Left.setOnClickListener(this);
        Right.setOnClickListener(this);
        Stop.setOnClickListener(this);

        mMotorService = ServiceGenerator.createService(MotorService.class);
    }

    @Override
    public void onClick(View v) {
        Motor m = new Motor();

        switch (v.getId()){
            case R.id.Forward:
                m.setStatus("F");
                break;
            case R.id.Backward:
                m.setStatus("B");
                break;
            case R.id.Left:
                m.setStatus("L");
                break;
            case R.id.Right:
                m.setStatus("R");
                break;
            case R.id.Stop:
                m.setStatus("S");
                break;
            default:

        }
        Call<Motor> call = mMotorService.sendData(m);
        call.enqueue(new Callback<Motor>() {
            @Override
            public void onResponse(Response<Motor> response) {
                response.body().getStatus();
            }

            @Override
            public void onFailure(Throwable t) {

            }
        });
    }
}
