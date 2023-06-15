#ifndef STABLO_H
#define STABLO_H

#include <utility>
#include <iostream>

using namespace std;


template<typename Tip>
class Stablo{
    struct Cvor{
        static bool napravljen_seed;
        long int prioritet;
        int broj_elemenata;
        Tip element;
        Cvor *ld, *dd, *rod;
        Cvor(const Cvor&);
        Cvor(Tip, Cvor*, Cvor*, Cvor*);
    };
    Cvor* korijen;
    Cvor* nadji_najmanji(Cvor*) const;
    Cvor* nadji_najveci(Cvor*) const;
    Cvor* sljedeci(Cvor*) const;
    Cvor* prethodni(Cvor*) const;

    public:
    //Osnove
    Stablo():korijen(nullptr){}
    Stablo(const Tip& element):korijen(new Cvor(element, nullptr, nullptr, nullptr)){korijen->broj_elemenata = 1; }
    ~Stablo();
    Stablo(const Stablo<Tip>&);
    Stablo(Stablo<Tip>&&);
    Stablo<Tip>& operator=(const Stablo<Tip>&);
    Stablo<Tip>& operator=(Stablo<Tip>&&);

    //Funkcjonalnosti
    const Cvor* pocetak() const {return korijen; }
    const Cvor* kraj() const {return nadji_najveci(korijen)->dd; }
    bool prazan() const {return korijen == nullptr; }
    int velicina() const;
    pair<Cvor*, bool> umetni(Cvor*);
    pair<Cvor*, bool> umetni(const Tip&);
    Cvor* nadji(const Tip&) const;
    void izbrisi(Cvor* za_brisanje);
    int izbrisi(const Tip&);

    //Pomocne
    void ispisi(const Cvor* cvor);
    template<typename Tip2>
    friend pair<Stablo<Tip2>, Stablo<Tip2>> razdvajanje(Stablo<Tip2>&, Tip2);
    template<typename Tip2>
    friend Stablo<Tip2> spajanje(Stablo<Tip2>, Stablo<Tip2>);
    template<typename Tip2>
    friend Stablo<Tip2> unija(Stablo<Tip2>&, Stablo<Tip2>&);
    int dodaj_djecu(Cvor*);

};

template<typename Tip>
bool Stablo<Tip>::Cvor::napravljen_seed = false;

#include "Stablo.cpp"


#endif
