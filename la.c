#include <stdio.h>

int istVokal(int c)
{
  return c == 'a' || c == 'e' ||c == 'i' ||c == 'o' || c == 'u';
}

void text2la (char* text, char* latext)
{
  int i = 0;
  int verschiebung = 0;
  // Durchlaufe Zeichenkette
  // text[i] <- Aktuelles Zeichen
  for (; text[i] != '\0'; i++)
  {
    latext[i + verschiebung] = text[i];
    // Letztes Zeichen ist Vokal, aktuelles ist nicht, DANN ...
    if (istVokal(text[i]) && !istVokal(text[i+1]))
    {
      // Fuege la ein
      latext[i+1 + verschiebung] = 'l';
      latext[i+2 + verschiebung] = 'a';
      verschiebung += 2;
    }
  }
  latext[i + verschiebung] = '\0';
}

int main(void)
{
  char text[] = "schweeeer verstaendlich";
  char latext[(3 * sizeof(text)) - 2];

  printf("Original: %s\n", text);
  text2la(text, latext);
  printf("La-Sprache: %s\n", latext);

  return 0;
}
