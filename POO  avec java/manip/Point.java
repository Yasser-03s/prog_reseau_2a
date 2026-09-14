public class Point{

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
    public static void main(String[] args){
        Point p= new Point(2,1);
        Point p2= new Point(3,1);
        System.out.println(p.distance(p2));
        p.afficherCoord();
    }

}