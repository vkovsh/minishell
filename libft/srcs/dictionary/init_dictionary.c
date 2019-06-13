#include "libft.h"

static void		insert(t_dictionary *d, t_node *item)
{
	d->size++;
	ft_bintree_add(&(d->array), ft_bintree_new(item), d->compare);
}

static void		del_item(t_dictionary *d,
				const void *key,
				const size_t key_size)
{
	d->array = ft_bintree_remove(d->array,
					key,
					key_size,
					d->compare,
					d->del_node);
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
	ft_bintree_del(&(d->array),
			d->del_node);
	d->array = NULL;
}

// static void		**data(t_dictionary *d)
// {

// }

void			init_dictionary(t_dictionary **d,
					t_compare_keys cmp_f,
					t_del_node del_node)
{
	*d = (t_dictionary *)malloc(sizeof(t_dictionary));
	(*d)->array = NULL;
	(*d)->size = 0;
	(*d)->compare = cmp_f;
	(*d)->find = find;
	(*d)->insert = insert;
	(*d)->del_item = del_item;
	(*d)->clear = clear;
	(*d)->del_node = del_node;
}