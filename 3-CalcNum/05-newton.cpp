//

#include <stdio.h>
#include <stdlib.h>
#include "./polinomio.h"

int main(int argc, char const *argv[])
{
  Polinomio *p = alocar_polinomio_preenchido();
  if (p == NULL)
  {
    return 1;
  }

  mostrar_polinomio(p);
  mostrar_forma_de_horner(p);
  liberar_polinomio(p);

  return 0;
}