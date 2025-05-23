#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "Patiant.hpp"

class Node_F{
    private:
        Patiant *p; //change to "int id"?
        Node_F *next;
    public:
        Node_F(Patiant *aux);

        friend class Queue;
};

class Queue{
    private:
        Node_F *head;
        Node_F *tail;
        int size;
        int wait_time;

    public: 
        Queue();
        void Enqueue(Patiant *p);
        void Remove(); //talvez mudar o tipo para retornar o valor do elemento retirado?
        bool isEmpty();
        void Finalize();
        Patiant* First();
};

#endif