/******************************************************************************
 * Copyright (C) 2017 by Alex Fosdick - University of Colorado
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are 
 * permitted to modify this and use it to learn about the field of embedded
 * software. Alex Fosdick and the University of Colorado are not liable for any
 * misuse of this material. 
 *
 *****************************************************************************/
/**
 * @file stats.c
 * @brief statistical analytics
 *
 * A simple application that performs statistical analytics on a dataset.
 *
 * @author Illia Baliuk
 * @date 19 March 2024
 *
 */



#include "platform.h"
#include "stats.h"


void print_statistics(unsigned char* pArray, unsigned int size){
    #ifdef VERBOSE

  PRINTF("Statistics of the array:\n");
  PRINTF(" - Median: %u \n", find_median(pArray, size));
  PRINTF(" - Mean: %u \n", find_mean(pArray, size));
  PRINTF(" - Maximum: %u \n", find_maximum(pArray, size));
  PRINTF(" - Minuimum: %u \n", find_minimum(pArray, size));
    #endif
}


void print_array(unsigned char* pArray, unsigned int size){
    #ifdef VERBOS
	char stat_str[128] = "\nArray contains: "
        char temp[16];
	for (unsigned int i = 0; i < size; i++){
		sprintf(temp,"\t%d",pArray[i];
		strcat(stat_str, temp);
	}
	strcat(stat_str,"\n\n");
	PRINTF(stat_str);
    #endif
}


unsigned char find_median(unsigned char* pArray, unsigned int size){
  unsigned char temp;
  sort_array(pArray, size);
  temp = (size % 2 == 1) ? pArray[size/2]: (pArray[(size/2)-1] + pArray[size/2])/2;
  return temp;
}


unsigned char find_mean(unsigned char* pArray, unsigned int size){
  long int sum = 0;
  for (unsigned int  i = 0; i < size; i++) {
    sum += pArray[i];
  }
  return sum / size;
}


unsigned char find_maximum(unsigned char* pArray, unsigned int size){
  unsigned char maximum = pArray[0];
  for(unsigned int i=1; i<size ; i++)
  {
     if (maximum < pArray[i])
     {
       maximum = pArray[i];
     }
  }
  return maximum;
}


unsigned char find_minimum(unsigned char* pArray, unsigned int size){
  unsigned char minimum = pArray[0];
  for(unsigned int i=1; i<size ; i++)
  {
    if (minimum > pArray[i])
    {
      minimum = pArray[i];
    }
  }
  return minimum;
}


void sort_array(unsigned char* pArray, unsigned int size){
  unsigned int j, k;
  unsigned char temp;
  for( j = 0 ; j < size-1 ; j++ )
  {
    for( k = size-1 ; k > j ; k-- )
    {
      if(pArray[k]>pArray[k-1])
      {
        temp = pArray[k-1];
        pArray[k-1] = pArray[k];
        pArray[k] = temp;
      }
    }
  }
}

