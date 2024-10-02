//Author Joel Woeste
//Last Modified 10/01/2024

/*


#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <random>

// uncomment and replace the following with your own headers
#include "AVLTree.cpp"

using namespace std;



TEST_CASE("Traversals and Traversal with a Duplicate", "[pre-order][post-order][in-order][traversal][duplicates]") {
    AVL_Tree tree;

    tree.insert("Luke", 12345678);
    tree.insert("Bob", 23456789);
    tree.insert("Luke", 87654321);              //inserting duplicate name with different GatorID
    tree.insert("Charlie", 34567890);

    stringstream outputBuffer;
    streambuf* originalCoutBuffer = cout.rdbuf(outputBuffer.rdbuf());

    tree.printInorder();
    cout.rdbuf(originalCoutBuffer);
    REQUIRE(outputBuffer.str() == "Luke, Bob, Charlie, Luke\n");

    outputBuffer.str("");
    cout.rdbuf(outputBuffer.rdbuf());
    tree.printPreorder();
    cout.rdbuf(originalCoutBuffer);
    REQUIRE(outputBuffer.str() == "Bob, Luke, Luke, Charlie\n");

    outputBuffer.str("");
    cout.rdbuf(outputBuffer.rdbuf());
    tree.remove(2345678); //not a full gatorID
    cout.rdbuf(originalCoutBuffer);
    REQUIRE(outputBuffer.str() == "unsuccessful\n");


    outputBuffer.str("");
    cout.rdbuf(outputBuffer.rdbuf());
    tree.printPostorder();
    cout.rdbuf(originalCoutBuffer);
    REQUIRE(outputBuffer.str() == "Luke, Charlie, Luke, Bob\n");
}




TEST_CASE("Remove + Insert + Level Count", "[remove][insert][level]") {
    AVL_Tree tree;

    stringstream outputBuffer;
    streambuf* originalCoutBuffer = cout.rdbuf(outputBuffer.rdbuf());

    tree.insert("Alice", 00000000);
    tree.insert("Bob", 11111111);
    tree.insert("Charlie", 22222222);

    outputBuffer.str("");
    tree.printLevelCount();
    cout.rdbuf(originalCoutBuffer);
    REQUIRE(outputBuffer.str() == "2\n");

    tree.remove(11111111);
    tree.insert("Carl", 99999999);
    tree.insert("Bob", 88888888);

    outputBuffer.str("");
    cout.rdbuf(outputBuffer.rdbuf());
    tree.printLevelCount();
    cout.rdbuf(originalCoutBuffer);
    REQUIRE(outputBuffer.str() == "3\n");

    cout.rdbuf(originalCoutBuffer);
}



TEST_CASE("Tree Balancing with Insertions and Deletions (All 4 Left & Right)", "[balance][insert][remove]") {
    AVL_Tree tree;

    // Right Rotation
    tree.insert("Carlton", 23456789);
    tree.insert("Beatrice", 34567890);
    tree.insert("Alan", 45678901); // Causes right rotation

    stringstream outputBuffer;
    streambuf* originalCoutBuffer = cout.rdbuf(outputBuffer.rdbuf());
    tree.printInorder();
    cout.rdbuf(originalCoutBuffer);
    REQUIRE(outputBuffer.str() == "Carlton, Beatrice, Alan\n");

    tree.remove(45678901); // No children
    outputBuffer.str("");
    cout.rdbuf(outputBuffer.rdbuf());
    tree.printInorder();
    cout.rdbuf(originalCoutBuffer);
    REQUIRE(outputBuffer.str() == "Carlton, Beatrice\n");

    // Left Rotation
    tree = AVL_Tree();
    tree.insert("Alan", 12345678);
    tree.insert("Beatrice", 23456789);
    tree.insert("Carlton", 34567890); // Causes left rotation

    outputBuffer.str("");
    cout.rdbuf(outputBuffer.rdbuf());
    tree.printInorder();
    cout.rdbuf(originalCoutBuffer);
    REQUIRE(outputBuffer.str() == "Alan, Beatrice, Carlton\n");

    tree.remove(23456789); // One child
    outputBuffer.str("");
    cout.rdbuf(outputBuffer.rdbuf());
    tree.printInorder();
    cout.rdbuf(originalCoutBuffer);
    REQUIRE(outputBuffer.str() == "Alan, Carlton\n");

    // Left-Right Rotation
    tree.insert("Rebecca", 56789012);
    tree.insert("Carl", 67890123); // Causes left-right rotation

    outputBuffer.str("");
    cout.rdbuf(outputBuffer.rdbuf());
    tree.printInorder();
    cout.rdbuf(originalCoutBuffer);
    REQUIRE(outputBuffer.str() == "Alan, Carlton, Rebecca, Carl\n");

    // Right-Left Rotation
    tree = AVL_Tree();
    tree.insert("Carlton", 23456789);
    tree.insert("David", 45678901);
    tree.insert("Alan", 12345678); // Causes right-left rotation

    outputBuffer.str("");
    cout.rdbuf(outputBuffer.rdbuf());
    tree.printInorder();
    cout.rdbuf(originalCoutBuffer);
    REQUIRE(outputBuffer.str() == "Alan, Carlton, David\n");

    tree.remove(45678901); // Two children
    outputBuffer.str("");
    cout.rdbuf(outputBuffer.rdbuf());
    tree.printInorder();
    cout.rdbuf(originalCoutBuffer);
    REQUIRE(outputBuffer.str() == "Alan, Carlton\n");
}



TEST_CASE("Invalid names and gatorIDs", "[insert][invalid]") {
    AVL_Tree tree;

    stringstream outputBuffer;
    streambuf* originalCoutBuffer = cout.rdbuf(outputBuffer.rdbuf());

    tree.insert("Jeremy", 56789101);
    REQUIRE(outputBuffer.str() == "successful\n");
    outputBuffer.str("");

    tree.insert("Alice123", 12345678);
    REQUIRE(outputBuffer.str() == "unsuccessful\n");
    outputBuffer.str("");

    tree.insert("Charlie!", 23456789);
    REQUIRE(outputBuffer.str() == "unsuccessful\n");
    outputBuffer.str("");

    tree.insert("Bob$", 34567890);
    REQUIRE(outputBuffer.str() == "unsuccessful\n");
    outputBuffer.str("");

    tree.insert("ValidName", 1234567);   // Too short
    REQUIRE(outputBuffer.str() == "unsuccessful\n");
    outputBuffer.str("");

    tree.insert("AnotherValidName", 123456789); // Too long
    REQUIRE(outputBuffer.str() == "unsuccessful\n");

    cout.rdbuf(originalCoutBuffer);
}

TEST_CASE("RemoveInOrder and Print Confirmations", "[insert][removeinorder]") {
    AVL_Tree tree;

    tree.insert("Aidan", 12345678);
    tree.insert("Billy", 23456789);
    tree.insert("Parson", 87654321);
    tree.insert("Judy", 34567890);
    tree.insert("Carl",25873246);
    tree.insert("Dahmer", 66547321);


    stringstream outputBuffer;
    streambuf* originalCoutBuffer = cout.rdbuf(outputBuffer.rdbuf());

    tree.printInorder();
    cout.rdbuf(originalCoutBuffer);
    REQUIRE(outputBuffer.str() == "Aidan, Billy, Carl, Judy, Dahmer, Parson\n");

    outputBuffer.str("");
    cout.rdbuf(outputBuffer.rdbuf());
    tree.printPreorder();
    cout.rdbuf(originalCoutBuffer);
    REQUIRE(outputBuffer.str() == "Judy, Billy, Aidan, Carl, Parson, Dahmer\n");

    outputBuffer.str("");
    cout.rdbuf(outputBuffer.rdbuf());
    tree.printPostorder();
    cout.rdbuf(originalCoutBuffer);
    REQUIRE(outputBuffer.str() == "Aidan, Carl, Billy, Dahmer, Parson, Judy\n");


    tree.insert("Samuel", 99999999);
    tree.removeInorder(2);
    tree.removeInorder(1);
    tree.removeInorder(0);

    outputBuffer.str("");
    cout.rdbuf(outputBuffer.rdbuf());
    tree.printInorder();
    cout.rdbuf(originalCoutBuffer);
    REQUIRE(outputBuffer.str() == "Judy, Dahmer, Parson, Samuel\n");

    outputBuffer.str("");
    cout.rdbuf(outputBuffer.rdbuf());
    tree.remove(87654321);
    tree.remove(34567890);
    tree.remove(99999999);
    tree.remove(66547321);

    //Generated 100 Node Names To Test
    vector<pair<string, int>> testData = {
            {"Aidan", 12345678}, {"Billy", 23456789}, {"Parson", 87654321}, {"Judy", 34567890},
            {"Carl", 25873246}, {"Dahmer", 66547321}, {"Emma", 11111111}, {"Olivia", 22222222},
            {"Liam", 33333333}, {"Noah", 44444444}, {"Sophia", 55555555}, {"Mason", 66666666},
            {"Isabella", 77777777}, {"Ethan", 88888888}, {"Avery", 99999999}, {"Mia", 10101010},
            {"James", 11121314}, {"Charlotte", 12131415}, {"Lucas", 13141516}, {"Amelia", 14151617},
            {"Logan", 15161718}, {"Harper", 16171819}, {"Alexander", 17181920}, {"Zoe", 18192021},
            {"Daniel", 19202122}, {"Grace", 20212223}, {"Henry", 21222324}, {"Scarlett", 22232425},
            {"Matthew", 23242526}, {"Addison", 24252627}, {"Jackson", 25262728}, {"Victoria", 26272829},
            {"Sebastian", 27282930}, {"Sofia", 28293031}, {"David", 29303132}, {"Ariana", 30313233},
            {"Gavin", 31323334}, {"Chloe", 32333435}, {"Caleb", 33343536}, {"Natalie", 34353637},
            {"Isaac", 35363738}, {"Lucy", 36373839}, {"Dylan", 37383940}, {"Ella", 38394041},
            {"Gabriel", 39404142}, {"Lily", 40414243}, {"Jordan", 41424344}, {"Layla", 42434445},
            {"Aaron", 43444546}, {"Madison", 44454647}, {"Maverick", 45464748}, {"Brooklyn", 46474849},
            {"Wyatt", 47484950}, {"Sadie", 48495051}, {"Nicholas", 49505152}, {"Kinsley", 50515253},
            {"Luna", 51525354}, {"Ian", 52535455}, {"Penelope", 53545556}, {"Santiago", 54555657},
            {"Alyssa", 55565758}, {"Asher", 56575859}, {"Clara", 57585960}, {"Cole", 58596061},
            {"Aria", 59606162}, {"Xavier", 60616263}, {"Elena", 61626364}, {"Harrison", 62636465},
            {"Nora", 63646566}, {"Adrian", 64656667}, {"Mila", 65666768}, {"Landon", 66676869},
            {"Bella", 67686970}, {"Robert", 68697071}, {"Katherine", 69707172}, {"Jonathan", 70717273},
            {"Peyton", 71727374}, {"Mackenzie", 72737475}, {"Brianna", 73747576}, {"Grayson", 74757677},
            {"Samantha", 75767778}, {"Justin", 76777879}, {"Summer", 77787980}, {"Charles", 78808081},
            {"Naomi", 79818283}, {"Julian", 80828384}, {"Paige", 81838485}, {"Megan", 82848586},
            {"Kayla", 83858687}, {"Kyle", 84868788}, {"Jaxon", 85878889}, {"Kylie", 86888990},
            {"Allison", 87899091}, {"Henry", 88909192}, {"Alana", 89019293}, {"Sebastian", 90192994},
            {"Nina", 91299495}, {"Zachary", 92349596}, {"Bianca", 93495697}, {"Freddie", 94569798},
            {"Tessa", 95697999}, {"Mikayla", 96799900}, {"Ella", 97890001}, {"Paxton", 98900102},
            {"Daphne", 99001003}
    };

    for (const auto& entry : testData) {
        tree.insert(entry.first, entry.second);
    }

    //10 Randomly scattered gatorIDs to remove
    vector<int> randomGatorIDsToRemove = {12345678, 91299495, 11121314, 34567890,
                                         25873246, 50515253, 69707172, 22222222,
                                         86888990, 14151617};


    for (int gatorID : randomGatorIDsToRemove) {
        tree.remove(gatorID);
    }

    outputBuffer.str("");
    cout.rdbuf(outputBuffer.rdbuf());
    tree.printInorder();
    cout.rdbuf(originalCoutBuffer);
    REQUIRE(outputBuffer.str() == "Mia, Emma, Charlotte, Lucas, Logan, Harper, Alexander, Zoe, Daniel, Grace, Henry, Scarlett, Matthew, Billy, Addison, Jackson, Victoria, Sebastian, Sofia, David, Ariana, Gavin, Chloe, Liam, Caleb, Natalie, Isaac, Lucy, Dylan, Ella, Gabriel, Lily, Jordan, Layla, Aaron, Noah, Madison, Maverick, Brooklyn, Wyatt, Sadie, Nicholas, Luna, Ian, Penelope, Santiago, Sophia, Alyssa, Asher, Clara, Cole, Aria, Xavier, Elena, Harrison, Nora, Adrian, Mila, Dahmer, Mason, Landon, Bella, Robert, Jonathan, Peyton, Mackenzie, Brianna, Grayson, Samantha, Justin, Isabella, Summer, Charles, Naomi, Julian, Paige, Megan, Kayla, Kyle, Jaxon, Parson, Allison, Ethan, Henry, Alana, Sebastian, Zachary, Bianca, Freddie, Tessa, Mikayla, Ella, Paxton, Daphne, Avery\n");
}

 */