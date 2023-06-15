#ifndef STABLO_CPP
#define STABLO_CPP

#include "Stablo.h"
#include <random>
#include <time.h>

using namespace std;

//Privatno
template<typename Tip>
Stablo<Tip>::Cvor::Cvor(const Cvor& kopija){
    element = kopija.element;
    ld = nullptr;
    dd = nullptr;
    rod = nullptr;

};

template<typename Tip>
Stablo<Tip>::Cvor::Cvor(Tip element, Cvor* rod, Cvor* ld, Cvor* dd):element(element), rod(rod), ld(ld), dd(dd){
    if(!napravljen_seed){
        srand(time(NULL));
        napravljen_seed = true;
    }
    prioritet = rand();
    broj_elemenata = 1;

}

template<typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::nadji_najmanji(Cvor* cvor) const {
    if(cvor == nullptr)
        return nullptr;

    Cvor *trenutni = cvor;
    while(trenutni->ld != nullptr)
        trenutni = trenutni->ld;

    return trenutni;
}

template<typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::nadji_najveci(Cvor* cvor) const {
    if(cvor == nullptr)
        return nullptr;

    Cvor *trenutni = cvor;
    while(trenutni->dd != nullptr)
        trenutni = trenutni->dd;

    return trenutni;
}

template<typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::sljedeci(Cvor* cvor) const {
    if(cvor->dd != nullptr)
        return nadji_najmanji(cvor->dd);

    Cvor* trenutni = cvor;
    while(trenutni != korijen && trenutni == trenutni->rod->dd)
        trenutni = trenutni->rod;

    if(trenutni == korijen)
        return nullptr;
    else
        return trenutni->rod;
}

template<typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::prethodni(Cvor* cvor) const {
    if(cvor->ld != nullptr)
        return nadji_najveci(cvor->ld);

    Cvor* trenutni = cvor;
    while(trenutni != korijen && trenutni == trenutni->rod->ld)
        trenutni = trenutni->rod;

    if(trenutni == korijen)
        return nullptr;
    else
        return trenutni->rod;
}

//Osnove
template<typename Tip>
Stablo<Tip>::~Stablo(){
    while(!prazan())
        izbrisi(korijen);

}

template<typename Tip>
Stablo<Tip>::Stablo(const Stablo<Tip>& kopija){
    korijen = nullptr;
    if(kopija.korijen == nullptr)
        return;

    Cvor* trenutni = kopija.nadji_najmanji(kopija.korijen);
    Cvor* kraj = kopija.nadji_najveci(kopija.korijen);
    while(trenutni != kraj){
        Cvor* temp = new Cvor(trenutni->element, nullptr, nullptr, nullptr);
        temp->prioritet = trenutni->prioritet;
        umetni(temp);
        trenutni = kopija.sljedeci(trenutni);
    }

    Cvor* temp = new Cvor(trenutni->element, nullptr, nullptr, nullptr);
    temp->prioritet = trenutni->prioritet;
    umetni(temp);

}

template<typename Tip>
Stablo<Tip>::Stablo(Stablo<Tip>&& kopija){
    korijen = kopija.korijen;
    kopija.korijen = nullptr;

}

template<typename Tip>
Stablo<Tip>& Stablo<Tip>::operator=(const Stablo<Tip>& rhs){
    while(!prazan())
        izbrisi(korijen);

    if(rhs.korijen == nullptr){
        korijen = nullptr;
        return *this;

    }

    Cvor* trenutni = rhs.nadji_najmanji(rhs.korijen);
    Cvor* kraj = rhs.nadji_najveci(rhs.korijen);
    while(trenutni != kraj){
        Cvor* temp = new Cvor(trenutni->element, nullptr, nullptr, nullptr);
        temp->prioritet = trenutni->prioritet;
        umetni(temp);
        trenutni = rhs.sljedeci(trenutni);
    }

    Cvor* temp = new Cvor(trenutni->element, nullptr, nullptr, nullptr);
    temp->prioritet = trenutni->prioritet;
    umetni(temp);

    return *this;

}

template<typename Tip>
Stablo<Tip>& Stablo<Tip>::operator=(Stablo<Tip>&& rhs){
    while(!prazan())
        izbrisi(korijen);

    korijen = rhs.korijen;
    rhs.korijen = nullptr;
    return *this;

}


//Funkcionalnosti
template<typename Tip>
int Stablo<Tip>::velicina()const {
    if(korijen == nullptr)
        return 0;
    return korijen->broj_elemenata;

}

template<typename Tip>
pair<typename Stablo<Tip>::Cvor*, bool> Stablo<Tip>::umetni(Cvor* novi){
    if(novi->ld != nullptr || novi->dd != nullptr || novi->rod != nullptr)
            throw "Cvor ima veze";

    if(korijen == nullptr) {
        korijen = novi;
        return {korijen, true};

    }

    Tip element = novi->element;
    Cvor *trenutni = korijen, *prethodni = nullptr;
    while(trenutni != nullptr){
        prethodni = trenutni;
        if(trenutni->element > element)
            trenutni = trenutni->ld;
        else
            trenutni = trenutni->dd;

    }

    novi->rod = prethodni;
    if(prethodni->element > element)
        prethodni->ld = novi;
    else
        prethodni->dd = novi;

    while(prethodni != nullptr && prethodni->prioritet < novi->prioritet){
        novi->rod = prethodni->rod;
        if(korijen == prethodni)
            korijen = novi;

        if(prethodni->rod != nullptr){
            if(prethodni->rod->element > novi->element)
                prethodni->rod->ld = novi;
            else
                prethodni->rod->dd = novi;

        }

        prethodni->rod = novi;
        if(prethodni->dd == novi){
            prethodni->dd = novi->ld;
            if(novi->ld != nullptr)
                novi->ld->rod = prethodni;

            novi->ld = prethodni;

        }
        else{
            prethodni->ld= novi->dd;
            if(novi->dd != nullptr)
                novi->dd->rod = prethodni;

            novi->dd = prethodni;

        }

        prethodni->broj_elemenata = dodaj_djecu(prethodni) + 1;
        prethodni = novi->rod;
    }

    novi->broj_elemenata = dodaj_djecu(novi) + 1;
    while(prethodni != nullptr){
        prethodni->broj_elemenata++;
        prethodni = prethodni->rod;

    }


    return {novi,true};
}

template<typename Tip>
pair<typename Stablo<Tip>::Cvor*, bool> Stablo<Tip>::umetni(const Tip& element){
    Cvor* cvor = new Cvor(element, nullptr, nullptr, nullptr);
    return umetni(cvor);

}

template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::nadji(const Tip& element) const {
    Cvor* trenutni = korijen;
    while(trenutni != nullptr) {
        if(element == trenutni->element)
            return trenutni;
        if(element < trenutni->element)
            trenutni = trenutni->ld;
        else
            trenutni = trenutni->dd;
    }

    return nullptr;
}

template <typename Tip>
void Stablo<Tip>::izbrisi(Cvor *za_brisanje){
    Cvor *temp = za_brisanje->rod;
    while(temp != nullptr){
        temp->broj_elemenata--;
        temp = temp->rod;
    }

    if(za_brisanje->dd == nullptr){
        if(za_brisanje->ld == nullptr){
            if(za_brisanje->rod != nullptr){
                if(za_brisanje->rod->dd == za_brisanje)
                    za_brisanje->rod->dd = nullptr;
                else
                    za_brisanje->rod->ld = nullptr;

            }
            else
                korijen = nullptr;

        }
        else {
            za_brisanje->ld->rod = za_brisanje->rod;
            if(za_brisanje->rod != nullptr){
                if(za_brisanje->rod->dd == za_brisanje)
                    za_brisanje->rod->dd = za_brisanje->ld;
                else
                    za_brisanje->rod->ld = za_brisanje->ld;

            }
            else
                korijen = za_brisanje->ld;

        }
    }
    else {
        if(za_brisanje->ld == nullptr){
            za_brisanje->dd->rod = za_brisanje->rod;
            if(za_brisanje->rod != nullptr){
                if(za_brisanje->rod->dd == za_brisanje)
                    za_brisanje->rod->dd = za_brisanje->dd;
                else
                    za_brisanje->rod->ld = za_brisanje->dd;

            }
            else
                korijen = za_brisanje->dd;

        }
        else {
            if(za_brisanje->ld->prioritet > za_brisanje->dd->prioritet){
                za_brisanje->ld->rod = za_brisanje->rod;
                if(za_brisanje->rod != nullptr){
                    if(za_brisanje->rod->dd == za_brisanje)
                        za_brisanje->rod->dd = za_brisanje->ld;
                    else
                        za_brisanje->rod->ld = za_brisanje->ld;
                }
                else
                    korijen = za_brisanje->ld;

                Cvor* najdesniji_lijevog = za_brisanje->ld;
                Cvor* najljevlji_desnog = za_brisanje->dd;
                while(najdesniji_lijevog->dd != nullptr)
                    najdesniji_lijevog = najdesniji_lijevog->dd;

                while(najljevlji_desnog->ld != nullptr)
                    najljevlji_desnog = najljevlji_desnog->ld;

                while(najljevlji_desnog != za_brisanje){
                    najdesniji_lijevog->broj_elemenata = dodaj_djecu(najdesniji_lijevog) + 1;
                    if(najljevlji_desnog->prioritet < najdesniji_lijevog->prioritet){
                        Cvor* temp = najljevlji_desnog->rod;
                        temp->ld = nullptr;
                        temp->broj_elemenata = dodaj_djecu(temp) + 1;
                        najljevlji_desnog->rod = najdesniji_lijevog;
                        if(najdesniji_lijevog->dd != nullptr){
                            najdesniji_lijevog->dd->rod = najljevlji_desnog;
                            najljevlji_desnog->ld = najdesniji_lijevog->dd;
                            najljevlji_desnog->broj_elemenata = dodaj_djecu(najljevlji_desnog) + 1;

                        }

                        najdesniji_lijevog->dd = najljevlji_desnog;
                        najdesniji_lijevog->broj_elemenata = dodaj_djecu(najdesniji_lijevog) + 1;
                        temp->broj_elemenata = dodaj_djecu(temp) + 1;
                        najljevlji_desnog = temp;

                    }
                    else
                        najdesniji_lijevog = najdesniji_lijevog->rod;


                }

                while(najdesniji_lijevog != nullptr){
                    najdesniji_lijevog->broj_elemenata = dodaj_djecu(najdesniji_lijevog) + 1;
                    najdesniji_lijevog = najdesniji_lijevog->rod;

                }

            }
            else {
                za_brisanje->dd->rod = za_brisanje->rod;
                if(za_brisanje->rod != nullptr){
                    if(za_brisanje->rod->dd == za_brisanje)
                        za_brisanje->rod->dd = za_brisanje->dd;
                    else
                        za_brisanje->rod->ld = za_brisanje->dd;
                }
                else
                    korijen = za_brisanje->dd;

                Cvor* najdesniji_lijevog = za_brisanje->ld;
                Cvor* najljevlji_desnog = za_brisanje->dd;
                while(najdesniji_lijevog->dd != nullptr)
                    najdesniji_lijevog = najdesniji_lijevog->dd;

                while(najljevlji_desnog->ld != nullptr)
                    najljevlji_desnog = najljevlji_desnog->ld;

                while(najdesniji_lijevog != za_brisanje){
                    najljevlji_desnog->broj_elemenata = dodaj_djecu(najljevlji_desnog) + 1;
                    if(najdesniji_lijevog->prioritet < najljevlji_desnog->prioritet){
                        Cvor* temp = najdesniji_lijevog->rod;
                        temp->dd = nullptr;
                        najdesniji_lijevog->rod = najljevlji_desnog;
                        if(najljevlji_desnog->ld != nullptr){
                            najljevlji_desnog->ld->rod = najdesniji_lijevog;
                            najdesniji_lijevog->dd = najljevlji_desnog->ld;
                            najdesniji_lijevog->broj_elemenata = dodaj_djecu(najdesniji_lijevog) + 1;
                        }

                        najljevlji_desnog->ld = najdesniji_lijevog;
                        najljevlji_desnog->broj_elemenata = dodaj_djecu(najljevlji_desnog) + 1;
                        temp->broj_elemenata = dodaj_djecu(temp) + 1;
                        najdesniji_lijevog = temp;

                    }
                    else
                        najljevlji_desnog = najljevlji_desnog->rod;


                }

                while(najljevlji_desnog != nullptr){
                    najljevlji_desnog->broj_elemenata = dodaj_djecu(najljevlji_desnog) + 1;
                    najljevlji_desnog = najljevlji_desnog->rod;

                }


            }


        }

    }


    delete za_brisanje;

}

template <typename Tip>
int Stablo<Tip>::izbrisi(const Tip &element) {
    Cvor *za_brisanje = nadji(element);
    if(za_brisanje != nullptr) {
        izbrisi(za_brisanje);
        return 1;
    }
    else
        return 0;

}


//Pomocne
template<typename Tip>
void Stablo<Tip>::ispisi(const Cvor* cvor) {
    if(cvor == nullptr)
        return;
    ispisi(cvor->ld);
    cout<<cvor->element << " ";
    ispisi(cvor->dd);

}

template<typename Tip>
pair<Stablo<Tip>, Stablo<Tip>> razdvajanje(Stablo<Tip>& s, Tip element){
    if(s.korijen == nullptr)
        return {Stablo<Tip>(), Stablo<Tip>()};


    typename Stablo<Tip>::Cvor* za_ubacit = new typename Stablo<Tip>::Cvor(element, nullptr, nullptr, nullptr);
    za_ubacit->prioritet = s.korijen->prioritet + 10;
    s.umetni(za_ubacit);
    Stablo<Tip> prvo_stablo, drugo_stablo;
    prvo_stablo.korijen = s.korijen->ld;
    drugo_stablo.korijen = s.korijen->dd;

    if(prvo_stablo.korijen != nullptr)
        s.korijen->ld->rod = nullptr;

    if(drugo_stablo.korijen != nullptr)
        s.korijen->dd->rod = nullptr;

    s.korijen->ld = nullptr;
    s.korijen->dd = nullptr;

    return {prvo_stablo, drugo_stablo};

}

template<typename Tip>
Stablo<Tip> spajanje(Stablo<Tip> s1, Stablo<Tip> s2){
    if(s1.korijen == nullptr)
        return s2;
    if(s2.korijen == nullptr)
        return s1;

    int broj_elemenata = s1.velicina() + s2.velicina();
    Tip vrijednost = s1.nadji_najveci(s1.korijen)->element + 1;
    if(vrijednost > s2.nadji_najmanji(s2.korijen)->element)
        vrijednost = (s1.nadji_najveci(s1.korijen)->element + s2.nadji_najmanji(s2.korijen)->element) / 2;

    long int prioritet = -1;
    typename Stablo<Tip>::Cvor* cvor = new typename Stablo<Tip>::Cvor(vrijednost, nullptr, s1.korijen, s2.korijen);
    s1.korijen->rod = cvor;
    s2.korijen->rod = cvor;
    cvor->ld = s1.korijen;
    cvor->dd = s2.korijen;
    cvor->prioritet = prioritet;
    Stablo<Tip> rez;
    rez.korijen = cvor;
    while(cvor != nullptr){
        if(cvor->ld == nullptr && cvor->dd == nullptr){
            if(cvor->rod != nullptr){
                if(cvor->rod->dd == cvor)
                    cvor->rod->dd = nullptr;
                else
                    cvor->rod->ld = nullptr;

           }
            else
                rez.korijen = nullptr;

            cvor = nullptr;
        }
        else if(cvor->ld == nullptr){
            cvor->dd->rod = cvor->rod;
            if(cvor->rod != nullptr){
                if(cvor->rod->dd == cvor)
                    cvor->rod->dd = cvor->dd;
                else
                    cvor->rod->ld = cvor->dd;

            }
            else
                rez.korijen = cvor->dd;

            cvor->rod = cvor->dd;
            cvor->dd = cvor->dd->ld;
            if(cvor->dd != nullptr)
                cvor->dd->rod = cvor;

            cvor->rod->ld = cvor;

        }
        else if(cvor->dd == nullptr){
            cvor->ld->rod = cvor->rod;
            if(cvor->rod != nullptr){
                if(cvor->rod->dd == cvor)
                    cvor->rod->dd = cvor->ld;
                else
                    cvor->rod->ld = cvor->ld;

            }
            else
                rez.korijen = cvor->ld;

            cvor->rod = cvor->ld;
            cvor->ld = cvor->ld->dd;
            if(cvor->ld != nullptr)
                cvor->ld->rod = cvor;

            cvor->rod->dd = cvor;

        }
        else{
            if(cvor->ld->prioritet > cvor->dd->prioritet){
                cvor->ld->rod = cvor->rod;
                if(cvor->rod != nullptr){
                    if(cvor->rod->dd == cvor)
                        cvor->rod->dd = cvor->ld;
                    else
                        cvor->rod->ld = cvor->ld;

                }
                else
                    rez.korijen = cvor->ld;

                cvor->rod = cvor->ld;
                cvor->ld = cvor->ld->dd;
                if(cvor->ld != nullptr)
                    cvor->ld->rod = cvor;

                cvor->rod->dd = cvor;

            }
            else{
                cvor->dd->rod = cvor->rod;
                if(cvor->rod != nullptr){
                    if(cvor->rod->dd == cvor)
                        cvor->rod->dd = cvor->dd;
                    else
                        cvor->rod->ld = cvor->dd;

                }
                else
                    rez.korijen = cvor->dd;

                cvor->rod = cvor->dd;
                cvor->dd = cvor->dd->ld;
                if(cvor->dd != nullptr)
                    cvor->dd->rod = cvor;

                cvor->rod->ld = cvor;

            }

        }

    }

    s1.korijen = nullptr;
    s2.korijen = nullptr;
    rez.korijen->broj_elemenata = broj_elemenata;
    return rez;

}

template<typename Tip>
Stablo<Tip> unija(Stablo<Tip>& s1, Stablo<Tip>& s2){
    if(s1.korijen == nullptr)
        return s2;

    if(s2.korijen == nullptr)
        return s1;

    Stablo<Tip> prvi_dio, drugi_dio;
    typename Stablo<Tip>::Cvor* korijen;
    if(s1.korijen->prioritet > s2.korijen->prioritet){
        Stablo<Tip> lijevo_podstablo_prvog, desno_podstablo_prvog;
        lijevo_podstablo_prvog.korijen = s1.korijen->ld;
        if(lijevo_podstablo_prvog.korijen != nullptr)
            lijevo_podstablo_prvog.korijen->rod = nullptr;

        desno_podstablo_prvog.korijen = s1.korijen->dd;
        if(desno_podstablo_prvog.korijen != nullptr)
            desno_podstablo_prvog.korijen->rod = nullptr;

        korijen = s1.korijen;
        korijen->ld = nullptr;
        korijen->dd = nullptr;
        pair<Stablo<Tip>, Stablo<Tip>> par = razdvajanje(s2, s1.korijen->element);
        prvi_dio = unija(lijevo_podstablo_prvog, par.first);
        drugi_dio = unija(desno_podstablo_prvog, par.second);

    }
    else{
        Stablo<Tip> lijevo_podstablo_drugog, desno_podstablo_drugog;
        lijevo_podstablo_drugog.korijen = s2.korijen->ld;
        if(lijevo_podstablo_drugog.korijen != nullptr)
            lijevo_podstablo_drugog.korijen->rod = nullptr;

        desno_podstablo_drugog.korijen = s2.korijen->dd;
        if(desno_podstablo_drugog.korijen != nullptr)
            desno_podstablo_drugog.korijen->rod = nullptr;

        korijen = s2.korijen;
        korijen->ld = nullptr;
        korijen->dd = nullptr;
        pair<Stablo<Tip>, Stablo<Tip>> par = razdvajanje(s1, s2.korijen->element);
        prvi_dio = unija(lijevo_podstablo_drugog, par.first);
        drugi_dio = unija(desno_podstablo_drugog, par.second);

    }

    s1.korijen = nullptr;
    s2.korijen = nullptr;
    korijen->broj_elemenata = prvi_dio.velicina() + drugi_dio.velicina() + 1;
    Stablo<Tip> rez = spajanje(prvi_dio, drugi_dio);
    rez.umetni(korijen);
    return rez;

}

template<typename Tip>
int Stablo<Tip>::dodaj_djecu(Cvor* cvor){
    if(cvor->ld == nullptr && cvor->dd == nullptr)
        return 0;
    if(cvor->dd == nullptr)
        return cvor->ld->broj_elemenata;
    if(cvor->ld == nullptr)
        return cvor->dd->broj_elemenata;
    return cvor->ld->broj_elemenata + cvor->dd->broj_elemenata;

}



#endif
