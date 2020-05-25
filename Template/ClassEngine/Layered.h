#pragma once

template <int IndexType>
class BaseLayered {
public:

};
///class X should contain fields:
///data itself
///IndexType next; //- this is the reference to unit, not index
///LayerType Layer; //- this is optional, need only if Layer-based functions used
///
template <class X, typename IndexType, typename LayerType>
class Layered {
	const int PoolSize = 4096;
	const int PoolShift = 12;
	const IndexType LinkEnd = -1;
	IndexType MaxUsedIndex;
	
	clist<IndexType*> AllocatedIndices;
	IndexType NIndices;
	
	clist<IndexType> FreeUnits;
	clist<X*> AllocatedUnits;
	IndexType NUnits;
	
public:
	struct scan_context {
		X* prev;
		X* cur;
		X* first;
		IndexType Index;
		bool LastIteration;
	};
	scan_context context(IndexType idx) const ;
	
	Layered();
	Layered& operator = (const Layered<X, IndexType, LayerType> & src);
	
	IndexType AllocateUnit();
	void EnsureIndexExists(IndexType index);
	

	X* unit(IndexType uidx);
	IndexType* index_ptr(IndexType idx);

	int size(IndexType idx);
	int size(IndexType idx, LayerType Layer);

	X* get(IndexType idx);
	X* get(IndexType idx, int sub);
	X* get_layer(IndexType idx, LayerType Layer);
	X* get_layer(IndexType idx, int sub, LayerType Layer);
	X* last(IndexType idx);

	X* next(IndexType idx, X* ref);
	X* next(IndexType idx, X* ref, LayerType Layer);
	IndexType next(IndexType idx, IndexType ref);
	IndexType next(IndexType idx, IndexType ref, LayerType Layer);
	bool next(scan_context& co);
	bool next_edge(scan_context& co);

	void del(IndexType idx);
	void del(IndexType idx, int sub);
	void del_layer(IndexType idx, LayerType Layer);
	void del_layer(IndexType idx, int sub, LayerType Layer);
	
	void Clear();
	void Free();
	
	X* Add(IndexType idx, LayerType Layer);
	X* Add(IndexType idx);
	X* Insert(IndexType idx, int pos, LayerType Layer);
	X* Insert(IndexType idx, int pos);
};

template <class X, typename IndexType, typename LayerType>
typename Layered<X, IndexType, LayerType>::scan_context Layered<X, IndexType, LayerType>::context(IndexType idx) const {
	Layered<X, IndexType, LayerType>::scan_context co;
	co.first = co.prev = co.cur = nullptr;
	co.Index = idx;
	co.LastIteration = false;
	return co;
}

template <class X, typename IndexType, typename LayerType>
Layered<X, IndexType, LayerType>::Layered() {
	NUnits = 0;
	NIndices = 0;
	MaxUsedIndex = -1;
}

template <class X, typename IndexType, typename LayerType>
Layered<X, IndexType, LayerType>& Layered<X, IndexType, LayerType>::operator=(
	const Layered<X, IndexType, LayerType>& src) {
	for(size_t i=0;i<src.AllocatedIndices.Count();i++) {
		IndexType* data = new IndexType[PoolSize];
		memcpy(data, src.AllocatedIndices[i], PoolSize * sizeof(IndexType));
		AllocatedIndices.Add(data);
	}
	NIndices = src.NIndices;

	for (size_t i = 0; i < src.AllocatedUnits.Count(); i++) {
		X* data = new X[PoolSize];
		memcpy(data, src.AllocatedUnits[i], PoolSize * sizeof(X));
		AllocatedUnits.Add(data);
	}
	FreeUnits = src.FreeUnits;
	NUnits = src.NUnits;
	return *this;
}

template <class X, typename IndexType, typename LayerType>
IndexType Layered<X, IndexType, LayerType>::AllocateUnit() {
	if (FreeUnits.Count() == 0) {
		X* pX = new X[PoolSize];
		IndexType i0 = IndexType(AllocatedUnits.Count() + 1) * PoolSize;
		for (int i = 0; i < PoolSize; i++) {
			FreeUnits.Add(--i0);
		}
		AllocatedUnits.Add(pX);
		NUnits += PoolSize;
	}
	IndexType r = FreeUnits.GetLast();
	FreeUnits.RemoveLast();
	return r;
}

template <class X, typename IndexType, typename LayerType>
void Layered<X, IndexType, LayerType>::EnsureIndexExists(IndexType index) {
	if (index >= NIndices) {
		int nu = 1 + ((index + 1) >> PoolShift);
		for(int k=AllocatedIndices.Count();k<nu;k++) {
			IndexType* data = new IndexType[PoolSize];
			AllocatedIndices.Add(data);
			for (int p = 0; p < PoolSize; p++)*(data++) = LinkEnd;
			NIndices += PoolSize;
		}
	}
	MaxUsedIndex = std::max(MaxUsedIndex, index);
}

template <class X, typename IndexType, typename LayerType>
X* Layered<X, IndexType, LayerType>::unit(IndexType uidx) {
	IndexType idx = uidx >> PoolShift;
	return AllocatedUnits[idx] + (uidx & (PoolSize -1));
}

template <class X, typename IndexType, typename LayerType>
IndexType* Layered<X, IndexType, LayerType>::index_ptr(IndexType idx) {
	EnsureIndexExists(idx);
	IndexType pidx = idx >> PoolShift;
	return AllocatedIndices[pidx] + (idx & (PoolSize - 1));
}

template <class X, typename IndexType, typename LayerType>
int Layered<X, IndexType, LayerType>::size(IndexType idx) {
	X* el = nullptr;
	int n = 0;
	while(el = next(idx, el)){
		n++;
	}
	return n;
}

template <class X, typename IndexType, typename LayerType>
int Layered<X, IndexType, LayerType>::size(IndexType idx, LayerType Layer) {
	X* el = nullptr;
	int n = 0;
	while (el = next(idx, el, Layer)) {
		n++;
	}
	return n;
}

template <class X, typename IndexType, typename LayerType>
X* Layered<X, IndexType, LayerType>::get(IndexType idx) {
	EnsureIndexExists(idx);
	IndexType pidx = idx >> PoolShift;
	IndexType p = AllocatedIndices[pidx][idx & (PoolSize - 1)];
	if (p != LinkEnd)return unit(p);
	return nullptr;
}

template <class X, typename IndexType, typename LayerType>
X* Layered<X, IndexType, LayerType>::get(IndexType idx, int sub) {
	EnsureIndexExists(idx);
	X* el = nullptr;
	int n = 0;
	while (el = next(idx, el)) {
		if (n++ == sub)return el;
	}
	return nullptr;
}

template <class X, typename IndexType, typename LayerType>
X* Layered<X, IndexType, LayerType>::get_layer(IndexType idx, LayerType Layer) {
	return next(idx, nullptr, Layer);
}

template <class X, typename IndexType, typename LayerType>
X* Layered<X, IndexType, LayerType>::get_layer(IndexType idx, int sub, LayerType Layer) {
	X* el = nullptr;
	int n = 0;
	while (el = next(idx, el, Layer)) {
		if (n++ == sub)return el;
	}
	return nullptr;
}

template <class X, typename IndexType, typename LayerType>
X* Layered<X, IndexType, LayerType>::last(IndexType idx) {
	X* el = nullptr;
	while (el = next(idx, el)) {
		if (el->next == LinkEnd)return el;
	}
	return nullptr;
}

template <class X, typename IndexType, typename LayerType>
X* Layered<X, IndexType, LayerType>::next(IndexType idx, X* ref) {
	if (!ref)return get(idx);
	if (ref->next == LinkEnd)return nullptr;
	return unit(ref->next);
}

template <class X, typename IndexType, typename LayerType>
X* Layered<X, IndexType, LayerType>::next(IndexType idx, X* ref, LayerType Layer) {
	do {
		ref = next(idx, ref);
		if ( ref && ref->Layer == Layer)return ref;
	} while (ref);
	return nullptr;
}

template <class X, typename IndexType, typename LayerType>
IndexType Layered<X, IndexType, LayerType>::next(IndexType idx, IndexType ref) {
	X* r = nullptr;
	if (ref == LinkEnd) {
		IndexType* it = index_ptr(idx);
		if (it)return *it;
	}
	else {
		r = unit(ref);
		if (r)return r->next;
	}
	return LinkEnd;
}

template <class X, typename IndexType, typename LayerType>
IndexType Layered<X, IndexType, LayerType>::next(IndexType idx, IndexType ref, LayerType Layer) {
	do {
		ref = next(idx, ref);
		if (ref != LinkEnd) {
			X* p = unit(ref);
			if (p && p->Layer == Layer)return ref;
		}
	} while (ref != LinkEnd);
	return LinkEnd;
}

template <class X, typename IndexType, typename LayerType>
bool Layered<X, IndexType, LayerType>::next(scan_context& co) {
	co.prev = co.cur;
	co.cur = next(co.Index, co.cur);
	if (!co.first)co.first = co.cur;
	return co.cur != nullptr;
}

template <class X, typename IndexType, typename LayerType>
bool Layered<X, IndexType, LayerType>::next_edge(scan_context& co) {
	if (co.LastIteration)return false;
	co.prev = co.cur;
	co.cur = next(co.Index, co.cur);
	if (!co.first)co.first = co.cur;
	if(co.cur==nullptr) {
		co.cur = co.first;
		co.LastIteration = true;
	}
	if(co.cur && !co.prev) {
		
	}
	return co.cur != nullptr;
}

template <class X, typename IndexType, typename LayerType>
void Layered<X, IndexType, LayerType>::del(IndexType idx) {
	IndexType t = LinkEnd;
	while ((t = next(idx, t)) != LinkEnd) {
		FreeUnits.Add(t);
	}
	IndexType* it = index_ptr(idx);
	if (it)*it = LinkEnd;
}

template <class X, typename IndexType, typename LayerType>
void Layered<X, IndexType, LayerType>::del(IndexType idx, int sub) {
	IndexType t = LinkEnd;
	X* ref = nullptr;
	IndexType* ptr = index_ptr(idx);
	IndexType* ptr0 = ptr;
	int pos = 0;
	if (ptr) {
		t = *ptr;
		if (t != LinkEnd) {
			do {
				X* cref = unit(t);
				if (cref) {
					if (pos == sub) {//condition to delete
						*ptr = cref->next;
						FreeUnits.Add(t);
						break;
					}
					pos++;
				}
				ptr = &cref->next;
				t = *ptr;
			} while (t != LinkEnd);
		}
	}
}

template <class X, typename IndexType, typename LayerType>
void Layered<X, IndexType, LayerType>::del_layer(IndexType idx, LayerType Layer) {
	IndexType t = LinkEnd;
	X* ref = nullptr;
	IndexType* ptr = index_ptr(idx);
	if(ptr){
		t = *ptr;
		if (t != LinkEnd) {
			do {
				X* cref = unit(t);
				if (cref && cref->Layer == Layer) {//condition to delete
					*ptr = cref->next;					
					FreeUnits.Add(t);
					t = *ptr;
				}
				else {
					ptr = &cref->next;
					t = *ptr;
				}
			} while (t != LinkEnd);
		}
	}
}

template <class X, typename IndexType, typename LayerType>
void Layered<X, IndexType, LayerType>::del_layer(IndexType idx, int sub, LayerType Layer) {
	IndexType t = LinkEnd;
	X* ref = nullptr;
	IndexType* ptr = index_ptr(idx);
	IndexType* ptr0 = ptr;
	int pos = 0;
	if (ptr) {
		t = *ptr;
		if (t != LinkEnd) {
			do {
				X* cref = unit(t);
				if (cref && cref->Layer == Layer) {
					if (pos == sub) {//condition to delete
						*ptr = cref->next;
						FreeUnits.Add(t);
						break;
					}
					pos++;
				}
				ptr = &cref->next;
				t = *ptr;
			} while (t != LinkEnd);
		}
	}
}

template <class X, typename IndexType, typename LayerType>
void Layered<X, IndexType, LayerType>::Clear() {
	Free();
}

template <class X, typename IndexType, typename LayerType>
void Layered<X, IndexType, LayerType>::Free() {
	for(size_t i=0;i<AllocatedUnits.Count();i++) {
		delete[](AllocatedUnits[i]);
	}
	AllocatedUnits.Free();
	for (size_t i = 0; i < AllocatedIndices.Count(); i++) {
		delete[](AllocatedIndices[i]);
	}
	AllocatedIndices.Free();
	FreeUnits.Free();
	NUnits = NIndices = 0;
}

template <class X, typename IndexType, typename LayerType>
X* Layered<X, IndexType, LayerType>::Add(IndexType idx, LayerType Layer) {
	X* r = Add(idx);
	if (r)r->Layer = Layer;
	return r;
}

template <class X, typename IndexType, typename LayerType>
X* Layered<X, IndexType, LayerType>::Add(IndexType idx) {
	EnsureIndexExists(idx);
	IndexType u = AllocateUnit();
	X* el = unit(u);
	el->next = LinkEnd;
	
	X* end = last(idx);
	if(end) {
		end->next = u;
	}else {
		IndexType* px = index_ptr(idx);
		if(px) {
			*px = u;
		}
	}
	return el;
}

template <class X, typename IndexType, typename LayerType>
X* Layered<X, IndexType, LayerType>::Insert(IndexType idx, int pos, LayerType Layer) {
	if (pos == 0) {
		//add to the beginning
		IndexType* px = index_ptr(idx);
		if (px) {
			IndexType u = AllocateUnit();
			X* el = unit(u);
			el->next = *px;
			*px = u;
			return el;
		}
	}
	else {
		X* r = get_layer(idx, pos - 1, Layer);
		if (r) {
			//insert
			IndexType u = AllocateUnit();
			X* el = unit(u);
			el->next = r->next;
			el->Layer = Layer;
			r->next = u;
			return el;
		}
	}
	return Add(idx, Layer);
}

template <class X, typename IndexType, typename LayerType>
X* Layered<X, IndexType, LayerType>::Insert(IndexType idx, int pos) {
	if (pos == 0) {
		//add to the beginning
		IndexType* px = index_ptr(idx);
		if (px) {
			IndexType u = AllocateUnit();
			X* el = unit(u);
			el->next = *px;
			*px = u;
			return el;
		}
	}
	else {
		X* r = get(idx, pos - 1);
		if (r) {
			//insert
			IndexType u = AllocateUnit();
			X* el = unit(u);
			el->next = r->next;
			r->next = u;
		}
	}
	return Add(idx);
}
