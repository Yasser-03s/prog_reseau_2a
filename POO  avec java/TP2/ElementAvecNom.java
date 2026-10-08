public class ElementAvecNom{
    private String titre;
    public ElementAvecNom(String titre){
        this.titre= titre;
    }
    public String getTitre(){
        return this.titre;
    }

    public String description(){
        return("titre : "+ this.titre);
    }
}