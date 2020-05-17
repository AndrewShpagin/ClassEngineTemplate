#pragma once
#include "StackArray.h"
//simplified and lightweight version of uni_hash
//very simple key->element correspondence to make fast correspondence tables
//supports multiple elements by key
template <class Elm, class Key, int TableSize = 256, int PoolSectionSize = 256>
class simple_hash {
	struct __temp {
		Elm E;
		Key K;
		int next;
	};
	StackArray<__temp, PoolSectionSize> Pool;
	StackArray<int, PoolSectionSize> Deleted;
	int Table[TableSize];
	int DynSize;
	void _testsize();
public:
	simple_hash() {
		DynSize = 0;
	}
	~simple_hash() {
		clear();
	}
	//setting table size allowed only when hash is still empty
	void set_table_size(int sz);
	//get element by key
	inline Elm* get(const Key& v, int SubIndex = 0);
	//add element e by key k and get pointet to element in hash
	inline Elm* add(const Key& k, const Elm& e);
	inline Elm* add_once(const Key& k, const Elm& e);
	inline Elm* add_uniq(const Key& k, const Elm& e);
	inline void del(const Key& k);
	inline void del_elm(const Key& k, const Elm& e);
	//just add element e by key k
	inline void add_quick(const Key& k, const Elm& e);
	//total amount of elements
	inline int size();
	//amount of elements with key k
	inline int size(const Key& k);
	//scan, scan_key support routines
	inline void start_scan(Key K, hash_context& ct);
	inline void start_scan(hash_context& ct);
	inline Elm* next(hash_context& ct);
	inline void clear();
	inline Key* _key(hash_context* co) const;
	inline bool test_integrity();
};

template <class Elm, class Key, int TableSize, int PoolSectionSize>
inline void simple_hash<Elm, Key, TableSize, PoolSectionSize>::set_table_size(int sz) {
	if (DynSize == 0)DynSize = -sz;
}

template <class Elm, class Key, int TableSize, int PoolSectionSize>
inline void simple_hash<Elm, Key, TableSize, PoolSectionSize>::_testsize() {
	if (DynSize <= 0) {
		if (DynSize == 0)DynSize = TableSize;
		else DynSize = -DynSize;
		if (DynSize > TableSize)DynSize = TableSize;
		memset(Table, 0, DynSize * 4);
	}
}
template <class Elm, class Key, int TableSize, int PoolSectionSize>
inline Elm* simple_hash<Elm, Key, TableSize, PoolSectionSize>::get(const Key& v, int SubIndex) {
	if (DynSize == 0)return NULL;
	int h = DWORD(v) % DynSize;
	int ptr = Table[h];
	while (ptr > 0) {
		__temp& vv = Pool[ptr - 1];
		if (vv.K == v) {
			if (SubIndex == 0)return &vv.E;
			SubIndex--;
		}
		ptr = vv.next;
	}
	return NULL;
}

template <class Elm, class Key, int TableSize, int PoolSectionSize>
inline void simple_hash<Elm, Key, TableSize, PoolSectionSize>::clear() {
	DynSize = 0;
	Pool.Clear();
}

template <class Elm, class Key, int TableSize, int PoolSectionSize>
inline Elm* simple_hash<Elm, Key, TableSize, PoolSectionSize>::add(const Key& k, const Elm& e) {
	_testsize();
	DWORD D = DWORD(k);
	DWORD h = D % DynSize;
	int ptr = Table[h];
	if (Deleted.Count()) {
		ptr = Deleted.pop_back();
		__temp& vv = Pool[ptr];
		vv.E = e;
		vv.K = k;
		vv.next = ptr;
	}
	else {
		__temp vv;
		vv.E = e;
		vv.K = k;
		vv.next = ptr;
		ptr = Pool.Add(vv);
	}
	Table[h] = ptr + 1;
	return &Pool[ptr].E;
}

template <class Elm, class Key, int TableSize, int PoolSectionSize>
inline Elm* simple_hash<Elm, Key, TableSize, PoolSectionSize>::add_once(const Key& k, const Elm& e) {
	Elm* e1 = get(k);
	if (e1)return e1;
	return add(k, e);
}
template <class Elm, class Key, int TableSize, int PoolSectionSize>
inline Elm* simple_hash<Elm, Key, TableSize, PoolSectionSize>::add_uniq(const Key& k, const Elm& e) {
	_testsize();
	DWORD D = DWORD(k);
	DWORD h = D % DynSize;
	int ptr = Table[h] - 1;
	while (ptr >= 0) {
		__temp* t = &Pool[ptr];
		if (t->E == e && t->K == k)return &t->E;
		ptr = t->next - 1;
	}
	if (Deleted.Count()) {
		ptr = Deleted.pop_back();
		__temp& vv = Pool[ptr];
		vv.E = e;
		vv.K = k;
		vv.next = ptr;
	}
	else {
		__temp vv;
		vv.E = e;
		vv.K = k;
		vv.next = ptr;
		ptr = Pool.Add(vv);
	}
	Table[h] = ptr + 1;
	return &Pool[ptr].E;
}

template <class Elm, class Key, int TableSize, int PoolSectionSize>
inline void simple_hash<Elm, Key, TableSize, PoolSectionSize>::del(const Key& k) {
	if (DynSize == 0)return;
	DWORD D = DWORD(k);
	DWORD h = D % DynSize;
	int ptr = Table[h] - 1;
	int pptr = -1;
	while (ptr >= 0) {
		__temp* t = &Pool[ptr];
		int next = t->next;
		if (t->K == k) {
			if (pptr == -1)Table[h] = next;
			else Pool[pptr].next = next;
			t->next = -1;
			Deleted.Add(ptr);
		}
		else {
			pptr = ptr;
		}
		ptr = next - 1;
	}
}
template <class Elm, class Key, int TableSize, int PoolSectionSize>
inline void simple_hash<Elm, Key, TableSize, PoolSectionSize>::del_elm(const Key& k, const Elm& e) {
	DWORD D = DWORD(k);
	DWORD h = D % DynSize;
	int ptr = Table[h] - 1;
	int pptr = -1;
	while (ptr >= 0) {
		__temp* t = &Pool[ptr];
		int next = t->next;
		if (t->K == k && t->E == e) {
			if (pptr == -1)Table[h] = next;
			else Pool[pptr].next = next;
			t->next = -1;
			Deleted.Add(ptr);
		}
		else {
			pptr = ptr;
		}
		ptr = next - 1;
	}
}

template <class Elm, class Key, int TableSize, int PoolSectionSize>
inline void simple_hash<Elm, Key, TableSize, PoolSectionSize>::add_quick(const Key& k, const Elm& e) {
	_testsize();
	DWORD D = DWORD(k);
	DWORD h = D % DynSize;
	int ptr = Table[h];
	if (Deleted.Count()) {
		ptr = Deleted.pop_back();
		__temp& vv = Pool[ptr];
		vv.E = e;
		vv.K = k;
		vv.next = ptr;
	}
	else {
		__temp vv;
		vv.E = e;
		vv.K = k;
		vv.next = ptr;
		ptr = Pool.Add(vv);
	}
	Table[h] = ptr + 1;
}

template <class Elm, class Key, int TableSize, int PoolSectionSize>
inline int simple_hash<Elm, Key, TableSize, PoolSectionSize>::size() {
	return Pool.Count() - Deleted.Count();
}

template <class Elm, class Key, int TableSize, int PoolSectionSize>
inline int simple_hash<Elm, Key, TableSize, PoolSectionSize>::size(const Key& k) {
	if (DynSize == 0)return 0;
	int h = DWORD(k) % DynSize;
	int ptr = Table[h];
	int n = 0;
	while (ptr >= 0) {
		__temp& vv = Pool[ptr - 1];
		if (vv.K == k)n++;
		ptr = vv.next;
	}
	return n;
}

template <class Elm, class Key, int TableSize, int PoolSectionSize>
inline void simple_hash<Elm, Key, TableSize, PoolSectionSize>::start_scan(Key K, hash_context& ct) {
	_testsize();
	ct.ScanAll = false;
	DWORD D = (DWORD)K;
	D %= DynSize;
	ct.ptr = NULL;
	int ptr = Table[D];
	if (ptr > 0) {
		__temp* t = &Pool[ptr - 1];
		while (t) {
			if (t->K == K) {
				ct.ptr = t;
				return;
			}
			int nn = t->next;
			if (nn > 0) {
				t = &Pool[nn - 1];
			}
			else t = NULL;
		}
	}
}
template <class Elm, class Key, int TableSize, int PoolSectionSize>
inline void simple_hash<Elm, Key, TableSize, PoolSectionSize>::start_scan(hash_context& ct) {
	_testsize();
	ct.ScanAll = true;
	ct.TblPos = 0;
	while (ct.TblPos < Pool.Count() && Pool[ct.TblPos].next == -1)ct.TblPos++;
	ct.TblPos;
}
template <class Elm, class Key, int TableSize, int PoolSectionSize>
inline Elm* simple_hash<Elm, Key, TableSize, PoolSectionSize>::next(hash_context& ct) {
	if (ct.ScanAll) {
		while (ct.TblPos < Pool.Count() && Pool[ct.TblPos].next == -1)ct.TblPos++;
		if (ct.TblPos < Pool.Count()) {
			__temp& pp = Pool[ct.TblPos];
			ct.pptr = &pp;
			ct.TblPos++;
			return &pp.E;
		}
	}
	else {

		__temp* t = (__temp*)ct.ptr;
		__temp* t0 = t;
		if (t0) {
			while (t) {
				__temp* pt = t;
				int nn = t->next;
				if (nn > 0) {
					t = &Pool[nn - 1];
				}
				else {
					t = NULL;
					ct.ptr = NULL;
				}
				if (t && t->K == t0->K) {
					ct.ptr = t;
					break;
				}
			}
			ct.pptr = &t0;
			return &t0->E;
		}
	}
	return NULL;
}
template <class Elm, class Key, int TableSize, int PoolSectionSize>
inline Key* simple_hash<Elm, Key, TableSize, PoolSectionSize>::_key(hash_context* co) const {
	return &((__temp*)(co->pptr))->K;
}

template <class Elm, class Key, int TableSize, int PoolSectionSize>
inline bool simple_hash<Elm, Key, TableSize, PoolSectionSize>::test_integrity() {
	int sz = size();
	int szz = 0;
	for (int i = 0; i < Pool.Count(); i++) {
		if (Pool[i].next != -1)szz++;
	}
	assert(szz == sz);
	if (szz != sz) {
		return false;
	}
	scan((*this), Elm * pe, Key * pk) {
		sz--;
	}scan_end;
	if (sz) {
		assert(0);
		return false;
	}
	for (int i = 0; i < Pool.Count(); i++) {
		if (Pool[i].next == i + 1) {
			assert(0);
			return false;
		}
	}
	for (int i = 0; i < DynSize; i++) {
		if (Table[i]) {
			__temp* t = &Pool[Table[i] - 1];
			while (t->next) {
				if (t->next < 0) {
					assert(0);
					return false;
				}
				t = &Pool[t->next - 1];
			}
		}
	}
	return true;
}
