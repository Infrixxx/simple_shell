#include "shell.h"

/**
 * add_alias - Add or update an alias in the linked list.
 * @alias_list: Pointer to the head of the alias linked list.
 * @name: The name of the alias.
 * @value: The value of the alias.
 */
void add_alias(Alias **alias_list, char *name, char *value)
{
	if (alias_list == NULL || name == NULL || value == NULL)
		return;

	Alias *current = *alias_list;
	while (current != NULL)
	{
		if (strcmp(current->name, name) == 0)
		{
			free(current->value);
			current->value = strdup(value);
			return;
		}
		current = current->next;
	}

	Alias *new_alias = malloc(sizeof(Alias));
	if (new_alias == NULL)
		return;

	new_alias->name = strdup(name);
	new_alias->value = strdup(value);
	new_alias->next = *alias_list;
	*alias_list = new_alias;
}

/**
 * get_alias_value - Get the value of an alias by its name.
 * @alias_list: Pointer to the head of the alias linked list.
 * @name: The name of the alias.
 *
 * Return: The value of the alias, or NULL if the alias is not found.
 */
char *get_alias_value(Alias *alias_list, char *name)
{
	if (alias_list == NULL || name == NULL)
		return NULL;

	Alias *current = alias_list;
	while (current != NULL)
	{
		if (strcmp(current->name, name) == 0)
			return current->value;
		current = current->next;
	}

	return NULL;
}

/**
 * print_aliases - Print the aliases in the required format.
 * @alias_list: Pointer to the head of the alias linked list.
 * @names: Array of alias names to print, or NULL to print all aliases.
 */
void print_aliases(Alias *alias_list, char **names)
{
	Alias *current = alias_list;

	while (current != NULL)
	{
		if (names == NULL)
			printf("%s='%s'\n", current->name, current->value);
		else
		{
			char **name_ptr = names;
			while (*name_ptr != NULL)
			{
				if (strcmp(current->name, *name_ptr) == 0)
				{
					printf("%s='%s'\n", current->name, current->value);
					break;
				}
				name_ptr++;
			}
		}
		current = current->next;
	}
}
