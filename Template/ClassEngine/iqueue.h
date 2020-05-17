#pragma once

struct iQElement{
	iQElement(){
		iqIndex=-1;
		prev=next=NULL;
	}
	int iqIndex;
	iQElement* prev;
	iQElement* next;
};
#define iq_max_pos 3000
#define iq_max_neg 45000
#define iq_summ (iq_max_pos+iq_max_neg)
class iQueue{
public:
	iQueue(){
		memset(queue,0,sizeof(queue));
		maxpos=0;
	}
	int maxpos;
	iQElement* queue[iq_summ];
	int getHash(float x){
		if(x<=0)return iq_summ-1;
		int v=iq_max_pos-int(log(x)*600);
		if(v<0)return 0;
		if(v>=iq_summ)return iq_summ-1;
		return v;
	}
	void add(iQElement* e,float w){
		remove(e);
		int p=getHash(w);
		iQElement* e0=queue[p];
		if(e0)e0->prev=e;
		e->prev=NULL;
		e->next=e0;
		e->iqIndex=p;
		queue[p]=e;
		maxpos=std::max(p,maxpos);
	}
	void remove(iQElement* e){
		if(e->iqIndex!=-1){
			if(e->prev)e->prev->next=e->next;
			else queue[e->iqIndex]=e->next;
			if(e->next)e->next->prev=e->prev;
			e->prev=e->next=NULL;
			e->iqIndex=-1;
		}
	}
	iQElement* get_cheapest(bool remove){
		while(maxpos>0 && queue[maxpos]==NULL)maxpos--;
		iQElement* e=queue[maxpos];
		if(e){
			if(remove){
				queue[maxpos]=e->next;
				if(e->next)e->next->prev=NULL;
				e->next=e->prev=NULL;
				e->iqIndex=-1;
			}
			return e;
		}
		return NULL;
	}
};