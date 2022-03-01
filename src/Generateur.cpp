#include "Generateur.hpp"


void Generateur::initGen()
{
   unsigned int seed = 48;


}

void Generateur::test64()
{
   MtRng64 mt;
   int i;
   unsigned long long init[4] = {0x12345ULL, 0x23456ULL, 0x34567ULL, 0x45678ULL};
   size_t length = 4;

   mt.init(init, length);

   printf("1000 outputs of genrand64_int64()\n");
   for (i = 0; i < 1000; i++)
   {
#if defined(VISUALCPP)
      // Visual C++ does not have ll prefix. You should use I64 prefix instead.
      printf("%20I64u ", mt.getUint());
#else
      printf("%20llu ", mt.getUint());
#endif
      if (i % 5 == 4)
         printf("\n");
   }

   printf("\n1000 outputs of genrand64_real2()\n");
   for (i = 0; i < 1000; i++)
   {
      printf("%10.8f ", mt.getReal2());
      if (i % 5 == 4)
         printf("\n");
   }
}

void Generateur::test32()
{
   MtRng32 mt;
   int i;
   unsigned int init[4] = {0x123U, 0x234U, 0x345U, 0x456U};
   size_t length = 4;
   mt.init(init, length);

   printf("1000 outputs of genrand_int32()\n");
   for (i = 0; i < 1000; i++)
   {
      printf("%10lu ", mt.getUint());
      if (i % 5 == 4)
         printf("\n");
   }

   printf("\n1000 outputs of genrand_real2()\n");
   for (i = 0; i < 1000; i++)
   {
      printf("%10.8f ", mt.getReal2());
      if (i % 5 == 4)
         printf("\n");
   }
}

void Generateur::mersenneTest()
{
   test32();
   puts("");
   puts("");
   test64();
}
