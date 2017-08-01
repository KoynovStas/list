#include "stest.h"
#include "spqueue.h"





struct tmp_data
{
   int key;
   int data;
};



#define DECLARE_TMP_DATA(name, key, data) \
    struct tmp_data name = { key, data}


int compare_int_keys(void* key1, void* key2) {

    int key1_v = *((int*)key1);
    int key2_v = *((int*)key2);


    if (key1_v <= key2_v)
        return 1;

    return 0;
}



int compare_int_keys_gt(void* key1, void* key2) {

    int key1_v = *((int*)key1);
    int key2_v = *((int*)key2);


    if (key1_v >= key2_v)
        return 1;

    return 0;
}





TEST(test_spqueue_size)
{
    DECLARE_SPQUEUE(tmp_pqueue, 4, compare_int_keys);
    DECLARE_TMP_DATA(d1, 1, 0);
    DECLARE_TMP_DATA(d2, 2, 0);
    DECLARE_TMP_DATA(d3, 3, 0);
    DECLARE_TMP_DATA(d4, 4, 0);

    int res;

    TEST_ASSERT(tmp_pqueue.size == 0);    //pqueue must be empty


    res = spqueue_push(&tmp_pqueue, &d1.key);    //now d1 is first
    TEST_ASSERT(tmp_pqueue.size == 1);           //pqueue now is NOT empty
    TEST_ASSERT(res == 0);

    res = spqueue_push(&tmp_pqueue, &d2.key);
    TEST_ASSERT(tmp_pqueue.size == 2);
    TEST_ASSERT(res == 0);

    res = spqueue_push(&tmp_pqueue, &d3.key);
    TEST_ASSERT(tmp_pqueue.size == 3);
    TEST_ASSERT(res == 0);

    res = spqueue_push(&tmp_pqueue, &d4.key);
    TEST_ASSERT(tmp_pqueue.size == 4);
    TEST_ASSERT(res == 0);

    res = spqueue_push(&tmp_pqueue, &d4.key);
    TEST_ASSERT(tmp_pqueue.size == 4);
    TEST_ASSERT(res == -1);



    spqueue_pop(&tmp_pqueue);
    TEST_ASSERT(tmp_pqueue.size == 3);

    spqueue_pop(&tmp_pqueue);
    TEST_ASSERT(tmp_pqueue.size == 2);

    spqueue_pop(&tmp_pqueue);
    TEST_ASSERT(tmp_pqueue.size == 1);

    spqueue_pop(&tmp_pqueue);
    TEST_ASSERT(tmp_pqueue.size == 0);

    spqueue_pop(&tmp_pqueue);
    TEST_ASSERT(tmp_pqueue.size == 0);



    TEST_PASS(NULL);
}



TEST(test_spqueue_top)
{
    DECLARE_SPQUEUE(tmp_pqueue, 4, compare_int_keys);
    DECLARE_TMP_DATA(d1, 1, 0);
    DECLARE_TMP_DATA(d2, 2, 0);
    DECLARE_TMP_DATA(d3, 3, 0);
    DECLARE_TMP_DATA(d4, 4, 0);


    TEST_ASSERT(tmp_pqueue.size == 0);    //pqueue must be empty


    spqueue_push(&tmp_pqueue, &d1.key);  //now d1 is first
    TEST_ASSERT(spqueue_top(&tmp_pqueue) == &d1.key);

    spqueue_push(&tmp_pqueue, &d2.key);
    TEST_ASSERT(spqueue_top(&tmp_pqueue) == &d1.key);

    spqueue_push(&tmp_pqueue, &d3.key);
    TEST_ASSERT(spqueue_top(&tmp_pqueue) == &d1.key);

    spqueue_push(&tmp_pqueue, &d4.key);
    TEST_ASSERT(spqueue_top(&tmp_pqueue) == &d1.key);




    spqueue_pop(&tmp_pqueue);
    TEST_ASSERT(spqueue_top(&tmp_pqueue) == &d2.key);

    spqueue_pop(&tmp_pqueue);
    TEST_ASSERT(spqueue_top(&tmp_pqueue) == &d3.key);

    spqueue_pop(&tmp_pqueue);
    TEST_ASSERT(spqueue_top(&tmp_pqueue) == &d4.key);

    spqueue_pop(&tmp_pqueue);
    TEST_ASSERT(spqueue_top(&tmp_pqueue) == NULL);

    spqueue_pop(&tmp_pqueue);
    TEST_ASSERT(spqueue_top(&tmp_pqueue) == NULL);



    TEST_PASS(NULL);
}



ptest_func tests[] =
{
    test_spqueue_size,
    test_spqueue_top,
};





MAIN_TESTS(tests)
