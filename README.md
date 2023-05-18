# shell_program
a c shell program



## Limitations
- Shell works in only interactive mode

- Heavy use of inbuilt functions

- Can not handle file manipulations

- aliases, builtins and the environment
- No piping or redirection
- No globbing

# Bugs
- Handle echo "/bin/ls" | ./hsh
- alias ls="ls -F"  
- alias dirA="echo working directory is $PWD" 
- bash: alias: {aliasname}: not found
- unalias
- using quoted command like 'ls'
- unalias: usage: unalias [-a] name [name ...]
-
# Test suit
consult make file (not an exhustive list).
- use checker.sh for now


# Handle built-ins
work on the built in functions
- exit
- cd
- alias
- help
- setenv