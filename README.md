# Levenshtein Distance

---

What is Levenstein Distance? 
The Levenshtein distance is a number that tells you how different two strings are. The higher the number, the more different the two strings are. After some research I decided to write the code of it. Found out that some implementations are better than others and decided to try to optimize standard Levenshtein Distance as much as I could. 

## Short Summary

- Model 1
Model 1 uses n*m matrix where n is size of the user input and m is size of the word from the dictionary. It uses memory not very efficiently and calls assign per call (which is slow).

- Model 2
Model 2 uses vector of size n*m i.e. flattened matrix. I also changed unnecessary assign to reserve + resize.

- Model 3
Model 3 uses vector but now of size 2 * n (flattened again). (minor change - instead of calling std::min({}) that creates initializer_list wrote two standard std::min()

- Model 4 (soon - parallel reading + early exit)
