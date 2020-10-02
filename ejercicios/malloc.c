#include <stdio.h>
#include <stdlib.h>

int main(){

  void *v = malloc(1073741824);

  if(v == NULL){
    printf("No pude\n");
  }
  else{
    ("Si pude\n");
  }
  free(v);
}
