#include <stdio.h>
#include "MST.h"


int main() {
    PGraphMartix pgm = GraphMartix_create(0, 6);
    GrapeMartix_print(pgm);

    Edge res[6];
    prim(pgm, res);

    return 0;
}