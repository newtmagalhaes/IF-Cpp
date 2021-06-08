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
#include <math.h>

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

// Calcula o resto da divisão de um número por 2
char string_moduloBin(char* numDecimal, int posicaoFinal) {
    char ultimoAlg = numDecimal[posicaoFinal - 1];
    if (ultimoAlg == '0' || ultimoAlg == '2' || ultimoAlg == '4' || ultimoAlg == '6' || ultimoAlg == '8')
    {
        return '0';
    }
    else
    {
        return '1';
    }
}

// Checa se o número armazenado na string é maior que 0
char string_positiva(char* numDecimal, int posicaoFinal) {
    for (int i = 0; i < posicaoFinal; i++)
    {
        if (numDecimal[i] > '0')
        {
            return TRUE;
        }
    }
    return FALSE;
}

// Divide um número por 2
void string_dividirBin(char* numDecimal, int posicaoFinal)
{
    int acum = 0;
    for (int i = 0; i < posicaoFinal; i++)
    {
        int numConvertido = numDecimal[i] - '0';
        numConvertido += acum;
        if (numConvertido % 2 == 1)
        {
            acum = 10;
        }
        else
        {
            acum = 0;
        }
        numConvertido >>= 1;
        numDecimal[i] = numConvertido + '0';
    }
}

// Multiplica um número por 2 e retorna a parte inteira do número após a multiplicação
char string_multiplicarBin(char* numDecimal, int posicaoInicial, int posicaoFinal)
{
    int acum = 0;
    for (int i = posicaoFinal - 1; i > posicaoInicial; i--)
    {
        int numConvertido = numDecimal[i] - '0';
        int aux = (numConvertido * 2) / 10;
        numConvertido <<= 1;
        numConvertido += acum;
        // Se o resultado da multiplicação for 10 ou mais, irá armazenar para somar no próximo algarismo
        acum = aux;
        numDecimal[i] = numConvertido % 10 + '0';
    }
    return (acum > 0) + '0';
}

// Converte um número de base 10 para a base 2
char* converter_numDecimal(char* resultado, char* numDecimal) {
    int posicaoSeparador = 0;
    int posicaoFinal = strlen(numDecimal);
    int i = 0;
    
    while (numDecimal[i] != '.' && numDecimal[i] != '\0')
    {
        posicaoSeparador++;
        i++;
    }
    // Conversão da parte inteira
    i = 0;
    while (string_positiva(numDecimal, posicaoSeparador))
    {
        resultado[i] = string_moduloBin(numDecimal, posicaoSeparador);
        string_dividirBin(numDecimal, posicaoSeparador);
        i++;
    }
    resultado[i] = '\0';
    string_reversa(resultado);
    resultado[i] = '.';
    // Conversão da parte fracionária
    i++;
    // A precisão é de 20 casas decimais
    for (int j = 0; j < 80; j++) {
        resultado[i] = string_multiplicarBin(numDecimal, posicaoSeparador, posicaoFinal);
        i++;
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
    int j = 0;
    
    while (numBinario[i] != '.')
    {
        posicaoSeparador++;
        i++;
    }
    limpar_string(resultado, 100);
    // Conversão da parte inteira
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

// Formata o número para 20 casas decimais
void formatar_casas(char* numero) {
    int i = 0;
    while (numero[i] != '.')
    {
        i++;
    }
    numero[i + 21] = '\0';
}

void conversao_de_base()
{
    char numDecimal[51];
    char numConvertido[250];
    
    printf("Digite um numero decimal: ");
    scanf("%50s", numDecimal);
    printf("\nRepresentação\n");
    char numBinario[250];
    strcpy(numBinario, converter_numDecimal(numConvertido, numDecimal));
    char numOctal[90];
    strcpy(numOctal, converter_numBinario(numConvertido, numBinario, 8));
    char numHexadecimal[70];
    strcpy(numHexadecimal, converter_numBinario(numConvertido, numBinario, 16));
    formatar_casas(numBinario);
    formatar_casas(numOctal);
    printf("Binario: %s\n", numBinario);
    printf("Octal: %s\n", numOctal);
    printf("Hexadecimal: %s\n", numHexadecimal);
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
typedef struct _polinomio
{
  unsigned n_coefs;
  double *coefs;
} Polinomio;

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

/// Preenche o polinômio conforme inputs da linha de comando @param p polinômio a ser preenchido.
void ler_polinomio(Polinomio *p)
{
  for (int i = p->n_coefs - 1; i >= 0; i--)
  {
    do
    {
      printf("a%u = ", i);
      scanf("%lf", &p->coefs[i]);

      // Caso seja digitado an <= 0 OU a0 == 0
    } while ((i == p->n_coefs - 1 && p->coefs[i] <= 0)
          || (i == 0 && p->coefs[i] == 0));
  }
}

void liberar_polinomio(Polinomio *p)
{
  free(p->coefs);
  free(p);
  printf("polinomio desalocado\n");
}

// usado em _L_teorema_de_lagrange
typedef enum lagrange
{
  L0, // não modificar p
  L1, // modificar p para obter p1(x) = x^n * p(1/x);
  L2, // modificar p para obter p2(x) = p(-x)
  L3  // modificar p para obter p3(x) = x^n * p(-1/x);
} _L_Lagrange;

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
      if (fabs(p->coefs[i]) > B)
      {
        B = fabs(p->coefs[i]);
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

// deverá calcular e exibir os intervalos onde se encontram as
// raízes reais negativas e as raízes reais positivas da equação.
void teorema_de_lagrange(Polinomio *p)
{
  double Lps = _L_teorema_de_lagrange(p, L0),
         Lpi = 1 / _L_teorema_de_lagrange(p, L1),
         Lni = -_L_teorema_de_lagrange(p, L2),
         Lns = -1 / _L_teorema_de_lagrange(p, L3);

  printf("intervalo contendo as raizes reais negativas: [%lf, %lf]\n", Lni, Lns);
  printf("intervalo contendo as raizes reais positivas: [%lf, %lf]\n", Lpi, Lps);
}

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
  } while (i <= 1000 || erro < _ERRO_TOLERAVEL);

  return m;
}

int equacao_algebrica()
{
  // Solicitar o grau da equação
  unsigned n = 0;
  printf("Informe o grau da equacao: ");
  scanf("%u", &n);

  Polinomio *p = alocar_polinomio(n);
  if (p == NULL)
  {
    printf("não foi possível alocar polinomio\n");
    return -1;
  }

  // Solicitar os coeficientes an até a0
  ler_polinomio(p);

  // calcular e exibir os intervalos onde se encontram as raízes
  // reais negativas e as raízes reais positivas da equação.
  teorema_de_lagrange(p);

  // solicitar ao usuário que informe um intervalo [a, b]
  double a, b;
  printf("Informe o início do intervalo, a: ");
  scanf("%lf", &a);
  printf("Informe o final do intervalo, b: ");
  scanf("%lf", &b);

  // verificar se o polinômio tem sinais opostos nas extremidades desse intervalo.
  if (eval(p, a) * eval(p, b) < 0)
  {
    // calcular e exibir uma aproximação para uma raiz contida nesse intervalo
    double m = metodo_bissecao(p, a, b);
    printf("Aproximação para a raiz contida no intervalo: %lf\n", m);
  }
  else
  {
    // informar que o número de raízes no intervalo é par.
    printf("O numero de raizes no intervalo e par\n");
  }

  liberar_polinomio(p);
  return 0;
}

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
