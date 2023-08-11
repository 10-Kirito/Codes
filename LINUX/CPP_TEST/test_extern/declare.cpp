extern int i;

extern float f(float);
float b;

float f(float a) {
  return a + 1.0;
}

int i;
int h(int x) {
  return x + 1;
}

int main (int argc, char *argv[])
{
  b = 1.0;
  i = 2;
  f(b);
  h(i);
  return 0;
}
