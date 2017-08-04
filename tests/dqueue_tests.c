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



TEST(test_dqueue_is_first)
{
    DECLARE_DQUEUE(dqueue1);
    DECLARE_DQUEUE(dqueue2);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);
    DECLARE_TMP_DATA(d3);


    dqueue_push_front(&d1.node, &dqueue1);              //now d1 is first

    TEST_ASSERT(dqueue_is_first(&d1.node, &dqueue1));   //d1 must be first


    dqueue_push_front(&d2.node, &dqueue1);              //now d2 is first

    TEST_ASSERT(dqueue_is_first(&d2.node, &dqueue1));   //d2 must be first
    TEST_ASSERT(!dqueue_is_first(&d1.node, &dqueue1));  //d1 is not first (d1 is last)


    dqueue_push_front(&d3.node, &dqueue2);              //now d3 is first
    TEST_ASSERT(!dqueue_is_first(&d3.node, &dqueue1));  //d3 is not first (d3 out of the dqueue1.)
    TEST_ASSERT(dqueue_is_first(&d3.node, &dqueue2));   //d3 is first in dqueue2


    TEST_PASS(NULL);
}



TEST(test_dqueue_is_last)
{
    DECLARE_DQUEUE(dqueue1);
    DECLARE_DQUEUE(dqueue2);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);
    DECLARE_TMP_DATA(d3);


    dqueue_push_front(&d1.node, &dqueue1);              //now d1 is first

    TEST_ASSERT(dqueue_is_last(&d1.node, &dqueue1));    //d1 must be first and last (list is circular)


    dqueue_push_back(&d2.node, &dqueue1);               //now d2 is last

    TEST_ASSERT(dqueue_is_last(&d2.node, &dqueue1));    //d2 must be last
    TEST_ASSERT(!dqueue_is_last(&d1.node, &dqueue1));   //now d1 dont must be last (d1 is first)


    dqueue_push_front(&d3.node, &dqueue2);             //now d3 is first

    TEST_ASSERT(!dqueue_is_last(&d3.node, &dqueue1));  //d3 is not first (d3 out of the dqueue1)
    TEST_ASSERT(dqueue_is_last(&d3.node, &dqueue2));   //d3 is first and last in dqueue2


    TEST_PASS(NULL);
}



TEST(test_dqueue_is_singular)
{
    DECLARE_DQUEUE(dqueue);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);


    TEST_ASSERT(!dqueue_is_singular(&dqueue));     //list must be empty (not singular)


    dqueue_push_front(&d1.node, &dqueue);          //now d1 is first

    TEST_ASSERT(dqueue_is_singular(&dqueue));      //list must be singular (in list only d1)


    dqueue_push_back(&d2.node, &dqueue);           //now d2 is last

    TEST_ASSERT(!dqueue_is_singular(&dqueue));     //list dont must be singular (in list d1,d2)


    TEST_PASS(NULL);
}



TEST(test_dqueue_size)
{
    DECLARE_DQUEUE(dqueue);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);
    DECLARE_TMP_DATA(d3);


    //add
    TEST_ASSERT(dqueue_size(&dqueue) == 0);    //size == 0 (dqueue is empty)

    dqueue_push_front(&d1.node, &dqueue);      //now d1 is first
    TEST_ASSERT(dqueue_size(&dqueue) == 1);    //size == 1 (d1)
    TEST_ASSERT(!dqueue_empty(&dqueue));       //dqueue dont must be empty

    dqueue_push_back(&d2.node, &dqueue);     //now d2 is last
    TEST_ASSERT(dqueue_size(&dqueue) == 2);  //size == 2 (d1,d2)
    TEST_ASSERT(!dqueue_empty(&dqueue));     //dqueue dont must be empty

    dqueue_push_back(&d3.node, &dqueue);     //now d3 is last
    TEST_ASSERT(dqueue_size(&dqueue) == 3);  //size == 3 (d1,d2, d3)
    TEST_ASSERT(!dqueue_empty(&dqueue));     //dqueue dont must be empty


    //delete
    dqueue_del(&d1.node, &dqueue);           //now d1 is not in list
    TEST_ASSERT(dqueue_size(&dqueue) == 2);  //size == 2 (d2,d3)
    TEST_ASSERT(!dqueue_empty(&dqueue));     //dqueue dont must be empty

    dqueue_del(&d2.node, &dqueue);           //now d2 is not in list
    TEST_ASSERT(dqueue_size(&dqueue) == 1);  //size == 1 (d3)
    TEST_ASSERT(!dqueue_empty(&dqueue));     //dqueue dont must be empty

    dqueue_del(&d3.node, &dqueue);           //now d3 is not in list
    TEST_ASSERT(dqueue_size(&dqueue) == 0);  //size == 0 (list is empty)
    TEST_ASSERT(dqueue_empty(&dqueue));      //dqueue must be empty

    TEST_PASS(NULL);
}



ptest_func tests[] =
{
    test_dqueue_empty,
    test_dqueue_is_first,
    test_dqueue_is_last,
    test_dqueue_is_singular,
    test_dqueue_size,

};



MAIN_TESTS(tests)
