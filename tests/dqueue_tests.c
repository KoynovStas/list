#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



#include "stest.h"
#include "dqueue.h"





struct tmp_data
{
   dqueue_node node;
   int         data;
};



#define DECLARE_TMP_DATA(name) \
    struct tmp_data name = { {NULL, NULL}, 0}





TEST(test_dqueue_empty)
{
    DECLARE_DQUEUE(dqueue);
    DECLARE_TMP_DATA(d1);


    TEST_ASSERT(dqueue_empty(&dqueue));     //dqueue must be empty

    dqueue_push_front(&d1.node, &dqueue);   //now d1 is first

    TEST_ASSERT(!dqueue_empty(&dqueue));    //now dqueue is NOT empty


    TEST_PASS(NULL);
}



ptest_func tests[] =
{
    test_dqueue_empty,

};



MAIN_TESTS(tests)
