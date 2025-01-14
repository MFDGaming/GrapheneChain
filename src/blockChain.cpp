#include "blockChain.h"
#include <iostream>
#include <string>
#include <vector>
#include "block.h"
#include "transaction.h"
#include <algorithm>
#include <ctime>
#include <fstream>
using namespace std;

BlockChain::BlockChain() {
    projectName = "";
    projectNameHash = sha256(projectName);
}



void BlockChain::setDifficulty(unsigned long long diff) {
    difficulty = diff;
}

void BlockChain::hashCurrentBlock() {
    if (!blockHashed && !ready) {
        currentHashedBlock.getHash();                       //this line might be the problem
        blockHashed = true;
    }
}

void BlockChain::setTargetTime(int target) {
    targetTime = target;
}

int BlockChain::getTargetTime() {
    return targetTime;
}

unsigned long long BlockChain::getDifficulty() {
    return difficulty;
}

Block BlockChain::getCurrentBlockHashed() {
    return currentHashedBlock;
}

bool BlockChain::getBlockhashed() {
    return blockHashed;
}

void BlockChain::pushBlock() {
    if (blockHashed && !ready) {
        time_t latest = currentHashedBlock.getTimeFound();
        double timeDifference;
        if (!chain.empty()) {
            time_t previous = chain.back().getTimeFound();

             timeDifference = difftime(latest, previous); //in seconds
        } else {
            timeDifference = 10;
        }
        chain.push_back(currentHashedBlock);

//        setDifficulty();

        if (timeDifference < 0.1) timeDifference = 0.1;
//        cout << timeDifference << "\n";
        if (targetTime > timeDifference)
            setDifficulty(getDifficulty()-(adjustmentFactor*((timeDifference/targetTime))));
        if (targetTime < timeDifference)
            setDifficulty(getDifficulty()+(adjustmentFactor*((timeDifference/targetTime))));
        while (getDifficulty() > 10) {
            if (numZerosAtStart > 0) {
                numZerosAtStart--;
                setDifficulty(getDifficulty()/10);
            }
        }
        while (getDifficulty() < 1) {
            numZerosAtStart++;
            setDifficulty(getDifficulty()+10);
        }

        addToFile(currentHashedBlock);


        ready = true;
    }
}

void BlockChain::addBlock(Block newBlock) {
    blockHashed = false;
    ready = false;
    currentHashedBlock = newBlock;
//    cout << "set success\n";
    hashCurrentBlock();
}

void BlockChain::removeBlock() {
    cout << "Not implemented yet \n";
}

bool BlockChain::verifyChain(int start, int end) {
    if (end == -1) {
        end = chain.size();
    }
    Block *blocks = new Block[chain.size()];
    int l = 0;
    for (Block const &i: chain) {
        blocks[l++] = i;
    }

    string currentHash = blocks[start].getHash();
    for (int i = start + 1; i < end; i++) {
        if (currentHash != blocks[i].getPreviousHash()) {
            return false;
        }
        if (!blocks[i].foundHash()) {
            return false;
        }
        currentHash = blocks[i].getHash();
    }
    return true;
}

//void BlockChain::setProjectNameHash(string projectName, string projectNameHash) {
//    this->projectName = "GrapheneChain"; //Change this to your cryptos name
//    this->projectNameHash = sha256(projectName);
//}
//
//void BlockChain::setProjectNameHash(string projectNameHash) {
//    this->projectNameHash = projectNameHash;
//}
//
//string BlockChain::getProjectNameHash() {
//    return projectNameHash;
//}

vector<Block> BlockChain::getBlocks() {
    vector<Block> vecOfStr(chain.begin(), chain.end());
    return vecOfStr;
}

int BlockChain::getDiffPadding() {
    return numZerosAtStart;
}

void BlockChain::addToFile(Block currentlyHashedBlock) {
    ofstream file("out/chain/"+getProjectNameHash()+".txt",ios::out | ios::trunc);
    //clear file


    // output to the file

    file.close();
}

void BlockChain::writeToFile() {
    ofstream file;
    cout << "File OUT\n";
    file.open("out/chain/"+getProjectNameHash()+".txt",ios::out | ios::trunc);
    file << toString();


    // output to the file

    file.close();
}

void BlockChain::resetLocalGetFromFile(string name) {
    resetMem();
}

void BlockChain::resetChain() {
    ofstream file("out/chain/"+getProjectNameHash()+".txt");

    file.close();
}

void BlockChain::resetMem() {}

void BlockChain::printFile() {
    string currentText;
    ifstream readFile("out/chain/"+getProjectNameHash()+".txt");
    while (getline (readFile, currentText)) {
        // Output the text from the file
        cout << currentText;
    }
    readFile.close();
}

BlockChain BlockChain::readFile() {
    BlockChain blockchain;
    return blockchain;
}

void BlockChain::setProjectName(string newProjectName) {
    this->projectName = newProjectName;
    projectNameHash = sha256(newProjectName);
}

string BlockChain::getProjectName() {
    return projectName;
}

string BlockChain::getProjectNameHash() {
    return projectNameHash;
}

string BlockChain::toString() {
    string output = "BlockChain\n";
    vector<Block> a = getBlocks();
//            cout << "project hash: " << chain.getProjectNameHash() << "\n";
    for (unsigned int i = 0; i < a.size(); i++) {
        Block current = a.at(i);
        output += current.getBlock();
    }
    return output;
}

string BlockChain::getBlockChain() {
    return toString();
}

ostream& operator<<(ostream& out, BlockChain& b) {
    return out << b.toString();
}
