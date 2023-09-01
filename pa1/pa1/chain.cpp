#include "chain.h"
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <float.h>

// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain() {
  this->clear();
}

/**
 * Inserts a new node after the node pointed to by p in the
 * chain (so p->next is the new node) and returns a pointer to
 * the newly created node.
 * If p is NULL, inserts a new head node to the chain.
 * This function **SHOULD** create a new Node and increase length_.
 *
 * @param p = The new node should be pointed to by p->next.
 *            If p is NULL, the new node becomes the head of the chain.
 * @param ndata = The data to be inserted.
 */
Chain::Node * Chain::insertAfter(Node * p,const Block &ndata) {
  /* your code here */
  if(p == NULL)
  {
    this->head_ = new Node(ndata);
    this->head_->next = NULL;
    this->head_->prev = NULL;
    this->length_++;
    return this->head_;
  } 
  
  else if(p->next != NULL){
    Node *front = p->next;
    p->next =new Node(ndata);
    p->next->next = front;
    p->next->prev = p;
    front->prev = p->next;
    this->length_++;
    return p->next;
  }
  else{
    p->next = new Node(ndata);
    p->next->next = NULL;
    p->next->prev = p;
    this->length_++;
    return p->next;
  }
}


void Chain::swap(Node *p, Node *q) {
  if(p==q)return;
  if(p== NULL || q==NULL) return;
  Node *pprev = p->prev;
  Node *pnext = p->next;
  Node *qprev = q->prev;
  Node *qnext = q->next;
  

  if (p->next == q){
    q->prev = pprev;
    if(pprev!= NULL){
      pprev->next = q;
    }
    else {
      head_=q;
    }
    p->next = qnext;
    if(qnext != NULL){
      qnext->prev = p;
    }
    p->prev = q;
    q->next = p;
  }
  else if (q->next == p){
    p->prev = qprev;
    if(qprev!= NULL){
      qprev->next = p;
    }
    else{
      head_=p;
    }
    q->next = pnext;
    if(pnext != NULL){
      pnext->prev = q;
    }
    q->prev = p;
    p->next = q;
  }
  else{
    if(qprev != NULL){
      qprev->next = p;
    }
    else{
      head_=p;
    }
    p->prev = qprev;
    if(pprev != NULL){
      pprev->next = q;
    }
    else{
      head_=q;
    }
    q->prev = pprev;
    if(qnext != NULL){
      qnext->prev = p;
    }
    p->next = qnext;
    if(pnext !=NULL){
      pnext->prev = q;
    }
    q->next = pnext;
  }
}


/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::clear() {
  /* your code here */
  Node *temp = this->head_;
  if(temp == NULL) return;
  while(temp->next != NULL){
     temp = temp->next; //temp points to last;
  }
  while(temp != this->head_){//deletes starting from last
    temp = temp ->prev;
    temp->next->prev = NULL;
    temp->next->next = NULL;
    temp->next = NULL;
    delete temp->next;
  }
  this->length_ = 0;
  head_->next = NULL;
  head_ = NULL;
  delete head_;
}

/**
 * Makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
 // other -> this
void Chain::copy(Chain const &other) {
  /* your code here */
  //Chain *newChain = new Chain();
  if(other.head_ == NULL){
    this->head_ = NULL;
    this->length_ = 0;
    return;
  }
  Node *head = new Node(other.head_->data);
  this->head_ =head;
  this->length_ =1;
  Node *otherFirst = other.head_->next;
  Node *newTemp = head;
  while(otherFirst != NULL){
    this->insertAfter(newTemp, otherFirst->data);
    otherFirst = otherFirst->next;
    newTemp = newTemp->next;
  }
}


/* Modifies the current chain:
 * 1) Find the node with the first (leftmost)  in the unscrambled
 *    image and move it to the head of the chain.
 *	This  is the one whose closest match (to the left) is the
 *	largest.  That is, the distance (using distanceTo) to this 
 *	is big for all other blocks.
 *	For each  B, find the distanceTo B from every other 
 *	and take the minimum of these distances as B's "value".
 *	Choose the  B with the maximum value over all blocks and
 *	swap its node to the head of the chain.
 *
 * 2) Starting with the (just found) first  B, find the node with
 *    the  that is the closest match to follow B (to the right)
 *    among the remaining blocks, move (swap) it to follow B's node,
 *    then repeat to unscramble the chain/image.
 */
void Chain::unscramble() {
  /* your code here */
  Node *currenthead = this->head_;
  Node *tempo = this->head_;
  Node *save;

  double min = DBL_MAX;
  double max = DBL_MAX;
  while(tempo != NULL){
    Node *tempo2 = this->head_;
    while(tempo2 != NULL){
      double distance = tempo->data.distanceTo(tempo2->data);
      if((tempo != tempo2) && (distance <= min)){
        min = distance;
      }
      tempo2 = tempo2->next;
    }
    if(min < max){
      max = min;
      save = tempo;
    }
    tempo = tempo->next;
  }

  swap(currenthead,save);
  this->head_ = save;

  
  Node *header = this->head_;
  while(header != NULL){
    Node *header2 = this->head_;
    Node *save2;
    double whatmin = DBL_MAX;
    while(header2 != NULL){
      double distance = header->data.distanceTo(header2->data);
      if(header != header2 && distance <= whatmin){
        whatmin = distance;
        save2 = header2;
      }
      header2 = header2->next;
    }
    swap(header->next,save2);
    header = header->next;
  }
}

