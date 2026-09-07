class comp{   
    public static void main(String[] args){
        int i1 = 12;
        int i2 = 12;
        double d1 = 12.0;
        double d2 = 12.0;
        Integer obj1 = new Integer(12);
        Integer obj2 = new Integer(12);
        String str1 = new String("hello");
        String str2 = new String("hello");


        System.out.println(i1 == i2);
        System.out.println(d1 == d2);
        System.out.println("Pour integer ");
        System.out.println( obj1 == obj2 );
        System.out.println(obj1.equals(obj2));
        System.out.println("Pour string ");
        System.out.println(str1 == str2);
        System.out.println(str1.equals(str2));

    }
}


//conclusion: pour les types primitifs, avec "==" on compare directement leurs valeurs
//            pour objets "==" compare leurs adresse donc il faut faire "Obj1.equals(Obj2)" pour deferencer les objets et comparer leurs valeurs

//scenario bogue: on cherche un mot dans une chaine String en effectuant un parcours par sequences de cette chaine du meme length()
//que le mot alors on ne va pas atteindre une instance de la boucle où c'est vrai si on utilise "=="

