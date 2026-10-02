package com.example.subvisibility;

import com.example.visibility.PublicClass;
import com.example.visibility.PrivateClass;
import com.example.visibility.ProtectedClass;


public class ClasseLiee extends ProtectedClass{

    public ClasseLiee(int i){
        super(i);
    }
    public static void main(String[] argv){
        ClasseLiee myclass= new ClasseLiee(2);
        System.out.println("j'herite de Protected l'attribut est: "+ myclass.aprt);
    }
}


//conclusion: dans la classe liée on a pu acceder a l'attribu protected mais private reste toujours inaccessible sans getters..