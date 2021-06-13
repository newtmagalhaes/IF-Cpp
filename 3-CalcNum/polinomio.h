// Equações polinomiais

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define _ERRO_TOLERAVEL 1e-8
#define _MAX_ITER 1000

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
 * Preenche o polinômio conforme inputs da linha de comando
 * @param p polinômio a ser preenchido.
*/
void ler_polinomio(Polinomio *p)
{
  for (int i = p->n_coefs - 1; i >= 0; i--)
  {
    printf("a%u = ", i);
    scanf("%lf", &p->coefs[i]);
  }
}

// Executa o Método de Briot-Ruffini
double metodo_briot_ruffini(Polinomio *p, double x, unsigned i)
{
  if (i == p->n_coefs - 1)
  {
    return p->coefs[i];
  }
  else
  {
    return x * metodo_briot_ruffini(p, x, i + 1) + p->coefs[i];
  }
}

// Computa P(x)
double eval(Polinomio *p, double x)
{
  return metodo_briot_ruffini(p, x, 0);
}

/**
 *  Executa o método da bisseção
 * @param p um polinômio para se determinar uma raíz;
 * @param a o limite inferior do intervalo;
 * @param b o limite superior do intervalo;
 * @return m, uma raíz aproximada do polinômio contida dentro do intervalo
*/
double metodo_bissecao(Polinomio *p, double a, double b)
{
  int i = 0;
  double m, erro;
  do
  {
    i++;
    m = (a + b) / 2;
    erro = (b - a) / 2;
    if (eval(p, m) == 0)
    {
      return m;
    }
    else if (eval(p, m) * eval(p, a) < 0)
    {
      b = m;
    }
    else
    {
      a = m;
    }
  } while (i <= _MAX_ITER || erro < _ERRO_TOLERAVEL);

  return m;
}

// usado em _L_teorema_de_lagrange
typedef enum lagrange
{
  L0, // não modificar p
  L1, // modificar p para obter p1(x) = x^n * p(1/x);
  L2, // modificar p para obter p2(x) = p(-x)
  L3  // modificar p para obter p3(x) = x^n * p(-1/x);
} _L_Lagrange;

// modificar p para obter x^n * p(1/x);
void _inverter_ordem_de_coeficientes(Polinomio *p)
{
  int n = p->n_coefs - 1;
  double aux;
  for (int i = 0; i < n / 2; i++)
  {
    aux = p->coefs[i];
    p->coefs[i] = p->coefs[n - i];
    p->coefs[n - i] = aux;
  }
}

// modificar p para obter p(-x)
void _simetrico_indices_impares(Polinomio *p)
{
  for (int i = 1; i < p->n_coefs; i += 2)
  {
    p->coefs[i] = -p->coefs[i];
  }
}

double _L_teorema_de_lagrange(Polinomio *p, _L_Lagrange l)
{
  // Fazer alterações necessárias conforme o retorno desejado
  if (l == L3 || l == L2)
  {
    // (alterar o sinal dos coeficientes de índice ímpar)
    _simetrico_indices_impares(p);
  }
  if (l == L3 || l == L1)
  {
    // (inverter a ordem dos coeficientes)
    _inverter_ordem_de_coeficientes(p);
  }

  int n = p->n_coefs - 1,
      desfazer_oposicao = 0;
  // SE an < 0, p(x) é redefinido para -p(x)
  if (p->coefs[n] < 0)
  {
    desfazer_oposicao = 1;
    for (int i = 0; i < p->n_coefs; i++)
    {
      p->coefs[i] = -p->coefs[i];
    }
  }

  // Definir k e B
  int k = 0;    // o maior índices dos coeficientes negativos;
  double B = 0, // o módulo do menor coeficiente negativo;
      an = p->coefs[n];
  for (int i = p->n_coefs - 1; i >= 0; i--)
  {
    if (p->coefs[i] < 0)
    {
      if (i > k)
      {
        k = i;
      }
      if (abs(p->coefs[i]) > B)
      {
        B = abs(p->coefs[i]);
      }
    }
  }

  // Desfazendo alterações recuperando o polinômio original
  if (desfazer_oposicao)
  {
    for (int i = 0; i < p->n_coefs; i++)
    {
      p->coefs[i] = -p->coefs[i];
    }
  }
  if (l == L3 || l == L1)
  {
    // (inverter a ordem dos coeficientes)
    _inverter_ordem_de_coeficientes(p);
  }
  if (l == L3 || l == L2)
  {
    // (alterar o sinal dos coeficientes de índice ímpar)
    _simetrico_indices_impares(p);
  }

  return 1 + pow(B / an, 1.0 / (n - k));
}

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
