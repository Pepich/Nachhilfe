#include <stdio.h>
// .....

typedef struct Knoten {
  // ...
} Knoten;

void Ausgabe(Knoten* zahlliste)
{
  Knoten* element = zahlliste;
  
  while ( element != NULL )
  {
    // Ausgabe
    printf("%i %s %s %s\n", element->zahl, element->de, element->en, element->fr);
    element = element->next;
  }
}

int main(void)
{

  // .....

  Ausgabe(zahlliste); 
}
