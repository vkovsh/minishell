#include "libft.h"

static void		insert(t_dictionary *d, t_node *item)
{
	t_bintree	*exist;

	exist = NULL;
	exist = ft_bintree_find(&(d->array), item->key, item->key_size, d->compare);
	if (exist == NULL)
	{
		d->size++;
		ft_bintree_add(&(d->array), ft_bintree_new(item), d->compare);
	}
	else
	{
		d->del_struct.del_v(exist->node.value);
		exist->node.value = ft_memalloc(item->value_size);
		ft_memmove(exist->node.value, item->value, item->value_size);
	}
}

static void		del_item(t_dictionary *d,
				const void *key,
				const size_t key_size)
{
	d->array = ft_bintree_remove(d->array,
								key,
								key_size,
								d->compare,
								&(d->del_struct));
}

static void		*find(t_dictionary *d, const void *key, const size_t key_size)
{
	t_bintree	*node;

	node = ft_bintree_find(&(d->array),
			key,
			key_size,
			d->compare);
	return (node ? node->node.value : NULL);
}

static void		clear(t_dictionary *d)
{
	ft_bintree_del(&(d->array), &(d->del_struct));
	d->array = NULL;
}

static t_dictionary	*clone(const t_dictionary *d)
{
	t_dictionary	*new_d;

	new_d = (t_dictionary *)malloc(sizeof(t_dictionary));
	new_d->clear = d->clear;
	new_d->clone = d->clone;
	new_d->compare = d->compare;
	new_d->data = d->data;
	new_d->del_item = d->del_item;
	new_d->del_struct = d->del_struct;
	new_d->find = d->find;
	new_d->insert = d->insert;
	return (new_d);
}

static void		**data(const t_dictionary *d)
{
	(void)d;
	return NULL;
}

void			init_dictionary(t_dictionary **d,
					t_compare_keys cmp_f,
					const t_del *del_struct)
{
	*d = (t_dictionary *)malloc(sizeof(t_dictionary));
	(*d)->array = NULL;
	(*d)->size = 0;
	(*d)->compare = cmp_f;
	(*d)->find = find;
	(*d)->insert = insert;
	(*d)->del_item = del_item;
	(*d)->clear = clear;
	(*d)->del_struct = *del_struct;
	(*d)->clone = clone;
	(*d)->data = data;
}