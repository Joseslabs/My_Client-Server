.SILENT:
CC = gcc
CFLAGS = -o
FILE1 =
FILE2 =
i =
NB_CLIENT=
SRC1 = server.c
SRC2 = client.c
exe1 = serv
exe2 = cli

$(exe1): $(SRC1)
	$(CC) $(SRC1) $(CFLAGS) $(exe1)

$(exe2): $(SRC2)
	$(CC) $(SRC2) $(CFLAGS) $(exe2)

gnome-run-for: SHELL:=/bin/bash
gnome-run-for: $(exe1) $(exe2) $(FILE1)
	gnome-terminal -- ./$(exe1) $(FILE1)
	echo "Nous allons créer $(NB_CLIENT) client(s)"
	for (( i = 0; i < $(NB_CLIENT); i++ )); do \
		if [ -d "Client_`expr $$i + 1`" ]; then \
			$(RM) -rfi Client_`expr $$i + 1`; \
		else \
			mkdir Client_`expr $$i + 1`; \
		fi ;\
		gnome-terminal -- ./$(exe2) Client_`expr $$i + 1`/$(FILE2); \
		echo "Le client n°`expr $$i + 1` vient d'être créé";\
	done

gnome-run-while: $(exe1) $(exe2) $(FILE1)
	gnome-terminal -- ./$(exe1) $(FILE1)
	echo "Si vous ne voulez plus créer de client tapez 0 puis validez sinon tapez n'importe quel autre nombre pour créer le client n°nombre ..."
	while read i; do \
		if [ "$$i" -eq '0' ]; then \
 	    	break ;\
 		fi  ;\
	   	if [ -d "Client_`expr $$i`" ]; then \
			$(RM) -rfi Client_`expr $$i`; \
		else \
			mkdir Client_`expr $$i`; \
		fi ;\
	    gnome-terminal -- ./$(exe2) Client_`expr $$i`/$(FILE2); \
	    echo "Un client vient d'être créé";\
	done

mate-run-for: SHELL:=/bin/bash
mate-run-for: $(exe1) $(exe2) $(FILE1)
	mate-terminal -- ./$(exe1) $(FILE1)
	echo "Nous allons créer $(NB_CLIENT) client(s)"
	for (( i = 0; i < $(NB_CLIENT); i++ )); do \
		if [ -d "Client_`expr $$i + 1`" ]; then \
			$(RM) -rfi Client_`expr $$i + 1`; \
		else \
			mkdir Client_`expr $$i + 1`; \
		fi ;\
		mate-terminal -- ./$(exe2) Client_`expr $$i + 1`/$(FILE2); \
		echo "Le client n°`expr $$i + 1` vient d'être créé";\
	done

mate-run-while: $(exe1) $(exe2) $(FILE1)
	mate-terminal -- ./$(exe1) $(FILE1)
	echo "Si vous ne voulez plus créer de client tapez 0 puis validez sinon tapez n'importe quel autre nombre pour créer le client n°nombre ..."
	while read i; do \
		if [ "$$i" -eq '0' ]; then \
 	    	break ;\
 		fi  ;\
	   	if [ -d "Client_`expr $$i`" ]; then \
			$(RM) -rfi Client_`expr $$i`; \
		else \
			mkdir Client_`expr $$i`; \
		fi ;\
	    mate-terminal -- ./$(exe2) Client_`expr $$i`/$(FILE2); \
	    echo "Un client vient d'être créé";\
	done

clean:
	$(RM) $(exe1) && $(RM) $(exe2) && $(RM) -rfi Client_*
clear:
	clear
