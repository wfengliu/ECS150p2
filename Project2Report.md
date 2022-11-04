Project #2 Report by Willie Feng-Liu & Takumi Imanaka
-------------

**Objective**

- The objective of this project is to understand and implement a
multithread system. We were asked to create our own queue and
thread API using the context API.

**Design Choices**

- The majority of our working code lies in our queue
- Our queue utilizes a linked list implementation. We use two structs
to make this possible, one to build each node, and the other to build
the queue itself. The node struct, QNode, holds a void pointer to a 
value, along with a self-referential pointer to the next QNode. The
Queue struct contains a head and tail pointer, and an int for the
number of nodes in the queue.
- We adjusted our queue_iterate() function to save the next qNode
so that in the case a node was deleted, our current node will be
pointing to the correct value
- We implemented our own queue_isempty() function so that we could
check conditions for dequeuing, destroying, and enqueuing
- We included a count variable in our structs to keep track of the amount
of Nodes in the queue. This helped a lot in our testing phase
- In our uthread.c file, our code was built upon the context API
and were implemented via the functions in context.c
- We chose to have a queue to hold our ready threads which would be
enqueued and dequeued as they were created and ran

**Testing**

- We conducted thorough testing of our queue functions. Every queue operation
is tested with various different scenarios possible. Some of the things we
tested are the values of the head and tail pointers after each of the queue
operations, along with the return values of these functions when being called
on empty, one-node, and multiple node queues. Passing these test cases means
that the queue is operating correctly.
- We created a makefile to simplify creating executables and the library
for testing. The Makefile itself also required testing to ensure we were
including a sufficient amount of objects
- We tested via the CSIF to ensure that the code would run correctly on
the autograder

**Errors and Explanations**

- Phase 2,3,4 not completed
- We were unable to test if the iteration funciton was resistance to
deletion in phase 1
- Code for phase 2 is written using the rubric provided in the lab manual,
though it is not fully flushed out enough run successfully

Link to our github repository: [github][1].

[1]: https://github.com/wfengliu/ECS-150-project-2
