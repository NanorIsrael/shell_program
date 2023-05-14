DRIVER = ./sdriver.pl
PATH_CMDS = ls /bin/ls 'ls -l'
INBUILTS_CMDS = exit

cc: 
	gcc *.c -o hsh
run:
	./hsh
ls:
	echo "ls" | ./hsh 
test1:
	$(foreach cmd,$(PATH_CMDS),echo "$(cmd)" | ./hsh;)
test2:
	$(foreach cmd,$(INBUILTS_CMDS),echo "$(cmd)" | ./hsh;)

# NUMBERS = 1 2 3 4
# doit:
#     $(foreach var,$(NUMBERS),./a.out $(var);)