/*
 * CSE 340 Project 1 - structs.h
 * Tyler Fichiera
 */
#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include <vector>
#include <string>
#include <set>

using namespace std;

struct REG_node {
  struct REG_node* first_neighbor;
  char first_label;
  struct REG_node* second_neighbor;
  char second_label;
  int id; // give them an id to compare later on
};

struct REG {
  struct REG_node* start;
  struct REG_node* accept;
};

struct TokenREG {
  string token_name;
  int token_line_no;
  REG* reg_pointer;
};

#endif
