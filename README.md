# Serialization
C++ code where I used input and output flow operators to serialize data (OOP included).

The data I serialized is a std::vector of class Person in a .txt file. I defined the flow operators inside class Person: two types of output flow operators (one for printing in console and another for serialize) and the input flow operator that is specified to get the data from the file. Besides this, there're functions to save, load, add, erase and find data.

Now, the way I followed to save each element of the vector in the .txt file is this: put each object attribute in a single line (lines 101-114). This means: 4 attributes of Person object will ocupate 4 lines in the file.
With this, loading data is easy to do (lines 116-135). We just need to get the attributes line by line and construct the object again (lines 89-86 and 127). However, after I finish getting all data the std::vector gets trash at the end because of the final line break in the file, so I erase the last element to solve that problem.

As I mentioned before, you can insert and delete data and see how serialization works. Besides de .cpp file, you have the .txt file used by the program so you can see how data is processed. That's all, I hope you like my work. Feel free to ask anything you want and use this proyect as you want.
