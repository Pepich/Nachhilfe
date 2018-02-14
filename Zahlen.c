#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { GROSSGENUG = 7 };
typedef struct Knoten
{
    int zahl;
    char de[GROSSGENUG];
    char en[GROSSGENUG];
    char fr[GROSSGENUG];
    struct Knoten* next;
} Knoten;

int main(void)
{
    Knoten *zahlliste;
    Knoten *k1, *k2, *k4, *k3;

    k4 = malloc(1*sizeof(Knoten));
    k4->zahl = 4;
    strcpy(k4->de, "vier");
    strcpy(k4->en, "four");
    strcpy(k4->fr, "??");
    k4->next = NULL;

    k2 = malloc(1*sizeof(Knoten));
    k2->zahl = 2;
    strcpy(k2->de, "zwei");
    strcpy(k2->en, "two");
    strcpy(k2->fr, "??");
    k2->next = k4;

    k1 = malloc(1*sizeof(Knoten));
    k1->zahl = 1;
    strcpy(k1->de, "eins");
    strcpy(k1->en, "one");
    strcpy(k1->fr, "??");
    k1->next = k2;
    zahlliste = k1;
    
    // Teilaufgabe a
    k3 = malloc(1*sizeof(Knoten));
    k3->zahl = 3;
    strcpy(k3->de, "drei");
    strcpy(k3->en, "three");
    strcpy(k3->fr, "trois");

    // Teilaufgabe b
    k3->next = zahlliste->next->next;
    zahlliste->next->next = k3;

    // Teilaufgabe c
    Knoten *element;
    for (element = zahlliste; element->next != NULL; element = element->next)
    {
        printf("%d %s %s %s\n", element->zahl, element->de, element->en, element->fr);
    }
}