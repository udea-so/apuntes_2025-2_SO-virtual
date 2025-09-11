

int currentTicket = 0;  // ticket for a job
int winner = getrandom(0, totaltickets);  // randomly generated lottery winner
node_t *currentJob = head;  // job to 

while (currentJob) {
    currentTicket = currentTicket + currentJob->tickets; // largest ticket
    if (currentTicket > winner)
        break;  // lottery winner is found, exit loop
    currentJob = currentJob->next;  // advance to the next job
}
