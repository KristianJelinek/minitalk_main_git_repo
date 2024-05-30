/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjelinek < kjelinek@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:44:12 by kjelinek          #+#    #+#             */
/*   Updated: 2024/05/30 13:34:24 by kjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

static void handle_signal(int sig, siginfo_t *info, void *context)
{
    static char c = 0;
    static int bit_count = 0;
    static pid_t client_pid = 0;

    (void)context;

    if (!client_pid)
        client_pid = info->si_pid;
    if (sig == SIGUSR1)
        c |= (1 << (7 - bit_count));
    bit_count++;
    if (bit_count == 8)
    {
        if (c == '\0')
        {
            write(1, "\n", 1);
            kill(client_pid, SIGUSR1);
            client_pid = 0;
        }
        else
        {
            write(1, &c, 1);
        }
        c = 0;
        bit_count = 0;
    }
}

int main()
{
    struct sigaction sa;
    sa.sa_sigaction = handle_signal;
    sa.sa_flags = SA_SIGINFO;

    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    printf("Server PID: %d\n", getpid());
    while (1)
    {
        pause();
    }
    return 0;
}