class Simple2 {
  public:
    int f(float) const {return 1;}
};

int (Simple2::*fp)(float) const;
int (Simple2::*fp2)(float) const = &Simple2::f;

int main (int argc, char *argv[])
{
  fp = &Simple2::f;
  return 0;
}
