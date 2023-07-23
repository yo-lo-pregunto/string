#include <assert.h>
#include <stdio.h>

#include "string.h"

int main(int argc, char *argv[])
{
    string_t string = string_new("paco MEMO");

    assert(string != NULL);

    assert(string_len(string) == 9);

    assert(str_equal(string, "paco MEMO") == Equal);

    str_t txt = string_capitalize(string);
    assert(text_equal(txt, "Paco MEMO") == Equal);

    txt = string_capitalize(string);
    printf("%s\n", txt);

    txt = string_case_fold(string);
    assert(text_equal(txt, "paco memo") == Equal);

    txt = string_capitalize(string);
    printf("%s\n", txt);

    string_destroy(&string);
    assert(string == NULL);

    return 0;
}
