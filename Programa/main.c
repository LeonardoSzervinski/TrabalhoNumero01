#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[100];
    char telefone[20];
    char curso[50];
    float nota1, nota2;
} Aluno;

int main() {
    FILE *arquivo;
    char linha[200];

    arquivo = fopen("DadosEntrada.csv", "r");
    if (arquivo == NULL) {
        perror("DadosEntrada.csv nao encontrado -> direcionar para a pasta 'output'");
        return 1;
    }

    FILE *arquivoSaida = fopen("SituacaoFinal.csv", "w");
    if (arquivoSaida == NULL) {
        perror("Erro ao gerar arquivo de saída!");
        return 1;
    }

    fprintf(arquivoSaida, "Nome,Nota Média,Situação Final\n");

    while (fgets(linha, sizeof(linha), arquivo)) {
        Aluno aluno;

        sscanf(linha, "%[^,],%[^,],%[^,],%f,%f", aluno.nome, aluno.telefone, aluno.curso, &aluno.nota1, &aluno.nota2);

        float media = (aluno.nota1 + aluno.nota2) / 2.0;

        char situacao[20];
        if (media >= 7.0) {
            strcpy(situacao, "APROVADO");
        } else {
            strcpy(situacao, "REPROVADO");
        }

        printf("Nome: %s\n", aluno.nome);
        printf("Telefone: %s\n", aluno.telefone);
        printf("Curso: %s\n", aluno.curso);
        printf("Nota 1: %.1f\n", aluno.nota1);
        printf("Nota 2: %.1f\n", aluno.nota2);
        printf("Media: %.1f\n", media);
        printf("Situacao: %s\n", situacao);
        printf("\n");

        fprintf(arquivoSaida, "%s,%.2f,%s\n", aluno.nome, media, situacao);
    }

    fclose(arquivo);
    fclose(arquivoSaida);

    return 0;
}