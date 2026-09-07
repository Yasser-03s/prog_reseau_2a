//ceci est un exemple de declaration de constructeur 
//le nom du fichier doit etre = au nom de la class pour executer
//le nom du constructeur doit etre le meme que celui de la classe
//chaque classe doit avoir au moins un constructeur


public class Date{
    private int yes, month, day;
    public Date(int y, int m, int d){
        if (verify(y, m, d)){
            year = y;
            month = m;
            day = d;
        }
    }
    private boulean verify(int y, int m, int d){
        //...
    }
}