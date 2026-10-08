public class MainExceptions {

    // La méthode de validation officielle fournie à la page 6 de votre sujet
    public static void verifie(String message, boolean condition) {
        if (condition) {
            System.out.println("\u001B[32m\u001B[1m[OK]\u001B[0m " + message);
        } else {
            System.out.println("\u001B[31m\u001B[1m[KO]\u001B[0m " + message);
        }
    }

    public static void main(String[] args) {
        System.out.println("=== DÉBUT DU TEST DES EXCEPTIONS (TP 2) ===");

        // -------------------------------------------------------------------
        // TEST 1 : Exception sur la classe Couleur (Valeurs hors de)
        // -------------------------------------------------------------------
        try {
            // Tentative de création d'une couleur avec une composante invalide
            // (ex: rouge négatif ou supérieur à 255)
            // TODO: Instancier la couleur fautive ici
            
            // Si le programme passe à la ligne suivante, c'est que l'exception n'a PAS été levée
            verifie("Exception Couleur : Détection valeur hors plage [0,255]", false);
        } catch (Exception e) { 
            // L'exception a été interceptée avec succès !
            // Optionnel : Vous pouvez vérifier si le message d'erreur contient un mot clé précis
            verifie("Exception Couleur : Détection valeur hors plage [0,255]", true);
        }

        // -------------------------------------------------------------------
        // TEST 2 : Exception sur la classe Axe (Taille négative)
        // -------------------------------------------------------------------
        try {
            // Tentative de création d'un Axe avec une taille négative (ex: -5)
            // TODO: Instancier l'axe fautif ici
            
            verifie("Exception Axe : Détection taille négative", false);
        } catch (Exception e) {
            verifie("Exception Axe : Détection taille négative", true);
        }

        // -------------------------------------------------------------------
        // TEST 3 : Exception sur la classe Point (Coordonnées négatives)
        // -------------------------------------------------------------------
        try {
            // Tentative de création d'un Point avec x ou y négatif (ex: -10)
            // TODO: Instancier le point fautif ici
            
            verifie("Exception Point : Détection coordonnées négatives", false);
        } catch (Exception e) {
            verifie("Exception Point : Détection coordonnées négatives", true);
        }

        // -------------------------------------------------------------------
        // TEST 4 : Exception sur EnsembleElementRepere (Index hors limites)
        // -------------------------------------------------------------------
        try {
            // Instanciation d'un ensemble vide et tentative immédiate de récupération
            // d'un élément à un index inexistant (ex: recuperer(0) ou recuperer(99))
            // TODO: Effectuer la récupération fautive ici
            
            verifie("Exception Ensemble : Récupération index invalide", false);
        } catch (Exception e) {
            verifie("Exception Ensemble : Récupération index invalide", true);
        }

        System.out.println("=== FIN DES TESTS ===");
    }
}
