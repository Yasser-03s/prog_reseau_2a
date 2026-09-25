package com.library.books;

public class Book{
    public String titre;
    public String auteur;
    public Double prix;

    public Book(String titre, String auteur, Double prix){
        this.titre = titre;
        this.auteur = auteur;
        this.prix = prix;
    }

    public void displayInfo(){
        System.out.println("le livre "+ titre+" de "+auteur+" coute: "+prix);
    }
}