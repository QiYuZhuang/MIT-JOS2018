// Ping-pong a counter between two processes.
// Only need to start one of these -- splits into two with fork.

#include <inc/lib.h>

void
umain(int argc, char **argv)
{
	envid_t who;
	if ((who = fork()) != 0) {
		// get the ball rolling
		cprintf("send 0 from %x to %x\n", sys_getenvid(), who);
//        cprintf("father, who: %x, 0x%08x : envpdir\n", sys_getenvid(), envs[ENVX(sys_getenvid())].env_pgdir);
		ipc_send(who, 0, 0, 0);
//        cprintf("father, who: %x\n, %x", sys_getenvid(), envs[ENVX(sys_getenvid())]);
	}

	while (1) {
	    cprintf("who: %x\n", sys_getenvid());
		uint32_t i = ipc_recv(&who, 0, 0);
		if (who == 1001)
		    panic("here");
		cprintf("%x got %d from %x\n", sys_getenvid(), i, who);
		if (i == 10)
			return;
		i++;
		ipc_send(who, i, 0, 0);
		if (i == 10)
			return;
	}

}

