#ifndef DICTIONARY_H
# define DICTIONARY_H
# include "bintree.h"
# define INSERT(d,i) d->insert(d,i)
# define DELETE(d,k) d->del_item(d,k) 
# define FIND(d,k,size) d->find(d,k,size)
# define CLEAR(d) d->clear(d)
# define ITEM(k,k_s,v,v_s) (t_item){k,k_s,v,v_s}
# define SIZE(d) (d->size)

struct				s_item;
struct				s_dictionary;

typedef void		(*t_insert)(struct s_dictionary *d, struct s_item item);
typedef void		(*t_del_item)(struct s_dictionary *d, void *key, size_t key_size);
typedef void		*(*t_find)(struct s_dictionary *d, void *key, size_t key_size);
typedef void		(*t_clear)(struct s_dictionary *d);

typedef struct		s_item
{
	void			*key;
	size_t			key_size;
	void			*value;
	size_t			value_size;
}					t_item;

typedef struct		s_dictionary
{
	t_bintree		*array;
	size_t			size;
	t_insert		insert;
	t_del_item		del_item;
	t_find			find;
	t_compare_keys	compare;
	t_clear			clear;
	t_del_node		del_node;
}					t_dictionary;

void				init_dictionary(t_dictionary **d,
						t_compare_keys cmp_f,
						t_del_node del_node);
#endif