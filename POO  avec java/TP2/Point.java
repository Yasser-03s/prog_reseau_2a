public class Point extends ElementRepere{
    private int x;
    private int y;
    public Point(String titre, Couleur c, int x, int y){
        super(titre, c);
        this.x=Math.max(0,x);
        this.y=Math.max(0,y);
    }
    public Point(){
        // point (0,0) par defaut
        super("Point", new Couleur());
        this.x= 0;
        this.y= 0;
    }
    public int getX(){
        return this.x;
    }
    public int getY(){
        return this.y;
    }

    @Override
    public String description(){
        return "Point ("+Integer.toString(this.x)+" ,"+Integer.toString(this.y)+") , "+ super.description(); 
    }

}