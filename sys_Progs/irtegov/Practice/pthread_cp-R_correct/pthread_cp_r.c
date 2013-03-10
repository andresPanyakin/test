/* File:   ptread_cp_r.c
 * correct version, 
 * it is using condition variable to work around file handle limit
 * instead of idle wait.
 * Author: Dmitry V Irtegov
 *
 * Created on April 3, 2007, 14:32 AM
 */

#define POSIX_C_SOURCE 199506L

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifndef _STDC_C99
#include <alloca.h>
#endif

#define BUFSIZE 4096

/* this program uses C99 dynamic array or BSD alloca function.
 * alloca is de-facto standard in modern Unix system
 * and it simplifies code alot - we do not need to call free for every exit path
 */

char *srcdir, *dstdir; /* source and destination dirs */

/* hold this mutex while opening files */
pthread_mutex_t fileopen_mutex=PTHREAD_MUTEX_INITIALIZER;
/* signal this variable when you close files */
pthread_cond_t fileopen_cond=PTHREAD_COND_INITIALIZER;

int create_thread_with_retry(pthread_t *threadp, pthread_attr_t *attrp,
       void *(*body)(void *), void *arg) 
{
    int err;
    do {
        err=pthread_create(threadp, attrp, body, arg);
        if (err!=EAGAIN) {
            return err;
        } else if (err==EAGAIN) {
            printf("Waiting for free threads\n");
            sleep(1);
        }
    } while (err!=0);
    /* we will need to change this when we'll start using pthread_join */
    pthread_detach(*threadp);
    return 0;
}

/* 
 * body of file-copying thread
 * param is malloc'ed zero-terminated string, name of the file relative to srcdir
 * does free(3C) on param
 * we do not have other way to pass variable-lenght data to many threads
 */
void *copy_file(void * param) {
    char * filename=(char *)param;
#ifdef _STDC_C99    
    char srcpathname[strlen(srcdir)+strlen(filename)+2],
         dstpathname[strlen(dstdir)+strlen(filename)+2];
#else
    char *srcpathname=alloca(strlen(srcdir)+strlen(filename)+2),
         *dstpathname=alloca(strlen(dstdir)+strlen(filename)+2);
#endif
    int srcfile, dstfile;
    char buf[BUFSIZE];
    struct stat stat;
    ssize_t was_read;
    
    /* this code formally is dangerous for buffer overrun.
       However we've just checked size of all string elements
       and just allocated buffer as needed.  So this is safe - unless
       somebody modifies src/dstpathname definition.
    */
    strcat(strcat(strcpy(srcpathname, srcdir), "/"), filename);
    strcat(strcat(strcpy(dstpathname, dstdir), "/"), filename);

    /* get rid of parameter as soon as possible */
    free(param);

    pthread_mutex_lock(&fileopen_mutex);
    do {
        /* trying to open both files
         * this is important, if we'd open one file and wait for another,
         * this could lead to deadlock scenario
         */
        /* trying to open src file */
        srcfile=open(srcpathname, O_RDONLY, 0);
        if (srcfile < 0 && errno!=EMFILE) {
           fprintf(stderr, "errno=%d ", errno);
           perror(dstpathname);
           pthread_mutex_unlock(&fileopen_mutex);
           return NULL;
        } 
        if (srcfile>0) {
            fstat(srcfile, &stat); /* check mode of source file */
            dstfile=open(dstpathname, O_WRONLY | O_CREAT, stat.st_mode);
            if (dstfile < 0 && errno != EMFILE) {
                fprintf(stderr, "errno=%d ", errno);
                perror(dstpathname);
                close(srcfile);
                pthread_mutex_unlock(&fileopen_mutex);
		pthread_cond_signal(&fileopen_cond);
                return NULL;
            }
        }
        if (srcfile<0 || dstfile <0) {
            if (srcfile>0) {
                close(srcfile);
                pthread_cond_signal(&fileopen_cond);
            }
/*            printf("waiting for file handles - opening file %s or %s\n", srcpathname, dstpathname); */
            pthread_cond_wait(&fileopen_cond, &fileopen_mutex);
        }
    } while(dstfile<0 || srcfile<0);
    pthread_mutex_unlock(&fileopen_mutex);
        
    while((was_read=read(srcfile, buf, sizeof buf))>0) {
        if (write(dstfile, buf, was_read)<0) {
            perror(dstpathname);
            break;
        }
    }
    
    if (was_read<0) {
        perror(srcpathname);
    }
    
    /* we open many files in this process, never forget to close them! */
    close(srcfile);
    close(dstfile);
    pthread_cond_signal(&fileopen_cond);
    /* printf("%s to %s copy finished\n", srcpathname, dstpathname); */
    return NULL;
}

/* 
 * body of directory-copying thread
 * param is malloc'ed zero-terminated string, name of the file relative to srcdir
 * does free(3C) on param
 * we do not have other way to pass variable-lenght data to many threads
 */
void * copy_directory(void * param) {
#ifdef _STDC_C99    
    char srcpathname[strlen(srcdir)+strlen(param)+2],
         dstpathname[strlen(dstdir)+strlen(param)+2],
         dirname[strlen(param)+1];
#else
    char *srcpathname=alloca(strlen(srcdir)+strlen(param)+2),
         *dstpathname=alloca(strlen(dstdir)+strlen(param)+2),
         *dirname=alloca(strlen(param)+1);
#endif
    DIR * srcdirp;
    struct stat stat;
    size_t max_fname_length;

    /* see comment in similar code at copy_file */
    strcpy(dirname, param); /* we need to store relative dirname! */
    strcat(strcat(strcpy(srcpathname, srcdir), "/"), dirname);
    strcat(strcat(strcpy(dstpathname, dstdir), "/"), dirname);
    free(param);
    
    pthread_mutex_lock(&fileopen_mutex);
    do {
        srcdirp=opendir(srcpathname);
        if (srcdirp==NULL && errno != EMFILE) {
            pthread_mutex_unlock(&fileopen_mutex);
            perror(srcpathname);
            return NULL;
        } else if (srcdirp==NULL && errno == EMFILE) {
    /*        printf("waiting for file handles\n"); */
            pthread_cond_wait(&fileopen_cond, &fileopen_mutex);
        }
    } while(srcdirp==NULL);
    pthread_mutex_unlock(&fileopen_mutex);
    
    if (mkdir(dstpathname, 0700)<0) {
        if (errno==EEXIST) {
            if (access(dstdir, W_OK | X_OK)) {
                fprintf(stderr, "%s: file or directory exist and access denied\n", dstdir);
                exit(0);
            }
        } else {
            perror(dstpathname);
            closedir(srcdirp);
            pthread_cond_signal(&fileopen_cond);
            return NULL;
        }
    }
    
    /* determine maximum possible file name length
     * we must call this for every new directory because any directory can be mount point
     * so, theoretically, any directory can belong to different filesystem
     * file name length is filesystem-dependent.
     * this also will help if we ever will support symlinks
     */
   max_fname_length=pathconf(srcpathname, _PC_NAME_MAX);

   do {
#ifdef _STDC_C99
        char dirent_allocated_space[sizeof(struct dirent)+max_fname_length+2];
        struct dirent *entry=(struct dirent *)dirent_allocated_space;
#else
        struct dirent *entry=alloca(sizeof(struct dirent)+max_fname_length+2);
#endif        
        struct dirent *result;
        
#ifdef _POSIX_PTHREAD_SEMANTICS    
        readdir_r(srcdirp, entry, &result);
#else
        result=readdir_r(srcdirp, entry);
#endif        
        if (result==NULL) break;
        /* readdir(3C) CAN return . and .. entries */
        /* We DEFINITELY do not want to recurse there */
        if (result!=NULL) {
            char * relativepathname;
#ifdef _STDC_C99
            char absolutepathname[strlen(srcpathname)+strlen(result->d_name)+2];
#else
            char *absolutepathname=
                alloca(strlen(srcpathname)+strlen(result->d_name)+2);
#endif
            pthread_t thread;
            
            if (strcmp(result->d_name, ".")==0 
             || strcmp(result->d_name, "..")==0) continue;
            strcat(strcat(strcpy(absolutepathname, srcpathname), "/"), result->d_name);
            
            /* change this to stat(2) if you want this to follow symlinks */
            lstat(absolutepathname, &stat);
            
            relativepathname=strdup(absolutepathname+strlen(srcdir)+1);
            if(S_ISREG(stat.st_mode)) {         
                int err;
                err=create_thread_with_retry(&thread, NULL, &copy_file, relativepathname);
                if (err!=0) {
                    fprintf(stderr, "creating thread: %s\n", strerror(err));
                    free(relativepathname);
                    return NULL;
                }
            } else if(S_ISDIR(stat.st_mode)) {
                int err;
                err=create_thread_with_retry(&thread, NULL, &copy_directory, relativepathname);
                if (err!=0) {
                    fprintf(stderr, "creating thread: %s\n", strerror(err));
                    free(relativepathname);
                    return NULL;
                }
            } else {
                /* ignore anything else */
                free(relativepathname);
            }
        }
   } while(1);
   closedir(srcdirp);
   pthread_cond_signal(&fileopen_cond);
}

void atexit_print(void) {
    printf("Copy %s to %s finished\n", srcdir, dstdir);
}

int main(int argc, char **argv) {
    /* no local variables */
    
    if (argc<2) {
        fprintf(stderr, "Usage: %s srcdir dstdir\n", argv[0]);
        exit(0);
    }
    srcdir=argv[1];
    dstdir=argv[2];
    if(mkdir(dstdir, 0700)<0) {
        if (errno==EEXIST) {
            if (access(dstdir, W_OK | X_OK)) {
                fprintf(stderr, "%s: file or directory exist and access denied\n", dstdir);
                exit(0);
            }
        } else {
            perror(dstdir);
            exit(0);
        }
    }
    
    /* register handler to print something when all is finished */
    atexit(&atexit_print);

    /* now start! */
    copy_directory(strdup(""));
    pthread_exit(NULL);
}
