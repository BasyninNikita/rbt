#include <catch.hpp>
#include <sstream>
#include "rbt.hpp"
TEST_CASE("creating tree")
{
    tree_t<int> tree;
    REQUIRE(tree.root()==nullptr);
}
TEST_CASE("add")
{
    tree_t<int> tree;
    tree.insert(2);
    tree.insert(1);
    tree.insert(3);
    tree.insert(4);
    std::string output {
            "------4\n"
        "---3\n"
        "2\n"
        "---1\n"
    };
    std::ostringstream ostream;
    tree.print(ostream,0,tree.root());
    REQUIRE( ostream.str() == output );
}
TEST_CASE("?")
{
    tree_t<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    REQUIRE( tree.find(6)==false );
    REQUIRE( tree.find(2)==true );
}
TEST_CASE("op+?")
{
    tree_t<int> tree;
    tree.oper1('+',2);
    tree.oper1('+',1);
    tree.oper1('+',3);
    std::string output{
        "---3\n"
        "2\n"
        "---1"
    };
    std::ostringstream ostream;
    tree.oper2('?',2,ostream);
    REQUIRE( ostream.str()== "true" );
    std::ostringstream ostream1;
    tree.oper2('?',5,ostream1);
    REQUIRE( ostream1.str()== "false" );
}
TEST_CASE("op+=")
{
    tree_t<int> tree;
    tree.oper1('+',2);
    tree.oper1('+',1);
    tree.oper1('+',3);
    std::string output{
        "---3\n"
        "2\n"
        "---1\n"
    };
    std::ostringstream ostream;
    tree.oper2('=',0,ostream);
    REQUIRE( ostream.str()== output );
}
TEST_CASE("ravenstvo")
{
    tree_t<int> tree1;
    tree_t<int> tree2;
    tree_t<int> tree3;
    tree1.oper1('+',2);
    tree1.oper1('+',1);
    tree1.oper1('+',3);
    tree2.oper1('+',2);
    tree2.oper1('+',1);
    tree2.oper1('+',3);
    tree3.oper1('+',5);
    tree3.oper1('+',2);
    tree3.oper1('+',7);
    REQUIRE(tree1==tree2);
    REQUIRE(!(tree1==tree3));
}
