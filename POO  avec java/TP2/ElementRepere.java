public class ElementRepere extends ElementAvecNom{
    private String description;
    private Couleur couleur;
    public ElementRepere(String titre, Couleur couleur){
        super(titre);
        this.couleur= couleur;
    }

    @Override
    public String description(){
        return "couleur : ("+Integer.toString(this.couleur.getR())+" ,"+Integer.toString(this.couleur.getG())+" ,"+Integer.toString(this.couleur.getB())+") , "+ super.description(); 
    }   
}