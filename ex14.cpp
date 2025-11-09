#include <iostream>
using namespace std;

class Telechargeable {
public:
    void telecharger() {
        cout << "Telechargement en cours..." << endl;
    }
    
    void afficherMessage() {
        cout << "Ressource telechargeable" << endl;
    }
};

class Ressource {
public:
    int id;
    string titre;
    string auteur;
    int annee;
    
    Ressource(int i, string t, string a, int an) {
        id = i;
        titre = t;
        auteur = a;
        annee = an;
    }
    
    void afficherInfos() {
        cout << "ID: " << id << ", Titre: " << titre << ", Auteur: " << auteur << ", Annee: " << annee << endl;
    }
    
    void telecharger() {
        cout << "Telechargement de la ressource..." << endl;
    }
    
    bool operator==(Ressource &r) {
        return id == r.id;
    }
};

class Livre : public Ressource, public Telechargeable {
public:
    int nbPages;
    
    Livre(int i, string t, string a, int an, int nb) : Ressource(i, t, a, an) {
        nbPages = nb;
    }
    
    void afficherInfos() {
        cout << "Livre - ";
        Ressource::afficherInfos();
        cout << "Nombre de pages: " << nbPages << endl;
    }
};

class Magazine : public Ressource, public Telechargeable {
public:
    int numero;
    
    Magazine(int i, string t, string a, int an, int n) : Ressource(i, t, a, an) {
        numero = n;
    }
    
    void afficherInfos() {
        cout << "Magazine - ";
        Ressource::afficherInfos();
        cout << "Numero: " << numero << endl;
    }
};

class Video : public Ressource, public Telechargeable {
public:
    int duree;
    
    Video(int i, string t, string a, int an, int d) : Ressource(i, t, a, an) {
        duree = d;
    }
    
    void afficherInfos() {
        cout << "Video - ";
        Ressource::afficherInfos();
        cout << "Duree: " << duree << " min" << endl;
    }
};

class Mediatheque {
public:
    Ressource* ressources[100];
    int nb;
    
    Mediatheque() {
        nb = 0;
    }
    
    void ajouter(Ressource *r) {
        if (nb < 100) {
            ressources[nb] = r;
            nb++;
            cout << "Ressource ajoutee" << endl;
        }
    }
    
    void afficher() {
        for (int i = 0; i < nb; i++) {
            ressources[i]->afficherInfos();
            cout << endl;
        }
    }
    
    void rechercher(string t) {
        cout << "Recherche par titre: " << t << endl;
        for (int i = 0; i < nb; i++) {
            if (ressources[i]->titre == t) {
                ressources[i]->afficherInfos();
            }
        }
    }
    
    void rechercher(int an) {
        cout << "Recherche par annee: " << an << endl;
        for (int i = 0; i < nb; i++) {
            if (ressources[i]->annee == an) {
                ressources[i]->afficherInfos();
            }
        }
    }
    
    void rechercher(string a, int an) {
        cout << "Recherche par auteur et annee" << endl;
        for (int i = 0; i < nb; i++) {
            if (ressources[i]->auteur == a && ressources[i]->annee == an) {
                ressources[i]->afficherInfos();
            }
        }
    }
};

int main() {
    Mediatheque m;
    
    Livre l1(1, "C++ pour debutants", "Dupont", 2020, 300);
    Magazine mag1(2, "Science et Vie", "Martin", 2023, 150);
    Video v1(3, "Tutoriel C++", "Dubois", 2022, 45);
    
    m.ajouter(&l1);
    m.ajouter(&mag1);
    m.ajouter(&v1);
    
    cout << "=== Affichage ===" << endl;
    m.afficher();
    
    cout << "\n=== Telecharger ===" << endl;
    l1.Ressource::telecharger();
    l1.Telechargeable::telecharger();
    
    cout << "\n=== Recherche ===" << endl;
    m.rechercher("C++ pour debutants");
    m.rechercher(2023);
    
    cout << "\n=== Comparaison ===" << endl;
    Livre l2(1, "Autre livre", "Autre", 2021, 200);
    if (l1 == l2) {
        cout << "Meme ID" << endl;
    }
    
    return 0;
}