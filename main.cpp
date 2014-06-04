#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <list> ///inlocuieste-l cu baze de date
#include <cctype>


using namespace std;/**nu uita sa implementezi si inchiderea fisierelor si setarile in timpul jocului si eastereggs
                      si mai multe mesaje, alese random, pentru diverse mesaje, de ex pierdut, castigat,
                      apelat instructiuni a doua oara etc ,la easter eggs, daca introduce 69 spunei ca e pervers daca 666
                      ca e satanist sau ceva de ex ca aici nu merge sau ceva de neron de ex "stii care-i povestea acestui
                      numar? si daca spune nu sa ii spui ca asta era forma codata (deoarece in ebraica/greaca literele
                      erau si cifre iar 666 era forma codata pt imparatul neron sau ceva de genul.... sau trimitel la
                      numberphile sau undeva sa afle mai multe singur, si in caz ca nu merge dai povestea intr-un fisier
                      + cuvinte cenzurate si mustrare/pedeapsa+ achivments+ mai multe dictionare si sa il alegi tu pe
                      care il folosesti+ sa alegi cum sunt afisate literele incercate in ordine alfabetica sau in ordinea
                      in care le-ai introdus*/
                    /// idee de medalie pt cand introduci prima data o cifra prea mare

unsigned short int const lungimeaceluimailungcuvantdinromana=44;

char transformare_in_majuscula(char litera)
{
    if(litera>90)
        litera-=32;
    return litera;
}

int litere_de_aflat(char cuvant[],int literecunoscute[],int lungimecuvant)
{
    int contor=0;
    for(int i=1;i<lungimecuvant-1;i++)
        if(!literecunoscute[(cuvant[i]-65)])
            contor++;
    return contor;
}

void afisare_literelor_incercate(int literecunoscute[])
{
    char a;
    cout<<endl<<"Literele cunoscute sau incercate sunt:";
    for(int i=0;i<26;i++)
        if(literecunoscute[i])
        {
            a=i+65;
            cout<<a<<" ";
        }
    cout<<endl;
}

void afisare_cuvant (int lungimecuvant,char cuvant[],int literecunoscute[])
{
    cout<<endl<<cuvant[0]<<" ";
    for(int i=1;i<lungimecuvant-1;i++)
        if(literecunoscute[cuvant[i]-65])
            cout<<cuvant[i]<<" ";
        else
            cout<<'_'<<" ";
    cout<<cuvant[lungimecuvant-1]<<endl;
}

void afisare_spanzuratoare(int greseli)
{
    char adresagreseli[]="greseala0.txt";
    adresagreseli[8]+=greseli;
    ifstream in (adresagreseli);
    char caracter;
    cout<<endl;
    while (in>>caracter)
    {
        switch(caracter)
        {
            case '.':cout<<" ";break;
            case ',':cout<<endl;break;
            default: cout<<caracter;
        }
    }
}

void joc_nou()
{
    ifstream dictionar("dictionar.txt");
    int CuvinteInDictionar,cuvantales,cop,greseli=0,lungimecuvant,literecunoscute[26],i,alegere,sem=1;
    char cuvant[lungimeaceluimailungcuvantdinromana],litera;
    srand(time(NULL));
    dictionar>>CuvinteInDictionar;
    cuvantales=rand()%CuvinteInDictionar+1;
    cop=cuvantales;
    do
    {
        dictionar>>cuvant;
        cop--;
    }while(cop);
    lungimecuvant=strlen(cuvant);
    for(i=0;i<26;i++)
        literecunoscute[i]=0;
    literecunoscute[cuvant[0]-65]=literecunoscute[cuvant[lungimecuvant-1]-65]=1;
    do
    {
        afisare_spanzuratoare(greseli);
        afisare_literelor_incercate(literecunoscute);
        afisare_cuvant(lungimecuvant,cuvant,literecunoscute);
        cin>>litera;
        litera=transformare_in_majuscula(litera);
        while(literecunoscute[litera-65])
        {
            system("cls");
            afisare_spanzuratoare(greseli);
            afisare_literelor_incercate(literecunoscute);
            afisare_cuvant(lungimecuvant,cuvant,literecunoscute);
            cout<<"N-are rost sa introduci acesta litera. Introdu alta."<<endl;
            cin>>litera;
            litera=transformare_in_majuscula(litera);
        }
        literecunoscute[litera-65]=1;
        if(!strchr(cuvant,litera))
            greseli++;
        if(greseli==6||litere_de_aflat(cuvant,literecunoscute,lungimecuvant)==0)
            sem=0;
        system("cls");
    }while(sem);
    afisare_spanzuratoare(greseli);
    afisare_cuvant(lungimecuvant,cuvant,literecunoscute);
    cout<<endl;
    if(greseli!=6)
    {
        cout<<"Felicitari, ai descoperit cuvantul secret!"<<endl<<endl; ///eventula adauga si afisarea a ceva gen "mai aveai atatea vieti, sau ai terminat fara sa pierzi nici o viata, felicitari si ia o medalie
        cout<<endl
            <<"Introdu orice pentru a te intoarce in meniul principal."<<endl;
        cin>>litera;
        system("cls");
    }
    else
    {
        cout<<"Ai fost spanzurat inainte de a descoperi cuvantul secret!"<<endl;
        cout<<"Vrei sa afli cuvantul secret?"<<endl
            <<"Da(1)  Nu(2)"<<endl;
        cin>>alegere;
        alegere=alegere%2;
        if(alegere)
        {
            cout<<"Cuvantul secret era "<<cuvant<<"."<<endl;
        }
        dictionar.close();
        cout<<endl
            <<"Introdu orice litera pentru a te intoarce in meniul principal."<<endl;
        cin>>litera;
        system("cls");
    }
}
void instructiuni ()
{
    char chr,alegere;
    cout<<endl<<endl
        <<"********** INSTRUCTIUNI **********"<<endl<<endl<<endl
        <<"@In acest joc se alege un cuvant aleatoriu pe care trebuie sa-l ghicesti."<<endl<<endl
        <<"@In timpul jocului literele cunoscute ce se afla in cuvantul 'secret' sunt"<<endl<<"afisate pe pozitiile lor iar in locul pozitiilor literelor lipsa este afisat"<<endl<<"'_', iar fiecare pozitie este separata printr-un spatiu. La inceput jocului"<<endl<<"prima si ultima litera sunt cunoscute."<<endl<<endl
        <<"@'Spanzuratoarea' reprezinta numarul de greseli pe care le poti face inainte de 'a fi spanzurat', adica de a pierde jocul. La inceputul jocului ai 6 greseli pe care le poti face. Acum o sa va reprezentam 'spanzuratorile' ce reprezinta de la"<<"6 la 0 greseli ramase, in aceasta ordine"<<endl<<endl;
    ifstream spanzuratoarepentruinstructiuni("spanzuratoripentruinstructiuni.txt");
    while(spanzuratoarepentruinstructiuni>>chr)
    {
        switch(chr)
        {
            case '.':cout<<" ";break;
            case ',':cout<<endl;break;
            default: cout<<chr;
        }
    }
    cout<<endl<<endl
        <<"@In timpul jocului literele cunsocute (prima sau ultima litera a cuvantului si"<<endl<<"toate literele incercate)  iti sunt afisate in ordine alfabetica."<<endl<<endl
        <<"@In timpul jocului pentru a incerca o noua litera trebuie sa apesi tasta"<<endl<<"corespunzatoare acelei litere si sa dai enter. Nu conteaza daca e minuscula sau majuscula. Daca litera introdusa este cunoscuta ti se va cere sa introduci alta litera."<<endl<<endl
        <<"@Daca la sfarsitul jocului nu ai gasit cuvantul secret vei fi intrebat daca vrei"<<"sa il afli."<<endl<<endl
        <<"@In afara jocului (sau la sfarsitul acestuia daca pierzi) pentru alege o obtiune"<<"introdu numarul corespunzator alegerii."<<endl;
    cout<<endl
        <<"Introdu litera pentru a te intoarce in meniul principal."<<endl;
    cin>>alegere;
    system("cls");
}

int afisarea_cuvintelor_din_dictionar()///need improve, eventual sa arate pe litere daca sunt prea multe, sa poata fi apelata si din  adauga/scoate cuvinte
{
    std::fstream fisierdictionar;
    fisierdictionar.open ("dictionar.txt", std::fstream::in );
    int cuvinteindictionar,alegere;
    fisierdictionar>>cuvinteindictionar;
    char cuvant[44];
    cout<<"In dictionar sunt urmatoarele "<<cuvinteindictionar<<" cuvinte:"<<endl<<endl;
    while(fisierdictionar>>cuvant)
        cout<<cuvant<<endl;
    cout<<endl
        <<"         In continuare vreau:"<<endl
        <<"Sa ma intorc in meniul dictionarului(1)"<<endl
        <<"  Sa ma intorc in meniul principal(2)"<<endl;
    cin>>alegere;
    alegere%=2;
    switch(alegere)
    {
        case 1: system("cls");return 1;
        default: system("cls");return 0;
    }
}

void adauga_mai_multe_cuvinte_in_dictionar_alfa(int numardecuvitnedeadaugat)
{
    std::fstream fisierdictionar;
    std::list<std::string> listacuvintelordindictionar;
    fisierdictionar.open ("dictionar.txt", std::fstream::in | std::fstream::out );
    int cuvintEindictionar,i,lungimecuvantnou,contor=0;
    char cuvantnou[lungimeaceluimailungcuvantdinromana],cuvintDindictionar[lungimeaceluimailungcuvantdinromana];
    fisierdictionar>>cuvintEindictionar;
    for(i=0;i<cuvintEindictionar;i++)
    {
        fisierdictionar>>cuvintDindictionar;
        listacuvintelordindictionar.push_back(cuvintDindictionar);
    }
    do
    {
        system("cls");
        cout<<"Mai vrei sa adaugi "<<numardecuvitnedeadaugat<<", daca nu scrii stop."<<endl
            <<"Introdu un cuvat nou."<<endl;
        cin>>cuvantnou;
        lungimecuvantnou=strlen(cuvantnou);
        for(i=0;i<lungimecuvantnou;i++)
            cuvantnou[i]=transformare_in_majuscula(cuvantnou[i]);
        if(cuvantnou!="stop")
            listacuvintelordindictionar.push_back(cuvantnou);
        numardecuvitnedeadaugat--;
        contor++;
    }while(numardecuvitnedeadaugat>0 && cuvantnou!="stop");

    listacuvintelordindictionar.sort();
    fisierdictionar.clear();
    fisierdictionar.seekp(0);
    fisierdictionar<<cuvintEindictionar+contor<<endl;
    for(std::list<string>::iterator i=listacuvintelordindictionar.begin();i!=listacuvintelordindictionar.end();i++)
            fisierdictionar<<*i<<endl;
    fisierdictionar.close();
}

void adauga_un_cuvant_in_dictionar() ///adauga optiunea de final, adauga din nou
{
    std::fstream fisierdictionar;
    std::list<std::string> listacuvintelordindictionar;
    fisierdictionar.open ("dictionar.txt", std::fstream::in | std::fstream::out );
    int cuvintEindictionar,i,lungimecuvantnou;
    char cuvantnou[lungimeaceluimailungcuvantdinromana],cuvintDindictionar[lungimeaceluimailungcuvantdinromana];
    fisierdictionar>>cuvintEindictionar;
    for(i=0;i<cuvintEindictionar;i++)
    {
        fisierdictionar>>cuvintDindictionar;
        listacuvintelordindictionar.push_back(cuvintDindictionar);
    }
    cout<<endl
        <<"Introdu cuvatul nou."<<endl;
    cin>>cuvantnou;
    lungimecuvantnou=strlen(cuvantnou);
    for(i=0;i<lungimecuvantnou;i++)
        cuvantnou[i]=transformare_in_majuscula(cuvantnou[i]);
    listacuvintelordindictionar.push_back(cuvantnou);
    listacuvintelordindictionar.sort();
    fisierdictionar.clear();
    fisierdictionar.seekp(0);
    fisierdictionar<<cuvintEindictionar+1<<endl;
    for(std::list<string>::iterator i=listacuvintelordindictionar.begin();i!=listacuvintelordindictionar.end();i++)
            fisierdictionar<<*i<<endl;
    fisierdictionar.close();
}


int adauga_cuvinte_in_dictionar()///implementeaza inchiderea programului din meniul dictionarului si din meniurile functiilor din dictionar
{                                ///zi undeva ca daca un cuv exista deja in dictionar nu va fi reintrodus
    int numardecuvintedeadugat,alegere;
    cout<<"Cate cuvinte vrei sa adaugi?"<<endl;
    cin>>numardecuvintedeadugat;
    switch(numardecuvintedeadugat)
    {
        case 0: break;
        case 1: adauga_un_cuvant_in_dictionar();break; ///ce nu merge
        default: adauga_mai_multe_cuvinte_in_dictionar_alfa(numardecuvintedeadugat);
    }
    cout<<"In continuare vreau:"<<endl
        <<"Sa ma intorc in meniul dictionarului(1)"<<endl
        <<"Sa ma intorc in meniul principal(2)"<<endl;
    cin>>alegere;
    alegere%=2;
    switch(alegere)
    {
        case 1: system("cls");return 1;
        default: system("cls");return 0;
    }
}

void dictionar ()   ///printre setari sa fie si obtiunea de a afisa literele in ordine alfabetica, in ordinea spusa, sau in amble si functia de a scoate cuv din dictionar
{
    int alegere,sem=1; ///adauga si scoaterea cuvintelor dupa nr lor sau spunand cuvantul
    while(sem)
    {
        cout<<endl
        <<"*********** DICTIONAR ***********"<<endl<<endl<<endl
        <<" Vezi cuvintele din dictionar(1)"<<endl
        <<"Scrie cuvinte noi in dictionar(2)"<<endl
        <<"Intoarcete in meniul principal(3)"<<endl<<endl
        <<"Vreau sa (Introdu numarul corespunzator):";
        cin>>alegere;
        alegere%=3;
        switch(alegere)
            {
                case 1: system("cls");sem=afisarea_cuvintelor_din_dictionar();break;
                case 2: system("cls");sem=adauga_cuvinte_in_dictionar();break;
                default: system("cls");sem=0;
            }
    }
}
void setari()
{
    char alegere;
    cout<<"Aceasta functie este in curs de programare"<<endl;
    cout<<endl
        <<"Introdu orice pentru a te intoarce in meniul principal."<<endl;
    cin>>alegere;
    system("cls");
}

void statistici()
{
    char alegere;
    cout<<"Aceasta functie este in curs de programare"<<endl;
    cout<<endl
        <<"Introdu orice pentru a te intoarce in meniul principal."<<endl;
    cin>>alegere;
    system("cls");
}

void generic()
{
    char alegere;
    cout<<"Aceasta functie este in curs de programare"<<endl;
    cout<<endl
        <<"Introdu orice litera pentru a te intoarce in meniul principal."<<endl;
    cin>>alegere;
    system("cls");

}

int main()
{
    int sem=1;
    cout<<"******* **SPANZURATOAREA** *******"<<endl
        <<"                beta"<<endl<<endl
        <<"Un joc clasic acum in terminal pentru tine!"<<endl<<endl;
    while(sem)
    {
        int alegere;
        cout<<endl<<endl
        <<"************* MENIU *************"<<endl<<endl<<endl
        <<"             Joc Nou(1)"<<endl
        <<"          Instructiuni(2)"<<endl
        <<"            Dictionar(3)"<<endl
        <<"             Setari(4)"<<endl
        <<"            Statistici(5)"<<endl
        <<"             Generic(6)"<<endl
        <<"             Iesire(7)"<<endl<<endl
        <<"Vreau sa (Introdu numarul corespunzator):";
        cin>>alegere;
        alegere%=7;
        switch(alegere)
        {
            case 1: system("cls");joc_nou(); break;
            case 2: system("cls");instructiuni(); break;
            case 3: system("cls");dictionar(); break;
            case 4: system("cls");setari(); break;
            case 5: system("cls");statistici(); break;
            case 6: system("cls");generic();break;
            default: sem=0;
        }
    }
    return 0;
}
