/*
 * libacmequeue - A simple persistent FIFO queue for
 *                queing arbitrary data.
 *
 * Copyright (C) 2019 Acme Amalgamaged Widgets
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
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
/*
 * Two constructors.  One takes the queue path
 * the other only the queue name.
 *
 */
AcmeQueue::AcmeQueue(const char *qn) {
  this->setDebug(false);
  this->createDir(queue_path, qn);
}

AcmeQueue::AcmeQueue(const char *qp, const char *qn){
  this->setDebug(false);
  this->createDir(qp, qn);
}
/*
 * Create the queue directory.
 *
 */
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
/*
 * Turn on debug messages by setting
 * Debug to true.
 *
 */
void AcmeQueue::setDebug(bool d) {
  this->Debug = d;
}

bool AcmeQueue::getDebug() {
  return this->Debug;
}
/*
 * List the contents of the queue and their size.
 *
 */
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
/*
 * Pop a element off of the queue and 
 * store its contents in the char[] pointed
 * to by s.
 *
 */
bool AcmeQueue::Pop(char *s) {
  int file_number = 0;
  int max_file_number = 0;
  bool queue_empty = true;
  char file_name[255];
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
    while (!feof(queue_file_fp)) *s++ = fgetc(queue_file_fp); 
    *s = '\0';
    fclose(queue_file_fp);
    if (this->getDebug()) fprintf(stderr, "removing file %s\n", file_name);
    remove(file_name);
  }
  return !queue_empty;
}
/*
 * Push the string pointed to by s
 * in the queue.
 *
 */
int AcmeQueue::Push(const char *s){
  int exist_file_number = 1;
  int file_number = 1;
  char file_name[255];
  DIR *queue_dir_dp;
  FILE *queue_file_fp;
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
    while (*s != '\0') fputc(*s++, queue_file_fp); 
    fclose(queue_file_fp);
  } else {
    return -2;
  } 
  return 0;
}
