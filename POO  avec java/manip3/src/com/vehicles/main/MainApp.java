package com.vehicles.main; 

//import com.vehicles.car.Car;
//import com.vehicles.bike.Car;
//conflit de noms


import com.vehicles.car.*;
import com.vehicles.bike.*;
//solution: utiliser import avec .* a la fin au lien de nommer la class, 
//mais utiliser les noms qualifiés: com.vehicles.car.Car vehicles.bike.Car

public class MainApp{
    public static void main(String[] argv){
        com.vehicles.car.Car Voiture1 = new com.vehicles.car.Car(13);
        com.vehicles.bike.Car Voiture2 = new com.vehicles.bike.Car(12);

        Voiture1.Stats();
        Voiture2.Stats();
    }
}