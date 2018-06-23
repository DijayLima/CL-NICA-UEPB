#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <unistd.h>


typedef struct{
    char rua[20], numero[6], bairro[20], cep[12], estado[15];
}END;

typedef struct{
    int dia, mes, ano;
}DATNAS;

typedef struct{
    char nome[30], cpf[15];
    DATNAS dn;
    long int codpaciente ;
    END endereco;
}PACIENTE;

typedef struct{
    char nome[30], curso[30], cpf[15];
    long int matricula;
}ALUNOS;

typedef struct{
    char nome[30], curso[30];
    long int codprofessor;
}SUPERVISORES;

typedef struct{
    long long int codagendamento, codpaciente;
    char nomepaciente[30], area[15];
    DATNAS dc;
}AGENDAMENTO;

typedef struct{
    long long int codatendimento, codagendamento, codaluno, codpaciente, codsupervisor;
    DATNAS daten;
    char nomealuno[30], nomepaciente[30], area[20], nomesupervisor[30];

}ATENDIMENTO;

void inicializando(){
    int i;

    for(i=0; i<10; i++){

        system("cls");
        printf ("\n\t\t=================================================================================================\n");
        printf ("\t\t__________________________________________CLÕNICA UEPB___________________________________________\n\n");
        printf ("\t\t=================================================================================================\n\n");
        printf("\t\tINICIALIZANDO SISTEMA...");
        printf("\n\n\n\n\t\tAGUARDE UM MOMENTO!!");
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\tCARREGANDO... ");
        if (i%2 == 0){
            printf("\t||||||||||");
        } else if (i%2 == 1){
            printf("\t||||||||||||||||||||");
        }

        sleep(1);
    }
}

void finalizando(){
    int i;

    for(i=0; i<10; i++){

        system("cls");
        printf ("\n\t\t=================================================================================================\n");
        printf ("\t\t__________________________________________CLÕNICA UEPB___________________________________________\n\n");
        printf ("\t\t=================================================================================================\n\n");
        printf("\t\tFINALIZANDO SISTEMA...");
        printf("\n\n\n\n\t\tAT… LOGO!!");
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\tENCERRANDO... ");
        if (i%2 == 0){
            printf("\t||||||||||");
        } else if (i%2 == 1){
            printf("\t||||||||||||||||||||");
        }

        sleep(1);
    }
}

void timesystem(){

    time_t now;
    struct tm ts;
    char buf[80];

    now=time(NULL);

    ts = *localtime(&now);
    strftime(buf, sizeof(buf), "%d/%m/%Y %H:%M:%S", &ts);
    printf("\n\n      \t\t\t\t\t\t\t\t\t\t\t%s\n", buf);
}

void cabecalho(){

    system("cls");

    timesystem();
    printf ("\n\t\t=================================================================================================\n");
    printf ("\t\t__________________________________________CLÕNICA UEPB___________________________________________\n\n");
    printf ("\t\t=================================================================================================\n\n");

}

int encontrar_aluno(int mat, int alunopermitido){

    FILE *arq = fopen("aluno.bin", "r+b");
    ALUNOS aluno;

    rewind(arq);

    while(fread(&aluno, sizeof(ALUNOS), 1, arq)){
        if (aluno.matricula == mat && aluno.matricula != alunopermitido){

            fclose(arq);
            return 1;
        }
    }

    fclose(arq);
    return 0;
}

void cadastro_aluno(){

    ALUNOS aluno;
    long int mat, result;
    char op, nome[30], curso[20];

    do{

        FILE *arq = fopen("aluno.bin", "a+b");

        cabecalho();

        printf("\t\t=================================================================================================\n\n");
        printf("\t\t____________________________________CADASTRO DE ALUNO____________________________________________\n\n");

        printf ("\n\t\tDIGITE O NOME DO ALUNO: ");
        scanf (" %[^\n]s", nome);

        strcpy(aluno.nome, strupr(nome));

        printf ("\n\t\tDIGITE O CURSO DO ALUNO: ");
        scanf (" %[^\n]s", curso);

        strcpy(aluno.curso, strupr(curso));

        do{
            printf ("\n\t\tDIGITE A MATRICULA DO ALUNO: ");
            scanf ("%d", &mat);

            result = encontrar_aluno(mat, 0);

            if (result == 1){
                printf("\n\n\t\tALUNO J¡ EST¡ CADASTRADO, DIGITE UM NOVO C”DIGO!\n\n");
                continue;
            } else {
                aluno.matricula = mat;
            }

        }while(result != 0);

        printf ("\n\t\tDIGITE O CPF DO ALUNO(ESCREVA APENAS NUMEROS): ");
        scanf (" %[^\n]s", aluno.cpf);

        puts("\n\n\n");

        fwrite(&aluno, sizeof(ALUNOS), 1,arq);

        printf("\t\tNOME: %s\n\t\tCURSO: %s\n\t\tMATRICULA: %d\n\t\tCPF: %s\n", aluno.nome, aluno.curso, aluno.matricula, aluno.cpf);
        printf("\t\t-------------------------------------------------------------------------------------------------\n");
        printf ("\n\n");

        fclose(arq);

        printf("\n\t\tDESEJA CADASTRAR UM NOVO ALUNO(S/N)? ");
        scanf(" %c", &op);

    }while(op == 'S' || op == 's');

    printf ("\n\n\t\tPRESSIONE ENTER PARA CONTINUAR...\n");
    system("pause");
}

void remover_aluno(){

    ALUNOS aluno;
    int mat, result;
    char c, op, s;


    do{

       cabecalho();

        printf("\t\t=================================================================================================\n\n");
        printf("\t\t_________________________________________REMOVER ALUNO___________________________________________\n\n");


        FILE *arq = fopen("aluno.bin", "r+b"), *aux = fopen("new_aluno.bin", "a+b");


        printf ("\t\tDIGITE A MATRICULA DO ALUNO: ");
        scanf ("%d", &mat);

        result = encontrar_aluno(mat, 0);

        if (result == 1){

            printf("\n\t\tTEM CERTEZA QUE DESEJA REMOVER O ALUNO(S/N)? ");
            scanf (" %c", &c);

            if (c == 'S' || c == 's'){

                rewind(arq);

                while(fread(&aluno, sizeof(ALUNOS),1,arq) == 1){

                    if (mat != aluno.matricula){

                        fwrite(&aluno, sizeof(ALUNOS),1,aux);

                    }

                }

                fclose(arq);
                fclose(aux);

                system("del aluno.bin");
                system("ren new_aluno.bin aluno.bin");

                printf ("\n\n\t\tALUNO REMOVIDO COM SUCESSO!\n\n");

                printf("\t\tDESEJA REMOVER OUTRO ALUNO(S/N)? ");
                scanf(" %c", &s);

            } else {

                fclose(arq);
                fclose(aux);

                system("del new_aluno.bin");
                printf("\n\t\tALUNO NAO FOI REMOVIDO!\n");
                break;

            }

        } else {

            printf("\n\t\tALUNO N√O CADASTRADO, IMPOSSÕVEL REMOVER ALUNO!\n");

            printf("\n\t\tDESEJA DIGITAR OUTRA MATRÕCULA(S/N)? ");
            scanf(" %c", &op);

            if (op == 's' || op == 'S'){

                fclose(arq);
                fclose(aux);

                system("del new_aluno.bin");

                s = 's';

            } else {


                fclose(arq);
                fclose(aux);

                system("del new_aluno.bin");
                printf("\n\t\tN√O FOI REMOVIDO NENHUM ALUNO!\n");
                break;

            }

        }



    }while(s == 'S' || s == 's');



    printf ("\n\t\tPRESSIONE ENTER PARA CONTINUAR...\n");
    system("pause");

}

void editar_aluno(){

    int mat, result, matp;
    char nome[30], curso[20], op, s, cpf[20];
    ALUNOS aluno, new_dados;

    do{
       cabecalho();

        printf("\t\t=================================================================================================\n\n");
        printf("\t\t____________________________________EDITAR ALUNO_________________________________________________\n\n");


        FILE *arq = fopen("aluno.bin", "a+b"), *aux = fopen("new_aluno.bin", "a+b");


        printf ("\n\t\tDIGITE A MATRICULA DO ALUNO: ");
        scanf ("%d", &mat);

        result = encontrar_aluno(mat, 0);


        if (result == 1){

            matp = mat;
            while(fread(&aluno, sizeof(ALUNOS),1,arq)==1){

                if (mat == aluno.matricula){

                    printf("\n\t\tDIGITE OS NOVOS DADOS DO ALUNO: \n\n");

                    printf ("\n\t\t\t\tNOME DO ALUNO: ");
                    scanf (" %[^\n]s", nome);

                    strcpy(new_dados.nome, strupr(nome));

                    printf ("\n\t\t\t\tDIGITE O CURSO DO ALUNO: ");
                    scanf (" %[^\n]s", curso);

                    strcpy(new_dados.curso, strupr(curso));

                    do{
                        printf ("\n\t\t\t\tA MATRICULA DO ALUNO: ");
                        scanf ("%d", &mat);

                        result = encontrar_aluno(mat, matp);

                        if (result == 1){
                            printf("\n\n\t\tALUNO J¡ EST¡ CADASTRADO, DIGITE UM NOVO C”DIGO!\n\n");
                            continue;
                        } else {
                            new_dados.matricula = mat;
                        }

                    }while(result != 0);


                    printf ("\n\t\t\t\tO CPF DO ALUNO(ESCREVA APENAS NUMEROS): ");
                    scanf (" %[^\n]s", new_dados.cpf);

                    fwrite(&new_dados, sizeof(ALUNOS), 1, aux);

                } else {

                    fwrite(&aluno, sizeof(ALUNOS),1,aux);

                }
            }

            fclose(arq);
            fclose(aux);

            system("del aluno.bin");
            system("ren new_aluno.bin aluno.bin");

            printf("\n\t\tDADOS DO ALUNO EDITADOS COM SUCESSO!\n\n");

            printf("\t\tNOME: %s\n\t\tCURSO: %s\n\t\tMATRICULA: %d\n\t\tCPF: %s\n", new_dados.nome, new_dados.curso, new_dados.matricula, new_dados.cpf);
            printf("\t\t-------------------------------------------------------------------------------------------------\n");
            printf ("\n\n");

            printf("\t\tDESEJA EDITAR OUTRO ALUNO(S/N)? ");
            scanf(" %c", &s);

        } else {

            printf("\n\n\t\tALUNO N√O CADASTRADO, IMPOSSÕVEL EDITAR ALUNO!\n");

            printf("\n\t\tDESEJA DIGITAR OUTRA MATRÕCULA(S/N)? ");
            scanf(" %c", &op);

            if (op == 's' || op == 'S'){

                fclose(arq);
                fclose(aux);

                system("del new_aluno.bin");

                s = 's';

            } else {

                fclose(arq);
                fclose(aux);

                system("del new_aluno.bin");
                printf("\n\t\tALUNO N√O FOI EDITADO!\n");
                break;
            }

        }

    }while(s == 'S' || s == 's');


    printf ("\n\t\tPRESSIONE ENTER PARA CONTINUAR...\n");
    system("pause");

}

void listar_alunos(){

    cabecalho();

    printf("\t\t=================================================================================================\n\n");
    printf("\t\t_____________________________________LISTA DE ALUNOS_____________________________________________\n\n");

    ALUNOS aluno;
    FILE *arq = fopen("aluno.bin", "r+b");
    int i = 1;

    if (fread(&aluno, sizeof(ALUNOS), 1, arq) == 1){

        rewind(arq);

        while(fread(&aluno, sizeof(ALUNOS), 1, arq) == 1){

            printf("\t\t%d∫ ALUNO:\n", i);

            printf("\n\t\tNOME: %s\n\t\tCURSO: %s\n\t\tMATRICULA: %d\n\t\tCPF: %s\n", aluno.nome, aluno.curso, aluno.matricula, aluno.cpf);
            printf("\t\t-------------------------------------------------------------------------------------------------\n");
            printf ("\n\n");

            i++;
        }
    } else {
        printf("\n\t\tAINDA N√O EXISTE ALUNOS CADASTRADOS!\n");
    }

    fclose(arq);

    printf ("\n\t\tPRESSIONE ENTER PARA CONTINUAR...\n");
    system("pause");
}

void pesquisar_aluno(){

    int cont = 0;
    char name[30], op;
    ALUNOS aluno;

    do{
        cabecalho();

        printf("\t\t=================================================================================================\n\n");
        printf("\t\t_________________________________________PESQUISAR ALUNO_________________________________________\n\n");

        FILE *arq = fopen("aluno.bin", "r+b");
        cont = 0;

        printf ("\n\t\tDIGITE O NOME DO ALUNO: ");
        scanf (" %[^\n]s", name);

        strcpy(name, strupr(name));

        rewind(arq);

        while(fread(&aluno, sizeof(ALUNOS), 1, arq) == 1){

            if (strstr(aluno.nome, name)!=NULL){

                printf("\n\n\t\tNOME: %s\n\t\tCURSO: %s\n\t\tMATRICULA: %d\n\t\tCPF: %s\n\n", aluno.nome, aluno.curso, aluno.matricula, aluno.cpf);

                printf("\t\t-------------------------------------------------------------------------------------------------\n");

                printf ("\n\n");

                cont ++;
            }
        }

        if (cont == 0){

            printf("\n\t\tALUNO N√O CADASTRADO!\n\n");

        }

        fclose(arq);

        printf("\n\t\tDESEJA PESQUISAR UM NOVO ALUNO(S/N)? ");
        scanf(" %c", &op);

    }while(op == 's' || op == 'S');

    printf ("\n\n\t\tPRESSIONE ENTER PARA CONTINUAR...\n\n");
    system("pause");
}

void menu_aluno(){

    int n;

    do{
        cabecalho();

        printf ("\t\t__________________________________________MENU DO ALUNO__________________________________________\n\n");

        printf ("\t\t=================================================================================================\n\n");

        printf ("\n\n\t\t\t\t\t\tSELECIONE A OP«√O DESEJADA:\n\n");
        printf ("\n\t\t\t\t\t1 - CADASTRAR ALUNO\t\t2 - REMOVER ALUNO\n\n");
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



int encontrar_paciente(int cod, int codv){

    FILE *arq = fopen("paciente.bin", "r+b");
    PACIENTE paciente;

    while(fread(&paciente, sizeof(PACIENTE), 1, arq)){
        if (paciente.codpaciente == cod && paciente.codpaciente != codv){

            fclose(arq);
            return 1;

        }
    }

    fclose(arq);
    return 0;
}

void cadastro_paciente(){

    PACIENTE paciente;

    int result, cod;
    char op, nome[30], rua[20], bairro[20], num[8], cep[15], est[20];

    do {
        cabecalho();

        printf("\t\t=================================================================================================\n\n");
        printf("\t\t_______________________________________CADASTRO DE PACIENTE______________________________________\n\n");

        FILE *arq = fopen("paciente.bin", "a+b");

        printf ("\n\t\tDIGITE O NOME DO PACIENTE: ");
        scanf (" %[^\n]s", nome);

        strcpy(paciente.nome, strupr(nome));

        do{
            printf ("\n\t\tDIGITE O C”DIGO DO PACIENTE: ");
            scanf (" %d", &cod);

            result = encontrar_paciente(cod, 0);

            if (result == 1){

                printf("\n\t\tPACIENTE J¡ CADASTRADO, POR FAVOR DIGITE UM NOVO C”DIGO!\n\n");
                continue;

            } else {
                paciente.codpaciente = cod;
            }

        }while(result != 0);


        printf ("\n\t\tDIGITE A DATA DE NASCIMENTO(DD MM AAAA): ");
        scanf ("%d %d %d", &paciente.dn.dia, &paciente.dn.mes, &paciente.dn.ano);

        printf ("\n\t\tDIGITE O CPF DO PACIENTE(ESCREVA APENAS NUMEROS): ");
        scanf (" %[^\n]s", paciente.cpf);

        printf("\n\t\tENDERE«O DO PACIENTE: \n");

        printf("\n\t\t\tRUA: ");
        scanf(" %[^\n]s", rua);
        strcpy(paciente.endereco.rua, strupr(rua));

        printf("\n\t\t\tBAIRRO: ");
        scanf(" %[^\n]s", bairro);
        strcpy(paciente.endereco.bairro, strupr(bairro));

        printf("\n\t\t\tNUMERO: ");
        scanf(" %[^\n]s", num);
        strcpy(paciente.endereco.numero, strupr(num));

        printf("\n\t\t\tCEP: ");
        scanf(" %[^\n]s", cep);
        strcpy(paciente.endereco.cep, strupr(cep));

        printf("\n\t\t\tESTADO: ");
        scanf(" %[^\n]s", est);
        strcpy(paciente.endereco.estado, strupr(est));

        puts("\n\n\n");

        fwrite(&paciente, sizeof(PACIENTE),1,arq);

        printf("\n\t\tNOME: %s\n", paciente.nome);
        printf("\n\t\tC”DIGO DO PACIENTE: %d\n", paciente.codpaciente);
        printf("\n\t\tDATA DE NASCIMENTO: %d/%d/%d\n", paciente.dn.dia, paciente.dn.mes, paciente.dn.ano);
        printf("\n\t\tCPF: %s\n", paciente.cpf);
        printf("\n\t\tENDERECO: \n");
        printf("\n\t\t\tRUA: %s\n", paciente.endereco.rua);
        printf("\n\t\t\tBAIRRO: %s\n", paciente.endereco.bairro);
        printf("\n\t\t\tNUMERO: %s\n", paciente.endereco.numero);
        printf("\n\t\t\tCEP: %s\n",  paciente.endereco.cep);
        printf("\n\t\t\tESTADO: %s\n", paciente.endereco.estado);

        printf("\t\t-------------------------------------------------------------------------------------------------\n");
        printf ("\n\n");


        fclose(arq);

        printf ("\n\t\tDESEJA CADASTRAR UM NOVO PACIENTE(S/N)? ");
        scanf(" %c", &op);

    }while(op == 's' || op == 'S');

    printf ("\n\t\tPRESSIONE ENTER PARA CONTINUAR...\n");
    system("pause");
}

void listar_paciente(){

    cabecalho();

    printf("\t\t=================================================================================================\n\n");
    printf("\t\t______________________________________LISTA DE PACIENTES_________________________________________\n\n");

    int i = 1;
    PACIENTE paciente;
    FILE *arq = fopen("paciente.bin", "r+b");

    if (fread(&paciente, sizeof(PACIENTE), 1, arq) == 1){

        rewind(arq);
        while(fread(&paciente, sizeof(PACIENTE), 1, arq) == 1){

            printf("\t\t%d∫ PACIENTE:\n", i);

            printf("\n\t\tNOME: %s\n", paciente.nome);
            printf("\n\t\tC”DIGO DO PACIENTE: %d\n", paciente.codpaciente);
            printf("\n\t\tDATA DE NASCIMENTO: %d/%d/%d\n", paciente.dn.dia, paciente.dn.mes, paciente.dn.ano);
            printf("\n\t\tCPF: %s\n", paciente.cpf);
            printf("\n\t\tENDERECO: \n");
            printf("\n\t\t\tRUA: %s\n", paciente.endereco.rua);
            printf("\n\t\t\tBAIRRO: %s\n", paciente.endereco.bairro);
            printf("\n\t\t\tNUMERO: %s\n", paciente.endereco.numero);
            printf("\n\t\t\tCEP: %s\n",  paciente.endereco.cep);
            printf("\n\t\t\tESTADO: %s\n", paciente.endereco.estado);

            printf("\t\t-------------------------------------------------------------------------------------------------\n");
            printf ("\n\n");

            i++;
        }
    } else {
        printf("\n\t\tAINDA N√O EXISTE PACIENTES CADASTRADOS!\n\n");
    }


    fclose(arq);

    printf ("\t\tPRESSIONE ENTER PARA CONTINUAR...\n");
    system("pause");
}

void remover_paciente(){

    PACIENTE paciente;
    int codigo, result;
    char c, op, s;

    do{
        cabecalho();

        printf("\t\t=================================================================================================\n\n");
        printf("\t\t____________________________________REMOVER PACIENTE_____________________________________________\n\n");


        FILE *arq = fopen("paciente.bin", "r+b"), *aux = fopen("new_paciente.bin", "a+b");


        printf ("\n\t\tDIGITE C”DIGO DO PACIENTE: ");
        scanf ("%d", &codigo);

        result = encontrar_paciente(codigo, 0);

        if (result == 1){

            printf("\n\t\tTEM CERTEZA QUE DESEJA REMOVER O PACIENTE(S/N)? ");
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

                system("del paciente.bin");
                system("ren new_paciente.bin paciente.bin");

                printf ("\n\n\t\tPACIENTE REMOVIDO COM SUCESSO!\n");

                printf("\n\t\tDESEJA REMOVER OUTRO PACIENTE(S/N)? ");
                scanf(" %c", &op);

            } else {

                printf("\n\n\t\tPACIENTE NAO FOI REMOVIDO!\n\n");

                fclose(arq);
                fclose(aux);
                system("del new_paciente.bin");

            }
        } else {

            printf("\n\t\tPACIENTE N√O CADASTRADO, IMPOSSÕVEL REMOVER PACIENTE!\n");

            printf("\n\t\tDESEJA DIGITAR OUTRO C”DIGO(S/N)? ");
            scanf(" %c", &s);

            if (s == 's' || s == 'S'){

                fclose(arq);
                fclose(aux);

                system("del new_paciente.bin");

                op = 's';

            } else {

                fclose(arq);
                fclose(aux);

                system("del new_paciente.bin");

                printf("\n\n\t\tPACIENTE N√O FOI REMOVIDO!\n");
                break;

            }
        }

    }while(op == 'S' || op == 's');

    printf ("\n\t\tPRESSIONE ENTER PARA CONTINUAR...\n");
    system("pause");
}

void editar_paciente(){

    int codpaciente, result, cod, codv;
    char op, s, rua[20], bairro[20], num[8], cep[15], est[20], nome[30];
    PACIENTE paciente, new_dados;

    do{

        cabecalho();

        printf("\t\t================================================================================================\n\n");
        printf("\t\t____________________________________EDITAR  PACIENTE_____________________________________________\n\n");


        FILE *arq = fopen("paciente.bin", "a+b"), *aux = fopen("new_paciente.bin", "a+b");


        printf ("\n\t\tDIGITE O C”DIGO DO PACIENTE: ");
        scanf ("%d", &cod);

        result = encontrar_paciente(cod, 0);

        if (result == 1){

            codv = cod;

            while(fread(&paciente, sizeof(PACIENTE),1,arq)==1){

                if (cod == paciente.codpaciente){

                    printf("\n\n\t\tDIGITE OS NOVOS DADOS DO PACIENTE: \n\n");

                    printf ("\t\t\t\tDIGITE O NOME DO PACIENTE: ");
                    scanf (" %[^\n]s", nome);
                    strcpy(new_dados.nome, strupr(nome));

                    do{

                        printf ("\n\t\t\t\tO C”DIGO DO PACIENTE: ");
                        scanf ("%d", &codpaciente);

                        result = encontrar_paciente(codpaciente, codv);

                        if (result == 1){
                            printf("\n\n\t\tPACIENTE J¡ EST¡ CADASTRADO, DIGITE UM NOVO C”DIGO!\n");
                            continue;
                        } else {
                            new_dados.codpaciente = codpaciente;
                        }

                    }while(result != 0);

                    printf ("\n\t\t\t\tDIGITE A DATA DE NASCIMENTO(DD MM AAAA): ");
                    scanf ("%d %d %d", &new_dados.dn.dia, &new_dados.dn.mes, &new_dados.dn.ano);

                    printf ("\n\t\t\t\tO CPF DO PACIENTE(ESCREVA APENAS NUMEROS): ");
                    scanf ("% [^\n]s", paciente.cpf);

                    printf("\n\t\tENDERE«O DO PACIENTE: \n");

                    printf("\n\t\t\t\t\tRUA: ");
                    scanf(" %[^\n]s", rua);
                    strcpy(new_dados.endereco.rua, strupr(rua));

                    printf("\n\t\t\t\t\tBAIRRO: ");
                    scanf(" %[^\n]s", bairro);
                    strcpy(new_dados.endereco.bairro, strupr(bairro));

                    printf("\n\t\t\t\t\tNUMERO: ");
                    scanf(" %[^\n]s", num);
                    strcpy(new_dados.endereco.numero, strupr(num));

                    printf("\n\t\t\t\t\tCEP: ");
                    scanf(" %[^\n]s", cep);
                    strcpy(new_dados.endereco.cep, strupr(cep));

                    printf("\n\t\t\t\t\tESTADO: ");
                    scanf(" %[^\n]s", est);
                    strcpy(new_dados.endereco.estado, strupr(est));

                    printf("\n\t\tNOME: %s\n", new_dados.nome);
                    printf("\n\t\tC”DIGO DO PACIENTE: %d\n", new_dados.codpaciente);
                    printf("\n\t\tDATA DE NASCIMENTO: %d/%d/%d\n", new_dados.dn.dia, paciente.dn.mes, paciente.dn.ano);
                    printf("\n\t\tCPF: %s\n", new_dados.cpf);
                    printf("\n\t\tENDERECO: \n");
                    printf("\n\t\t\tRUA: %s\n", new_dados.endereco.rua);
                    printf("\n\t\t\tBAIRRO: %s\n", new_dados.endereco.bairro);
                    printf("\n\t\t\tNUMERO: %s\n", new_dados.endereco.numero);
                    printf("\n\t\t\tCEP: %s\n",  new_dados.endereco.cep);
                    printf("\n\t\t\tESTADO: %s\n", new_dados.endereco.estado);

                    printf("\t\t-------------------------------------------------------------------------------------------------\n");
                    printf ("\n\n");

                    fwrite(&new_dados, sizeof(PACIENTE),1,aux);

                } else {

                    fwrite(&paciente, sizeof(PACIENTE),1,aux);

                }
            }

            fclose(arq);
            fclose(aux);

            system("del paciente.bin");
            system("ren new_paciente.bin paciente.bin");

            printf("\n\t\tDADOS DO PACIENTE EDITADOS COM SUCESSO!\n\n");

            printf("\t\tDESEJA EDITAR OUTRO PACIENTE(S/N)? ");
            scanf(" %c", &op);

        } else {

            printf("\n\t\tPACIENTE N√O CADASTRADO, IMPOSSÕVEL EDITAR PACIENTE!\n");

            printf("\n\t\tDESEJA DIGITAR OUTRO C”DIGO(S/N)? ");
            scanf(" %c", &s);

            if (s == 's' || s == 'S'){

                fclose(arq);
                fclose(aux);

                system("del new_paciente.bin");

                op = 's';

            } else {

                fclose(arq);
                fclose(aux);

                system("del new_paciente.bin");

                printf("\n\n\t\tNENHUM PACIENTE FOI EDITADO!\n");
                break;
            }
        }

    }while(op == 'S' || op == 's');

    printf ("\n\t\tPRESSIONE ENTER PARA CONTINUAR...\n");
    system("pause");
}

void pesquisar_paciente(){

    int cont = 0;
    char name[30], op;
    PACIENTE paciente;


    do{
        cabecalho();

        printf("\t\t=================================================================================================\n\n");
        printf("\t\t_____________________________________PESQUISAR PACIENTE______________________________________________\n\n");

        FILE *arq = fopen("paciente.bin", "r+b");

        cont = 0;

        printf ("\t\tDIGITE O NOME DO PACIENTE: ");
        scanf (" %[^\n]s", name);

        rewind(arq);

        while(fread(&paciente, sizeof(PACIENTE), 1, arq) == 1){

            if (strstr(paciente.nome, strupr(name))!= NULL){

                printf("\n\t\tNOME: %s\n", paciente.nome);
                printf("\t\tC”DIGO DO PACIENTE: %d\n", paciente.codpaciente);
                printf("\t\tDATA DE NASCIMENTO: %d/%d/%d\n", paciente.dn.dia, paciente.dn.mes, paciente.dn.ano);
                printf("\t\tCPF: %s\n", paciente.cpf);
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

        fclose(arq);

        printf("\t\tDESEJA PESQUISAR UM NOVO PACIENTE(S/N)?");
        scanf(" %c", &op);

    }while(op == 's' || op == 'S');

    printf ("\n\n\t\tPRESSIONE ENTER PARA CONTINUAR...\n\n");
    system("pause");
}

void menu_paciente(){
    int n;

    do{
        cabecalho();

        printf ("\t\t________________________________________MENU DO PACIENTE_________________________________________\n\n");

        printf ("\t\t=================================================================================================\n\n");

        printf ("\n\n\t\t\t\t\t\tSELECIONE A OP«√O DESEJADA:\n\n");

        printf ("\n\t\t\t\t\t1 - CADASTRAR PACIENTE\t\t2 - REMOVER PACIENTE\n\n");
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



int encontrar_supervisor(int cod, int codvalido){

    FILE *arq = fopen("supervisores.bin", "r+b");
    SUPERVISORES supervisor;

    while(fread(&supervisor, sizeof(SUPERVISORES), 1, arq)){

        if (supervisor.codprofessor == cod && supervisor.codprofessor != codvalido){

            fclose(arq);
            return 1;

        }
    }

    fclose(arq);
    return 0;
}


void cadastro_supervisor(){

    SUPERVISORES supervisores;
    int result, cod;
    char op, nome[30], curso[20];

    do {
        cabecalho();

        printf("\t\t=================================================================================================\n\n");
        printf("\t\t____________________________________CADASTRO DE SUPERVISORES_____________________________________\n\n");

        FILE *arq = fopen("supervisores.bin", "a+b");

        printf ("\n\t\tDIGITE O NOME DO SUPERVISOR: ");
        scanf (" %[^\n]s", nome);

        strcpy(supervisores.nome, strupr(nome));

        do{

            printf ("\n\t\tDIGITE O C”DIGO DO SUPERVISOR: ");
            scanf ("%d", &cod);

            result = encontrar_supervisor(cod, 0);

            if (result == 1){

                printf("\n\t\tSUPERVISOR J¡ EST¡ CADASTRADO, POR FAVOR DIGITE UM NOVO C”DIGO!\n");
                continue;

            } else {
                supervisores.codprofessor = cod;
            }

        }while(result != 0);


        printf ("\n\t\tDIGITE O CURSO DO SUPERVISOR: ");
        scanf(" %[^\n]s", curso);

        strcpy(supervisores.curso, strupr(curso));

        printf("\n\t\tNOME: %s\n", supervisores.nome);
        printf("\n\t\tC”DIGO DO SUPERVISOR: %d\n", supervisores.codprofessor);
        printf("\n\t\tCURSO DO SUPERVISOR: %s\n", supervisores.curso);

        printf("\t\t-------------------------------------------------------------------------------------------------\n");
        printf ("\n\n");

        fwrite(&supervisores, sizeof(SUPERVISORES),1,arq);

        fclose(arq);

        printf ("\t\tDESEJA CADASTRAR UM NOVO SUPERVISOR(S/N)? ");
        scanf(" %c", &op);

    }while(op == 's' || op == 'S');

    printf ("\n\n\t\tPRESSIONE ENTER PARA CONTINUAR...\n\n");
    system("pause");
}

void remover_supervisor(){

    SUPERVISORES supervisores;
    int codigo, result;
    char c, op, s;

    do {

        cabecalho();

        printf ("\t\t=================================================================================================\n");
        printf("\t\t____________________________________REMOVER SUPERVISOR____________________________________________\n\n");


        FILE *arq = fopen("supervisores.bin", "r+b"), *aux = fopen("new_supervisor.bin", "a+b");


        printf ("\n\t\tDIGITE C”DIGO DO SUPERVISOR: ");
        scanf ("%d", &codigo);

        result = encontrar_supervisor(codigo, 0);

        if (result == 1){

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

                    system("del supervisores.bin");
                    system("ren new_supervisor.bin supervisores.bin");

                    printf ("\n\t\tSUPERVISOR REMOVIDO COM SUCESSO!\n\n");

                    printf("\t\tDESEJA REMOVER OUTRO SUPERVISOR(S/N)? ");
                    scanf(" %c", &op);

                } else {

                    fclose(arq);
                    fclose(aux);

                    system("del new_supervisor.bin");

                    printf("\n\nSUPERVISOR N√O FOI REMOVIDO!\n");

                }

        } else {

            printf("\n\t\tSUPERVISOR N√O CADASTRADO, IMPOSSÕVEL REMOVER SUPERVISOR!\n");

            printf("\n\t\tDESEJA DIGITAR OUTRO C”DIGO(S/N)? ");
            scanf(" %c", &s);

            if (s == 's' || s == 'S'){

                fclose(arq);
                fclose(aux);

                system("del new_supervisor.bin");

                op = 's';

            } else {

                fclose(arq);
                fclose(aux);

                system("del new_supervisor.bin");
                printf("\n\t\tN√O FOI REMOVIDO NENHUM SUPERVISOR!\n");
                break;

            }
        }


    }while(op == 's' || op == 'S');

    printf ("\n\n\t\tPRESSIONE ENTER PARA CONTINUAR...\n\n");
    system("pause");
}

void editar_supervisor(){

    int codprofessor, result, cod, codv;
    char s, op, nome[30], curso[20];
    SUPERVISORES supervisores, new_dados;

    do{
        cabecalho();

        printf("\t\t=================================================================================================\n");
        printf("\t\t____________________________________EDITAR SUPERVISOR____________________________________________\n\n");


        FILE *arq = fopen("supervisores.bin", "a+b"), *aux = fopen("new_supervisor.bin", "a+b");

        printf ("\n\t\tDIGITE O C”DIGO DO SUPERVISOR QUE DESEJA EDITAR: ");
        scanf ("%d", &codprofessor);

        result = encontrar_supervisor(codprofessor, 0);

        if(result == 1){

            codv =codprofessor;

            while(fread(&supervisores, sizeof(SUPERVISORES),1,arq)==1){

                if (codprofessor == supervisores.codprofessor){

                    printf("\n\t\tDIGITE OS NOVOS DADOS DO SUPERVISOR: \n\n");

                    printf ("\t\t\t\tDIGITE O NOME DO SUPERVISOR: ");
                    scanf (" %[^\n]s", nome);

                    strcpy(new_dados.nome, strupr(nome));

                    do{
                        printf ("\n\t\t\t\tO C”DIGO DO SUPERVISOR: ");
                        scanf ("%d", &cod);

                        result = encontrar_supervisor(cod, codv);

                        if (result == 1){

                            printf("\n\t\tSUPERVISOR J¡ EST¡ CADASTRADO, DIGITE UM NOVO C”DIGO!\n");
                            continue;

                        } else {
                            new_dados.codprofessor = cod;
                        }

                    }while(result != 0);

                    printf ("\n\t\t\t\tDIGITE O CURSO DO SUPERVISOR: ");
                    scanf(" %[^\n]s", curso);

                    strcpy(new_dados.curso, strupr(curso));

                    printf("\n\t\tNOME: %s\n", new_dados.nome);
                    printf("\n\t\tC”DIGO DO SUPERVISOR: %d\n", new_dados.codprofessor);
                    printf("\n\t\tCURSO DO SUPERVISOR: %s\n", new_dados.curso);

                    printf("\t\t-------------------------------------------------------------------------------------------------\n");
                    printf ("\n\n");

                    fwrite(&new_dados, sizeof(SUPERVISORES),1,aux);

                } else {

                    fwrite(&supervisores, sizeof(SUPERVISORES),1,aux);

                }
            }

            fclose(arq);
            fclose(aux);

            system("del supervisores.bin");
            system("ren new_supervisor.bin supervisores.bin");

            printf("\n\t\tDADOS DO SUPERVISOR EDITADOS COM SUCESSO!\n");

            printf("\n\t\tDESEJA EDITAR OUTRO SUPERVISOR(S/N)? ");
            scanf(" %c", &s);

        } else {

            printf("\n\t\tSUPERVISOR N√O CADASTRADO, IMPOSSÕVEL EDITAR SUPERVISOR!\n");

            printf("\n\t\tDESEJA DIGITAR OUTRO C”DIGO(S/N)? ");
            scanf(" %c", &op);

            if (op == 's' || op == 'S'){

                fclose(arq);
                fclose(aux);

                system("del new_supervisor.bin");

                s = 's';

            } else {

                fclose(arq);
                fclose(aux);

                system("del new_supervisor.bin");
                printf("\n\t\tNENHUM SUPERVISOR FOI EDITADO!\n");
                break;

            }

        }


    }while(s == 's' || s == 'S');

    printf ("\n\n\t\tPRESSIONE ENTER PARA CONTINUAR...\n\n");
    system("pause");
}

void listar_supervisor(){

    cabecalho();

    printf ("\t\t=================================================================================================\n");
    printf("\t\t___________________________________LISTA DE SUPERVISORES__________________________________________\n\n");

    int i = 1;
    SUPERVISORES supervisores;
    FILE *arq = fopen("supervisores.bin", "r+b");


        while(fread(&supervisores, sizeof(SUPERVISORES), 1, arq) == 1){

            printf("\t\t%d∫ SUPERVISORES:\n", i);

            printf("\n\t\tNOME: %s\n", supervisores.nome);
            printf("\n\t\tC”DIGO DO SUPERVISOR: %d\n", supervisores.codprofessor);
            printf("\n\t\tCURSO DO SUPERVISOR: %s\n", supervisores.curso);

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
    char name[30], op;
    SUPERVISORES supervisores;

    do{
        cabecalho();

        printf("\t\t=================================================================================================\n\n");
        printf("\t\t_____________________________________PESQUISAR SUPERVISOR________________________________________\n\n");

        cont = 0;
        FILE *arq = fopen("supervisores.bin", "r+b");

        printf ("\t\tDIGITE O NOME DO SUPERVISOR: ");
        scanf (" %[^\n]s", name);

        rewind(arq);

        while(fread(&supervisores, sizeof(SUPERVISORES), 1, arq) == 1){

            if (strstr(strupr(name), supervisores.nome)!=NULL){

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
        fclose(arq);

        printf("\t\tDESEJA PESQUISAR UM NOVO SUPERVISOR(S/N)?");
        scanf(" %c", &op);

    }while(op == 's' || op == 'S');
}

void menu_supervisor(){

    int n;

    do{
        cabecalho();

        printf ("\t\t________________________________________MENU DO SUPERVISOR_______________________________________\n\n");

        printf ("\t\t=================================================================================================\n\n");

        printf ("\n\n\t\t\t\t\t\tSELECIONE A OP«√O DESEJADA:\n\n");

        printf ("\n\t\t\t\t\t1 - CADASTRAR SUPERVISOR\t2 - REMOVER SUPERVISOR\n\n");
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



int encontrar_agendamento(int cod){

    FILE *arq = fopen("agendamento.bin", "r+b");
    AGENDAMENTO agendamento;

    while(fread(&agendamento, sizeof(AGENDAMENTO), 1, arq)){

        if (agendamento.codagendamento == cod){

            fclose(arq);
            return 1;

        }
    }

    fclose(arq);
    return 0;
}


int verificar_area(int cod, char area[]){

    FILE *arq = fopen("agendamento.bin", "r+b");
    AGENDAMENTO agendamento;

    rewind(arq);

    while(fread(&agendamento, sizeof(AGENDAMENTO), 1, arq)){

        if ((cod == agendamento.codpaciente) && (strcmp(agendamento.area, area)==0)){

                fclose(arq);
                return 1;
            }
    }

    fclose(arq);
    return 0;
}

void cria_agendamento(){

    AGENDAMENTO agendamento;
    PACIENTE paciente;
    int result, volta, cod, n, codag, retorno;
    char op, area[20];

    do{

        cabecalho();

        printf("\t\t=================================================================================================\n");
        printf("\t\t________________________________________NOVO AGENDAMENTO_________________________________________\n\n");

        FILE *arq = fopen("agendamento.bin", "a+b"), *arqpaciente = fopen("paciente.bin", "r+b");

        srand( (unsigned)time(NULL));

        while(1){
            codag = 1000 + rand();
            retorno = encontrar_agendamento(codag);
            if(retorno == 1){
                continue;
            } else {
                agendamento.codagendamento = codag;
                break;
            }
        }

        do{
            printf ("\n\t\tDIGITE O C”DIGO DO PACIENTE: ");
            scanf ("%d", &cod);

            result = encontrar_paciente(cod, 0);

            if (result == 1){

                agendamento.codpaciente = cod;

                while(fread(&paciente, sizeof(PACIENTE), 1, arqpaciente) == 1){

                    if (cod == paciente.codpaciente){

                        strcpy(agendamento.nomepaciente, paciente.nome);

                        break;

                    }

                }

            } else {

                printf("\n\t\tPACIENTE N√O EST¡ CADASTRADO, POR FAVOR DIGITE UM C”DIGO NOVAMENTE!\n\n");
                continue;

            }

        }while(result != 1);

        while(1){

            printf("\n\t\tSELECIONE A ¡REA DE ATENDIMENTO: \n\n");
            printf("\t\t\t\t1 - FISIOTERAPIA\n\t\t\t\t2 - ODONTOLOGIA\n\t\t\t\t3 - PSICOLOGIA");

            printf("\n\n\t\tOP«√O: ");
            scanf("%d", &n);

            if (n == 1){

                   strcpy(area, "FISIOTERAPIA");

            } else if (n == 2){

                    strcpy(area, "ODONTOLOGIA");

             } else if (n == 3){

                    strcpy(area, "PSICOLOGIA");

              } else {

                    printf("\n\n\t\tOP«√O INV¡LIDA, POR FAVOR SELECIONE UMA V¡LIDA!");
                    continue;

              }

              volta = verificar_area(cod, area);

              if (volta == 1){

                    printf("\n\n\t\tPACIENTE J¡ POSSUI AGENDAMENTO NESSA ¡REA POR FAVOR SELECIONE OUTRA ¡REA!\n\n");
                    continue;

              } else {

                    strcpy(agendamento.area, area);
                    break;

              }


        }

        printf("\n\t\tDIGITE A DATA DE ATENDIMENTO(DD MM AAAA): ");
        scanf("%d %d %d", &agendamento.dc.dia, &agendamento.dc.mes, &agendamento.dc.ano);

        printf("\n\t\tC”DIGO DO AGENDAMENTO: %d\n", agendamento.codagendamento);
        printf("\n\t\tNOME DO PACIENTE: %s\n", agendamento.nomepaciente);
        printf("\n\t\tC”DIGO DO PACIENTE: %d\n", agendamento.codpaciente);
        printf("\n\t\t¡REA DE ATENDIMENTO: %s\n", agendamento.area);
        printf("\n\t\tDATA DA CONSULTA: %d/%d/%d\n", agendamento.dc.dia, agendamento.dc.mes, agendamento.dc.ano);

        printf("\t\t-------------------------------------------------------------------------------------------------\n");
        printf ("\n\n");

        fwrite(&agendamento, sizeof(AGENDAMENTO), 1, arq);

        printf("\n\n\t\tCADASTRO REALIZADO COM SUCESSO!\n\n");

        fclose(arq);
        fclose(arqpaciente);

        printf("\t\tDESEJA REALIZAR UM NOVO CADASTRO(S/N)? ");
        scanf(" %c", &op);

    }while(op == 'S' || op == 's');

    printf ("\n\t\tPRESSIONE ENTER PARA CONTINUAR...\n");
    system("pause");
}

void cancela_agendamento(){

    AGENDAMENTO agendamento;
    int codigo, result;
    char c, op, s;

    do{

        cabecalho();

        printf("\t\t=================================================================================================\n");
        printf("\t\t___________________________________CANCELAMENTO DE AGENDAMENTO___________________________________\n\n");

        FILE *arq = fopen("agendamento.bin", "r+b"), *aux = fopen("new_agendamento.bin", "a+b");

        printf ("\n\t\tDIGITE C”DIGO DO AGENDAMENTO A SER CANCELADO: ");
        scanf ("%d", &codigo);

        result = encontrar_agendamento(codigo);

        if (result == 1){

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

                    system("del agendamento.bin");
                    system("ren new_agendamento.bin agendamento.bin");

                    printf ("\n\n\t\tAGENDAMENTO CANCELADO COM SUCESSO!\n");
                    system("pause");

                } else {

                    printf("\n\nAGENDAMENTO NAO FOI CANCELADO!\n");

                    fclose(arq);
                    fclose(aux);

                    printf("\n\n\t\tDESEJA CANCELAR OUTRO AGENDAMENTO(S/N)? ");
                    scanf(" %c", &op);

                }
        } else {

                printf("\n\t\tAGENDAMENTO N√O CADASTRADO, IMPOSSÕVEL CANCELAR AGENDAMENTO!\n");

                printf("\n\t\tDESEJA DIGITAR OUTRO C”DIGO(S/N)? ");
                scanf(" %c", &s);

                if (s == 's' || s == 'S'){

                    fclose(arq);
                    fclose(aux);

                    system("del new_agendamento.bin");

                    op = 's';

                } else {

                    fclose(arq);
                    fclose(aux);

                    system("del new_agendamento.bin");
                    printf("\n\t\tN√O FOI POSSÕVEL CANCELAR NENHUM AGENDAMENTO!\n");
                    break;

                }
        }

    }while(op == 'S' || op == 's');


}

void lista_agendamento(){

    cabecalho();

    printf("\t\t=================================================================================================\n");
    printf("\t\t______________________________________LISTA DE AGENDAMENTO_______________________________________\n\n");

    int i = 1;
    AGENDAMENTO agendamento;
    FILE *arq = fopen("agendamento.bin", "r+b");

        while(fread(&agendamento, sizeof(AGENDAMENTO), 1, arq) == 1){

            printf("\t\t%d∫ AGENDAMENTO:\n", i);

            printf("\n\t\tC”DIGO DO AGENDAMENTO: %d\n", agendamento.codagendamento);
            printf("\n\t\tNOME DO PACIENTE: %s\n", agendamento.nomepaciente);
            printf("\n\t\tC”DIGO DO PACIENTE: %d\n", agendamento.codpaciente);
            printf("\n\t\t¡REA DE ATENDIMENTO: %s\n", agendamento.area);
            printf("\n\t\tDATA DA CONSULTA: %d/%d/%d\n", agendamento.dc.dia, agendamento.dc.mes, agendamento.dc.ano);

            printf("\t\t-------------------------------------------------------------------------------------------------\n");
            printf ("\n\n");

            i++;
        }


    fclose(arq);

    printf ("\n\t\tPRESSIONE ENTER PARA CONTINUAR...\n");
    system("pause");
}

void menu_agendamento(){

    int n;

    do{
        cabecalho();

        printf ("\t\t______________________________________MENU DO AGENDAMENTO________________________________________\n\n");
        printf ("\t\t=================================================================================================\n\n");

        printf ("\n\n\t\t\t\t\t\tSELECIONE A OP«√O DESEJADA:\n\n");

        printf ("\n\t\t\t\t\t1 - CRIAR NOVO AGENDAMENTO\t2 - CANCELAR AGENDAMENTO\n\n\n");
        printf ("\t\t\t\t\t3 - LISTAR AGENDAMENTO\t\t4 - SAIR\n\n");

        printf ("\t\tOPCAO: ");

        scanf ("%d", &n);

        if (n == 1){

            cria_agendamento();

        } else if (n == 2){

            cancela_agendamento();

        } else if (n == 3){

            lista_agendamento();

        } else if (n != 4){

            printf("\n\t\tOPCAO INVALIDA POR FAVOR DIGITE UMA OPCAO VALIDA!\n");
            system("pause");

        }

    } while(n != 4);
}

void remove_agendamento(int cod){

    AGENDAMENTO agendamento;

    FILE *arq = fopen("agendamento.bin", "r+b"), *aux = fopen("new_agendamento.bin", "a+b");

    rewind(arq);

    while(fread(&agendamento, sizeof(AGENDAMENTO), 1, arq) == 1){

            if (cod != agendamento.codagendamento){

                    fwrite(&agendamento, sizeof(AGENDAMENTO),1,aux);

            }

    }

    fclose(arq);
    fclose(aux);

    system("del agendamento.bin");
    system("ren new_agendamento.bin agendamento.bin");
}


int encontrar_atendimento(int cod){

    FILE *arq = fopen("atendimento.bin", "r+b");
    ATENDIMENTO atendimento;

    while(fread(&atendimento, sizeof(ATENDIMENTO), 1, arq)){

        if (cod == atendimento.codatendimento){

            fclose(arq);
            return 1;

        }
    }

    fclose(arq);
    return 0;
}

void cria_atendimento(){

    int result, codsup, codagendamento, codaluno, recebealuno, recebesup, codigo, cod, retorno;
    char op, s;
    ATENDIMENTO atendimento;
    AGENDAMENTO agendamento;
    ALUNOS aluno;
    SUPERVISORES supervisor;
    do{
        cabecalho();

        printf("\t\t=================================================================================================\n");
        printf("\t\t_________________________________________NOVO ATENDIMENTO________________________________________\n\n");

        FILE *arq = fopen("atendimento.bin", "a+b"), *arqagendamento = fopen("agendamento.bin", "r+b"), *arqaluno = fopen("aluno.bin", "r+b");
        srand( (unsigned)time(NULL));

        while(1){
            cod = 1000 + rand();
            retorno = encontrar_atendimento(cod);
            if ( retorno == 1){
                continue;
            } else {
                atendimento.codatendimento = cod;
                break;
            }

        }


        printf("\n\n\t\tDIGITE O C”DIGO DO AGENDAMENTO: ");
        scanf("%d", &codagendamento);

        result = encontrar_agendamento(codagendamento);

        if (result == 1){

            atendimento.codagendamento = codagendamento;

            codigo = codagendamento;

            while(fread(&agendamento, sizeof(AGENDAMENTO), 1, arqagendamento) == 1){

                if (codagendamento == agendamento.codagendamento){

                    atendimento.daten.dia = agendamento.dc.dia;
                    atendimento.daten.mes = agendamento.dc.mes;
                    atendimento.daten.ano = agendamento.dc.ano;
                    strcpy( atendimento.nomepaciente, agendamento.nomepaciente);
                    atendimento.codpaciente = agendamento.codpaciente;
                    strcpy(atendimento.area, agendamento.area);

                }
            }

            fclose(arqagendamento);

            while(1){

                printf("\n\t\tDIGITE O C”DIGO DO ALUNO: ");
                scanf("%d", &codaluno);

                recebealuno = encontrar_aluno(codaluno, 0);

                if (recebealuno == 1){

                    atendimento.codaluno = codaluno;

                    while(fread(&aluno, sizeof(ALUNOS), 1, arqaluno) == 1){

                        if (codaluno == aluno.matricula){
                            strcpy(atendimento.nomealuno, aluno.nome);
                        }

                    }
                    break;

                } else {

                        printf("\n\n\t\tALUNO N√O CADASTRADO!\n");
                        printf("\n\n\t\tPOR FAVOR DIGITE UM C”DIGO V¡LIDO!\n\n");

                }

            }

            fclose(arqaluno);

            while(1){

                printf("\n\n\t\tDIGITE O C”DIGO DO SUPERVISOR: ");
                scanf("%d", &codsup);

                recebesup = encontrar_supervisor(codsup, 0);

                FILE *arqsupervisor = fopen("supervisores.bin", "r+b");

                if (recebesup == 1){

                    atendimento.codsupervisor = codsup;

                    while(fread(&supervisor, sizeof(SUPERVISORES), 1, arqsupervisor) == 1){

                        if (codsup == supervisor.codprofessor){
                            strcpy(atendimento.nomesupervisor, supervisor.nome);
                        }

                    }
                    break;
                    fclose(arqsupervisor);

                } else {

                    printf("\n\n\t\tSUPERVISOR N√O CADASTRADO!");
                    printf("\n\n\t\tPOR FAVOR DIGITE UM C”DIGO V¡LIDO!\n\n");
                    fclose(arqsupervisor);

                }

            }



            printf("\n\n\t\tC”DIGO DO ATENDIMENTO: %d\n\n", atendimento.codatendimento);
            printf("\t\tC”DIGO DO AGENDAMENTO: %d\n\n", atendimento.codagendamento);
            printf("\t\tDATA DA ATENDIMENTO: %d/%d/%d\n\n", atendimento.daten.dia, atendimento.daten.mes, atendimento.daten.ano);
            printf("\t\tNOME DO ALUNO: %s\n\n", atendimento.nomealuno);
            printf("\t\tC”DIGO DO ALUNO: %d\n\n", atendimento.codaluno);
            printf("\t\tNOME DO PACIENTE: %s\n\n", atendimento.nomepaciente);
            printf("\t\tC”DIGO DO PACIENTE: %d\n\n", atendimento.codpaciente);
            printf("\t\tDATA DO ATENDIMENTO: %d/%d/%d\n\n", atendimento.daten.dia, atendimento.daten.mes, atendimento.daten.ano);
            printf("\t\t¡REA DE ATENDIMENTO: %s\n\n", atendimento.area);
            printf("\t\tNOME DO SUPERVISOR: %s\n", atendimento.nomesupervisor);

            printf("\t\t-------------------------------------------------------------------------------------------------\n");
            printf ("\n\n");

            fwrite(&atendimento, sizeof(ATENDIMENTO), 1, arq);

            remove_agendamento(codigo);

            printf("\n\n\t\tCADASTRO DE ATENDIMENTO REALIZADO COM SUCESSO!\n\n");

        } else {

            printf("\n\n\t\tAGENDAMENTO N√O CADASTRADO!\n\n");
        }

        fclose(arq);

        printf("\n\n\t\tDESEJA REALIZAR UM NOVO ATENDIMENTO(S/N)? ");
        scanf(" %c", &s);
    }while(s == 'S' || s == 's');

    printf ("\n\t\tPRESSIONE ENTER PARA CONTINUAR...\n");
    system("pause");
}

void cancela_atendimento(){

    AGENDAMENTO agendamento;
    ATENDIMENTO atendimento;
    int codigo, cont = 0, result, cod;
    char c, op, s;

    do {

        cabecalho();

        printf("\t\t=================================================================================================\n");
        printf("\t\t_____________________________CANCELAMENTO DE ATENDIMENTO_________________________________________\n\n");

        FILE *arq = fopen("atendimento.bin", "r+b"), *aux = fopen("new_atendimento.bin", "a+b");

        printf ("\n\t\tDIGITE C”DIGO DO ATENDIMENTO A SER CANCELADO: ");
        scanf ("%d", &codigo);

        result = encontrar_atendimento(codigo);

        if (result == 1){

            printf("\n\n\t\tTEM CERTEZA QUE DESEJA CANCELAR O ATENDIMENTO(S/N)? ");
            scanf (" %c", &c);

            if (c == 'S' || c == 's'){

                    rewind(arq);

                    while(fread(&atendimento, sizeof(ATENDIMENTO), 1, arq) == 1){

                        if (codigo != atendimento.codatendimento){

                            fwrite(&atendimento, sizeof(ATENDIMENTO),1,aux);

                            cod = atendimento.codagendamento;

                        }

                    }

                    fclose(arq);
                    fclose(aux);

                    system("del atendimento.bin");
                    system("ren new_atendimento.bin atendimento.bin");

                    remove_agendamento(cod);

                    printf ("\n\n\t\tATENDAMENTO CANCELADO COM SUCESSO!\n");
                    system("pause");

              } else {

                    printf("\n\n\t\tATENDAMENTO NAO FOI CANCELADO!\n");

                    fclose(arq);
                    fclose(aux);

                    system("del atendimento.bin");

                    printf("\n\n\t\tDESEJA CANCELAR OUTRO ATENDAMENTO(S/N)? ");
                    scanf(" %c", &op);
              }


        } else {

                printf("\n\t\tATENDAMENTO N√O CADASTRADO, IMPOSSÕVEL CANCELAR AGENDAMENTO!\n");

                printf("\n\t\tDESEJA DIGITAR OUTRO C”DIGO(S/N)? ");
                scanf(" %c", &s);

                if (s == 's' || s == 'S'){

                    fclose(arq);
                    fclose(aux);

                    system("del new_atendamento.bin");

                    op = 's';

                } else {

                    fclose(arq);
                    fclose(aux);

                    system("del new_atendamento.bin");
                    printf("\n\t\tN√O FOI POSSÕVEL CANCELAR NENHUM ATENDAMENTO!\n");
                    break;

                }

        }

    }while(op == 's' || op == 'S');

    printf ("\n\t\tPRESSIONE ENTER PARA CONTINUAR...\n");
    system("pause");
}

void lista_atendimento(){

    cabecalho();

    printf("\t\t=================================================================================================\n\n");
    printf("\t\t___________________________________LISTA DE ATENDIMENTO__________________________________________\n\n");

    int i = 1;
    ATENDIMENTO atendimento;
    FILE *arq = fopen("atendimento.bin", "r+b");

        while(fread(&atendimento, sizeof(ATENDIMENTO), 1, arq) == 1){

            printf("\t\t%d∫ ATENDIMENTO:\n", i);

            printf("\n\t\tC”DIGO DO ATENDIMENTO: %d\n\n", atendimento.codatendimento);
            printf("\t\tC”DIGO DO AGENDAMENTO: %d\n\n", atendimento.codagendamento);
            printf("\t\tDATA DA ATENDIMENTO: %d/%d/%d\n\n", atendimento.daten.dia, atendimento.daten.mes, atendimento.daten.ano);
            printf("\t\tNOME DO ALUNO: %s\n\n", atendimento.nomealuno);
            printf("\t\tC”DIGO DO ALUNO: %d\n\n", atendimento.codaluno);
            printf("\t\tNOME DO PACIENTE: %s\n\n", atendimento.nomepaciente);
            printf("\t\tC”DIGO DO PACIENTE: %d\n\n", atendimento.codpaciente);
            printf("\t\tDATA DO ATENDIMENTO: %d/%d/%d\n\n", atendimento.daten.dia, atendimento.daten.mes, atendimento.daten.ano);
            printf("\t\t¡REA DE ATENDIMENTO: %s\n\n", atendimento.area);
            printf("\t\tNOME DO SUPERVISOR: %s\n", atendimento.nomesupervisor);

            printf("\t\t-------------------------------------------------------------------------------------------------\n");
            printf ("\n\n");

            i++;
        }


    fclose(arq);

    printf ("\n\t\tPRESSIONE ENTER PARA CONTINUAR...\n");
    system("pause");
}

void listar_area(){

    cabecalho();

    printf("\t\t=================================================================================================\n\n");
    printf("\t\t_____________________________________LISTA DE ATENDIMENTO________________________________________\n\n");

    int i = 1, n, cont=0;
    ATENDIMENTO atendimento;
    FILE *arq = fopen("atendimento.bin", "r+b");

    do{
        printf("\t\tSELECIONE A ¡REA DE ATENDIMENTO QUE DESEJA LISTAR: \n\n");
        printf("\t\t1 - FISIOTERAPIA\n\t\t2 - ODONTOLOGIA\n\t\t3 - PSICOLOGIA\n\n");

        printf("\t\tOP«√O: ");
        scanf("%d", &n);

        if (n<1 || n>3){
            printf("\n\t\tOP«√O INVALIDA!\n\n");
        }

    }while(n<1 || n>3);





    while(fread(&atendimento, sizeof(ATENDIMENTO), 1, arq) == 1){

        if (n == 1 && strcmp(atendimento.area,"FISIOTERAPIA")==0){

            printf("\n\t\tC”DIGO DO ATENDIMENTO: %d\n", atendimento.codatendimento);
            printf("\n\t\tC”DIGO DO AGENDAMENTO: %d\n", atendimento.codagendamento);
            printf("\n\t\tDATA DA ATENDIMENTO: %d/%d/%d\n", atendimento.daten.dia, atendimento.daten.mes, atendimento.daten.ano);
            printf("\n\t\tNOME DO ALUNO: %s\n", atendimento.nomealuno);
            printf("\n\t\tC”DIGO DO ALUNO: %d\n", atendimento.codaluno);
            printf("\n\t\tNOME DO PACIENTE: %s\n", atendimento.nomepaciente);
            printf("\n\t\tC”DIGO DO PACIENTE: %d\n", atendimento.codpaciente);
            printf("\n\t\tDATA DO ATENDIMENTO: %d/%d/%d\n", atendimento.daten.dia, atendimento.daten.mes, atendimento.daten.ano);
            printf("\n\t\t¡REA DE ATENDIMENTO: %s\n", atendimento.area);
            printf("\n\t\tNOME DO SUPERVISOR: %s\n", atendimento.nomesupervisor);

            printf("\t\t-------------------------------------------------------------------------------------------------\n");
            printf ("\n\n");
            cont++;

        } else if (n == 2 && strcmp(atendimento.area, "ODONTOLOGIA")==0){

            printf("\n\t\tC”DIGO DO ATENDIMENTO: %d\n", atendimento.codatendimento);
            printf("\n\t\tC”DIGO DO AGENDAMENTO: %d\n", atendimento.codagendamento);
            printf("\n\t\tDATA DA ATENDIMENTO: %d/%d/%d\n", atendimento.daten.dia, atendimento.daten.mes, atendimento.daten.ano);
            printf("\n\t\tNOME DO ALUNO: %s\n", atendimento.nomealuno);
            printf("\n\t\tC”DIGO DO ALUNO: %d\n", atendimento.codaluno);
            printf("\n\t\tNOME DO PACIENTE: %s\n", atendimento.nomepaciente);
            printf("\n\t\tC”DIGO DO PACIENTE: %d\n", atendimento.codpaciente);
            printf("\n\t\tDATA DO ATENDIMENTO: %d/%d/%d\n", atendimento.daten.dia, atendimento.daten.mes, atendimento.daten.ano);
            printf("\n\t\t¡REA DE ATENDIMENTO: %s\n", atendimento.area);
            printf("\n\t\tNOME DO SUPERVISOR: %s\n", atendimento.nomesupervisor);

            printf("\t\t-------------------------------------------------------------------------------------------------\n");
            printf ("\n\n");
            cont++;

        } else if (n == 3 && strcmp(atendimento.area, "PSICOLOGIA")==0){

            printf("\n\t\tC”DIGO DO ATENDIMENTO: %d\n", atendimento.codatendimento);
            printf("\n\t\tC”DIGO DO AGENDAMENTO: %d\n", atendimento.codagendamento);
            printf("\n\t\tDATA DA ATENDIMENTO: %d/%d/%d\n", atendimento.daten.dia, atendimento.daten.mes, atendimento.daten.ano);
            printf("\n\t\tNOME DO ALUNO: %s\n", atendimento.nomealuno);
            printf("\n\t\tC”DIGO DO ALUNO: %d\n", atendimento.codaluno);
            printf("\n\t\tNOME DO PACIENTE: %s\n", atendimento.nomepaciente);
            printf("\n\t\tC”DIGO DO PACIENTE: %d\n", atendimento.codpaciente);
            printf("\n\t\tDATA DO ATENDIMENTO: %d/%d/%d\n", atendimento.daten.dia, atendimento.daten.mes, atendimento.daten.ano);
            printf("\n\t\t¡REA DE ATENDIMENTO: %s\n", atendimento.area);
            printf("\n\t\tNOME DO SUPERVISOR: %s\n", atendimento.nomesupervisor);

            printf("\t\t-------------------------------------------------------------------------------------------------\n");
            printf ("\n\n");

            cont++;

        }

    }

    if (cont == 0){
        printf("\n\t\tN√O EXISTE ATENDIMENTOS EM NOSSOS REGISTROS.\n");
    }

    fclose(arq);

    printf ("\n\t\tPRESSIONE ENTER PARA CONTINUAR...\n");
    system("pause");

}

void listar_aluno_especifico(){

    cabecalho();

    printf("\t\t=================================================================================================\n\n");
    printf("\t\t_____________________________________LISTA DE ATENDIMENTO________________________________________\n\n");

    int i = 1, mat, cont=0, recebealuno;
    ATENDIMENTO atendimento;
    FILE *arq = fopen("atendimento.bin", "r+b");

    while(1){

            printf("\n\t\tDIGITE A MATRICULA DO ALUNO QUE VOC  DESEJA LISTAR: ");
            scanf("%d", &mat);

            recebealuno = encontrar_aluno(mat, 0);

            if (recebealuno == 1){

                break;

            } else {

                    printf("\n\n\t\tALUNO N√O CADASTRADO!\n");
                    printf("\n\n\t\tPOR FAVOR DIGITE UM C”DIGO V¡LIDO!\n\n");

            }

    }



    while(fread(&atendimento, sizeof(ATENDIMENTO), 1, arq) == 1){

        if (mat == atendimento.codaluno){

            printf("\n\n\t\tC”DIGO DO ATENDIMENTO: %d\n\n", atendimento.codatendimento);
            printf("\n\t\tC”DIGO DO AGENDAMENTO: %d\n\n", atendimento.codagendamento);
            printf("\n\t\tDATA DA ATENDIMENTO: %d/%d/%d\n\n", atendimento.daten.dia, atendimento.daten.mes, atendimento.daten.ano);
            printf("\n\t\tNOME DO ALUNO: %s\n\n", atendimento.nomealuno);
            printf("\n\t\tMATRÕCULA DO ALUNO: %d\n\n", atendimento.codaluno);
            printf("\n\t\tNOME DO PACIENTE: %s\n\n", atendimento.nomepaciente);
            printf("\n\t\tC”DIGO DO PACIENTE: %d\n\n", atendimento.codpaciente);
            printf("\n\t\tDATA DO ATENDIMENTO: %d/%d/%d\n\n", atendimento.daten.dia, atendimento.daten.mes, atendimento.daten.ano);
            printf("\n\t\t¡REA DE ATENDIMENTO: %s\n\n", atendimento.area);
            printf("\n\t\tNOME DO SUPERVISOR: %s\n\n", atendimento.nomesupervisor);

            printf("\t\t-------------------------------------------------------------------------------------------------\n");
            printf ("\n\n");

            i++;

            cont++;
        }

    }

    if (cont == 0){
        printf("\n\t\tN√O EXISTE ATENDIMENTOS COM DADOS DESSE ALUNO EM NOSSOS REGISTROS.\n");
    }

    fclose(arq);

    printf ("\n\t\tPRESSIONE ENTER PARA CONTINUAR...\n");
    system("pause");

}

void listar_paciente_especifico(){

    cabecalho();

    printf("\t\t=================================================================================================\n\n");
    printf("\t\t_______________________________________LISTA DE ATENDIMENTO______________________________________\n\n");

    int i = 1, cod, result, cont=0;
    ATENDIMENTO atendimento;
    FILE *arq = fopen("atendimento.bin", "r+b");

     while(1){

            printf("\n\t\tDIGITE O C”DIGO DO PACIENTE QUE VOC  DESEJA LISTAR: ");
            scanf("%d", &cod);

            result = encontrar_paciente(cod, 0);

            if (result == 1){

                break;

            } else {

                    printf("\n\n\t\tPACIENTE N√O CADASTRADO!\n");
                    printf("\n\n\t\tPOR FAVOR DIGITE UM C”DIGO V¡LIDO!\n\n");

            }

    }



    while(fread(&atendimento, sizeof(ATENDIMENTO), 1, arq) == 1){

        if (cod == atendimento.codpaciente){

            printf("\n\n\t\tC”DIGO DO ATENDIMENTO: %d\n", atendimento.codatendimento);
            printf("\n\t\tC”DIGO DO AGENDAMENTO: %d\n", atendimento.codagendamento);
            printf("\n\t\tDATA DA ATENDIMENTO: %d/%d/%d\n", atendimento.daten.dia, atendimento.daten.mes, atendimento.daten.ano);
            printf("\n\t\tNOME DO ALUNO: %s\n", atendimento.nomealuno);
            printf("\n\t\tC”DIGO DO ALUNO: %d\n", atendimento.codaluno);
            printf("\n\t\tNOME DO PACIENTE: %s\n", atendimento.nomepaciente);
            printf("\n\t\tC”DIGO DO PACIENTE: %d\n", atendimento.codpaciente);
            printf("\n\t\tDATA DO ATENDIMENTO: %d/%d/%d\n", atendimento.daten.dia, atendimento.daten.mes, atendimento.daten.ano);
            printf("\n\t\t¡REA DE ATENDIMENTO: %s\n", atendimento.area);
            printf("\n\t\tNOME DO SUPERVISOR: %s\n", atendimento.nomesupervisor);

            printf("\t\t-------------------------------------------------------------------------------------------------\n");
            printf ("\n\n");

            i++;

            cont++;
        }

    }

    if (cont == 0){
        printf("\n\t\tN√O EXISTE ATENDIMENTOS COM DADOS DESSE PACIENTE EM NOSSOS REGISTROS.\n");
    }


    fclose(arq);

    printf ("\n\t\tPRESSIONE ENTER PARA CONTINUAR...\n");
    system("pause");
}

void menu_listar_atendimento(){
    int n;

    do{

        cabecalho();

        printf ("\t\t_____________________________________MENU DO LISTAR ATENDIMENTO__________________________________\n\n");

        printf ("\t\t=================================================================================================\n\n");

        printf ("\n\n\t\t\t\t\t\tSELECIONE A OP«√O DESEJADA:\n\n");

        printf ("\n\t\t\t\t1 - LISTAR TODOS OS ATENDIMENTOS\t2 - LISTAR POR ¡REAS ESPECÕFICAS\n\n");
        printf ("\n\t\t\t\t3 - LISTAR POR ALUNO ESPECÕFICO\t\t4 - LISTAR POR PACIENTE ESPECÕFICO\n\n");
        printf ("\n\t\t\t\t\t\t\t\t5 - SAIR\n\n");

        printf ("\n\n\t\tOPCAO: ");

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

        printf ("\t\t_______________________________________MENU DO ATENDIMENTO_______________________________________\n\n");

        printf ("\t\t=================================================================================================\n\n");

        printf ("\n\n\t\t\t\t\t\tSELECIONE A OP«√O DESEJADA:\n\n");

        printf ("\n\t\t\t\t\t1 - CRIAR NOVO ATENDIMENTO\t2 - CANCELAR ATENDIMENTO\n\n");
        printf ("\n\t\t\t\t\t3 - LISTAR ATENDIMENTO\t\t4 - SAIR\n\n");

        printf ("\t\tOPCAO: ");

        scanf ("%d", &n);

        if (n == 1){

            cria_atendimento();

        } else if (n == 2){

            cancela_atendimento();

        } else if (n == 3){

            menu_listar_atendimento();

        } else if (n != 4){

            printf("\n\n\t\tOPCAO INVALIDA POR FAVOR DIGITE UMA OPCAO VALIDA!\n");
            system("pause");

        }

    } while(n != 4);
}

void menu_principal(){

    int n;

    do{

        cabecalho();

        printf ("\t\t________________________________________MENU DO PRINCIPAL________________________________________\n\n");

        printf ("\t\t=================================================================================================\n\n");

        printf("\t\t\t\t\t\tSEJA BEM VINDO ¿ CLÕNICA DA UEPB!\n\n");
        printf ("\n\n\t\t\t\t\t\t    SELECIONE A OP«√O DESEJADA:\n\n");

        printf ("\n\n\t\t\t\t\t1 - MENU ALUNO\t\t\t2 - MENU PACIENTE\n\n");
        printf ("\t\t\t\t\t3 - MENU SUPERVISOR\t\t4 - MENU AGENDAMENTO\n\n");
        printf ("\t\t\t\t\t5 - MENU ATENDIMENTO\t\t6 - ENCERRAR PROGRAMA\n\n");

        printf ("\t\tOPCAO: ");

        scanf ("%d", &n);

        if (n == 1){

            menu_aluno();

        } else if (n == 2){

            menu_paciente();

        } else if (n == 3){

            menu_supervisor();

        } else if (n == 4){

            menu_agendamento();

        } else if (n == 5){

            menu_atendimento();
        } else  if (n != 6){

            printf("\n\n\t\tOPCAO INVALIDA POR FAVOR DIGITE UMA OPCAO VALIDA!\n");
            system("pause");

        }

    } while(n != 6);
}

int main (){

    setlocale(LC_ALL, "portuguese");

    system("color BC");

    inicializando();

    menu_principal();

    finalizando();

    return 0;
}
