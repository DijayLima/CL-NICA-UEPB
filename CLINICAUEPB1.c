#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>


typedef struct{
    char rua[20], numero[6], bairro[20], cep[12], estado[15];
}END;

typedef struct{
    int dia, mes, ano;
}DATNAS;

typedef struct{
    char nome[30];
    DATNAS dn;
    int codpaciente, cpf;
    END endereco;
}PACIENTE;

typedef struct{
    char nome[30], curso[30];
    int matricula, cpf;
}ALUNOS;

typedef struct{
    char nome[30], curso[30];
    int codprofessor;
}SUPERVISORES;

typedef struct{
    int codagendamento, codpaciente;
    char nomepaciente[30], area[15];
    DATNAS dc;
}AGENDAMENTO;

typedef struct{
    int codatendimento, codagendamento, codaluno, codpaciente, codsupervisor;
    DATNAS daten;
    char nomealuno[30], nomepaciente[30], area[20], nomesupervisor[30];

}ATENDIMENTO;

int encontrar_aluno(ALUNOS student){

    FILE *arq = fopen("aluno.bin", "r+b");
    ALUNOS aluno;

    while(fread(&aluno, sizeof(ALUNOS), 1, arq)){
        if (aluno.matricula == student.matricula){
            return 1;
        }
    }

    return 0;
}


void cabecalho(){
    system("cls");

    printf ("\t\t=================================================================================================\n");
    printf ("\t\t__________________________________________CLÕNICA UEPB___________________________________________\n\n");
    printf ("\t\t=================================================================================================\n\n");

}

void cadastro_aluno(){

    ALUNOS aluno;
    FILE *arq = fopen("aluno.bin", "a+b");
    int result;

    do {
        cabecalho();

        printf("\t\t================================================================================================\n\n");
        printf("\t\t____________________________________CADASTRO DE ALUNO_____________________________________________\n\n");

        printf ("\t\tDIGITE O NOME DO ALUNO: ");
        scanf (" %[^\n]s", aluno.nome);

        printf ("\t\tDIGITE O CURSO DO ALUNO: ");
        scanf (" %[^\n]s", aluno.curso);

        do{
            printf ("\t\tDIGITE A MATRICULA DO ALUNO: ");
            scanf ("%d", &aluno.matricula);

            result = encontrar_aluno(aluno);

            if (result == 1){
                printf("\n\t\tALUNO J¡ EST¡ CADASTRADO, DIGITE UM NOVO C”DIGO!\n\n");
                continue;
            }

        }while(result != 0);


        printf ("\t\tDIGITE O CPF DO ALUNO(ESCREVA APENAS NUMEROS): ");
        scanf ("%d", &aluno.cpf);

        puts("\n\n\n");

        fwrite(&aluno, sizeof(ALUNOS),1,arq);

        printf ("\t\tDESEJA CADASTRAR UM NOVO ALUNO(S/N)? ");

    }while(getche() == 's');

    fclose(arq);
}

void remover_aluno(){

    cabecalho();

    printf("\t\t================================================================================================\n\n");
    printf("\t\t____________________________________REMOVER ALUNO_____________________________________________\n\n");

    ALUNOS aluno;
    int mat;
    char c;
    FILE *arq = fopen("aluno.bin", "r+b"), *aux = fopen("new_aluno.bin", "a+b");


    printf ("\t\tDIGITE A MATRICULA DO ALUNO: ");
    scanf ("%d", &mat);

    printf("TEM CERTEZA QUE DESEJA REMOVER O ALUNO(S/N)? ");
    scanf (" %c", &c);

    if (c == 'S' || c == 's'){

        rewind(arq);

        while(fread(&aluno, sizeof(ALUNOS),1,arq)==1){

            if (mat != aluno.matricula){

                fwrite(&aluno, sizeof(ALUNOS),1,aux);

            }

        }

        printf ("ALUNO REMOVIDO COM SUCESSO!\n");

    } else {

        printf("ALUNO NAO FOI REMOVIDO!\n");

    }

    remove("aluno.bin");
    rename("new_aluno.bin","aluno.bin");

    fclose(arq);
    fclose(aux);

    system("pause");

}

void editar_aluno(){

    cabecalho();

    printf("\t\t================================================================================================\n\n");
    printf("\t\t____________________________________EDITAR ALUNO_____________________________________________\n\n");

    int mat, cpf;
    char name[30], curse[30];
    ALUNOS aluno, new_dados;
    FILE *arq = fopen("aluno.bin", "a+b"), *aux = fopen("new_aluno.bin", "a+b");

    printf ("\t\tDIGITE O NOME DO ALUNO: ");
    scanf (" %[^\n]s", name);

    printf ("\t\tDIGITE O CURSO DO ALUNO: ");
    scanf (" %[^\n]s", curse);

    printf ("\t\tDIGITE A MATRICULA DO ALUNO: ");
    scanf ("%d", &mat);

    printf ("\t\tDIGITE O CPF DO ALUNO(ESCREVA APENAS NUMEROS): ");
    scanf ("%d", &cpf);

    while(fread(&aluno, sizeof(ALUNOS),1,arq)==1){

            if ((mat == aluno.matricula) && (cpf == aluno.cpf)){

                    printf("\t\tDIGITE OS NOVOS DADOS DO ALUNO: \n\n");

                    printf ("\t\tNOME DO ALUNO: ");
                    scanf (" %[^\n]s", new_dados.nome);

                    printf ("\t\tO CURSO DO ALUNO: ");
                    scanf (" %[^\n]s", new_dados.curso);

                    printf ("\t\tA MATRICULA DO ALUNO: ");
                    scanf ("%d", &new_dados.matricula);

                    printf ("\t\tO CPF DO ALUNO(ESCREVA APENAS NUMEROS): ");
                    scanf ("%d", &new_dados.cpf);

                    fwrite(&new_dados, sizeof(ALUNOS), 1, aux);

            } else {

                    fwrite(&aluno, sizeof(ALUNOS),1,aux);

            }
    }

    fclose(arq);
    fclose(aux);

    remove("aluno.bin");
    rename("new_aluno.bin", "aluno.bin");
}

void listar_alunos(){

    cabecalho();

    printf("\t\t=================================================================================================\n\n");
    printf("\t\t_____________________________________LISTA DE ALUNOS_____________________________________________\n\n");

    ALUNOS aluno;
    FILE *arq = fopen("aluno.bin", "r+b");
    int i = 1;

    while(fread(&aluno, sizeof(ALUNOS), 1, arq) == 1){

        printf("\t\t%d∫ ALUNO:\n", i);

        printf("\t\tNOME: %s\n\t\tCURSO: %s\n\t\tMATRICULA: %d\n\t\tCPF: %d\n", aluno.nome, aluno.curso, aluno.matricula, aluno.cpf);
        printf("\t\t-------------------------------------------------------------------------------------------------\n");
        printf ("\n\n");

        i++;
    }

    fclose(arq);

    printf ("PRESSIONE ENTER PARA CONTINUAR...\n");
    system("pause");
}

void pesquisar_aluno(){

    int cont = 0;
    char name[30];
    ALUNOS aluno;
    FILE *arq = fopen("aluno.bin", "r+b");

    do{
        cabecalho();

        printf("\t\t=================================================================================================\n\n");
        printf("\t\t_____________________________________PESQUISAR ALUNO______________________________________________\n\n");

        cont = 0;

        printf ("\t\tDIGITE O NOME DO ALUNO: ");
        scanf (" %[^\n]s", name);

        rewind(arq);

        while(fread(&aluno, sizeof(ALUNOS), 1, arq) == 1){

                if (strcmp(name, aluno.nome)==0){

                            printf("\t\tNOME: %s\n\t\tCURSO: %s\n\t\tMATRICULA: %d\n\t\tCPF: %d\n\n", aluno.nome, aluno.curso, aluno.matricula, aluno.cpf);

                            printf("\t\t-------------------------------------------------------------------------------------------------\n");

                            printf ("\n\n");

                            cont ++;
                }
        }

        if (cont == 0){

            printf("\t\tALUNO N√O CADASTRADO!\n\n");

        }

        printf("\t\tDESEJA PESQUISAR UM NOVO ALUNO(S/N)?");

    }while(getche() == 's');

    fclose(arq);

    printf ("\n\n\t\tPRESSIONE ENTER PARA CONTINUAR...\n\n");
    system("pause");
}

void menu_aluno(){

    int n;

    do{
        cabecalho();

        printf ("\t\t__________________________________________MENU DO ALUNO__________________________________________\n");
        printf ("\t\t#################################################################################################\n");
        printf ("\t\t=================================================================================================\n\n");

        printf ("\t\t\t\t\t\tSELECIONE A OP«√O DESEJADA:\n\n");
        printf ("\t\t\t\t\t1 - CADASTRAR ALUNO\t\t2 - REMOVER ALUNO\n\n");
        printf ("\t\t\t\t\t3 - EDITAR ALUNO\t\t4 - LISTAR ALUNOS\n\n");
        printf ("\t\t\t\t\t5 - PESQUISAR\t\t\t6 - SAIR\n\n");

        printf ("\t\tOPCAO: ");

        scanf ("%d", &n);

        if (n == 1){

            cadastro_aluno();

        } else if (n == 2){

            remover_aluno();

        } else if (n == 3){

            editar_aluno();

        } else if (n == 4){

            listar_alunos();

        } else if (n == 5){

            pesquisar_aluno();

        } else if (n != 6){

            printf("OPCAO INVALIDA POR FAVOR DIGITE UMA OPCAO VALIDA!\n");

        }

    } while(n != 6);

}



int encontrar_paciente(PACIENTE patient){

    FILE *arq = fopen("paciente.bin", "r+b");
    PACIENTE paciente;

    while(fread(&paciente, sizeof(PACIENTE), 1, arq)){
        if (paciente.codpaciente == patient.codpaciente){
            return 1;
        }
    }

    return 0;
}


void cadastro_paciente(){

    PACIENTE paciente;
    FILE *arq = fopen("paciente.bin", "a+b");
    int result;

    do {
        cabecalho();

        printf("\t\t================================================================================================\n\n");
        printf("\t\t____________________________________CADASTRO DE PACIENTE_____________________________________________\n\n");

        printf ("\t\tDIGITE O NOME DO PACIENTE: ");
        scanf (" %[^\n]s", paciente.nome);

        do{
            printf ("\t\tDIGITE O C”DIGO DO PACIENTE: ");
            scanf (" %d", &paciente.codpaciente);

            result = encontrar_paciente(paciente);

            if (result == 1){

                printf("\n\t\tPACIENTE J¡ CADASTRADO, POR FAVOR DIGITE UM NOVO C”DIGO!\n\n");
                continue;

            }
        }while(result != 0);


        printf ("\t\tDIGITE A DATA DE NASCIMENTO(DD MM AAAA): ");
        scanf ("%d %d %d", &paciente.dn.dia, &paciente.dn.mes, &paciente.dn.ano);

        printf ("\t\tDIGITE O CPF DO PACIENTE(ESCREVA APENAS NUMEROS): ");
        scanf ("%d", &paciente.cpf);

        printf("\t\tENDERE«O DO PACIENTE: \n");

        printf("\t\t\tRUA: ");
        scanf(" %[^\n]s", paciente.endereco.rua);

        printf("\t\t\tBAIRRO: ");
        scanf(" %[^\n]s", paciente.endereco.bairro);

        printf("\t\t\tNUMERO: ");
        scanf(" %[^\n]s", paciente.endereco.numero);

        printf("\t\t\tCEP: ");
        scanf(" %[^\n]s", paciente.endereco.cep);

        printf("\t\t\tESTADO: ");
        scanf(" %[^\n]s", paciente.endereco.estado);

        puts("\n\n\n");

        fwrite(&paciente, sizeof(PACIENTE),1,arq);

        printf ("\t\tDESEJA CADASTRAR UM NOVO PACIENTE(S/N)? ");

    }while(getche() == 's');

    fclose(arq);

}

void listar_paciente(){

    cabecalho();

    printf("\t\t=================================================================================================\n\n");
    printf("\t\t_____________________________________LISTA DE PACIENTES_____________________________________________\n\n");

    int i = 1;
    PACIENTE paciente;
    FILE *arq = fopen("paciente.bin", "r+b");

    while(fread(&paciente, sizeof(PACIENTE), 1, arq) == 1){

        printf("\t\t%d∫ PACIENTE:\n", i);

        printf("\n\t\tNOME: %s\n", paciente.nome);
        printf("\t\tC”DIGO DO PACIENTE: %d\n", paciente.codpaciente);
        printf("\t\tDATA DE NASCIMENTO: %d/%d/%d\n", paciente.dn.dia, paciente.dn.mes, paciente.dn.ano);
        printf("\t\tCPF: %d\n", paciente.cpf);
        printf("\t\tENDERECO: \n");
        printf("\t\t\tRUA: %s\n", paciente.endereco.rua);
        printf("\t\t\tBAIRRO: %s\n", paciente.endereco.bairro);
        printf("\t\t\tNUMERO: %s\n", paciente.endereco.numero);
        printf("\t\t\tCEP: %s\n",  paciente.endereco.cep);
        printf("\t\t\tESTADO: %s\n", paciente.endereco.estado);

        printf("\t\t-------------------------------------------------------------------------------------------------\n");
        printf ("\n\n");

        i++;
    }

    fclose(arq);

    printf ("\t\tPRESSIONE ENTER PARA CONTINUAR...\n");
    system("pause");
}

void remover_paciente(){

    cabecalho();

    printf("\t\t================================================================================================\n\n");
    printf("\t\t____________________________________REMOVER PACIENTE_____________________________________________\n\n");

    PACIENTE paciente;
    int codigo;
    char c;
    FILE *arq = fopen("paciente.bin", "r+b"), *aux = fopen("new_paciente.bin", "a+b");


    printf ("\n\t\tDIGITE C”DIGO DO PACIENTE: ");
    scanf ("%d", &codigo);

    printf("\n\n\t\tTEM CERTEZA QUE DESEJA REMOVER O PACIENTE(S/N)? ");
    scanf (" %c", &c);

    if (c == 'S' || c == 's'){

            rewind(arq);

            while(fread(&paciente, sizeof(PACIENTE), 1, arq) == 1){

                    if (codigo != paciente.codpaciente){

                            fwrite(&paciente, sizeof(PACIENTE),1,aux);

                    }

            }

            fclose(arq);
            fclose(aux);

            remove("paciente.bin");
            rename("new_paciente.bin","paciente.bin");

            printf ("\n\n\t\tPACIENTE REMOVIDO COM SUCESSO!\n");
            system("pause");

    } else {

            printf("\n\nPACIENTE NAO FOI REMOVIDO!\n");

            fclose(arq);
            fclose(aux);
    }
}

void editar_paciente(){

    cabecalho();

    printf("\t\t================================================================================================\n\n");
    printf("\t\t____________________________________EDITAR  PACIENTE_____________________________________________\n\n");

    int codpaciente, dia, mes, ano, cpf;
    char name[30], estado[15], rua[30], bairro[20], numero[8], cep[15];
    PACIENTE paciente, new_dados;
    FILE *arq = fopen("paciente.bin", "a+b"), *aux = fopen("new_paciente.bin", "a+b");


    printf ("\n\t\tDIGITE O C”DIGO DO PACIENTE: ");
    scanf (" %d", &codpaciente);

    printf ("\t\tDIGITE O CPF DO PACIENTE(ESCREVA APENAS NUMEROS): ");
    scanf ("%d", &cpf);

    while(fread(&paciente, sizeof(PACIENTE),1,arq)==1){

            if ((codpaciente == paciente.codpaciente) && (cpf == paciente.cpf)){

                    printf("\n\n\t\tDIGITE OS NOVOS DADOS DO PACIENTE: \n\n");

                    printf ("\t\tDIGITE O NOME DO PACIENTE: ");
                    scanf (" %[^\n]s", new_dados.nome);

                    printf ("\t\tDIGITE O C”DIGO DO PACIENTE: ");
                    scanf (" %d", &new_dados.codpaciente);

                    printf ("\t\tDIGITE A DATA DE NASCIMENTO(DD MM AAAA): ");
                    scanf ("%d %d %d", &new_dados.dn.dia, &new_dados.dn.mes, &new_dados.dn.ano);

                    printf ("\t\tDIGITE O CPF DO PACIENTE(ESCREVA APENAS NUMEROS): ");
                    scanf ("%d", &new_dados.cpf);

                    printf("\t\tENDERE«O DO PACIENTE: \n");

                    printf("\t\t\tRUA: ");
                    scanf(" %[^\n]s", new_dados.endereco.rua);

                    printf("\t\t\tBAIRRO: ");
                    scanf(" %[^\n]s", new_dados.endereco.bairro);

                    printf("\t\t\tNUMERO: ");
                    scanf(" %[^\n]s", new_dados.endereco.numero);

                    printf("\t\t\tCEP: ");
                    scanf(" %[^\n]s", new_dados.endereco.cep);

                    printf("\t\t\tESTADO: ");
                    scanf(" %[^\n]s", new_dados.endereco.estado);

                    fwrite(&new_dados, sizeof(PACIENTE),1,aux);

            } else {

                    fwrite(&paciente, sizeof(PACIENTE),1,aux);

            }
    }

    fclose(arq);
    fclose(aux);

    remove("paciente.bin");
    rename("new_paciente.bin", "paciente.bin");

}

void pesquisar_paciente(){

    int cont = 0;
    char name[30];
    PACIENTE paciente;
    FILE *arq = fopen("paciente.bin", "r+b");

    do{
        cabecalho();

        printf("\t\t=================================================================================================\n\n");
        printf("\t\t_____________________________________PESQUISAR PACIENTE______________________________________________\n\n");

        cont = 0;

        printf ("\t\tDIGITE O NOME DO PACIENTE: ");
        scanf (" %[^\n]s", name);

        rewind(arq);

        while(fread(&paciente, sizeof(PACIENTE), 1, arq) == 1){

                if (strcmp(name, paciente.nome)==0){

                           printf("\n\t\tNOME: %s\n", paciente.nome);
                           printf("\t\tC”DIGO DO PACIENTE: %d\n", paciente.codpaciente);
                           printf("\t\tDATA DE NASCIMENTO: %d/%d/%d\n", paciente.dn.dia, paciente.dn.mes, paciente.dn.ano);
                           printf("\t\tCPF: %d\n", paciente.cpf);
                           printf("\t\tENDERECO: \n");
                           printf("\t\t\tRUA: %s\n", paciente.endereco.rua);
                           printf("\t\t\tBAIRRO: %s\n", paciente.endereco.bairro);
                           printf("\t\t\tNUMERO: %s\n", paciente.endereco.numero);
                           printf("\t\t\tCEP: %s\n",  paciente.endereco.cep);
                           printf("\t\t\tESTADO: %s\n\n", paciente.endereco.estado);

                            printf("\t\t-------------------------------------------------------------------------------------------------\n");

                            printf ("\n\n");

                            cont ++;

                }
        }

        if (cont == 0){

            printf("\t\tPACIENTE N√O CADASTRADO!\n\n");

        }

        printf("\t\tDESEJA PESQUISAR UM NOVO PACIENTE(S/N)?");

    }while(getche() == 's');

    fclose(arq);

    printf ("\n\n\t\tPRESSIONE ENTER PARA CONTINUAR...\n\n");
    system("pause");
}

void menu_paciente(){
    int n;

    do{
        cabecalho();

        printf ("\t\t________________________________________MENU DO PACIENTE_________________________________________\n");
        printf ("\t\t#################################################################################################\n");
        printf ("\t\t=================================================================================================\n\n");

        printf ("\t\t\t\t\t\tSELECIONE A OP«√O DESEJADA:\n\n");

        printf ("\t\t\t\t\t1 - CADASTRAR PACIENTE\t\t2 - REMOVER PACIENTE\n\n");
        printf ("\t\t\t\t\t3 - EDITAR PACIENTE\t\t4 - LISTAR PACIENTE\n\n");
        printf ("\t\t\t\t\t5 - PESQUISAR\t\t\t6 - SAIR\n\n");

        printf ("\t\tOPCAO: ");

        scanf ("%d", &n);

        if (n == 1){

            cadastro_paciente();

        } else if (n == 2){

            remover_paciente();

        } else if (n == 3){

            editar_paciente();

        } else if (n == 4){

            listar_paciente();

        } else if (n == 5){

            pesquisar_paciente();

        } else if (n != 6){

            printf("OPCAO INVALIDA POR FAVOR DIGITE UMA OPCAO VALIDA!\n");

        }

    } while(n != 6);
}



int encontrar_supervisor(SUPERVISORES teacher){

    FILE *arq = fopen("supervisores.bin", "r+b");
    SUPERVISORES supervisor;

    while(fread(&supervisor, sizeof(SUPERVISORES), 1, arq)){
        if (supervisor.codprofessor == teacher.codprofessor){
            return 1;
        }
    }

    return 0;
}


void cadastro_supervisor(){

    SUPERVISORES supervisores;
    FILE *arq = fopen("supervisores.bin", "a+b");
    int result;

    do {
        cabecalho();

        printf("\t\t================================================================================================\n\n");
        printf("\t\t____________________________________CADASTRO DE SUPERVISORES_____________________________________________\n\n");

        printf ("\t\tDIGITE O NOME DO SUPERVISOR: ");
        scanf (" %[^\n]s", supervisores.nome);

        do{
            printf ("\t\tDIGITE O C”DIGO DO SUPERVISOR: ");
            scanf (" %d", &supervisores.codprofessor);

            result = encontrar_supervisor(supervisores);

            if (result == 1){

                printf("\n\t\tSUPERVISOR J¡ EST¡ CADASTRADO, POR FAVOR DIGITE UM NOVO C”DIGO!\n\n");
                continue;

            }

        }while(result != 0);


        printf ("\t\tDIGITE O CURSO DO SUPERVISOR: ");
        scanf(" %[^\n]s", supervisores.curso);

        puts("\n\n\n");

        fwrite(&supervisores, sizeof(SUPERVISORES),1,arq);

        printf ("\t\tDESEJA CADASTRAR UM NOVO SUPERVISOR(S/N)? ");

    }while(getche() == 's');

    fclose(arq);
}

void remover_supervisor(){

    cabecalho();

    printf("\t\t================================================================================================\n\n");
    printf("\t\t____________________________________REMOVER SUPERVISOR_____________________________________________\n\n");

    SUPERVISORES supervisores;
    int codigo;
    char c;
    FILE *arq = fopen("supervisores.bin", "r+b"), *aux = fopen("new_supervisor.bin", "a+b");


    printf ("\n\t\tDIGITE C”DIGO DO SUPERVISOR: ");
    scanf ("%d", &codigo);

    printf("\n\n\t\tTEM CERTEZA QUE DESEJA REMOVER O SUPERVISOR(S/N)? ");
    scanf (" %c", &c);

    if (c == 'S' || c == 's'){

            rewind(arq);

            while(fread(&supervisores, sizeof(SUPERVISORES), 1, arq) == 1){

                    if (codigo != supervisores.codprofessor){

                            fwrite(&supervisores, sizeof(SUPERVISORES),1,aux);

                    }

            }

            fclose(arq);
            fclose(aux);

            remove("supervisores.bin");
            rename("new_supervisor.bin","supervisores.bin");

            printf ("\n\n\t\tSUPERVISOR REMOVIDO COM SUCESSO!\n");
            system("pause");

    } else {

            printf("\n\nSUPERVISOR NAO FOI REMOVIDO!\n");

            fclose(arq);
            fclose(aux);
    }

}

void editar_supervisor(){

    cabecalho();

    printf("\t\t================================================================================================\n\n");
    printf("\t\t____________________________________EDITAR SUPERVISOR_____________________________________________\n\n");

    int codprofessor;
    SUPERVISORES supervisores, new_dados;
    FILE *arq = fopen("supervisores.bin", "a+b"), *aux = fopen("new_supervisor.bin", "a+b");

    printf ("\n\t\tDIGITE O C”DIGO DO SUPERVISOR QUE DESEJA EDITAR: ");
    scanf ("%d", &codprofessor);

    while(fread(&supervisores, sizeof(SUPERVISORES),1,arq)==1){

            if (codprofessor == supervisores.codprofessor){

                    printf("\n\n\t\tDIGITE OS NOVOS DADOS DO SUPERVISOR: \n\n");

                    printf ("\t\tDIGITE O NOME DO PACIENTE: ");
                    scanf (" %[^\n]s", new_dados.nome);

                    printf ("\t\tDIGITE O C”DIGO DO SUPERVISOR: ");
                    scanf (" %d", &new_dados.codprofessor);

                    printf ("\t\tDIGITE O CURSO DO SUPERVISOR: ");
                    scanf(" %[^\n]s", new_dados.curso);

                    fwrite(&new_dados, sizeof(SUPERVISORES),1,aux);

            } else {

                    fwrite(&supervisores, sizeof(SUPERVISORES),1,aux);

            }
    }

    fclose(arq);
    fclose(aux);

    remove("supervisores.bin");
    rename("new_supervisor.bin", "supervisores.bin");
}

void listar_supervisor(){

    cabecalho();

    printf("\t\t=================================================================================================\n\n");
    printf("\t\t_____________________________________LISTA DE SUPERVISORES_____________________________________________\n\n");

    int i = 1;
    SUPERVISORES supervisores;
    FILE *arq = fopen("supervisores.bin", "r+b");

    while(fread(&supervisores, sizeof(SUPERVISORES), 1, arq) == 1){

        printf("\t\t%d∫ SUPERVISORES:\n", i);

        printf("\n\t\tNOME: %s\n", supervisores.nome);
        printf("\t\tC”DIGO DO SUPERVISOR: %d\n", supervisores.codprofessor);
        printf("\t\tCURSO DO SUPERVISOR: %s\n", supervisores.curso);

        printf("\t\t-------------------------------------------------------------------------------------------------\n");
        printf ("\n\n");

        i++;
    }

    fclose(arq);

    printf ("\t\tPRESSIONE ENTER PARA CONTINUAR...\n");
    system("pause");
}

void pesquisar_supervisor(){

    int cont = 0;
    char name[30];
    SUPERVISORES supervisores;
    FILE *arq = fopen("supervisores.bin", "r+b");

    do{
        cabecalho();

        printf("\t\t=================================================================================================\n\n");
        printf("\t\t_____________________________________PESQUISAR PACIENTE______________________________________________\n\n");

        cont = 0;

        printf ("\t\tDIGITE O NOME DO SUPERVISOR: ");
        scanf (" %[^\n]s", name);

        rewind(arq);

        while(fread(&supervisores, sizeof(SUPERVISORES), 1, arq) == 1){

                if (strcmp(name, supervisores.nome)==0){

                           printf("\n\t\tNOME: %s\n", supervisores.nome);
                           printf("\t\tC”DIGO DO SUPERVISOR: %d\n", supervisores.codprofessor);
                           printf("\t\tCURSO DO SUPERVISOR: %s\n", supervisores.curso);

                            printf("\t\t-------------------------------------------------------------------------------------------------\n");

                            printf ("\n\n");

                            cont ++;

                }
        }

        if (cont == 0){

            printf("\n\t\tSUPERVISOR N√O CADASTRADO!\n\n");

        }

        printf("\t\tDESEJA PESQUISAR UM NOVO SUPERVISOR(S/N)?");

    }while(getche() == 's');
}

void menu_supervisor(){

    int n;

    do{
        cabecalho();

        printf ("\t\t________________________________________MENU DO SUPERVISOR_________________________________________\n");
        printf ("\t\t#################################################################################################\n");
        printf ("\t\t=================================================================================================\n\n");

        printf ("\t\t\t\t\t\tSELECIONE A OP«√O DESEJADA:\n\n");

        printf ("\t\t\t\t\t1 - CADASTRAR SUPERVISOR\t\t2 - REMOVER SUPERVISOR\n\n");
        printf ("\t\t\t\t\t3 - EDITAR SUPERVISOR\t\t4 - LISTAR SUPERVISOR\n\n");
        printf ("\t\t\t\t\t5 - PESQUISAR\t\t\t6 - SAIR\n\n");

        printf ("\t\tOPCAO: ");

        scanf ("%d", &n);

        if (n == 1){

            cadastro_supervisor();

        } else if (n == 2){

            remover_supervisor();

        } else if (n == 3){

            editar_supervisor();

        } else if (n == 4){

            listar_supervisor();

        } else if (n == 5){

            pesquisar_supervisor();

        } else if (n != 6){

            printf("OPCAO INVALIDA POR FAVOR DIGITE UMA OPCAO VALIDA!\n");

        }

    } while(n != 6);
}



int encontrar_agendamento(AGENDAMENTO agenda){

    FILE *arq = fopen("agendamento.bin", "r+b");
    AGENDAMENTO agendamento;

    while(fread(&agendamento, sizeof(AGENDAMENTO), 1, arq)){
        if (agendamento.codagendamento == agenda.codagendamento){
            return 1;
        }
    }

    return 0;
}


int verificar_area(int cod, int op){

    FILE *arq = fopen("agendamento.bin", "r+b");
    AGENDAMENTO agendamento;
    PACIENTE paciente;

    if (op == 1){

        rewind(arq);
        while(fread(&agendamento, sizeof(AGENDAMENTO), 1, arq)){
            if ((paciente.codpaciente == agendamento.codpaciente) && (strcmp(agendamento.area, "FISIOTERAPIA")==1)){
                return 1;
            }
        }

        return 0;

    } else if (op == 2){

        rewind(arq);
        while(fread(&agendamento, sizeof(AGENDAMENTO), 1, arq)){
            if (paciente.codpaciente == agendamento.codpaciente && strcmp(agendamento.area, "ODONTOLOGIA")==1){
                return 1;
            }
        }

        return 0;

    } else if (op == 3){

        rewind(arq);
        while(fread(&agendamento, sizeof(AGENDAMENTO), 1, arq)){
            if (paciente.codpaciente == agendamento.codpaciente && strcmp(agendamento.area, "PSICOLOGIA")==1){
                return 1;
            }
        }

        return 0;

    }

}

void cria_agendamento(){

    cabecalho();

    printf("\t\t================================================================================================\n\n");
    printf("\t\t____________________________________NOVO AGENDAMENTO_____________________________________________\n\n");

    int cont, n;
    FILE *arq = fopen("agendamento.bin", "a+b"), *arqpaciente = fopen("paciente.bin", "r+b");
    AGENDAMENTO agendamento;
    PACIENTE paciente;
    int result, volta;
    char op;

    do{
        printf("DIGITE O C”DIGO DO AGENDAMENTO: ");
        scanf("%d", &agendamento.codagendamento);

        result = encontrar_agendamento(agendamento);

        if (result == 1){
            printf("\n\t\tC”DIGO DE AGENDAMENTO J¡ EXISTE, POR FAVOR DIGITE UM NOVO C”DIGO!\n\n");
        }

    }while(result != 0);


    do {

        printf("DIGITE O C”DIGO DO PACIENTE: ");
        scanf("%d", &agendamento.codpaciente);

        while(fread(&paciente, sizeof(PACIENTE), 1, arqpaciente) == 1){

            if (agendamento.codpaciente == paciente.codpaciente){

                strcpy(agendamento.nomepaciente, paciente.nome);

                do{

                    printf("SELECIONE A ¡REA DE ATENDIMENTO: \n\n");
                    printf("\t\t1 - FISIOTERAPIA\n\t\t2 - ODONTOLOGIA\n\t\t3 - PSICOLOGIA\n\n");

                    printf("OP«√O: ");
                    scanf("%d", &n);

                    volta = verificar_area(paciente.codpaciente, n);

                    if (n == 1){

                            if (volta == 1){

                                printf("\n\t\tPACIENTE N√O PODE SER ATENDIDO NESSA ¡REA, POR FAVOR ESCOLHA OUTRA ¡REA DE ATENDIMENTO!\n\n");
                                continue;

                            } else {

                                strcpy(agendamento.area, "FISIOTERAPIA");

                            }

                    } else if (n == 2){

                            if (volta == 1){

                                printf("\n\t\tPACIENTE N√O PODE SER ATENDIDO NESSA ¡REA, POR FAVOR ESCOLHA OUTRA ¡REA DE ATENDIMENTO!\n\n");
                                continue;

                            } else {

                                strcpy(agendamento.area, "ODONTOLOGIA");

                            }

                    } else if (n == 3){

                            if (volta == 1){

                                printf("\n\t\tPACIENTE N√O PODE SER ATENDIDO NESSA ¡REA, POR FAVOR ESCOLHA OUTRA ¡REA DE ATENDIMENTO!\n\n");
                                continue;

                            } else {

                                strcpy(agendamento.area, "PSICOLOGIA");

                            }

                    } else {

                        printf("OP«√O INV¡LIDA, POR FAVOR SELECIONE UMA V¡LIDA!");

                    }



                } while(n <1 || n > 3);

                cont ++;
                break;

            }

        }

        if (cont == 0){

            printf("PACIENTE N√O CADASTRADO!\n\n\t\tDESEJA CADASTRAR UM PACIENTE(S/N)? \n\n");
            scanf(" %c", op);

            if (op == 's' || op == 'S'){
                cadastro_paciente();
            } else {
                printf("\n\t\tPOR FAVOR DIGITE UM C”DIGO V¡LIDO!\n\n");
            }

        } else {

            break;

        }

    }while(cont != 0);



    printf("DIGITE A DATA DE ATENDIMENTO(DD MM AAAA): ");
    scanf("%d %d %d", &agendamento.dc.dia, &agendamento.dc.mes, &agendamento.dc.ano);

    fwrite(&agendamento, sizeof(AGENDAMENTO), 1, arq);

    printf("CADASTRO REALIZADO COM SUCESSO!\n\n");

    fclose(arq);
    system("pause");
}

void cancela_agendamento(){

    cabecalho();

    printf("\t\t================================================================================================\n\n");
    printf("\t\t____________________________________CANCELAMENTO DE AGENDAMENTO_____________________________________________\n\n");

    AGENDAMENTO agendamento;
    int codigo;
    char c;
    FILE *arq = fopen("agendamento.bin", "r+b"), *aux = fopen("new_agendamento.bin", "a+b");


    printf ("\n\t\tDIGITE C”DIGO DO AGENDAMENTO A SER CANCELADO: ");
    scanf ("%d", &codigo);

    printf("\n\n\t\tTEM CERTEZA QUE DESEJA CANCELAR O AGENDAMENTO(S/N)? ");
    scanf (" %c", &c);

    if (c == 'S' || c == 's'){

            rewind(arq);

            while(fread(&agendamento, sizeof(AGENDAMENTO), 1, arq) == 1){

                    if (codigo != agendamento.codagendamento){

                            fwrite(&agendamento, sizeof(AGENDAMENTO),1,aux);

                    }

            }

            fclose(arq);
            fclose(aux);

            remove("agendamento.bin");
            rename("new_agendamento.bin","agendamento.bin");

            printf ("\n\n\t\tAGENDAMENTO CANCELADO COM SUCESSO!\n");
            system("pause");

    } else {

            printf("\n\nAGENDAMENTO NAO FOI CANCELADO!\n");

            fclose(arq);
            fclose(aux);
    }
}

void lista_agendamento(){

    cabecalho();

    printf("\t\t=================================================================================================\n\n");
    printf("\t\t_____________________________________LISTA DE AGENDAMENTO_____________________________________________\n\n");

    int i = 1;
    AGENDAMENTO agendamento;
    FILE *arq = fopen("agendamento.bin", "r+b");

    while(fread(&agendamento, sizeof(AGENDAMENTO), 1, arq) == 1){

        printf("\t\t%d∫ AGENDAMENTO:\n", i);

        printf("\n\t\tC”DIGO DO AGENDAMENTO: %d\n", agendamento.codagendamento);
        printf("\t\tNOME DO PACIENTE: %s\n", agendamento.nomepaciente);
        printf("\t\tC”DIGO DO PACIENTE: %d\n", agendamento.codpaciente);
        printf("\t\t¡REA DE ATENDIMENTO: %s\n", agendamento.area);
        printf("\t\tDATA DA CONSULTA: %d/%d/%d\n", agendamento.dc.dia, agendamento.dc.mes, agendamento.dc.ano);

        printf("\t\t-------------------------------------------------------------------------------------------------\n");
        printf ("\n\n");

        i++;
    }

    fclose(arq);

    printf ("\t\tPRESSIONE ENTER PARA CONTINUAR...\n");
    system("pause");
}

void menu_agendamento(){

    int n;

    do{
        cabecalho();

        printf ("\t\t________________________________________MENU DO AGENDAMENTO_________________________________________\n");
        printf ("\t\t#################################################################################################\n");
        printf ("\t\t=================================================================================================\n\n");

        printf ("\t\t\t\t\t\tSELECIONE A OP«√O DESEJADA:\n\n");

        printf ("\t\t\t\t\t1 - CRIAR NOVO AGENDAMENTO\t\t2 - CANCELAR AGENDAMENTO\n\n");
        printf ("\t\t\t\t\t3 - LISTAR AGENDAMENTO\t\t4 - SAIR\n\n");
        //printf ("\t\t\t\t\t5 - PESQUISAR\t\t\t6 - SAIR\n\n");

        printf ("\t\tOPCAO: ");

        scanf ("%d", &n);

        if (n == 1){

            cria_agendamento();

        } else if (n == 2){

            cancela_agendamento();

        } else if (n == 3){

            lista_agendamento();

        } else if (n != 4){

            printf("OPCAO INVALIDA POR FAVOR DIGITE UMA OPCAO VALIDA!\n");
            system("pause");

        }

    } while(n != 4);
}




int encontrar_atendimento(ATENDIMENTO attendance){

    FILE *arq = fopen("atendimento.bin", "r+b");
    ATENDIMENTO atendimento;

    while(fread(&atendimento, sizeof(ATENDIMENTO), 1, arq)){
        if (atendimento.codatendimento == atendimento.codatendimento){
            return 1;
        }
    }

    return 0;
}


void remover_agendamento(int codigo){

    AGENDAMENTO agendamento;
    FILE *arq = fopen("agendamento.bin", "r+b"), *aux = fopen("new_agendamento.bin", "a+b");

    rewind(arq);

    while(fread(&agendamento, sizeof(AGENDAMENTO), 1, arq) == 1){

            if (codigo != agendamento.codagendamento){

                    fwrite(&agendamento, sizeof(AGENDAMENTO),1,aux);

            }

    }

    fclose(arq);
    fclose(aux);

    remove("agendamento.bin");
    rename("new_agendamento.bin","agendamento.bin");

}


void cria_atendimento(){

    cabecalho();

    printf("\t\t================================================================================================\n\n");
    printf("\t\t____________________________________NOVO ATENDIMENTO_____________________________________________\n\n");

    int cont=0, num, result;
    char op;
    FILE *arq = fopen("atendimento.bin", "a+b"), *arqpaciente = fopen("paciente.bin", "r+b"), *arqaluno = fopen("aluno.bin", "r+b"), *arqagendamento = fopen("agendamento.bin", "r+b"), *arqsupervisor = fopen("supervisores.bin", "r+b");
    ATENDIMENTO atendimento;
    AGENDAMENTO agendamento;
    SUPERVISORES supervisor;
    PACIENTE paciente;
    ALUNOS aluno;

    do{
        printf("DIGITE O C”DIGO DO ATENDIMENTO: ");
        scanf("%d", &atendimento.codatendimento);

        result = encontrar_atendimento(atendimento);

        if (result == 1){

            printf("\n\t\tC”DIGO DE ATENDIMENTO J¡ EXISTE, POR FAVOR DIGITE UM NOVO C”DIGO!\n");
            continue;

        }
    }while(result != 0);


    do {

        printf("DIGITE O C”DIGO DO AGENDAMENTO: ");
        scanf("%d", &atendimento.codagendamento);

        while(fread(&agendamento, sizeof(AGENDAMENTO), 1, arqagendamento) == 1){

            if (atendimento.codagendamento == agendamento.codagendamento){

                atendimento.daten.dia = agendamento.dc.dia;
                atendimento.daten.mes = agendamento.dc.mes;
                atendimento.daten.ano = agendamento.dc.ano;
                strcpy( atendimento.nomepaciente, agendamento.nomepaciente);
                atendimento.codpaciente = agendamento.codpaciente;
                strcpy(atendimento.area, agendamento.area);

                num = 0;

                printf("\t\tDIGITE O NOME DO ALUNO: ");
                scanf(" %[^\n]s", atendimento.nomealuno);

                do {

                        printf("DIGITE O C”DIGO DO ALUNO: ");
                        scanf("%d", &atendimento.codaluno);

                        while(fread(&aluno, sizeof(ALUNOS), 1, arqaluno) == 1){

                                if (atendimento.codaluno == aluno.matricula){

                                        num ++;
                                        break;

                                }

                        }

                        if (num == 0){

                                printf("ALUNO N√O CADASTRADO!\n\n\t\tDESEJA REALIZAR O CADASTRO DE UM ALUNO(S/N)? \n\n");
                                scanf(" %c", op);

                                if (op == 's' || op == 'S'){
                                    cadastro_aluno();
                                } else {
                                    printf("\n\t\tPOR FAVOR DIGITE UM C”DIGO V¡LIDO!\n\n");
                                }

                        } else {

                                break;

                        }

                }while(num != 0);

                num = 0;

                printf("DIGITE O NOME DO SUPERVISOR: ");
                scanf(" %[^\n]s", atendimento.nomesupervisor);

                do {

                        printf("DIGITE O C”DIGO DO SUPERVISOR: ");
                        scanf("%d", &atendimento.codsupervisor);

                        while(fread(&supervisor, sizeof(SUPERVISORES), 1, arqsupervisor) == 1){

                                    if (atendimento.codsupervisor == supervisor.codprofessor){

                                            num ++;
                                            break;

                                    }

                        }

                        if (num == 0){

                                    printf("SUPERVISOR N√O CADASTRADO!\n\n\t\tDESEJA CADASTRAR UM NOVO SUPERVISOR(S/N)? \n\n");
                                    scanf(" %c", op);

                                    if (op == 's' || op == 'S'){
                                        cadastro_supervisor();
                                    } else {
                                        printf("\n\t\tPOR FAVOR DIGITE UM C”DIGO V¡LIDO!\n\n");
                                    }

                        } else {

                                    break;

                        }

                }while(num != 0);

                fwrite(&atendimento, sizeof(ATENDIMENTO), 1, arq);

                printf("CADASTRO DE ATENDIMENTO REALIZADO COM SUCESSO!\n\n");

                remover_agendamento(agendamento.codagendamento);

                cont ++;
                break;

            }

        }

        if (cont == 0){

            printf("\n\n\t\tAGENDAMENTO N√O CADASTRADO!\n\n\t\tDIGITE UM C”DIGO DE AGENDAMENTO V¡LIDO!\n\n");

        } else {

            break;

        }

    }while(cont != 0);

    fclose(arq);
    system("pause");
}

void cancela_atendimento(){

    cabecalho();

    printf("\t\t================================================================================================\n\n");
    printf("\t\t____________________________________CANCELAMENTO DE ATENDIMENTO_____________________________________________\n\n");

    ATENDIMENTO atendimento;
    int codigo, cont = 0;
    char c;
    FILE *arq = fopen("atendimento.bin", "r+b"), *aux = fopen("new_atendimento.bin", "a+b");




    do {

        printf ("\n\t\tDIGITE C”DIGO DO ATENDIMENTO A SER CANCELADO: ");
        scanf ("%d", &codigo);

        while(fread(&atendimento, sizeof(ATENDIMENTO), 1, arq) == 1){

            if (atendimento.codatendimento == codigo){

                cont ++;
                break;

            }

        }

        if (cont == 0){

            printf("ATENDIMENTO N√O CADASTRADO POR FAVOR DIGITE UM C”DIGO V¡LIDO!\n\n");

        } else {

            break;

        }

    }while(cont != 0);

    printf("\n\n\t\tTEM CERTEZA QUE DESEJA CANCELAR O ATENDIMENTO(S/N)? ");
    scanf (" %c", &c);

    if (c == 'S' || c == 's'){

            rewind(arq);

            while(fread(&atendimento, sizeof(ATENDIMENTO), 1, arq) == 1){

                    if (codigo != atendimento.codatendimento){

                            fwrite(&atendimento, sizeof(ATENDIMENTO),1,aux);

                    }

            }

            fclose(arq);
            fclose(aux);

            remove("atendimento.bin");
            rename("new_atendimento.bin","atendimento.bin");

            printf ("\n\n\t\tATENDIMENTO CANCELADO COM SUCESSO!\n");
            system("pause");

    } else {

            printf("\n\nATENDIMENTO NAO FOI CANCELADO!\n");

            fclose(arq);
            fclose(aux);
    }
}

void lista_atendimento(){

    cabecalho();

    printf("\t\t=================================================================================================\n\n");
    printf("\t\t_____________________________________LISTA DE ATENDIMENTO_____________________________________________\n\n");

    int i = 1;
    ATENDIMENTO atendimento;
    FILE *arq = fopen("atendimento.bin", "r+b");

    while(fread(&atendimento, sizeof(ATENDIMENTO), 1, arq) == 1){

        printf("\t\t%d∫ ATENDIMENTO:\n", i);

        printf("\n\t\tC”DIGO DO ATENDIMENTO: %d\n", atendimento.codatendimento);
        printf("\t\tC”DIGO DO AGENDAMENTO: %d\n", atendimento.codagendamento);
        printf("\t\tDATA DA ATENDIMENTO: %d/%d/%d\n", atendimento.daten.dia, atendimento.daten.mes, atendimento.daten.ano);
        printf("\t\tNOME DO ALUNO: %s\n", atendimento.nomealuno);
        printf("\t\tC”DIGO DO ALUNO: %d\n", atendimento.codaluno);
        printf("\t\tNOME DO PACIENTE: %s\n", atendimento.nomepaciente);
        printf("\t\tC”DIGO DO PACIENTE: %d\n", atendimento.codpaciente);
        printf("\t\tDATA DO ATENDIMENTO: %d/%d/%d\n", atendimento.daten.dia, atendimento.daten.mes, atendimento.daten.ano);
        printf("\t\t¡REA DE ATENDIMENTO: %s\n", atendimento.area);
        printf("\t\tNOME DO SUPERVISOR: %s\n", atendimento.nomesupervisor);

        printf("\t\t-------------------------------------------------------------------------------------------------\n");
        printf ("\n\n");

        i++;
    }

    fclose(arq);

    printf ("\t\tPRESSIONE ENTER PARA CONTINUAR...\n");
    system("pause");
}

void listar_area(){

    cabecalho();

    printf("\t\t=================================================================================================\n\n");
    printf("\t\t_____________________________________LISTA DE ATENDIMENTO_____________________________________________\n\n");

    int i = 1, n;
    ATENDIMENTO atendimento;
    FILE *arq = fopen("atendimento.bin", "r+b");

    printf("SELECIONE A ¡REA DE ATENDIMENTO  QUE DESEJA LISTAR: \n\n");
    printf("\t\t1 - FISIOTERAPIA\n\t\t2 - ODONTOLOGIA\n\t\t3 - PSICOLOGIA\n\n");

    printf("OP«√O: ");
    scanf("%d", &n);

    while(fread(&atendimento, sizeof(ATENDIMENTO), 1, arq) == 1){

        if (n == 1 && strcmp(atendimento.area,"FISIOTERAPIA")==1){

            printf("\t\t%d∫ ATENDIMENTO:\n", i);

            printf("\n\t\tC”DIGO DO ATENDIMENTO: %d\n", atendimento.codatendimento);
            printf("\t\tC”DIGO DO AGENDAMENTO: %d\n", atendimento.codagendamento);
            printf("\t\tDATA DA ATENDIMENTO: %d/%d/%d\n", atendimento.daten.dia, atendimento.daten.mes, atendimento.daten.ano);
            printf("\t\tNOME DO ALUNO: %s\n", atendimento.nomealuno);
            printf("\t\tC”DIGO DO ALUNO: %d\n", atendimento.codaluno);
            printf("\t\tNOME DO PACIENTE: %s\n", atendimento.nomepaciente);
            printf("\t\tC”DIGO DO PACIENTE: %d\n", atendimento.codpaciente);
            printf("\t\tDATA DO ATENDIMENTO: %d/%d/%d\n", atendimento.daten.dia, atendimento.daten.mes, atendimento.daten.ano);
            printf("\t\t¡REA DE ATENDIMENTO: %s\n", atendimento.area);
            printf("\t\tNOME DO SUPERVISOR: %s\n", atendimento.nomesupervisor);

            printf("\t\t-------------------------------------------------------------------------------------------------\n");
            printf ("\n\n");

            i++;

        } else if (n == 2 && strcmp(atendimento.area, "ODONTOLOGIA")==1){

            printf("\t\t%d∫ ATENDIMENTO:\n", i);

            printf("\n\t\tC”DIGO DO ATENDIMENTO: %d\n", atendimento.codatendimento);
            printf("\t\tC”DIGO DO AGENDAMENTO: %d\n", atendimento.codagendamento);
            printf("\t\tDATA DA ATENDIMENTO: %d/%d/%d\n", atendimento.daten.dia, atendimento.daten.mes, atendimento.daten.ano);
            printf("\t\tNOME DO ALUNO: %s\n", atendimento.nomealuno);
            printf("\t\tC”DIGO DO ALUNO: %d\n", atendimento.codaluno);
            printf("\t\tNOME DO PACIENTE: %s\n", atendimento.nomepaciente);
            printf("\t\tC”DIGO DO PACIENTE: %d\n", atendimento.codpaciente);
            printf("\t\tDATA DO ATENDIMENTO: %d/%d/%d\n", atendimento.daten.dia, atendimento.daten.mes, atendimento.daten.ano);
            printf("\t\t¡REA DE ATENDIMENTO: %s\n", atendimento.area);
            printf("\t\tNOME DO SUPERVISOR: %s\n", atendimento.nomesupervisor);

            printf("\t\t-------------------------------------------------------------------------------------------------\n");
            printf ("\n\n");

            i++;

        } else if (n == 3 && strcmp(atendimento.area, "PSICOLOGIA")==1){

            printf("\t\t%d∫ ATENDIMENTO:\n", i);

            printf("\n\t\tC”DIGO DO ATENDIMENTO: %d\n", atendimento.codatendimento);
            printf("\t\tC”DIGO DO AGENDAMENTO: %d\n", atendimento.codagendamento);
            printf("\t\tDATA DA ATENDIMENTO: %d/%d/%d\n", atendimento.daten.dia, atendimento.daten.mes, atendimento.daten.ano);
            printf("\t\tNOME DO ALUNO: %s\n", atendimento.nomealuno);
            printf("\t\tC”DIGO DO ALUNO: %d\n", atendimento.codaluno);
            printf("\t\tNOME DO PACIENTE: %s\n", atendimento.nomepaciente);
            printf("\t\tC”DIGO DO PACIENTE: %d\n", atendimento.codpaciente);
            printf("\t\tDATA DO ATENDIMENTO: %d/%d/%d\n", atendimento.daten.dia, atendimento.daten.mes, atendimento.daten.ano);
            printf("\t\t¡REA DE ATENDIMENTO: %s\n", atendimento.area);
            printf("\t\tNOME DO SUPERVISOR: %s\n", atendimento.nomesupervisor);

            printf("\t\t-------------------------------------------------------------------------------------------------\n");
            printf ("\n\n");

            i++;
        }

    }

    fclose(arq);

    printf ("\t\tPRESSIONE ENTER PARA CONTINUAR...\n");
    system("pause");

}

void listar_aluno_especifico(){

    cabecalho();

    printf("\t\t=================================================================================================\n\n");
    printf("\t\t_____________________________________LISTA DE ATENDIMENTO_____________________________________________\n\n");

    int i = 1, mat;
    ATENDIMENTO atendimento;
    FILE *arq = fopen("atendimento.bin", "r+b");

    printf("\n\t\tDIGITE A MATRICULA DO ALUNO QUE VOC  DESEJA LISTAR: ");
    scanf("%d", mat);

    while(fread(&atendimento, sizeof(ATENDIMENTO), 1, arq) == 1){

        if (mat == atendimento.codaluno){

            printf("\t\t%d∫ ATENDIMENTO:\n", i);

            printf("\n\t\tC”DIGO DO ATENDIMENTO: %d\n", atendimento.codatendimento);
            printf("\t\tC”DIGO DO AGENDAMENTO: %d\n", atendimento.codagendamento);
            printf("\t\tDATA DA ATENDIMENTO: %d/%d/%d\n", atendimento.daten.dia, atendimento.daten.mes, atendimento.daten.ano);
            printf("\t\tNOME DO ALUNO: %s\n", atendimento.nomealuno);
            printf("\t\tC”DIGO DO ALUNO: %d\n", atendimento.codaluno);
            printf("\t\tNOME DO PACIENTE: %s\n", atendimento.nomepaciente);
            printf("\t\tC”DIGO DO PACIENTE: %d\n", atendimento.codpaciente);
            printf("\t\tDATA DO ATENDIMENTO: %d/%d/%d\n", atendimento.daten.dia, atendimento.daten.mes, atendimento.daten.ano);
            printf("\t\t¡REA DE ATENDIMENTO: %s\n", atendimento.area);
            printf("\t\tNOME DO SUPERVISOR: %s\n", atendimento.nomesupervisor);

            printf("\t\t-------------------------------------------------------------------------------------------------\n");
            printf ("\n\n");

            i++;
        }

    }

    fclose(arq);

    printf ("\t\tPRESSIONE ENTER PARA CONTINUAR...\n");
    system("pause");

}

void listar_paciente_especifico(){

    cabecalho();

    printf("\t\t=================================================================================================\n\n");
    printf("\t\t_____________________________________LISTA DE ATENDIMENTO_____________________________________________\n\n");

    int i = 1, cod;
    ATENDIMENTO atendimento;
    FILE *arq = fopen("atendimento.bin", "r+b");

    printf("\n\t\tDIGITE O C”DIGO DO PACIENTE QUE VOC  DESEJA LISTAR: ");
    scanf("%d", cod);

    while(fread(&atendimento, sizeof(ATENDIMENTO), 1, arq) == 1){

        if (cod == atendimento.codpaciente){

            printf("\t\t%d∫ ATENDIMENTO:\n", i);

            printf("\n\t\tC”DIGO DO ATENDIMENTO: %d\n", atendimento.codatendimento);
            printf("\t\tC”DIGO DO AGENDAMENTO: %d\n", atendimento.codagendamento);
            printf("\t\tDATA DA ATENDIMENTO: %d/%d/%d\n", atendimento.daten.dia, atendimento.daten.mes, atendimento.daten.ano);
            printf("\t\tNOME DO ALUNO: %s\n", atendimento.nomealuno);
            printf("\t\tC”DIGO DO ALUNO: %d\n", atendimento.codaluno);
            printf("\t\tNOME DO PACIENTE: %s\n", atendimento.nomepaciente);
            printf("\t\tC”DIGO DO PACIENTE: %d\n", atendimento.codpaciente);
            printf("\t\tDATA DO ATENDIMENTO: %d/%d/%d\n", atendimento.daten.dia, atendimento.daten.mes, atendimento.daten.ano);
            printf("\t\t¡REA DE ATENDIMENTO: %s\n", atendimento.area);
            printf("\t\tNOME DO SUPERVISOR: %s\n", atendimento.nomesupervisor);

            printf("\t\t-------------------------------------------------------------------------------------------------\n");
            printf ("\n\n");

            i++;
        }

    }

    fclose(arq);

    printf ("\t\tPRESSIONE ENTER PARA CONTINUAR...\n");
    system("pause");
}

void menu_listar_atendimento(){
    int n;

    do{

        cabecalho();

        printf ("\t\t__________________________________MENU DO LISTAR ATENDIMENTO___________________________________\n");
        printf ("\t\t#################################################################################################\n");
        printf ("\t\t=================================================================================================\n\n");

        printf ("\t\t\t\t\t\tSELECIONE A OP«√O DESEJADA:\n\n");

        printf ("\t\t\t\t\t1 - LISTAR TODOS OS ATENDIMENTOS\t\t2 - LISTAR POR ¡REAS ESPECÕFICAS\n\n");
        printf ("\t\t\t\t\t3 - LISTAR POR ALUNO ESPECÕFICO\t\t4 - LISTAR POR PACIENTE ESPECÕFICO\n\n");
        printf ("\t\t\t\t\t3 - SAIR\n\n");

        printf ("\t\tOPCAO: ");

        scanf ("%d", &n);

        if (n == 1){

            lista_atendimento();

        } else if (n == 2){

            listar_area();

        } else if (n == 3){

           listar_aluno_especifico();

        } else if (n == 4){

            listar_paciente_especifico();

        } else if (n != 5){

            printf("OPCAO INVALIDA POR FAVOR DIGITE UMA OPCAO VALIDA!\n");
            system("pause");

        }

    } while(n != 5);
}

void menu_atendimento(){

    int n;

    do{

        cabecalho();

        printf ("\t\t________________________________________MENU DO ATENDIMENTO_________________________________________\n");
        printf ("\t\t#################################################################################################\n");
        printf ("\t\t=================================================================================================\n\n");

        printf ("\t\t\t\t\t\tSELECIONE A OP«√O DESEJADA:\n\n");

        printf ("\t\t\t\t\t1 - CRIAR NOVO ATENDIMENTO\t\t2 - CANCELAR ATENDIMENTO\n\n");
        printf ("\t\t\t\t\t3 - LISTAR ATENDIMENTO\t\t4 - SAIR\n\n");
        //printf ("\t\t\t\t\t5 - PESQUISAR\t\t\t6 - SAIR\n\n");

        printf ("\t\tOPCAO: ");

        scanf ("%d", &n);

        if (n == 1){

            cria_atendimento();

        } else if (n == 2){

            cancela_atendimento();

        } else if (n == 3){

            menu_listar_atendimento();

        } else if (n != 4){

            printf("OPCAO INVALIDA POR FAVOR DIGITE UMA OPCAO VALIDA!\n");
            system("pause");

        }

    } while(n != 4);
}

int main (){
    setlocale(LC_ALL, "portuguese");

    //menu_aluno();

    menu_paciente();

    //menu_supervisor();
    //menu_agendamento();
    //menu_atendimento();

    return 0;
}
