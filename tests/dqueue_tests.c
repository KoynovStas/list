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



TEST(test_dqueue_del)
{
    DECLARE_DQUEUE(dqueue);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);
    DECLARE_TMP_DATA(d3);


    //add
    TEST_ASSERT(dqueue_size(&dqueue) == 0);  //size == 0 (list is empty)

    dqueue_push_front(&d1.node, &dqueue);    //now d1 is first
    dqueue_push_back(&d2.node, &dqueue);     //now d2 is last
    dqueue_push_back(&d3.node, &dqueue);     //now d3 is last
    TEST_ASSERT(dqueue_size(&dqueue) == 3);  //size == 3 (d1,d2, d3)


    //delete
    TEST_ASSERT(!dqueue_empty(&dqueue));     //d1 in list
    dqueue_del(&d1.node, &dqueue);           //now d1 is not in list
    TEST_ASSERT(dqueue_size(&dqueue) == 2);  //size == 2 (d2,d3)
    TEST_ASSERT(dlist_empty(&d1.node));      //d1 is not in list


    TEST_ASSERT(!dqueue_empty(&dqueue));      //d2 in list
    dqueue_del(&d2.node, &dqueue);            //now d2 is not in list
    TEST_ASSERT(dqueue_size(&dqueue) == 1);   //size == 1 (d3)
    TEST_ASSERT(dlist_empty(&d2.node));       //d2 is not in list

    TEST_ASSERT(!dqueue_empty(&dqueue));      //d3 in list
    dqueue_del(&d3.node, &dqueue);            //now d3 is not in list
    TEST_ASSERT(dqueue_size(&dqueue) == 0);   //size == 0 (list is empty)
    TEST_ASSERT(dqueue_empty(&dqueue));
    TEST_ASSERT(dlist_empty(&d3.node));       //d3 is not in list

    TEST_PASS(NULL);
}



TEST(test_dqueue_pop_front)
{
    DECLARE_DQUEUE(dqueue);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);
    DECLARE_TMP_DATA(d3);


    //add
    dqueue_push_front(&d1.node, &dqueue);    //now d1 is first
    dqueue_push_front(&d2.node, &dqueue);    //now d2 is first
    dqueue_push_front(&d3.node, &dqueue);    //now d3 is first
    TEST_ASSERT(dqueue_size(&dqueue) == 3);  //size == 3 (d3, d2, d1)


    dqueue_pop_front(&dqueue);
    TEST_ASSERT(dqueue_size(&dqueue) == 2);           //size == 2 (d2, d1)
    TEST_ASSERT(dlist_empty(&d3.node));
    TEST_ASSERT(dqueue_is_first(&d2.node, &dqueue));  //(d2, d1)


    dqueue_pop_front(&dqueue);
    TEST_ASSERT(dqueue_size(&dqueue) == 1);          //size == 1 (d1)
    TEST_ASSERT(dlist_empty(&d2.node));
    TEST_ASSERT(dqueue_is_first(&d1.node, &dqueue)); //(d1)


    dqueue_pop_front(&dqueue);
    TEST_ASSERT(dqueue_size(&dqueue) == 0);           //size == 0 ()
    TEST_ASSERT(dqueue_empty(&dqueue));
    TEST_ASSERT(dlist_empty(&d1.node));


    //dqueue empty
    dqueue_pop_front(&dqueue);
    TEST_ASSERT(dqueue_size(&dqueue) == 0);           //size == 0 ()
    TEST_ASSERT(dqueue_empty(&dqueue));


    TEST_PASS(NULL);
}



TEST(test_dqueue_pop_back)
{
    DECLARE_DQUEUE(dqueue);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);
    DECLARE_TMP_DATA(d3);


    //add
    dqueue_push_front(&d1.node, &dqueue);   //now d1 is first
    dqueue_push_front(&d2.node, &dqueue);   //now d2 is first
    dqueue_push_front(&d3.node, &dqueue);   //now d3 is first
    TEST_ASSERT(dqueue_size(&dqueue) == 3); //size == 3 (d3, d2, d1)


    dqueue_pop_back(&dqueue);
    TEST_ASSERT(dqueue_size(&dqueue) == 2);           //size == 2 (d2, d1)
    TEST_ASSERT(dlist_empty(&d1.node));
    TEST_ASSERT(dqueue_is_first(&d3.node, &dqueue));  //(d3, d2)


    dqueue_pop_back(&dqueue);
    TEST_ASSERT(dqueue_size(&dqueue) == 1);          //size == 1 (d3)
    TEST_ASSERT(dlist_empty(&d2.node));
    TEST_ASSERT(dqueue_is_first(&d3.node, &dqueue)); //(d3)


    dqueue_pop_back(&dqueue);
    TEST_ASSERT(dqueue_size(&dqueue) == 0);           //size == 0 ()
    TEST_ASSERT(dqueue_empty(&dqueue));
    TEST_ASSERT(dlist_empty(&d3.node));


    //list empty
    dqueue_pop_back(&dqueue);
    TEST_ASSERT(dqueue_size(&dqueue) == 0);           //size == 0 ()
    TEST_ASSERT(dqueue_empty(&dqueue));


    TEST_PASS(NULL);
}



TEST(test_dqueue_replace_init)
{
    DECLARE_DQUEUE(dqueue);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);


    //add
    dqueue_push_front(&d1.node, &dqueue);

    TEST_ASSERT(dqueue_is_last(&d1.node, &dqueue));    //d1 in list
    TEST_ASSERT(dqueue_is_first(&d1.node, &dqueue));   //d1 in list
    TEST_ASSERT(!dqueue_is_last(&d2.node, &dqueue));   //d2 dont in list


    dqueue_replace_init(&d1.node, &d2.node);


    TEST_ASSERT(dlist_empty(&d1.node));               //d1 must be clean

    TEST_ASSERT(dqueue_size(&dqueue) == 1);           //size == 1 (d1)
    TEST_ASSERT(!dqueue_is_last(&d1.node, &dqueue));  //d1 dont in list
    TEST_ASSERT(dqueue_is_last(&d2.node, &dqueue));


    TEST_PASS(NULL);
}



TEST(test_dqueue_move_to_front)
{
    DECLARE_DQUEUE(dqueue1);
    DECLARE_DQUEUE(dqueue2);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);


    //add
    dqueue_push_front(&d1.node, &dqueue1);
    dqueue_push_front(&d2.node, &dqueue1);


    dqueue_move_to_front(&d1.node, &dqueue1);


    TEST_ASSERT(dqueue_size(&dqueue1) == 2);
    TEST_ASSERT(dqueue_is_first(&d1.node, &dqueue1));
    TEST_ASSERT(!dqueue_is_first(&d2.node, &dqueue1));   //d2 is not first
    TEST_ASSERT(dqueue_is_last(&d2.node, &dqueue1));


    TEST_PASS(NULL);
}



ptest_func tests[] =
{
    test_dqueue_empty,
    test_dqueue_is_first,
    test_dqueue_is_last,
    test_dqueue_is_singular,
    test_dqueue_size,
    test_dqueue_del,
    test_dqueue_pop_front,
    test_dqueue_pop_back,
    test_dqueue_replace_init,
    test_dqueue_move_to_front,

};



MAIN_TESTS(tests)
