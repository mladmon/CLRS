## C++ implementations of data structures and algorithms from CLRS

On a quest to improve my general data structures and algorithms knowledge, I decided to read Introduction to Algorithms (colloquially referred to as [CLRS](https://en.wikipedia.org/wiki/Introduction_to_Algorithms) after the initials of the authors). I've also learned that the best way to learn something is to do it, especially when it comes to programming, and so I decided to do mini programming projects along the way to cement the concepts covered. I also saw this as an opportunity to refresh and build new C++ skills. The result is this repository, which contains 34 C++ implementations of various data structures and algorithms as covered in CLRS.

The directories are named such that they correspond to sections from the book. For example, [15.1-rod-cutting](https://github.com/mladmon/CLRS/tree/master/15.1-rod-cutting) refers to CLRS section 15.1 Rod cutting, where you learn how to cut rods in a very dynamic way. For anyone trying to learn or review topics from CLRS, you can refer to each directory as an example of how the pseudocode in the corresponding section from the book might translate into an actual programming language.

Another goal of mine was to refresh my C++ programming skills and gain experience with the new facilities that C++11 brought along. As a result, you'll notice a progression from rather rudimentary implementations in the beginning to more sophisticated (and possibly slightly unnecessary) implementations that make use of the various language features (STL containers and algorithms, iterators, [\<random\>](http://www.cplusplus.com/reference/random/), functors, etc.). 


### Running the code
Provided with each mini project is a simple program that serves to test the implementation for correctness and to make it more interactive. If you wish to run the code on your own, navigate to the directory of interest and compile the code first using:

```
g++ --std=c++11 -Wall -Werror -o rod-cutting rod-cutting.cpp
```

and then run with:

```
./rod-cutting
```

To anyone who believes in self-taught learning, I hope you find these projects useful in your quest to master the concepts covered in CLRS. As always, I'm open to any and all feedback! Feel free to shoot me an email at mladmon589@gmail.com with any thoughts or questions you may have. Cheers!
