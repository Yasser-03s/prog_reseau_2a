public class ElementRepere{
    @Override
    public String toString(){
        System.out.println("Je suis un ElementRepere.");
    }
    public static void main(String[] argv){
        Point p= new Point(1,2);
    }
}

class Point extends ElementRepere{
    @Override
    public String toString(){
        System.out.println("Je suis un ElementRepere. Je suis aussi un point.");
    }
}






