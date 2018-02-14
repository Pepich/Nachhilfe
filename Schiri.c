#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef enum { Ausgezeichnet, Gut, Ausreichend, Blind } Uebersicht;
typedef enum { Schnell, Durchschnittlich, Langsam, Hinkend } Geschwindigkeit;
typedef enum { Hoch, Mittel, Gering } Bestechlichkeit;
typedef int Patzer;

typedef struct
{
    char name[32];
    Uebersicht u;
    Geschwindigkeit g;
    Bestechlichkeit b;
    Patzer p;
} Schiri;

typedef struct
{
    Schiri *s;
    int anz; /* Anzahl der Schiris in s */
    int anzmax; /* Kapazitaet von s */
} Aufgebot;

int main( void )
{
    Aufgebot a;
    Schiri s;
    
    // Teilaufgabe a

    // Anzahl initialisieren
    // Da variable nicht Pointer: . anstatt ->
    a.s = NULL;
    a.anz = 0;
    a.anzmax = 0;

    // Teilaufgabe b
    // Schiri initialisieren
    strcpy(s.name, "Mesut"); // Strings mit strcpy kopieren, NICHT mit string = "Wert" -> strcpy(ZIEL, QUELLE)
    s.u = Ausgezeichnet;
    s.g = Durchschnittlich;
    s.b = Gering;
    s.p = 3;
    
    // Teilaufgabe c
    // Speicher anfordern
    a.s = malloc(2*sizeof(Schiri));
    // Verfügbarkeit prüfen
    // --------------------------------
    assert(a.s);
    // --------------------------------
    // Entspricht assert(a.s);
    if (!a.s)
    {
        printf("Kein Speicher verfügbar\n");
        return 1;
    }
    // -------------------------------
    
    // Kapazität auf 2 setzen
    a.anzmax = 2;

    // Mesut einfügen (kopieren aus Schiri s)
    strcpy(a.s[0].name, s.name);
    a.s[0].u = s.u;
    a.s[0].g = s.g;
    a.s[0].b = s.b;
    a.s[0].p = s.p;
    a.anz++;

    // Teilaufgabe d
    // Giovanni einfügen
    strcpy(a.s[1].name, "Giovanni");
    a.s[1].u = Blind;
    a.s[1].g = Hinkend;
    a.s[1].b = Hoch;
    a.s[1].p = 42;
    a.anz++;

    // Teilaufgabe e
    free(a.s);
    a.anz = 0;
    a.anzmax = 0;

    return 0;
}



/*
        12 34 56 78 9A BC DE F0 
        xx xx 00 00 11 11 22 22
        33 33 44 44 xx xx xx xx

        ...

        xx Sc hi ri xx xx xx xx

        int array -> sizeof(int) == 4

        array = &s

*/