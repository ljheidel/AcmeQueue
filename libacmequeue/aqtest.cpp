using namespace std;
#include <iostream>
#include <stdio.h>
#include "libacmequeue.h"

int main() {
  char s[255];
  printf("construct\n");
  AcmeQueue *ac = new AcmeQueue("AcmeQueueTest");
  printf("Push\n");
  ac->Push("{\"is_json\": 1 }");
  printf("Pop");
  ac->Pop(s);
  printf("%s", s);
}
