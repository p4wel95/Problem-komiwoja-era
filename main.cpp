#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iomanip>

using namespace std;

//-------- wstawienie punktu do sciezki
//-------- funkcja wstawiajaca wartosc w wybrane miejsce tabeli,
//-------- wstawiajac w miejsce [5] przesunie miejsca od [5] do [tabsize] o 1 w prawo.
void tabInsert (int *c,int value, int pos, int tabsize)
{
    for (int i = tabsize-1; i>pos;i--)
    {
        c[i] = c[i-1];
    }
    c[pos] = value;
}

//------- wysietla sciezke
void showC (int *c,int cLength)
{
    for (int i=0; i<cLength; i++)
        {
            cout<<c[i]<<" - ";

        }
}


int main()
{
    //------wybranie opcji-----
	int wybor;
	cout<<"Wprowadz punkty :"<<endl;
	cout<<"1. z klawiatury"<<endl;
	cout<<"2. z pliku"<<endl;
	cout<<"3. losowo"<<endl;
	//------- powrot gdy wybierze sie zla opcje: ------------
	poczontek:
	cout<<"Wybor : ",cin>>wybor;
	//-------- deklaracja zmiennych -------
	int n;
	string linia;
	fstream plik;
	string xstr = "";
    string ystr = "";
    int zakresOd;
    int zakresDo;
    //------ podanie ilosci punktow --------------
	if (wybor==1 || wybor ==3)
	{
		cout<<"liczba punktow : ",cin>>n;
	}
    //-------- gdy odczyt z pliku program sam wyznacza na podstawie liczby linii w pliku ------
	else if (wybor == 2)
	{
        n=0;
        plik.open("plik.txt", ios::in);
        if(plik.good()==false) cout<<"Nie mozna otworzyc pliku!";
        while (getline(plik, linia))
        {
            n++;
        }
        cout<<"liczba punktow : "<<n<<endl;
        plik.clear();
        plik.seekg(0, ios::beg);
	}
	// ---- wraca na poczatek gdy niepoprawny wybor opcji ----------
	else goto poczontek;

    // --------  deklaracja tablic z wspolrzednymi punktow ----------
	double x[n+1];
    double y[n+1];
    //punkt startowy ma wspolrzedne 0,0
    x[0]=0;
    y[0]=0;
    // ---------- pobranie danych z klawiatury i zapis do tabel x,y ----------
	if (wybor==1)
	{
		cout<<"podaj wspolrzedne punktow oddzielone przecinkiem np : 11.2,22.3"<<endl;
		for (int i = 0; i < n; i++)
		{

  			cout << i+1 << " : ",cin>>linia;
  			for (int j=0;j<linia.length();j++)
            {
                if (linia[j] != 44)
                {
                    continue;
                }
                else
                {
                    xstr = linia.substr(0,j);
                    ystr = linia.substr(j+1,50);

                    x[i+1] = atof(xstr.c_str());
                    y[i+1] = atof(ystr.c_str());
                }

            }
		}
	}
    //---------- pobranie danych z pliku i zapis do tabel x,y ----------
	else if (wybor == 2)
	{
    for (int i=0; i<n; i++)
    {
        getline(plik, linia);
        for (int j=0;j<linia.length();j++)
        {
            if (linia[j] != 44)
            {
                continue;
            }
            else
            {
                xstr = linia.substr(0,j);
                ystr = linia.substr(j+1,50);

                x[i+1] = atof(xstr.c_str());
                y[i+1] = atof(ystr.c_str());
            }

        }

    }

    plik.close();

	}
    // -------- losowanie wspolrzednych ---------
	else if (wybor == 3)
	{

		cout<<"zakres od (liczba dodatnia): ",cin>>zakresOd;
		cout<<"zakres do (liczba dodatnia): ",cin>>zakresDo;
		srand (time(NULL));
		int ile = 1;
		int duplikat = 0;
		while (ile < n+1)
        {
            duplikat = 0;
            x[ile] = rand()%(zakresDo-zakresOd+1)+zakresOd;
            y[ile] = rand()%(zakresDo-zakresOd+1)+zakresOd;
            for (int i = 1; i<ile;i++)
            {
                if (x[ile]== x[i] && y[ile]==y[i])
                {
                    duplikat = 1;
                }
            }
            if (duplikat==0) ile++;

        }

	}
    //----------- wyswietlenie wprowadzonych danych --------------
    n++;
    cout<<endl<<"punkty : "<<endl<<endl;
    for (int i = 0; i < n; i++)
		{

  			cout << i << " : "<<x[i]<<" , "<<y[i];
  			if (i==0) cout<<" <- pkt startowy";
  			cout<<endl;
		}
    double m[n][n];

 // ------- wyliczenie macierzy kosztow
    for (int i=0;i<n;i++)
    {

        for (int j=0;j<n;j++)
        {
            m[i][j] = sqrt(pow((x[j]-x[i]),2)+pow((y[j]-y[i]),2));
        }
    }

    cout << fixed;
/*
    for (int i=0; i<5;i++)
    {
        for (int j=0;j<5;j++)
        {
            cout<<"m["<<i<<"]["<<j<<"] = ",cin>>m[i][j];
            cout<<endl;
        }
    }


m[0][0] = 0;
m[0][1] = 7;
m[0][2] = 8;
m[0][3] = 1;
m[0][4] = 14;

m[1][0] = 7;
m[1][1] = 0;
m[1][2] = 4;
m[1][3] = 5;
m[1][4] = 3;

m[2][0] = 8;
m[2][1] = 4;
m[2][2] = 0;
m[2][3] = 11;
m[2][4] = 6;

m[3][0] = 1;
m[3][1] = 5;
m[3][2] = 11;
m[3][3] = 0;
m[3][4] = 8;

m[4][0] = 14;
m[4][1] = 3;
m[4][2] = 6;
m[4][3] = 8;
m[4][4] = 0;

*/
//-------- wyswietlenie macierzy kosztow
    cout<<endl<<"macierz kosztow : "<<endl<<"  ||";
    for (int i=0;i<n;i++) cout<<"    "<<i<<"    ";
    cout<<endl<<"  ||"<<endl;
    for (int i=0;i<n;i++)
    {
        cout<<i<<" || ";
        for (int j=0;j<n;j++)
        {
            if (m[i][j] < 10) cout << setprecision(4);
            else if (m[i][j] < 100) cout << setprecision(3);
            else if (m[i][j] < 1000) cout << setprecision(2);
            else if (m[i][j] < 10000) cout << setprecision(1);
            else cout << setprecision(0);
            cout<<m[i][j]<<" | ";
        }
        cout<<endl;
    }
    cout << setprecision(4);
    //tablica d algorytmu
    double d[n];

    //tablica zawierajaca sciezke :
    int *c = new int[n+1];

    int dmax = 0;

    // 1 iteracja algorytmu :
    //wyznaczenie tablicy d i max z tablicy d:
    for (int i=0; i<n; i++)
    {
        d[i]=m[0][i];
        if (d[i] > d[dmax]) dmax = i;
    }
    cout<<endl<<"d : ";
    for (int i=0; i<n; i++)
    {
        cout<<d[i]<<"   ";

    }
    cout<<endl<<endl<<"d max : "<<dmax<<endl;
    // sciezka po 1 iteracji :
    c[0] = 0;
    c[1] = dmax;
    c[2] = 0;
    int cLength = 3;
    // dlugosc drogi - zostanie wyliczona na koncu algorytmu
    double droga = 0;

    // wyswietlenie sciezki po 1 kroku algorytmu.
    showC(c,cLength);

    // deklaracja zmiennych uzywanych do  wyliczania miejsca wstawienia kolejnego punktu:
    double k = 0;
    double kmin = 0;
    int kpos = 1;


    // kolejne iteracje algorytmu
    for (int i = 0; i<n-2; i++)
    {
        // aktualizacja tabeli d
        for (int j = 0; j<n; j++)
        {
            if (d[j] > m[dmax][j])  d[j]=m[dmax][j];
        }
        // wyznaczenie max z tabeli d
        dmax = 0;
        for (int j=0; j<n; j++)
        {
            if (d[j] > d[dmax]) dmax = j;
        }
        cout<<endl<<"d : ";
        for (int j=0; j<n; j++)
        {
            cout<<d[j]<<"   ";
        }
        cout<<endl<<endl<<"d max : "<<dmax<<endl;

        // wyliczanie optymalnego miesca do wstawienia kolejnego punktu do sciezki
        // pierwszy wynik zapisywany do kmin, jesli nastepny bedzie mniejszy kmin przyjmuje jego wartosc
        kmin = (m[c[0]][dmax] + m[dmax][c[1]] - m[c[0]][c[1]]);
        cout<<"kmin : "<<kmin<<endl;
        // kpos zawiera pozycje gdzie wstawic punkt do sciezki
        kpos = 1;
        // wyliczanie kolejnych k, jesli mniejsze aktualizacja kmin i kpos.
        for (int i=1;i<cLength-1;i++)
        {
            k = m[c[i]][dmax] + m[dmax][c[i+1]] - m[c[i]][c[i+1]];
            if (k < kmin) kmin = k, kpos = i+1;
        }
        cout<<"k : "<<k<<endl;
        cout<<"kmin : "<<kmin<<endl;
        cout<<"kpos : "<<kpos<<endl;

        //dodanie punktu do sciezki
        tabInsert(c, dmax, kpos,n+1);
        // cLength zawira ilosc punktow w sciezce
        cLength++;
        // wyswietlenie sciezki
        showC(c,cLength);


    }
    // wyliczenie dlugosci drogi.
    for (int i=0; i<n; i++)
    {
        droga = droga + m[c[i]][c[i+1]];
    }
    // wyswietlenie dlugosci drogi
    cout <<"droga = "<<droga;


    cin.get(),cin.get();
    return 0;
}
