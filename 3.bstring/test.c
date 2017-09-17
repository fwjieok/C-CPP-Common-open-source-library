
#include <stdio.h>

#include "./bstrlib/bstrlib.h"


int main () {
    bstring aaa = bformat("name: %s", "ABCDEFG HIJKLMN OPQRST UVWXYZ");
    printf("bstring mlen: %d, slen: %d, data: %s\n", aaa->mlen, aaa->slen, aaa->data);

    bstring bbb = bformat("age: %d", 12345);
    bstring ccc = bformat("%s,%s,%d,%d,%d,%s",
                          aaa->data, bbb->data, 123, 456, 789, "Hello,world");
    struct bstrList *list = bsplit(ccc, ',');
    /* for (int i = 0; i < list->qty; i ++) { */
    /*     bstring ddd = *(list->entry + i); */
    /*     printf("entry: %s\n", ddd->data); */
    /*     //bdestroy(ddd); */
    /* } */
    printf("bstrList: qty: %d, mlen: %d\n", list->qty, list->mlen);

    bstring fff = bjoin(list, bfromcstr("&"));
    printf("ffff: %s\n", fff->data);

    bdestroy(aaa);
    bdestroy(bbb);
    bdestroy(ccc);
    bdestroy(fff);
    bstrListDestroy(list);
}
