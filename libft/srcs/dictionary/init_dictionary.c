#include "dictionary.h"
#include "ft_printf.h"

static void			insert(t_dictionary *d, t_node *item)
{
	t_bintree		*exist;

	exist = NULL;
	exist = ft_bintree_find(&(d->array),
				item->key,
				item->key_size, d->compare_init);
	if (exist == NULL)
	{
		d->size++;
		ft_bintree_add(&(d->array),
				ft_bintree_new(item), d->compare_init);
	}
	else
	{
		d->del_struct.del_v(exist->node.value);
		exist->node.value = ft_memalloc(item->value_size);
		ft_memmove(exist->node.value, item->value, item->value_size);
	}
}

static void			del_item(t_dictionary *d,
					const void *key,
					const size_t key_size)
{
	int res = 0;
	
	res = ft_bintree_remove(&(d->array),
								key,
								key_size,
								d->compare_init,
								&(d->del_struct));
	if (res == 0)
	{
		d->size--;
	}
}

static void		*find(t_dictionary *d, const void *key, const size_t key_size)
{
	t_bintree	*node;

	node = ft_bintree_find(&(d->array),
			key,
			key_size,
			d->compare_find);
	return (node ? node->node.value : NULL);
}

static void		clear(t_dictionary *d)
{
	if (d->array != NULL)
	{
		ft_bintree_del(&(d->array), &(d->del_struct));
		d->array = NULL;
		d->size = 0;
	}
}

static void			add_node(t_node *node, void *out)
{
	t_dictionary	*new_d;

	new_d = (t_dictionary *)out;
	INSERT(new_d, node);
}

static t_dictionary	*clone(t_dictionary *d)
{
	t_dictionary	*new_d;

	new_d = (t_dictionary *)malloc(sizeof(t_dictionary));
	new_d->size = 0;
	new_d->array = NULL;
	new_d->clear = d->clear;
	new_d->clone = d->clone;
	new_d->compare_init = d->compare_init;
	new_d->compare_find = d->compare_find;
	new_d->data = d->data;
	new_d->del_item = d->del_item;
	new_d->del_struct = d->del_struct;
	new_d->find = d->find;
	new_d->insert = d->insert;
	ft_bintree_infix_traverse(&(d->array), add_node, new_d);
	return (new_d);
}

static void			add_arg_from_dict(t_node *node, void *out)
{
	static int index = 0;
	void			**args;

	if (node == NULL)
	{
		index = 0;
	}
	else
	{
		args = (void **)out;
		args[index++] = ft_strjoin_free(node->key, ft_strjoin("=", node->value), FALSE, TRUE);
	}
}

static void			**data(t_dictionary *d)
{
	void			**args;

	if (d->size == 0)
	{
		return (NULL);
	}
	args = (void **)malloc(sizeof(void *) * (d->size + 1));
	args[d->size] = NULL;
	add_arg_from_dict(NULL, NULL);
	ft_bintree_infix_traverse(&(d->array), add_arg_from_dict, (void *)args);
	return (args);
}

void			init_dictionary(t_dictionary **d,
						t_compare_keys cmp_f_init,
						t_compare_keys cmp_f_find,
						const t_del *del_struct)
{
	*d = (t_dictionary *)malloc(sizeof(t_dictionary));
	(*d)->array = NULL;
	(*d)->size = 0;
	(*d)->compare_init = cmp_f_init;
	(*d)->compare_find = cmp_f_find;
	(*d)->find = find;
	(*d)->insert = insert;
	(*d)->del_item = del_item;
	(*d)->clear = clear;
	(*d)->del_struct = *del_struct;
	(*d)->clone = clone;
	(*d)->data = data;
}