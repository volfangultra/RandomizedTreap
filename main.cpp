#include "Stablo.h"
#include <iostream>


using namespace std;

int main(){
    Stablo<int> s;  //Dodavanje elemenata
    s.umetni(30);
    s.umetni(25);
    s.umetni(35);
    s.umetni(10);
    s.umetni(5);
    s.umetni(15);
    s.umetni(32);
    s.umetni(12);
    s.umetni(17);
    s.umetni(18);


    Stablo<int> a;
    a.umetni(70);
    a.umetni(45);
    a.umetni(1);
    a.umetni(20);

    cout << "Napravimo dva stabla: " << endl;
    s.ispisi(s.pocetak()); cout << endl;
    a.ispisi(a.pocetak()); cout << endl << endl;
    cout << "Prvo stablo razdvojimo oko elementa 16" << endl;

    pair<Stablo<int>, Stablo<int>> par = razdvajanje(s, 16);    //Razdvajanje na dva djela
    par.first.ispisi(par.first.pocetak()); cout  << "-> broj elemenata je: " << par.first.velicina() << endl;
    par.second.ispisi(par.second.pocetak()); cout << "-> broj elemenata je: " << par.second.velicina() << endl << endl;

    cout << "Kada smo ih razdvojili sada ih mozemo spojit: " << endl;
    s = spajanje(par.first, par.second);    //Spajanje vec razdvojenih
    s.ispisi(s.pocetak()); cout << "-> broj elemenata je: " << s.velicina() << endl << endl;

    cout << "Unija dva orginalna stabla je: " << endl;

    Stablo<int> rez(unija(s, a));
    rez.ispisi(rez.pocetak());
    cout << "-> broj elemenata je: " << rez.velicina() << endl << endl;
    cout << "Ako obrisemo (20, 30, 35, 17, 18, 45) dobijemo: " << endl;

    rez.izbrisi(20);
    rez.izbrisi(30);
    rez.izbrisi(35);
    rez.izbrisi(17);
    rez.izbrisi(18);
    rez.izbrisi(45);
    rez.ispisi(rez.pocetak());
    cout << "-> broj elemenata je: " << rez.velicina() << endl;

}
