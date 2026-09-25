public class ElementRepere{
    @Override
    public String toString(){
        //System.out.println("Je suis un ElementRepere.");
        return "Je suis un ElementRepere.";
    }
    public static void main(String[] argv){
        Point p= new Point(1,2);
        System.out.println(p.toString());
        
    }
}

class Point extends ElementRepere{

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

    @Override
    public String toString(){
        //System.out.println("Je suis un ElementRepere. Je suis aussi un point.");
        return "Je suis un ElementRepere. Je suis aussi un point.";
    }
}






