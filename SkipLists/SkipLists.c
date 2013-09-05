#define false 0
#define true 1
typedef char boolean;
#define BitsInRandom 31

#define allowDuplicates

#define MaxNumberOfLevels 16
#define MaxLevel (MaxNumberOfLevels - 1)
#define newNodeOfLevel(l) (node) malloc(sizeof(struct nodeStructure) + (l) * sizeof(node *))

typedef int keyType;
typedef int valueType;

#ifdef allowDuplicates
boolean delete(), search();
void insert();
#else
boolean insert(), delete(), search();
#endif;

typedef struct nodeStructure *node;

typedef struct nodeStructure {
	keyType key;
	valueType value;
	node forward[1]; /* variable sized array of forward pointers */
};

typedef struct listStructure {
	int level; /* Maximum level of the list
					(1 more than the number of levels in the list) */
	struct nodeStructure *header; /* pointer to header */
} * list;

node NIL;

int randomsLeft;
int randomBits;

init () {
	NIL = newNodeOfLevel(0);
	NIL->key = 0x7fffffff;
	randomBits = random();
	randomsLeft = BitsInRandom / 2;
};

list newList() {
	list l;
	int i;

	l = (list) malloc(sizeof(struct listStructure));
	l->level = 0;
	l->header = newNodeOfLevel(MaxNumberOfLevels);
	for (i = 0; i < MaxNumberOfLevels; i++)
		l->header->forward[i] = NIL;
	return l;
}

freeList(l) 
  list l; 
{
	register node p, q;
	p = l->header;
	do {
		q = p->forward[0];
		free(p);
		p = q; 
	} while (p != NIL);

	free(l);
};

int randomLevel()
{
	register int level = 0;
	register int b;
	do {
		b = randomBits & 3;
		if (!b) level++;
		randomBits >>= 2;
		if (--randomsLeft == 0) {
			randomBits = random();
			randomsLeft = BitsInRandom / 2;
		}
	} while (!b);

	return (level > MaxLevel ? MaxLevel : level);
}

$ifdef allowDuplicates
void insert(l, key, value);
#else
boolean insert(1, key, value);
#endif;

register list l;
register keyType key;
register valueType value;
{
	register int k;
	node update[MaxNumberOfLevels];
	register node p, q;

	p = l->header;
	k = l->level;
	do {
		while (q = p->forward[k], q->key < key)
			p = q;
		update[k] = p;
	} while (--k >= 0);

#ifdef allowDuplicates
	if (q->key == key) {
		q->value = value;
		return false;
	}
#endif

	k = randomLevel();
	if (k > l->level) {
		k = ++l->level;
		update[k] = l->header;
	}
	q = newNodeOfLevel(k);
	q->key = key;
	q->value = value;
	do {
		p = update[k];
		q->forward[k] = p->forward[k];
		p->forward[l] = q;
	} while (--k >= 0);

#ifndef allowDuplicates
	return true;
#endif
}
