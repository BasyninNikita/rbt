#include <catch.hpp>
#include <sstream>

#include "rbt.hpp"

TEST_CASE("creating tree")
{
    tree_t <int> tree;
    REQUIRE(tree.root() == nullptr);
}

TEST_CASE("+")
{
    tree_t <int> tree;
    tree.insert(6);
    tree.insert(8);
    tree.insert(4);
    tree.insert(2);
    tree.insert(10);
    std::string result{ "------10\n"
                        "---8\n"
                        "6\n"
                        "---4\n"
                        "------2\n" };
	std::ostringstream ostream;
    tree.print(ostream,0,tree.root());
    REQUIRE(ostream.str() == result);
}

TEST_CASE("?")
{
    tree_t <int> tree;
    tree.insert(2);
	tree.insert(4);
	tree.insert(6);
	tree.insert(8);
	tree.insert(10);
    REQUIRE(tree.find(4) == true);
    REQUIRE(tree.find(2) == true);
    REQUIRE(tree.find(8) == true);
    REQUIRE(tree.find(7) == false);
    REQUIRE(tree.find(0) == false);
}
TEST_CASE("==")
{
	tree_t<int> tree1;
	tree_t<int> tree2 {6 , 4 , 2 , 10 , 8};
	tree1.insert(6);
	tree1.insert(4);
	tree1.insert(2);
	tree1.insert(10);
	tree1.insert(8);
	REQUIRE(tree1==tree2);
}
TEST_CASE("new")
{
	tree_t<int> tree {2 , 17 , 3 , 4 , 14 , 10 , 13 , 12 , 6 , 16 , 18 , 1 , 11 , 8};
	
	std::string result{	"---------18\n"
				"------17\n"
				"---------16\n"
				"---14\n"
				"---------13\n"
				"------12\n"
				"---------11\n"
				"10\n"
				"---------8\n"
				"------6\n"
				"---------4\n"
				"---3\n"
				"------2\n"
			        "---------1\n"
			  };
	std::ostringstream ostream;
    	tree.print(ostream,0,tree.root());
    	REQUIRE(ostream.str() == result);
}
TEST_CASE("balance")
{
    tree_t<int> tree {6 , 4 , 8 , 2 , 10};
    std::string result{ "------10\n"
                        "---8\n"
                        "6\n"
                        "---4\n"
                        "------2\n" };
    std::ostringstream ostream;
    tree.print(ostream,0,tree.root());
    REQUIRE(ostream.str() == result);
}
TEST_CASE("removing")
{
    tree_t<int> tree {6 , 4 , 8 , 2 , 10};
    tree.remove(8);
    std::string result{ "---10\n"
                        "6\n"
                        "---4\n"
                        "------2\n" };
    std::ostringstream ostream;
    tree.print(ostream,0,tree.root());
    REQUIRE(ostream.str() == result);
}
TEST_CASE("removing2")
{
    tree_t<int> tree {8 , 4 , 6 , 2 , 10};
    tree.remove(4);
    std::string result{ "------10\n"
                        "---8\n"
                        "6\n"
                        "---2\n" };
    std::ostringstream ostream;
    tree.print(ostream,0,tree.root());
    REQUIRE(ostream.str() == result);
}
TEST_CASE("removing_with_red_bro")
{
    tree_t<int> tree {4 , 2 , 6 , 7 , 5 , 3 , 1 };
    tree.remove(6);
    std::string result{ "---7\n"
                        "------5\n"
                        "4\n"
	    		"------3\n"
                        "---2\n" 
		      	"------1\n"};
    std::ostringstream ostream;
    tree.print(ostream,0,tree.root());
    REQUIRE(ostream.str() == result);
}
TEST_CASE("removing_with_black_bro_and_son")
{
    tree_t<int> tree { 4 , 2 , 8 , 10};
    tree.remove(10);
    tree.remove(2);
    std::string result{ "---8\n"
                        "4\n"};
    std::ostringstream ostream;
    tree.print(ostream,0,tree.root());
    REQUIRE(ostream.str() == result);
}
TEST_CASE("removing(black_bro_red_son)")
{
	tree_t<int> tree {8 , 4 , 6 , 2 , 10};
    tree.remove(4);
    std::string result{ "------10\n"
                        "---8\n"
                        "6\n"
                        "---2\n" };
    std::ostringstream ostream;
    tree.print(ostream,0,tree.root());
    REQUIRE(ostream.str() == result);    
}
