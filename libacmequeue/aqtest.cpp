using namespace std;
#include <iostream>
#include <stdio.h>
#include "libacmequeue.h"

int main() {
  char s[255];
  AcmeQueue *ac = new AcmeQueue("AcmeQueueTest");
  ac->setDebug(true);
  ac->Push("{\"is_json\": 1 }");
  ac->List();
  ac->Pop(s);
  printf("%s", s);
}
