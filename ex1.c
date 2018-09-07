#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define K 3
#define NUM_STATES 4

#define INPUT_LENGTH 20

// the received output states with I & Q
unsigned int input[INPUT_LENGTH] = {0,3,3,0,1,2,1,3,3,2,0,0,3,0,3,2,3,0,0,0};

/* for a given state this structure represents
 * the what the next state will be given we
 * have an input of 0 or 1
*/
unsigned int next_state_arr[NUM_STATES][2] =
{
  {0,2},
  {0,2},
  {1,3},
  {1,3}
};

/* for a given state this structure represents
 * what the output will be given the input is
 * a 0 or 1
 */
unsigned int output_state_arr[NUM_STATES][2] =
{
  {0,3},
  {3,0},
  {2,1},
  {1,2}
};

/*unsigned int states[NUM_STATES] =
{
  0,
  1,
  2,
  3
};*/

unsigned int state_trans[NUM_STATES][4] =
{
  {0,9,1,9},
  {0,9,1,9},
  {9,0,9,1},
  {9,0,9,1}
};

/*
 * These arrays are populated as the decoder processes
 * each time sample. They use the state arrays that are
 * already initialized above
 */


// the path metric for each state transition
unsigned int acc_metric[NUM_STATES][INPUT_LENGTH]; // TODO length

// the suvivor states at each time sample
unsigned int surviv[NUM_STATES][INPUT_LENGTH]; // TODO length

// add-compare-select array for each state
// this array is populated per time sample
// and we can take the lowest path metric
// from the state transitions
unsigned int acs[NUM_STATES] = {9,9,9,9};

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
  unsigned int d1,d2;
  unsigned int ns0,ns1;
  for(int t=0;t<INPUT_LENGTH;t++)
  {
    for(int state=0;state<NUM_STATES;state++) acs[state] = 9;
    // i = 0 we have 2 paths
    // i = 1 we have 2*2 = 4 paths
    // i = 2 we have 2*2*2 = 8 paths
    // i > 2 we took best so 8 paths
    for(int state=0;state<NUM_STATES;state++)
    {

      ns0 = next_state_arr[state][0];
      ns1 = next_state_arr[state][1];

      d1 = hamming_distance(output_state_arr[state][0],input[t]);
      d2 = hamming_distance(output_state_arr[state][1],input[t]);

      if(t==0 && state==0)
      {
        acc_metric[next_state_arr[state][0]][t] = d1;
        acc_metric[next_state_arr[state][1]][t] = d2;
      }
      if(t==1 && (state==0 || state==2))
      {
        acc_metric[ns0][t] = d1;
        acc_metric[ns1][t] = d2;
      }
      if(t==1)
      {
        acc_metric[next_state_arr[state][0]][t] += acc_metric[state][t-1];
        acc_metric[next_state_arr[state][1]][t] += acc_metric[state][t-1];
      }
      if(t>1) // we have to compute 8 paths and take best ?
      {
        unsigned int acc_metrics[2];
        unsigned int di0,di1;
        di0 = hamming_distance(output_state_arr[state][0],input[t]);
        di1 = hamming_distance(output_state_arr[state][1],input[t]);

        unsigned int am0,am1;
        am0 = acc_metric[state][t-1];
        am1 = acc_metric[state][t-1];

        acc_metrics[0] = di0+am0;
        acc_metrics[1] = di1+am1;

        if(acc_metrics[0] < acs[ns0]) {
          acs[ns0] = acc_metrics[0];
          surviv[ns0][t] = state;
        }

        if(acc_metrics[1] < acs[ns1]) {
          acs[ns1] = acc_metrics[1];
          surviv[ns1][t] = state;
        }

        acc_metric[ns0][t] = acs[ns0];
        acc_metric[ns1][t] = acs[ns1];

        //printf("&& t=%d state=%d %d %d+%d %d\n",t,state,ns0,am0,di0,acs[ns0]);
        //printf("&& t=%d state=%d %d %d+%d %d\n",t,state,ns1,am1,di1,acs[ns1]);
      }
    }
  }

  for(int t=0;t<INPUT_LENGTH;t++)
  {
    unsigned int min_metric = 9;
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
  // warning currently only doing 2-bits
  unsigned int distance = 0;

  unsigned int a1 = 1 & a;
  unsigned int a2 = 2 & a;
  unsigned int b1 = 1 & b;
  unsigned int b2 = 2 & b;

  distance += (a1 ^ b1);
  distance += (a2 ^ b2) >> 1;
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
              printf("%.2x   ",i-1);
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
              printf("%.2x   ",i-1);
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
