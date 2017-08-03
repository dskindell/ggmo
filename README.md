# Global GoogleMock Objects #

# README #

Simply add the ggmo.h header to your project and include it in every GoogleTest unit test source file.
The provided API will allow to define mocks for your C or global functions using GoogleMock.

### How do I get set up? ###

1. Add the ggmo.h header to your project.
2. Write your GoogleTest test source file (\*\_test.cpp) and include
    * gtest/gtest.h
    * gmock/gmock.h
    * ggmo.h
    * production\_source.c
3. Define your mocks for your global functions. The functions you wish to mock cannot be defined in 'production\_source.c'.
4. Use GMO\_EXPECT\_CALL and GMO\_ON\_CALL macros just as you would GoogleMock's EXPECT\_CALL and ON\_CALL.
5. Compile your test source and link with the GoogleTest libraries
6. Run test files.
   
In order to use this API (or really any C function mocking API) there are some restrictions you
must adhere to your test framework. Since we're mocking our global functions, the real definitions
cannot be present when linking the tests (due to defintion conflicts). So unlike C++ projects,
you cannot compile all your tests into a single test binary. Also, unlike C++ projects,
you will have #include your production **source** files into your test files (not simply the
production **header** files).

For example, given a project with production source:

    inc/module\_foo.h
    inc/module\_bar.h
    src/module\_foo.c
    src/module\_bar.c

Unit tests for module\_foo.c may mock out all functions definined in module\_bar.c and visa-versa.
However, any functions in module\_foo. cannot be mocked when testing module\_foo.c. Moving functions
to other source files is the best way to de-couple your source for unit testing.

So back to our example, given the production source above, our unit tests file might
be organized like so:

    test/support/googletest/inc/...
    test/support/ggmo.h
    test/module\_foo\_test.cpp
    test/module\_bar\_test.cpp

Which, when build would produce test files:

    bin/module\_foo\_test.exe
    bin/module\_bar\_test.exe

### How do I use the API ###

Ok using the example above let's say module\_foo.c looks like:
    /* module_foo.c */
	#include "module_foo.h"
	#include "module_bar.h"
	
	int foo(int i)
	{
	    return bar(i)+1;
	}

Our test file for module\_foo.c (module\_foo\_test.cpp) migth look like:
    // module_foo_test.cpp
    #include "gtest/gtest.h"
    #include "gmock/gmock.h"
	#include "ggmo.h"
	#include "module_foo.c"
	
	MOCK_GLOBAL_OBJ1(bar, int) {}
	
	class fooTest : public ::testing::Test
	{
	    public:
		    DECL_GLOBAL_FUNC_MOCK(bar);
	};
	
	TEST_F(fooTest, WhenBarReturnsOne)
	{
	    GMO_EXPECT_CALL(bar,(10)).WillOnce(Return(1));
	    EXPECT_THAT(foo(10), Eq(2));
	}
	
Given the example above, there are 3 sections to define using the ggmo API.

1. Declare define mock class.
2. Declare the global mock objects.
3. Define the expectations.

#### How do I define the global mock classes? ####

##### Mocking functions with a return type #####

The general syntax is:

    MOCK\_GLOBAL\_OBJ#(rtn\_type, func, arg\_types...)
	
Where
  - #: the number of arguments the global object takes
  - func: the name of the function being mocked
  - arg\_types: comma-seperated list of parameter types.
  - rtn\_type: return type of 'func'
  
So for a function

    char * my_itoa(char * str, int num, int base)
	
the mock class declaration would be

    MOCK_GLOBAL_OBJ3(char *, my_itoa, char *, int, int) {}

Within the class defintion, you may optionally provided default behavior for the mock object
(following the documentation for GoogleMock). So for the example above if you wanted the function
to, by default, return a NULL pointer you would write:

    MOCK_GLOBAL_OBJ3(char *, my_itoa, char *, int, int)
	{
		ON_CALL(*this, my_itoa(_, _, _)).WillByDefault(ReturnNull());
	}

##### Mocking functions that return 'void' #####

If you mocking function returns void the syntax changes to:

    MOCK_GLOBAL_VOID_OBJ#(func, arg_types...);
	
Which matches except the '\_VOID\_' and the lack of a rtn\_type.

#### How do I declare the global mock objects? ####

In the example above we have:

	class fooTest : public ::testing::Test
	{
	    public:
		    DECL_GLOBAL_FUNC_MOCK(bar);
	};

**DECL\_GLOBAL\_FUNC\_MOCK(func);**
This line is required to instantiate the singeton mock-able classes defined in the previous step.
Skipping this line will result in odd crashes when you run your tests and the mocked function is called by the SUT.

There are 3 forms this declaration have have:

    DECL_GLOBAL_FUNC_MOCK(func); // Declare a naggy GoogleMock mock object.
    DECL_NICE_GLOBAL_FUNC_MOCK(func); // Declare a nice GoogleMock mock object.
    DECL_STRICT_GLOBAL_FUNC_MOCK(func); // Declare a strict GoogleMock mock object.
	
See the GoogleMock documentation for an explaination of the 3 types of mock objects.

Another option is to group all the functions of file/module into helper files and have your test fixtures
inheirt from these helper classes. This way you define your test modules and avoid declaring your mock
objects repeatedly. A simple setup would be:

    // mock_module_bar.h
	#include "ggmo.h"
	
	MOCK_GLOBAL_OBJ1(int, bar, int) {}
	MOCK_GLOBAL_VOID_OBJ2(other_bar_func, int, char*) {}
	
	class BarMocker
	{
	    public:
		DECL_GLOBAL_FUNC_MOCK(bar);
		DECL_GLOBAL_FUNC_MOCK(other_bar_func);
	};
	class NiceBarMocker
	{
	    public:
		DECL_NICE_GLOBAL_FUNC_MOCK(bar);
		DECL_NICE_GLOBAL_FUNC_MOCK(other_bar_func);
	};
	class StrictBarMocker
	{
	    public:
		DECL_STRICT_GLOBAL_FUNC_MOCK(bar);
		DECL_STRICT_GLOBAL_FUNC_MOCK(other_bar_func);
	};
	
Now the module\_foo\_test.cpp from above would look like this:
    // module_foo_test.cpp
    #include "gtest/gtest.h"
    #include "gmock/gmock.h"
	#include "mock_module_bar.h"
	#include "module_foo.c"
	
	class fooTest
	    : public ::testing::Test
		, BarMocker
	{
	    public:
	};
	
	TEST_F(fooTest, WhenBarReturnsOne)
	{
	    GMO_EXPECT_CALL(bar,(10)).WillOnce(Return(1));
	    EXPECT_THAT(foo(10), Eq(2));
	}
The limitation here is you cannot change the mock type (naggy/strict/nice) of individual functions of
bar (i.e. nice bar() and naggy other\_bar\_func()).

#### How do I define the global mock expectations? ####

Defining the expectations of a GMO mock object is the same as with classic GoogleMock objects with 3 exceptions:
1. You must prefix the EXPECT/ON\_CALL macro with 'GMO\_'
2. There is no object to reference as the first parameter (well there is but is not obvious).
2. You must add an extra comma between the function name and the parameter list.

So if the GoogleMock expectation looked like:

    EXPECT_CALL(my_obj, foo(_, Eq(1))).WillOnce(Return(1));
	
The equivalent GMO expectation would be:

    GMO_EXPECT_CALL(foo, (_,Eq(1))).WillOnce(Return(1));

To help understand this, or if you do not want to use the GMO\_ or extra comma, the longer version would be:

    EXPECT_CALL(GMO(foo), foo(_, Eq(1))).WillOnce(Return(1));
	
Where GMO(foo) gets the singleton object that holds the mock for foo().

### What limitations are there compared to classic GoogleMock objects ###

1. Cannot declare multiple global mock objects for functions with optional parameters. You can provide at
most 1 global mock class signature for each function/symbol.

### Who do I talk to? ###

* Author: David Skindell <gmskindell@hotmail.com> 
