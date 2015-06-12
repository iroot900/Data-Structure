# Data-Structure (C++)
This repository include my implementation of many widely used non-trivial data structures. Templates are used to make them more generic and ready to use for project.

>HashTable with Chaining

>HashTable with Open addressing (Linear probe)

For my test case, when HashTables have same number of buckets, chaining is about twice faster than open addressing. But chaining takes more memory since all nodes contain a pointer to next node. That being said, if using same memory, open addresing could have twice as much buckets, and in this case, difference is very small with chainning slighter better. Anyway, chaining seems a better solution in practice. Open address takes the risk of being filled full(end up really really slow) and moving item around, which is very expensive. 

>MinHeap (decrease key are supported)

>B tree

>AVL tree
