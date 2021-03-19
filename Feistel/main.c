#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "fonction_festel.h"

void question1(){

    char ch;
    printf("Tapez le caractere : ");
    scanf("%c",&ch);

    viderBuffer();

    int enc[5]={0};
    encrypt_binaire(ch,enc);

    printf(" encrypt -> ");
    for(int j=0;j<5;j++)
    {
        printf("%d",enc[j]);
    }

    int decr = decrypt_binaire(enc);
    printf("\n decrypt -> %c",decr);
}

void question2(){

    int cle[10]={1,0,0,1,0,1,0,0,1,0};
    char lettrePourCodage[2], Resultat[2];

    char w1;
    printf("\n\nTapez le caractere : ");
    scanf("%c",&w1);

    viderBuffer();

    char w2;
    printf("\nTapez le caractere : ");
    scanf("%c",&w2);

    lettrePourCodage[0]=w1;
    lettrePourCodage[1]=w2;

    function(lettrePourCodage,cle,Resultat);
    printf("\n    %c %c\n -> %c %c",lettrePourCodage[0], lettrePourCodage[1], Resultat[0],Resultat[1]);


}

void question345(){
    char bloc[4];
    char mdp[4]={'K','X','C','X'};
    int cle[10]={1,0,0,1,0,1,0,0,1,0};
    int choice;


    printf("Insérez les 4 caracteres :\n1. ");
    scanf("%c",&bloc[0]);
    viderBuffer();

    printf("2. ");
    scanf("%c",&bloc[1]);
    viderBuffer();

    printf("3. ");
    scanf("%c",&bloc[2]);
    viderBuffer();

    printf("4. ");
    scanf("%c",&bloc[3]);
    viderBuffer();


    printf("\n 1. Chiffrement\n 2. Dechiffrement\n 1 ou 2 : ");
    scanf("%d",&choice);
    viderBuffer();

    while(choice!=1 && choice !=2)
    {
        printf("\n Erreur\n 1. Chiffrement\n 2. Dechiffrement\n 1 ou 2: ");
        scanf("%d",&choice);
        viderBuffer();
    }
    if(choice==1){
        encrypt_feistel(bloc,mdp);
    }
    else
    {
        decrypt_feistel(bloc,mdp);
    }
}

int main()
{
    question345();

    printf("\n\n\n\n\n");
}

