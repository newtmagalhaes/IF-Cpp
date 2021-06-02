/** Exercício Programa 1
 * Alunos:
 *  - Anilton Magalhães de Castro
 *  - Lucas Dantas Moura Ferreira
 *  - Pablo Moreira de Sousa
 *  - Rodrigo Matos Aguiar
*/

#include <stdio.h>
#include <stdlib.h>

#define FILENAME_LENGTH 20
#define _ERRO_TOLERAVEL 1e-8

// Conversões de base - INÍCIO
void conversao_De_Base()
{}

// Conversões de base - FIM

// Sistema Linear - INÍCIO
double **alocar_matriz(unsigned n_linhas, unsigned n_colunas)
{
  double **m = (double **)malloc(n_linhas * sizeof(double *));
  if (m == NULL)
  {
    return NULL;
  }

  for (unsigned i = 0; i < n_linhas; i++)
  {
    m[i] = (double *)calloc(n_colunas, sizeof(double));
    if (m[i] == NULL)
    {
      // Caso não consiga alocar uma linha, libera tudo.
      for (unsigned j = 0; j < i; j++)
      {
        free(m[j]);
      }
      free(m);
      return NULL;
    }
  }

  return m;
}

void mostrar_matriz(double **matriz, unsigned n_linhas, unsigned n_colunas, unsigned *map_colunas)
{
  unsigned i, j;
  // Util apenas com o vetor auxiliar retornado pelo método de jordan
  if (map_colunas != NULL)
  {
    printf("[%5.d", 0);
    for (unsigned i = 0; i < n_linhas; i++)
    {
      printf("x%d %7.d", map_colunas[i] + 1, 0);
    }
    printf("B%4.d]\n", 0);
  }

  for (i = 0; i < n_linhas; i++)
  {
    printf("[");
    for (j = 0; j < n_colunas; j++)
    {
      printf("%10.3lf", matriz[i][j]);
    }
    printf("]\n");
  }
}

void _trocar_colunas(double **matriz, unsigned n_linhas, unsigned col_a, unsigned col_b)
{
  double aux;
  for (unsigned i = 0; i < n_linhas; i++)
  {
    aux = matriz[i][col_a];
    matriz[i][col_a] = matriz[i][col_b];
    matriz[i][col_b] = aux;
  }
}

void liberar_matriz(double **matriz, unsigned n_linhas)
{
  for (unsigned i = 0; i < n_linhas; i++)
  {
    free(matriz[i]);
  }
  free(matriz);
}

unsigned *metodo_jordan(double **matriz, unsigned n_linhas)
{
  double mult;
  unsigned i, j, coluna_aux;
  // vetor auxiliar mapeia as colunas trocadas
  unsigned *aux = (unsigned *)calloc(n_linhas, sizeof(unsigned));
  if (aux == NULL)
  {
    printf("Vetor auxiliar não alocado\n");
    return NULL;
  }

  for (i = 0; i < n_linhas; i++)
  {
    aux[i] = i;
  }

  for (i = 0; i < n_linhas; i++)
  {
    // Se o pivô da linha for 0
    if (matriz[i][i] == 0)
    {
      j = i + 1;

      // busca a próxima coluna sem pivô nulo
      while (j < n_linhas && matriz[i][j] == 0)
      {
        j++;
      }

      // Se houver linha j com pivô não nulo
      // Troca as linhas i e j.
      if (j < n_linhas)
      {
        _trocar_colunas(matriz, n_linhas, i, j);
        coluna_aux = aux[i];
        aux[i] = aux[j];
        aux[j] = coluna_aux;
      }
      else
      {
        // Se não houver coluna para trocar, a
        // coluna é variável livre e pode ser zerada.
        for (unsigned l = 0; l < n_linhas; l++)
        {
          matriz[l][i] = 0;
        }
      }
    }

    // Realiza a pivotação
    if (matriz[i][i] != 0)
    {
      for (j = i + 1; j < n_linhas; j++)
      {
        mult = -matriz[j][i] / matriz[i][i];
        // colunas anteriores ao pivô já são nulas
        for (unsigned k = i; k <= n_linhas; k++)
        {
          matriz[j][k] += mult * matriz[i][k];
        }
      }
    }
  }

  return aux;
}

int substituicao_retroativa(double **m, unsigned n, double *x)
{
  double soma;
  int tipo = 0;
  for (int i = n - 1; i >= 0; i--)
  {
    soma = 0;
    // Não ocorre na primeira iteração
    for (int j = i + 1; j < n; j++)
    {
      soma += m[i][j] * x[j];
    }

    if (m[i][i] == 0)
    {
      if (m[i][n] - soma < _ERRO_TOLERAVEL)
      {
        // x[i] é variavel livre
        x[i] = 0;
        // SL indeterminado
        tipo = 1;
      }
      else
      {
        // SL incompatível
        tipo = 2;
        return tipo;
      }
    }
    else
    {
      x[i] = (m[i][n] - soma) / m[i][i];
    }
  }

  return tipo;
}

int sistema_linear()
{
  // Pedir o nome de um arquivo de texto
  char filename[FILENAME_LENGTH];
  printf("Digite o nome do arquivo: ");
  scanf("%20s", filename);

  // Abrir o arquivo de texto
  FILE *file_ptr = fopen(filename, "r");
  if (file_ptr == NULL)
  {
    printf("nao foi possivel abrir o arquivo\n");
    return -1;
  }

  unsigned n;
  fscanf(file_ptr, "%u", &n);

  // Alocar matriz para o Sistema Linear
  double **m = alocar_matriz(n, n + 1);
  if (m == NULL)
  {
    printf("nao foi possivel alocar matriz\n");
    fclose(file_ptr);
    return -1;
  }

  // Alocar vetor de soluções do Sistema Linear
  double *x = (double *)calloc(n, sizeof(double));
  if (x == NULL)
  {
    printf("nao foi possivel alocar vetor de solucoes\n");
    liberar_matriz(m, n);
    fclose(file_ptr);
    return -1;
  }

  // Ler dados do Sistema linear presentes no arquivo
  for (unsigned i = 0; i < n; i++)
  {
    for (unsigned j = 0; j < n + 1; j++)
    {
      fscanf(file_ptr, "%lf", &m[i][j]);
    }
  }

  unsigned *aux = metodo_jordan(m, n);
  printf("matriz apos metodo Jordan:\n");
  mostrar_matriz(m, n, n + 1, aux);

  int tipo_de_SL = substituicao_retroativa(m, n, x);
  if (tipo_de_SL == 2)
  {
    printf("Sistema Linear incompativel\n");
  }
  else
  {
    printf("Sistema linear compativel %s\n", tipo_de_SL == 0 ? "determinado" : "indeterminado");
    for (unsigned i = 0; i < n; i++)
    {
      printf("x%d = %10.3lf\n", aux[i] + 1, x[i]);
    }
  }

  liberar_matriz(m, n);
  fclose(file_ptr);
  free(x);
  free(aux);
  return 0;
}

// Sistema Linear - FIM

// Equações Algébricas - INÍCIO
void equacao_Algebrica()
{}

// Equações Algébricas - FIM

// Menu Principal
int main(int argc, char const *argv[])
{
  char option;
  do
  {
    printf("\n< -- Escolha a seguir a opção desejada: -- >\n");
    printf("C - Conversões de base\n");
    printf("E - Equação Algébrica\n");
    printf("S - Sistema Linear\n");
    printf("F - Finalizar programa\n");
    do
    {
      scanf("%c", &option);
    } while (option == '\n');
    // scanf("%c\n", &option);

    switch (option)
    {
    case 'C':
      printf("Conversão de Base\n");
      //conversao_De_Base();
      break;
    case 'E':
      printf("Equação Algébrica\n");
      equacao_Algebrica();
      break;
    case 'S':
      printf("Sistema Linear\n");
      sistema_linear();
      break;
    case 'F':
      printf("Programa finalizado\n");
      break;
    default:
      printf("Opção Inválida.\n");
      break;
    };
  } while (option != 'F');

  return 0;
}
