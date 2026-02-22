package com.example.template.domeniu;

import java.time.LocalDate;

public class DTO {
    private Long clientId;
    private String locatie;
    private LocalDate data1;
    private LocalDate data2;
    public DTO(Long clientID, String locatie, LocalDate data1, LocalDate data2){
        this.clientId=clientID;
        this.locatie=locatie;
        this.data1=data1;
        this.data2=data2;
    }

    public Long getClientId() {
        return clientId;
    }

    public void setClientId(Long clientId) {
        this.clientId = clientId;
    }

    public String getLocatie() {
        return locatie;
    }

    public void setLocatie(String locatie) {
        this.locatie = locatie;
    }

    public LocalDate getData1() {
        return data1;
    }

    @Override
    public String toString() {
        return "DTO{" +
                "clientId=" + clientId +
                ", locatie='" + locatie + '\'' +
                ", data1=" + data1 +
                ", data2=" + data2 +
                '}';
    }

    public void setData1(LocalDate data1) {
        this.data1 = data1;
    }

    public LocalDate getData2() {
        return data2;
    }

    public void setData2(LocalDate data2) {
        this.data2 = data2;
    }
}
