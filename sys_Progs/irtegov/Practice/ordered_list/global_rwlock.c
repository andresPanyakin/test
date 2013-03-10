#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_LEN (80)
typedef struct list_elem{
  struct list_elem* next;
  char*      data;
}list_elem;

typedef struct head_list_elem{
  struct list_elem* first;
  int size;
}head_list_elem;


pthread_rwlock_t global_mutex;

head_list_elem* cont_allocate(){
  head_list_elem* head = NULL;
  head = (head_list_elem*)malloc( sizeof (head_list_elem));
  assert ( head );
  head->size = 0;
  head->first = NULL;
  return head;
}

void cont_free ( head_list_elem* root ){
  list_elem* cur = root->first;
  list_elem* tmp = NULL;
  free(root);
  while ( cur ){
    tmp = cur->next;
    free(cur);
    cur = tmp;
  }
    
}

void cont_add_first ( head_list_elem* root, char* str ){
  list_elem* tmp        = NULL;
  list_elem* newElement = NULL;

  tmp = root->first;
  if ( NULL == tmp ){               

    pthread_rwlock_wrlock(&global_mutex);      //if container is empty

    newElement = (list_elem*)malloc(sizeof(list_elem));
    (root->size)++;           	  //allocate memory to the new element
    newElement->next   = NULL;
    newElement->data   = str;
    root->first = newElement;

    pthread_rwlock_unlock(&global_mutex);

    return;
  }

  pthread_rwlock_wrlock(&global_mutex);

  newElement = (list_elem*)malloc(sizeof(list_elem));
  (root->size)++;
  newElement->next   = (root->first);
  newElement->data   = str;
  root->first = newElement;

  pthread_rwlock_unlock(&global_mutex);

  return;
}

void swap ( list_elem* a, list_elem* b){
  void* tmp = a->data;
  a->data = b->data;
  b->data = tmp;
    
}

void cont_print ( head_list_elem* root ){
  pthread_rwlock_rdlock(&global_mutex);
  list_elem* cur = root->first;
    

  printf("________________________________\n");
  while ( cur ){
    printf ( "%s\n", cur->data );
    cur = cur->next;
  }
  printf("________________________________\n");
  pthread_rwlock_unlock(&global_mutex);
}

void* cont_sort(void* root) {
  assert( root );
    
  while (1) {
    list_elem* list  = ((head_list_elem*)root)->first;
    list_elem* iteri = NULL;
    sleep(5);

    pthread_rwlock_wrlock(&global_mutex);
    for (iteri = list; iteri; iteri = iteri->next) {
      list_elem* iterj = NULL;
      for (iterj = iteri->next; iterj; iterj = iterj->next) {
	if (0 < strcmp(iteri->data, iterj->data)) {
	            
	  swap(iteri, iterj);
	}
      }
    }

    pthread_rwlock_unlock(&global_mutex);
    cont_print(root);
	
  }
  return NULL;
}

int main(int argc, char* argv[]){
  char* cur = NULL;
  head_list_elem* root = NULL;
  pthread_t sort_thread;
	    
  pthread_rwlock_init(&global_mutex, NULL);
  root = cont_allocate();
						
  pthread_create(&sort_thread, NULL, cont_sort, (void*)(root));

  while (1){
    cur = (char*)calloc( MAX_LEN, sizeof(char));
    assert(cur);
	    
    fgets(cur, MAX_LEN, stdin);
    if ('\n' == cur[strlen(cur) - 1]) {
      cur[strlen(cur) - 1] = 0;
    }
		    
    if (0 == strlen(cur)) {
      cont_print(root);
      continue;
    }
    cont_add_first(root, cur);
  }
				
  pthread_cancel(sort_thread);
  pthread_join(sort_thread, NULL);
  pthread_rwlock_destroy(&global_mutex);
  cont_free(root);

  return 0;
}


