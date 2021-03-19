#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "fonction_rsa.h"


int main()
{
    srand(time(NULL));

    printf("Programme C:\n\n");

    int ClePublicA_e;
    int ClePriveeA_d;
    int ClePublicB_e;
    int ClePriveeB_d;

//Formation de P et Q pour A:
    int Pa=CreationPetQ();
    int Qa=CreationPetQ();
    printf("Pa=%d\n",Pa);
    printf("Qa=%d\n",Qa);

//Formation de P et Q pour B:
    int Pb=CreationPetQ();
    int Qb=CreationPetQ();
    printf("Pb=%d\n",Pb);
    printf("Qb=%d\n\n",Qb);

//Calcul de N et Phi pour A:
    int Na=Pa*Qa;
    int FIa=(Pa-1)*(Qa-1);
    printf("Na=%d\n",Na);
    printf("FIa=%d\n",FIa);

//Calcul de N et Phi pour B:
    int Nb=Pb*Qb;
    int FIb=(Pb-1)*(Qb-1);
    printf("Nb=%d\n",Nb);
    printf("FIb=%d\n\n",FIb);

//Choix de la clé public pour A:
    ClePublicA_e=Choix_e(FIa);
    printf("clé public de A=%d\n",ClePublicA_e);

//Choix de la clé public pour B:
    ClePublicB_e=Choix_e(FIb);
    printf("clé public de B=%d\n\n",ClePublicB_e);

//Formation de la cle privee pour A:
    ClePriveeA_d=algoEuclide(ClePublicA_e,FIa);
    printf("clé privee de A=%d\n",ClePriveeA_d);

//Formation de la cle privee pour B:
    ClePriveeB_d=algoEuclide(ClePublicB_e,FIb);
    printf("clé privee de B=%d\n\n",ClePriveeB_d);



    

//Formation du message AB?! par Alice:
    int Message[4]={'A','B','?','!'};
    MainAfficheEnvoieAvantCodage(Message);

    printf("\n\nQuestion 1\n");
//Codage de chaque caracteres:
    int Code[4];

    for (int i = 0; i < 4; ++i) {
        Code [i]=ExponentiationMod(Message[i],ClePublicB_e,Nb);
    }
    MainAfficheEnvoie(Code);

//Bob decripte le message :

    int MessageDecode[4];

    for (int i = 0; i < 4; ++i) {
        MessageDecode[i]=ExponentiationMod(Code[i],ClePriveeB_d,Nb);
    }
    MainAfficheRecu(MessageDecode);

    printf("\n\nQuestion 2\n");
//Bob repond a Alice

    int Reponse[4]={'A','B','O','K'};
    MainAfficheEnvoieAvantCodage(Reponse);

    int ReponseEnvoyee[4];

    for (int i = 0; i < 4; ++i) {
        ReponseEnvoyee[i]=ExponentiationMod(Reponse[i],ClePublicA_e,Na);
    }
    MainAfficheEnvoie(ReponseEnvoyee);

//Alice va donc decoder le message recue de Bob:

    int MessageReponse[4];

    for (int i = 0; i < 4; ++i) {
        MessageReponse[i]=ExponentiationMod(ReponseEnvoyee[i],ClePriveeA_d,Na);
    }
    MainAfficheRecu(MessageReponse);


    printf("\n\n Question 3\n");
//Alice genere un nombre aleatoire equivalent a 4 caractere:

    int NombreAleatoire[4];

    for (int i = 0; i < 4; ++i) {
        NombreAleatoire[i]=rand()%(90-65+1) + 65;
    }
    MainAfficheEnvoieAvantCodage(NombreAleatoire);

//codage avec cle public de b:
    for (int i = 0; i < 4; ++i) {
        Code [i]=ExponentiationMod(NombreAleatoire[i],ClePublicB_e,Nb);
    }
    MainAfficheEnvoie(Code);

//Decryptage du code:
    for (int i = 0; i < 4; ++i) {
        MessageDecode[i]=ExponentiationMod(Code[i],ClePriveeB_d,Nb);
    }
    MainAfficheRecu(MessageDecode);

//cryptage du resultat obtenu:
    for (int i = 0; i < 4; ++i) {
        ReponseEnvoyee[i]=ExponentiationMod(MessageDecode[i],ClePublicA_e,Na);
    }
    MainAfficheEnvoie(ReponseEnvoyee);

//Decryptage final par Bob :
    for (int i = 0; i < 4; ++i) {
        MessageReponse[i]=ExponentiationMod(ReponseEnvoyee[i],ClePriveeA_d,Na);
    }
    MainAfficheRecu(MessageReponse);
    printf("\n\n\n\n\n\n");
}



