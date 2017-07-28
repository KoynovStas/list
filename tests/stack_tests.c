#include "stest.h"
#include "stack.h"





struct tmp_data
{
   struct list_head list;
   int              data;
};



#define DECLARE_TMP_DATA(name) \
    struct tmp_data name = { {NULL}, 0}





TEST(test_stack_empty)
{
    DECLARE_STACK(tmp_stack);
    DECLARE_TMP_DATA(d1);


    TEST_ASSERT(tmp_stack.size == 0);    //stack must be empty


    stack_push(&d1.list, &tmp_stack);    //now d1 is first

    TEST_ASSERT(tmp_stack.size == 1);    //now stack is NOT empty


    TEST_PASS(NULL);
}



TEST(test_stack_size)
{
    DECLARE_STACK(tmp_stack);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);
    DECLARE_TMP_DATA(d3);



    TEST_ASSERT(tmp_stack.size == 0);               //size == 0 (is empty)
    TEST_ASSERT(stack_top(&tmp_stack) == NULL);


    //push
    stack_push(&d1.list, &tmp_stack);               //now d1 is first
    TEST_ASSERT(tmp_stack.size == 1);               //size == 1 (d1)
    TEST_ASSERT(!list_empty(&d1.list));             //list dont must be empty
    TEST_ASSERT(stack_top(&tmp_stack) == &d1.list); //d1 on top


    stack_push(&d2.list, &tmp_stack);               //now d2 is first
    TEST_ASSERT(tmp_stack.size == 2);               //size == 2 (d1, d2)
    TEST_ASSERT(!list_empty(&d2.list));             //list dont must be empty
    TEST_ASSERT(stack_top(&tmp_stack) == &d2.list); //d2 on top


    stack_push(&d3.list, &tmp_stack);               //now d3 is first
    TEST_ASSERT(tmp_stack.size == 3);               //size == 3 (d1, d2, d3)
    TEST_ASSERT(!list_empty(&d3.list));             //list dont must be empty
    TEST_ASSERT(stack_top(&tmp_stack) == &d3.list); //d2 on top



    //pop
    stack_pop(&tmp_stack);                          //now d3 del from stask
    TEST_ASSERT(tmp_stack.size == 2);               //size == 2 (d1, d2)
    TEST_ASSERT(list_empty(&d3.list));              //list must be empty
    TEST_ASSERT(stack_top(&tmp_stack) == &d2.list); //d2 on top


    stack_pop(&tmp_stack);                          //now d2 del from stask
    TEST_ASSERT(tmp_stack.size == 1);               //size == 1 (d1)
    TEST_ASSERT(list_empty(&d2.list));              //list must be empty
    TEST_ASSERT(stack_top(&tmp_stack) == &d1.list); //d1 on top


    stack_pop(&tmp_stack);                          //now d1 del from stask
    TEST_ASSERT(tmp_stack.size == 0);               //size == 0 ()
    TEST_ASSERT(list_empty(&d1.list));              //list must be empty
    TEST_ASSERT(stack_top(&tmp_stack) == NULL);     //NULL on top


    stack_pop(&tmp_stack);                          //nothing del from stask
    TEST_ASSERT(tmp_stack.size == 0);               //size == 0 ()
    TEST_ASSERT(stack_top(&tmp_stack) == NULL);     //NULL on top


    TEST_PASS(NULL);
}



ptest_func tests[] =
{
    test_stack_empty,
    test_stack_size,

};



MAIN_TESTS(tests)
