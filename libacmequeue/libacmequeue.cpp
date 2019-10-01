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
  this->setDebug(false);
  this->createDir(queue_path, qn);
}

AcmeQueue::AcmeQueue(const char *qp, const char *qn){
  this->setDebug(false);
  this->createDir(qp, qn);
}

void AcmeQueue::createDir(const char *qp, const char *qn) {
  int e;
  struct stat sb;

  sprintf(this->dirName, "%s/%s", qp, qn);
  e = stat(this->dirName, &sb);
  if (!e) {
    if (sb.st_mode & S_IFDIR) {
      if (this->getDebug()) fprintf(stderr, "directory %s already exists\n", this->dirName);
    } else {
      if (this->getDebug()) fprintf(stderr, "%s exists and is not a directory.\n", this->dirName);
    }
  } else if (errno == ENOENT) {
    if (this->getDebug()) fprintf(stderr, "%s doesnt exist - creating.\n", this->dirName);
    int mkdir_result = mkdir(this->dirName, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  }
}

void AcmeQueue::setDebug(bool d) {
  this->Debug = d;
}

bool AcmeQueue::getDebug() {
  return this->Debug;
}

void AcmeQueue::List() {
  DIR *queue_dir_dp;
  struct dirent *directory_entry;

  if (this->getDebug()) fprintf(stderr, "listing %s\n", this->dirName); 
  if ((queue_dir_dp = opendir(this->dirName))) {
    while ((directory_entry = readdir(queue_dir_dp)) != NULL) {
      printf("%8s %8d\n", directory_entry->d_name, directory_entry->d_reclen); 
    }
  }
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

  if (this->getDebug()) fprintf(stderr, "pop from %s\n", this->dirName); 

  if ((queue_dir_dp = opendir(this->dirName))) {
    while((directory_entry = readdir(queue_dir_dp)) != NULL) {
      if ((file_number = atoi(directory_entry->d_name))) {
        queue_empty = false;
        if (max_file_number < file_number) max_file_number = file_number;
      }
    }
    closedir(queue_dir_dp);
  }
  sprintf(file_name, "%s/%08d", this->dirName, max_file_number);
  if (this->getDebug()) fprintf(stderr, "reading from %s\n", file_name);
  if((queue_file_fp = fopen(file_name, "r"))) {
    while (!feof(queue_file_fp)) {
      s[count] = fgetc(queue_file_fp);
      count++;
    }
    s[count] = '\0';
    fclose(queue_file_fp);
    if (this->getDebug()) fprintf(stderr, "removing file %s\n", file_name);
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

  if (this->getDebug()) fprintf(stderr, "push to %s\n", this->dirName); 

  if ((queue_dir_dp = opendir(this->dirName))) {
    while((directory_entry = readdir(queue_dir_dp)) != NULL) {
      if ((exist_file_number = atoi(directory_entry->d_name))) {
        if (exist_file_number >= file_number) file_number = exist_file_number + 1;
      }
    }
    closedir(queue_dir_dp);
  } else {
    return 1;
  }

  sprintf(file_name, "%s/%08d", this->dirName, file_number);
  if (this->getDebug()) fprintf(stderr, "writing to file %s\n", file_name);

  if ((queue_file_fp = fopen(file_name, "w"))) {
    fprintf(queue_file_fp, "%s", s);
    fclose(queue_file_fp);
  } else {
    return -2;
  } 
  return 0;
}
