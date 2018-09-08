#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define K 3
#define NUM_STATES 32

#define INPUT_LENGTH 20

// the received output states with I & Q
unsigned int input[INPUT_LENGTH] = {0,3,2,1,0,0,1,0,1,1,1,3,1,1,0,2,2,1,3,0};

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

unsigned int state_trans[NUM_STATES][32] =
{
  { 0, 1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255}, // state 1,
  {255,255, 0, 1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255}, // state 2,
  {255,255,255,255, 0, 1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255}, // state 3,
  {255,255,255,255,255,255, 0, 1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255}, // state 4,
  {255,255,255,255,255,255,255,255, 0, 1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255}, // state 5,
  {255,255,255,255,255,255,255,255,255,255, 0, 1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255}, // state 6,
  {255,255,255,255,255,255,255,255,255,255,255,255, 0, 1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255}, // state 7,
  {255,255,255,255,255,255,255,255,255,255,255,255,255,255, 0, 1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255}, // state 8,
  {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 0, 1,255,255,255,255,255,255,255,255,255,255,255,255,255,255}, // state 9,
  {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 0, 1,255,255,255,255,255,255,255,255,255,255,255,255}, // state 10,
  {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 0, 1,255,255,255,255,255,255,255,255,255,255}, // state 11,
  {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 0, 1,255,255,255,255,255,255,255,255}, // state 12,
  {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 0, 1,255,255,255,255,255,255}, // state 13,
  {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 0, 1,255,255,255,255}, // state 14,
  {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 0, 1,255,255}, // state 15,
  {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 0, 1}, // state 16,
  { 0, 1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255}, // state 17,
  {255,255, 0, 1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255}, // state 18,
  {255,255,255,255, 0, 1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255}, // state 19,
  {255,255,255,255,255,255, 0, 1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255}, // state 20,
  {255,255,255,255,255,255,255,255, 0, 1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255}, // state 21,
  {255,255,255,255,255,255,255,255,255,255, 0, 1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255}, // state 22,
  {255,255,255,255,255,255,255,255,255,255,255,255, 0, 1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255}, // state 23,
  {255,255,255,255,255,255,255,255,255,255,255,255,255,255, 0, 1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255}, // state 24,
  {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 0, 1,255,255,255,255,255,255,255,255,255,255,255,255,255,255}, // state 25,
  {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 0, 1,255,255,255,255,255,255,255,255,255,255,255,255}, // state 26,
  {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 0, 1,255,255,255,255,255,255,255,255,255,255}, // state 27,
  {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 0, 1,255,255,255,255,255,255,255,255}, // state 28,
  {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 0, 1,255,255,255,255,255,255}, // state 29,
  {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 0, 1,255,255,255,255}, // state 30,
  {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 0, 1,255,255}, // state 31,
  {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 0, 1}, // state 32
};

/*
 * These arrays are populated as the decoder processes
 * each time sample. They use the state arrays that are
 * already initialized above
 */

// the path metric for each state transition
unsigned int acc_metric[NUM_STATES][INPUT_LENGTH];

// the suvivor states at each time sample
unsigned int surviv[NUM_STATES][INPUT_LENGTH];

// add-compare-select array for each state
// this array is populated per time sample
// and we can take the lowest path metric
// from the state transitions
unsigned int acs[NUM_STATES];

// used to traceback through the acc_metric array to
// determine which output states have the lowest
// metric
unsigned int traceback[INPUT_LENGTH];

// once the traceback array output states are found
// we can use the state_trans to find the encoded
// bits that were an input to the convolutional
// encoder
unsigned int decoded[INPUT_LENGTH];

unsigned int hamming_distance(unsigned int a, unsigned int b);

/*
 * functions for debugging
 */
void print_survivors();
void print_acc_metrics();
void print_traceback();
void print_decoded();

int main(int argc, char *argv[])
{

  for(int t=0;t<INPUT_LENGTH;t++)
  {
    for(int state=0;state<NUM_STATES;state++)
    {
      int initval = t<4 ? 9 : 0;
      acc_metric[state][t] = initval;
    }
  }

  unsigned int d0,d1;
  unsigned int ns0,ns1;
  unsigned int os0,os1;
  for(int t=0;t<INPUT_LENGTH;t++)
  {
    // TODO
    for(int state=0;state<NUM_STATES;state++) acs[state] = 255;
    // i = 0 we have 2 paths
    // i = 1 we have 2*2 = 4 paths
    // i = 2 we have 2*2*2 = 8 paths
    // i = 3 we have 2^4 = 16 paths
    // i = 4 we have 32 paths
    // i = 5 we have 64 paths where best one so 32
    for(int state=0;state<NUM_STATES;state++)
    {
      ns0 = next_state_arr[state][0];
      ns1 = next_state_arr[state][1];

      os0 = output_state_arr[ns0][0];
      os1 = output_state_arr[ns1][1];

      d0 = hamming_distance(os0,input[t]);
      d1 = hamming_distance(os1,input[t]);

      if(t==0 && state==0)
      {
        acc_metric[os0][t] = d0;
        acc_metric[os1][t] = d1;

        if(t<3) {
          printf("dist state=%d os0=%d input=%d\n",state,os0,input[t]);
          printf("dist state=%d os1=%d input=%d\n",state,os1,input[t]);
        }
      }
      if(t>0)
      {
        unsigned int acc_metrics[2];
        unsigned int prev_metric;
        unsigned int surviv_state;
        unsigned int nns0=99,nns1=99;
        unsigned int w0=0,w1=0;

        prev_metric = acc_metric[state][t-1];

        acc_metrics[0] = d0+prev_metric;
        acc_metrics[1] = d1+prev_metric;

        if(acc_metrics[0] < acs[ns0]) {
          acs[ns0] = acc_metrics[0];
          w0 = 1;
        }

        if(acc_metrics[1] < acs[ns1]) {
          acs[ns1] = acc_metrics[1];
          w1 = 1;
        }

        acc_metric[ns0][t] = acs[ns0];
        acc_metric[ns1][t] = acs[ns1];

        if(t<3)
        {
          printf("t=%d w0=%d state=%d input=%d ns=%d %d+%d acc_metric=%d surviv_state=%d nns0=%d nns1=%d\n",t,w0,state,input[t],ns0,prev_metric,d0,acs[ns0],surviv_state,nns0,nns1);
          printf("t=%d w1=%d state=%d input=%d ns=%d %d+%d acc_metric=%d surviv_state=%d nns0=%d nns1=%d\n",t,w1,state,input[t],ns1,prev_metric,d1,acs[ns1],surviv_state,nns0,nns1);
        }
      }
    }
  }

  for(int t=0;t<INPUT_LENGTH;t++)
  {
    unsigned int min_metric = 255;
    unsigned int min_state = 0;
    for(int state=0;state<NUM_STATES;state++)
    {
      if(acc_metric[state][t] < min_metric) {
        min_state = state;
        min_metric = acc_metric[state][t];
      }
    }
    traceback[t] = min_state;
  }

  for(int t=1;t<INPUT_LENGTH-1;t++)
  {
    decoded[t-1] = state_trans[traceback[t-1]][traceback[t]];
  }

  print_acc_metrics();
  print_survivors();
  print_traceback();
  print_decoded();
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

void print_survivors()
{
  puts("surviving predecessors:");
  for(int i=0;i<NUM_STATES+1;i++)
  {
    for(int j=0;j<INPUT_LENGTH+1;j++)
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
              printf("%3d ",surviv[i-1][j-1]);
          }
      }
    }
    puts("");
  }
  puts("");
}

void print_acc_metrics()
{
  puts("accumulated metrics:");
  for(int i=0;i<NUM_STATES+1;i++)
  {
    for(int j=0;j<INPUT_LENGTH+1;j++)
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

void print_traceback()
{
  puts("traceback:");
  for(int i=0;i<1+1;i++)
  {
    for(int j=0;j<INPUT_LENGTH+1;j++)
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

void print_decoded()
{
  puts("decoded:");
  for(int i=0;i<1+1;i++)
  {
    for(int j=0;j<INPUT_LENGTH+1-1;j++)
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
