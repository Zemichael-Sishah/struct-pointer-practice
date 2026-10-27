# HW0.5 | Structs and Intro to Pointers

In this **second** assignment in the  "introduction to C" series of homeworks, we will explore the following:

1. dealing with **compound** types,
2. accessing **pointers** and
3. writing effective **test cases**.

While we are still _sorting_ data, we move on to sorting _compound types_, _viz.,_ **structs** &rarr; accessed using **pointers**.

## coding instructions

As before, you must implement your sorting code in the following file: `sorting_function.c`. 

1. First, you must implement the following functions:

```C
int sorting_function( struct student* student_records[], int count, enum sort_base base ) ;
int is_sorted( struct student* student_records[], int count, enum sort_base base ) 
```

2. In addition, you need to implement the following "helper" functions, also known as "**comparator**" functions,

```C
int string_comparator( const char str1[], const char str2[] ) ;
int integer_comparator(int a, int b) ;
```

Hence, you must implement a total of **four** functions, all in the same file, `sorting_function.c`.

The objective of the assignment is to sort an array of **pointers** to the following **struct**:

```C
struct student
{
    int _id ;
    char _name[MAX_NAME_LENGTH] ;
} ;
```

The array of pointers represents "student records" that need to be sorted in _one of two ways_ (more below).

**Note**: 
- `sorting_function.c` is the **only** source file you should change. **Do not** modify **any** other `.c` or `.h` file! If you make any other changes, then the grading script may break and **you will lose points**!
- each function has additional instructions/hints provided as comments. Please **pay careful attention** to the comments. They also include information on the return values as well.
- you **do not** need to allocate/free the memory for anything, including `struct student` -- this is taken care of for you. You do need to make sure you're **accessing** them correctly, _i.e.,_ using the `->` notation.


3. In addition, you must **develop test cases** to properly check your code. Note that the `tests` directory only includes **two** tests! More on this later.


## building/compiling/running your code

The repository includes a `Makefile`. While you may not understand all of it (if you're not familiar with makefiles), such files are **very** important -- especially in large projects or to carry out multiple tasks (_e.g.,_ building/compiling code, running tests, _etc._ as we do here). 

1. to **compile** ("build" -- which include more than just compilation, it includes "linking" as well -- you will learn more later), type the following at the **command line**:

```$> make```

**Note:** you should **not** type the `$>` part -- that is just to indicate that whatever **follows** it should be typed on the command line. In this case, just `make`. 

Run the above in the main directory of your project. 

This will compile and build your code using `gcc` -- one of the most popular `C` compilers. If your code has errors, then that will show up as well. Once your code is complete, and free of _compile-time errors_ (there may still be _runtime/logic errors_ in your code) the makefile will create an _executable_, named `sort`. 

2. to **run** your code, type:

```
./sort <name/id> <input file> <output file>
```

<br>
where,

||||
|----|----|----|
| `<name/id>` | one of `name` or `id` | sort the data based on NAME or the student ID |
| `<input file>` | the input file name with the data to be sorted | look in `tests\` folder for some examples |
| `<output file>` | filename where the output is to be stored | look in `tests\test_outputs\expected*` files for some examples |
||

As you may have already guessed, your code should be able to sort the array in one of two ways (in ascending order):

1. based on the student **name** or
2. based on the student **ID number**

And this is where the two **comparator** functions come in. You need to write the code inside each,
- `string_comparator()` &rarr; takes in two strings (how does `C` represent strings?) and returns if one is "smaller/larger/equal" ([lexicographic/alphabetic order](https://en.wikipedia.org/wiki/Alphabetical_order)) when compared to the other.
- `integer_comparator()` &rarr; takes two integers and returns if one is smaller/larger/equal when compared to the other. 

(See the comments in the functions for the properties of the return values.)

Your code **must** use these two functions based on the value passed via the argument, `enum sort_base base` where `base` is one of two values: `name` or `id` (recall how enums are created/used).

Here is an example on how to run your code,

```
./sort name tests/test1.txt tests/test_outputs/test1.output.txt.id
```

So, we're saying,

- sort "base" is `name`
- the inputs are in the file `test1.txt` in the `tests` folder
- write the output to the `test1.output.txt.id` file in the `tests/test_outputs/` folder


## I/O file formats

You can use the **two** public test cases in the `tests` folder to test your code but **you must write other test cases of your own** to make sure you properly capture all sorts of edge cases for the sorting algorithm!

> Tip: Test for any edge case you can think of (including an input of 0)

To run _all_ of the public test cases, type:

```$> make tests```

It will go through all the test cases in the `tests` folder, run each one twice (once for NAME, once for ID) and write the outputs in the `tests\test_outputs` folder. Files that end in `.name` are the attempts for ordering based on the names and those that end in `.id` are the outputs for the tests that sorted the records based on the IDs.

(It is a good idea to run `make clean` before running `make tests`.)

### input file format

The input file is a **text** file with the following format:

```
<number of integers>
<id1> <name1>
<id2> <name2>
<id3> <name3>
...
<idN> <nameN>
```

**Note** that `<id>`s are integers while `<name>`s are strings.

The **first** number in the file is the **count** of how many records (the actual input) must be sorted. 

For example, `test1.txt` in the public tests:

```
2
123456 William Wordsworth
876543 Mirza Ghalib
```

As before, the framework will read in the file (as long as the proper name is provided) and give you the `count` and the "records" in the `student_records` array.

(Look at `helper_functions.c` and `sort.c` to peek under the hood -- to see how this "magic" happens.)


### output file format 

The output file is also a **text** file with the following format. 

Either,

```
Array is SORTED by the <NAME/ID> base!!

<list of sorted records, one per line>
```

OR

```
Array is NOT SORTED by the <NAME/ID> base!!

<list of records, one per line>
```

depending on whether your sorting code worked or not.

(In the second case -- NOT sorted -- the _order_ of the records _may not_ match the original order from the input file. Why?)

**Note:** the _correct_ outputs for two tests (prefaced by the word, `expected`) have been provided in the `tests/test_outputs/`folder:

- `expected.test1.txt.id`
- `expected.test1.txt.name`
- `expected.test2.txt.id`
- `expected.test2.txt.name`

You can use these to verify the outputs for the two **public** test cases. But it is not enough that you match these! See below.

**Note:** you can drop leading zeroes in the ID.

## writing **effective** test cases

As mentioned earlier, we have only provided **two** public test cases. But we will test with a lot more (an additional **eight** hidden ones making up a total of **ten**). So the question is: 

```
How do you know what the other test cases will include? 
```

The correct answer is: **you won't**! But you can definitely guess. Even better, and the right thing to do, is:

1. write your code in a **defensive** manner &rarr; think of all the issues that can happen _inside_ the four functions, as well as the test cases you may receive from _outside_
2. try to create **as many test cases as you can** &rarr; think of all the ways you can break the code!

This second one is really important. You need to think of yourself as an adversary to yourself -- your main goal is to **break** the sorting algorithm code that you have written! 

Recall that your main "interface" to the program is via these **input text files**. So, how many **different** kinds of input files can you create that tests **your code** (not mine, not the reading/parsing framework). 

The trick is to imagine that you want to **break someone else's sorting code**__+__ in the following instances,

- you have **not seen** their code/algorithm and
- you **have seen** their code algorithm.

(__+__ pick your nemesis and imagine breaking their sorting code!)

Ask yourself questions like,

- what types of assumptions would they make?
- did they forget an edge case? 
- is there a particular order of records that could trip them up?
- what if I don't follow the \<id> \<name> format for the input -- technically this tests my framework but you can try to see what happens
- what else can break that implementation?
- if someone changes the internal implementation, is the test case still useful?

The tests should test the **intention** of the code/spec. Read through this spec carefully. What are the things I have asked for? What have I missed (likely your code has missed as well)?

Create as many tests as you can think of. Put them in the `tests` folder and run `make tests` or run them separately from the command line. See what happens to the outputs. 


## 2-step submission instructions

### Step 1:

You must submit the following via `git`:

1. `sorting_function.c` &rarr; your implementation of the sorting code
2. any additional test cases you have created -- place them in the `tests` folder

**Note:** **DO NOT** modify/submit any other code/files. 

Once you have checked everything in via git, _i.e.,_
- `$> git add`
- `$> git commit -m <message>`
- `$> git pull`
- `$> git push`

### Step 2:

You must submit the following via the **[submit server](https://submit.cs.seas.gwu.edu):**

1. **ONLY** `sorting_function.c`&rarr; your implementation of the sorting code (__Do not submit any other files__)

## important details

- You can receive up to **5% extra credit** on your grade for submitting up to 3 days before the deadline
- **do not** modify any other code/file than the one from the aformentioned instructions
- **remove all `printf()` statements** you have added in the `sorting_function()`. You can use `printf()` calls to help debug your code but before you submit your fina version, please remove/comment them out
- **comment** and **indent** your code properly
- remember that you must `git push` and submit on the submit server for your code to be "submitted" -- make sure that you are on the `main`/`master` branch of your repo
- **do not** use any standard library sorting function! You must implement **your own** code.

If you do not follow the instructions in a precise manner, then you will likely **lose major parts of your grade**!


## grading rubric

|score | phase |
|------|-------|
| `0`  | code does **not compile/build** |
| `+5` | code compiles and builds but **does not run** |
| `+19`| `+9.5` for **each** run (`name`/`id`) of the public test cases (`2` test cases) |
| `+76` | `+9.5` for **each** run (`name`/`id`) of the hidden test cases (`8` test cases) |
|||
|**`100`**| Total Score |
||

<br>

**Note:**

- as mentioned in the [class policies](https://jiezhoucs.github.io/courses/csci-2410/fall-2026/syllabus/) **do not** cheat/copy code and **do not** use any AI/code generation/LLM tools
- if we detect any of this, your grade for this homework will be `0` and you will be reported for an academic integrity violation!


