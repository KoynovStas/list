# Simple linked lists implementation



## Description

It is implementation a very simple **embedded** list on C.

>Embedded list?
>>Yes see next



### Standart linked list on C:

```C++
struct node
{
	void *data;           //or user_type data, or user_type *data
	struct node *next;
};
```
More details see in [Linked list Wiki](https://en.wikipedia.org/wiki/Linked_list)



### Embedded linked list on C:

```C++
struct list_head
{
    struct list_head *next;
};
```

**Node** - a data structure (payloads) in which one of the fields is a variable of type **list_head**.

*list_head* **embedded** in user_type.

**example:**
```C++
struct user_type
{
    struct list_head list;
    int              data;
    int              data2;
    //....
};
```

---


### Standart doubly linked list on C:

```C++
struct node
{
	void *data;           //or user_type data, or user_type *data
	struct node *next;
    struct node *prev;
};
```
More details see in [Doubly linked list Wiki](https://en.wikipedia.org/wiki/Doubly_linked_list)


### Embedded doubly linked list on C:
```C++
struct dlist_head
{
    struct dlist_head *next;
    struct dlist_head *prev;
};
```

**Node** - a data structure (payloads) in which one of the fields is a variable of type **dlist_head**.

*dlist_head* **embedded** in user_type.

**example:**
```C++
struct user_type
{
    struct dlist_head list;
    int               data;
    int               data2;
    //....
};
```



<br/>
## [list.h](./list.h) - Embedded circular linked list implementation on C

**empty list:**
```
        ______
       |      |
    -->| head |---
    |  |______|  |
    |            |
    |____________|
```
 

**list with nodes:**
```
       ______     _______     _______
      |      |   |       |   |       |
   -->| head |-->| node0 |-->| node1 |---
   |  |______|   |_______|   |_______|  |
   |                                    |
   |____________________________________|
```


**Node** - a data structure (payloads) in which one of the fields is
a variable of type list_head.

example:
```C++
struct tmp_data
{
    struct list_head list;
    int              data;
};
```

node* - a pointer to a Node, which is a pointer == pointer to
member (list_head) within the struct of data.

If a member(list_head) in data structure (payloads) is
the first member (offset == 0) then the Node* == node*

To get pointer to data structure(payloads), if you have a pointer to a node,
use the function: **list_data**



<br/>
## [dlist.h](./dlist.h) - Embedded circular doubly linked list implementation on C

**empty list:**
```
        ______
       |      |
    -->| head |<--
    |  |______|  |
    |            |
    |____________|
```
 

**list with nodes:**
```
       ______     _______     _______
      |      |   |       |   |       |
   -->| head |<->| node0 |<->| node1 |<--
   |  |______|   |_______|   |_______|  |
   |                                    |
   |____________________________________|
```


**Node** - a data structure (payloads) in which one of the fields is
a variable of type dlist_head.

example:
```C++
struct tmp_data
{
    struct dlist_head list;
    int               data;
};
```

node* - a pointer to a Node, which is a pointer == pointer to
member (dlist_head) within the struct of data.

If a member(dlist_head) in data structure (payloads) is
the first member (offset == 0) then the Node* == node*

To get pointer to data structure(payloads), if you have a pointer to a node,
use the function: **dlist_data**



<br/>
## Algorithmic complexity

func                 |  list.h | dlist.h |
---------------------|---------|---------|
list_size            |   O(n)  |   O(n)  |
list_empty           |   O(1)  |   O(1)  |
list_is_first        |   O(1)  |   O(1)  |
list_is_last         |   O(1)  |   O(1)  |
list_is_singular     |   O(1)  |   O(1)  |
list_push_front      |   O(1)  |   O(1)  |
list_pop_front       |   O(1)  |   O(1)  |
list_push_back       |   O(n)  |   O(1)  |
list_pop_back        |   O(n)  |   O(1)  |
list_del             |   O(n)  |   O(1)  |
list_replace         |   O(n)  |   O(1)  |
list_replace_init    |   O(n)  |   O(1)  |
list_move_to_front   |   O(n)  |   O(1)  |
list_move_to_back    |   O(2n) |   O(1)  |
list_rotate_left     |   O(2n) |   O(1)  |
list_rotate_right    |   O(2n) |   O(1)  |
list_splice_front    |   O(n)  |   O(1)  |
list_splice_back     |   O(2n) |   O(1)  |


#### Get Data from node

macros               | list.h | dlist.h |
---------------------|--------|---------|
list_data            |  O(1)  |   O(1)  |
list_first_data      |  O(1)  |   O(1)  |
list_last_data       |  O(n)  |   O(1)  |


#### Iterator
 
Iterator             | list.h | dlist.h |
---------------------|--------|---------|
list_citer           |   Yes  |  Yes    |
list_criter          |   No   |  Yes    |
list_iter            |   Yes  |  Yes    |
list_riter           |   No   |  Yes    |
list_data_citer      |   Yes  |  Yes    |
list_data_criter     |   No   |  Yes    |
list_data_iter       |   Yes  |  Yes    |
list_data_riter      |   No   |  Yes    |


#### Algorithm

func                 | list.h |  dlist.h |
---------------------|--------|----------|
list_for_each        |  O(n)  |   O(n)   |
list_min             |  O(n)  |   O(n)   |
list_max             |  O(n)  |   O(n)   |



<br/>
## License

[BSD 3-Clause License](./LICENSE).
