public class Axe extends ElementAvecNom{
    private int taille;

    public int getTaille(){
        return this.taille;
    }
    public Axe(String titre, int taille){
        super(titre.toUpperCase());
        this.taille= Math.max(0,taille); //donne 0 si taille negatif
    }
    public Axe(){
        //titre "AXE" par defaut?
        super("AXE");
        this.taille= 1;
    }

    @Override
    public String description(){
        return "Axe taille : "+Integer.toString(this.taille)+" , "+ super.description(); 
    }

}