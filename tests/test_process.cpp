#define CATCH_CONFIG_MAIN
#include "catch.hpp"

//the files being tested
#include "process.cpp"
#include "parser.cpp"

//Below includes are here for while writing code so vscode can check syntax
// #include "process.h" 
// #include "parser.h"

#include <iostream>

//CHECKING ALL PARTS OF PARSING STRING: "ls|ps aux | du -d 1 -h" into a Process Object Vector
TEST_CASE( "Test Parser: Number of Processes", "[classic]") {
    GIVEN("Test Parser: Number of Processes") {
        std::string str = "ls|ps aux | du -d 1 -h";
        CHECK( parseString(str).size() == 3);
    }
}
TEST_CASE( "Test Parser: Process Commands", "[classic]") {
    GIVEN("Test Parser: Process Commands") {
        std::string str = "ls|ps aux | du -d 1 -h";
        CHECK( parseString(str).at(0).getCommand() == "ls");
        CHECK( parseString(str).at(1).getCommand() == "ps");
        CHECK( parseString(str).at(2).getCommand() == "du");
    }
}
TEST_CASE( "Test Parser: Number of Arguments", "[classic]") {
    GIVEN("Test Parser: Number of Arguments") {
        std::string str = "ls|ps aux | du -d 1 -h";
        CHECK( parseString(str).at(0).getArguments().size() == 0);
        CHECK( parseString(str).at(1).getArguments().size() == 1);
        CHECK( parseString(str).at(2).getArguments().size() == 3);
    }
}
TEST_CASE( "Test Parser: Process Arguments for Process #2", "[classic]") {
    GIVEN("Test Parser: Process Arguments for Process #2") {
        std::string str = "ls|ps aux | du -d 1 -h";
        CHECK( parseString(str).at(1).getArgument(0) == "aux");
    }
}
TEST_CASE( "Test Parser: Process Arguments for Process #3", "[classic]") {
    GIVEN("Test Parser: Process Arguments for Process #3") {
        std::string str = "ls|ps aux | du -d 1 -h";
        CHECK( parseString(str).at(2).getArgument(0) == "-d");
        CHECK( parseString(str).at(2).getArgument(1) == "1");
        CHECK( parseString(str).at(2).getArgument(2) == "-h");
    }
}
TEST_CASE( "Test Parser: Check for Missmatched Quotes - NONE", "[classic]") {
    GIVEN("Test Parser: Check for Missmatched Quotes - NONE") {
        std::string str = "ls|ps aux | du -d 1 -h";
        CHECK_NOTHROW(parseString(str));
    }
}

// (2) CHECKING ALL PARTS OF PARSING STRING: "ls \"Welcome to | the jungle\" > ps the aux cord" into a Process Object Vector
TEST_CASE( "Test Parser 2: Number of Processes", "[classic]") {
    GIVEN("Test Parser 2: Number of Processes") {
        std::string str = "ls \"Welcome to | the jungle\" > ps the aux cord";
        CHECK( parseString(str).size() == 2);
    }
}
TEST_CASE( "Test Parser 2: Process Commands", "[classic]") {
    GIVEN("Test Parser 2: Process Commands") {
        std::string str = "ls \"Welcome to | the jungle\" > ps the aux cord";
        CHECK( parseString(str).at(0).getCommand() == "ls");
        CHECK( parseString(str).at(1).getCommand() == "ps");
    }
}
TEST_CASE( "Test Parser 2: Number of Arguments", "[classic]") {
    GIVEN("Test Parser 2: Number of Arguments") {
        std::string str = "ls \"Welcome to | the jungle\" > ps the aux cord";
        CHECK( parseString(str).at(0).getArguments().size() == 1);
        CHECK( parseString(str).at(1).getArguments().size() == 3);
    }
}
TEST_CASE( "Test Parser 2: Process Arguments for Process #2", "[classic]") {
    GIVEN("Test Parser 2: Process Arguments for Process #2") {
        std::string str = "ls \"Welcome to | the jungle\" > ps the aux cord";
        CHECK( parseString(str).at(0).getArgument(0) == "Welcome to | the jungle");
    }
}
TEST_CASE( "Test Parser 2: Process Arguments for Process #3", "[classic]") {
    GIVEN("Test Parser 2: Process Arguments for Process #3") {
        std::string str = "ls \"Welcome to | the jungle\" > ps the aux cord";
        CHECK( parseString(str).at(1).getArgument(0) == "the");
        CHECK( parseString(str).at(1).getArgument(1) == "aux");
        CHECK( parseString(str).at(1).getArgument(2) == "cord");
    }
}
TEST_CASE( "Test Parser 2: Check for Missmatched Quotes - NONE", "[classic]") {
    GIVEN("Test Parser 2: Check for Missmatched Quotes - NONE") {
        std::string str = "ls \"Welcome to | the jungle\" > ps the aux cord";
        CHECK_NOTHROW(parseString(str));
    }
}

//Test for recognizing mismatched Quotes
TEST_CASE( "Test Parser 3: Check for Missmatched Quotes - TRUE", "[classic]") {
    GIVEN("Test Parser 3: Check for Missmatched Quotes - TRUE") {
        std::string str = "ls \"Welcome to | the jungle > ps the aux cord";
        CHECK_THROWS_WITH( parseString(str), "Mismatched Quotes");
    }
}

//Tests for Process Class
TEST_CASE( "Test Process: Set and Get Command") {
    GIVEN("Test Process: Set and Get Command") {
        Process p;
        p.setCommand("correctCommand");
        CHECK(p.getCommand() == "correctCommand");
    }
}
TEST_CASE( "Test Process: Add and Get Arguments") {
    GIVEN("Test Process: Add and Get Arguments") {
        Process p;
        p.setCommand("correctCommand");
        p.addArgument("argy");
        p.addArgument("argie");
        CHECK(p.getArguments().size() == 2);
        CHECK(p.getArgument(0) == "argy");
        CHECK(p.getArgument(1) == "argie");
    }
}
TEST_CASE( "Test Process: Get all Args") {
    GIVEN("Test Process: Get all Args") {
        Process p;
        p.setCommand("correctCommand");
        p.addArgument("paramy");
        p.addArgument("paramie");
        CHECK(p.getArguments().size() == 2);
        CHECK(p.getArguments().at(0) == "paramy");
        CHECK(p.getArguments().at(1) == "paramie");
    }
}
TEST_CASE( "Test Process: Copy Constructor") {
    GIVEN("Test Process: Copy Constructor") {
        Process one;
        one.setCommand("grep");
        one.addArgument("first");
        one.addArgument("second");
        one.addArgument("third");
        Process copy(one);
        CHECK(copy.getCommand() == "grep");
        CHECK(copy.getArguments().size() == 3);
        CHECK(copy.getArgument(0) == "first");
        CHECK(copy.getArgument(1) == "second");
        CHECK(copy.getArgument(2) == "third");
    }
}
TEST_CASE( "Test Process: Clear Process") {
    GIVEN("Test Process: Clear Process") {
        Process p;
        p.setCommand("correctCommand");
        p.addArgument("argy");
        p.addArgument("arie");
        p.clear();
        CHECK(p.getCommand() == "");
        CHECK(p.getArguments().size() == 0);
    }
}


