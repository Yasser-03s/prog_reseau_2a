public class Axe extends ElementAvecNom{
    private int taille;
    public Axe(String titre, int taille){
        super(titre.toUpperCase());
        this.taille=taille;
    }
    public int getTaille(){
        return this.taille;
    }
}