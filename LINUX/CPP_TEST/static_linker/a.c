extern int shared;

void swap(int *, int *);

int main (int argc, char *argv[])
{
  int a = 100;
  swap(&a, &shared);
  return 0;
}
