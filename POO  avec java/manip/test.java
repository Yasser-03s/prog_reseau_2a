//1. Cherchez la méthode qui permet de mettre une chaı̂ne en majuscules.
//— Comment fonctionne cette méthode ?
//— Modifiez le programme précédent pour construire une chaı̂ne en ma-
//juscules à partir de s.
//2. De la même manière, trouvez les méthodes qui permettent de :
//(a) Convertir une chaı̂ne en minuscules.
//(b) Extraire une sous-chaı̂ne à partir d’une chaı̂ne.
//(c) Vérifier si une chaı̂ne commence par une autre chaı̂ne donnée.
//(d) Calculer la longueur d’une chaı̂ne.
//(e) Concaténer deux chaı̂nes.
//3. Testez toutes ces méthodes dans un programme Java.
//4. Question de réflexion : Les méthodes qui renvoient des String modifient-elles l’objet sur lequel on les appelle, 
//ou bien travaillent-elles sur des copies ? -> des copies 


class test{
    public static void main(String [] args){
        String s;        
        s = new String("Hello World!");
        //String majs= s.toUpperCase();
        //String mins= s.toLowerCase();
        String a = "bon";
        String b= "jour";
        System.out.println(s);  
        System.out.println(s.toLowerCase());
        System.out.println(s.toUpperCase());                
        System.out.println(s.startsWith("Hello"));
        System.out.println(s.substring(0,4)); //(0,n) stops at n-1
        System.out.println(s.length());
        System.out.println(a.concat(b) + " vs "+ a);
        //System.out.println();
    }
}