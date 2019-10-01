using namespace std;
#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libacmequeue.h"

main (int argc, char **argv){
  char *queue_path = NULL;
  char *queue_name = NULL;
  int c;

  while ((c = getopt(argc, argv, p:n:)) != -1) {
    switch(c) {
      case 'p':
        queue_path = optarg;
        break;
      case 'n': 
        queue_name = optarg;
        break;
      case '?':
        if (optopt == 'p' || optopt == 'n') {
          fprintf(stderr, "Option -%c requires an arguement.\n", optopt)
  
}

int main() {
  char s[255];
  AcmeQueue *ac = new AcmeQueue("AcmeQueueTest");
  ac->setDebug(true);
  ac->Push("{\"is_json\": 1 }");
  ac->List();
  ac->Pop(s);
  printf("%s", s);
}
