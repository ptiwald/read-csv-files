#include <stdio.h>
#include <string.h>

struct dataset {
  char type[10];
  char priority[10];
  float mapx,mapy;
  int disp_day, disp_month, disp_year, disp_min;
  int arr_day, arr_month, arr_year, arr_min;
  char dispo[10];
  int district;
};

int main(int argc, char *argv[])
{
  FILE *csvfile;
  char buffer[1000];
  char sub_buffer[100];
  int ifield, leftb, rightb, ibuffer;
  struct dataset single_set;
  const int Nfields=17; //last field is split in two parts

  // read first line of csv file into string buffer
  csvfile = fopen("Calls_for_Service_2011.csv","r");
  fgets(buffer, 1000, csvfile);
  fclose(csvfile);
  
  // print fields of buffer separated by ","
  leftb = 0;
  rightb = 1;

  for (ifield=1; ifield<=Nfields; ifield++) {
    while ( (buffer[rightb] != ',') && (buffer[rightb] != '\n') ) rightb++;
    for (ibuffer=leftb; ibuffer<rightb; ibuffer++) {
      sub_buffer[ibuffer-leftb] = buffer[ibuffer];
    }
    sub_buffer[ibuffer-leftb] = '\0'; //index ibuffer-leftb is increased by 1 as compared to the last run of loop!
    leftb=rightb+1;
    rightb=leftb+1;
    //printf("The %2d. field reads %s\n",ifield,sub_buffer);
    //fill in the fields in the datasets
    switch(ifield) {
    case 2:
      strcpy(single_set.type,sub_buffer);
      break;
    case 4:
      strcpy(single_set.priority,sub_buffer);
      break;
    case 5:
      sscanf(sub_buffer, "%f", &single_set.mapx);
      break;
    case 6:
      sscanf(sub_buffer, "%f", &single_set.mapy);
      break;
    }
  }

  printf("Type: %s\n", single_set.type);
  printf("Priority: %s\n", single_set.priority);
  printf("mapx: %f\n",single_set.mapx);

  return 0;

}
