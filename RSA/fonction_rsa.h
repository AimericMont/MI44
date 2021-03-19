#ifndef FONCTION_RSA_H
#define FONCTION_RSA_H
#include <time.h>
#include <math.h>

int IsPrime(const int a)
{
    if (a<=1)
    {
        return 0;
    }
    if(a%2==0 && a>2)
    {
        return 0;
    }
    for (int i=3;i<a;i+=2) {
        if (a%i==0)
        {
            return 0;
        }
    }
    return 1;
}

int pgcd(int a, int b)
{
    while(b!=0)
    {
        int c=a%b;
        a=b;
        b=c;
    }
    return a;
}

// nombres premiers avec x et inférieurs à max
void premier(int x, int max)
{
    int nombre_premier = 1;
    for(int j = 2 ; j <= max ; j++)
    {
        nombre_premier = 1;
        for(int i = 2 ; i <= j ; i++)
        {
            if ((x % i) == 0 && (j % i) == 0 )
            {
                                nombre_premier = 0;
                break;
            }
        }
        if(nombre_premier==1)
        printf("%d  " ,j);
    }
}

int Choix_e(int Fi)
{
    int e=rand()%(Fi-2)+1;
    while (pgcd(e,Fi)!=1)
    {
           e=rand()%(Fi-2)+1;
    }
    return e;

}

int algoEuclide (int nb, int mod)
{
    int no=mod;
    int bo=nb;
    int to=0;
    int t=1;
    int q=no/bo;
    int r=no-q*bo;
    while(r>0)
    {
        int temp=to-q*t;
        if(temp>=0)
        {
            temp=temp%mod;
        }
        else
        {
            temp=mod-((-temp)%mod);
        }
        to=t;
        t=temp;
        no=bo;
        bo=r;
        q=no/bo;
        r=no-q*bo;
    }
        if (bo!=1)
        {
            printf("%d n'a pas d'inverse modulaire\n",nb);
            return 0;
        }
        else
        {
            printf("%d a comme inverse mod %d : %d \n",nb,mod,t);
            return t;
        }
}

int CreationPetQ()
{
    int temp=rand()%(100-2)+1;
    while(IsPrime(temp)==0||temp==1)
    {
        temp=rand()%(100-2)+1;
    }
    return temp;
}

void CodageBinaire(int exposant, int* tableau)
{
    int i=0;
    while(exposant!=0)
    {
        tableau[13-i]=exposant%2;
        exposant=(exposant)/2;
        i++;
    }
}


int ExponentiationMod(long Messagebis, int Cle, int modulo)
{
    int Binaire[14];

    for (int v = 0; v < 14; ++v) {
        Binaire[v]=0;
    }

    CodageBinaire(Cle,Binaire);


	//Formation d'un tableau des puissances de 2 correspondant a la cle public de B:
    int Tableau[14];
    for (int it = 0; it < 14; ++it) {
        Tableau[13-it]=pow(2,13-it)*Binaire[it];
    }

	//Decomposition de M puissance e:
   /*
    int tableauPuissance2[14];

    for (int t=0;t<14;++t)
    {
          tableauPuissance2[t]=pow(2,t);
    }
    */

    long CarreModn=Messagebis;
    CarreModn=(CarreModn)%modulo;
    long ResultatCode=1;
    for (int p = 0; p < 14; ++p)
    {
        if (Binaire[13-p]==1)
        {
            ResultatCode=(ResultatCode*CarreModn)%modulo;
        }
        CarreModn=(CarreModn*CarreModn)%modulo;
    }
    return ResultatCode;
}

void AfficheTableauNombre (int* tableau)
{
    for (int i = 0; i < 4; ++i) {
        printf("%d",tableau[i]);
    }
}

void AfficheTableauCaractere (int* tableau)
{
    printf("\"");
    for (int i = 0; i < 4; ++i) {
        printf("%c",tableau[i]);
    }
    printf("\"");
}

void MainAfficheEnvoie(int* tableau)
{
    printf("\nle code envoyé est ");
    AfficheTableauNombre(tableau);
    printf(" ie \n ");
    AfficheTableauCaractere(tableau);
}

void MainAfficheEnvoieAvantCodage(int* tableau)
{
    printf("\nle message à envoyer est ");
    AfficheTableauNombre(tableau);
    printf(" ie \n ");
    AfficheTableauCaractere(tableau);
}

void MainAfficheRecu(int* tableau)
{
    printf("\nle message  recu et decodé est ");
    AfficheTableauNombre(tableau);
    printf(" ie \n ");
    AfficheTableauCaractere(tableau);
}

#endif // FONCTION_RSA_H
