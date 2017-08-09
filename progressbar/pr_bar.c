#include <stdio.h>
#include <unistd.h>

int print_bar(double t);
int main()
{
  double taskcompleted;

  taskcompleted = 0;

  while (taskcompleted < 77)
  {
    print_bar(taskcompleted);
    taskcompleted++;
    //sleep(1);
  }
  return (0);
}


int print_bar(double taskcompleted)
{
  double numtasks;
  int i;

  i = 0;
  numtasks = 76; // количевство итераций для прогресс бара
  int position = (taskcompleted / numtasks) * 100;
  printf("\033[1;31m{");
  while (i <= 100)
  {
    if (i < position)
      printf("\033[1;34m=");
    if (i == position)
      printf("\033[1;32m>");
    if (i > position)
      printf(" ");
    i++;
  }
  printf("\033[1;31m}");
  printf(" \033[1;32m%d%%", position);
  usleep(50000);
  if (taskcompleted != numtasks)
    printf("\r");
  else
    printf("\n");
  return (0);
}
