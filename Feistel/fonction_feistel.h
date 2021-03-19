#ifndef FONCTION_FESTEL_H
#define FONCTION_FESTEL_H
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void addition10(int* msg, int* key){

    for(int j=0;j<10;j++)
    {
        if(msg[j]!=key[j])
        {
            msg[j]=1;
        }
        else
        {
            msg[j]=0;
        }
    }
}

void affiche5(int* tab)
{ // Affiche un caractere encrypté en binaire
    for(int j=0;j<5;j++)
    {
        printf("%d",tab[j]);
    }
}

void affiche10(int* tab)
{ // Affiche deux caracteres encryptés en binaire
    for(int j=0;j<10;j++)
    {
        printf("%d",tab[j]);
    }
}

void addition5(int* rec, int* ajout)
{ // Operation XOR de deux nombres en binaire
    for(int j=0;j<5;j++)
    {
        if(rec[j]==ajout[j])
        {
            rec[j]=0;
        }
        else
        {
            rec[j]=1;
        }
    }
}

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

void decalage(int* msg){

    int sw = msg[0];

    for(int i=0;i<9;i++)
    {
        msg[i]=msg[i+1];
    }

    msg[9]=sw;
}

void encrypt_binaire(char a, int* enc){

    int k, i=0, b;

    if (a>64 && a<91)
    {
        k=a-65;
    }
    else
    {
        switch (a) {
        case ' ':
            k=26;
            break;
        case '.':
            k=27;
            break;
        case ',':
            k=28;
            break;
        case '\'':
            k=29;
            break;
        case '!':
            k=30;
            break;
        case '?':
            k=31;
            break;
        default:
            break;
        }
    }

    while (k!=0 && i<5)
    {
        b=k%2;
        k=k/2;
        enc[4-i]=b;
        i=i+1;
    }
}

int decrypt_binaire(int* tab)
{
    int x=0;
    for(int i=0;i<5;i++)
    {
        x=x+pow(2,4-i)*tab[i];
    }

    if (x>=0 && x<26)
    {
        return x+65;
    }
    else
    {
        switch (x) {
        case 26:
            return ' ';
            break;
        case 27:
            return '.';
            break;
        case 28:
            return ',';
            break;
        case 29:
            return '\'';
            break;
        case 30:
            return '!';
            break;
        case 31:
            return '?';
            break;
        default:
            break;
        }
    }
}

void concat(int* t1, int* t2, int* msg)
{
    for(int j=0;j<5;j++)
    {
        msg[j]=t1[j];
        msg[j+5]=t2[j];
    }
}

void function(char* lettrePourCodage, int* key, char* codeRetour){

    printf("\n------------ function -----------\n ");

    int m1e[5]={0};
    encrypt_binaire(lettrePourCodage[0],m1e);
    int m2e[5]={0};
    encrypt_binaire(lettrePourCodage[1],m2e);

    int msg[10]={0};
    concat(m1e,m2e,msg);

    printf("\n msg > ");
    affiche10(msg);

    decalage(msg);

    printf("\n dcl > ");
    affiche10(msg);

    addition10(msg, key);

    printf("\n + k > ");
    affiche10(key);

    printf("\n   = > ");
    affiche10(msg);

    int l1e[5], l2e[5];
    for(int j=0;j<5;j++)
    {
        l1e[j]=msg[j];
        l2e[j]=msg[j+5];
    }

    codeRetour[0]=decrypt_binaire(l1e);
    codeRetour[1]=decrypt_binaire(l2e);

    printf(" < codeRetour < {%c,%c}",codeRetour[0],codeRetour[1]);

    printf("\n\n---------------------------------\n");
}

void k_indice(int i, char* mdp, char* K, int* bK){
    K[0]=mdp[i-1];
    K[1]=mdp[i%4];
    int t1[5]={0},t2[5]={0};
    encrypt_binaire(K[0],t1);
    encrypt_binaire(K[1],t2);
    concat(t1,t2,bK);
}

void encrypt_feistel(char* bloc, char* mdp){
    char K[2]={0}, G[2]={0}, D[2]={0}, sw[2]={0}, retourFunc[2]={0};
    int bK[10]={0},bD1[5]={0},bD2[5]={0};
    int rf1[5]={0},rf2[5]={0};

    for(int j=0;j<2;j++)
    {
        G[j]=bloc[j];
        D[j]=bloc[j+2];
    }

    printf("\n\n\nG0 > {%c,%c}\nD0 > {%c,%c}\n",G[0],G[1],D[0],D[1]);

    printf("\n\n\n\n--------------------------------------------------------\n");

    for(int i=1;i<=4;i++)
    {
        printf("                        i = %d\n",i);

        //on met Ki+1 dans K (char) et dans bK (version binaire)
        k_indice(i,mdp,K,bK);

        printf("\n K > {%c,%c} > ",K[0],K[1]);
        affiche10(bK);

        // reinitialisation
        for(int j=0;j<5;j++){
            bD1[j]=0;
            bD2[j]=0;
        }

        //on recupere les versions binaires de Gi
        encrypt_binaire(G[0],bD1);
        encrypt_binaire(G[1],bD2);

        for(int j=0;j<2;j++)
        {
            sw[j]=D[j];
            D[j]=G[j];
            G[j]=sw[j]; // Gi+1=Di
        }

        printf("\n\n G > {%c,%c}\n D > {%c,%c}\n",G[0],G[1],D[0],D[1]);

        // reinitialisation
        retourFunc[0]=0;
        retourFunc[1]=0;

        // retourFunc prend la valeur de function(Gi+1,K) (ici, sw=Gi+1)
        function(sw,bK,retourFunc); //retourFunc prend la valeur de function(Di,Ki+1) (ici, sw=Di)

        // reinitialisation
        for(int j=0;j<5;j++)
        {
            rf1[j]=0;
            rf2[j]=0;
        }

        // rf1 et rf1 sont les versions binaires du retourFunc
        encrypt_binaire(retourFunc[0],rf1);
        encrypt_binaire(retourFunc[1],rf2);

        printf("\n retourFunc > {%c,%c} > ",retourFunc[0],retourFunc[1]);
        affiche5(rf1);
        affiche5(rf2);
        printf("\n\n  G%d > ",i-1);
        affiche5(bD1);
        affiche5(bD2);

        // somme XOR pour obtenir Gi
        addition5(bD1,rf1);
        addition5(bD2,rf2);

        printf("\n + f > ");
        affiche5(rf1);
        affiche5(rf2);
        printf("\n   = > ");
        affiche5(bD1);
        affiche5(bD2);

        //D prend les caracteres correspondants
        D[0]=decrypt_binaire(bD1);
        D[1]=decrypt_binaire(bD2);

        printf(" < D < {%c,%c}",D[0],D[1]);

        printf("\n\n\n G%d > {%c,%c}\n D%d > {%c,%c}\n",i,G[0],G[1],i,D[0],D[1]);

        printf("\n--------------------------------------------------------\n");

    }
    printf("\n\n\n                %c%c%c%c  >>>  %c%c%c%c",bloc[0],bloc[1],bloc[2],bloc[3],G[0],G[1],D[0],D[1]);
    printf("\n                1234       1234");
}

void decrypt_feistel(char* bloc, char* mdp){
    char K[2]={0}, G[2]={0}, D[2]={0}, sw[2]={0}, retourFunc[2]={0};
    int bK[10]={0},bD1[5]={0},bD2[5]={0};
    int rf1[5]={0},rf2[5]={0};

    for(int j=0;j<2;j++)
    {
        G[j]=bloc[j];
        D[j]=bloc[j+2];
    }

    printf("\n\n\nG4 > {%c,%c}\nD4 > {%c,%c}\n",G[0],G[1],D[0],D[1]);

    printf("\n\n\n\n--------------------------------------------------------\n");

    for(int i=1;i<=4;i++)
    {
        printf("                        i = %d\n",i);

        //on recupere les bonnes valeurs de K (char) et de bK (version binaire)
        k_indice(5-i,mdp,K,bK);

        printf("\n K > {%c,%c} > ",K[0],K[1]);
        affiche10(bK);

        // reinitialisation
        for(int j=0;j<5;j++){
            bD1[j]=0;
            bD2[j]=0;
        }

        // on recupere les versions binaires de Di+1
        encrypt_binaire(D[0],bD1);
        encrypt_binaire(D[1],bD2);

        for(int j=0;j<2;j++)
        {
            sw[j]=G[j];
            G[j]=D[j];
            D[j]=sw[j]; // Di=Gi+1
        }

        printf("\n\n G > {%c,%c}\n D > {%c,%c}\n",G[0],G[1],D[0],D[1],sw[0],sw[1]);

        // reinitialisation
        retourFunc[0]=0;
        retourFunc[1]=0;

        // retourFunc prend la valeur de function(Gi+1,K) (ici, sw=Gi+1)
        function(sw,bK,retourFunc);

        // reinitialisation
        for(int j=0;j<5;j++)
        {
            rf1[j]=0;
            rf2[j]=0;
        }

        // rf1 et rf1 sont les versions binaires du retourFunc
        encrypt_binaire(retourFunc[0],rf1);
        encrypt_binaire(retourFunc[1],rf2);

        printf("\n retourFunc > {%c,%c} > ",retourFunc[0],retourFunc[1]);
        affiche5(rf1);
        affiche5(rf2);
        printf("\n\nDi+%d > ",5-i);
        affiche5(bD1);
        affiche5(bD2);

        // somme XOR pour obtenir Gi
        addition5(bD1,rf1);
        addition5(bD2,rf2);

        printf("\n + f > ");
        affiche5(rf1);
        affiche5(rf2);
        printf("\n   = > ");
        affiche5(bD1);
        affiche5(bD2);

        //G prend les caracteres correspondants
        G[0]=decrypt_binaire(bD1);
        G[1]=decrypt_binaire(bD2);

        printf(" < D < {%c,%c}",D[0],D[1]);

        printf("\n\n\nG%d > {%c,%c}\nD%d > {%c,%c}\n",5-i-1,G[0],G[1],5-i-1,D[0],D[1]);

        printf("\n--------------------------------------------------------\n");

    }
    printf("\n\n\n                %c%c%c%c  >>>  %c%c%c%c",bloc[0],bloc[1],bloc[2],bloc[3],G[0],G[1],D[0],D[1]);
    printf("\n                1234       1234");
}

#endif // FONCTION_FESTEL_H
