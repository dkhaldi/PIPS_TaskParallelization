/*************
 * Header file for signal_handler.c
 * 1999 E. Rouat
 * $Id: signal_handler.h 5188 2011-12-31 09:49:52Z coelho $
 ************/

#ifndef SIGNAL_HANDLER_H_INCLUDED
#define SIGNAL_HANDLER_H_INCLUDED

RETSIGTYPE ft_sigintr(void);
RETSIGTYPE sigfloat(int sig, int code);
RETSIGTYPE sigstop(void);
RETSIGTYPE sigcont(void);
RETSIGTYPE sigill(void);
RETSIGTYPE sigbus(void);
RETSIGTYPE sigsegv(void);
RETSIGTYPE sig_sys(void);

extern JMP_BUF jbuf;

#endif
