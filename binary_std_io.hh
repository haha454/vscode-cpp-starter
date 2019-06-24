#ifndef BINARY_STD_IO
#define BINARY_STD_IO

#include <cstdio>

// little endian binary standard I/O
// Decimal: 133124
// Hex: 0x04080200
// binary:
// 00000100	00001000	00000010	00000000
// bits 7-0	bits 15-8	bits 24-16	bits 31-25
class BinaryStdOut
{
private:
   char buf, pos;

public:
   BinaryStdOut() : buf(0), pos(7) {}

   void put_bit(bool bit)
   {
      if (pos == 0)
      {
         fputc(buf + bit, stdout);
         pos = 7;
         buf = 0;
         return;
      }
      buf += bit << pos--;
   }

   void put_char(char ch)
   {
      for (int i = 7; i >= 0; i--)
      {
         put_bit(ch >> i);
         ch &= (1 << i) - 1;
      }
   }

   void put_int(int num)
   {
      for (int i = 0; i < 4; i++)
      {
         put_char(num & 255);
         num >>= 8;
      }
   }

   void close()
   {
      fputc(buf, stdout);
      fflush(stdout);
   }
};

class BinaryStdIn
{
private:
   char buf, bits;

public:
   BinaryStdIn() : buf(0), bits(0) {}

   bool read_bit()
   {
      if (!bits)
      {
         bits = 8;
         buf = fgetc(stdin);
      }
      bits--;
      return buf & (1 << bits);
   }

   char read_char()
   {
      char result = 0;
      for (int i = 0; i < 8; i++)
      {
         bool bit = read_bit();
         result = (result << 1) + bit;
      }
      return result;
   }

   int read_int()
   {
      int result = 0;
      for (int i = 0; i < 4; i++)
      {
         char ch = read_char();
         result += ch << (i << 3);
      }
      return result;
   }
};

#endif