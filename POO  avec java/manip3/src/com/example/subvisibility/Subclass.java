// celle la est la class non liée car pas d'heritage
package com.example.subvisibility;

import com.example.visibility.PublicClass;
import com.example.visibility.ProtectedClass;
import com.example.visibility.PrivateClass;

public class Subclass{
    public static void main(String[] argv){
        PublicClass PublicAtt= new PublicClass(1);
        ProtectedClass ProtectedAtt= new ProtectedClass(2);
        PrivateClass PrivateAtt= new PrivateClass(3); 
        System.out.println("Public attribut: "+ PublicAtt.apublic);
        //System.out.println("Protected attribut: "+ ProtectedAtt.aprt);
        //System.out.println("Private attribut: "+ PrivateAtt.aprivate);       
    }
}