# Gestionale Garage in C++

Questo è un semplice progetto in C++ da riga di comando che simula la gestione di un garage di veicoli. L'obiettivo principale è mettere in pratica i concetti fondamentali della programmazione orientata agli oggetti (OOP) e capire come gestire i flussi di dati quando si lavora direttamente con la memoria del computer (lo Heap).

Il programma permette all'utente di creare un elenco di veicoli personalizzato, inserendo sia auto elettriche che auto diesel, e calcola in automatico l'autonomia di ogni mezzo in base allo stato della batteria o ai litri di carburante rimasti.

---

## Struttura del progetto

Il codice è interamente contenuto nel file main.cpp ed è diviso in tre parti logiche: la classe base, le classi derivate e la logica di controllo nel main.

### 1. La classe Base: Veicolo
È il modello di partenza per ogni mezzo che può entrare nel garage. Contiene le informazioni communes a tutti i veicoli (la targa e la marca). 
* La classe è definita astratta perché contiene il metodo virtual void calcolaAutonomia() = 0. Questo significa che non è possibile creare un veicolo generico, ma si è obbligati a specificare di che tipo di veicolo si tratta tramite le classi figlie.
* Include un distruttore virtuale per garantire che, quando cancelliamo un veicolo dalla memoria, vengano distrutti anche i dati specifici delle classi derivate, evitando di lasciare spazzatura nello Heap.

### 2. Le classi Figlie: AutoElettrica e AutoDiesel
Espandono la classe base aggiungendo le caratteristiche specifiche del tipo di alimentazione:
* AutoElettrica: aggiunge il campo privato per la percentuale della batteria. Quando calcola l'autonomia, applica la proporzione 1% = 4 km. Include anche un costruttore di default che crea un'auto preimpostata (una BYD con targa standard) per i test rapidi.
* AutoDiesel: aggiunge il campo per i litri di carburante. Il calcolo dell'autonomia si basa sulla proporzione 1 litro = 15 km.

Entrambe le classi implementano l'override della funzione calcolaAutonomia(), stampando i dati formattati a schermo, e hanno un distruttore personalizzato che notifica quando l'oggetto viene rimosso dal sistema.

### 3. La logica nel main()
Il programma esegue le seguenti operazioni in sequenza:
1. Alloca un'auto elettrica di default direttamente nello Stack per verificare subito il funzionamento della classe.
2. Chiede all'utente quanti veicoli vuoi inserire e alloca dinamicamente lo spazio necessario nello Heap per ospitare i puntatori ai veicoli.
3. Avvia un ciclo in cui l'utente sceglie il tipo di veicolo (1 per Elettrica, 2 per Diesel) e ne inserisce marca, targa e livello di energia/carburante.
4. Esegue un secondo ciclo che sfrutta il polimorfismo: chiama lo stesso metodo calcolaAutonomia() per tutti gli elementi del garage, ma il programma esegue automaticamente la formula corretta a seconda che l'oggetto sia un'auto elettrica o diesel.
5. Pulisce la memoria eliminando prima i singoli veicoli creati con new e poi l'array del garage stesso, assicurando che non ci siano memory leak.

---

## Logica di calcolo dell'autonomia

I calcoli all'interno dei metodi di override sono molto diretti:

* Veicoli Elettrici: Autonomia (km) = Percentuale Batteria * 4
* Veicoli Diesel: Autonomia (km) = Litri Carburante * 15

---

## Come compilarlo ed eseguirlo

Per far girare il programma serve un compilatore C++ standard (come g++) installato sul sistema. I comandi da terminale sono i seguenti:

1. Compilazione:
g++ -Wall -std=c++17 main.cpp -o garage.out
(Il flag -Wall serve a mostrare tutti gli avvisi del compilatore in caso di potenziali problemi nel codice).

2. Esecuzione:
./garage.out

---

## Esempio pratico di esecuzione

Ecco cosa compare a schermo quando si avvia il programma e si inseriscono due auto diverse:

```text
[*] Targa: AA000BB
[*] Marca: BYD
[*] Autonomia: 400

[*] Quanti veicoli vuoi inserire nel garage? 
2

[*] Quale tipologia di veicolo vuoi inserire nel garage? 
1
[*] Inserisco vettura elettrica. 
[*] Inserisci targa: EF456GH
[*] Inserisci marca: Tesla
[*] Inserisci percentuale Batteria: 85
[*] Fatto. 

[*] Quale tipologia di veicolo vuoi inserire nel garage? 
2
[*] Inserisco vettura diesel. 
[*] Inserisci targa: IL789MN
[*] Inserisci marca: Audi
[*] Inserisci litri: 45
[*] Fatto. 

[*] Targa: EF456GH
[*] Marca: Tesla
[*] Autonomia: 340

[*] Targa: IL789MN
[*] Marca: Audi
[*] Autonomia: 675

[*] Adessen libero la memoria. Dealloco dall'heap 
[*] Distruttore di AutoElettrica invocato
[*] Distruttore di AutoDiesel invocato
