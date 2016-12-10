#ifndef STACK_H
#define STACK_H

#include "Cubies.h"

#include <memory>

#define BlockSize 10000

using namespace std;

struct DataBlock
{
    shared_ptr<Cubies> node;
    int distance;

    DataBlock() {}

    DataBlock(shared_ptr<Cubies> cbs, int dist)
    {
        node = cbs;
        distance = dist;
    }
};

class Stack
{

    struct Block
    {
        struct Block *leftlink;
        DataBlock data[BlockSize];
    };

    Block* rightblock;
    int rightindex; /* index into last block, points to last element */

public:
    long length;


    Stack()
    {
        length = 0;
        rightblock = nullptr;
    }

    bool push(shared_ptr<Cubies> cbs, int dist)
    {
        if (rightblock == nullptr)
        {
            /* initialize */
            rightblock = new Block;
            rightblock->leftlink = nullptr;
            length = 0;
            rightindex = -1;
        }
        else if (rightindex == BlockSize-1)
        {
            /* Needs a new block */
            Block* newblock = new Block;
            newblock->leftlink =rightblock;
            rightblock = newblock;
            rightindex = -1;
        }
        length++;
        rightindex++;
        /* Now copy data in */
        rightblock->data[rightindex].node = cbs;
        rightblock->data[rightindex].distance = dist;

        return true;
    }

    bool empty()
    {
        if (length == 0) return true;
        return false;
    }

    DataBlock top()
    {
        return rightblock->data[rightindex];
    }

    bool pop()
    {
        /* Just erase the last element */
        length--;
        if (rightindex == 0)
        {
            /* Freeing an entire block */
            Block* oldblock = rightblock;
            rightblock = oldblock->leftlink;
            delete oldblock;
            rightindex = BlockSize - 1;
        }
        else
        {
            rightindex--;
        }
        return true;
    }

    int size()
    {
        return length;
    }
};

#endif // STACK_H
