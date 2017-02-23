package com.qhipa.qhipa.car.api.models;

import com.google.gson.annotations.Expose;
import com.google.gson.annotations.SerializedName;

public class Motor {

    @SerializedName("date_created")
    @Expose
    private String dateCreated;
    @SerializedName("status")
    @Expose
    private String status;

    /**
     * No args constructor for use in serialization
     *
     */
    public Motor() {
    }

    /**
     *
     * @param status
     * @param dateCreated
     */
    public Motor(String dateCreated, String status) {
        super();
        this.dateCreated = dateCreated;
        this.status = status;
    }

    public String getDateCreated() {
        return dateCreated;
    }

    public void setDateCreated(String dateCreated) {
        this.dateCreated = dateCreated;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

}