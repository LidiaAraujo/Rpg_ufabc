//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Seção de variáveis
#define MAX_TAMANHO_DA_PALAVRA 100
#define NUMERO_ITENS 5
#define OPCOES_DIA 3
#define OPCOES_MENU 4
#define MAX_TAMANHO_NOME 150
#define VALOR_PROVA 10

int sair = 0;
int final = 0;

void criarlinha(int n);
void inserindoInfoDoProtagonista(char tipo, int info);
void itemprova();

//Lista dinâmica
struct listadinamica
{
	char palavra [MAX_TAMANHO_DA_PALAVRA];
	struct listadinamica *p;
	
};

typedef struct listadinamica Item;
typedef struct listadinamica* listadef;

listadef *crialistadinamica (){
	listadef *plista;
	plista = (listadef*) malloc (sizeof(listadef));
	
	if (plista != NULL)
	{
		*plista = NULL;
	}
	
	return plista;
}

void escrevelistadinamicaf(listadef *ponteiro, char n[MAX_TAMANHO_DA_PALAVRA]) {
	Item *no;
	no = (Item*) malloc (sizeof(Item));
	strcpy(no->palavra, n);
	no->p = (*ponteiro);
	*ponteiro = no;

}

int qtd_itens(listadef *p){
	int cont = 0;
	Item *no = *p;

	while (no != NULL)
	{
		cont++;
		no=no->p;
	}
	
	return cont;
}

void ler_lista(listadef *p){
	Item *no = *p;

	for (int i = 0; i< qtd_itens(p); i++){
		criarlinha(40);
		printf("(%d) %s\n", i, no->palavra);
		no=no->p;
	}
	criarlinha(40);
}

int remover_elemento(listadef *p, char n [MAX_TAMANHO_DA_PALAVRA]){
	
	if ((p == NULL) || ((*p)  == NULL)) {
		return 0;
	} else {
		Item *no_atual, *no_ant;
		no_atual = *p;

		while(no_atual != NULL && no_atual->palavra != n){
			if (strcmp(no_atual->palavra, n) == 0) {
				break;
			}
			no_ant = no_atual;
			no_atual = no_atual->p;
		}

		if (no_atual == 0) {
			return 2; //Se retornar 2 não achou o elemento
		} else {
			if (no_atual == *p) {
				*p = no_atual->p;
			} else {
				no_ant->p = no_atual->p;
			}

		}
		free(no_atual);
		return 1;
	}


}


struct protag
{
    char nome[MAX_TAMANHO_DA_PALAVRA];
    int energia;
    int estudo;
    int social;
    int dinheiro;
    int saude;
    int dia_atual;
    int nota;
    listadef *listaitem;
};

struct protag protagonista;

//Seção menus
void criarlinha(int n) {
    for (int i = 0; i < n; i++) {
        printf("-");
    }
    printf("\n");
}

void imprimeListaDePalavras(char arr[][MAX_TAMANHO_DA_PALAVRA], int tam){
    
    criarlinha(34);

    for(int i =0; i < tam; i++  ){
        printf("|(%d) %s \n",i, arr[i]);
        criarlinha(34);
    }

}


//Criar personagem
void Protagonista(){
    fflush(stdin);

    printf("Qual o nome do aluno?\n");
        fgets(protagonista.nome, MAX_TAMANHO_DA_PALAVRA, stdin);
    
    protagonista.energia = 10;
    protagonista.dinheiro = 10;
    protagonista.estudo = 0;
    protagonista.saude = 10;
    protagonista.social = 0;
    protagonista.nota = 0;
    protagonista.listaitem = crialistadinamica();
}

//Lê os créditos
void LerCreditos(){

    printf("\n\n        CREDITOS           \nProjeto RPGemC\nDesenvolvedores:\n Gabriel Gomes De Oliveira Costa (RA: 11201921471)\n Isabela Leopoldino Conti (RA:11201811574)\n Lidia Victoria Alves de Araujo (RA:11201920456)\n Nathalia Caroline de Oliveira Pinto(RA:21088416)\nDisciplina Programacao Estruturada || Professor:  Wagner Tanaka Botelho\n\n\n");

}

//Introdução
void LerInicio(){

    printf("Texto do inicio\n");

}

//Compra de itens nos dias comuns
void ItemDias(){
    int aux;
    fflush(stdin);

    printf("Compre itens para usar na hora da prova! Voce tem %d de dinheiro sobrando\n", protagonista.dinheiro);

    char itens[NUMERO_ITENS][MAX_TAMANHO_DA_PALAVRA] = {"Cafe (+2 de energia) - 2 reais", "Barrinha de cereal (+5 de energia) - 5 reais", "Livro didatico (+3 de estudo) - 10 reais", "Folha de resposta (+10 de ... estudo?) - 20 reais", "To so dando uma olhadinha (voltar ao menu)"};
    imprimeListaDePalavras(itens, NUMERO_ITENS);

    scanf("%d", &aux);

    switch (aux)
    {
    case 0:
        //café
        if (protagonista.dinheiro >= 2) {
            printf("Voce comprou um cafe!\n");
            protagonista.dinheiro -= 2;
            escrevelistadinamicaf(protagonista.listaitem, "Cafe (+2 de energia)");
        } else {
            printf("Sem dinheiro o suficiente! (Saldo restante: %d reais)\n", protagonista.dinheiro);
        }
        break;
    case 1:
        //Barrinha
        if (protagonista.dinheiro >= 5) {
            printf("Voce comprou uma barrinha de cereal!\n");
            protagonista.dinheiro -= 5;    
            escrevelistadinamicaf(protagonista.listaitem, "Barrinha de cereal (+5 de energia)");
        } else {
            printf("Sem dinheiro o suficiente! (Saldo restante: %d reais)\n", protagonista.dinheiro);
        }
        break;
    case 2:
        //livro
        if (protagonista.dinheiro >= 10) {
            printf("Voce comprou um livro didatico!\n");
            protagonista.dinheiro -= 10;
            escrevelistadinamicaf(protagonista.listaitem, "Livro didatico (+3 de estudo)");
        } else {
            printf("Sem dinheiro o suficiente! (Saldo restante: %d reais)\n", protagonista.dinheiro);
        }
        break;
    case 3:
        //Respostas
        if (protagonista.dinheiro >= 20) {
            printf("Voca comprou uma folha de respostas!\n");
            protagonista.dinheiro -=20;
            escrevelistadinamicaf(protagonista.listaitem, "Folha de resposta (+10 de ... estudo?)");
        } else {
            printf("Sem dinheiro o suficiente! (Saldo restante: %d reais)\n", protagonista.dinheiro);
        }
        break;
    case 4:
        break;
    default:
        printf("Houve um erro, por favor digite novamente\n");
        ItemDias();
        break;
    }

}

//Sistema de Salvar (0 )
void Carregar(){
   
    char aux_str[MAX_TAMANHO_DA_PALAVRA];

    FILE *fpInfo;
    int num = 0;
   
    fpInfo = fopen("Save.txt" , "r");
   
    char att[6] = {'e', '&','s','z','d','a'};
    char attInfo[6][MAX_TAMANHO_DA_PALAVRA] = {"Energia", "Estudo", "Social", "Saude", "Dinheiro","Dia Atual"};

    printf("Carregando as informacoes...... \n");
    criarlinha(34);

    if(fpInfo == NULL){
        printf("Erro na abertura do arquivo -> não foi possível recuperar as informações salvas\n");
        return;
    } 


    printf("Informaçoes salvas :");



    while(!feof(fpInfo)){
        if(num == 0){
            fgets(aux_str,MAX_TAMANHO_DA_PALAVRA, fpInfo);
            strcpy(protagonista.nome , aux_str);
            printf("Bem vindo de volta %s\n", protagonista.nome);

        } else if (num > 0 && num < 7){
            int info = atoi(fgets(aux_str,MAX_TAMANHO_DA_PALAVRA, fpInfo));
            printf("%s : %d\n",attInfo[num - 1], info);
            inserindoInfoDoProtagonista(att[num - 1], info);
        } else {
            break;
        }
        num ++;
   }

    fclose(fpInfo);


}

int obtendoInfoDoProtagonista(char tipo){
    switch(tipo){
        case 'e' :
            return protagonista.energia;
        case '&' : 
            return protagonista.estudo;
        case 's' :
            return protagonista.social;
        case 'z' :
            return protagonista.saude;
        case 'd' :
            return protagonista.dinheiro;
        default :
            return protagonista.dia_atual;
    }
}

void inserindoInfoDoProtagonista(char tipo, int info){
    switch(tipo) {
        case 'e' :
            protagonista.energia = info;
        case '&' :
            protagonista.estudo = info;
        case 's' :
            protagonista.social = info;
        case 'z' :
            protagonista.saude = info;
        case 'd' :
            protagonista.dinheiro = info;
        default :
            protagonista.dia_atual = info;
    }

}


void Salvar(){
    char aux_str[MAX_TAMANHO_DA_PALAVRA];
    FILE *fpInfo;

    char c;
    
    fpInfo = fopen("Save.txt" , "w");


    char att[6] = {'e', '&','s','z','d','a'};

    if( fpInfo == NULL){
        printf("Erro na abertura do arquivo - Não foi possível salvar as informações\n");
        return;
    } 

    fprintf(fpInfo, protagonista.nome);

    for(int i =0; i < 6; i++){
        fprintf(fpInfo, strcat(itoa(obtendoInfoDoProtagonista(att[i]), aux_str, 10), "\n"));
    }
    fclose(fpInfo);
}

//Ações nos dias comuns
void AcoesDias(){

}


//Sistema de provas
void Prova(int dia){
    int vida_prova, aux, continua = 0, maxprova, r;
    char prova[3][MAX_TAMANHO_DA_PALAVRA] = {"Tentar responder as questoes (-1 energia)", "Usar um item", "Desisto!"};

    if(dia <= 4) {
            printf("Hora da prova 1!\n");
            maxprova = VALOR_PROVA;
    } else {
            printf("Hora da prova final!\n");
            maxprova = VALOR_PROVA*2;
    }
    
    vida_prova = maxprova;

    while (continua == 0){

        if (protagonista.energia <= 0)
        {
            break;
        }
        

        printf("Ainda faltam %d de %d questoes\nVoce tem %d de energia sobrando\n", vida_prova, maxprova, protagonista.energia);

        imprimeListaDePalavras(prova, 3);
        scanf("%d", &aux);

        switch (aux)
        {
        case 0:
            r = (rand() % 4) + 0.5*protagonista.estudo;
            vida_prova = vida_prova - r;
            printf("Voce conseguiu fazer %d questoes\n", r);
            break;
        
        case 1:
            itemprova();
            break;
        case 2:
            printf("Voce desistiu de fazer a prova. Acontece\n");
            protagonista.energia = -1;
            continua = 1;
        default:

            break;
        }

        if (vida_prova <= 0) {
            continua = 1;
        } else {
            protagonista.energia--;
        }
    }

    if (protagonista.energia >= 0) {
        printf("Voce terminou a prova!\n");
        protagonista.nota++;
    } else {
        printf("Voce nao conseguiu terminar a prova\n");
    }
}

void itemprova(){
    int aux;

    if (qtd_itens(protagonista.listaitem) < 0) {
        printf("Voce nao tem nenhum item!\n");
    } else {
        ler_lista(protagonista.listaitem);

        printf("Que item voce quer utilizar?\n");
        fflush(stdin);
        scanf("%d", &aux);
    
        
    }
}

void Final(){
    //Se nota = 0 -> reprosvou as duas / nota = 1 -> passou em uma / se nota = 2 -> Passou nas duas
}

//Exibe a tela de início
int tela(){
    fflush(stdin);
    int esc = 0;

    char menu[OPCOES_MENU][MAX_TAMANHO_DA_PALAVRA] = {"Novo jogo", "Carregar jogo", "Creditos", "Sair"};
    imprimeListaDePalavras(menu, OPCOES_MENU);

    scanf(" %d", &esc);

    if (esc == 0) {
        Protagonista();
    } else if (esc == 1) {
        Carregar();
    } else if (esc == 2) {
        LerCreditos();
        tela();
    } else if (esc == 3){
        sair = 1;
    } else {
        printf("Houve um erro, por favor digite novamente\n");
        tela();
    }

    return esc;
}

void dias(){
    int esc;
    fflush(stdin);

    char diaacoes[OPCOES_DIA][MAX_TAMANHO_DA_PALAVRA] = {"Fazer alguma coisa!", "Ir no mercadinho", "Ir dormir (encerrar o dia)"};
    
    printf("Mais um dia comeca! O que %s vai fazer hoje?\n", protagonista.nome);
    while (1 == 1) {    

        printf("%s tem %d/10 de energia restando\n", protagonista.nome, protagonista.energia);
        imprimeListaDePalavras(diaacoes, OPCOES_DIA);
        scanf(" %d", &esc);

        if (esc == 0) {
            AcoesDias();
        } else if (esc == 1) {
            ItemDias();
        } else if (esc == 2) {
            break;
        } else {
            printf("Houve algum erro, por favor digite novamente");
        }
    }

}


int determinarDia(int carregado){
    if(carregado == 1) {
        return protagonista.dia_atual;
    } 
    else{
        return 1;
    }

}

void passagemDasSemanas(int dia, char s){
    for (dia <= 7; dia++;){
            if (sair==1) {
                break;
            }
            printf("Voce esta no dia %d/7\n", dia);
            if (dia == 3 || dia == 7) {
                Prova(dia);
            } else {
                dias();                
            }

            protagonista.energia = 10;
            protagonista.saude -= 2;

            fflush(stdin);
            printf("Pronto para o proximo dia? (s ou n)\n");
            scanf(" %c", &s);
            if (s == 'n') {
                sair = 1;
            }

            fflush(stdin);
            printf("Deseja salvar o jogo? (s ou n)\n");
            scanf(" %c", &s);


            if (s == 's') {
                protagonista.dia_atual = dia;
                Salvar();
            }

            if (dia >= 7){
                final = 1;
                break;
            }
    }
}

// getters e setters do "Java"
// void inserindoInfoDoProtagonista(char info[]){


// }


void main(){
    char s;
    LerInicio();

    while(sair == 0 || final == 0) {
        int carregado = tela();
        int dia = determinarDia(carregado);
        passagemDasSemanas(dia, s);
    }

    if (final == 1) {
        Final();
        printf("Obrigado por jogar!");
        LerCreditos();
    }

    printf("BYE BYE");

}