#include <catch.hpp>
#include <sstream>

#include "rbt.hpp"

TEST_CASE("creating tree")
{
    tree_t <int> tree;
    REQUIRE(tree.root() == nullptr);
}

TEST_CASE("insert and print tree int")
{
    tree_t <int> tree;
    tree.insert(3);
	tree.insert(4);
	tree.insert(2);
	tree.insert(1);
	tree.insert(5);
    std::string result{ "------5\n"
                        "----4\n"
                        "--3\n"
                        "----2\n"
                        "------1\n" };
	std::ostringstream ostream;
    tree.print(ostream,0,tree.root());
    REQUIRE(ostream.str() == result);
}

TEST_CASE("find tree int")
{
    tree_t <int> tree;
    tree.insert(3);
	tree.insert(4);
	tree.insert(2);
	tree.insert(1);
	tree.insert(5);
   

    REQUIRE(tree.find(1) == true);
    REQUIRE(tree.find(2) == true);
    REQUIRE(tree.find(5) == true);
    REQUIRE(tree.find(7) == false);
    REQUIRE(tree.find(0) == false);
}

TEST_CASE("find tree double")
{
    tree_t <double> tree;

    tree.insert(3.3);
	tree.insert(4.4);
	tree.insert(2.2);
	tree.insert(1.1);
	tree.insert(5.5);
   
    REQUIRE(tree.find(1.1) == true);
    REQUIRE(tree.find(2.2) == true);
    REQUIRE(tree.find(5.5) == true);
    REQUIRE(tree.find(7.7) == false);
    REQUIRE(tree.find(0) == false);
}

TEST_CASE("equal")
{
	tree_t<int> tree1;
	tree_t<int> tree2 {3 , 4 , 2 , 1 , 5};
	tree1.insert(3);
	tree1.insert(4);
	tree1.insert(2);
	tree1.insert(1);
	tree1.insert(5);
	REQUIRE(tree1==tree2);
}

TEST_CASE("new0")
{
	tree_t<int> tree {10 , 85 , 15};
	
	std::string result{	"----85\n"
                        	"--15\n"
                        	"----10\n"};
	
	std::ostringstream ostream;
    	tree.print(ostream,0,tree.root());
    	REQUIRE(ostream.str() == result);
}

TEST_CASE("new")
{
	tree_t<int> tree {10 , 85 , 15 , 70 , 20 , 60 , 30 , 50 , 65 , 80 , 90 , 40 , 5 , 55};
	
	std::string result{	"--------90\n"
                        	"------85\n"
                        	"--------80\n"
                        	"----70\n"
                        	"--------65\n"
			  	"------60\n"
			  	"----------55\n"
			  	"--------50\n"
			  	"----------40\n"
			  	"--30\n"
			  	"------20\n"
			  	"----15\n"
			  	"------10\n"
			  	"--------5\n"};
	
	std::ostringstream ostream;
    	tree.print(ostream,0,tree.root());
    	REQUIRE(ostream.str() == result);
}
