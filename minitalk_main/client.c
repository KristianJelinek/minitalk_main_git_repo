/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjelinek < kjelinek@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:51:09 by kjelinek          #+#    #+#             */
/*   Updated: 2024/05/30 13:34:00 by kjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

void send_char(int pid, char c)
{
    int bit_count = 0;

    while (bit_count < 8)
    {
        if ((c >> (7 - bit_count)) & 1)
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        usleep(100);
        bit_count++;
    }
}

static void handle_ack(int sig)
{
    (void)sig;
    write(1, "Acknowledged\n", 13);
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        write(2, "Usage: ./client <server_pid> <string_to_send>\n", 47);
        return 1;
    }

    struct sigaction sa;
    sa.sa_handler = handle_ack;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);

    pid_t server_pid = atoi(argv[1]);
    char *message = argv[2];
    int i = 0;

    while (message[i] != '\0')
    {
        send_char(server_pid, message[i]);
        i++;
    }
    send_char(server_pid, '\0');

    pause();

    return 0;
}