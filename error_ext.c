#include "main.h"

void file_error(g_data *info)
{
    _eprint_one_line("Usage: ");
    _eprint_one_line(info->file_name);
    _eprint_one_line(" [batch_file]\n");
}

void print_alias(l_node *tmp)
{
    _print_one_line(tmp->data);
    _print_one_line("=");
    _print_one_line(tmp->sub_data);
    _putchar('\n');
}