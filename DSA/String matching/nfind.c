#include<stdio.h>
#include<string.h>
#define MAX 20

int nfind(char *txt , char *pat)
{
  int start = 0 , i, j;
  int lastt = strlen(txt) - 2;//last index of text
  int lastp = strlen(pat) - 2;//last index of Pattern
  int end = lastp;
  for(i = 0; end<=lastt ;end++,start++) // Outer loop to slide the pattern over the text
  {// Check if the current ending character in the text matches the last character of the pattern
      if(txt[end] == pat[lastp])
          for(i=start,j=0;j<=lastp && txt[i] == pat[j] ;i++,j++) // Inner loop to check the rest of the pattern from the beginning
              if(j == lastp)// // If all characters of the pattern match, return the start index
                  return start;
      
  }
  return -1;// Return -1 if the pattern is not found
}
int main()
{
  char txt[MAX] , pat[MAX];
  printf("Enter the text string:");
  fgets(txt , MAX , stdin );// Read the text string from user input 
  printf("Enter the pattern string:");
  fgets(pat , MAX , stdin ); // Read the pattern string from user input
  int res = nfind(txt , pat);  // Call the nfind function to search the pattern in the text
  if(res == -1)
  {
      printf("Pattern is not present in the given text");
  }
  else
  {
      printf("Pattern is found at %d",res+1);
  }
}