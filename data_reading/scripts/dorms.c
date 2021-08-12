// dorms.c


#include "dormfunc.h"

int main()
{
  Dorm nd_dorms[50];
  bool done = false;
  int count, sum, choice;

  count = read_dorms(nd_dorms);

  while(!done) {
    choice = menu();
    switch (choice) {
      case 1:
        display_all_dorms(nd_dorms, count);
        break;
      case 2:
        display_dorms_split_by_gender(nd_dorms, count);
        break;
      case 3:
        display_dorms_M_or_F(nd_dorms, count);
        break;
      case 4:
        display_before_year(nd_dorms, count);
        break;
      case 5:
        sum = total_cap(nd_dorms, count);
        printf("Total dorm capacity is: %d\n", sum);
        break;
      case 6:
        done = true;
        break;
      default:
        printf("incorrect choice\n");
    }
  }

  return 0;
}
