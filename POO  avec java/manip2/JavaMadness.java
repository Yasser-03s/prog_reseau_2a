class JavaMadness {
    public static void main(String[] args) {
        System.out.println("Debut du point d’entree.");
        System.out.println("Declaration d’un objet de type Point.");
        Point p;
        System.out.println("Access a une propriete statique");
        VerboseString s = Point.sX;
        System.out.println("Creation d’un objet de type Point.");
        p = new Point(); // seule création d’objet du point d’entree.
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
