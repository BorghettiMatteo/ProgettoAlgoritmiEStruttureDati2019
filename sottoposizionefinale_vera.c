#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXIM 100
//working

//non si libera più nil

typedef struct tree{
	struct tree *padre,*left,*right;
	struct tree *tree_in_tree_head;
	int num_rel_entranti;
	char ricevente[50];
	}btree;

typedef struct hash{
	struct hash *next;
	char id_nome[50];
	}hash_id;

typedef struct treelist{
	struct tree *nodes;
	struct treelist *next;
	char relazione[50];
	}list_of_tree_roots;

typedef struct listreport{
	struct listreport *next;
	char id[50];
	}list_report;

typedef struct list{
	btree *elem;
	struct list *next;
	}tbdtreenode;



int hash_function(char []);
int delete_hash(char [],hash_id* [],hash_id *);
void inorder(btree*,btree*);
void gestione_input_fid_sid(char [],char [], char [], char [], char []);
void delete_tree_all(btree* , btree*);
void deletetree(btree*,btree*);
btree* search_for_duplicates(btree*,char [],btree*);
btree* delete_no_decremento(btree*,char [],btree*);
btree* search_and_insert(btree*, btree* , char [] , char []);
btree* exist_relation(list_of_tree_roots*, char []);
btree* insert(btree* , char [] ,btree*,char []);
btree* insert_tree(btree* , char [] , btree*);
btree* inorder_to_delete(btree*, btree*,char [],btree *);
btree* mintree(btree* ,btree*);
btree* search(btree*,char [],btree*);
btree* transplant(btree*, btree* , btree*, btree*);
btree* delete(btree*,char [],btree*,btree*);
list_of_tree_roots* delete_routine(list_of_tree_roots*,btree*);
list_of_tree_roots* delete_from_tree_roots(list_of_tree_roots*,char [] , btree*); 
list_of_tree_roots* append_roots(list_of_tree_roots*,char [], btree*); 
list_report* compile_report(btree*,btree*,int *);
list_report* append(list_report*,char []);
btree* delete_no_decremento_fast(btree*,btree*,btree*);

list_report *head = NULL;
tbdtreenode *listaa=NULL;

int main(int argc,char *argv[]){
	tbdtreenode *tempdeleteroot = NULL;
	int i=0,valhash=0,cont,flag,flag_a;
	char comand[50] , fid[50] , sid[50] , idrels[50];
	btree *nil=NULL;
	btree *temproot=NULL,*radicealbero=NULL , *x = NULL,*aa = NULL,*fg=NULL;
	list_of_tree_roots *head_tree_list=NULL , *temp_tree_root = NULL , *p=NULL ,*pa=NULL,*temparr[20];
	hash_id *array[100], *nuovonodes = NULL , *temp_hash_head = NULL ,*forsearch_addrel=NULL;
	list_report *deletelist=NULL;
	//list_report *head_report = NULL;
	int max = 0,j=0;	
	int returnscanf=0;
	nil = (btree*)malloc(sizeof(btree));
	nil->left = nil;
	nil->right = nil;
	nil->padre = nil;
	nil->tree_in_tree_head = NULL;
	nil->num_rel_entranti = -1;
	memset(nil->ricevente,'\0',50);
	for(cont=0;cont<100;cont++)
		array[cont] = NULL;
	
	do{
		memset(comand,'\0',50); //free la stringa idrels così da poter fare una end corretta
		memset(fid,'\0',50);
		memset(sid,'\0',50);
		memset(idrels,'\0',50);
		//memset(input,'\0',100);
		flag = 0;	
		flag_a = 0;
		temproot = NULL;
		radicealbero = NULL;
		//temp_tree_root = NULL;
		p = NULL;
		x = NULL;
		fg = NULL;
		pa = NULL;
		p= NULL;
		aa = NULL;
		nuovonodes = NULL;
		temp_hash_head = NULL;
		forsearch_addrel=NULL;
		listaa=NULL;
		for(cont=0;cont<20;cont++)
			temparr[cont] = NULL;
		returnscanf=scanf("%s",comand);
		if((strcmp(comand,"addent")==0) || (strcmp(comand,"delent")==0)){	
			returnscanf=scanf("%s",fid);
		}else{ if(strcmp(comand,"report")==0 ||(strcmp(comand,"end")==0))
				;
			else{
				returnscanf=scanf("%s",fid);
				returnscanf=scanf("%s",sid);
				returnscanf=scanf("%s",idrels);
				}
		}		
		//fine input
/****************************************************************************************************************************/

		if(strcmp(comand,"addrel") == 0){
			valhash = 0;

			valhash = hash_function(fid);
			forsearch_addrel= array[valhash];
			while(forsearch_addrel != NULL && flag_a==0){
				if(strcmp(forsearch_addrel-> id_nome , fid) == 0){
						flag_a = 1;
 				}else{ forsearch_addrel = forsearch_addrel->next;
					flag_a = 0;
				}
			}
			forsearch_addrel=NULL;
			valhash = hash_function(sid);
			forsearch_addrel = array[valhash];
			while(forsearch_addrel != NULL && flag==0){
				if(strcmp(forsearch_addrel-> id_nome , sid) == 0){
						//printf("entità presente\n");
						flag = 1;
				}else{
					forsearch_addrel = forsearch_addrel->next;
					flag = 0;
					}
			}
			//printf("ADDREL 1.1: %d  %d\n",flag,flag_a);
			if(flag == 1 && flag_a == 1){ //se falg == 1 tutte le entità sono presenti
				//printf("ADDREL 2: ho trovato sid e fid\n");
				//controllare se idrels è già presepnte nell'array delle liste
				p = head_tree_list;
				while(p){
					if(strcmp(p->relazione,idrels)==0){
						radicealbero = p->nodes;
						//printf("1\n");
						break;					
					}
					p = p->next;	
				}
				temproot = radicealbero;
				if(temproot != NULL && p!=NULL){
					//printf("ADDREL 3:  sto inserendo nella relazione %s , con nodo radice %s\n",p->relazione,temproot->ricevente);
					//Se esite la esiste la relazione
					fg = temproot;
					while((fg != nil)&&(strcmp(fg->ricevente,sid)!=0)){
						if(strcmp(fg -> ricevente , sid) <0){


							fg = fg -> right;
						}else
							fg = fg -> left;
					}
					if(fg == nil){
						//printf("ADDREL 4:  non ho trovato il nodo ricevente, devo aggiungere il nodo %s \n",fg->ricevente);
						temproot = insert(temproot,sid,nil,fid);				
						p -> nodes = temproot;					
					}else{
					//il nodo già esiste ma dovo modificarne il valore
						//printf("ADDREL 5: nodo %s  esistente , aggiornamento dei contatori %d\n",fg->ricevente,fg->num_rel_entranti);
						x = fg;
						if(search_for_duplicates(fg->tree_in_tree_head,fid,nil)==nil){
							//printf("ADDREL 6:  sto aggiornando la quantità di %s \n",fg->ricevente);
							fg->num_rel_entranti= fg->num_rel_entranti+1;
							//printf("ADDREL 7:  sto aggiornando l'albero tree in tree per inserire %s \n",fid);
							x->tree_in_tree_head = insert_tree(x->tree_in_tree_head,fid,nil);
											
						}					
					}
					//inserisco nel nodo nel nodo 		
				}else{
					//inizializzazione root;
					temproot =(btree*)malloc(sizeof(btree));
					temproot->padre = nil;
					temproot->left=nil;
					temproot->right=nil;
					temproot->tree_in_tree_head = NULL;
					temproot->num_rel_entranti = 1;
					strcpy(temproot->ricevente,sid);
					// inserisco nodo in nodo albero
					temproot->tree_in_tree_head = nil; 
					temproot->tree_in_tree_head = insert_tree(temproot->tree_in_tree_head , fid , nil);
					head_tree_list = append_roots(head_tree_list, idrels , temproot);
					//head_tree_list->nodes = temproot;	
				}
			
			}
					
/* *******************************************************************************************************************************************/
		}else if(strcmp(comand,"addent") == 0){
			
			valhash = hash_function(fid);
			temp_hash_head = array[valhash];
			while(temp_hash_head && flag!=1){
				if(strcmp(temp_hash_head->id_nome , fid) == 0){
					//printf("6\n");
					flag=1;
				}else{	
					//printf("7\n");
					temp_hash_head = temp_hash_head->next;
					flag=0;
				}				
			}
			if(flag==0){	
				nuovonodes=(hash_id*)malloc(sizeof(hash_id));
				strcpy(nuovonodes->id_nome , fid);
				nuovonodes -> next = array[valhash];
				array[valhash] = nuovonodes;
			//printf("ADDENT 1:anagrafica = %s\n",nuovonodes->id_nome);
			}
		
/****************************************************************************************************************************************/
		}else if(strcmp(comand,"delent") == 0){
			//cerca enità fid in hashtable		
			if(delete_hash(fid,array,temp_hash_head)==1){
				//printf("8\n");
				pa = head_tree_list;
				while(pa != NULL){
					//printf("9\n");
					x = pa -> nodes;
					pa -> nodes = inorder_to_delete(pa->nodes,nil,fid,x);
					//fine iterazivo
					if(listaa != NULL){
						tempdeleteroot = listaa;
						while(tempdeleteroot != NULL){
							pa->nodes = delete_no_decremento_fast(pa->nodes,tempdeleteroot->elem,nil);
							tempdeleteroot = tempdeleteroot -> next;
						}

					while(listaa != NULL){	
						tempdeleteroot = listaa;
						listaa = listaa -> next;
							free(tempdeleteroot);
					}
					}
					
					if(pa->nodes == nil){
						//printf("10\n");
						head_tree_list = delete_from_tree_roots(head_tree_list,pa->relazione,pa->nodes);
						pa = head_tree_list;
					}else
						pa = pa -> next;
				}	
			}
/*****************************************************************************************************************************************/
		}else if(strcmp(comand,"delrel") == 0){
			//controllo che fid e sid siano presenti nella tabella hash			
			valhash = hash_function(fid);
			temp_hash_head = array[valhash];
			while(temp_hash_head != NULL && flag_a==0){
				if(strcmp(temp_hash_head -> id_nome , fid) == 0){
						flag_a = 1;
						//printf("11\n");
						////printf("entità presente\n");
 				}else{ temp_hash_head = temp_hash_head->next;
					flag_a = 0;
				}
			}
			temp_hash_head = NULL;
			valhash = hash_function(sid);
			temp_hash_head = array[valhash];
			while(temp_hash_head != NULL && flag==0){
				//printf("12\n");
				if(strcmp(temp_hash_head -> id_nome , sid) == 0){
						////printf("entità presente\n");
						flag = 1;
				}else{
					temp_hash_head = temp_hash_head->next;
					flag = 0;
					}
			}
			if(flag == 1 && flag_a == 1){	
				//controllo presenza relazione	
				p = head_tree_list;
				//printf("albero -> %s\n",p->relazione);
				while(p){
					//printf("13\n");
					if(strcmp(p->relazione,idrels)==0){
						radicealbero = p->nodes;
						break;					
					}else
						p = p->next;	
				}
				temproot = radicealbero;
				if(p !=  NULL){
				if(strcmp(p->relazione,idrels)==0){
				//ricerca del nodo sid dopo aver trovato l'albero della relazione
					x = temproot;
					while((x != nil)&&(strcmp(x->ricevente,sid))!=0){
						if(strcmp(x -> ricevente , sid) <0){
							x = x -> right;
						}else
							x = x -> left;
					}			
					if(x != nil&&strcmp(x->ricevente,sid)==0){
						aa = x;
						x -> tree_in_tree_head = delete(x->tree_in_tree_head,fid,nil,aa);
						if(x->num_rel_entranti == 0){
							//eliminazione nodo
							temproot = delete_no_decremento_fast(temproot,x,nil);	
						}
						p->nodes = temproot;	
						if(temproot==nil){
							head_tree_list = delete_from_tree_roots(head_tree_list,idrels,temproot);	
												
						}
					}			
				}
				}	
			}

/****************************************************************************************************************************************/
		}else if(strcmp(comand,"report") == 0){
			p = head_tree_list;
			list_report *temporary=NULL;
			if(head_tree_list){
				for(i=0;p!=NULL;p = p->next,i++){
					temparr[i] = p;
				}
				for(j=0;j<i;j++){
					for(cont=0;cont<i-j-1;cont++){
						if(strcmp(temparr[cont]->relazione,temparr[cont+1]->relazione)>0){
							pa = temparr[cont];
							temparr[cont]=temparr[cont+1];
							temparr[cont+1]=pa;
						}
					}
				}
				i = 0;
				p = NULL;
				while(temparr[i]){
					max=0;
					p = temparr[i];
					head = compile_report(p->nodes,nil,&max);
					//fputs(p->relazione,stdout);
					fputs(p->relazione,stdout);				
					fputs(" ",stdout);
					temporary = head;
					while(temporary!=NULL){
						fputs(temporary->id,stdout);
						fputs(" ",stdout);
						temporary = temporary->next;
					
					}
					temporary = NULL;
					printf("%d;",max);
					if(temparr[i+1] != NULL)
						fputs(" ",stdout);
				p = p -> next;
				i++;
				}
				fputs("\n",stdout);
			}else fputs("none\n",stdout);
			
		}

	i = 0;//restora l'indice di scorrimento a 0,non avendo for devo farlo per forza
	//memset(input,'\0',100); //free l'input per anvere una nuova stringa linda per input
	valhash = 0;
	}while(strcmp(comand,"end") != 0);
	/*head_tree_list = delete_routine(head_tree_list,nil);
	for(cont=0;cont<100;cont++){
		while(array[cont]){
			temp_hash_head = array[cont];
			array[cont]=array[cont]->next;
			free(temp_hash_head);
		}
	array[cont]=NULL;
	}
	free(nil);	
	while(head){
		deletelist = head;
		head = head -> next;
		free(deletelist);
	}*/
	//nil = NULL;	
return 0;

}

	
int hash_function(char da_convertire[]){
	float valhash=0;
	int i=0;
	while(da_convertire[i]!='\0'){
		valhash = valhash +(float)da_convertire[i];
		i++;
	}
	//printf("%f\n",valhash);
	valhash = valhash/100;
	valhash = valhash-(int)valhash;
	valhash = valhash*90+5;
	
return (int)valhash;
}

btree* insert(btree *root, char da_inserire[],btree *nil,char rel_uscente[]){  //inserisce nodo exnovo nell albero relazione
	btree *newnode;
	btree *y = nil;
	btree *x;
	x = root;
	newnode = (btree*)malloc(sizeof(btree));	
	newnode -> padre = nil;
	newnode -> left = nil;
	newnode -> right = nil;
	newnode -> num_rel_entranti = 1;
	strcpy(newnode -> ricevente , da_inserire);
	while(x != nil){
		//printf("19\n");
		y = x;
		if(strcmp(newnode -> ricevente , x -> ricevente)<0){
			x = x -> left;
		}
		else{ x = x -> right;
		}
	newnode -> padre = y;
	}if(y == nil)
		root = newnode;
	else if(strcmp(newnode -> ricevente , y -> ricevente)<0){
			y -> left = newnode;
			//printf("INSTERT SX : ho inserito nell'albero delle relazioni %s\n",y->left->ricevente);			
			y -> left -> tree_in_tree_head = nil;			
			y -> left -> tree_in_tree_head = insert_tree(y->left->tree_in_tree_head,rel_uscente,nil);
		}
		else{
			y -> right = newnode;
			//printf("INSERT DX: ho inserito nell'albero delle relazioni %s\n",y->right->ricevente);
			y -> right -> tree_in_tree_head = nil;
			y -> right -> tree_in_tree_head = insert_tree(y->right->tree_in_tree_head,rel_uscente,nil);
		}
	return root;
}

btree* insert_tree(btree *root, char da_inserire[],btree *nil){  //inserisce nodo exnovo nell albero delle relazioni uscenti
	btree *newnode;
	btree *y = nil;
	btree *x;
	x = root;
	newnode = (btree*)malloc(sizeof(btree));
	newnode -> padre = nil;
	newnode -> left = nil;
	newnode -> right = nil;
	//newnode -> num_rel_entranti = -2;
	strcpy(newnode -> ricevente , da_inserire);
	while(x != nil){
		//printf("20\n");
		y = x;
		if(strcmp(newnode -> ricevente , x -> ricevente)<0){
			x = x -> left;
		}
		else{ x = x -> right;
		}
	newnode -> padre = y;
	}if(y == nil)
		root = newnode;
	else if(strcmp(newnode -> ricevente , y -> ricevente)<0)
		y -> left = newnode;
	else y -> right = newnode;
	//printf("INSERT_TREE 1: ho inserito nell'albero delle relazioni %s , left = %s , right = %s\n",newnode->ricevente,y->left->ricevente,y->right->ricevente);
	return root;
}

int delete_hash(char id_delete[] , hash_id *array[],hash_id *hash_head){
	hash_id *tbd=NULL , *temp=NULL ,*temphead = NULL;
	int valhashtemp,flag_a=0;
	valhashtemp = hash_function(id_delete);
	temphead = array[valhashtemp];
	while(temphead && flag_a==0){
		if(strcmp(temphead -> id_nome , id_delete) == 0){
			flag_a = 1;
 		}else{ temphead = temphead->next;
			flag_a = 0;
		}
	}
	if(flag_a==1){ //si cancella e riconcatena lista
		if(strcmp(array[valhashtemp]->id_nome,id_delete)==0 && array[valhashtemp]!=NULL){		
			tbd=array[valhashtemp];
			array[valhashtemp] = array[valhashtemp] -> next;
			free(tbd);

		}
		temp = array[valhashtemp];
		while(temp && temp -> next){
			if(strcmp(temp -> next -> id_nome , id_delete) == 0){
				tbd = temp -> next;
				temp -> next = tbd -> next;
				free(tbd);
			}
			else
				temp = temp -> next;
		}
	}else
		return 0;
	return 1;
}

btree* inorder_to_delete(btree *root, btree *nil,char id_delete[],btree *radiceoriginaria){
	btree *temproot_c = NULL,*deletetreetemp=NULL;
	tbdtreenode *tbd=NULL; 
	if(root != nil){
		temproot_c = root;
		inorder_to_delete(root->left,nil,id_delete,radiceoriginaria);	
		if(strcmp(temproot_c->ricevente,id_delete)==0){
			deletetreetemp=temproot_c->tree_in_tree_head;
			deletetree(deletetreetemp,nil);			
			tbd =(tbdtreenode*)malloc(sizeof(tbdtreenode));
			tbd->elem = temproot_c;
			tbd -> next = listaa;
			listaa = tbd;
			temproot_c = root;
		}else{
			temproot_c->tree_in_tree_head = delete(temproot_c->tree_in_tree_head,id_delete,nil,temproot_c);
			root = temproot_c;
			if(temproot_c->num_rel_entranti == 0){
				tbd =(tbdtreenode*)malloc(sizeof(tbdtreenode));
				tbd->elem = temproot_c;
				tbd -> next = listaa;
				listaa = tbd;
			}
				//radiceoriginaria = delete(radiceoriginaria,id_delete,nil,temproot); //cancella nodo se ilcontatore
		}			
		inorder_to_delete(root->right,nil,id_delete,radiceoriginaria);		
	}
	return radiceoriginaria;
}


btree* delete(btree *root,char tbd[],btree *nil,btree *temproot_c){
	btree *tbdnodes = NULL,*y = NULL , *temproot_b = NULL;
	temproot_b = root;	
	tbdnodes = search(temproot_b,tbd,nil);
	//printf("banane %s e %s\n",root->ricevente,temproot_b->ricevente);
	//printf("nodo da cercare %s\n",tbdnodes->ricevente);
	if(strcmp(tbdnodes->ricevente,tbd)==0){
		temproot_c->num_rel_entranti = temproot_c->num_rel_entranti-1;
		if(tbdnodes -> left == nil)
			temproot_b = transplant(temproot_b,tbdnodes,tbdnodes -> right,nil);
		else if(tbdnodes -> right == nil)
				temproot_b = transplant(temproot_b,tbdnodes,tbdnodes -> left,nil);
			else{ 
				y = mintree(tbdnodes -> right,nil);
				if(y -> padre != tbdnodes){	
					temproot_b = transplant(temproot_b,y,y -> right,nil);
					y -> right = tbdnodes -> right;
					y -> right -> padre = y;
				}
				temproot_b = transplant(temproot_b,tbdnodes,y,nil);
				y -> left = tbdnodes -> left;
				y -> left -> padre = y;
			}
		free(tbdnodes);
		root = temproot_b;
	}
	return root;	
}


btree* transplant(btree *temproot_a , btree *u , btree *v, btree *nil){
	if(u -> padre == nil)
		temproot_a = v;
	else{
		if(u == u -> padre -> left){
			u -> padre -> left = v;	
		}
		else u -> padre -> right = v;
	}if(v != nil)
		v -> padre = u -> padre;
	//free(u);
	return temproot_a;
}

btree* search(btree *xz,char da_cercare[],btree *nil){
	if((xz == nil)||(strcmp(da_cercare,xz->ricevente)==0)){
		return xz;
	}
	if(strcmp(da_cercare,xz->ricevente)<0){
		return search(xz -> left,da_cercare,nil);
	}else return search(xz -> right,da_cercare,nil);
}

btree* mintree(btree *root,btree* nil){
	btree *xx = root;
	while(xx -> left != nil)
		xx = xx -> left;
	return xx;
}


void deletetree(struct tree *broot,struct tree *nil){
	if(broot != nil){
		deletetree(broot -> left,nil);
		deletetree(broot -> right,nil);
	free(broot); 
	}
		//printf("banana terracottan\n");
}

list_of_tree_roots* delete_routine(list_of_tree_roots *head_x,btree *nil){
	list_of_tree_roots *py=NULL,*tbd=NULL;
	py = head_x;
	while(py){
		delete_tree_all(py->nodes,nil);
		tbd = py;
		py = py -> next;
		free(tbd);		
	}
return head_x=py;
}

void delete_tree_all(btree *root,btree *nil){
	if(root==nil){
		return;
	}
	delete_tree_all(root->left,nil);
	deletetree(root->tree_in_tree_head,nil);
	delete_tree_all(root->right,nil);
	free(root);
}

//cerca nell'albero tree_in_tree se il nodo fid esite di già,se così ritorna 0
btree* search_for_duplicates(btree *head_dup,char da_cercare[],btree *nil){
	if(head_dup == nil){
		//printf("21\n");
		return nil;
	}
	else{ if(strcmp(da_cercare,head_dup->ricevente)==0 && head_dup != nil)
		return head_dup;
	}if(strcmp(da_cercare,head_dup->ricevente)<0){
		search_for_duplicates(head_dup -> left,da_cercare,nil);
	}else search_for_duplicates(head_dup -> right,da_cercare,nil);
}

btree* delete_no_decremento(btree *root,char tbd[],btree *nil){
	btree *tbdnode = NULL,*yz = NULL , *temp_root = NULL;
	temp_root=root;	
	tbdnode = search(temp_root,tbd,nil);
	if(tbdnode != nil){
		if(tbdnode -> left == nil)
			temp_root = transplant(temp_root,tbdnode,tbdnode -> right,nil);
		else if(tbdnode -> right == nil)
				temp_root = transplant(temp_root,tbdnode,tbdnode -> left,nil);
			else{
				yz = mintree(tbdnode -> right,nil);
				if(yz -> padre != tbdnode){	
					temp_root = transplant(temp_root,yz,yz -> right,nil);
					yz -> right = tbdnode -> right;
					yz -> right -> padre = yz;
				}
				temp_root = transplant(temp_root,tbdnode,yz,nil);
				yz -> left = tbdnode -> left;
				yz -> left -> padre = yz;
			}
	free(tbdnode);
	root = temp_root;
	}
	return root;	
}

list_of_tree_roots* delete_from_tree_roots(list_of_tree_roots *head_tree_list , char idrelazione[] , btree *temproot){
	list_of_tree_roots *temp = NULL,*tbd = NULL;
	if(head_tree_list!=NULL && strcmp(head_tree_list->relazione,idrelazione)==0){		
		tbd=head_tree_list;
		head_tree_list = head_tree_list -> next;
		//free(head_list->nodes);
		free(tbd);
	}
	temp = head_tree_list;
	while(temp && temp -> next){
		//printf("22\n");
		if(strcmp(temp -> next -> relazione , idrelazione) == 0){
			tbd = temp -> next;
			temp -> next = tbd -> next;
			//free(temp->nodes);
			free(tbd);
		}
		else
			temp = temp -> next;
	}
	return head_tree_list;
}
	
list_report* compile_report(btree *rootbanane,btree *nil,int *max){
	list_report *tbd=NULL;
	if(rootbanane != nil){
		compile_report(rootbanane->left,nil,max);
				//printf("valore maxd %d\n",*max);
				if(rootbanane->num_rel_entranti > *max && rootbanane!=nil){
					*max = rootbanane->num_rel_entranti;					
					if(head != NULL){
						while(head){ //elimina tutta la lista per ripopolarla
							//printf("deleten nodo lista\n");
							tbd = head;
							head = head -> next;
							free(tbd);
						}
					head = NULL;
					}
					head = append(head,rootbanane->ricevente);							
				}else if(rootbanane->num_rel_entranti==*max && rootbanane!=nil){ // il nodo controllato è ha già il valore massimo
						head = append(head,rootbanane->ricevente);						
						}
		compile_report(rootbanane->right,nil,max);
	}
return head;
}

list_report* append(list_report *head,char ins[]){
	list_report *newnode=NULL,*px=NULL;
	newnode=(list_report*)malloc(sizeof(list_report));
		strcpy(newnode->id,ins);
		newnode -> next = NULL;
		if(head){
			for(px = head; px -> next != NULL ; px = px-> next)
				;
			px -> next = newnode;
		}else head = newnode;
	
	return head;
}

list_of_tree_roots* append_roots(list_of_tree_roots* headtree,char da_inserire[],btree *radice){
	list_of_tree_roots *newnode=NULL,*px=NULL;
	newnode=(list_of_tree_roots*)malloc(sizeof(list_of_tree_roots));
	strcpy(newnode->relazione,da_inserire);
	newnode -> next = NULL;
	newnode -> nodes = radice;
	if(headtree){
		for(px = headtree; px -> next != NULL ; px = px-> next)
			;
		px -> next = newnode;
	}else headtree = newnode;
	return headtree;
}





btree* delete_no_decremento_fast(btree *root,btree *tbd,btree *nil){
	btree *tbdnode = NULL,*yz = NULL , *temp_root = NULL;
	temp_root=root;	
	tbdnode = tbd;
	if(tbdnode != nil){
		if(tbdnode -> left == nil)
			temp_root = transplant(temp_root,tbdnode,tbdnode -> right,nil);
		else if(tbdnode -> right == nil)
				temp_root = transplant(temp_root,tbdnode,tbdnode -> left,nil);
			else{
				yz = mintree(tbdnode -> right,nil);
				if(yz -> padre != tbdnode){	
					temp_root = transplant(temp_root,yz,yz -> right,nil);
					yz -> right = tbdnode -> right;
					yz -> right -> padre = yz;
				}
				temp_root = transplant(temp_root,tbdnode,yz,nil);
				yz -> left = tbdnode -> left;
				yz -> left -> padre = yz;
			}
	free(tbdnode);
	root = temp_root;
	}
	return root;	
}










