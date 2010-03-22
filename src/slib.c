/* ------------------------------------------------------------------------
 * Copyright (c) 2010 Arif Endro Nugroho
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of Arif Endro Nugroho may not be used to endorse or promote
 *    products derived from this software without specific prior written
 *    permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY ARIF ENDRO NUGROHO "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ARIF ENDRO NUGROHO BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 * 
 * End Of License.
 * ------------------------------------------------------------------------
 */
#include <stdio.h>
#include <sys/stat.h>
#include "slib.h"

void gethashul(const char *s, unsigned long *h, char *mode, char *fn, const int i)
{
   switch(i) {
      case 4 :
         sscanf(s, "%08lx%08lx%08lx%08lx%2c%[^\n\r]", 
               &h[0], &h[1], &h[2], &h[3],        mode, fn);
      break;
      case 5 :
         sscanf(s, "%08lx%08lx%08lx%08lx%08lx%2c%[^\n\r]", 
               &h[0], &h[1], &h[2], &h[3], &h[4], mode, fn);
      break;
      case 6 :
         sscanf(s, "%08lx%08lx%08lx%08lx%08lx%08lx%2c%[^\n\r]", 
               &h[0], &h[1], &h[2], &h[3], &h[4], &h[5], mode, fn);
      break;
      case 7 :
         sscanf(s, "%08lx%08lx%08lx%08lx%08lx%08lx%08lx%2c%[^\n\r]", 
               &h[0], &h[1], &h[2], &h[3], &h[4], &h[5], &h[6], mode, fn);
      break;
      case 8 :
         sscanf(s, "%08lx%08lx%08lx%08lx%08lx%08lx%08lx%08lx%2c%[^\n\r]", 
               &h[0], &h[1], &h[2], &h[3], &h[4], &h[5], &h[6], &h[7], mode, fn);
      break;
   }
}

void gethashull(const char *s, unsigned long long *h, char *mode, char *fn, const int i)
{
   switch(i) {
      case 4 :
         sscanf(s, "%016llx%016llx%016llx%016llx%2c%[^\n\r]", 
               &h[0], &h[1], &h[2], &h[3],        mode, fn);
      break;
      case 5 :
         sscanf(s, "%016llx%016llx%016llx%016llx%016llx%2c%[^\n\r]", 
               &h[0], &h[1], &h[2], &h[3], &h[4], mode, fn);
      break;
      case 6 :
         sscanf(s, "%016llx%016llx%016llx%016llx%016llx%016llx%2c%[^\n\r]", 
               &h[0], &h[1], &h[2], &h[3], &h[4], &h[5], mode, fn);
      break;
      case 7 :
         sscanf(s, "%016llx%016llx%016llx%016llx%016llx%016llx%016llx%2c%[^\n\r]", 
               &h[0], &h[1], &h[2], &h[3], &h[4], &h[5], &h[6], mode, fn);
      break;
      case 8 :
         sscanf(s, "%016llx%016llx%016llx%016llx%016llx%016llx%016llx%016llx%2c%[^\n\r]", 
               &h[0], &h[1], &h[2], &h[3], &h[4], &h[5], &h[6], &h[7], mode, fn);
      break;
   }
}

unsigned long cmpul(const unsigned long *a, const unsigned long *b, const int i)
{
   switch(i) {
      case 4 : return ((a[0] ^ b[0]) | (a[1] ^ b[1]) | (a[2] ^ b[2]) | (a[3] ^ b[3])); /* 128-bit */
      case 5 : return ((a[0] ^ b[0]) | (a[1] ^ b[1]) | (a[2] ^ b[2]) | (a[3] ^ b[3]) |
                       (a[4] ^ b[4])                                                ); /* 160-bit */
      case 7 : return ((a[0] ^ b[0]) | (a[1] ^ b[1]) | (a[2] ^ b[2]) | (a[3] ^ b[3]) |
                       (a[4] ^ b[4]) | (a[5] ^ b[5]) | (a[6] ^ b[6])                ); /* 224-bit */
      case 8 : return ((a[0] ^ b[0]) | (a[1] ^ b[1]) | (a[2] ^ b[2]) | (a[3] ^ b[3]) |
                       (a[4] ^ b[4]) | (a[5] ^ b[5]) | (a[6] ^ b[6]) | (a[7] ^ b[7])); /* 256-bit */
   }
   return 1;
}

unsigned long long cmpull(const unsigned long long *a, const unsigned long long *b, const int i)
{
   switch(i) {
/*    case 4 : return ((a[0] ^ b[0]) | (a[1] ^ b[1]) | (a[2] ^ b[2]) | (a[3] ^ b[3])); // 256-bit */
      case 6 : return ((a[0] ^ b[0]) | (a[1] ^ b[1]) | (a[2] ^ b[2]) | (a[3] ^ b[3]) |
                       (a[4] ^ b[4]) | (a[5] ^ b[5])                                ); /* 384-bit */
      case 8 : return ((a[0] ^ b[0]) | (a[1] ^ b[1]) | (a[2] ^ b[2]) | (a[3] ^ b[3]) |
                       (a[4] ^ b[4]) | (a[5] ^ b[5]) | (a[6] ^ b[6]) | (a[7] ^ b[7])); /* 512-bit */
   }
   return 1;
}

unsigned long swapul(const unsigned long l)
{
   union {
   unsigned long      dword     ;
   unsigned short      word[0x2];
   unsigned char       byte[0x4];
   }a,b;

   b.dword = l;

   a.byte[0x0] = b.byte[0x3];
   a.byte[0x1] = b.byte[0x2];
   a.byte[0x2] = b.byte[0x1];
   a.byte[0x3] = b.byte[0x0];

   return a.dword;
}

unsigned long long swapull(const unsigned long long l)
{
   union {
   unsigned long long      qword;
   unsigned long      dword[0x2];
   unsigned short      word[0x4];
   unsigned char       byte[0x8];
   }a,b;

   b.qword = l;

   a.byte[0x0] = b.byte[0x7];
   a.byte[0x1] = b.byte[0x6];
   a.byte[0x2] = b.byte[0x5];
   a.byte[0x3] = b.byte[0x4];
   a.byte[0x4] = b.byte[0x3];
   a.byte[0x5] = b.byte[0x2];
   a.byte[0x6] = b.byte[0x1];
   a.byte[0x7] = b.byte[0x0];

   return a.qword;
}

int checkf(const char *fpt)
{
   struct stat sb                   ;
   if (stat(fpt, &sb) == -1) {
      perror(fpt);
      return 1;
   }
   switch (sb.st_mode & S_IFMT) {
      case S_IFBLK:  fprintf(stderr, "`%s' is a block device\n", fpt); return 1;
      case S_IFCHR:  fprintf(stderr, "`%s' is a character device\n", fpt); return 1;
      case S_IFDIR:  fprintf(stderr, "`%s' is a directory\n", fpt); return 1;
      case S_IFIFO:  fprintf(stderr, "`%s' is a FIFO/pipe\n", fpt); return 1;
/*    case S_IFLNK:  fprintf(stderr, "`%s' is a symlink\n", fpt); return 1; */
      case S_IFREG:  /* fprintf(stderr, "`%s' is a regular file\n", fpt); */ return 0;
/*    case S_IFSOCK: fprintf(stderr, "`%s' is a socket\n", fpt); return 1; */
      default:       fprintf(stderr, "`%s' is a unknown?\n", fpt); return 1;
   }
   return 0;
}

int isempty(const char *fpt)
{
   struct stat sb                   ;
   if (stat(fpt, &sb) == -1) {
      perror(fpt);
      return 1;
   }
   if((long long)sb.st_size == 0) {
      fprintf(stderr, "`%s' is an empty file.\n", fpt);
      return 1;
   } else return 0;
}
