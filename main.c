#include <stdlib.h>
#include <stdio.h>
#define true 1
#define false 0
#define IDADEPREFERENCIAL 60

typedef int bool;

typedef struct aux {
  int id;
  int idade;
  struct aux* prox;
} ELEMENTO, * PONT;

typedef struct {
  PONT inicio;
  PONT fimPref;
  PONT inicioNaoPref;
  PONT fim;
} FILAPREFERENCIAL, * PFILA;

PFILA criarFila(){
	PFILA res = (PFILA) malloc(sizeof(FILAPREFERENCIAL));
	res->inicio = NULL; 
	res->fimPref = NULL;
	res->inicioNaoPref = NULL;
	res->fim = NULL;
	return res;
}

int tamanho(PFILA f){
	PONT atual = f->inicio;
	int tam = 0;
	while (atual) {
		atual = atual->prox;
		tam++;
	}
	return tam;
}

PONT buscarID(PFILA f, int id){
	PONT atual = f->inicio;
	 while (atual) {
		if (atual->id == id) return atual;
		atual = atual->prox;
	}
	return NULL;
}

void exibirLog(PFILA f){
	int numElementos = tamanho(f);
	printf("\nLog fila [elementos: %i] - Inicio:", numElementos);
	PONT atual = f->inicio;
	while (atual){
		printf(" [%i;%i]", atual->id, atual->idade);
		atual = atual->prox;
	}
	printf("\n\n");
}


int consultarIdade(PFILA f, int id){
	PONT atual = f->inicio;
	 while (atual) {
		if (atual->id == id) return atual->idade;
		atual = atual->prox;
	}
	return -1;
}



bool inserirPessoaNaFila(PFILA f, int id, int idade){
  
  //checagem para retornos de erro
  if ((id<0)||(idade<0)||(buscarID(f, id))) return false;
  
  //criação do novo elemento da fila
  PONT novo = (PONT) malloc(sizeof(ELEMENTO));
  novo->id = id;
  novo->idade = idade;
  novo->prox = NULL;


  ///////////////////////inserção na fila

  ///idade maior ou igual que a preferencial
  if (novo->idade>=IDADEPREFERENCIAL){
    

    //caso fila esteja vazia ou não haja ninguém com idade preferencial
    if((f->inicio == NULL)||(f->inicio == f->inicioNaoPref)){
      
      f->inicio = novo;
      f->fimPref = novo;

      //caso a fila não preferencial possua membros
      if(f->inicioNaoPref!=NULL){
        f->fimPref->prox = f->inicioNaoPref;
        
        return true;
      }

      //caso a fila não preferencial esteja vazia
      else{
        f->fim = novo;
        
        return true;
      }

    }

    //caso a fila preferencial possua membros
    else{
      f->fimPref->prox = novo;
      f->fimPref = novo;
      

      //caso a fila não preferencial possua membros
      if(f->inicioNaoPref!=NULL){
        f->fimPref->prox = f->inicioNaoPref;
        
        return true;
      }

      //caso a fila não preferencial esteja vazia
      else{
        f->fim = novo;
        
        return true;
      }
    }

  ///idade menor que a idade preferencial
  }else{
    

    //caso a fila preferencial esteja vazia
    if (f->fimPref == NULL){
      

      //caso a fila não preferencial esteja vazia
      if(f->inicioNaoPref == NULL){
        
        f->inicio = novo;
        f->inicioNaoPref = novo;
        f->fim = novo;
        return true;
      }

      //caso a fila não preferencial possua membros
      else{
        
        f->fim->prox = novo;
        f->fim = novo;
        return true;
      }
    }

    //caso a fila preferencial possua membros
    else{
      

      //caso a fila não preferencial esteja vazia
      if(f->inicioNaoPref == NULL){
        
        f->inicioNaoPref = novo;
        f->fimPref->prox = novo;
        f->fim = novo;
        return true;
      }

      //caso a fila não preferencial possua membros
      else{
        
        f->fim->prox = novo;
        f->fim = novo;
        return true;
      }
    }
  }
	return false;
}


bool atenderPrimeiraDaFila(PFILA f, int* id){

  //checagem para retorno de erro
  if (f->inicio == NULL) return false;

  //atribuição requisitada no enunciado do ep
  *id = f->inicio->id;

  PONT apagar = f->inicio;

  //caso o atendido seja o último da fila preferencial
  if(f->inicio == f->fimPref){

    //caso a fila não preferencial possua membros
    if(f->inicioNaoPref != NULL){
      f->fimPref = NULL;
      f->inicio = f->inicio->prox;
      free(apagar);
      return true;
    }

    //caso a fila não preferencial esteja vazia
    else{
      f->inicio = NULL;
      f->fimPref = NULL;
      f->inicioNaoPref = NULL;
      f->fim = NULL;
      free(apagar);
      return true;
    }
  }

  //caso o atendido seja o último da fila
  if(f->inicio == f->fim){
    f->inicio = NULL;
    f->fimPref = NULL;
    f->inicioNaoPref = NULL;
    f->fim = NULL;
    free(apagar);
    return true;
  }

  //caso o atendido não seja o último da fila preferencial nem da não-preferencial
  else{
    f->inicio = f->inicio->prox;
    free(apagar);
    return true;
  }

	return false;
}


bool desistirDaFila(PFILA f, int id){

  //buscando id fornecido
  if(!(buscarID(f, id))) return false;

  PONT ant = f->inicio;
  PONT atual = f->inicio;
  PONT desiste = f->inicio;

	while (atual->id!=id){
    ant = atual;
		atual = atual->prox;
  }
  desiste = atual;

  

  
  

  //caso o desistente seja o último da fila preferencial
  if(desiste == f->fimPref){

    //caso a fila não preferencial possua membros
    if(f->inicioNaoPref != NULL){
      f->fimPref = NULL;
      f->inicio = f->inicioNaoPref;
      free(desiste);
      return true;
    }

    //caso a fila não preferencial esteja vazia
    else{
      f->inicio = NULL;
      f->fimPref = NULL;
      f->inicioNaoPref = NULL;
      f->fim = NULL;
      free(desiste);
      return true;
    }
  }

  //caso o desistente seja o primeiro da fila preferencial
  if((desiste == f->inicio)&&(desiste != f->inicioNaoPref)){
    f->inicio = f->inicio->prox;
    free(desiste);
    return true;
  }

  //caso o desistente seja o primeiro da fila nao preferencial
  if(desiste == f->inicioNaoPref){
    
    //caso a fila nao preferencial ainda possua membros
    if(f->inicioNaoPref->prox != NULL){

      f->inicioNaoPref = f->inicioNaoPref->prox;

      //caso a fila preferencial possua membros
      if (f->fimPref != NULL){
        ant->prox = f->inicioNaoPref;
        free(desiste);
        return true;
      }

      //caso a fila preferencial esteja vazia
      else{
        f->inicio = f->inicioNaoPref;
        free(desiste);
        return true;
      }
    }
  }

  //caso o desistente seja o último da fila
  if(desiste == f->fim){
    f->fim = ant;
    f->inicio = NULL;
    f->fimPref = NULL;
    f->inicioNaoPref = NULL;
    f->fim = NULL;
    free(desiste);
    return true;
  }

  //qualquer outro caso
  else{
    ant->prox = desiste->prox;
    free(desiste);
    return true;
  }

  

	return false;
}



int main() {
	PFILA f = criarFila();
	int id;
	int idade;
	bool res;

	printf("################# INSERINDO #######################\n");

	exibirLog(f);
	res = inserirPessoaNaFila(f, -1, -2);
	if(res) printf("Insercao retornou true (0).\n");
	else printf("Insercao retornou false (0). [OK]\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 1, 21);
	if(res) printf("Insercao retornou true (1). [OK]\n");
	else printf("Insercao retornou false (1).\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 2, 11);
	if(res) printf("Insercao retornou true (2). [OK]\n");
	else printf("Insercao retornou false (2).\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 3, 31);
	if(res) printf("Insercao retornou true (3). [OK]\n");
	else printf("Insercao retornou false (3).\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 4, 71);
	if(res) printf("Insercao retornou true (4). [OK]\n");
	else printf("Insercao retornou false (4).\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 5, 61);
	if(res) printf("Insercao retornou true (5). [OK]\n");
	else printf("Insercao retornou false (5).\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 6, 81);
	if(res) printf("Insercao retornou true (6). [OK]\n");
	else printf("Insercao retornou false (6).\n");
	exibirLog(f);


	printf("################# ATENDENDO #######################\n");
	exibirLog(f);
	res = atenderPrimeiraDaFila(f, &id);
	if(res) printf("Atendimento retornou true (7), id=%i. [OK]\n",id);
	else printf("Atendimento retornou false (7).\n");

	exibirLog(f);
	res = atenderPrimeiraDaFila(f, &id);
	if(res) printf("Atendimento retornou true (8), id=%i. [OK]\n",id);
	else printf("Atendimento retornou false (8).\n");

	exibirLog(f);
	res = atenderPrimeiraDaFila(f, &id);
	if(res) printf("Atendimento retornou true (9), id=%i. [OK]\n",id);
	else printf("Atendimento retornou false (9).\n");

	exibirLog(f);
	res = atenderPrimeiraDaFila(f, &id);
	if(res) printf("Atendimento retornou true (10), id=%i. [OK]\n",id);
	else printf("Atendimento retornou false (10).\n");

	exibirLog(f);
	res = atenderPrimeiraDaFila(f, &id);
	if(res) printf("Atendimento retornou true (11), id=%i. [OK]\n",id);
	else printf("Atendimento retornou false (11).\n");

	exibirLog(f);
	res = atenderPrimeiraDaFila(f, &id);
	if(res) printf("Atendimento retornou true (12), id=%i. [OK]\n",id);
	else printf("Atendimento retornou false (12).\n");

	exibirLog(f);
	res = atenderPrimeiraDaFila(f, &id);
	if(res) printf("Atendimento retornou true (13), id=%i.\n",id);
	else printf("Atendimento retornou false (13). [OK]\n");
	exibirLog(f);



	printf("################# INSERINDO PARTE 2 ###############\n");

	exibirLog(f);
	res = inserirPessoaNaFila(f, 7, 72);
	if(res) printf("Insercao retornou true (14). [OK]\n");
	else printf("Insercao retornou false (14).\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 8, 22);
	if(res) printf("Insercao retornou true (15). [OK]\n");
	else printf("Insercao retornou false (15).\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 9, 60);
	if(res) printf("Insercao retornou true (16). [OK]\n");
	else printf("Insercao retornou false (16).\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 10, 42);
	if(res) printf("Insercao retornou true (17). [OK]\n");
	else printf("Insercao retornou false (17).\n");
	exibirLog(f);


	printf("################# SAINDO DA FILA ##################\n");

	exibirLog(f);
	res = desistirDaFila(f, 6);
	if(res) printf("Desistindo da fila retornou true (18).\n");
	else printf("Desistindo da fila retornou false (18). [OK]\n");
	exibirLog(f);
	res = desistirDaFila(f, 7);
	if(res) printf("Desistindo da fila retornou true (19). [OK]\n");
	else printf("Desistindo da fila retornou false (19).\n");
	exibirLog(f);
	res = desistirDaFila(f, 8);
	if(res) printf("Desistindo da fila retornou true (20). [OK]\n");
	else printf("Desistindo da fila retornou false (20).\n");
	exibirLog(f);
	res = desistirDaFila(f, 9);
	if(res) printf("Desistindo da fila retornou true (21). [OK]\n");
	else printf("Desistindo da fila retornou false (21).\n");
	exibirLog(f);
	res = desistirDaFila(f, 10);
	if(res) printf("Desistindo da fila retornou true (22). [OK]\n");
	else printf("Desistindo da fila retornou false (22).\n");
	exibirLog(f);

	return 0;
}
