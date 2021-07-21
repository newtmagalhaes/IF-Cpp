//

#include <stdio.h>
#include <stdlib.h>
#include "./polinomio.h"

int main(int argc, char const *argv[])
{
  unsigned n = 0;
  scanf("%u", &n);
  Polinomio *p = alocar_polinomio(n);
  if (p == NULL)
  {
    return 1;
  }

  mostrar_polinomio(p);
  mostrar_forma_de_horner(p);
  liberar_polinomio(p);

  return 0;
}