# TODO List

## Gestione attivita' progetto PIGA

### Manto
non segarsi non segarsi non segarsi

sistemare remove
movimenti Enemy(manca chase)
costruttore brutto di character
Enemy proiettili
items

Room.hpp {   //o come si chiama
    protected:
        ...
        List listaDiProiettili, listaNemici, ...   //List è la tua lista
        ...
}

main.cpp {
    ...
    Projectile newProjectile = Projectile(parametro1, parametro2, ...);
    current_room.getListaProiettili().add(newProjectile);  //add o come si chiama
    ...
}

### HAZE
non segarsi non segarsi non segarsi

### Liam
non segarsi non segarsi non segarsi


### Brian
non segarsi non segarsi non segarsi

### GEN
https://docs.google.com/spreadsheets/d/1OLR-SXiAPb2hF5HqI_HXK4uz4xTSWIK0N3RCSS4bh_Y/edit?usp=sharing

- Makefile
- Main.cpp
- studiare progetti
- studiare strutture di programmi e classi
- ha senso tenere un inventario per il personaggio? può avere dei superpoteri? sparare in modo diverso, muoversi più veloce? o solo il numero di chiavi raccolte così quando le prende tutte si aprono le porte? o meglio, lo vogliamo fare più complesso o solo le cose base?

Haz3:
- devo confrontarmi con gli altri per capire dove mettere le singole funzioni per i colori e per ridurre il wall of text di funzioni
- inoltre credo sia meglio sistemare la dimensione della finestra in modo che venga in 16:9 o qualcosa del genere ma cresca in base alla grandezza della finestra del terminale
- dobbiamo inoltre sistemare come abbiamo scritto la funzione per gestire se il carattere è uguale a q per terminare