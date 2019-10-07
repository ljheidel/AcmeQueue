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
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libacmequeue.h"

#define LIST 1
#define PUSH 2
#define POP 4

int main (int argc, char **argv){
  char *queue_path = NULL;
  char *queue_name = NULL;
  int c;
  bool verbose = false;
  bool mode =  0;
  bool pop = false;
  bool list = false;
  char buf[1024];
  int index;
  
  fprintf(stderr, "%i %i %i\n", LIST, POP, PUSH);

  while ((c = getopt(argc, argv, "vuolp:n:")) != -1) {
    switch(c) {
      case 'u':
        mode = PUSH;  
        printf("u\n");
        break;
      case 'o':
        mode = POP;
        printf("o\n");
        break;
      case 'l': 
        mode = LIST;
        break;
      case 'p':
        queue_path = optarg;
        break;
      case 'n': 
        queue_name = optarg;
        break;
      case 'v':
        verbose = true;
        break;
      case '?':
        if (optopt == 'p') {
          fprintf(stderr, "Option -%c requires an arguement.\n", optopt);
        }
        if (optopt == 'n') {
          fprintf(stderr, "Option -%c requires an arguement.\n", optopt);
        }
        return 255;
    }
  }

  fprintf(stderr, "mode %i\n", mode);

  if ((mode & LIST) + (mode & PUSH) + (mode & POP) > 1) {
    fprintf(stderr, "Use only one of -l, -u or -o\n");
    return 255;
  }

  if (queue_path == NULL || queue_name == NULL) {
    fprintf(stderr, "-p and -n are mandator\n");
    return 255;
  }

  if (verbose) fprintf(stderr, "Usinq path %s and queue %s\n", queue_path, queue_name);
  AcmeQueue *aq = new AcmeQueue(queue_path, queue_name);
  if (verbose) aq->setDebug(true);
  if (mode & PUSH) {
    for (index = optind; index < argc; index++) {
      if (verbose) fprintf(stderr, "pushing...\n");
      aq->Push(argv[index]);  
    }
  } else if (mode & POP) {
    if (verbose) fprintf(stderr, "popping...\n");
    aq->Pop(buf);
    printf("%s", buf);
  } else if (mode & LIST) {
    if (verbose) fprintf(stderr, "listing...\n");
    aq->List();
  } 
 
  return 0; 
}
