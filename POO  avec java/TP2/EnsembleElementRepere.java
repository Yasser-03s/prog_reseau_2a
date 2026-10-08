import java.util.ArrayList;
public class EnsembleElementRepere{
    private int tailleCourante;
    private int tailleMaximale;
    private ArrayList<ElementRepere> elements;
    public void ajouterElement(ElementRepere e){
        this.elements.add(e);
        this.tailleCourante= this.elements.size();
    }

    public ElementRepere recuperer(int i){
        return this.elements.get(i);
    }
    public EnsembleElementRepere(){
        this.tailleCourante= 0;
        this.tailleMaximale= 2000;
        elements = new ArrayList<ElementRepere>();
    }

    public int getTailleCourante(){
        return this.elements.size();
    }
}