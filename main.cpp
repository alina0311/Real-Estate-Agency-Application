//Dorneanu Alina-Mihaela, 141
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;
class locuinta
{
protected:
    string numeClient;
    double suprafataUtila;
    double discount;
    double pretMetruPatrat;
public:
    locuinta(string = "", double = 0, double = 0, double = 0);
    locuinta(const locuinta&);
    virtual ~locuinta();
    locuinta& operator=(const locuinta&);
    friend istream& operator>>(istream &in, locuinta&);
    friend ostream& operator<<(ostream &out, locuinta&);
    virtual double chirie() = 0;
    virtual void citire(istream& in) = 0;
    virtual void afisare(ostream& out) = 0;
};
locuinta::locuinta(string nume, double s, double d, double p)
{
    this->numeClient = nume;
    this->suprafataUtila = s;
    this->discount = d;
    this->pretMetruPatrat = p;
}
locuinta::locuinta(const locuinta& l)
{
    this->numeClient = l.numeClient;
    this->suprafataUtila = l.suprafataUtila;
    this->discount = l.discount;
    this->pretMetruPatrat = l.pretMetruPatrat;
}
locuinta::~locuinta()
{
    numeClient = "";
    suprafataUtila = 0;
    discount = 0;
    pretMetruPatrat = 0;
}
locuinta& locuinta::operator=(const locuinta& l)
{
    if (this == &l)
    {
        return *this;
    }
    this->numeClient = l.numeClient;
    this->suprafataUtila = l.suprafataUtila;
    this->discount = l.discount;
    this->pretMetruPatrat = l.pretMetruPatrat;
    return *this;
}
void locuinta::citire(istream& in)
{
    cout << "Dati numele clientului: ";
    in >> numeClient;
    cout << "Dati suprafata utila: ";
    in >> suprafataUtila;
    do
    {
        try
        {
            cout << "Dati discount-ul (%): ";
            in >> discount;
            if(discount < 0 or discount > 10)
                throw invalid_argument("ATENTIE! Discount-ul trebuie sa fie intre 0-10%.\n");
        }
        catch(invalid_argument exceptie)
        {
            cout << exceptie.what();
        }
    }
    while(discount < 0 or discount > 10);
    cout << "Dati pretul de inchiriere pe metru patrat: ";
    in >> pretMetruPatrat;
}
void locuinta::afisare(ostream& out)
{
    out << "\nNumele clientului: " << numeClient;
    out << "\nSuprafata utila: " << suprafataUtila;
    out << "\nDiscount-ul: " << discount;
    out << "\nPretul de inchieriere pe metru patrat: " << pretMetruPatrat;
}

istream& operator>>(istream &in, locuinta& l)
{
    l.citire(in);
    return in;
}
ostream& operator<<(ostream &out, locuinta& l)
{
    l.afisare(out);
    return out;
}
//clasa APARTAMENT

class apartament:public locuinta
{
    int etaj;
public:
    apartament(string = "", double = 0, double = 0, double = 0, int = 0);
    apartament(const apartament& a);
    virtual ~apartament();
    apartament& operator=(const apartament&);
    virtual double chirie();
    friend istream& operator>>(istream &in, apartament&);
    friend ostream& operator<<(ostream &out, const apartament&);
    virtual void citire(istream& in);
    virtual void afisare(ostream& out);
};
apartament::apartament(string nume, double s, double d, double p, int etaj):locuinta(nume, s, d, p ), etaj(etaj)
{
}
apartament::apartament(const apartament& a):locuinta(a)
{
    this->etaj = a.etaj;
}
apartament& apartament::operator=(const apartament& a)
{
    if (this == &a)
    {
        return *this;
    }
    locuinta::operator=(a);
    this->etaj = a.etaj;
    return *this;
}
double apartament::chirie()
{
    double c, p = 1;
    p = pretMetruPatrat * suprafataUtila;
    c = (discount * p)/100;
    return p - c;
}
void apartament::citire(istream& in)
{
    locuinta::citire(in);
    cout << "Dati etajul apartamentului: ";
    in >> etaj;
}
void apartament::afisare(ostream& out)
{
    locuinta::afisare(out);
    out << "\nEtajul apartamentului: " << etaj << '\n';
    out << "Chirie: " << chirie() << '\n';
}
ostream& operator<<(ostream& out, apartament& a)
{
    a.afisare(out);
    return out;
}
istream& operator>>(istream& in, apartament& a)
{
    a.citire(in);
    return in;
}
apartament::~apartament()
{
    etaj = 0;
}
//CLASA CASA
class casa: public locuinta
{
    int numarEtaje;
    double suprafataCurte;
    vector<double> suprafataEtaj;
    double pretMetruCurte;
public:
    casa(string = "", double = 0, double = 0, double = 0, int = 0, double = 0, vector<double> = {}, double = 0);
    casa(const casa&);
    virtual ~casa();
    casa& operator=(const casa&);
    virtual double chirie();
    friend istream& operator>>(istream &in, casa&);
    friend ostream& operator<<(ostream &out, casa&);
    virtual void citire(istream& in);
    virtual void afisare(ostream& out);
};
casa::casa(string nume, double suprafata, double dis, double pret, int n, double supCurte, vector<double> sup, double pretCurte):locuinta(nume, suprafata, dis, pret)
{
    this->numarEtaje = n;
    this->suprafataCurte = supCurte;
    this->pretMetruCurte = pretCurte;
    suprafataEtaj = sup;
}
casa::casa(const casa& c):locuinta(c)
{
    this->numarEtaje = c.numarEtaje;
    this->suprafataCurte = c.suprafataCurte;
    this->pretMetruCurte = c.pretMetruCurte;
    suprafataEtaj = c.suprafataEtaj;
}

casa::~casa()
{
    numarEtaje = 0;
    suprafataCurte = 0;
    pretMetruCurte = 0;
    suprafataEtaj.clear();
}
casa& casa::operator=(const casa& c)
{
    if (this == &c)
    {
        return *this;
    }
    locuinta::operator=(c);
    this->numarEtaje = c.numarEtaje;
    this->suprafataCurte = c.suprafataCurte;
    this->pretMetruCurte = c.pretMetruCurte;
    suprafataEtaj = c.suprafataEtaj;
    return *this;
}
double casa::chirie()
{
    double c, p = 1, s;
    p = pretMetruPatrat * suprafataUtila;
    s = (discount * p)/100;
    c = pretMetruCurte * suprafataCurte;
    return p - s + c;
}
istream& operator>>(istream &in, casa& c)
{
    c.citire(in);
    return in;
}
ostream& operator<<(ostream &out, casa& c)
{
    c.afisare(out);
    return out;
}

void casa::citire(istream& in)
{
    double x;
    locuinta::citire(in);
    cout << "Dati suprafata curtii: ";
    in >> suprafataCurte;
    cout << "Dati pretul pe metru patrat de curte: ";
    in >> pretMetruCurte;
    cout << "Dati numarul de etaje: ";
    in >> numarEtaje;
    cout << "Dati suprafata utila pe fiecare etaj: ";
    for(int i = 0; i < numarEtaje; i++)
    {
        in >> x;
        suprafataEtaj.push_back(x);
    }
}
void casa::afisare(ostream& out)
{
    locuinta::afisare(out);
    out << "\nNumar etaje: " << numarEtaje;
    out << "\nSuprafata curtii: " << suprafataCurte;
    out << "\nPretul pe metru patrat de curte: " << pretMetruCurte;
    out << "\nSuprafata utila pe fiecare etaj: ";
    for(int i = 0; i < numarEtaje; i++)
        out << suprafataEtaj[i] << ' ';
    out << '\n';
    out << "Chirie: " << chirie() << '\n';
}
//clasa gestiune
template <class t> class Gestiune
{
    t *v;
    static int index;
    int nr;
public:
    //supraincarcare pe =
    Gestiune(t *p = NULL, int n = 0)
    {
        nr = n;
        if(nr != 0)
        {
            v = new t[nr];
            for(int i = 0; i < nr; i++)
                v[i] = p[i];
        }
    }
    Gestiune(Gestiune &a)
    {
        nr = a.nr;
        v = new t[nr];
        for(int i = 0; i < nr; i++)
            v[i] = a.v[i];
    }
    ~Gestiune()
    {
        delete [] v;
    };
    t getLocuinta(int i)
    {
        return v[i];
    };
    const int getNr()
    {
        return nr;
    }
    static int getIndex(){
        return index;
    }
    friend istream& operator >>(istream &in, Gestiune<t> &g)
    {
        cout << "\nDati numarul de apartamente: ";
        in >> g.nr;
        g.v = new t[g.nr];
        for(int i = 0; i < g.nr; i++)
        {
            index++;
            cout << "\n\tApartamentul numarul " << i + 1 << ":" << "\n====================================\n\n";
            in >> g.v[i];
        }
        return in;
    }
    friend ostream& operator <<(ostream &out, Gestiune<t> &g)
    {
        if(g.nr != 1)
            out << "\n------------------------------------\nIN AGENTIA IMOBILIARA SUNT " << g.getIndex() << " APARTAMENTE:" << '\n';
        else
            out << "\n------------------------------------\nIN AGENTIA IMOBILIARA EXISTA DOAR UN APARTAMENT:\n";
        for(int i = 0; i < g.nr; i++)
            out << "\n\tApartamentul numarul " << i + 1 << ":\n====================================\n" << g.v[i];
    }
    Gestiune<t>& operator=(const Gestiune<t>& c)
    {
        if (this == &c)
        {
            return *this;
        }
        this->nr = c.nr;
        v = new t[nr];
        for(int i = 0; i < nr; i++)
        {
            v[i] = c.v[i];
        }
        return *this;
    }
    Gestiune<t>& operator+=(const Gestiune<t>& g)
    {
        int c = nr;
        t *w;
        w = new t[nr];
        for(int i = 0; i < nr; i++)
            w[i] = v[i];
        index = index + g.nr - 1;
        nr = nr + g.nr;
        v = new t[nr];
        for(int i = 0; i < nr; i++)
        {
            if(i < c)
                v[i] = w[i];
            else
                v[i] = g.v[i-c];
        }
        return *this;
    }
};
template <class t> int Gestiune<t>::index = 0;
//template casa
template <> class Gestiune <casa>
{
    casa* v;
    int nr;
    static int numarCase;
    static double chirieTotala;
public:
    Gestiune(casa *p = NULL, int n = 0)
    {
        nr = n;
        v = new casa[n];
        for(int i = 0; i < n; i++)
            v[i] = p[i];
    }
    Gestiune(Gestiune &a)
    {
        nr = a.nr;
        v = new casa[nr];
        for(int i = 0; i < nr; i++)
            v[i] = a.v[i];
    }
    ~Gestiune()
    {
        delete [] v;
    }
    static int getNumarCase()
    {
        return numarCase;
    }
    casa getv(int i)
    {
        return v[i];
    }
    friend istream& operator >>(istream &in, Gestiune <casa> &g)
    {
        cout << "\n\nDati numarul de case: ";
        in >> g.nr;
        g.v = new casa[g.nr];
        for(int i = 0; i < g.nr; i++)
        {
            numarCase++;
            cout << "\n\tCasa numarul " << i + 1 << ":" << "\n====================================\n\n";
            in >> g.v[i];
        }
        return in;
    }
    friend ostream& operator <<(ostream &out, Gestiune<casa> &g)
    {
        if(numarCase != 1)
            out << "\n------------------------------------\nIN AGENTIA IMOBILIARA SUNT " << numarCase << " CASE:\n";
        else
            out << "\n------------------------------------\nIN AGENTIA IMOBILIARA EXISTA DOAR O CASA:\n";
        for(int i = 0; i < g.nr; i++)
            out << "\n\tCasa numarul " << i + 1 << ":\n====================================\n" << g.v[i];
        g.calculeazaChirieTotala();
        out << "\nChiria obtinuta de pe toate casele este: " << getChirieTotala();
        return out;
    }
    Gestiune<casa>& operator=(const Gestiune<casa>& c)
    {
        if (this == &c)
        {
            return *this;
        }
        this->nr = c.nr;
        v = new casa[nr];
        for(int i = 0; i < nr; i++)
        {
            v[i] = c.v[i];
        }
        return *this;
    }
    void calculeazaChirieTotala()
    {
        for(int i = 0; i < nr ; i++)
        {
            chirieTotala = chirieTotala + v[i].chirie();
        }
    }
    static double getChirieTotala()
    {
        return chirieTotala;
    }
};
template <>int Gestiune<casa>::numarCase = 0;
template <>double Gestiune<casa>::chirieTotala = 0;
void printMeniu()
{
    cout << "\n*********************************AGENTIE IMOBILIARA*********************************\n";
    cout << '\n';
    cout << "\t\tMENIU:";
    cout << "\n\tAlegeti dintre urmatoarele optiuni: ";
    cout << "\n\t1. Agentie imobiliara cu case si apartamente.";
    cout << "\n\t2. Agentie imobiliara doar cu case.";
    cout << "\n\t3. Agentie imobiliara doar cu apartamente.";
    cout << "\n\t0. Iesire.";
}
void tip(locuinta*& L, vector<locuinta*> &v, int& i)
{
    string tipLocuinta;
    cout << "\nIntroduceti tipul de locuinta: ";
    cin >> tipLocuinta;
    cout << "\n\tProprietatea imobiliara numarul " << i + 1 << ":" << "\n==============================================\n\n";
    try
    {
        if(tipLocuinta == "casa")
        {
            L = new casa;
            cin >> *L;
            v.push_back(*&L);
            i++;
        }
        else if(tipLocuinta == "apartament")
        {
            L = new apartament;
            cin >> *L;
            v.push_back(*&L);
            i++;
        }
        else
            throw 3;
    }
    catch (bad_alloc exceptie)
    {
        cout << "\nAllocation Failure";
        exit(EXIT_FAILURE);
    }
    catch (int nr)
    {
        cout << "\nVa rugam sa introduceti o locuinta valida. Aceasta trebuie sa fie de tip casa sau apartament.";
    }
}
void meniu()
{
    int optiune, nr, index = 1, numarCase = 0, numarApartamente = 0;
    optiune = 0, nr = 0;
    locuinta **v;
    vector <locuinta*> L;
    Gestiune <apartament> A;
    Gestiune <casa> C;
    do
    {
        printMeniu();
        cout << "\n\n\tIntroduceti numarul actiunii pe care doriti sa o realizati: ";
        cin >> optiune;
        if(optiune == 0)
        {
            cout << "\n\n\nATI IESIT DIN APLICATIE!\n";
        }
        if(optiune == 1)
        {
            cout << "\nDati numarul de proprietati imobiliare: ";
            cin >> nr;
            v = new locuinta*[nr];
            if(nr > 0)
            {
                for(int i = 0; i < nr;)
                {
                    tip(v[i], L, i);
                }
                for(int i = 0; i < nr; i++)
                {
                    casa *p1 = dynamic_cast<casa*>(v[i]);
                    apartament *p2 = dynamic_cast<apartament*>(v[i]);
                    if (p1)
                        numarCase++;
                    if (p2)
                        numarApartamente++;
                }
                cout << "\n------------------------------------\nIN AGENTIA IMOBILIARA SUNT " << numarCase << " CASE SI " << numarApartamente << " APARTAMENTE:\n";
                vector <locuinta*>::iterator i;
                for(i = L.begin(); i != L.end(); i++)
                {
                    cout << "\n\tProprietatea imobiliara numarul " << index << ":\n=================================================\n";
                    cout << "\nTipul proprietatii imobiliare: ";
                    casa *p1 = dynamic_cast<casa*>(*i);
                    apartament *p2 = dynamic_cast<apartament*>(*i);
                    if(p1)
                        cout << "casa\n";
                    if(p2)
                        cout << "apartament\n";
                    cout << (**i);
                    cout << '\n';
                    index++;
                }
            }
            else
            {
                cout << "Numarul de proprietati imobiliare trebuie sa fie strict pozitiv.";
            }
        }
        if(optiune == 2)
        {
            Gestiune <casa> G;
            cin >> G;
            cout << G;
        }
        if(optiune == 3)
        {
            Gestiune <apartament> G;
            cin >> G;
            cout << G;
        }
    }
    while(optiune);
}
//main-ul
int main()
{
    //Pentru a testa operatorul += si + am lasat mai jos acestea
    /*
    Gestiune <casa> a;
    Gestiune <casa> b;
    cin >> a;
    b = a;
    cout << b;
    Gestiune <apartament> d, c;
    cin >> d;
    cin >> c;
    d += c;
    cout << d;
    */
    meniu();
    return 0;
}
