#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int contador = 0; // Variavel criada para poder percorrer os indices do Vetor
const int MAX = 100; // Constante declarada para gerar os valores randomicos

// Protótipo para funcoes
int *inversao(int tamanho, int vetor[]);
int *ordenacao(int tamanho, int vetor[]);
int *arquivo_para_array(int vetor[], int tamanho);
int binario(int valor);

void gera_arquivo(int tamanho);
void arquivo_invertido(int vetor[], int tamanho);
void arquivo_ordenado(int vetor[], int tamanho);
void arquivo_maiorMenor_media(int vetor[], int tamanho);
void arquivo_binario(int vetor[], int tamanho);


int main(void)
{
    srand(time(0));

    int quantidade;
   
    printf("Informe a quantidade de valores para armazenar no vetor: ");
    scanf("%i", &quantidade);

    gera_arquivo(quantidade);

    int *numeros = arquivo_para_array(numeros, quantidade);

     arquivo_binario(numeros, quantidade);
    
    arquivo_invertido(numeros, quantidade);

    arquivo_ordenado(numeros, quantidade);

    arquivo_maiorMenor_media(numeros, quantidade);
}



/* * * * * *  
 *         *
 * FUNCOES *
 *         *
 * * * * * */

int *inversao(int tamanho, int vetor[])
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

int *ordenacao(int tamanho, int vetor[])
{
    for(int i=0; i<tamanho; i++)
    {
       for(int j=i; j<tamanho; j++)
       {
           if(vetor[i] > vetor[j])
           {
               int aux = vetor[i];
               vetor[i] = vetor[j];
               vetor[j] = aux;
           }
       }
    }
    return vetor;
}

int binario(int valor)
{
    int binario = 0, resto, aux = 1;

    while(valor != 0)
    {
        // A cada iteração pega o resto da divisão do valor informado por 2;
        resto = valor%2; // resto = 0 | resto = 1 | resto = 0 | resto = 0 | resto = 0 | resto = 0 | resto = 1
        
        // Condição de parada: Divide o valor informado por 2 até que valor == 0;
        valor = valor / 2; // valor = 33 | valor = 16 | valor = 8 | valor = 4 | valor = 2 | valor = 1 | valor = 0

        // Resultado
        binario = binario + resto*aux; // binario = 0 | binario = 10 | binario = 10 | binario = 10 | binario = 10 | binario = 10 | binario = 1000010

        // Increnta a variavel aux sempre com multiplos de 10 para que seja somado posteriormente ao resultado final
        aux = aux * 10; // aux = 10 | aux = 100 |aux = 1000 | aux = 10000 | aux = 100000 | aux = 1000000 | 
    }
    return binario;

}

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

int *arquivo_para_array(int vetor[], int tamanho)
{
    FILE *fptr;
    char *numeros_string, *stop = ";";

    numeros_string = (char *)malloc(tamanho * (sizeof(int))); // alocação dinâmica do espaço

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
    for (char* aux = numeros_string; *stop == ';'; aux = stop + 1) // Laço de repetição para que o strtol continue procurando por números
    {
        vetor[nEncontrados] = (int)strtol(aux, &stop, 10); // Converte os numeros encontrados em int e envia para dentro do vetor
        nEncontrados++;
        if (stop == aux) break; // Se não ouver números após ";" para o laço;
    }

    free(numeros_string); // Libera o array alocado dinâmicamente

    return vetor;
}

void arquivo_invertido(int vetor[], int tamanho)
{
    FILE *fptr;
    int *numeros_inverso = inversao(tamanho, vetor); // chamada da função inversao que devolve um vetor com os valores na ordem inversa
    fptr = fopen("./numeros_inverso.csv", "w");

    // Testa a abertura do arquivo
    if(fptr == NULL)
    {
        printf("Erro para abrir o arquivo!!");
        exit(1);
    }


    // Lê o vetor e insere os valores no arquivo;
    for(int i=0; i<tamanho; i++)
    {
        fprintf(fptr, "%i;", numeros_inverso[i]);
    }
    fclose(fptr);
}

void arquivo_ordenado(int vetor[], int tamanho)
{
    FILE *fptr;
    int *numeros_ordenados = ordenacao(tamanho, vetor); // chamada da função ordenacao que devolve um vetor com os valores ordenados
    fptr = fopen("./numeros_ordenados.csv", "w");

    // Testa a abertura do arquivo
    if(fptr == NULL)
    {
        printf("Erro para abrir o arquivo!!");
        exit(1);
    }

    // Lê o vetor e insere os valores no arquivo;
    for(int i=0; i<tamanho; i++)
    {
        fprintf(fptr, "%i;", numeros_ordenados[i]);
    }
    fclose(fptr);

}

void arquivo_maiorMenor_media(int vetor[], int tamanho)
{
    FILE *fptr;
    int maior=vetor[0], menor=vetor[0];
    float media;

    fptr = fopen("numeros_maiorMenor_media.csv", "w");

    for(int i = 0; i<tamanho; i++)
    {
        media += vetor[i];
        if(vetor[i] > maior)
        {
            maior = vetor[i];
        }

        if(vetor[i] < menor)
        {
            menor = vetor[i];
        }
    }
    fprintf(fptr, "Maior;Menor;Media\n%i;%i;%.2f\n", maior, menor, (media/tamanho));

    fclose(fptr);
}

void arquivo_binario(int vetor[], int tamanho)
{
    FILE *fptr;

    fptr = fopen("numeros_binarios.csv", "w");

    for(int i=0; i< tamanho; i++)
    {
        fprintf(fptr, "%i;", binario(vetor[i]));
    }
}