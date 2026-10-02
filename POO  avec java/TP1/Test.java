// Classe qui permet de vérifier le code produit dans le TP.
class Tests {
    // Point d'entrée qui permet de lancer tous les tests.
    // Au début du TP, certaines lignes ne compileront pas (par exemple les lignes relatives
    // à la classe Segment tant que vous n'avez pas introduit cette classe). N'hésitez pas
    // à les commenter.
    // L'exécution des tests se base sur une méthode statique verifie qui est donnée à la suite de la méthode main.
    public static void main(String[] args) {
        // Tests relatifs à la classe Couleur
        Couleur c = new Couleur(-12, 258, 13);
        verifie("composante r négative", c.getR() == 0);
        verifie("composante g supérieure à 255", c.getG() == 255);
        verifie("composante b normale", c.getB() == 13);

        Couleur n = Couleur.noir();
        verifie("couleur noire", n.getR() == 0 && n.getG() == 0 && n.getB() == 0);

        Couleur w = Couleur.blanc();
        verifie("couleur blanche", w.getR() == 255 && w.getG() == 255 && w.getB() == 255);

        Couleur b = Couleur.bleu();
        verifie("couleur bleue", b.getR() == 0 && b.getG() == 0 && b.getB() == 255);

        Couleur r = Couleur.rouge();
        verifie("couleur rouge", r.getR() == 255 && r.getG() == 0 && r.getB() == 0);

        Couleur v = Couleur.vert();
        verifie("couleur verte", v.getG() == 255 && v.getR() == 0 && v.getB() == 0);

        // Tests relatifs à la classe Axe
        Axe x = new Axe("Axe x", -5);
        Axe y = new Axe("Axe y", 10);
        verifie("titre axe en majuscules", x.getTitre().equals("AXE X"));
        verifie("taille axe négative", x.getTaille() == 0);
        verifie("taille axe normale", y.getTaille() == 10);
        verifie("description axe", y.description().equals("Axe taille : 10 , titre : AXE Y"));

        // Tests relatifs à la classe Point
        Point p1 = new Point("p1", Couleur.noir(), -10, -3);
        Point p2 = new Point("p2", Couleur.blanc(), 0, 5);
        verifie("coordonnée point x négative", p1.getX() == 0);
        verifie("coordonnée point y négative", p1.getY() == 0);
        verifie("coordonnée point x normale", p2.getX() == 0);
        verifie("coordonnée point y normale", p2.getY() == 5);
        verifie("description point", p2.description().equals("Point (0 ,5) , couleur : (255 ,255 ,255) , titre : p2"));

        // Tests relatifs à la classe Segment
        Segment d1 = new Segment("d1", Couleur.blanc(), p1, p2);
        verifie("longueur segment", d1.getLongueur() == 5.0);
        verifie("description segment", d1.description().equals("Segment (0 ,0) -> (0 ,5) , couleur : (255 ,255 ,255) , titre : d1"));

        // Tests relatifs à la classe EnsembleElementRepere
        EnsembleElementRepere e = new EnsembleElementRepere();
        verifie("ensemble vide", e.getTailleCourante() == 0);

        e.ajouterElement(p1);
        verifie("taille après ajout du point", e.getTailleCourante() == 1);
        verifie("récupération du point", e.recuperer(0) == p1);

        e.ajouterElement(d1);
        verifie("taille après ajout du segment", e.getTailleCourante() == 2);
        verifie("récupération du segment", e.recuperer(1) == d1);

        for (int i = 0; i < 1000; i++) {
            e.ajouterElement(new Point());
        }
        verifie("taille après ajout de 1000 points", e.getTailleCourante() == 1002);
        verifie("récupération du dernier élément après ajout de 1000 points", e.recuperer(e.getTailleCourante() - 1) instanceof Point);
    }

    public static void verifie(String message, boolean condition) {
        if (condition) {
            System.out.println("\u001B[32m\u001B[1m[ OK ]\u001B[0m " + message + "\u001B[0m");
        } else {
            System.out.println("\u001B[31m\u001B[1m[ KO ] " + message + "\u001B[0m");
        }
    }
}
