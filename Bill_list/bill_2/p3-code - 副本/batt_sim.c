// batt_sim.c: DO NOT MODIFY
//
// Battery display simulator support functions.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "batt.h"
#include <stdint.h>

#define BATT_MAX_BITS 30

// These global variables are documented in the header file
short BATT_VOLTAGE_PORT;
int32_t BATT_DISPLAY_PORT = 0;
unsigned char BATT_STATUS_PORT = 0;

// Convenience struct for representing the battery display  as characters 
typedef struct {
  char chars[7][32];
} batt_display;


// +-^^^-+                         0 
// |     |  #  #   ####  ####      1                 
// |     |  #  #      #     #      2                 
// |#####|  ####   ####  ####  V   3                 
// |#####|     #   #        #      4                 
// |#####|     # o ####  ####      5                    
// +-----+                         6
// 01234567890123456789012345678901                       
// 0         1         2         3                                 

// position of decimal place is at row 4, col 17

batt_display init_display = {
  .chars = {
    "+-^^^-+                        ", 
    "|     |                        ",                 
    "|     |                        ",                 
    "|     |                        ",                 
    "|     |                        ",                 
    "|     |                        ",                    
    "+-----+                        ",
  }
};

// Reset batt_display to be empty 
void reset_batt_display(batt_display *batt){
  *batt = init_display;
}  

// Print an batt_display 
void internal_print_batt_display(batt_display *batt){
  for(int i=0; i<7; i++){
    printf("%s\n",batt->chars[i]);
  }
}  

// Data and functions to set the state of the batt display 

// Position and char in display 
typedef struct {
  int r,c; int ch;
} charpos;
    
// Collection of characters corresponding to one bit in the state being set 
typedef struct {
  int len;                      // number of chars corresponding to this bit
  charpos pos[5];               // position of chars for this bit
} charpos_coll;

#define RGT 0
#define MID 6
#define LFT 13

// Correspondence of bit positions to which characters should be set 
charpos_coll bits2chars[BATT_MAX_BITS] = {
  { .len=1, .pos={{ 4,28,'%'}}                                      }, // 0
  { .len=1, .pos={{ 3,28,'V'}}                                      }, // 1
  { .len=1, .pos={{ 6,14,'o'}}                                      }, // 2

  { .len=4, .pos={{ 0,22 -RGT,'#'},{ 0,23 -RGT,'#'}, { 0,24 -RGT,'#'},{ 0,25 -RGT,'#'}} }, //  3 
  { .len=4, .pos={{ 0,25 -RGT,'#'},{ 1,25 -RGT,'#'}, { 2,25 -RGT,'#'},{ 3,25 -RGT,'#'}} }, //  4 
  { .len=4, .pos={{ 3,25 -RGT,'#'},{ 4,25 -RGT,'#'}, { 5,25 -RGT,'#'},{ 6,25 -RGT,'#'}} }, //  5 
  { .len=4, .pos={{ 6,22 -RGT,'#'},{ 6,23 -RGT,'#'}, { 6,24 -RGT,'#'},{ 6,25 -RGT,'#'}} }, //  6 
  { .len=4, .pos={{ 3,22 -RGT,'#'},{ 4,22 -RGT,'#'}, { 5,22 -RGT,'#'},{ 6,22 -RGT,'#'}} }, //  7 
  { .len=4, .pos={{ 0,22 -RGT,'#'},{ 1,22 -RGT,'#'}, { 2,22 -RGT,'#'},{ 3,22 -RGT,'#'}} }, //  8 
  { .len=4, .pos={{ 3,22 -RGT,'#'},{ 3,23 -RGT,'#'}, { 3,24 -RGT,'#'},{ 3,25 -RGT,'#'}} }, //  9 

  { .len=4, .pos={{ 0,22 -MID,'#'},{ 0,23 -MID,'#'}, { 0,24 -MID,'#'},{ 0,25 -MID,'#'}} }, // 10 
  { .len=4, .pos={{ 0,25 -MID,'#'},{ 1,25 -MID,'#'}, { 2,25 -MID,'#'},{ 3,25 -MID,'#'}} }, // 11 
  { .len=4, .pos={{ 3,25 -MID,'#'},{ 4,25 -MID,'#'}, { 5,25 -MID,'#'},{ 6,25 -MID,'#'}} }, // 12 
  { .len=4, .pos={{ 6,22 -MID,'#'},{ 6,23 -MID,'#'}, { 6,24 -MID,'#'},{ 6,25 -MID,'#'}} }, // 13 
  { .len=4, .pos={{ 3,22 -MID,'#'},{ 4,22 -MID,'#'}, { 5,22 -MID,'#'},{ 6,22 -MID,'#'}} }, // 14 
  { .len=4, .pos={{ 0,22 -MID,'#'},{ 1,22 -MID,'#'}, { 2,22 -MID,'#'},{ 3,22 -MID,'#'}} }, // 15 
  { .len=4, .pos={{ 3,22 -MID,'#'},{ 3,23 -MID,'#'}, { 3,24 -MID,'#'},{ 3,25 -MID,'#'}} }, // 16 

  { .len=4, .pos={{ 0,22 -LFT,'#'},{ 0,23 -LFT,'#'}, { 0,24 -LFT,'#'},{ 0,25 -LFT,'#'}} }, // 17 
  { .len=4, .pos={{ 0,25 -LFT,'#'},{ 1,25 -LFT,'#'}, { 2,25 -LFT,'#'},{ 3,25 -LFT,'#'}} }, // 18 
  { .len=4, .pos={{ 3,25 -LFT,'#'},{ 4,25 -LFT,'#'}, { 5,25 -LFT,'#'},{ 6,25 -LFT,'#'}} }, // 19 
  { .len=4, .pos={{ 6,22 -LFT,'#'},{ 6,23 -LFT,'#'}, { 6,24 -LFT,'#'},{ 6,25 -LFT,'#'}} }, // 20 
  { .len=4, .pos={{ 3,22 -LFT,'#'},{ 4,22 -LFT,'#'}, { 5,22 -LFT,'#'},{ 6,22 -LFT,'#'}} }, // 21 
  { .len=4, .pos={{ 0,22 -LFT,'#'},{ 1,22 -LFT,'#'}, { 2,22 -LFT,'#'},{ 3,22 -LFT,'#'}} }, // 22 
  { .len=4, .pos={{ 3,22 -LFT,'#'},{ 3,23 -LFT,'#'}, { 3,24 -LFT,'#'},{ 3,25 -LFT,'#'}} }, // 23 

  { .len=5,.pos={{5,1,'#'},{5,2,'#'},{5,3,'#'},{5,4,'#'},{5,5,'#'}} }, // 24
  { .len=5,.pos={{4,1,'#'},{4,2,'#'},{4,3,'#'},{4,4,'#'},{4,5,'#'}} }, // 25
  { .len=5,.pos={{3,1,'#'},{3,2,'#'},{3,3,'#'},{3,4,'#'},{3,5,'#'}} }, // 26
  { .len=5,.pos={{2,1,'#'},{2,2,'#'},{2,3,'#'},{2,4,'#'},{2,5,'#'}} }, // 27
  { .len=5,.pos={{1,1,'#'},{1,2,'#'},{1,3,'#'},{1,4,'#'},{1,5,'#'}} }, // 28
};


// Assumes ints are at least 32 bits for disp
void set_batt_display(batt_display *batt, int disp){
  int i,j;
  int mask = 0x1;
  reset_batt_display(batt);
  for(i=0; i<BATT_MAX_BITS; i++){
    //    printf("Checking %d\n",i);
    if( disp & (mask << i) ){ // ith bit set, fill in characters 
      //      printf("%d IS SET\n",i);
      charpos_coll coll = bits2chars[i];
      //      printf("Coll len: %d\n",coll.len);
      for(j=0; j<coll.len; j++){
        //        printf("Inner iter %d\n",j);
        charpos pos = coll.pos[j];
        batt->chars[pos.r][pos.c] = pos.ch;
        // print_batt_display(batt);
      }
    }
  }
}


// Use the global BATT_DISPLAY_PORT to print the battery display
void print_batt_display(){
  batt_display batt;
  set_batt_display(&batt, BATT_DISPLAY_PORT);
  internal_print_batt_display(&batt);
  return;
}



#define NCLUSTERS 6
int clusters[NCLUSTERS] = {
  3, 5, 7, 7, 7, 3
};

// Generate a string version of the bits which clusters the bits based
// on the logical groupings in the problem
char *bitstr(int x, int bits){
  static char buffer[512];
  int idx = 0;
  int clust_idx = 0;
  int clust_break = clusters[0];
  for(int i=0; i<bits; i++){
    if(i==clust_break){
      buffer[idx] = ' ';
      idx++;
      clust_idx++;
      clust_break += clusters[clust_idx];
    }
    buffer[idx] = x & (1 << (bits-i-1)) ? '1' : '0';
    idx++;
  }
  buffer[idx] = '\0';
  return buffer;
}

// Creates a string of bit indices matching the clustering pattern
// above
char *bitstr_index(int bits){
  static char buffer[512];
  char format[256];
  int pos = 0;
  int idx = bits;
  for(int i=0; i<NCLUSTERS; i++){
    idx -= clusters[i];
    if(clusters[i] > 1){
      sprintf(format, "%s%dd ","%",clusters[i]);
      pos += sprintf(buffer+pos, format, idx);
    }
    else{                       // cluster of 1 bit gets no index
      pos += sprintf(buffer+pos, "  ");
    }
  }
  buffer[pos-1] = '\0';         // eliminate trailing space
  return buffer;
}
