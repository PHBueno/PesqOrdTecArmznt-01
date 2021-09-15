#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int contador = 0; // Variavel criada para poder percorrer os indices do Vetor
const int MAX = 100; // Constante declarada para gerar os valores randomicos
const int QNT_ARRAY = 100; // Constante declarada para a quantidade mínima de indices no array

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
void menu();

int main(void)
{
    srand(time(0));

    int quantidade, opcao, *numeros;

    do
    {
        menu();
        printf("Informe sua opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1: // Gerar Arquivo
        {
            printf("Informe a quantidade de valores para armazenar (MÍNIMO 100): ");
            scanf("%i", &quantidade);

            if(quantidade < QNT_ARRAY){quantidade = QNT_ARRAY;} // Se o valor informado for menor que o mínimo, atribui o minimo na quantidade

            gera_arquivo(quantidade);
            numeros = arquivo_para_array(numeros, quantidade);
            break;
        }
        case 2: // Gerar arquivo com os valores em binário
        {
            arquivo_binario(numeros, quantidade);
            break;
        }
        case 3: // Gerar arquivo com os valores invertidos
        {
            arquivo_invertido(numeros, quantidade);
            break;
        }
        case 4: // Gerar arquivo com maior, menor e a média dos valores
        {
            arquivo_maiorMenor_media(numeros, quantidade);
            break;
        }
        case 5: // Gerar arquivo com os valores ordenados
        {
            arquivo_ordenado(numeros, quantidade);
            break;
        }
        case 6: // Sair
        {
            printf("\n\nAté mais!! :)\n\n");
            break;
        }
        
        default:
            printf("\n\nOpção inválida, tente novamente!\n\n");
            break;
        }

    } while (opcao != 6);
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
    // O loop de fora sempre vai estar um passo atrás do for aninhado
    for(int i=0; i<tamanho; i++)
    {
       // O loop de dentro eh utilizado para compara todos os valores com o valor para índice do loop de fora
      for(int j=i; j<tamanho; j++)
       {
           // Verifica se o valor do loop de fora é maior que o restante dos valores do array
           if(vetor[i] > vetor[j])
           {
               int auxiliar = vetor[i]; // Se for maior, precisamos de uma variável auxiliar para armazenar o maior valor e mandar ele para o lugar o número menor
               vetor[i] = vetor[j]; // Então, o menor valor vai entrar no lugar no valor maior
               vetor[j] = auxiliar; // A posição do valor menor vai ser substituida pelo maior valor
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

    printf("\n\nArquivo gerado com sucesso!!\n\n");
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
    printf("\n\nArquivo inverso gerado com sucesso!!\n\n");
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

    printf("\n\nArquivo ordenado gerado com sucesso\n\n");

}

void arquivo_maiorMenor_media(int vetor[], int tamanho)
{
    FILE *fptr;
    int maior=vetor[0], menor=vetor[0];
    float media;

    fptr = fopen("numeros_maiorMenor_media.csv", "w");

    if(fptr == NULL)
    {
        printf("Erro para abrir o arquivo!!");
        exit(1);
    }

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

    printf("\n\nArquivo com: Maior, Menor e Médida Gerado com sucesso\n\n");
}

void arquivo_binario(int vetor[], int tamanho)
{
    FILE *fptr;

    fptr = fopen("numeros_binarios.csv", "w");

    if(fptr == NULL)
    {
        printf("Erro para abrir o arquivo!!");
        exit(1);
    }

    for(int i=0; i< tamanho; i++)
    {
        fprintf(fptr, "%i;", binario(vetor[i]));
    }
    fclose(fptr);
    printf("\n\n!!Arquivo Binário Gerado com sucesso!!\n\n");
}

void menu()
{
    printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf("1 - Gerar arquivo \n2 - Converter para Binário\n3 - Inverter Ordem\n4 - Achar Maior e Menor valor\n5 - Ordenar Sequencia\n6 - Sair");
    printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
}