/*---------------------------------------------------------------------------------
  "Criar um CRUD na linguagem C para cadastrar dados de alunos e os cursos que eles fazem
    1- O programa deverá cadastrar os seguintes dados: matricula do aluno, cpf, data de nascimento, email, telefone, endereço, sexo, curso que está fazendo, exemplo: computação, física e etc.
    2- O programa tem a fução de listar todos os alunos e o curso que ele faz.
    3- Fazer busca de um aluno pelo matricula.
    4- Alterar cadastro de um aluno pela matrícula.
    5- Remover cadastro de um aluno.
-------------------------------------------------------------------------------------*/

/* Membros: Rosana Celine Pinheiro Damaceno,  Laís Carvalho Coutinho,
  Thaís Araújo de Paiva.
*/

#ifdef __WIN32
#define limpar_tela "cls"
#else
#define limpar_tela "clear"
#endif

// inclusão de bibliotecas
#include <unistd.h> //para funcoes de sleep
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//RENOMECOES

typedef struct aluno TAluno;

struct aluno {
  int matricula;
  char nasc[11], email[30], endereco[50], sexo[2], telefone[20], curso[50],
      cpf[16];
};

// PROTOTIPOS
char menu();
void menu_alteracao(int matricula);
int existe_aluno(FILE *arq_alunos, int matricula);
void cadastrar_aluno(); 
void alterar_aluno();
void listar_alunos(); 
void buscar_aluno();
void remover_aluno();
void limpar_buffer();

// MAIN
int main(int argc, char *argv[]) {
  char opcao;

  while (1) {
    opcao = menu();     // Menu de Opcoes
    if (opcao == '1') { // Insere um cadastro
      cadastrar_aluno();
    } else if (opcao == '2') { // Lista todos os alunos
      listar_alunos();
    } else if (opcao == '3') { // Busca aluno pela matricula
      buscar_aluno();
    } else if (opcao == '4') { // Altera cadastro
      alterar_aluno();
    } else if (opcao == '5') { // Remove aluno
      remover_aluno();
    } else if (opcao == '0') { // Sair do programa
      break;
    } else {
      printf("\nOpção inválida! Pressione <Enter> para continuar...");
      limpar_buffer();
    }
    limpar_buffer();
    system(limpar_tela);
  }
  printf("\n\nAté breve!!\n");

  return 0;
}


// EXIBE MENU E RETORNA A OPCAO ESCOLHIDA PELO USUARIO
char menu() {
  char opcao[2];
  printf("---------------------- Menu de Opcoes ----------------------\n\n");
  printf("\t1 - Cadastrar um aluno.\n");
  printf("\t2 - Listar todos os alunos.\n");
  printf("\t3 - Fazer busca de um aluno pelo matrícula.\n");
  printf("\t4 - Alterar cadastro de um aluno pela matrícula.\n");
  printf("\t5 - Remover cadastro de um aluno.\n");
  printf("\t0 - Sair\n\n");
  printf("Digite o numero da opção: ");
  scanf("%1s%*c", opcao); // o *c pega o Enter e descarta 

  // se chegou aqui, é porque a opção é válida
  return opcao[0];
}

// MENU ALTERACOES
void menu_alteracao(int matricula){
  char opcao[2];
  TAluno aluno;
  
  printf("Voce desejaria modificar que informação do cadastro do aluno \"%d\":\n\n", matricula);
  printf("\tA - CPF.\n");
  printf("\tB - Data de Nascimento.\n");
  printf("\tC - Email.\n");
  printf("\tD - Telefone.\n");
  printf("\tE - Endereço.\n");
  printf("\tF - Sexo.\n");
  printf("\tG - Curso.\n");
  printf("\t0 - Sair do menu de alteração.\n");
}

void limpar_buffer(){
  int ch;
  while((ch = fgetc(stdin)) != EOF && ch != '\n');
}

// VERIFICA SE A MATRICULA EXISTE NO SISTEMA
// retorna 0 se NÃO existe e 1 caso contrário
int existe_aluno(FILE *arq_alunos, int matricula) {
  // vai para o início do arquivo
  rewind(arq_alunos);

  TAluno aluno;
  // loop para percorrer o arquivo
  while (1) {
    // fread retorna o número de elementos lidos com sucesso
    size_t result = fread(&aluno, sizeof(TAluno), 1, arq_alunos);

    // se for 0, é porque não há mais elemento, então sai do loop
    if (result == 0) break;

    // verifica se a matricula é igual
    if (aluno.matricula == matricula)
      return 1;
  }

  // se chegou aqui é porque NÃO existe o aluno, então retorna 0
  return 0;
}

// CADASTRA ALUNO NO ARQUIVO
void cadastrar_aluno() {
  // abre o arquivo para escrita
  // um arquivo binária para leitura e escrita
  FILE *arq_alunos = fopen("alunos.bin", "a+b");

  // testa a abertura do arquivo
  if (arq_alunos == NULL) {
    printf("\nFalha ao abrir arquivo(s)!\n");
    exit(1); 
  }
  
  TAluno aluno;
  int matricula;

  // ^\n indica para pegar até a quebra de linha (enter)
  // %*c descarta o enter

  while(1){
    printf("\nMatricula do aluno: ");
    scanf("%d", &matricula);
    if(existe_aluno(arq_alunos, matricula) == 1)
      printf("\nMatrícula ja existente. \nPor favor escolha outra matrícula.\n");
    else{
      aluno.matricula = matricula;
      break;
    }
  }
  limpar_buffer();
  
  printf("CPF do aluno: ");
  scanf(" %[^\n]s", aluno.cpf);
  limpar_buffer();

  printf("Data de nascimento do aluno (DD/MM/AAAA): ");
  scanf(" %[^\n]s", aluno.nasc);
  limpar_buffer();

  printf("Email do aluno: ");
  scanf(" %[^\n]s", aluno.email);
  limpar_buffer();

  printf("Telefone do aluno: ");
  scanf(" %[^\n]s", aluno.telefone);
  limpar_buffer();

  printf("Endereço do aluno: ");
  scanf(" %[^\n]s", aluno.endereco);
  limpar_buffer();

  printf("Sexo do aluno (F/M): ");
  scanf(" %[^\n]s", aluno.sexo);
  limpar_buffer();

  printf("Curso do aluno: ");
  scanf(" %[^\n]s", aluno.curso);
  limpar_buffer();

  // se o ponteiro não estiver no final do arquivo nada é escrito
  fseek(arq_alunos, 0, SEEK_END);
  
  fwrite(&aluno, sizeof(TAluno), 1, arq_alunos);

  fclose(arq_alunos);

  printf("\nAluno \"%d\" cadastrado com sucesso!\n", aluno.matricula);
  
  printf("\n\nPressione <Enter> para continuar...");
}

// ALTERA ALGUMA INFORMACAO DO ALUNO
void alterar_aluno() {
  int matricula = 0;
  TAluno aluno;

  // rb+ abre para leitura/atualização
  FILE *arq_alunos = fopen("alunos.bin", "rb+"); 

  // se não conseguiu abrir, então cria o arquivo
  // wb+ abre para escrita/atualização (cria o arquivo se ele NÃO existir)
  if (arq_alunos == NULL) {
    arq_alunos = fopen("alunos.bin", "wb+");
    if (arq_alunos == NULL) {
      printf("\nFalha ao criar arquivo(s)!\n");
      exit(1); // aborta o programa
    }
  }

  printf("\nDigite a matrícula do aluno: ");
  scanf("%d", &matricula);

  // verifica se existe aluno com a matricula
  if (existe_aluno(arq_alunos, matricula) == 1) {
    char op[2];
    printf("\nMatrícula encontrada.\n");
    printf("\nIndo para o menu de alteração...\n");
    sleep(2);
    limpar_buffer();
    while(1){
      system(limpar_tela);
      menu_alteracao(matricula);
      printf("\n\tDigite uma opção: ");
      scanf("%1s%*c", op); // o *c pega o Enter e descarta
      char opcao = op[0];
      if(opcao == 'A' || opcao == 'a') {
        printf("\nDigite o novo cpf do aluno \"%d\": ", matricula);
        char cpf[16];
        scanf(" %[^\n]s", cpf); 
        strcpy(aluno.cpf, cpf);
        fseek(arq_alunos, -sizeof(TAluno), SEEK_CUR);
        fwrite(&aluno, sizeof(TAluno), 1, arq_alunos);
      } else if(opcao == 'B' || opcao == 'b'){
        printf("\nDigite a nova data de nascimento do aluno \"%d\": ", matricula);
        char nasc[11];
        scanf(" %[^\n]s", nasc);
        strcpy(aluno.nasc, nasc);
        fseek(arq_alunos, -sizeof(TAluno), SEEK_CUR);
        fwrite(&aluno, sizeof(TAluno), 1, arq_alunos);
      } else if(opcao == 'C' || opcao == 'c'){
        printf("\nDigite o novo email do aluno \"%d\": ", matricula);
        char email[30];
        scanf(" %[^\n]s", email);
        strcpy(aluno.email, email);
        fseek(arq_alunos, -sizeof(TAluno), SEEK_CUR);
        fwrite(&aluno, sizeof(TAluno), 1, arq_alunos);
      } else if(opcao == 'D' || opcao == 'd'){
        printf("\nDigite o novo telefone do aluno \"%d\": ", matricula); 
        char telefone[20];
        scanf(" %[^\n]s", telefone);
        strcpy(aluno.telefone, telefone);
        fseek(arq_alunos, -sizeof(TAluno), SEEK_CUR);
        fwrite(&aluno, sizeof(TAluno), 1, arq_alunos);
      } else if(opcao == 'E' || opcao == 'e'){ 
        printf("\nDigite o novo endereço do aluno \"%d\": ", matricula);
        char endereco[50];
        fgets(endereco, 50, stdin);
        endereco[strcspn(endereco, "\n")] = '\0';
        strcpy(aluno.endereco, endereco);
        fseek(arq_alunos, -sizeof(TAluno), SEEK_CUR);
        fwrite(&aluno, sizeof(TAluno), 1, arq_alunos);
      } else if(opcao == 'F' || opcao == 'f'){ 
        printf("\nDigite o novo sexo do aluno \"%d\" (F/M): ", matricula);
        char sexo[2];
        fgets(sexo, 2, stdin);
        sexo[strcspn(sexo, "\n")] = '\0';
        strcpy(aluno.sexo, sexo);
        fseek(arq_alunos, -sizeof(TAluno), SEEK_CUR);
        fwrite(&aluno, sizeof(TAluno), 1, arq_alunos);
      } else if(opcao == 'G' || opcao == 'g'){
        printf("\nDigite o novo curso do aluno \"%d\": ", matricula);
        char curso[50];
        scanf(" %[^\n]s", curso);
        strcpy(aluno.curso, curso);
        fseek(arq_alunos, -sizeof(TAluno), SEEK_CUR);
        fwrite(&aluno, sizeof(TAluno), 1, arq_alunos);
      } else if(opcao == '0'){
        printf("\nSaindo do menu de alteração...\n");
        break;
      } else 
        printf("\nOpção inválida!\n");
      limpar_buffer();
      printf("\nCadastro \"%d\" atualizado com sucesso!\n", matricula);
      fseek(arq_alunos, matricula * sizeof(TAluno), SEEK_SET);
      } 
  } 
  else printf("\n\nNenhum aluno com a matrícula \"%d\" encontrado.\n\n", matricula);

  // fecha os arquivos
  fclose(arq_alunos);

  printf("\nPressione <Enter> para continuar...");
  limpar_buffer();
}

// LISTA/EXIBE OS ALUNOS EXISTENTES
void listar_alunos() {
  // rb => abre arquivo binário para leitura apenas
  FILE *arq_alunos = fopen("alunos.bin", "rb");

  // testa a abertura do arquivo
  if (arq_alunos == NULL) {
    printf("\nFalha ao abrir arquivo(s) ou ");
    printf("Nenhum aluno cadastrado.\n");
    printf("\nPressione <Enter> para continuar...");
    limpar_buffer(); 
    return;
  }

  // variável que indica se encontrou pelo menos 1 aluno
  int encontrou_alunos = 0;
  TAluno aluno;

  printf("\n\nListando todos os alunos...\n");
  // loop para percorrer o arquivo
  while (1) {
    // fread retorna o número de elementos lidos com sucesso
    size_t result = fread(&aluno, sizeof(TAluno), 1, arq_alunos);

    // se for 0, é porque não há mais elemento, então sai do loop
    if (result == 0) break;

    // atualiza a variável indicando que encontrou
    // pelo menos um cliente
    encontrou_alunos = 1;

    // mostra os dados do aluno
    printf("\n\nMatrícula do aluno: %d", aluno.matricula);
    printf("\nCPF do aluno: %s", aluno.cpf);
    printf("\nData de nascimento do aluno: %s", aluno.nasc);
    printf("\nEmail do aluno: %s", aluno.email);
    printf("\nTelefone do aluno: %s", aluno.telefone);
    printf("\nEndereço do aluno: %s", aluno.endereco);
    printf("\nSexo do aluno: %s", aluno.sexo);
    printf("\nCurso do aluno: %s", aluno.curso);
  }

  if (encontrou_alunos == 0)
    printf("\n\nNenhum aluno cadastrado.\n");

  fclose(arq_alunos);

  printf("\n\nPressione <Enter> para continuar...");
}


// BUSCA ALUNO E EXIBE SUAS INFORMACOEs
void buscar_aluno() {
  int matricula;
  int encontrou_aluno = 0;

  // rb+ => abre para leitura somente
  FILE *arq_alunos = fopen("alunos.bin", "rb");

  // testa a abertura do arquivo
  if (arq_alunos == NULL) {
    printf("\nFalha ao abrir arquivo(s)!\n");
    exit(1); // aborta o programa
  }

  printf("\nDigite a matrícula do aluno: ");
  scanf("%d", &matricula);

  // loop para percorrer o arquivo
  if(existe_aluno(arq_alunos, matricula)){
    TAluno aluno;
    rewind(arq_alunos); // Volta para o início do arquivo
    
    while (1) {   
      // fread retorna o número de elementos lidos com sucesso
      size_t result = fread(&aluno, sizeof(TAluno), 1, arq_alunos); 

      if (result == 0) 
        break; // se for 0, é porque não há mais elemento, então sai do loop

      if (aluno.matricula == matricula){
        printf("\nMatrícula do aluno: %d", aluno.matricula);
        printf("\nCPF do aluno: %s", aluno.cpf);
        printf("\nData de nascimento do aluno: %s", aluno.nasc);
        printf("\nEmail do aluno: %s", aluno.email);
        printf("\nTelefone do aluno: %s", aluno.telefone);
        printf("\nEndereço do aluno: %s", aluno.endereco);
        printf("\nSexo do aluno: %s", aluno.sexo);
        printf("\nCurso do aluno: %s\n\n", aluno.curso);
        encontrou_aluno = 1;
        break;
      }
    } 
  } 
  
  if (encontrou_aluno == 0)
    printf("\n\nNenhum aluno com a matrícula \"%d\" encontrado.\n\n", matricula);

  fclose(arq_alunos); 
  
  printf("\nPressione <Enter> para continuar...");
  limpar_buffer(); 
}


// REMOVE CADASTRO DO ALUNO
void remover_aluno() {
  int matricula;

  printf("\nDigite a matrícula do aluno: ");
  scanf("%d", &matricula);

  fseek(stdin, 0, SEEK_END); 

  // rb abre para leitura (o arquivo deve existir)
  FILE *arq_alunos = fopen("alunos.bin", "rb");

  if (arq_alunos == NULL) {
    printf("\nFalha ao abrir arquivo(s)!\n");
    exit(1); // aborta o programa
  }
  
  // verifica se o aluno existe
  if (existe_aluno(arq_alunos, matricula) == 1) {
    
    char nasc[11], email[30], endereco[50], sexo[2], telefone[20], curso[50], cpf[16];
    // abre um novo arquivo temporário
    FILE *arq_temp = fopen("temp_alunos.bin", "a+b");
    if (arq_temp == NULL) {
      printf("\nFalha ao criar arquivo temporário!\n");
      fclose(arq_alunos);
      exit(1); // aborta o programa
    }

    rewind(arq_alunos); // vai para o início do arquivo

    TAluno aluno;
    
    while (1) {
      // loop para percorrer o arquivo
      // fread retorna o número de elementos lidos com sucesso
      
      size_t result = fread(&aluno, sizeof(TAluno), 1, arq_alunos);
      // se for 0, é porque não há mais elemento, então sai do loop
      if (result == 0) break;

      // só copia pro novo arquivo se for diferente
      if (aluno.matricula != matricula) {
        // escreve no arquivo temporário
        fwrite(&aluno, sizeof(TAluno), 1, arq_temp);
      } 
      else{
      strncpy(nasc, aluno.nasc, 11);
      strncpy(email, aluno.email, 30);
      strncpy(endereco, aluno.endereco, 50);
      strncpy(sexo, aluno.sexo, 2);
      strncpy(telefone, aluno.telefone, 20);
      strncpy(curso, aluno.curso, 50);
      strncpy(cpf, aluno.cpf, 16);
      }
    }
    
    // antes de fazer operações de remover arquivo e renomear,
    // é preciso fechar os dois arquivos
    fclose(arq_alunos);
    fclose(arq_temp);

    // depois de fechar o arquivo, então tentamos remover
    if (remove("alunos.bin") != 0)
      printf("\nErro ao deletar o arquivo \"alunos.bin\"\n");
    else {
      // renomeia o arquivo
      int r = rename("temp_alunos.bin", "alunos.bin");
      if (r != 0) {
        printf("\nPermissão negada para renomear o arquivo!\n");
        printf("Feche esse programa bem como o arquivo \"temp_alunos.bin\" e "
               "renomeie manualmente para \"alunos.bin\"\n");
      } 
      else
        printf("\nAluno \"%d\" removido com sucesso!\n", matricula);
    }
  } 
  else 
    printf("\n\nNenhum aluno com a matrícula \"%d\" encontrado.\n\n", matricula);
  
  printf("\nPressione <Enter> para continuar...");
  limpar_buffer();
}

//==================================================================================;
