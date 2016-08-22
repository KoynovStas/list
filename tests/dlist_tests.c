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



int test_list_is_singular(struct test_info_t  *test_info)
{

    TEST_INIT;

    DECLARE_DLIST_HEAD(tmp_list);

    struct tmp_data d1, d2;



    if(dlist_is_singular(&tmp_list))         //list must be empty (not singular)
        return TEST_BROKEN;


    dlist_push_front(&d1.list, &tmp_list);   //now d1 is first

    if(!dlist_is_singular(&tmp_list))        //list must be singular (in list only d1)
        return TEST_BROKEN;



    dlist_push_back(&d2.list, &tmp_list);    //now d2 is last

    if(dlist_is_singular(&tmp_list))         //list dont must be singular (in list d1,d2)
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_list_size(struct test_info_t  *test_info)
{

    TEST_INIT;

    DECLARE_DLIST_HEAD(tmp_list);

    struct tmp_data d1, d2, d3;


    //add
    if(dlist_size(&tmp_list) != 0)           //size == 0 (list is empty)
        return TEST_BROKEN;


    dlist_push_front(&d1.list, &tmp_list);   //now d1 is first
    if(dlist_size(&tmp_list) != 1)           //size == 1 (d1)
        return TEST_BROKEN;



    dlist_push_back(&d2.list, &tmp_list);    //now d2 is last
    if(dlist_size(&tmp_list) != 2)           //size == 2 (d1,d2)
        return TEST_BROKEN;


    dlist_push_back(&d3.list, &tmp_list);    //now d2 is last
    if(dlist_size(&tmp_list) != 3)           //size == 3 (d1,d2, d3)
        return TEST_BROKEN;


    //delete
    dlist_del(&d1.list);                     //now d1 is not in list
    if(dlist_size(&tmp_list) != 2)           //size == 1 (d2,d3)
        return TEST_BROKEN;



    dlist_del(&d2.list);                     //now d2 is not in list
    if(dlist_size(&tmp_list) != 1)           //size == 2 (d3)
        return TEST_BROKEN;


    dlist_del(&d3.list);                     //now d3 is not in list
    if(dlist_size(&tmp_list) != 0)           //size == 0 (list is empty)
        return TEST_BROKEN;


    return TEST_PASSED;
}




int test_list_pop_front(struct test_info_t  *test_info)
{

    TEST_INIT;

    DECLARE_DLIST_HEAD(tmp_list);

    struct tmp_data d1, d2, d3;


    //add
    dlist_push_front(&d1.list, &tmp_list);   //now d1 is first
    dlist_push_front(&d2.list, &tmp_list);   //now d2 is first
    dlist_push_front(&d3.list, &tmp_list);   //now d3 is first
    if(dlist_size(&tmp_list) != 3)           //size == 3 (d3, d2, d1)
        return TEST_BROKEN;


    dlist_pop_front(&tmp_list);
    if(dlist_size(&tmp_list) != 2)           //size == 2 (d2, d1)
        return TEST_BROKEN;

    if(!dlist_empty(&d3.list))
        return TEST_BROKEN;

    if(!dlist_is_first(&d2.list, &tmp_list))  //(d2, d1)
        return TEST_BROKEN;


    dlist_pop_front(&tmp_list);
    if(dlist_size(&tmp_list) != 1)           //size == 1 (d1)
        return TEST_BROKEN;

    if(!dlist_empty(&d2.list))
        return TEST_BROKEN;

    if(!dlist_is_first(&d1.list, &tmp_list)) //(d1)
        return TEST_BROKEN;


    dlist_pop_front(&tmp_list);
    if(dlist_size(&tmp_list) != 0)           //size == 0 ()
        return TEST_BROKEN;

    if(!dlist_empty(&d1.list))
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_list_pop_back(struct test_info_t  *test_info)
{

    TEST_INIT;

    DECLARE_DLIST_HEAD(tmp_list);

    struct tmp_data d1, d2, d3;


    //add
    dlist_push_front(&d1.list, &tmp_list);   //now d1 is first
    dlist_push_front(&d2.list, &tmp_list);   //now d2 is first
    dlist_push_front(&d3.list, &tmp_list);   //now d3 is first
    if(dlist_size(&tmp_list) != 3)           //size == 3 (d3, d2, d1)
        return TEST_BROKEN;


    dlist_pop_back(&tmp_list);
    if(dlist_size(&tmp_list) != 2)           //size == 2 (d2, d1)
        return TEST_BROKEN;

    if(!dlist_empty(&d1.list))
        return TEST_BROKEN;

    if(!dlist_is_first(&d3.list, &tmp_list))  //(d3, d2)
        return TEST_BROKEN;


    dlist_pop_back(&tmp_list);
    if(dlist_size(&tmp_list) != 1)           //size == 1 (d3)
        return TEST_BROKEN;

    if(!dlist_empty(&d2.list))
        return TEST_BROKEN;

    if(!dlist_is_first(&d3.list, &tmp_list)) //(d3)
        return TEST_BROKEN;


    dlist_pop_back(&tmp_list);
    if(dlist_size(&tmp_list) != 0)           //size == 0 ()
        return TEST_BROKEN;

    if(!dlist_empty(&d3.list))
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_list_replace_init(struct test_info_t  *test_info)
{

    TEST_INIT;

    DECLARE_DLIST_HEAD(tmp_list);

    struct tmp_data d1, d2;


    //add
    dlist_push_front(&d1.list, &tmp_list);

    if(!dlist_is_last(&d1.list, &tmp_list))  //d1 in list
        return TEST_BROKEN;

    if(dlist_is_last(&d2.list, &tmp_list))   //d2 dont in list
        return TEST_BROKEN;


    dlist_replace_init(&d1.list, &d2.list);


    if(dlist_size(&tmp_list) != 1)           //size == 1 (d1)
        return TEST_BROKEN;

    if(dlist_is_last(&d1.list, &tmp_list))   //d1 dont in list
        return TEST_BROKEN;


    if(!dlist_is_last(&d2.list, &tmp_list))  //d1 dont in list
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_list_move_to_front(struct test_info_t  *test_info)
{

    TEST_INIT;

    DECLARE_DLIST_HEAD(tmp_list1);
    DECLARE_DLIST_HEAD(tmp_list2);

    struct tmp_data d1, d2;


    //add
    dlist_push_front(&d1.list, &tmp_list1);
    dlist_push_front(&d2.list, &tmp_list2);


    dlist_move_to_front(&d1.list, &tmp_list2);


    if(dlist_size(&tmp_list1) != 0)             //d1 moved to list2
        return TEST_BROKEN;


    if(dlist_size(&tmp_list2) != 2)             //d1 moved to list2
        return TEST_BROKEN;


    if(dlist_is_first(&d1.list, &tmp_list1))    //d1 in list2
        return TEST_BROKEN;


    if(dlist_is_first(&d2.list, &tmp_list2))    //d2 is not first
        return TEST_BROKEN;


    if(!dlist_is_first(&d1.list, &tmp_list2))   //d1 is first in list2
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_list_move_to_back(struct test_info_t  *test_info)
{

    TEST_INIT;

    DECLARE_DLIST_HEAD(tmp_list1);
    DECLARE_DLIST_HEAD(tmp_list2);

    struct tmp_data d1, d2;


    //add
    dlist_push_front(&d1.list, &tmp_list1);
    dlist_push_front(&d2.list, &tmp_list2);


    dlist_move_to_back(&d1.list, &tmp_list2);


    if(dlist_size(&tmp_list1) != 0)             //d1 moved to list2
        return TEST_BROKEN;


    if(dlist_size(&tmp_list2) != 2)             //d1 moved to list2
        return TEST_BROKEN;


    if(dlist_is_last(&d1.list, &tmp_list1))     //d1 last in list2
        return TEST_BROKEN;


    if(!dlist_is_first(&d2.list, &tmp_list2))   //d2 is first
        return TEST_BROKEN;


    if(!dlist_is_last(&d1.list, &tmp_list2))    //d1 is last in list2
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_list_rotate_left(struct test_info_t  *test_info)
{

    TEST_INIT;

    DECLARE_DLIST_HEAD(tmp_list);

    struct tmp_data d1, d2, d3, d4;


    //add
    dlist_push_front(&d4.list, &tmp_list);
    dlist_push_front(&d3.list, &tmp_list);
    dlist_push_front(&d2.list, &tmp_list);
    dlist_push_front(&d1.list, &tmp_list);      //[head] <-> [d1] <-> [d2] <-> [d3] <-> [d4]



    dlist_rotate_left(&tmp_list);               //[d1] <-> [head] <-> [d2] <-> [d3] <-> [d4]


    if(!dlist_is_last(&d1.list, &tmp_list))     //d1 last
        return TEST_BROKEN;

    if(!dlist_is_first(&d2.list, &tmp_list))    //d2 first
        return TEST_BROKEN;



    dlist_rotate_left(&tmp_list);               //[d1] <-> [d2] <-> [head] <-> [d3] <-> [d4]


    if(!dlist_is_last(&d2.list, &tmp_list))     //d2 last
        return TEST_BROKEN;

    if(!dlist_is_first(&d3.list, &tmp_list))    //d3 first
        return TEST_BROKEN;



    dlist_rotate_left(&tmp_list);               //[d1] <-> [d2] <-> [d3] <-> [head] <-> [d4]


    if(!dlist_is_last(&d3.list, &tmp_list))     //d3 last
        return TEST_BROKEN;

    if(!dlist_is_first(&d4.list, &tmp_list))    //d4 first
        return TEST_BROKEN;



    dlist_rotate_left(&tmp_list);               //[d2] <-> [d3] <-> [d4] <-> [head] <-> [d1]


    if(!dlist_is_last(&d4.list, &tmp_list))     //d4 last
        return TEST_BROKEN;

    if(!dlist_is_first(&d1.list, &tmp_list))    //d1 first
        return TEST_BROKEN;



    return TEST_PASSED;
}



int test_list_rotate_right(struct test_info_t  *test_info)
{

    TEST_INIT;

    DECLARE_DLIST_HEAD(tmp_list);

    struct tmp_data d1, d2, d3, d4;


    //add
    dlist_push_front(&d4.list, &tmp_list);
    dlist_push_front(&d3.list, &tmp_list);
    dlist_push_front(&d2.list, &tmp_list);
    dlist_push_front(&d1.list, &tmp_list);      //[head] <-> [d1] <-> [d2] <-> [d3] <-> [d4]



    dlist_rotate_right(&tmp_list);              //[d3] <-> [head] <-> [d4] <-> [d1] <-> [d2]


    if(!dlist_is_last(&d3.list, &tmp_list))     //d3 last
        return TEST_BROKEN;

    if(!dlist_is_first(&d4.list, &tmp_list))    //d4 first
        return TEST_BROKEN;



    dlist_rotate_right(&tmp_list);              //[d1] <-> [d2] <-> [head] <-> [d3] <-> [d4]


    if(!dlist_is_last(&d2.list, &tmp_list))     //d2 last
        return TEST_BROKEN;

    if(!dlist_is_first(&d3.list, &tmp_list))    //d3 first
        return TEST_BROKEN;



    dlist_rotate_right(&tmp_list);              //[d3] <-> [d4] <-> [d1] <-> [head] <-> [d2]


    if(!dlist_is_last(&d1.list, &tmp_list))     //d1 last
        return TEST_BROKEN;

    if(!dlist_is_first(&d2.list, &tmp_list))    //d2 first
        return TEST_BROKEN;



    dlist_rotate_right(&tmp_list);              //[d2] <-> [d3] <-> [d4] <-> [head] <-> [d1]


    if(!dlist_is_last(&d4.list, &tmp_list))     //d4 last
        return TEST_BROKEN;

    if(!dlist_is_first(&d1.list, &tmp_list))    //d1 first
        return TEST_BROKEN;



    return TEST_PASSED;
}



int test_list_splice_front(struct test_info_t  *test_info)
{

    TEST_INIT;

    DECLARE_DLIST_HEAD(list1);
    DECLARE_DLIST_HEAD(list2);

    const size_t COUNT_NODES = 100;
    size_t i;
    struct tmp_data  nodes[COUNT_NODES];
    struct tmp_data  *it;


    for(i=0; i < COUNT_NODES; i++)
    {
        nodes[i].data = i;
        dlist_push_back(&nodes[i].list, &list1);
    }

    dlist_splice_front(&list1, &list2);


    if( dlist_size(&list1) != 0 )
        return TEST_BROKEN;

    if( dlist_size(&list2) != COUNT_NODES )
        return TEST_BROKEN;


    i=0;
    dlist_data_citer(it, &list2, struct tmp_data, list)
    {
        if(it->data != i)
            return TEST_BROKEN;

        i++;
    }

    //is front
    if( list2.next != &nodes[0].list )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_list_splice_back(struct test_info_t  *test_info)
{

    TEST_INIT;

    DECLARE_DLIST_HEAD(list1);
    DECLARE_DLIST_HEAD(list2);

    const size_t COUNT_NODES = 100;
    size_t i;
    struct tmp_data  nodes[COUNT_NODES];
    struct tmp_data  *it;


    for(i=0; i < COUNT_NODES; i++)
    {
        nodes[i].data = i;
        dlist_push_back(&nodes[i].list, &list1);
    }

    dlist_splice_back(&list1, &list2);


    if( dlist_size(&list1) != 0 )
        return TEST_BROKEN;

    if( dlist_size(&list2) != COUNT_NODES )
        return TEST_BROKEN;


    i=0;
    dlist_data_citer(it, &list2, struct tmp_data, list)
    {
        if(it->data != i)
            return TEST_BROKEN;

        i++;
    }

    //is back
    if( list2.next != &nodes[0].list )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//---------------- Get Data from node ----------------



int test_list_data(struct test_info_t  *test_info)
{

    TEST_INIT;

    struct tmp_data d1;

    if( dlist_data(&d1.list, struct tmp_data, list) != &d1 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_list_data_or_null(struct test_info_t  *test_info)
{

    TEST_INIT;

    DECLARE_DLIST_HEAD(tmp_list);

    struct tmp_data d1;

    dlist_init_head(&d1.list);


    if( dlist_data_or_null(&d1.list, struct tmp_data, list) != NULL )
        return TEST_BROKEN;


    dlist_push_front(&d1.list, &tmp_list);


    if( dlist_data_or_null(&d1.list, struct tmp_data, list) != &d1 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_list_first_data(struct test_info_t  *test_info)
{

    TEST_INIT;

    DECLARE_DLIST_HEAD(tmp_list);

    struct tmp_data d1, d2;


    dlist_push_front(&d1.list, &tmp_list);


    if( dlist_first_data(&tmp_list, struct tmp_data, list) != &d1 )
        return TEST_BROKEN;


    dlist_push_front(&d2.list, &tmp_list);


    if( dlist_first_data(&tmp_list, struct tmp_data, list) != &d2 )
        return TEST_BROKEN;


    if( dlist_first_data(&tmp_list, struct tmp_data, list) == &d1 ) //now d2 first
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_list_last_data(struct test_info_t  *test_info)
{

    TEST_INIT;

    DECLARE_DLIST_HEAD(tmp_list);

    struct tmp_data d1, d2;


    dlist_push_back(&d1.list, &tmp_list);


    if( dlist_last_data(&tmp_list, struct tmp_data, list) != &d1 )
        return TEST_BROKEN;


    dlist_push_back(&d2.list, &tmp_list);


    if( dlist_last_data(&tmp_list, struct tmp_data, list) != &d2 )
        return TEST_BROKEN;


    if( dlist_last_data(&tmp_list, struct tmp_data, list) == &d1 ) //now d2 last
        return TEST_BROKEN;


    return TEST_PASSED;
}



//---------------- Iterator ----------------



int test_list_citer(struct test_info_t  *test_info)
{

    TEST_INIT;

    DECLARE_DLIST_HEAD(tmp_list);

    const size_t COUNT_NODES = 100;
    size_t i;
    struct tmp_data nodes[COUNT_NODES];
    struct dlist_head *it;


    for(i=0; i < COUNT_NODES; i++)
        dlist_push_back(&nodes[i].list, &tmp_list);


    i=0;
    dlist_citer(it, &tmp_list)
    {
        if( it != &nodes[i].list )  //test nodes
            return TEST_BROKEN;
        i++;
    }


    return TEST_PASSED;
}



int test_list_criter(struct test_info_t  *test_info)
{

    TEST_INIT;

    DECLARE_DLIST_HEAD(tmp_list);

    const size_t COUNT_NODES = 100;
    size_t i;
    struct tmp_data nodes[COUNT_NODES];
    struct dlist_head *it;


    for(i=0; i < COUNT_NODES; i++)
        dlist_push_front(&nodes[i].list, &tmp_list);


    i=0;
    dlist_criter(it, &tmp_list)
    {
        if( it != &nodes[i].list )  //test nodes
            return TEST_BROKEN;
        i++;
    }


    return TEST_PASSED;
}




ptest_func tests[] =
{
    test_list_empty,
    test_list_is_first,
    test_list_is_last,
    test_list_is_singular,
    test_list_size,
    test_list_pop_front,
    test_list_pop_back,
    test_list_replace_init,
    test_list_move_to_front,
    test_list_move_to_back,
    test_list_rotate_left,
    test_list_rotate_right,
    test_list_splice_front,
    test_list_splice_back,

    //Get Data from node
    test_list_data,
    test_list_data_or_null,
    test_list_first_data,
    test_list_last_data,

    //Iterator
    test_list_citer,
    test_list_criter,
};



int main(void)
{

    RUN_TESTS(tests);

    return 0;
}

