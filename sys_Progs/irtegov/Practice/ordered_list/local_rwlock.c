#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_LEN (81)

const int SLEEP_TIME = 5;


typedef struct tag_list_t {
  char* data;
  pthread_rwlock_t rwlock;
  struct tag_list_t* prev;
  struct tag_list_t* next;
} list_t;

list_t* list_create(void) {
  list_t* list = (list_t*)malloc(sizeof(list_t));
  if (NULL == list) {
    return NULL;
  }
  list->prev = NULL;
  list->next = NULL;
  list->data = NULL;
  if (pthread_rwlock_init(&list->rwlock, NULL)) {
    free(list);
    return NULL;
  }

  return list;
}

void list_release(list_t* list) {
  list_t* iter = list;

  assert(NULL != list);

  while (iter) {
    list_t* next = iter->next;
    free(iter->data);		
    pthread_rwlock_destroy(&iter->rwlock);
    free(iter);
    iter = next;
  }
}

list_t* list_add(list_t* list, char* str) {
  list_t* item = (list_t*)malloc(sizeof(list_t));
  if (NULL == item) {
    return NULL;
  }

  assert(NULL != list);

  if (pthread_rwlock_init(&item->rwlock, NULL)) {
    free(item);
    return NULL;
  }
    
  pthread_rwlock_wrlock(&list->rwlock);
  if (NULL != list->next) {
    pthread_rwlock_wrlock(&list->next->rwlock);
  }

  item->data = str;
  item->prev = list;
  item->next = list->next;
  if (NULL != list->next) {
    list->next->prev = item;
  }
  list->next = item;

  pthread_rwlock_unlock(&list->rwlock);
  if (NULL != item->next) {
    pthread_rwlock_unlock(&item->next->rwlock);
  }

  return item;
}

void swap_data(list_t* iteri, list_t* iterj) {
  char* tmp = NULL;

  assert(NULL != iteri);
  assert(NULL != iterj);

  tmp = iteri->data;
  iteri->data = iterj->data;
  iterj->data = tmp;
}

void list_print(list_t* list) {
  list_t* iter = NULL;

  assert(NULL != list);
	
  printf("________________________\n");
  if (NULL != list->next) {
    pthread_rwlock_rdlock(&list->next->rwlock);
  }
    
  for (iter = list->next; iter; iter = iter->next) {
    printf("%s \n", iter->data);

    pthread_rwlock_unlock(&iter->rwlock);
    if (NULL != iter->next) {
      pthread_rwlock_rdlock(&iter->next->rwlock);
    }
  }
  printf("________________________\n");
}

void* list_sort(void* p) {
  assert(NULL != p);

  while (1) {
    list_t* list = (list_t*)p;
    list_t* iteri = NULL;
	
    sleep(SLEEP_TIME);

    if (NULL != list->next) {
      pthread_rwlock_wrlock(&list->next->rwlock);
    }
    for (iteri = list->next; iteri; iteri = iteri->next) {
      list_t* iterj = NULL;
      if (NULL != iteri->next) {
	pthread_rwlock_wrlock(&iteri->next->rwlock);
      }
      for (iterj = iteri->next; iterj; iterj = iterj->next) {
	if (0 < strcmp(iteri->data, iterj->data)) {
	  swap_data(iteri, iterj);
	}
	pthread_rwlock_unlock(&iterj->rwlock);
	if (NULL != iterj->next) {
	  pthread_rwlock_wrlock(&iterj->next->rwlock);
	}
      }
      pthread_rwlock_unlock(&iteri->rwlock);
      if (NULL != iteri->next) {
	pthread_rwlock_wrlock(&iteri->next->rwlock);
      }
    }
    list_print(list);
  }
  return NULL;
}

int main(void) {
  char* cur = NULL;
  list_t* list = NULL;
  pthread_t sort_thread;

  list = list_create();
  if (NULL == list) {
    return -1;
  }

  if (pthread_create(&sort_thread, NULL, list_sort, (void*)(list))) {
    list_release(list);
    return -1;
  }

  do {
    cur = (char*)calloc(MAX_LEN, sizeof(char));
    if (NULL == cur) {
      list_release(list);
      return -1;
    }
    	
    fgets(cur, MAX_LEN, stdin);
	
    if ('\n' == cur[strlen(cur) - 1]) {
      cur[strlen(cur) - 1] = 0;
    }
    	
    if (0 == strlen(cur)) { 
      list_print(list);
      continue;
    }
    if (NULL == list_add(list, cur)) {
      list_release(list);
      return -1;
    }
  } while (1);

  pthread_cancel(sort_thread);

  pthread_join(sort_thread, NULL);

  list_release(list);
	
  return 0;
}
