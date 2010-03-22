# ------------------------------------------------------------------------
# Copyright (c) 2010 Arif Endro Nugroho
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. The name of Arif Endro Nugroho may not be used to endorse or promote
#    products derived from this software without specific prior written
#    permission.
# 
# THIS SOFTWARE IS PROVIDED BY ARIF ENDRO NUGROHO "AS IS" AND ANY EXPRESS
# OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL ARIF ENDRO NUGROHO BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
# 
# End Of License.
# ------------------------------------------------------------------------
#
# options: -std=c99 supporting 'long long' data types, -D_BSD_SOURCE for file stat operation, -fno-builtin to disable GCC builtin function like isspace.
CC     = gcc
CFLAGS = -Wall -Wextra -Wshadow -Wconversion -Wpointer-arith -Wbad-function-cast -Wcast-align -Wwrite-strings -Wmissing-noreturn -Wmissing-format-attribute -Wredundant-decls -Winline -Wdisabled-optimization -Wmissing-prototypes -O2 -pedantic -std=c99 -D_BSD_SOURCE -fno-builtin
BINDIR = bin
SRC    = md4sum.c md5sum.c rmd128sum.c rmd160sum.c sha1sum.c sha224sum.c sha256sum.c sha384sum.c sha512sum.c
SFXWIN = .exe
BIN    = $(patsubst %.c, $(BINDIR)/%$(SFXWIN), $(SRC))
NFHL   = ../nfhl
BCFLAGS= -I$(NFHL)/include -L$(NFHL)/lib lib/slib.o

vpath %.c src

all: lib/slib.o $(BIN)

lib/slib.o : slib.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BINDIR)/%$(SFXWIN) : %.c
	$(CC) $(CFLAGS) $(BCFLAGS) -o $@ $< -lnfhl

clean:
	-@echo -- remove these files: $(BIN) --
