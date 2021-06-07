/** Exercício Programa 1
 * Alunos:
 *  - Anilton Magalhães de Castro
 *  - Lucas Dantas Moura Ferreira
 *  - Pablo Moreira de Sousa
 *  - Rodrigo Matos Aguiar
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME_LENGTH 20
#define _ERRO_TOLERAVEL 1e-8
#define TRUE 1
#define FALSE 0

// Conversões de base - INÍCIO

// Converte um valor decimal para um algarismo em uma outra base qualquer. Vai apresentar comportamento inesperado caso o valor seja negativo ou grande o bastante
char converter_algDecimal(int algDecimal) {
    if (algDecimal <= 9) {
        return algDecimal + '0';
    } else {
        return algDecimal - 10 + 'A';
    }
}

// Modifica uma string de forma que os seus elementos estejam na posição oposta a que começaram, de acordo com o tamanho da string
void string_reversa(char* string) {
    int tamString = strlen(string);
    int i;
    for (i = 0; i < tamString / 2; i++)
    {
        char aux = string[i];
        string[i] = string[tamString - i - 1];
        string[tamString - i - 1] = aux;
    }
}

// Retorna a parte fracionária de um número
double parte_fracionaria(double valor) {
    return valor - (int) valor;
}

// Converte um número de base 10 para uma outra base
char* converter_numDecimal(char* resultado, double numDecimal, int base) {
    // Conversão da parte inteira
    int parteInteira = (int) numDecimal;
    int i = 0;
    while (parteInteira > 0)
    {
        resultado[i] = converter_algDecimal(parteInteira % base);
        parteInteira /= base;
        i++;
    }
    resultado[i] = '\0';
    string_reversa(resultado);
    resultado[i] = '.';
    // Conversão da parte fracionária
    double parteFracionaria = parte_fracionaria(numDecimal);
    i++;
    // A precisão é de 20 casas decimais
    for (int j = 0; j < 20; j++) {
        double produto = parteFracionaria * base;
        resultado[i] = converter_algDecimal((int) produto);
        parteFracionaria = parte_fracionaria(produto);
        i++;
//        printf("pf%2d: %.20f\n", i, parteFracionaria);
    }
    resultado[i] = '\0';
    return resultado;
}

// Converte um valor binário, armazenado numa string, em um algarismo em uma base potência de 2
char converter_algBinario(char* algBinario)
{
    int numConvertido = 0;
    int numDigitos = strlen(algBinario);
    for (int i = 0; i < numDigitos; i++)
    {
        // Transforma cada caractere em número e multiplica esse número por uma potência de 2 adequada
        numConvertido += (algBinario[i] - '0') * 1 << (numDigitos - i - 1);
    }
    return converter_algDecimal(numConvertido);
}

// Limpa uma string, isto é, seta todos os caracteres para 0, até mesmo os caracteres nulos
void limpar_string(char* string, int tamanhoString)
{
    for (int i = 0; i < tamanhoString; i++)
    {
        string[i] = 0;
    }
}

// Calcula e devolve o logaritmo de um número na base 2. Funciona para logaritmandos que são potências de 2
int logaritmo2(int logaritmando)
{
    int logaritmo = 0;
    while (logaritmando > 1) {
        logaritmando /= 2;
        logaritmo++;
    }
    return logaritmo;
}

// Converte um número de base 2 para uma outra base. Funciona para bases que são potências de 2
char* converter_numBinario(char* resultado, char* numBinario, int base)
{
    int numDigitosPacote = logaritmo2(base);
    int posicaoSeparador = 0;
    int posicaoFinal = strlen(numBinario);
    int i = 0;
    int j;
    
    while (numBinario[i] != '.')
    {
        posicaoSeparador++;
        i++;
    }
    limpar_string(resultado, 100);
    // Conversão da parte inteira
    i = posicaoSeparador;
    j = 0;
    do
    {
        i -= numDigitosPacote;
        char algBinario[numDigitosPacote + 1];
        for (int k = 0; k < numDigitosPacote; k++)
        {
            if (i + k >= 0)
            {
                algBinario[k] = numBinario[i + k];
            }
            else
            {
                algBinario[k] = '0';
            }
        }
        algBinario[numDigitosPacote] = '\0';
        resultado[j] = converter_algBinario(algBinario);
        j++;
    } while (i > 0);
    resultado[j] = '\0';
    string_reversa(resultado);
    resultado[j] = '.';
    // Conversão da parte fracionária
    i = posicaoSeparador + 1;
    j++;
    do
    {
        char algBinario[numDigitosPacote + 1];
        for (int k = 0; k < numDigitosPacote; k++)
        {
            if (i + k >= 0)
            {
                algBinario[k] = numBinario[i + k];
            }
            else
            {
                algBinario[k] = '0';
            }
        }
        algBinario[numDigitosPacote] = '\0';
        resultado[j] = converter_algBinario(algBinario);
        i += numDigitosPacote;
        j++;
    } while (i < posicaoFinal);
    resultado[j] = '\0';
    return resultado;
}

void conversao_de_base()
{
    double numDecimal;
    char numConvertido[100];
    
    printf("Digite um numero decimal: ");
    scanf("%lf", &numDecimal);
    printf("\nRepresentação\n");
//    printf("Decimal: %.15f\n", numDecimal);
    char numBinario[100];
    strcpy(numBinario, converter_numDecimal(numConvertido, numDecimal, 2));
    printf("Binario: %s\n", numBinario);
    printf("Octal 1o: %s\n", converter_numDecimal(numConvertido, numDecimal, 8));
    printf("Octal 2o: %s\n", converter_numBinario(numConvertido, numBinario, 8));
    printf("Hexadecimal 1o: %s\n", converter_numDecimal(numConvertido, numDecimal, 16));
    printf("Hexadecimal 2o: %s\n", converter_numBinario(numConvertido, numBinario, 16));
}

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
  printf("\nMatriz apos Metodo de Jordan:\n");
  mostrar_matriz(m, n, n + 1, aux);

  int tipo_de_SL = substituicao_retroativa(m, n, x);
  if (tipo_de_SL == 2)
  {
    printf("\nSistema Linear incompativel\n");
  }
  else
  {
    printf("\nSistema linear compativel %s\n", tipo_de_SL == 0 ? "determinado" : "indeterminado");
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
void equacao_algebrica()
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
      printf("\nConversão de Base\n");
      conversao_de_base();
      break;
    case 'E':
      printf("\nEquação Algébrica\n");
      equacao_algebrica();
      break;
    case 'S':
      printf("\nSistema Linear\n");
      sistema_linear();
      break;
    case 'F':
      printf("\nPrograma finalizado\n");
      break;
    default:
      printf("\nOpção Inválida.\n");
      break;
    };
  } while (option != 'F');

  return 0;
}
