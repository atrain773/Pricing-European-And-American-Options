#pragma once

#include <iostream>
#include <math.h>
#include <stdlib.h>

#include <chrono>
using namespace std::chrono;

// To Implement (Jiaqi)

class CrrBinomial{
    public:
    //constructor
    CrrBinomial(char option, float K, float T, float S_0, float v, float r, float q, float N, char exercise);

    float GetPrice();//output the price
    //void GetTime(auto begin,auto stop);//output the running time
    
    private: 
    //type: time - node(n,j)
    struct time{
        int n;//time n * delta
        int j;//the number of up moves in the stock price
    };

    //type: node
    struct node{
        time t;
        float american;//use to compute american option price
        float price;//Current stock price at the time
        struct node* pre_up;//pre node contains higher price than current node
        struct node* pre_down;//pre node contains lower price than current node
        struct node* up;//up node
        struct node* down;//down node

    };

    //CreateNode
    struct node* createNode(float data, int n, int j){
        struct node* newNode = (struct node*)malloc(sizeof(struct node));
        if(newNode == NULL) return NULL;
        newNode->price = data;
        newNode->american = -1;
        newNode->t.n = n;
        newNode->t.j = j;
        newNode->pre_up = NULL;
        newNode->pre_down = NULL;
        newNode->up = NULL;
        newNode->down = NULL;
        return newNode;
    };

    //functions
    void buildTree(node* N);//build the binomial tree
    void freeTree(node* N);//free each node after used

    void American(node* N);//return call or put price of American Option
    void European(node* N);//return call or put price of European Option

    //unsigned long long nCr(int N, int R);//return C choose R
    float nCr(int N, int R);

    float max(float a, float b);//return larger number

    //parameters
    char c_p;//call(C) or put(P)
    char A_E;//American option(A) or European option(E)

    float Strike;//Strike price

    int step;
    float delta;//divide [0,T] into N euqal intercals

    float r_;//free interest rate

    float u;//extent of an increase of stock price
    float d;//extent of an decrease of stock price

    float p;//risk neutrual probability
    float p_;//(1-p)

    float option_price;
    //float option_price = 0.0;//final option price

    struct node* start;//head of the tree
    struct node* end;//Node(N,0)

    int test;
    //int test = 1;

    struct node* temp;
    struct node*  temp_;
};