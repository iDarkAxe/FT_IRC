#ifndef SIGNALS_HPP
#define SIGNALS_HPP

#include <csignal>

extern sig_atomic_t g_sig;

int signal_init(void);

#endif // SIGNALS_HPP
