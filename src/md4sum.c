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
#include <string.h>
#include "nfhl.h"
#include "slib.h"
#define iscomment(c) (int )(c == 0x09 || c == 0x0a || c == 0x0b || c == 0x0c || c == 0x0d || c == 0x20 || c == '#')
void usage      (void);
int  md         (const char *, unsigned long *);

int main(int argc, char *argv[])
{
   FILE         *fp     = NULL        ;
   char          fpt[1024-128]        ;
   int           e      = 0           ;
   int           i      = 0           ;
   unsigned long IH[0x08]             ;
   unsigned long  H[0x08]             ;
   char  mode[2], h[1024]             ; /* (128)hash message + file name */
   unsigned char l      = 0x00        ;

   if((argc > 1) && !((strcmp(argv[1], "-c") == 0)||(strcmp(argv[1], "-v") == 0))){
      for (i = 1; i < argc; i++) {
         if(md(argv[i], IH) == 0) {
            for(e=0; e<0x04; e++) printf("%08lx", IH[e]); printf("  %s\n", argv[i]);
         } else {
            fprintf(stderr, "md4sum unable to open: %s\n", argv[i]);
         }
      }
      return 0;
   }

   i = 0; e = 0;
   if((argc == 3) && ((strcmp(argv[1], "-c") == 0) || (strcmp(argv[1], "-v") == 0))){
      if ((fp = fopen(argv[2], "rb")) == NULL) { printf("md4sum unable to open: %s\n", argv[2]); return 0; }
      while(!feof(fp)) {
         if(fgets(h, 1024, fp)) {
            if(iscomment(h[0])) continue;
            gethashul(h, H, mode, fpt, 4);
            md(fpt, IH);
            l = (unsigned char )cmpul(IH, H, 4);
            printf("%s : %s\n", (!l) ? "[  OK  ]" : "[FAILED]" ,fpt);
            if(l) e++;
            i++;
         }
      }
      if(e>0) fprintf(stderr, "!WARNING!: %d of %d didn't have matching hash.\n", e, i);
      return 0;
   }

   return 0;
}

int md(const char *fpt, unsigned long *IH)
{
   unsigned long c    = 0x00000000UL;
   unsigned long e    = 0x00000000UL;
   unsigned long i    = 0x00000000UL;
   union {
      unsigned long long qword      ;
      unsigned long      dword[0x02];
   } byte;
   FILE *fp           = NULL        ;
   union {
      unsigned long      dword[0x10];
      unsigned short      word[0x20];
      unsigned char       byte[0x40];
   } M;
   
   if(strcmp(fpt, "-")) {
      if(checkf(fpt) == 1) return 1;
      fp = fopen(fpt, "rb");
   } else fp = stdin;

   if(fpt && fp) {
      byte.qword = 0x0000000000000000ULL;   
      c          = 0x00000001UL;
      for(e=0; e<0x04; e++) IH[e]         = 0x00000000UL; /* erase first */
      while (!feof(fp)) {
         for(e=0; e<0x10; e++) M.dword[e] = 0x00000000UL; /* erase first */
         if((i = fread(&M, 1, 0x40, fp)) == 0x40) {
            { md4(M.dword, IH, c); c = 0; }
            byte.qword = byte.qword + 0x40;
         } else {
            if (i == 0) {
               byte.qword   = (byte.qword + i) << 3;
               M.dword[0x0] = 0x00000080UL; 
               M.dword[0xe] = (byte.dword[0x0]);
               M.dword[0xf] = (byte.dword[0x1]);
               md4(M.dword, IH, c);
            } else {
               M.byte [ i ] = 0x80;
               if(i < 0x38) {
                  byte.qword   = (byte.qword + i) << 3;
                  M.dword[0xe] = (byte.dword[0x0]);
                  M.dword[0xf] = (byte.dword[0x1]);
                  md4(M.dword, IH, c);
               } else {
                  M.dword[0xe] = (M.dword[0xe]);
                  M.dword[0xf] = (M.dword[0xf]);
                  { md4(M.dword, IH, c); c = 0;}
                  for(e=0; e<0x10; e++) M.dword[e] = 0x00000000UL; /* erase first */
                  byte.qword   = (byte.qword + i) << 3;
                  M.dword[0xe] = (byte.dword[0x0]);
                  M.dword[0xf] = (byte.dword[0x1]);
                  md4(M.dword, IH, c);
               }
            }
         }
      }
      fclose(fp);
   } else {
      return 1;
   }
   for(e=0; e<0x04; e++) IH[e]         = swapul(IH[e]);

   return 0;
}
