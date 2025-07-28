// TestVisualStudioCatch2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include "catch_amalgamated.hpp"
#define CATCH_CONFIG_MAIN

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
    printf("The function function_that_throws() threw an error.\n");
}

int globalargc = 0;
const char** globalargv = nullptr;
const char* myname = nullptr;

TEST_CASE("test 1", "[failing]") {
    std::cout << "I will run a test that may or may not fail.\n";
    size_t length = 0;
    bool notme = true;
    int guessed_num = -78;
    if (strcmp(myname, "Aaron") == 0) {
        printf("Hello, Aaron!\n");
        printf("You can type 4 to run a test that succeeds.\n");
        size_t num_i_expect2 = 0;
        std::string realrg = std::string();
        std::getline(std::cin, realrg);
        const char* num_i_expect2_str = realrg.c_str();
        for (int i = 0; i < strlen(num_i_expect2_str); i++) {
            if (num_i_expect2_str[i] < '0' || num_i_expect2_str[i] > '9') {
                printf("Error: Character %d of your input is %c instead of a number.\nI suggest trying 4.\n", i + 1, num_i_expect2_str[i]);
                FAIL();
            }
        }
        //Set input to atoi
        guessed_num = atoi(num_i_expect2_str);
        notme = false;
    }
        
    else if (notme) {
        if (globalargc <= 1) {
            printf("Try running me with an argument.");
            FAIL();
        }
        for (int i = 0; i < strlen(globalargv[1]); i++) {
            if (globalargv[1][i] < '0' || globalargv[1][i] > '9') {
                printf("Error: Character %d of your input is %c instead of a number.\nI suggest trying 4.\n", i + 1, globalargv[1][i]);
                FAIL();
            }
        }
        guessed_num = atoi(globalargv[1]);
        if (guessed_num != 4 and guessed_num != 3) {
            printf("Try 3 as a command-line arg to this command.\n");
        }
        
        if (atoi(globalargv[1]) == 3) {
            printf("Fooled you! :=>)");
        }
        
    }
    if (guessed_num != 4) {
        FAIL("Incorrect number passed. Try again!\n");
    }
    if (globalargc > 1 && notme) {
        printf("Good job guessing the number.\n");
    }
    else {
        printf("Good job entering the right name and the right number.\n");
    }
}

int sofar = 0;
int main(int argc, char *argv[])
{
    Catch::Session session; // There must be exactly one instance of Catch::Session
    std::cout << "Hello World!\n";
    const char* testargv[3] = { argv[0], nullptr, nullptr}; // Initialize testargv with the first argument
    char** realargspassed = argv;
    const char* hi = "hi.";
    //Credit: https://github.com/catchorg/Catch2/blob/devel/docs/own-main.md#top
    globalargc = argc;
    globalargv = testargv;
    printf("What's your name?\n");
    std::string user;
    std::getline(std::cin, user);
    myname = user.c_str();
    if (globalargc > 1) {
        testargv[1] = argv[1];
    }
    printf("Running a test with %d args...\n", argc);
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
