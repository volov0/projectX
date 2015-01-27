/**
 * @file threads.c
 * @author volovo
 * @date 27.01.2015
 * @brief Multithreading sample.
 * @detail ... 
 */

#include <string.h>
#include <stdio.h>


void sell_tickets(int agent_id, int num_tickets_to_sell);

/**
 * Function main
 * -------------
 */
int main(int argc, char *argv[]) {
	int num_agents = 10;
	int num_tickets = 150;
	int agent;
	
	for (agent = 0; agent <= num_agents; agent++) {   
		sell_tickets(agent, num_tickets / num_agents);
	}

	return 0;
}

void sell_tickets(int agent_id, int num_tickets_to_sell) {
	while (num_tickets_to_sell > 0) {
		printf("Agent %d prodava jizdenku.\n", agent_id);
		num_tickets_to_sell--;
	}
	printf("Agent %d: hotovo.\n", agent_id);
}
