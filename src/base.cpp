/*
 *  Created by StealthHydra179 and TechyGuy17
 *
 * If you found this code useful please donate here:
 *https://www.patreon.com/GrapheneDev
 *
 * This code is distributed under the GPL 3 license, to read it refer to https://github.com/Graphene-Dev/GrapheneChain/blob/master/LICENSE . if you find an error put it in
 * the errors page on GitHub
 *
 * Thank you
 */

//Include all needed things
#ifdef _WIN32
#include <Windows.h>
#else

#include <unistd.h>

#endif

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include "sha256.h"
#include "blockChain.h"
#include "transaction.h"
#include "block.h"

#include "net/server.h"



#include <time.h>

//set namespace
using namespace std;


BlockChain chain;
Block block;

bool running = true;

void userActions() {
    while (true) {
        cout << "The availible commands are: \n toFile \n newTransacion \n displayChain \n displayCurrentBlock \n";
        cout << "Next action?";
        string input;
        cin >> input;
        if (input == "exit") {
            running = false;
            return;
        }
        if (input == "newTransaction") {
            string from;
            string to;
            int amount;
            cout << "From?";
            cin >> from;
            cout << "To?";
            cin >> to;
            cout << "Amount?";
            cin >> amount;
            Transaction newTransaction(from, to, amount);
            block.addTransaction(newTransaction);
        }
        if (input == "displayChain") {
//            cout << "Chain\n";
            cout << chain.getBlockChain();
        }
        if (input == "toFile") {
//            cout << "Chain\n";
            chain.writeToFile();
            cout<< "Done";
        }
        if (input == "displayCurrentBlock") {
            cout << "Previous Hash: " << block.getPreviousHash() << "\n";
            vector<Transaction> a = block.getTransactions();
            cout << "Transactions:" << "\n";
            for (unsigned int i = 0; i < a.size(); i++)
                cout << i + 1 << ". " << a.at(i).getTransaction() << "\n";
            if (block.foundHash()) {
                cout << "Block Hash: ";
                cout << block.getHash() << "\n";
            }
            stringstream ss;
            ss << hex << block.getDifficulty();
            string diff = ss.str();
            for (int j = 0; j < block.getDiffPadding(); j++) {
                diff = "0" + diff;
            }
            cout << "Difficulty: " << diff << "\n";

            cout << "Found date: " << to_string(block.getTimeFound());
            cout << "\n";
        }
        if (input =="transactiontest") {
            string from;
            string to;
            int amount;
            cout << "From?";
            cin >> from;
            cout << "To?";
            cin >> to;
            cout << "Amount?";
            cin >> amount;
            Transaction newTransaction(from, to, amount);
            cout << newTransaction;
            cout << "\n";//throws serror if amount is a string i think i need to fix that later
        }
    }
}

int main() {
    server *srv = new server("0.0.0.0", 19132);
//    cout << "\033[31;1;7;37mBase Start\033[0m\n";
    cout << "Base Start\n"; //for some reason i cant get colors to work
//    cout << "\033[1;31mbold red text\033[0m\n";
    chain.setProjectName("test");
    cout << chain.getProjectNameHash();

    //Initialize Genesis Block
    block.setPreviousHash("");
    thread thread_obj(userActions);
    chain.addBlock(block);

    //Loop to add blocks when the blockchain allows for it
    while (running) {
        if (chain.getBlockhashed()) {
            chain.pushBlock();
            vector<Block> blocksList = chain.getBlocks();
            string prevHash = "";
            if (!blocksList.empty()) {
                prevHash = chain.getBlocks().at(chain.getBlocks().size()-1).getHash();
                block.setPreviousHash(prevHash);
            }
            chain.addBlock(block);
            block = *new Block;
            block.setDifficulty(chain.getDifficulty());
            block.setDiffPadding(chain.getDiffPadding());
        }
    }
    thread_obj.join();

    cout << "Base End\n";

    return 0;
}
