#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int contador = 0; // Variavel criada para poder percorrer os indices do Vetor
const int MAX = 100; // Constante declarada para gerar os valores randomicos

// Protótipo para funcoes
int *inversao(int tamanho, int *vetor);
void file_to_array(int *vetor, int tamanho);
void gera_arquivo(int tamanho);


int main(void)
{
    srand(time(0));

    int quantidade;
   
    printf("Informe a quantidade de valores para armazenar no vetor: ");
    scanf("%i", &quantidade);

    gera_arquivo(quantidade);

    int numeros[quantidade];

    file_to_array(numeros, quantidade);

    for(int i = 0; i<quantidade; i++)
    {
        printf("%i\n", numeros[i]);
    }
    
}

// Funcao de inversao dos valores
int *inversao(int tamanho, int *vetor)
{

    if(tamanho <= contador)
    {
        return vetor;
    }
    else
    {
        int auxilia = vetor[tamanho-1]; // A variavel auxiliar recebe o ultimo valor do vetor

        vetor[tamanho-1] = vetor[contador];

        vetor[contador] = auxilia;

        // Incrementa o contador para o proximo elemento do vetor
        contador++;

        // Chamada recursiva decrementando o tamanho do vetor ateh que tamanho <= contador;
        return inversao(--tamanho, vetor);
    }
}

// int *numeros_invertidos = inversao(quantidade, numeros);

void gera_arquivo(int tamanho)
{
    FILE *fptr;

    fptr = fopen("./numeros.csv", "w");

    // Testa a abertura do arquivo
    if(fptr == NULL)
    {
        printf("Erro para abrir o arquivo!!");
        exit(1);
    }

    // Insere numeros aleatorios no arquivo
    for (int i = 0; i < tamanho; i++)
    {
        fprintf(fptr, "%i;", rand() % MAX);
    }

    fclose(fptr);
}

void file_to_array(int *vetor, int tamanho)
{
    FILE *fptr;
    char *numeros_string, *stop = ";";

    numeros_string = (char *)malloc(tamanho * (sizeof(char))); // alocação dinâmica do espaço

    fptr = fopen("./numeros.csv", "r");

    // Testa a abertura do arquivo
    if(fptr == NULL)
    {
        printf("Erro para abrir o arquivo!!");
        exit(1);
    }

    fscanf(fptr, "%s", numeros_string);
    fclose(fptr);

    int nEncontrados = 0; // Variavel que servira de indice para o array
    for (char* aux = numeros_string; *stop == ';'; aux = stop + 1) 
    {
        vetor[nEncontrados] = (int)strtol(aux, &stop, 10); 
        nEncontrados++;
        if (stop == aux) break;
    }

    free(numeros_string);
}