#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>

#define NAME_MAX 50
// On windows, for termination with ?, uncomment this:
// #define EOF '?'

// Status enum (könnte auch #define S_getname 0 ... verwenden)
typedef enum {
    getname,
    getalpha2,
    getalpha3
} Status;

// Vorgegebenes struct Staat
typedef struct {
    char name[NAME_MAX + 1];
    char alpha2[3];
    char alpha3[4];
} Staat;

// struct Knoten
typedef struct Knoten {
    Staat staat;
    struct Knoten *next;
    struct Knoten *prev;
} Knoten;

// struct Liste
typedef struct {
    struct Knoten *first;
    struct Knoten *last;
} Liste;

// Zähle alle Elemente in Liste, gib Länge als int zurück
int len(Liste* list)
{
    int i = 0;
    for (Knoten* k = list->first; k != NULL; k = k->next) i++;
    return i;
}

// Fülle Array mit Elementen der Liste
void fill(Knoten *array[], Liste *list, int length)
{
    Knoten *k = list->first;
    for (int i = 0; i < length; i++)
        k = (array[i] = k)->next;
}

// Fülle Liste mit Elementen aus Array (in ensprechender Reihenfolge)
void assignBy(Knoten *array[], Liste *list, int length)
{
    // Sonderfall leeres Array
    if (!length)
    {
        list->first = NULL;
        list->last = NULL;
        return;
    }

    // Erstes Element zuweisen und prev auf NULL setzen
    list->first = array[0];
    array[0]->prev = NULL;

    // Sonderfall bei Länge 1, abbruch.
    if (length == 1)
    {
        list->last = array[0];
        array[0]->next = NULL;
        return;
    }
    
    // Elemente 1 bis length einsortieren
    for (int i = 1; i < length; i++)
    {
        array[i-1]->next = array[i];
        array[i]->prev = array[i-1];
    }

    // Letztes element an list->last setzen und list->last->next auf NULL setzen
    list->last = array[length-1];
    list->last->next = NULL;
}

// Bubblesort, aufsteigend
// Bubblesort, ascending
void sort_asc(Liste* list)
{
    // Wenn Liste leer, dann abbruch
    // Skip empty list
    if (list->first == NULL)
        return;
    // Länge der Liste zählen
    // Count elements in list so we know the length
    int length = len(list);
    // Hilfsarray anlegen, wenn man in einer Liste Elemente tauscht, so wird das iterieren verdammt schwer. Bei arrays ist das mit ner Zähövariable einfach.
    // Copy elements into an array, as modifying a linked list is umm. No.
    Knoten *array[length];
    // Array aus Liste befüllen
    // And fill it with the elements from the list. Custom function, just assume it works.
    fill(array, list, length);

    // Sort, ascending order
    // Fange beim ersten Element an, sortiere jedes Element bis zum letzen
    // Start at index 0, sort all elements till we arrive at the last one
    for (int i = 0; i < length; i++)
    {
        // Iteriere rückwärts bis zum Anfang des Arrays, oder bis ein kleineres Element gefunden wird
        // Go backwards from our index to the start of the array
        for (int j = i; j > 0; j--)
        {
            // Wenn das hintere Element kleiner ist, tausche
            // Swap if the 2nd element is smaller
            if (strcmp(array[j]->staat.name, array[j-1]->staat.name) < 0)
            {
                // Hilfsvariable zum Tauschen
                // Temp variable for swapping elements
                Knoten *temp = array[j];
                array[j] = array[j-1];
                array[j-1] = temp;
            }
            // Brich Schleifendurchlauf ab, sobald ein kleineres Element gefunden wurde, und springe zum nächsten Element des Arrays
            // If element isn't smaller, skip rest of the list
            else
                break;
        }
    }
    // Liste der Reihe nach mit Elementen aus Hilfsarray befüllen
    // Refill list with elements from array
    assignBy(array, list, length);
}

// Bubblesort, absteigend
void sort_desc(Liste* list)
{
    // Siehe oben
    if (list->first == NULL)
        return;
    int length = len(list);
    Knoten *array[length];
    fill(array, list, length);

    // Sort, descending order
    // Fange beim letzten Element an, sortiere jedes Element bis zum ersten
    for (int i = length - 1; i >= 0; i--)
    {
        // Iteriere vorwärts bis zum Ende des Arrays, oder bis ein größeres Element gefunden wird
        for (int j = i; j < length; j++)
        {
            // Wenn das Element kleiner ist, tausche
            if (strcmp(array[j-1]->staat.name, array[j]->staat.name) < 0)
            {
                Knoten *temp = array[j];
                array[j] = array[j-1];
                array[j-1] = temp;
            }
            else
                break;
        }
    }
    // Liste der Reihe nach mit Elementen aus Hilfsarray befüllen
    assignBy(array, list, length);
}

void print(Liste* list)
{
    // Erstes Element auswählen
    Knoten *k = list->first;
    // Falls Liste leer ist, Abbruch!
    if (k == NULL)
        return;
    // Über alle Elemente iterieren und ausgeben
    for (; k != NULL; k = k->next)
        printf("Name: %s\n2er: %s\n3er: %s\n\n", k->staat.name, k->staat.alpha2, k->staat.alpha3);
}

int main(void)
{
    // Aktuelles Zeichen
    char in;
    // Anzahl der bereits eingelesenen Zeichen
    int n = 0;
    // Momentaner Status (fängt mit einlesen des Namens an)
    Status status = getname;
    
    // Anlegen der Liste
    Liste list = {NULL, NULL};
    // Anlegen des Knotens der für Eingaben verwendet wird
    Knoten *temp;
    // Speicher reservieren
    temp = malloc(1*sizeof(Knoten));
    // Überprüfen, ob der Speicher zur Verfügung steht
    assert(temp);
    // Solange kein EOF (oder auch ?, siehe oben) gelesen wird, lies weiter
    while ((in = getchar()) != EOF)
    {
        switch (status)
        {
            case getname:
            {
                // Name des Eintrags komplett bei Leerzeichen oder Zeilenumbruch
                if (in == '\n' || in == ' ')
                {
                    // Nullzeichen schreiben
                    temp->staat.name[n] = '\0';
                    // Anzahl der gelesenen Zeichen auf 0 setzen
                    n = 0;
                    // alpha2 lesen
                    status = getalpha2;
                    break;
                
                }
                // Wenn der Eintrag zu lang ist, ignoriere weitere Eingaben
                if (n < NAME_MAX)
                {
                    // Zeichen speichern
                    temp->staat.name[n] = in;
                    // Anzahl der gelesenen Zeichen erhöhen
                    n++;
                }
                break;
            }
            case getalpha2:
            {
                // Name des Eintrags komplett bei Leerzeichen oder Zeilenumbruch
                if (in == '\n' || in == ' ')
                {
                    // Nullzeichen schreiben
                    temp->staat.alpha2[n] = '\0';
                    // Anzahl der gelesenen Zeichen auf 0 sezten
                    n = 0;
                    // alpha3 lesen
                    status = getalpha3;
                    break;
                }
                // Wenn der Eintrag zu lang ist, ignoriere weitere Eingaben
                if (n < 2)
                {
                    // Zeichen speichern
                    temp->staat.alpha2[n] = in;
                    // Anzahl der gelesenen Zeichen erhöhen
                    n++;
                }
                break;
            }
            case getalpha3:
            {
                // Name des Eintrags komplett bei Leerzeichen oder Zeilenumbruch
                if (in == '\n' || in == ' ')
                {
                    // Nullzeichen schreiben
                    temp->staat.alpha3[n] = '\0';
                    // Anzahl der gelesenen Zeichen auf 0 setzen
                    n = 0;
                    // Wenn dies das erste Element ist, speichere es als list.first
                    if (list.first == NULL)
                        list.first = temp;
                    // Da am Ende der Liste eingefügt wird, ist der Vogänger dieses Elements gleich dem momentanen Ende der Liste
                    temp->prev = list.last;
                    // Falls bereits ein Ende existiert ist unser temp Element nun der Nachfolger des Endes
                    if (list.last)
                        list.last->next = temp;
                    // Setze temp ans Ende der Liste
                    list.last = temp;
                    // Reserviere neuen Speicher für temp
                    temp = malloc(1*sizeof(Knoten));
                    // Lies namen
                    status = getname;
                    break;
                
                }
                // Wenn der Eintrag zu lang ist, ignoriere weitere Eingaben
                if (n < 3)
                {
                    // Zeichen speichern
                    temp->staat.alpha3[n] = in;
                    // Anzahl der gelesenen Zeichen erhöhen
                    n++;
                }
                break;
            }
        }
    }
    // Gib Speicher für unvollständiges Element temp wieder frei (WICHTIG: Alle Elemente, die gespeichert werden sollen MÜSSEN mit einem Leerzeichen oder Zeilenumbruch enden!)
    free(temp);

    // Gib unsortierte Liste aus
    print(&list);
    // Gib Platzhalter aus
    printf("---------------------------\n\n");
    // Sortiere Liste aufsteigend
    sort_asc(&list);
    print(&list);
    printf("---------------------------\n\n");
    // Sortiere Liste absteigend
    sort_desc(&list);
    print(&list);
    return 0;
}