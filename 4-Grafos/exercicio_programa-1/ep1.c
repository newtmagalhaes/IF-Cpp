/** Exercício programa 1
 * Alunos:
 *  - Anilton Magalhães de Castro
 *  - Gustavo Alves de Vasconcelos
 *  - Lucas Agostinho Fernandes
 *  - Vitor Bryan Melo de Lima
 * 
 * Orientações de Código:
 *  - O grafo é implementado como uma matriz de adjacências;
 *  - O tipo Resposta contém o vetor anterior e o vetor de custos
 *      para chegar a cada vértice, que são preenchidos ao longo
 *      da execução do algoritmo de Dijkstra.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define FILENAME_LENGTH 20

/* Grafos - INÍCIO */
typedef struct grafo
{
  int n_vertices;
  double **matriz_adjacente;
} Grafo;

// Aloca dinamicamente um grafo de matriz de adjacência
Grafo *criar_grafo(int n_vertices)
{
  Grafo *g = (Grafo *)malloc(sizeof(Grafo));
  if (g == NULL)
  {
    return NULL;
  }

  double **matriz = (double **)malloc(n_vertices * sizeof(double *));
  if (matriz == NULL)
  {
    free(g);
    return NULL;
  }

  for (int i = 0; i < n_vertices; i++)
  {
    matriz[i] = (double *)malloc(n_vertices * sizeof(double));
    if (matriz[i] == NULL)
    {
      for (int j = 0; j < i; j++)
      {
        free(matriz[j]);
      }
      free(matriz);
      free(g);
      return NULL;
    }

    for (int k = 0; k < n_vertices; k++)
    {
      matriz[i][k] = -1;
    }
  }

  g->n_vertices = n_vertices;
  g->matriz_adjacente = matriz;

  return g;
}

// Realiza a desalocação das partes do grafo
void liberar_grafo(Grafo *g)
{
  for (int i = 0; i < g->n_vertices; i++)
  {
    free(g->matriz_adjacente[i]);
  }
  free(g->matriz_adjacente);
  free(g);
}
/* Grafos - FIM */

/* Solução - INÍCIO */
// Contém o vetor anterior e o vetor de custos
// utilizados pelo algoritmo de dijkstra
typedef struct resposta
{
  int length,
      *anterior;
  double *custo;
} Resposta;

// Aloca dinamicamente a struct resposta
Resposta *alocar_resposta(int len)
{
  Resposta *r = (Resposta *)malloc(sizeof(Resposta));
  if (r == NULL)
  {
    return NULL;
  }

  r->length = len;
  r->anterior = (int *)calloc(len, sizeof(int));
  if (r->anterior == NULL)
  {
    free(r);
    return NULL;
  }

  r->custo = (double *)calloc(len, sizeof(double));
  if (r->custo == NULL)
  {
    free(r->anterior);
    free(r);
    return NULL;
  }

  return r;
}

// Mostra o arco que chega no vertice anterior ao do parâmetro
// E mostra o arco que chega no vertice do parâmetro
void mostrar_caminho_recursivo(Resposta *r, int vertice)
{
  // A recursão para quando chega no vertice inicial (start)
  // na posição do vertice inicial não há anterior (r->anterior[start] == -1)
  if (r->anterior[vertice] != -1)
  {
    mostrar_caminho_recursivo(r, r->anterior[vertice]);
    printf(" (%d -> %d)", r->anterior[vertice] + 1, vertice + 1);
  }
}

// Dado uma resposta já computada pelo algoritmo de dijkstra
// Imprime na tela com base no vetor anterior já definido
void mostrar_caminho_minimo(Resposta *r, int start, int stop)
{
  if (r->custo[stop - 1] == INFINITY)
  {
    printf("Nao ha caminho do vertice %d para o vertice %d:\n", start, stop);
    printf("O custo para chegar no vertice %d entao e: %lf\n", stop, INFINITY);
  }
  else
  {
    printf("Caminho minimo do vertice %d para o vertice %d:\n", start, stop);
    mostrar_caminho_recursivo(r, stop - 1);
    printf("\nO custo para chegar no vertice %d entao e: %10.3lf\n", stop, r->custo[stop - 1]);
  }
}

// Desaloca dinamicamente a resposta e suas partes
void liberar_resposta(Resposta *r)
{
  free(r->custo);
  free(r->anterior);
  free(r);
}
/* Solução - FIM */

/* Algoritmo de Dijkstra - INÍCIO */
Resposta *algoritmo_dijkstra(Grafo *g, int start, int stop)
{
  // Aloca resposta a ser computada
  Resposta *r = alocar_resposta(g->n_vertices);
  if (r == NULL)
  {
    return NULL;
  }

  // Inicializar resposta
  for (unsigned i = 0; i < g->n_vertices; i++)
  {
    r->custo[i] = INFINITY;
    r->anterior[i] = -1;
  }
  r->custo[start - 1] = 0;

  // Aloca vetor de booleanos marcando para
  // quais vértices já se conhece o caminho mínimo
  bool *z = (bool *)calloc(g->n_vertices, sizeof(bool));
  if (z == NULL)
  {
    liberar_resposta(r);
    return NULL;
  }

  // Posição do vértice inicial no grafo
  int v_aux = start - 1;
  double custo_min_aux = 0;

  // Enquanto v_aux não for o vértice de destino
  // EE o custo mínimo não for INFINITO
  while (v_aux != stop - 1
         && custo_min_aux != INFINITY)
  {
    custo_min_aux = INFINITY;
    for (unsigned i = 0; i < g->n_vertices; i++)
    {
      // Se o vértice não está em Z
      // EE o custo para chegar nele for o menor dentre os demais custos
      if (z[i] == false
          && r->custo[i] >= 0
          && r->custo[i] < custo_min_aux)
      {
        custo_min_aux = r->custo[i];
        // define-se novo vértice a ser inserido em Z
        v_aux = i;
      }
    }

    // Se v_aux não for o vértice de destino
    // EE o custo mínimo não for INFINITO
    if (v_aux != stop - 1
        && custo_min_aux != INFINITY)
    {
      // Para cada vértice i do grafo g
      for (unsigned i = 0; i < g->n_vertices; i++)
      {
        // Se o vértice i não estiver em Z
        // EE existir um arco de v_aux -> i
        // EE (o custo de chegar a v_aux + o custo desse arco) < o custo de chegar a i
        if (z[i] == false
            && g->matriz_adjacente[v_aux][i] != -1
            && r->custo[v_aux] + g->matriz_adjacente[v_aux][i] < r->custo[i])
        {
          // Atualiza os valores dos vétores de custo e anteriores
          r->custo[i] = r->custo[v_aux] + g->matriz_adjacente[v_aux][i];
          r->anterior[i] = v_aux;
        }
      }
      // Adiciona v_aux a Z
      z[v_aux] = true;
    }
  }

  return r;
}
/* Algoritmo de Dijkstra - FIM */

int main(int argc, char const *argv[])
{
  //receba pela linha de comando o nome de um arquivo que contém a descrição de um digrafo.
  char filename[FILENAME_LENGTH];
  printf("Digite o nome do arquivo: ");
  scanf("%20s", filename);

  // Abre o arquivo de nome passado pela linha de comando
  printf("\nfilename: %s\n", filename);
  FILE *arq = fopen(filename, "r");
  if (arq == NULL)
  {
    printf("Arquivo nao foi aberto\n");
    return -1;
  }

  // Criar Grafo com os dados extraídos do arquivo
  int n, m, s, t;
  fscanf(arq, "%d %d %d %d", &n, &m, &s, &t);

  Grafo *g = criar_grafo(n);
  if (g == NULL)
  {
    printf("Grafo nao foi criado\n");
    fclose(arq);
    return -1;
  }

  int u, v;
  double c;
  for (int i = 0; i < m; i++)
  {
    fscanf(arq, "%d %d %lf", &u, &v, &c);
    g->matriz_adjacente[u - 1][v - 1] = c;
  }

  // Criar Resposta utilizando o Algoritmo de Dijkstra
  Resposta *r = algoritmo_dijkstra(g, s, t);
  if (r == NULL)
  {
    printf("Nao foi possivel alocar resposta\n");
    liberar_grafo(g);
    fclose(arq);
    return -1;
  }

  // exibir um caminho de custo mínimo de s a t com base na Resposta.
  mostrar_caminho_minimo(r, s, t);

  // Desalocar variáveis dinâmicas (Grafo, Resposta, etc...)
  liberar_resposta(r);
  liberar_grafo(g);
  fclose(arq);

  return 0;
}
