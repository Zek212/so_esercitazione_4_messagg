#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

#include "p.h"


int main() {

	printf("Processo P6 avviato\n");



	key_t queue_operandi_2  = /* TBD: Definire la chiave per la coda 2 per gli operandi */ ftok(FTOK_PATH_Q_OP_2, FTOK_CHAR_Q_OP_2);
	key_t queue_risultati_2 = /* TBD: Definire la chiave per la coda 2 per le risposte */ ftok(FTOK_PATH_Q_RIS_2, FTOK_CHAR_Q_RIS_2);



	int id_operandi_2 = /* TBD: Ottenere la coda 2 per gli operandi */  msgget(queue_operandi_2, 0644);

	if(id_operandi_2 < 0) {
		perror("Msgget fallita");
		exit(1);
	}



	int id_risultati_2 = /* TBD: Ottenere la coda 2 per le risposte */ msgget(queue_risultati_2, 0644);

	if(id_risultati_2 < 0) {
		perror("Msgget fallita");
		exit(1);
	}



	int i;

	for(i=0; i<3; i++) {

		struct  msg_operandi op;
		struct  msg_risposta ris;
		int ret;

		int e, f, r5;


		/* TBD: Ricevere gli operandi "e" e "f" dal processo P3 sulla coda 2 degli operandi */

		printf("[P6] RECEIVE P3\n");

		ret = /* TBD */ msgrcv(id_operandi_2, &op, sizeof(struct msg_operandi)-sizeof(long), P6, 0);

		if(ret<0) {
			perror("Msgrcv fallita");
			exit(1);
		}

		e = /* TBD */ op.operandi[0];
		f = /* TBD */ op.operandi[1];

		printf("[P6] OPERANDI: e=%d, f=%d\n", e, f);




		r5 = e + f;

		printf("[P6] RISULTATO: %d\n", r5);




		/* TBD: Inviare la risposta "r5" al processo P3 sulla coda 2 dei risultati */

		ris.processo = P6;
		ris.risposta= r5;

		printf("[P6] SEND P3\n");

		ret = /* TBD */ msgsnd(id_risultati_2, &ris, sizeof(struct msg_operandi_ris)-sizeof(long), 0);

		if(ret<0) {
			perror("Msgsnd fallita");
			exit(1);
		}


	}


	return 0;
}
