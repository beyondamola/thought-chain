# thought-chain
 **thought-chain is a terminal based journaling system written with besboke linked-list methods to store your chain_of_thought over time...**
 
### personal note:
  this is my first personal project; 
  a small but serious step in taking CS more seriously; 
  had a lot of fun.
  eventually I plan to make a special visual with these nodes; 
  first have to get the barebones working..
  Enjoy.

## HOW IT WORKS:
  **Nodes store user entries as strings and can load/save them onto files. All nodes form a linked list in memory. 
    The program includes traditional linked-list logic - handwritten, not stl.**
    
## FEATURES:
  - Timestamps attached to entries at time of creation
  - Deleted entry trash bin (stores your 'broken_links')
  - Save/load methods from '.txt' files (main & trash)
  - Organizes all entries into node chains (literally..)

## FILE STRUCTURE: 
  *All data is stored and loaded as linked lists in computer memory.*
  'chain_of_thought.txt' -> { houses MAIN entries} 
  'broken_links.txt' -> {houses DELETED entries (trash)}

## TECH STACK:
  C++;  Basic File I/O;  Custom Linked List Implentation;

## ON THE CHOPPING BLOCK:
  - Memory is not cleaned on reload (old nodes persist)
  - No input validation for out of bound deletes
  - entry count of main nodes are constantly recalculated) (not persistant)
  - No real UI (yet - WIP)

---
*thanks for reading*
