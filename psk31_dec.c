#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#define K 3
#define NUM_STATES 32

#define INPUT_LENGTH 20

// the received output states with I & Q

void read_input(unsigned int *input, unsigned int *len);
//unsigned int input[INPUT_LENGTH] = {0,3,2,1,0,0,1,0,1,1,1,3,1,1,0,2,2,1,3,0};

/* for a given state this structure represents
 * the what the next state will be given we
 * have an input of 0 or 1
*/

unsigned int next_state_arr[NUM_STATES][2] =
{
  { 0, 1}, // state 0
  { 2, 3}, // state 1
  { 4, 5}, // state 2
  { 6, 7}, // state 3
  { 8, 9}, // state 4
  {10,11}, // state 5
  {12,13}, // state 6
  {14,15}, // state 7
  {16,17}, // state 8
  {18,19}, // state 9
  {20,21}, // state 10
  {22,23}, // state 11
  {24,25}, // state 12
  {26,27}, // state 13
  {28,29}, // state 14
  {30,31}, // state 15
  { 0, 1}, // state 16
  { 2, 3}, // state 17
  { 4, 5}, // state 18
  { 6, 7}, // state 19
  { 8, 9}, // state 20
  {10,11}, // state 21
  {12,13}, // state 22
  {14,15}, // state 23
  {16,17}, // state 24
  {18,19}, // state 25
  {20,21}, // state 26
  {22,23}, // state 27
  {24,25}, // state 28
  {26,27}, // state 29
  {28,29}, // state 30
  {30,31}, // state 31
};

/* for a given state this structure represents
 * what the output will be given the input is
 * a 0 or 1
 */

unsigned int output_state_arr[NUM_STATES][2] =
{
  {0,3}, // state 0
  {0,3}, // state 1
  {2,1}, // state 2
  {2,1}, // state 3
  {2,1}, // state 4
  {2,1}, // state 5
  {0,3}, // state 6
  {0,3}, // state 7
  {1,2}, // state 8
  {1,2}, // state 9
  {3,0}, // state 10
  {3,0}, // state 11
  {3,0}, // state 12
  {3,0}, // state 13
  {1,2}, // state 14
  {1,2}, // state 15
  {3,0}, // state 16
  {3,0}, // state 17
  {1,2}, // state 18
  {1,2}, // state 19
  {1,2}, // state 20
  {1,2}, // state 21
  {3,0}, // state 22
  {3,0}, // state 23
  {2,1}, // state 24
  {2,1}, // state 25
  {0,3}, // state 26
  {0,3}, // state 27
  {0,3}, // state 28
  {0,3}, // state 29
  {2,1}, // state 30
  {2,1}  // state 31
};

unsigned int state_trans[NUM_STATES][NUM_STATES] =
{
  {0,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}, // state 0
  {3,3,0,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}, // state 1
  {3,3,3,3,0,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}, // state 2
  {3,3,3,3,3,3,0,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}, // state 3
  {3,3,3,3,3,3,3,3,0,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}, // state 4
  {3,3,3,3,3,3,3,3,3,3,0,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}, // state 5
  {3,3,3,3,3,3,3,3,3,3,3,3,0,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}, // state 6
  {3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}, // state 7
  {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3}, // state 8
  {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,1,3,3,3,3,3,3,3,3,3,3,3,3}, // state 9
  {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,1,3,3,3,3,3,3,3,3,3,3}, // state 10
  {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,1,3,3,3,3,3,3,3,3}, // state 11
  {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,1,3,3,3,3,3,3}, // state 12
  {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,1,3,3,3,3}, // state 13
  {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,1,3,3}, // state 14
  {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,1}, // state 15
  {0,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}, // state 16
  {3,3,0,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}, // state 17
  {3,3,3,3,0,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}, // state 18
  {3,3,3,3,3,3,0,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}, // state 19
  {3,3,3,3,3,3,3,3,0,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}, // state 20
  {3,3,3,3,3,3,3,3,3,3,0,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}, // state 21
  {3,3,3,3,3,3,3,3,3,3,3,3,0,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}, // state 22
  {3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}, // state 23
  {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3}, // state 24
  {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,1,3,3,3,3,3,3,3,3,3,3,3,3}, // state 25
  {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,1,3,3,3,3,3,3,3,3,3,3}, // state 26
  {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,1,3,3,3,3,3,3,3,3}, // state 27
  {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,1,3,3,3,3,3,3}, // state 28
  {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,1,3,3,3,3}, // state 29
  {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,1,3,3}, // state 30
  {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,1}  // state 31
};

/*
 * These arrays are populated as the decoder processes
 * each time sample. They use the state arrays that are
 * already initialized above
 */

// the path metric for each state transition
//unsigned int acc_metric[NUM_STATES][INPUT_LENGTH];

// add-compare-select array for each state
// this array is populated per time sample
// and we can take the lowest path metric
// from the state transitions
unsigned int acs[NUM_STATES];

// used to traceback through the acc_metric array to
// determine which output states have the lowest
// metric
//unsigned int traceback[INPUT_LENGTH];

// once the traceback array output states are found
// we can use the state_trans to find the encoded
// bits that were an input to the convolutional
// encoder
//unsigned int decoded[INPUT_LENGTH];

unsigned int hamming_distance(unsigned int a, unsigned int b);

void cnv_dec(unsigned int encoded[], unsigned int len, unsigned int *decoded[]);

/*
 * functions for debugging
 */
void print_acc_metrics(unsigned int acc_metric[NUM_STATES][1024], int len);
void print_traceback(unsigned int traceback[], int len);
void print_decoded(unsigned int decoded[], int len);

int main(int argc, char *argv[])
{
  unsigned int input[1024];
  unsigned int len;
  unsigned int *decoded;

  FILE* fdo = stdout;

  read_input(input,&len);
  cnv_dec(input,len,&decoded);
  for(int i=0;i<len;i++) {
    fprintf(fdo,"%d",decoded[i]);
  }
  free(decoded);
}

void read_input(unsigned int *input, unsigned int *len)
{
  int n = 0;
  char buf[1];

  while(read(0, buf, sizeof(buf))>0) {
    switch(buf[0])
    {
      case '0':
        input[n++] = 0;
        break;
      case '1':
        input[n++] = 1;
        break;
      case '2':
        input[n++] = 2;
        break;
      case '3':
        input[n++] = 3;
        break;
      case '\n':
        *len = n;
        return;
        break;
      default:
        break;
    }
  }
}

unsigned int hamming_distance(unsigned int a, unsigned int b)
{
  unsigned int distance = 0;

  unsigned int a1 =  1 & a;
  unsigned int a2 =  2 & a;
  unsigned int a3 =  4 & a;
  unsigned int a4 =  8 & a;
  unsigned int a5 = 16 & a;

  unsigned int b1 =  1 & b;
  unsigned int b2 =  2 & b;
  unsigned int b3 =  4 & b;
  unsigned int b4 =  8 & b;
  unsigned int b5 = 16 & b;

  distance += (a1 ^ b1);
  distance += (a2 ^ b2) >>  1;
  distance += (a3 ^ b3) >>  2;
  distance += (a4 ^ b4) >>  3;
  distance += (a5 ^ b5) >>  4;
  return distance;
}

void cnv_dec(unsigned int encoded[], unsigned int len, unsigned int *decoded[])
{
  /*
   * These arrays are populated as the decoder processes
   * each time sample. They use the state arrays that are
   * already initialized above
   */

  // the path metric for each state transition
  unsigned int acc_metric[NUM_STATES][1024];

  // used to traceback through the acc_metric array to
  // determine which output states have the lowest
  // metric
  unsigned int *traceback;

  // distance from next state given a 0 and 1
  unsigned int d0,d1;

  // next state given current state if next is 0 or 1
  unsigned int ns0,ns1;

  // output state if next is 0 or 1
  unsigned int os0,os1;

  assert(len<1024); // TODO

  traceback = (unsigned int*) calloc(len,sizeof(int));
  // TODO wny need array
  unsigned int *_decoded = (unsigned int*) calloc(len,sizeof(int));
  *decoded = _decoded;

  for(int t=0;t<len;t++)
  {
    for(int state=0;state<NUM_STATES;state++)
    {
      int initval = t<4 ? 9 : 0;
      acc_metric[state][t] = initval;
    }
  }

  for(int t=0;t<len;t++)
  {
    // initialize ACS to anything smaller than 255 will be used
    for(int state=0;state<NUM_STATES;state++) acs[state] = 255;
    for(int state=0;state<NUM_STATES;state++)
    {
      ns0 = next_state_arr[state][0];
      ns1 = next_state_arr[state][1];

      os0 = output_state_arr[ns0][0];
      os1 = output_state_arr[ns1][1];

      d0 = hamming_distance(os0,encoded[t]);
      d1 = hamming_distance(os1,encoded[t]);

      // since the state machine starts at state 0 at time 0
      // we will only compute for state transtions of 0
      if(t==0 && state==0)
      {
        acc_metric[ns0][t] = d0;
        acc_metric[ns1][t] = d1;
      }
      if(t>0)
      {
        unsigned int acc_metrics[2];
        unsigned int prev_metric;

        prev_metric = acc_metric[state][t-1];

        acc_metrics[0] = d0+prev_metric;
        acc_metrics[1] = d1+prev_metric;

        if(acc_metrics[0] < acs[ns0]) {
          acs[ns0] = acc_metrics[0];
        }

        if(acc_metrics[1] < acs[ns1]) {
          acs[ns1] = acc_metrics[1];
        }

        acc_metric[ns0][t] = acs[ns0];
        acc_metric[ns1][t] = acs[ns1];
      }
    }
  }

  for(int t=0;t<len;t++)
  {
    unsigned int min_metric = 255;
    unsigned int min_metric2 = 255;
    unsigned int min_state = 0;
    for(int state=0;state<NUM_STATES;state++)
    {
      unsigned int metric = acc_metric[state][t];
      if(metric < min_metric)
      {
        min_state = state;
        min_metric = metric;
      }
    }
    traceback[t] = min_state;
    if(t>0)
    {
      _decoded[t-1] = state_trans[traceback[t-1]][traceback[t]];
      if(_decoded[t-1] > 1)
      {
         printf("here0 %d %d\n",min_state,t);
         unsigned int past_min_state = traceback[t-1];
         unsigned int min_state2 = (past_min_state+1)%NUM_STATES;
         unsigned int min_metric2 = acc_metric[min_state2][t-1];
         printf("%d %d %d\n",min_state2,min_metric2,t);
         unsigned int decoded2;
         if(past_min_state%2 == 0 && min_metric2 == acc_metric[past_min_state][t-1])
         {
           puts("here1");
           decoded2 = state_trans[min_state2][traceback[t]];
           if(decoded2 < 2)
           {
             _decoded[t-1] = decoded2;
             printf("*");
           }
         }
      }
    }

  }

  /*for(int t=1;t<len-1;t++)
  {
    _decoded[t-1] = state_trans[traceback[t-1]][traceback[t]];
  }*/

  free(traceback);

  print_acc_metrics(acc_metric,len);
  print_traceback(traceback,len);
  print_decoded(_decoded,len);
}

void print_acc_metrics(unsigned int acc_metric[NUM_STATES][1024], int len)
{
  puts("accumulated metrics:");
  for(int i=0;i<NUM_STATES+1;i++)
  {
    for(int j=0;j<len+1;j++)
    {
      switch(i)
      {
        case 0:
          switch(j)
          {
            case 0:
              printf("t=   ");
              break;
            default:
              printf("%3d ",j-1);
          }
          break;
        default:
          switch(j)
          {
            case 0:
              printf("%2d   ",i-1);
              break;
            default:
              printf("%3d ",acc_metric[i-1][j-1]);
          }
      }
    }
    puts("");
  }
  puts("");
}

void print_traceback(unsigned int traceback[], int len)
{
  puts("traceback:");
  for(int i=0;i<1+1;i++)
  {
    for(int j=0;j<len+1;j++)
    {
      switch(i)
      {
        case 0:
          switch(j)
          {
            case 0:
              printf("t=   ");
              break;
            default:
              printf("%3d ",j-1);
          }
          break;
        default:
          switch(j)
          {
            case 0:
              printf("     ");
              break;
            default:
              printf("%3d ",traceback[j-1]);
          }
      }
    }
    puts("");
  }
  puts("");
}

void print_decoded(unsigned int decoded[], int len)
{
  puts("decoded:");
  for(int i=0;i<1+1;i++)
  {
    for(int j=0;j<len+1-1;j++)
    {
      switch(i)
      {
        case 0:
          switch(j)
          {
            case 0:
              printf("t=   ");
              break;
            default:
              printf("%3d ",j-1);
          }
          break;
        default:
          switch(j)
          {
            case 0:
              printf("     ");
              break;
            default:
              printf("%3d ",decoded[j-1]);
          }
      }
    }
    puts("");
  }
  puts("");
}
