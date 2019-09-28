#include <iostream>
#include <stdio.h>
#include "libacmequeue.h"

int main() {
  char s[255];
  AcmeQueue ac = AcmeQueue("EnvData");
  ac.Push("{\"is_json\": 1 }");
  ac.Pop(s);
  printf("%s", s);
}
