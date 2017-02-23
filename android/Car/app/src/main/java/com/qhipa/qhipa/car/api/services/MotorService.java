package com.qhipa.qhipa.car.api.services;

import com.qhipa.qhipa.car.api.urls;
import com.qhipa.qhipa.car.api.models.Motor;

import retrofit.http.Body;
import retrofit.http.POST;
import retrofit.Call;

/**
 * Created by qhipa on 2/22/17.
 */

public interface MotorService {
    @POST(urls.API_MOTOR)
    Call<Motor> sendData(@Body Motor motor);
}
