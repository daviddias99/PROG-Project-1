--- MIEIC-PROG: Project 1 2017/2017 ---

AUTHORS

David Luis Dias da Silva, up201705473
Luis Pedro Pereira Lopes Mascarenhas Cunha, up201706736



INTRODUCTION

.These programs were assigned to us as the first project for the class "Programming" in order to apply the knowledge we gained through the semester about the concepts of structured programming, top-down and bottom-up development and the programming language C++(library functions, syntax, data-structures,...).
The project is divided in two segments.

PROGRAM 1

.The first part of the project consisted of a program with receives a "dictionary" file created by the use, and 
analyzes it, retrieving all the simple words of the "headlines" that it contains, sorting them, removing duplicates, and 
writing them to a text file.

.The main challenges of the first part were:
-reading and writing to the text file;
-choosing of the correct algorithms to analyze the lines of the dictionary in order to sort out the valid ones;
-choosing of the correct algorithms to manipulate the complex headlines;
-analyzing the different sorting and removing-duplicates methods in order to choose the most appropriate one 
to the task at hand;
-structuring the program to make it easy to read, understand and modify 
-handling invalid inputs


.Having these points into account, we can say that we were able to tackle them and produce a solid, well commented, 
and functional program. Our program writes all the 95903 simple words from the test dictionary given to us into a text file, 
although the dot (‘.’) display may be a little off(we did not give that much attention since in our opinion it was only an 
aesthetic part of the program and it didn’t affect the main purpose of the program). We also would like to point out that 
we tried to use self-made sorting and removing-duplicate functions. We first tried using a bubble sort, as we thought that 
the it would be suitable to the partial sorted vector,however, the O(n^2) temporal complexity of this sort made it
take a very long time to complete. As such we decided to use a Quicksort which fixes the issue. As for the removing duplicates 
we tried writing a function but do to the time it took to complete its process, we decided to use a set of functions from the 
C++ libraries.

PROGRAM 2

.The second part of the project consisted of a program that read a dictionary file (of the type of the one
produced by the first program) and implemented some word games from it.

.The main challenges of the first part were:
-choosing a layout and figuring out a way to repeat the functions and returning to the main menu;
-implementing some of the algorithms that manipulate words and compare them to one's on the dictionary;
-choosing the most efficient algorithms to implement the games;
-programming a efficient way to search a word on a vector;


.We were able to program the games that we were asked to do, however, there might exist better ways to implement them 
then the one's we used. Nonetheless we feel that these programs allowed us to show some efficient and solid algorithms, and
to show some of the capabilities of the C++/C programming language. Some of the aspects that can be improved on this program
are some handling of "invalid" inputs(such as if the user inputs ctrl+z in the first and fourth games) and the using of a 
"minor" case of recursion in the part of returning to the menu.



