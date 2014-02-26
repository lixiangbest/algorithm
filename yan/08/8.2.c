/*
* ���ϵͳ P205
* �㷨8.2
* 2012-09-22
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//�����ÿռ�������1024�ֵ�2���ݴΣ��ӱ�ĸ���Ϊm+1
#define m 10
//���ϵͳ�����ÿռ��Ľṹ
typedef struct Word{
	struct Word *llink;//ָ��ǰ�����
	int tag;//���־,0:����;1:ռ��
	int kval;//���С��ֵΪ2���ݴ�k
	struct Word *rlink;//ͷ����ָ���̽��
}Word,head,*Space;//Word:�ڴ������ͣ����ĵ�һ����Ҳ��Ϊhead

typedef struct HeadNode{
	int nodesize;//������Ŀ��п�Ĵ�С
	struct Word *first;//������ı�ͷָ��
}FreeList[m+1];//��ͷ��������

#define N 100 //ռ�ÿ���������ֵ
Space r;//rΪ�������ɿռ���׵�ַ��ȫ����

/*
�㷨8.2 P205
avail[0..m]Ϊ�����ÿռ��nΪ��������������в�С��n�Ŀ��п飬�������Ӧ�Ĵ洢�飬
���������׵�ַ�����򷵻�NULL��
*/
Space allocBuddy(FreeList *avail,int n){
	int i,k;
	Space pa,pi,pre,suc;
	//�����������Ҫ����ӱ����п��С����n�ı�
	for(k=0;k<=m&&((*avail)[k].nodesize<n+1||!(*avail)[k].first);k++);
	printf("k=%d\n",k);
	if(k>m){
		printf("Allocate failed!\n");
		return NULL;
	}else{//���з���
		pa = (*avail)[k].first;//ָ��ɷ����ӱ�ĵ�һ�����
		pre = pa->llink;//ָ��ǰ��
		suc = pa->rlink;//ָ����
		if(pa==suc){//��ͬ��
			(*avail)[k].first = NULL;//�������ӱ��ɿձ�
		}else{//���ӱ�ɾȥ*pa���(�����)
			pre->rlink = suc;
			suc->llink = pre;
			(*avail)[k].first = suc;
		}
		//����(*avail)[k]��ʣ���ֳɰ��ɴ�С��(2��k-i����)��˳��
		//���β�����Ӧ��С���ӱ���
		for(i=1;(*avail)[k-i].nodesize>=n+1;i++){
			pi = pa+(int)pow(2,k-i);//����2��k-i����
			pi->rlink = pi;
			pi->llink = pi;
			pi->tag = 0;
			pi->kval = k-i;
			(*avail)[k-i].first = pi;
		}
		//�������ȥ��pa��
		pa->tag = 1;
		pa->kval = k-(--i);
	}
	return pa;
}

//���������ʼ��ַΪp�����СΪpow(2,k)�Ŀ�Ļ���ַ
Space buddy(Space p){
	int po = pow(2,p->kval+1);
	if((p-r)%po==0){//pΪǰ��
		return p+(int)pow(2,p->kval);
	}else{//pΪ���
		return p-(int)pow(2,p->kval);
	}
}

//���ϵͳ�Ļ����㷨 ��p��ָ���ͷſ���յ������ÿռ��pav��
void reclaim(FreeList *pav,Space *p){
	Space s;
	//�������ʼ��ַ
	s = buddy(*p);
	printf("Retrieve process:raw header address:%u,space address:%u,partner header address:%u,plus1:%d,plus2:%d\n",r,*p,s,*p-r,s-r);
	//�鲢����,s>=r&&s<r+(*pav)[m].nodesize˵��������ʼ��ַ
	//����Ч��Χ���һ������
	while(s>=r&&s<r+(*pav)[m].nodesize&&s->tag==0){
		//��������ɾ�����
		if(s->llink==s&&s->rlink==s){//�����Ͻ���һ�����
			(*pav)[s->kval].first = NULL;//�ô�����Ϊ��
		}else{//�����ϲ�ֹһ����㣬�򽫸ý��sɾ��
			//printf("\n%d\n",s->kval);
			s->llink->rlink = s->rlink;//ǰ���ĺ��Ϊ�ý��ĺ��
			s->rlink->llink = s->llink;//��̵�ǰ��Ϊ�ý���ǰ��
			if((*pav)[s->kval].first==s){//s������ĵ�һ�����
				(*pav)[s->kval].first = s->rlink;//��ͷָ����һ�����
			}
		}
		//�޸Ľ��ͷ��
		if((*p-r)%(int)pow(2,(*p)->kval+1)==0){//pΪǰ��
			(*p)->kval++;
			//printf("%d\n",(*p)->kval);
		}else{//pΪ���
			s->kval = (*p)->kval+1;
			*p = s;//pָ���¿��׵�ַ
		}
		s = buddy(*p);//��һ���������ʼ��ַ
		printf("Retrieve process:raw header address:%u,space address:%u,partner header address:%u,plus1:%d,plus2:%d\n",r,*p,s,*p-r,s-r);
		//printf("Next buddy header address:\n",s);
	}
	//��p��������ÿռ����
	(*p)->tag = 0;
	if((*pav)[(*p)->kval].first == NULL){//�������
		(*pav)[(*p)->kval].first = (*p)->llink = (*p)->rlink = *p;
	}else{//�����տ���ڱ�ͷ
		(*p)->rlink = (*pav)[(*p)->kval].first;
		(*p)->llink = (*p)->rlink->llink;
		(*p)->rlink->llink = *p;
		(*p)->llink->rlink = *p;
		(*pav)[(*p)->kval].first = *p;
	}
	*p = NULL;
}

// ���p��ָ�Ŀ����ÿռ��
void print(FreeList p){
	int i;
	Space h;
	printf("Available space table:\n");
	for(i=0;i<=m;i++){
		if(p[i].first){//��i�������ÿռ����
			h = p[i].first;//hָ������ĵ�һ������ͷ����(�׵�ַ)
			do{
				//��������Ϣ
				printf("Block size = %d,Block first address=%u;",(int)pow(2,h->kval),h);
				printf("Block tag=%d(0:extra 1:own),next block header address=%u;\n",h->tag);
				h = h->rlink;//ָ����һ������ͷ����(�׵�ַ)
			}while(h!=p[i].first);//û��ѭ������ı�β
		}
	}
	printf("\n");
}

// ���p������ָ���ѷ���ռ�
void printUser(Space p[]){
	int i;
	printf("Allocated space table:\n");
	for(i=0;i<N;i++){
		if(p[i]){//ָ�벻Ϊ0(ָ��һ��ռ�ÿ�)
			printf("Block %d header address=%u;",i,p[i]);//��������Ϣ
			printf("Block size=%d;",(int)pow(2,p[i]->kval));
			printf("Block tag=%d(0:extra 1:own)\n",(p[i])->tag);
		}
	}
	printf("\n");
}

main(){
	int i,n;
	FreeList a;//����
	Space q[N] = {NULL};//q����Ϊռ�ÿ���׵�ַ,N=100,m=10
	
	//���β��Ե��ڴ��Ĵ�С�Խṹ��word���ֽ���Ϊ��λ���Ƶġ�
	printf("This assume the memory cell is the bytes of struct Word:\n");
	printf("struct Word occupy %u Bytes\n\n",sizeof(Word));
	printf("Available space for allocated(int)pow(2,%d) = %u Bytes\n\n",m,(int)pow(2,m));//���õĴ�СΪ2��m�η�
	printf("--------------------------------------------------------------\n");
	
	//��ʼ�������ÿռ�a
	for(i=0;i<=m;i++){
		a[i].nodesize = (int)pow(2,i);//������С
		a[i].first = NULL;//���ָ��
	}
	
	//���������������һ�����
	r = a[m].first = (Word*)malloc(a[m].nodesize*sizeof(Word));//���ɵ�2��m�η���Word�ִ�С����
	if(r){//���ɽ��ɹ�
		printf("Header address:%u\n",r);
		r->llink = r->rlink = r;//��ʼ���ý��
		r->tag = 0;
		r->kval = m;//���С��2��m�ݴ�
		print(a);
		printUser(q);
		printf("--------------------------------------------------------------\n");
		
		n = 100;
		printf("After allocate %d:\n",n);
		//��a����100��Word���ڴ�(ʵ�ʻ��128��Word��Ϊ100>64&&100<128�����Ը���������128��Word���ڴ�)
		q[0] = allocBuddy(&a,n);
		print(a);
		printUser(q);
		printf("--------------------------------------------------------------\n");
		
		n = 200;
		printf("After allocate %d:\n",n);
		//��a����200��Word���ڴ�(ʵ�ʻ��256��Word)
		q[1] = allocBuddy(&a,n);
		print(a);
		printUser(q);
		printf("--------------------------------------------------------------\n");
		
		n = 220;
		printf("After allocate %d:\n",n);
		//��a����220��Word���ڴ�(ʵ�ʻ��256��Word)
		q[2] = allocBuddy(&a,n);
		print(a);
		printUser(q);
		printf("--------------------------------------------------------------\n");
		
		printf("--------------------------Retrueve--------------------------------\n");
		printf("After retrieve q[1]:\n");
		reclaim(&a,&q[1]);//����q[1]����鲻����
		print(a);
		printUser(q);
		printf("--------------------------------------------------------------\n");
		
		printf("After retrieve q[0]:\n");
		reclaim(&a,&q[0]);//����q[0]��������
		print(a);
		printUser(q);
		printf("--------------------------------------------------------------\n");
		
		printf("After retrieve q[2]:\n");
		reclaim(&a,&q[2]);//����q[2]�������У�����һ������
		print(a);
		printUser(q);
	}else{
		printf("Allocate failed!\n");
	}
	return 0;
}


