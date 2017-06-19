#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



#include "stest.h"
#include "list.h"





struct tmp_data
{
   struct list_head list;
   int              data;
};



#define DECLARE_TMP_DATA(name) \
    struct tmp_data name = { {NULL}, 0}





TEST(test_list_empty)
{
    DECLARE_LIST_HEAD(tmp_list);
    DECLARE_TMP_DATA(d1);


    TEST_ASSERT(list_empty(&tmp_list));     //list must be empty


    list_push_front(&d1.list, &tmp_list);   //now d1 is first

    TEST_ASSERT(!list_empty(&tmp_list));    //now list is NOT empty


    TEST_PASS(NULL);
}



TEST(test_list_is_first)
{
    DECLARE_LIST_HEAD(tmp_list);
    DECLARE_LIST_HEAD(tmp_list2);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);
    DECLARE_TMP_DATA(d3);


    list_push_front(&d1.list, &tmp_list);              //now d1 is first

    TEST_ASSERT(list_is_first(&d1.list, &tmp_list));   //d1 must be first


    list_push_front(&d2.list, &tmp_list);              //now d2 is first

    TEST_ASSERT(list_is_first(&d2.list, &tmp_list));   //d2 must be first
    TEST_ASSERT(!list_is_first(&d1.list, &tmp_list));  //d1 is not first (d1 is second)


    list_push_front(&d3.list, &tmp_list2);             //now d3 is first
    TEST_ASSERT(!list_is_first(&d3.list, &tmp_list));  //d3 is not first (d3 out of the list.)
    TEST_ASSERT(list_is_first(&d3.list, &tmp_list2));  //d3 is first in list2


    TEST_PASS(NULL);
}



TEST(test_list_is_last)
{
    DECLARE_LIST_HEAD(tmp_list);
    DECLARE_LIST_HEAD(tmp_list2);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);
    DECLARE_TMP_DATA(d3);


    list_push_front(&d1.list, &tmp_list);              //now d1 is first

    TEST_ASSERT(list_is_last(&d1.list, &tmp_list));    //d1 must be first and last (list is circular)


    list_push_back(&d2.list, &tmp_list);               //now d2 is last

    TEST_ASSERT(list_is_last(&d2.list, &tmp_list));    //d2 must be last
    TEST_ASSERT(!list_is_last(&d1.list, &tmp_list));   //now d1 dont must be last (d1 is first)


    list_push_front(&d3.list, &tmp_list2);             //now d3 is first

    TEST_ASSERT(!list_is_last(&d3.list, &tmp_list));  //d3 is not first (d3 out of the list.)
    TEST_ASSERT(list_is_last(&d3.list, &tmp_list2));  //d3 is first and last in list2


    TEST_PASS(NULL);
}



TEST(test_list_is_singular)
{
    DECLARE_LIST_HEAD(tmp_list);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);


    TEST_ASSERT(!list_is_singular(&tmp_list));  //list must be empty (not singular)

    list_push_front(&d1.list, &tmp_list);       //now d1 is first
    TEST_ASSERT(list_is_singular(&tmp_list));   //list must be singular (in list only d1)


    list_push_back(&d2.list, &tmp_list);        //now d2 is last
    TEST_ASSERT(!list_is_singular(&tmp_list));  //list dont must be singular (in list d1,d2)


    TEST_PASS(NULL);
}



TEST(test_list_size)
{
    DECLARE_LIST_HEAD(tmp_list);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);
    DECLARE_TMP_DATA(d3);


    //add
    TEST_ASSERT(list_size(&tmp_list) == 0);  //size == 0 (list is empty)

    list_push_front(&d1.list, &tmp_list);    //now d1 is first
    TEST_ASSERT(list_size(&tmp_list) == 1);  //size == 1 (d1)
    TEST_ASSERT(!list_empty(&d1.list));      //list dont must be empty

    list_push_back(&d2.list, &tmp_list);     //now d2 is last
    TEST_ASSERT(list_size(&tmp_list) == 2);  //size == 2 (d1,d2)
    TEST_ASSERT(!list_empty(&d2.list));      //list dont must be empty

    list_push_back(&d3.list, &tmp_list);     //now d3 is last
    TEST_ASSERT(list_size(&tmp_list) == 3);  //size == 3 (d1,d2, d3)
    TEST_ASSERT(!list_empty(&d3.list));      //list dont must be empty


    //delete
    list_del(&d1.list);                     //now d1 is not in list
    TEST_ASSERT(list_size(&tmp_list) == 2); //size == 2 (d2,d3)
    TEST_ASSERT(list_empty(&d1.list));      //list must be empty

    list_del(&d2.list);                     //now d2 is not in list
    TEST_ASSERT(list_size(&tmp_list) == 1); //size == 1 (d3)
    TEST_ASSERT(list_empty(&d2.list));      //list must be empty

    list_del(&d3.list);                     //now d3 is not in list
    TEST_ASSERT(list_size(&tmp_list) == 0); //size == 0 (list is empty)
    TEST_ASSERT(list_empty(&d3.list));      //list must be empty

    TEST_PASS(NULL);
}



TEST(test_list_del)
{
    DECLARE_LIST_HEAD(tmp_list);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);
    DECLARE_TMP_DATA(d3);


    //add
    TEST_ASSERT(list_size(&tmp_list) == 0);  //size == 0 (list is empty)

    list_push_front(&d1.list, &tmp_list);    //now d1 is first
    list_push_back(&d2.list, &tmp_list);     //now d2 is last
    list_push_back(&d3.list, &tmp_list);     //now d3 is last
    TEST_ASSERT(list_size(&tmp_list) == 3);  //size == 3 (d1,d2, d3)


    //delete
    TEST_ASSERT(!list_empty(&d1.list));     //d1 in list
    list_del(&d1.list);                     //now d1 is not in list
    TEST_ASSERT(list_size(&tmp_list) == 2); //size == 2 (d2,d3)
    TEST_ASSERT(list_empty(&d1.list));      //d1 is not in list


    TEST_ASSERT(!list_empty(&d2.list));     //d2 in list
    list_del(&d2.list);                     //now d2 is not in list
    TEST_ASSERT(list_size(&tmp_list) == 1); //size == 1 (d3)
    TEST_ASSERT(list_empty(&d2.list));      //d2 is not in list

    TEST_ASSERT(!list_empty(&d3.list));     //d3 in list
    list_del(&d3.list);                     //now d3 is not in list
    TEST_ASSERT(list_size(&tmp_list) == 0); //size == 0 (list is empty)
    TEST_ASSERT(list_empty(&d3.list));      //d3 is not in list

    TEST_PASS(NULL);
}



TEST(test_list_pop_front)
{
    DECLARE_LIST_HEAD(tmp_list);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);
    DECLARE_TMP_DATA(d3);


    //add
    list_push_front(&d1.list, &tmp_list);   //now d1 is first
    list_push_front(&d2.list, &tmp_list);   //now d2 is first
    list_push_front(&d3.list, &tmp_list);   //now d3 is first
    TEST_ASSERT(list_size(&tmp_list) == 3); //size == 3 (d3, d2, d1)


    list_pop_front(&tmp_list);
    TEST_ASSERT(list_size(&tmp_list) == 2);           //size == 2 (d2, d1)
    TEST_ASSERT(list_empty(&d3.list));
    TEST_ASSERT(list_is_first(&d2.list, &tmp_list));  //(d2, d1)


    list_pop_front(&tmp_list);
    TEST_ASSERT(list_size(&tmp_list) == 1);          //size == 1 (d1)
    TEST_ASSERT(list_empty(&d2.list));
    TEST_ASSERT(list_is_first(&d1.list, &tmp_list)); //(d1)


    list_pop_front(&tmp_list);
    TEST_ASSERT(list_size(&tmp_list) == 0);          //size == 0 ()
    TEST_ASSERT(list_empty(&d1.list));


    TEST_PASS(NULL);
}



TEST(test_list_pop_back)
{
    DECLARE_LIST_HEAD(tmp_list);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);
    DECLARE_TMP_DATA(d3);


    //add
    list_push_front(&d1.list, &tmp_list);   //now d1 is first
    list_push_front(&d2.list, &tmp_list);   //now d2 is first
    list_push_front(&d3.list, &tmp_list);   //now d3 is first
    TEST_ASSERT(list_size(&tmp_list) == 3); //size == 3 (d3, d2, d1)


    list_pop_back(&tmp_list);
    TEST_ASSERT(list_size(&tmp_list) == 2);           //size == 2 (d2, d1)
    TEST_ASSERT(list_empty(&d1.list));
    TEST_ASSERT(list_is_first(&d3.list, &tmp_list));  //(d3, d2)


    list_pop_back(&tmp_list);
    TEST_ASSERT(list_size(&tmp_list) == 1);           //size == 1 (d3)
    TEST_ASSERT(list_empty(&d2.list));
    TEST_ASSERT(list_is_first(&d3.list, &tmp_list));  //(d3)


    list_pop_back(&tmp_list);
    TEST_ASSERT(list_size(&tmp_list) == 0);           //size == 0 ()
    TEST_ASSERT(list_empty(&d3.list));


    TEST_PASS(NULL);
}



TEST(test_list_replace_init)
{
    DECLARE_LIST_HEAD(tmp_list);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);


    //add
    list_push_front(&d1.list, &tmp_list);
    TEST_ASSERT(list_is_last(&d1.list, &tmp_list));  //d1 in list
    TEST_ASSERT(!list_is_last(&d2.list, &tmp_list)); //d2 dont in list


    list_replace_init(&d1.list, &d2.list);
    TEST_ASSERT(list_size(&tmp_list) == 1);           //size == 1 (d1)
    TEST_ASSERT(!list_is_last(&d1.list, &tmp_list));  //d1 dont in list
    TEST_ASSERT(list_is_last(&d2.list, &tmp_list));


    TEST_PASS(NULL);
}



TEST(test_list_move_to_front)
{
    DECLARE_LIST_HEAD(tmp_list1);
    DECLARE_LIST_HEAD(tmp_list2);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);


    //add
    list_push_front(&d1.list, &tmp_list1);
    list_push_front(&d2.list, &tmp_list2);


    list_move_to_front(&d1.list, &tmp_list2);

    TEST_ASSERT(list_size(&tmp_list1) == 0);             //d1 moved to list2
    TEST_ASSERT(list_size(&tmp_list2) == 2);             //d1 moved to list2
    TEST_ASSERT(!list_is_first(&d1.list, &tmp_list1));   //d1 in list2
    TEST_ASSERT(!list_is_first(&d2.list, &tmp_list2));   //d2 is not first
    TEST_ASSERT(list_is_first(&d1.list, &tmp_list2));    //d1 is first in list2


    TEST_PASS(NULL);
}



TEST(test_list_move_to_back)
{
    DECLARE_LIST_HEAD(tmp_list1);
    DECLARE_LIST_HEAD(tmp_list2);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);


    //add
    list_push_front(&d1.list, &tmp_list1);
    list_push_front(&d2.list, &tmp_list2);


    list_move_to_back(&d1.list, &tmp_list2);

    TEST_ASSERT(list_size(&tmp_list1) == 0);            //d1 moved to list2
    TEST_ASSERT(list_size(&tmp_list2) == 2);            //d1 moved to list2
    TEST_ASSERT(!list_is_last(&d1.list, &tmp_list1));   //d1 last in list2
    TEST_ASSERT(list_is_first(&d2.list, &tmp_list2));   //d2 is first
    TEST_ASSERT(list_is_last(&d1.list, &tmp_list2));    //d1 is last in list2

    TEST_PASS(NULL);
}



TEST(test_list_rotate_left)
{
    DECLARE_LIST_HEAD(tmp_list);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);
    DECLARE_TMP_DATA(d3);
    DECLARE_TMP_DATA(d4);


    //add
    list_push_front(&d4.list, &tmp_list);
    list_push_front(&d3.list, &tmp_list);
    list_push_front(&d2.list, &tmp_list);
    list_push_front(&d1.list, &tmp_list);              //[head] <-> [d1] <-> [d2] <-> [d3] <-> [d4]


    list_rotate_left(&tmp_list);                       //[d1] <-> [head] <-> [d2] <-> [d3] <-> [d4]

    TEST_ASSERT(list_is_last(&d1.list, &tmp_list));    //d1 last
    TEST_ASSERT(list_is_first(&d2.list, &tmp_list));   //d2 first


    list_rotate_left(&tmp_list);                       //[d1] <-> [d2] <-> [head] <-> [d3] <-> [d4]

    TEST_ASSERT(list_is_last(&d2.list, &tmp_list));    //d2 last
    TEST_ASSERT(list_is_first(&d3.list, &tmp_list));   //d3 first


    list_rotate_left(&tmp_list);                       //[d1] <-> [d2] <-> [d3] <-> [head] <-> [d4]

    TEST_ASSERT(list_is_last(&d3.list, &tmp_list));    //d3 last
    TEST_ASSERT(list_is_first(&d4.list, &tmp_list));   //d4 first


    list_rotate_left(&tmp_list);                       //[d2] <-> [d3] <-> [d4] <-> [head] <-> [d1]

    TEST_ASSERT(list_is_last(&d4.list, &tmp_list));    //d4 last
    TEST_ASSERT(list_is_first(&d1.list, &tmp_list));   //d1 first


    TEST_PASS(NULL);
}



TEST(test_list_rotate_right)
{
    DECLARE_LIST_HEAD(tmp_list);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);
    DECLARE_TMP_DATA(d3);
    DECLARE_TMP_DATA(d4);


    //add
    list_push_front(&d4.list, &tmp_list);
    list_push_front(&d3.list, &tmp_list);
    list_push_front(&d2.list, &tmp_list);
    list_push_front(&d1.list, &tmp_list);              //[head] <-> [d1] <-> [d2] <-> [d3] <-> [d4]


    list_rotate_right(&tmp_list);                      //[d3] <-> [head] <-> [d4] <-> [d1] <-> [d2]

    TEST_ASSERT(list_is_last(&d3.list, &tmp_list));    //d3 last
    TEST_ASSERT(list_is_first(&d4.list, &tmp_list));   //d4 first


    list_rotate_right(&tmp_list);                      //[d1] <-> [d2] <-> [head] <-> [d3] <-> [d4]

    TEST_ASSERT(list_is_last(&d2.list, &tmp_list));    //d2 last
    TEST_ASSERT(list_is_first(&d3.list, &tmp_list));   //d3 first


    list_rotate_right(&tmp_list);                      //[d3] <-> [d4] <-> [d1] <-> [head] <-> [d2]

    TEST_ASSERT(list_is_last(&d1.list, &tmp_list));    //d1 last
    TEST_ASSERT(list_is_first(&d2.list, &tmp_list));   //d2 first


    list_rotate_right(&tmp_list);                      //[d2] <-> [d3] <-> [d4] <-> [head] <-> [d1]

    TEST_ASSERT(list_is_last(&d4.list, &tmp_list));    //d4 last
    TEST_ASSERT(list_is_first(&d1.list, &tmp_list));   //d1 first


    TEST_PASS(NULL);
}



TEST(test_list_splice_front)
{
    DECLARE_LIST_HEAD(list1);
    DECLARE_LIST_HEAD(list2);

    const int COUNT_NODES = 100;
    int i;
    struct tmp_data  nodes[COUNT_NODES];
    struct tmp_data  *it;


    for(i=0; i < COUNT_NODES; i++)
    {
        nodes[i].data = i;
        list_push_back(&nodes[i].list, &list1);
    }

    list_splice_front(&list1, &list2);


    TEST_ASSERT( list_size(&list1) == 0 );
    TEST_ASSERT( list_size(&list2) == COUNT_NODES );


    i=0;
    list_data_citer(it, &list2, struct tmp_data, list)
    {
        TEST_ASSERT(it->data == i);
        i++;
    }

    //is front
    TEST_ASSERT( list2.next == &nodes[0].list );


    TEST_PASS(NULL);
}



TEST(test_list_splice_back)
{
    DECLARE_LIST_HEAD(list1);
    DECLARE_LIST_HEAD(list2);

    const int COUNT_NODES = 100;
    int i;
    struct tmp_data  nodes[COUNT_NODES];
    struct tmp_data  *it;


    for(i=0; i < COUNT_NODES; i++)
    {
        nodes[i].data = i;
        list_push_back(&nodes[i].list, &list1);
    }

    list_splice_back(&list1, &list2);


    TEST_ASSERT( list_size(&list1) == 0 );
    TEST_ASSERT( list_size(&list2) == COUNT_NODES );


    i=0;
    list_data_citer(it, &list2, struct tmp_data, list)
    {
        TEST_ASSERT(it->data == i);
        i++;
    }

    //is back
    TEST_ASSERT( list2.next == &nodes[0].list );


    TEST_PASS(NULL);
}



//---------------- Get Data from node ----------------



TEST(test_list_data)
{
    DECLARE_TMP_DATA(d1);

    TEST_ASSERT(list_data(&d1.list, struct tmp_data, list) == &d1 );

    TEST_PASS(NULL);
}



TEST(test_list_data_or_null)
{
    DECLARE_LIST_HEAD(tmp_list);

    DECLARE_TMP_DATA(d1);

    list_init_head(&d1.list);
    TEST_ASSERT(list_data_or_null(&d1.list, struct tmp_data, list) == NULL );


    list_push_front(&d1.list, &tmp_list);
    TEST_ASSERT(list_data_or_null(&d1.list, struct tmp_data, list) == &d1 );


    TEST_PASS(NULL);
}



TEST(test_list_first_data)
{
    DECLARE_LIST_HEAD(tmp_list);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);


    list_push_front(&d1.list, &tmp_list);

    TEST_ASSERT(list_first_data(&tmp_list, struct tmp_data, list) == &d1 );


    list_push_front(&d2.list, &tmp_list);

    TEST_ASSERT(list_first_data(&tmp_list, struct tmp_data, list) == &d2 );
    TEST_ASSERT(list_first_data(&tmp_list, struct tmp_data, list) != &d1 ); //now d2 first


    TEST_PASS(NULL);
}



TEST(test_list_last_data)
{
    DECLARE_LIST_HEAD(tmp_list);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);


    list_push_back(&d1.list, &tmp_list);

    TEST_ASSERT(list_last_data(&tmp_list, struct tmp_data, list) == &d1 );


    list_push_back(&d2.list, &tmp_list);

    TEST_ASSERT(list_last_data(&tmp_list, struct tmp_data, list) == &d2 );
    TEST_ASSERT(list_last_data(&tmp_list, struct tmp_data, list) != &d1 ); //now d2 last


    TEST_PASS(NULL);
}



//---------------- Iterator ----------------



TEST(test_list_citer)
{
    DECLARE_LIST_HEAD(tmp_list);

    const int COUNT_NODES = 100;
    int i;
    struct tmp_data nodes[COUNT_NODES];
    struct list_head *it;


    for(i=0; i < COUNT_NODES; i++)
        list_push_back(&nodes[i].list, &tmp_list);


    i=0;
    list_citer(it, &tmp_list)
    {
        TEST_ASSERT( it == &nodes[i].list );  //test nodes
        i++;
    }


    TEST_PASS(NULL);
}



TEST(test_list_iter)
{
    DECLARE_LIST_HEAD(tmp_list);

    const int COUNT_NODES = 100;
    int i;
    struct tmp_data nodes[COUNT_NODES];
    struct list_head *it;
    struct list_head *tmp_it;


    for(i=0; i < COUNT_NODES; i++)
        list_push_back(&nodes[i].list, &tmp_list);


    TEST_ASSERT(list_size(&tmp_list) == COUNT_NODES );


    i=0;
    list_iter(it, tmp_it, &tmp_list)   //dont change
    {
        TEST_ASSERT( it == &nodes[i].list );     //test nodes
        i++;
    }


    i=0;
    list_iter(it, tmp_it, &tmp_list)   //+ change (del)
    {
        if(i & 1)
            list_del(it);
        i++;
    }

    TEST_ASSERT( list_size(&tmp_list) == (COUNT_NODES/2) );

    TEST_PASS(NULL);
}



TEST(test_list_data_citer)
{
    DECLARE_LIST_HEAD(tmp_list);

    const int COUNT_NODES = 100;
    int i;
    struct tmp_data nodes[COUNT_NODES];
    struct tmp_data *it;



    for(i=0; i < COUNT_NODES; i++)
    {
        nodes[i].data = i;
        list_push_back(&nodes[i].list, &tmp_list);
    }


    i=0;
    list_data_citer(it, &tmp_list, struct tmp_data, list)
    {
        TEST_ASSERT( it->data == nodes[i].data );     //test nodes
        i++;
    }


    TEST_PASS(NULL);
}



TEST(test_list_data_iter)
{
    DECLARE_LIST_HEAD(tmp_list);

    const int COUNT_NODES = 100;
    int i;
    struct tmp_data  nodes[COUNT_NODES];
    struct tmp_data  *it;
    struct list_head *tmp_it;


    for(i=0; i < COUNT_NODES; i++)
    {
        nodes[i].data = i;
        list_push_back(&nodes[i].list, &tmp_list);
    }


    i=0;
    list_data_iter(it, &tmp_list, tmp_it, struct tmp_data, list)   //+ change (del)
    {
        if(i & 1)
            list_del(&it->list);
        i++;
    }


    TEST_ASSERT( list_size(&tmp_list) == (COUNT_NODES/2) );


    i=0;
    list_data_citer(it, &tmp_list, struct tmp_data, list)
    {
        TEST_ASSERT(it->data == i);
        i+= 2;
    }


    TEST_PASS(NULL);
}



//---------------- Algorithm ----------------



void node_inc(struct list_head *it)
{
    struct tmp_data *data = list_data(it, struct tmp_data, list);

    data->data++;
}



TEST(test_list_for_each)
{
    DECLARE_LIST_HEAD(tmp_list);

    const int COUNT_NODES = 100;
    int i;
    struct tmp_data  nodes[COUNT_NODES];
    struct tmp_data  *it_data;


    for(i=0; i < COUNT_NODES; i++)
    {
        nodes[i].data = i;
        list_push_back(&nodes[i].list, &tmp_list);
    }


    list_for_each(tmp_list.next, &tmp_list, node_inc);


    i=0;
    list_data_citer(it_data, &tmp_list, struct tmp_data, list)
    {
        TEST_ASSERT( it_data->data == (i+1) );
        i++;
    }


    TEST_PASS(NULL);
}



int comp_less(const struct list_head *n1,const struct list_head *n2)
{
    struct tmp_data *d1 = list_data(n1, struct tmp_data, list);
    struct tmp_data *d2 = list_data(n2, struct tmp_data, list);

    return d1->data < d2->data;
}



TEST(test_list_min)
{
    DECLARE_LIST_HEAD(tmp_list);

    const int COUNT_NODES = 100;
    int i;
    struct tmp_data  nodes[COUNT_NODES];
    struct tmp_data  *tmp_data;
    struct list_head *min;


    min = list_min(tmp_list.next, &tmp_list, comp_less);
    TEST_ASSERT(min == &tmp_list); //min == end iterator (list empty)


    for(i=0; i < COUNT_NODES; i++)
    {
        nodes[i].data = i;
        list_push_back(&nodes[i].list, &tmp_list);
    }


    min = list_min(tmp_list.next, &tmp_list, comp_less);
    tmp_data = list_data(min, struct tmp_data, list);

    TEST_ASSERT(tmp_data->data == 0);


    list_init_head(&tmp_list);  //clear

    for(i=0; i < COUNT_NODES; i++)
    {
        nodes[i].data = -i;
        list_push_back(&nodes[i].list, &tmp_list);
    }


    min = list_min(tmp_list.next, &tmp_list, comp_less);
    tmp_data = list_data(min, struct tmp_data, list);

    TEST_ASSERT(tmp_data->data == -(COUNT_NODES-1));


    TEST_PASS(NULL);
}



TEST(test_list_max)
{
    DECLARE_LIST_HEAD(tmp_list);

    const int COUNT_NODES = 100;
    int i;
    struct tmp_data  nodes[COUNT_NODES];
    struct tmp_data  *tmp_data;
    struct list_head *max;


    max = list_max(tmp_list.next, &tmp_list, comp_less);
    TEST_ASSERT(max == &tmp_list); //max == end iterator (list empty)


    for(i=0; i < COUNT_NODES; i++)
    {
        nodes[i].data = i;
        list_push_back(&nodes[i].list, &tmp_list);
    }


    max = list_max(tmp_list.next, &tmp_list, comp_less);
    tmp_data = list_data(max, struct tmp_data, list);

    TEST_ASSERT(tmp_data->data == COUNT_NODES-1);


    list_init_head(&tmp_list);  //clear

    for(i=0; i < COUNT_NODES; i++)
    {
        nodes[i].data = -i;
        list_push_back(&nodes[i].list, &tmp_list);
    }


    max = list_max(tmp_list.next, &tmp_list, comp_less);
    tmp_data = list_data(max, struct tmp_data, list);

    TEST_ASSERT(tmp_data->data == 0);


    TEST_PASS(NULL);
}



TEST(test_list_minmax)
{
    DECLARE_LIST_HEAD(tmp_list);

    const int COUNT_NODES = 100;
    int i;
    struct tmp_data  nodes[COUNT_NODES];
    struct tmp_data  *tmp_data;
    struct list_head *res[2];


    list_minmax(tmp_list.next, &tmp_list, comp_less, res);
    TEST_ASSERT(res[0] == &tmp_list); //min == end iterator (list empty)
    TEST_ASSERT(res[1] == &tmp_list); //max == end iterator (list empty)



    for(i=0; i < COUNT_NODES; i++)
    {
        nodes[i].data = i;
        list_push_back(&nodes[i].list, &tmp_list);
    }


    list_minmax(tmp_list.next, &tmp_list, comp_less, res);
    tmp_data = list_data(res[0], struct tmp_data, list);
    TEST_ASSERT(tmp_data->data == 0);                       //min

    tmp_data = list_data(res[1], struct tmp_data, list);
    TEST_ASSERT(tmp_data->data == COUNT_NODES-1);           //max


    list_init_head(&tmp_list);  //clear

    for(i=0; i < COUNT_NODES; i++)
    {
        nodes[i].data = -i;
        list_push_back(&nodes[i].list, &tmp_list);
    }


    list_minmax(tmp_list.next, &tmp_list, comp_less, res);
    tmp_data = list_data(res[0], struct tmp_data, list);
    TEST_ASSERT(tmp_data->data == -(COUNT_NODES-1));        //min

    tmp_data = list_data(res[1], struct tmp_data, list);
    TEST_ASSERT(tmp_data->data == 0);                       //max


    TEST_PASS(NULL);
}



int pred_50(const struct list_head *it)
{
    struct tmp_data *data = list_data(it, struct tmp_data, list);

    return data->data == 50;
}



TEST(test_list_find)
{
    DECLARE_LIST_HEAD(tmp_list);

    const int COUNT_NODES = 100;
    int i;
    struct tmp_data   nodes[COUNT_NODES];
    struct list_head *f;


    for(i=0; i < COUNT_NODES; i++)
    {
        nodes[i].data = i;
        list_push_back(&nodes[i].list, &tmp_list);
    }


    f = list_find(tmp_list.next, &tmp_list, pred_50);

    TEST_ASSERT(f == &nodes[50].list );


    TEST_PASS(NULL);
}



int pred_data(const struct list_head *it, void *user_data)
{
    struct tmp_data *data = list_data(it, struct tmp_data, list);

    int *user_int = (int *)user_data;

    return data->data == *user_int;
}



TEST(test_list_find2)
{
    DECLARE_LIST_HEAD(tmp_list);

    const int COUNT_NODES = 100;
    int i;
    struct tmp_data   nodes[COUNT_NODES];
    struct list_head *f;


    for(i=0; i < COUNT_NODES; i++)
    {
        nodes[i].data = i;
        list_push_back(&nodes[i].list, &tmp_list);
    }


    for(i=0; i < COUNT_NODES; i++)
    {
        f = list_find2(tmp_list.next, &tmp_list, pred_data, &i);

        TEST_ASSERT(f == &nodes[i].list );
    }


    TEST_PASS(NULL);
}



ptest_func tests[] =
{
    test_list_empty,
    test_list_is_first,
    test_list_is_last,
    test_list_is_singular,
    test_list_size,
    test_list_del,
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
    test_list_iter,
    test_list_data_citer,
    test_list_data_iter,

    //Algorithm
    test_list_for_each,
    test_list_min,
    test_list_max,
    test_list_minmax,
    test_list_find,
    test_list_find2,
};



MAIN_TESTS(tests)
