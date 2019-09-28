using namespace std;
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include "libacmequeue.h"

const char *queue_path = QUEUE_PATH;

AcmeQueue::AcmeQueue(const char *qn) {
  AcmeQueue(queue_path, qn);
}

AcmeQueue::AcmeQueue(const char *qp, const char *qn){
  // queueName = (char *)qn;
  // queuePath = (char *)qp;
  sprintf(dirName, "%s/%s", qp, qn);
  if (1) printf("queuepath is %s\ndirname is %s\n", qp, dirName);
  DIR* dir = opendir(dirName);
  if (dir == NULL) {
    int mkdir_result = mkdir(dirName, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  }
  closedir(dir);
}

bool AcmeQueue::Pop(char *s) {
  int file_number = 0;
  int max_file_number = 0;
  bool queue_empty = true;
  char file_name[255];
  char c;
  int count = 0;
  FILE *queue_file_fp;
  DIR *queue_dir_dp;
  struct dirent *directory_entry;
  if ((queue_dir_dp = opendir(dirName))) {
    while((directory_entry = readdir(queue_dir_dp)) != NULL) {
      if ((file_number = atoi(directory_entry->d_name))) {
        queue_empty = false;
        if (max_file_number < file_number) max_file_number = file_number;
      }
    }
    closedir(queue_dir_dp);
  }
  sprintf(file_name, "%s/%08d", dirName, max_file_number);
  if((queue_file_fp = fopen(file_name, "r"))) {
    while (!feof(queue_file_fp)) {
      s[count] = fgetc(queue_file_fp);
      count++;
    }
    s[count] = 0;
    fclose(queue_file_fp);
    remove(file_name);
  }
  return !queue_empty;
}

int AcmeQueue::Push(const char *s){
  int exist_file_number = 1;
  int file_number = 1;
  char file_name[255];
  FILE *queue_file_fp;
  DIR *queue_dir_dp;
  struct dirent *directory_entry;

  printf("dir name in Push is %s\n", dirName);  
  if ((queue_dir_dp = opendir(dirName))) {
    while((directory_entry = readdir(queue_dir_dp)) != NULL) {
      if ((exist_file_number = atoi(directory_entry->d_name))) {
        if (exist_file_number >= file_number) file_number = exist_file_number + 1;
      }
    }
    closedir(queue_dir_dp);
  } else {
    return 1;
  }

  sprintf(file_name, "%s/%08d", dirName, file_number);
  if (1) printf("generating file %s\n", file_name);

  if ((queue_file_fp = fopen(file_name, "w"))) {
    fprintf(queue_file_fp, "%s", s);
    fclose(queue_file_fp);
  } else {
    return -2;
  } 
  return 0;
}
