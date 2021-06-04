// Equações polinomiais

#pragma once
#include <stdio.h>
#include <stdlib.h>

struct Polinomio
{
  unsigned n_coefs;
  double *coefs;
};

/// @return um polinômio alocado dinamicamente ou NULL caso não consiga
Polinomio *alocar_polinomio(unsigned n_termos)
{
  Polinomio *p = (Polinomio *)malloc(sizeof(Polinomio));
  if (p == NULL)
  {
    return NULL;
  }
  p->coefs = (double *)calloc(n_termos, sizeof(double));
  if (p->coefs == NULL)
  {
    free(p);
    return NULL;
  }
  p->n_coefs = n_termos;
  return p;
}

/**
 * Aloca e preenche o polinômio conforme inputs da linha de comando
 * @param p polinômio a ser preenchido.
*/
Polinomio *alocar_polinomio_preenchido()
{
  unsigned n;
  printf("Digite a quantidade de termos do polinomio: ");
  scanf("%u", &n);

  Polinomio *p = alocar_polinomio(n);
  if (p == NULL)
  {
    return NULL;
  }

  for (int i = p->n_coefs - 1; i >= 0; i--)
  {
    printf("a%u = ", i);
    scanf("%lf", &p->coefs[i]);
  }

  return p;
}

// Computa P(x)
double eval(Polinomio *p, double x);

void mostrar_polinomio(Polinomio *p)
{
  printf("P(x) = ");
  for (int i = p->n_coefs - 1; i >= 1; i--)
  {
    if (p->coefs[i] != 1)
    {
      printf(" %+5.2lf", p->coefs[i]);
    }
    printf("x");
    if (i > 1)
    {
      printf("^%u", i);
    }
  }
  printf(" %+5.2lf\n", p->coefs[0]);
}

void _horner_recursivo(Polinomio *p, unsigned i)
{
  if (i < p->n_coefs - 1)
  {
    printf("(");
    _horner_recursivo(p, i + 1);
    printf("x %+5.2lf)", p->coefs[i]);
  }
  else
  {
    printf("%+5.2lf", p->coefs[i]);
  }
}

void mostrar_forma_de_horner(Polinomio *p)
{
  printf("P(x) =");
  _horner_recursivo(p, 0);
  printf("\n");
}

void liberar_polinomio(Polinomio *p)
{
  free(p->coefs);
  free(p);
  printf("polinomio desalocado\n");
}
