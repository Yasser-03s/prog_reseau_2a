import java.util.Random;

public class Couleur{
    private int r;
    private int g;
    private int b;

    public static Couleur auHasard(){
        Random rand= new Random();
        int r= rand.nextInt(256);
        int g= rand.nextInt(256);
        int b= rand.nextInt(256);
        return new Couleur(r,g,b);
    }
    public static Couleur rouge(){
        return new Couleur(255,0,0);
    }
    public static Couleur vert(){
        return new Couleur(0,255,0);
    }
    public static Couleur bleu(){
        return new Couleur(0,0,255);
    }
    public static Couleur noir(){
        return new Couleur(0,0,0);
    }
    public static Couleur blanc(){
        return new Couleur(255,255,255);
    }
    public Couleur(int r, int g, int b){   
        // Math.max(0,x) donne 0 si x negatif
        // Math.min(255,x) donne 255 so x>255
        //on combine et cela donne:     
        this.r=Math.max(0,Math.min(255,r));
        this.g=Math.max(0,Math.min(255,g));
        this.b=Math.max(0,Math.min(255,b));
    }
    public int getR(){
        return this.r;
    }
    public int getG(){
        return this.g;
    }
    public int getB(){
        return this.b;
    }
//    public static void main(String[] args) {}
}