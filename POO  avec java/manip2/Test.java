//ceci est un fichier test de toString()


class Point{

    private int x;
    private int y;


    public Point(int x, int y){
        this.x=x;
        this.y=y;
    }

    public int getX(){
        return this.x;
    }
    public int getY(){
        return this.y;
    }
    public void setX(int a){
        this.x = a;
    }
    public void setY(int b){
        this.y = b;
    }
    public void afficherCoord(){
        System.out.println("votre point est de coordonnées x= "+ x + " et y=" + y);
    }
    public double distance(Point p2){
        return Math.sqrt(Math.pow(this.x - p2.getX() ,2) + Math.pow(this.y - p2.getY() ,2));
    }


}


public class Test{
    public static void main(String[] argv){
        Object object = new Object();
        String object2 = new String();
        System.out.println("le resultat de vide est "+ object.toString());
        //renvoi l'adresse logique A.K.A le hashcode
        System.out.println("le resultat de String est "+ object2.toString());
        Point p= new Point(2,1);
        System.out.println("le resultat de Point est "+ p.toString());
    }

}

//resultat le code de la methode toString est le meme pour les classes Object et Point mais il est redefini (override) pour la classe String