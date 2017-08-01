#include "stest.h"
#include "pqueue.h"





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



TEST(test_pqueue_size)
{
    struct pqueue_t tmp_pqueue;

    TEST_ASSERT(pqueue_init(&tmp_pqueue, 0, 4, compare_int_keys) == 0);

    DECLARE_TMP_DATA(d1, 1, 0);
    DECLARE_TMP_DATA(d2, 2, 0);
    DECLARE_TMP_DATA(d3, 3, 0);
    DECLARE_TMP_DATA(d4, 4, 0);

    int res;

    TEST_ASSERT(tmp_pqueue.size == 0);    //pqueue must be empty


    res = pqueue_push(&tmp_pqueue, &d1.key);     //now d1 is first
    TEST_ASSERT(tmp_pqueue.size == 1);           //pqueue now is NOT empty
    TEST_ASSERT(res == 0);

    res = pqueue_push(&tmp_pqueue, &d2.key);
    TEST_ASSERT(tmp_pqueue.size == 2);
    TEST_ASSERT(res == 0);

    res = pqueue_push(&tmp_pqueue, &d3.key);
    TEST_ASSERT(tmp_pqueue.size == 3);
    TEST_ASSERT(res == 0);

    res = pqueue_push(&tmp_pqueue, &d4.key);
    TEST_ASSERT(tmp_pqueue.size == 4);
    TEST_ASSERT(res == 0);

    res = pqueue_push(&tmp_pqueue, &d4.key);
    TEST_ASSERT(tmp_pqueue.size == 4);
    TEST_ASSERT(res == -1);



    pqueue_pop(&tmp_pqueue);
    TEST_ASSERT(tmp_pqueue.size == 3);

    pqueue_pop(&tmp_pqueue);
    TEST_ASSERT(tmp_pqueue.size == 2);

    pqueue_pop(&tmp_pqueue);
    TEST_ASSERT(tmp_pqueue.size == 1);

    pqueue_pop(&tmp_pqueue);
    TEST_ASSERT(tmp_pqueue.size == 0);

    pqueue_pop(&tmp_pqueue);
    TEST_ASSERT(tmp_pqueue.size == 0);



    TEST_PASS(NULL);
}



TEST(test_pqueue_size2)
{
    struct pqueue_t tmp_pqueue;

    TEST_ASSERT(pqueue_init(&tmp_pqueue, 16, 4, compare_int_keys) == 0);

    DECLARE_TMP_DATA(d1, 1, 0);
    DECLARE_TMP_DATA(d2, 2, 0);
    DECLARE_TMP_DATA(d3, 3, 0);
    DECLARE_TMP_DATA(d4, 4, 0);

    int res;

    TEST_ASSERT(tmp_pqueue.size == 0);    //pqueue must be empty


    res = pqueue_push(&tmp_pqueue, &d1.key);  //now d1 is first
    TEST_ASSERT(tmp_pqueue.size == 1);           //pqueue now is NOT empty
    TEST_ASSERT(res == 0);

    res = pqueue_push(&tmp_pqueue, &d2.key);
    TEST_ASSERT(tmp_pqueue.size == 2);
    TEST_ASSERT(res == 0);

    res = pqueue_push(&tmp_pqueue, &d3.key);
    TEST_ASSERT(tmp_pqueue.size == 3);
    TEST_ASSERT(res == 0);

    res = pqueue_push(&tmp_pqueue, &d4.key);
    TEST_ASSERT(tmp_pqueue.size == 4);
    TEST_ASSERT(res == 0);

    res = pqueue_push(&tmp_pqueue, &d4.key);
    TEST_ASSERT(tmp_pqueue.size == 5);
    TEST_ASSERT(res == 0);
    TEST_ASSERT(tmp_pqueue.capacity == 20);


    TEST_PASS(NULL);
}



TEST(test_pqueue_top)
{
    struct pqueue_t tmp_pqueue;
    TEST_ASSERT(pqueue_init(&tmp_pqueue, 0, 4, compare_int_keys) == 0);

    DECLARE_TMP_DATA(d1, 1, 0);
    DECLARE_TMP_DATA(d2, 2, 0);
    DECLARE_TMP_DATA(d3, 3, 0);
    DECLARE_TMP_DATA(d4, 4, 0);


    TEST_ASSERT(tmp_pqueue.size == 0);    //pqueue must be empty


    pqueue_push(&tmp_pqueue, &d1.key);  //now d1 is first
    TEST_ASSERT(pqueue_top(&tmp_pqueue) == &d1.key);

    pqueue_push(&tmp_pqueue, &d2.key);
    TEST_ASSERT(pqueue_top(&tmp_pqueue) == &d1.key);

    pqueue_push(&tmp_pqueue, &d3.key);
    TEST_ASSERT(pqueue_top(&tmp_pqueue) == &d1.key);

    pqueue_push(&tmp_pqueue, &d4.key);
    TEST_ASSERT(pqueue_top(&tmp_pqueue) == &d1.key);




    pqueue_pop(&tmp_pqueue);
    TEST_ASSERT(pqueue_top(&tmp_pqueue) == &d2.key);

    pqueue_pop(&tmp_pqueue);
    TEST_ASSERT(pqueue_top(&tmp_pqueue) == &d3.key);

    pqueue_pop(&tmp_pqueue);
    TEST_ASSERT(pqueue_top(&tmp_pqueue) == &d4.key);

    pqueue_pop(&tmp_pqueue);
    TEST_ASSERT(pqueue_top(&tmp_pqueue) == NULL);

    pqueue_pop(&tmp_pqueue);
    TEST_ASSERT(pqueue_top(&tmp_pqueue) == NULL);



    TEST_PASS(NULL);
}



TEST(test_pqueue_top2)
{

    const size_t SIZE = 100;

    struct pqueue_t tmp_pqueue;
    TEST_ASSERT(pqueue_init(&tmp_pqueue, 0, SIZE, compare_int_keys) == 0);

    struct tmp_data items[SIZE];

    TEST_ASSERT(tmp_pqueue.size == 0);    //pqueue must be empty


    for(size_t i = 0; i < SIZE; i++)
    {
        items[i].key = i;
        pqueue_push(&tmp_pqueue, &items[i].key);
    }

    TEST_ASSERT(tmp_pqueue.size == SIZE);


    for(size_t i = 0; i < SIZE; i++)
    {
        TEST_ASSERT(pqueue_top(&tmp_pqueue) == &items[i].key);
        pqueue_pop(&tmp_pqueue);
    }

    TEST_ASSERT(tmp_pqueue.size == 0);


    //reverse

    for(size_t i = 0; i < SIZE; i++)
    {
        items[i].key = SIZE-i;
        pqueue_push(&tmp_pqueue, &items[i].key);
    }

    TEST_ASSERT(tmp_pqueue.size == SIZE);


    for(size_t i = 0; i < SIZE; i++)
    {
        TEST_ASSERT(pqueue_top(&tmp_pqueue) == &items[SIZE-i-1].key);
        pqueue_pop(&tmp_pqueue);
    }

    TEST_ASSERT(tmp_pqueue.size == 0);


    TEST_PASS(NULL);
}



TEST(test_pqueue_top3)
{

    const size_t SIZE = 100;

    struct pqueue_t tmp_pqueue;
    TEST_ASSERT(pqueue_init(&tmp_pqueue, 32, 32, compare_int_keys) == 0);

    struct tmp_data items[SIZE];

    TEST_ASSERT(tmp_pqueue.size == 0);    //pqueue must be empty


    for(size_t i = 0; i < SIZE; i++)
    {
        items[i].key = i;
        pqueue_push(&tmp_pqueue, &items[i].key);
    }

    TEST_ASSERT(tmp_pqueue.size == SIZE);
    TEST_ASSERT(tmp_pqueue.capacity == 128);


    for(size_t i = 0; i < SIZE; i++)
    {
        TEST_ASSERT(pqueue_top(&tmp_pqueue) == &items[i].key);
        pqueue_pop(&tmp_pqueue);
    }

    TEST_ASSERT(tmp_pqueue.size == 0);


    //reverse

    for(size_t i = 0; i < SIZE; i++)
    {
        items[i].key = SIZE-i;
        pqueue_push(&tmp_pqueue, &items[i].key);
    }

    TEST_ASSERT(tmp_pqueue.size == SIZE);


    for(size_t i = 0; i < SIZE; i++)
    {
        TEST_ASSERT(pqueue_top(&tmp_pqueue) == &items[SIZE-i-1].key);
        pqueue_pop(&tmp_pqueue);
    }

    TEST_ASSERT(tmp_pqueue.size == 0);


    TEST_PASS(NULL);
}



ptest_func tests[] =
{
    test_pqueue_size,
    test_pqueue_size2,
    test_pqueue_top,
    test_pqueue_top2,
    test_pqueue_top3,
};





MAIN_TESTS(tests)
