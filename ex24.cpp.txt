#include <iostream>
using namespace std;

class Client {
private:
    string nom;
    string CIN;
    int idClient;
    
public:
    Client(string n, string c, int id) {
        nom = n;
        CIN = c;
        idClient = id;
    }
    
    void afficher() {
        cout << "Client: " << nom << ", CIN: " << CIN << ", ID: " << idClient << endl;
    }
    
    friend class AgentBancaire;
    friend class Banque;
};

class CompteBancaire {
private:
    int numeroCompte;
    float solde;
    int codeSecret;
    Client *client;
    
public:
    CompteBancaire(int num, float s, int code, Client *c) {
        numeroCompte = num;
        solde = s;
        codeSecret = code;
        client = c;
    }
    
    void deposer(float montant) {
        solde = solde + montant;
        cout << "Depot de " << montant << " DH effectue" << endl;
    }
    
    void retirer(float montant) {
        if (solde >= montant) {
            solde = solde - montant;
            cout << "Retrait de " << montant << " DH effectue" << endl;
        }
        else {
            cout << "Solde insuffisant" << endl;
        }
    }
    
    void afficher() {
        cout << "Compte " << numeroCompte << " - Solde: " << solde << " DH" << endl;
        client->afficher();
    }
    
    friend class AgentBancaire;
    friend class Banque;
};

class AgentBancaire {
private:
    string nom;
    int idAgent;
    
public:
    AgentBancaire(string n, int id) {
        nom = n;
        idAgent = id;
    }
    
    void consulterCodeSecret(CompteBancaire &c) {
        cout << "Agent " << nom << " consulte le code secret du compte " << c.numeroCompte << endl;
        cout << "Code secret: " << c.codeSecret << endl;
    }
    
    void transferer(CompteBancaire &source, CompteBancaire &dest, float montant) {
        if (source.solde >= montant) {
            source.solde = source.solde - montant;
            dest.solde = dest.solde + montant;
            cout << "Transfert de " << montant << " DH effectue" << endl;
        }
        else {
            cout << "Solde insuffisant pour le transfert" << endl;
        }
    }
};

class Banque {
private:
    string nomBanque;
    CompteBancaire* comptes[50];
    int nbComptes;
    
public:
    Banque(string nom) {
        nomBanque = nom;
        nbComptes = 0;
    }
    
    void ajouterCompte(CompteBancaire *c) {
        if (nbComptes < 50) {
            comptes[nbComptes] = c;
            nbComptes++;
        }
    }
    
    void afficherTousLesComptes() {
        cout << "\n=== Liste des comptes - " << nomBanque << " ===" << endl;
        for (int i = 0; i < nbComptes; i++) {
            comptes[i]->afficher();
            cout << endl;
        }
    }
    
    void rapportAudit() {
        cout << "\n=== RAPPORT D'AUDIT - " << nomBanque << " ===" << endl;
        for (int i = 0; i < nbComptes; i++) {
            cout << "Compte numero: " << comptes[i]->numeroCompte << endl;
            cout << "Titulaire: " << comptes[i]->client->nom << endl;
            cout << "Solde: " << comptes[i]->solde << " DH" << endl;
            cout << "Code secret: " << comptes[i]->codeSecret << endl;
            cout << "---" << endl;
        }
    }
};

int main() {
    Client c1("Ahmed Alami", "AB12345", 1);
    Client c2("Fatima Bennani", "CD67890", 2);
    Client c3("Youssef Idrissi", "EF11223", 3);
    
    CompteBancaire compte1(1001, 5000, 1234, &c1);
    CompteBancaire compte2(1002, 3000, 5678, &c2);
    CompteBancaire compte3(1003, 8000, 9012, &c3);
    
    Banque banque("Bank Al Maghrib");
    banque.ajouterCompte(&compte1);
    banque.ajouterCompte(&compte2);
    banque.ajouterCompte(&compte3);
    
    cout << "=== Operations bancaires ===" << endl;
    compte1.deposer(1000);
    compte2.retirer(500);
    
    banque.afficherTousLesComptes();
    
    AgentBancaire agent("Mohamed Tazi", 100);
    
    cout << "\n=== Operations agent ===" << endl;
    agent.consulterCodeSecret(compte1);
    agent.transferer(compte1, compte2, 2000);
    
    banque.afficherTousLesComptes();
    
    banque.rapportAudit();
    
    return 0;
}