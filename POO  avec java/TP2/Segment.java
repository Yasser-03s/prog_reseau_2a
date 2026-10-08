public class Segment extends ElementRepere{
    
    private Point origine;
    private Point destination;

    public Segment(String titre, Couleur c, Point origine, Point destination){
        super(titre,c);
        this.origine= origine;
        this.destination= destination;
    }
    public Segment(){
        super("SEGMENT",new Couleur());
        this.origine= new Point();
        this.destination= new Point();
    }
    public double getLongueur(){
        int X1= this.origine.getX();
        int X2= this.destination.getX();
        int Y1= this.origine.getY();
        int Y2= this.destination.getY();
        return Math.sqrt((X1-X2)*(X1-X2) + (Y1-Y2)*(Y1-Y2));
    }

    @Override
    public String description(){
        String X1= Integer.toString(this.origine.getX());
        String X2= Integer.toString(this.destination.getX());
        String Y1= Integer.toString(this.origine.getY());
        String Y2= Integer.toString(this.destination.getY());
        return "Segment ("+X1+" ,"+Y1+") -> ("+X2+" ,"+Y2+") , "+ super.description(); 
    }

}
