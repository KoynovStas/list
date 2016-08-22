#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



#include "unit_tests.h"
#include "dlist.h"





struct tmp_data
{
   struct dlist_head list;
   int               data;
};





int test_list_empty(struct test_info_t  *test_info)
{

    TEST_INIT;

    DECLARE_DLIST_HEAD(tmp_list);
    struct tmp_data d1;


    if(!dlist_empty(&tmp_list))             //list must be empty
        return TEST_BROKEN;


    dlist_push_front(&d1.list, &tmp_list);   //now d1 is first

    if(dlist_empty(&tmp_list))               //now list is NOT empty
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_list_is_first(struct test_info_t  *test_info)
{

    TEST_INIT;

    DECLARE_DLIST_HEAD(tmp_list);

    struct tmp_data d1, d2, d3;

    dlist_push_front(&d1.list, &tmp_list);   //now d1 is first

    if(!dlist_is_first(&d1.list, &tmp_list)) //d1 must be first
        return TEST_BROKEN;


    if(dlist_is_first(&d2.list, &tmp_list))  //d2 is not first (d2 out of the list.)
        return TEST_BROKEN;



    dlist_push_front(&d2.list, &tmp_list);    //now d2 is first

    if(!dlist_is_first(&d2.list, &tmp_list))  //d2 must be first
        return TEST_BROKEN;


    if(dlist_is_first(&d1.list, &tmp_list))   //d1 is not first (d1 is second)
        return TEST_BROKEN;


    if(dlist_is_first(&d3.list, &tmp_list))   //d3 is not first (d3 out of the list.)
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_list_is_last(struct test_info_t  *test_info)
{

    TEST_INIT;

    DECLARE_DLIST_HEAD(tmp_list);

    struct tmp_data d1, d2, d3;

    dlist_push_front(&d1.list, &tmp_list);   //now d1 is first

    if(!dlist_is_last(&d1.list, &tmp_list))  //d1 must be first and last (list is circular)
        return TEST_BROKEN;


    if(dlist_is_last(&d2.list, &tmp_list))   //d2 is not last (d2 out of the list.)
        return TEST_BROKEN;



    dlist_push_back(&d2.list, &tmp_list);    //now d2 is last

    if(!dlist_is_last(&d2.list, &tmp_list))  //d2 must be last
        return TEST_BROKEN;


    if(dlist_is_last(&d1.list, &tmp_list))   //now d1 dont must be last (d1 is first)
        return TEST_BROKEN;


    if(!dlist_is_first(&d1.list, &tmp_list)) //now d1 dont must be last (d1 is first)
        return TEST_BROKEN;


    if(dlist_is_last(&d1.list, &tmp_list))   //d1 is not last (d1 is first)
        return TEST_BROKEN;


    if(dlist_is_last(&d3.list, &tmp_list))   //d3 is not last (d3 out of the list.)
        return TEST_BROKEN;


    return TEST_PASSED;
}



ptest_func tests[] =
{
    test_list_empty,
    test_list_is_first,
    test_list_is_last,
};



int main(void)
{

    RUN_TESTS(tests);

    return 0;
}

