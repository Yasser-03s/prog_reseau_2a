package com.library.main;

import com.library.books.Book;
import com.library.members.Member;

public class LibraryApp {
    public static void main(String[] args) {
        // Création de livres
        Book book1 = new Book("Les Misérables", "Victor Hugo", 15.99);
        Book book2 = new Book("Le Petit Prince", "Antoine de Saint-Exupéry", 9.50);

        // Création de membres
        Member member1 = new Member("Alice Dupont", "M001", "Étudiant");
        Member member2 = new Member("Jean Martin", "M002", "Enseignant");

        // Affichage des informations des livres
        System.out.println("Livres disponibles :");
        book1.displayInfo();
        book2.displayInfo();

        // Affichage des informations des membres
        System.out.println("\nMembres de la bibliothèque :");
        member1.displayInfo();
        member2.displayInfo();
    }
}
