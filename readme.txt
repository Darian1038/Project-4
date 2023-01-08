The idea of this project is to utilize Binary search trees while allocating memory.
The goal is to not lose any memory when freeing some of the search trees and to be able 
to access any tree when given a command.
Input:
The first line of the input contains the N number of trees, the total number of items 
in the list to be inserted to all trees, and the number of queries listed in the input file.
The next N lines contains the list of names of the trees, followed by the 
I lines of items to be inserted into these trees. These I lines contains the name of the tree,
then the item name, then the count of the item. Finally, the next 1 lines contain a set of queries 
which need to be processed. You can search(displays count of an item in a tree),
item_before(counts the items in a given treebefore the given item name), height_balance
(determines if a tree is balanced), count(displaces total number of items in a tree), reduce
(reduces count of an item in a tree), delete(deletes item from a tree), delete_name(deletes an entire tree).

 Output:
Displays all the trees and the items in the tree, followed by all of the query commands given by the input file.