class JavaMadness {
    public static void main(String[] args) {
        System.out.println("Debut du point d’entree.");
        System.out.println("Declaration d’un objet de type Point.");
        Point p;// affiche rien
        System.out.println("Access a une propriete statique");
        //VerboseString s = Point.sX; //affiche "sTitle cree statiquement." du parent
        System.out.println("Creation d’un objet de type Point.");
        //p = new Point(); // seule création d’objet du point d’entree.
        //Etape 1 si on supprime VerboseString s = Point.sX;, le code affiche "sTitle cree statiquement." ici
        //Etape 2 n'affiche rien car on a aucune creation
        //affiche "x cree dynamiquement."
        // puis "Appel du constructeur de Point."
        
    }
}

class VerboseString {
    public VerboseString(String s) {
        System.out.println(s);
    }
}

class ElementAvecTitre {
    public static VerboseString sTitle = new VerboseString("sTitle cree statiquement.");
    public VerboseString title = new VerboseString("title cree dynamiquement.");
    public ElementAvecTitre() {
        System.out.println("Appel du constructeur de ElementAvecTitre.");
    }
}

class Point extends ElementAvecTitre {
    public static VerboseString sX = new VerboseString("sX cree statiquement.");
    public VerboseString x = new VerboseString("x cree dynamiquement.");
    public Point() {
        System.out.println("Appel du constructeur de Point.");
    }
}
