package com.library.members;

public class Member{
    String nom;
    String identifiant;
    String type;

    public Member(String nom, String identifiant, String type){
        this.nom= nom;
        this.identifiant= identifiant;
        this.type= type;
    }
    public void displayInfo(){ 
        System.out.println("nom: "+ nom+" id: "+identifiant+" type: "+type);
    }
}
