#include <iostream>
#include <string>

using namespace std;

class Veicolo{
    protected:
        string targa;
        string marca;
    public:
        // costruttore con initializer list
        Veicolo(string t, string m) : targa(t), marca(m) {};
        // metodo virtuale puro, rende la classe astratta
        virtual void calcolaAutonomia() = 0;
        // distruttore (opzionale)
        virtual ~Veicolo(){};
};

class AutoElettrica : public Veicolo {
    private: 
        int percentualeBatteria;
    public:
        // overload costruttore
        //default (ma comunque parametrizzato)
        AutoElettrica() : Veicolo("AA000BB","BYD"), percentualeBatteria(100) {};
        //parametrizzato custom
        AutoElettrica(string t, string m , int batt_perc) : Veicolo(t,m), percentualeBatteria(batt_perc) {};
        
        // override del metodo calcolaAutonomia
        // 1 percent = 4 km di autonomia

        void calcolaAutonomia() override {
            int autonomia = percentualeBatteria * 4;
            cout<<"[*] Targa: "<<targa<<"\n";
            cout<<"[*] Marca: "<<marca<<"\n";
            cout<<"[*] Autonomia: "<<autonomia<<"\n";
        };

        // distruttore
        ~AutoElettrica(){
            cout<<"[*] Distruttore di AutoElettrica invocato\n";
        };
};

class AutoDiesel : public Veicolo {
    private:
        float litriCarburante = 0;
    public:
        // cost. param.
        AutoDiesel(string t, string m, float carb_lt) : Veicolo(t,m), litriCarburante(carb_lt) {};
        // override calcolaAutonomia
        // 1 litro per 15 km di autonomia
        void calcolaAutonomia() override {
            int autonomia = litriCarburante * 15;
            cout<<"[*] Targa: "<<targa<<"\n";
            cout<<"[*] Marca: "<<marca<<"\n";
            cout<<"[*] Autonomia: "<<autonomia<<"\n";
        };

        // distruttore
        ~AutoDiesel(){
            cout<<"[*] Distruttore di AutoDiesel invocato\n";
        };
};

int main(){
    int N; // dimensione del garage
    // alloco nello stack una prima auto
    AutoElettrica a1;
    a1.calcolaAutonomia();
    // allocazione dinamica del garage
    cout<<"[*] Quanti veicoli vuoi inserire nel garage? "<<endl;
    cin>>N;
    // allocazione dinamica del garage
    // int* p = new int(10)
    // double pointer perchè è un puntatore che punta al vettore di puntatori
    // ogni veicolo è allocato dinamicamente -> puntatore
    // il garage anche allocato dinamicamente -> puntatore
    // il risultato è un puntatore che punta alla lista di puntatori degli ogg.dinamici (le auto)
    Veicolo** garage = new Veicolo*[N];
    // riempio il garage
    for(int i=0;i<N;i++){

        int tipo_veicolo = 0;
        string targa;
        string marca;
        int percentualeBatteria = 0;
        int litri = 0;
        cout<<"[*] Quale tipologia di veicolo vuoi inserire nel garage? "<<endl;
        cin>>tipo_veicolo;

        if (tipo_veicolo == 1){
            cout<<"[*] Inserisco vettura elettrica. "<<endl;
            cout<<"[*] Inserisci targa: "<<endl;
            cin>>targa;
            cout<<"[*] Inserisci marca: "<<endl;
            cin>>marca;
            cout<<"[*] Inserisci percentuale Batteria: "<<endl;
            cin>>percentualeBatteria;
            cout<<"[*] Fatto. "<<endl;
            garage[i] = new AutoElettrica(targa,marca,percentualeBatteria);
        };

        if (tipo_veicolo == 2){
            cout<<"[*] Inserisco vettura diesel. "<<endl;
            cout<<"[*] Inserisci targa: "<<endl;
            cin>>targa;
            cout<<"[*] Inserisci marca: "<<endl;
            cin>>marca;
            cout<<"[*] Inserisci litri: "<<endl;
            cin>>litri;
            cout<<"[*] Fatto. "<<endl;
            garage[i] = new AutoDiesel(targa,marca,litri);
        };
    };

    for (int i=0;i<N;i++){
        garage[i]->calcolaAutonomia();
    }

    cout<<"[*] Adesso libero la memoria. Dealloco dall'heap \n";
    for (int i=0;i<N;i++){
        delete garage[i];
    };
    delete[] garage;

};