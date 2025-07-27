// TestVisualStudioCatch2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
//Credit: Google
#define CATCH_CONFIG_RUNNER

#include "catch_amalgamated.hpp"
#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_RUNNER

void function_that_throws() {
	throw std::runtime_error("This is an exception from function_that_throws.");
}

TEST_CASE("test 2", "[succeding]") {
	std::cout << "I will run a succeeding test.\n";
	CHECK(1 + 1 == 2);
	// You can add more checks here if needed
	CHECK(2 + 2 == 4); // Example of another check
	// If you want to test exceptions, you can use REQUIRE_THROWS or similar macros
	REQUIRE_THROWS(function_that_throws());
	printf("Test 2 passed successfully.\nThe function function_that_throws() threw an error.\n");
}

int globalargc = 0;
char** globalargv = nullptr;

TEST_CASE("test 1", "[failing]") {
    std::cout << "I will run a test that may or may not fail.\n";
    if (globalargc <= 1) {
		std::cout << "No command-line argument provided.\n";
        FAIL();
    }
    else {
		int lentgh = strlen(globalargv[1]);
		for (int i = 0; i < lentgh; i++) {
			if (globalargv[1][i] < '0' || globalargv[1][i] > '9') {
				printf("Error: Character %d of argument 1 is %c instead of a number.\nI suggest trying 3.\n", i+1, globalargv[1][i]);
				FAIL();
			}
		}
		printf("Try 3 as a command-line arg to this command.\n");
		if (atoi(globalargv[1]) == 3) {
			printf("Fooled you! :=>)");
		}
		if (atoi(globalargv[1]) != 4) {
			FAIL();	
		}
    }
}

int sofar = 0;
int main(int argc, char *argv[])
{
	Catch::Session session; // There must be exactly one instance of Catch::Session
    std::cout << "Hello World!\n";
    char* testargv[2] = { argv[0], nullptr}; // Initialize testargv with the first argument
    char** realargspassed = argv;
    printf("Running a test with %d args...\n", argc);
    const char* hi = "hi.";
    //Credit: https://github.com/catchorg/Catch2/blob/devel/docs/own-main.md#top
	globalargc = argc;
    globalargv = realargspassed;
    int numfailed = session.run(1, testargv);
    printf("Really. I failed %s tests.\n", numfailed == 0 ? "no" : "some");
    return numfailed;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
