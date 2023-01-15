# Copyright 2022-2023 Raducanu George 321CA

# Octavian's Saga
------
## Task 1

In this task we must resolve the set cover problem using a SAT solver.

Thus, the problem must be reduced to a boolean SAT problem.
The reduction is done simillar to the vertex cover which is explained
in the pdf. For the set cover I have used the folowing types of clauses, 
considering Y(m, k) a matrix where y(i, j) is true only is the i set read 
from the input is the j from the so called cover.

>( y(1,r) V y(2, r) V ... V y(m, r) ) for r = 1:k <br/>

>( not(y(i, r)) V not(y(i, s)) ) for i = 1:m; r = 1:k; s = r+1:k <br/>

>( not(y(i, r)) V not(y(j, r)) ) for r = 1:k; i = 1:m; j = j+1:m <br/>

>( y(x1, 1) V ... V y(x1, k) V y(x2, k) V ... V y(xp, k))
where x1, ..., xp are the indices of the sets that contain a certain example. 

The last step must be repeted for each element 1:n

My implementation is straightford. It uses an frequency matrix.
Meaning each row represents a set and each colomn represents an element.

Thus, the matrix is (m, n) in size. Additionally I introduced
a helper matrix in order to have a easier and clearer solution.

A solution without the *helper* matrix could be more efficient in
terms of space and time (slightly).

The decoding of the oracle is easier and is done reading the response,
selecting the true variables (positives ones) and performing a modulo
operartion.

For a short overview in terms of complexity V = m * k and F = n + k * (k - 1) / 2 * m + m * (m - 1) / 2 * k + k;

Thus, if we consider O(1) the printing of a line we can say that the 
formulation of the clause to the oracle is O(F)

The decoding of the oracle is done in O(V) if the printing of a character is
 considered O(1)

------
## Task 2

This task is resolved in the same way as the precedent one. The difference is
 that we need to construct our elements.
Firstly we number only the card names that are wanted and that the player
does not posess.
The old n is now at max M
The old m is now P

Then for the ease of efficiency, at the reading of each package the precedent
 frequency matrix is constructed with the mention that
 card names that are not wanted are ignored. This is a small optimization
 that can be done and is also a valid crieria for our problem.

 My implementation uses string from the STL library. 
 The problems are continuisly formulated to the oracle until a true 
 valid assignation is returned.

------
## Task 3
This task is based on the code written above, but instead of the oracle
(SAT solver), there is an heuristic aproach.

My idea of the heuristics is very simple and easy to understand.

At each step the set with the most elements that have not been yet
 choosen is picked. This strategy is repeted untill all
  elements have been picked obtaining k, or all the sets have been picked,
   meaning there doesn't exist a solution using the provided set of cards.

Details regarding implementation:

The heuristics explained above is implemented using a frequency matrix.
At each step the line with the largest sum is chosen and then, the
elements that are 1 (in the current line) have their corresponding column
 made zero in the entire matrix.
 This facts assures us that we will not choose the next sets taking 
 into account elements that have been already picked.

---
 ### Complexity details:
 
 A quick overview:
 After eliminating the cards that are already owned the matrix is at
 most (P, M) where P is the number of packets read and M is the cards
 wanted.

In terms of complexity the heuristics algorithm is 
O(k * M * P), where k are the number of sets choosen, 
it is fairly good in terms of complexity and as the testing
has proven it is a good aproximation.

The idea is very straightforward and can be improved by also taking
into account the frequency of each element, but this direct aproach 
is very good and fast.