/*
* �߽��ʶ�� P200
* �㷨8.1(�״���Ϸ�)
* 2012-09-20
*/
#include<stdio.h>
#include<stdlib.h>

// �߽��ʶ�������ÿռ��Ľ��ṹ
// head��foot�ֱ��ǿ����ÿռ���н��ĵ�һ���ֺ����һ����(Word)
// ������
typedef struct Word{
	union{
		struct Word *llink;//ͷ����ָ��ǰ�����
		struct Word *uplink;//�ײ���ָ�򱾽��ͷ��
	}a;
	int tag;//���־��0�����У�1��ռ�ã�ͷ����β������
	int size;//ͷ���򣬿��С
	struct Word *rlink;//ͷ����ָ���̽��
}Word,head,foot,*Space;//*space:�����ÿռ�ָ������

// �������ĺ궨�壬ָ��p��ָ���ĵײ�(���һ����)
#define FootLoc(p) (p)+(p)->size-1

#define MAX 1000//�����ÿռ�Ĵ�С(��Word���ֽ���Ϊ��λ)
#define E 10//�����С�ߴ�-1(��Word�ֽ���Ϊ��λ)

/*
�㷨8.1(�״���Ϸ�) P200
pavָ������ÿռ��ͷ�������в�С��n�Ŀ��п飬�������Ӧ�Ĵ洢�飬
���������׵�ַ�����򷵻�NULL�������������ÿռ���գ���pavָ��
���иշ�����Ľ��ĺ�̽��(��һ�����ý��)
*/
Space AllocBoundTag(Space *pav,int n){
	Space p,f;
	int times = 0;
	//���Ҳ�С��n�Ŀ��п飬p->rlink == *p˵������ͷָ����.
	for(p=*pav;p&&p->size<n&&p->rlink!=*pav;p=p->rlink){
		times++;
	}
	printf("times=%d\n",times);
	//�Ҳ��������ؿ�ָ��
	if(!p||p->size<n){
		printf("Allocate failed!\n");
		return NULL;
	}else{//pָ���ҵ��Ŀ��п飬�����и�
		//ָ��ײ�tail
		f = FootLoc(p);
		//pavָ��*p���ĺ�̽�㣬p��Ҫ�������ȥ��
		*pav = p->rlink;
		if(p->size-n<=E){//������䣬������<=e��ʣ����
			//�����ÿռ���Ϊ�ձ�
			if(*pav==p){
				*pav = NULL;
			}else{//�ڱ���ɾ������Ľ��
				//pavָ��p��ǰ��һ�����
				(*pav)->a.llink = p->a.llink;
				//p��ǰ��һ�����ָ��p�ĺ����Ǹ���㣬��ʵ���������ǽ�p�ӱ���ɾ��
				p->a.llink->rlink = *pav;
			}
			//�޸ķ������ͷ���͵ײ���־
			p->tag = f->tag = 1;
		}else{//����ÿ�ĺ�n����(�ߵ�ַ����)
			//�޸ķ����ĵײ���־
			f->tag = 1;
			//����ʣ����С������������p��β�������仯����Ϊ�����Ƿ���ÿ�ĺ�
			//n����(�ߵ�ַ����)������������
			p->size -= n;
			//fָ��������ʣ���ĵײ�
			f = FootLoc(p);
			//����ʣ���ײ���־Ϊ����
			f->tag = 0;
			//β��ָ��ͷ��
			f->a.uplink = p;
			//ָ���·�����ͷ��
			p = f+1;
			//�����·�����ͷ��
			p->tag = 1;
			p->size = n;
		}
		//���ط�����׵�ַ
		return p;
	}
}

/*
�߽��ʶ���Ļ����㷨
pavΪ�����ÿռ�ͷָ�룬pΪ�ͷſ�ͷ�׵�ַ
*/
void Reclaim(Space *pav,Space *p){
	//(*p-1)Ϊ���ڿ�ĵײ�������(*p-1)>a.uplinkָ���ͷſ�����ڿ�
	//(����ʱ)��ͷ����ַҲ���Ǹÿ���׵�ַ
	Space s = (*p-1)->a.uplink;
	//tָ���ͷſ�����ڿ�(���п�)���׵�ַ
	Space t = *p + (*p)->size;
	//lָʾ�ͷſ�����ڿ��Ƿ����
	int left = (*p-1)->tag;
	//rָʾ�ͷſ�����ڿ��Ƿ����
	int right = (*p+(*p)->size)->tag;
	printf("left=%d,right=%d\n",left,right);
	
	//�����ÿռ��Ϊ��
	if(!*pav){
		//���ͷſ���뵽pav��ָ�Ŀ����ÿռ����
		//ͷ���������ָ�뼰pav��ָ���ͷſ�
		*pav = (*p)->a.llink = (*p)->rlink = *p;
		//�޸�ͷ������־Ϊ����
		(*p)->tag = 0;
		//�޸�β����
		(FootLoc(*p))->a.uplink = *p;
		//�޸�β������־Ϊ����
		(FootLoc(*p))->tag = 0;
	}else{//�����ÿռ����
		if(left==1&&right==1){//����������Ϊռ�ÿ�
			(*p)->tag = 0;//�޸�ͷ������־Ϊ����
			(FootLoc(*p))->a.uplink = *p;//�޸�β����
			(FootLoc(*p))->tag = 0;
			//��p��ָ���(���ͷŵĽ��)����pav��ָ���֮ǰ
			(*pav)->a.llink->rlink = *p;
			(*p)->a.llink = (*pav)->a.llink;
			(*p)->rlink = *pav;
			(*pav)->a.llink = *p;
			//�޸�pav������ͷŵĽ��Ϊ�´η���ʱ�����Ȳ�ѯ�Ľ��
			*pav = *p;
		}else if(left==0&&right==1){//���ڿ�Ϊ���п飬������Ϊռ�ÿ�
			//�ϲ����ڿ���ͷſ�
			//���ڿ��п��ͷ����ַ,(*p-1)Ϊ���ڿ��β��
			s = (*p-1)->a.uplink;
			s->size+=(*p)->size;//�����µĿ��п��С
			t = FootLoc(*p);//�����µĿ��п�ײ�
			t->a.uplink = s;
			t->tag = 0;
		}else if(left==1&&right==0){//������Ϊ���п飬������Ϊռ�ÿ�
			//�ϲ����ڿ���ͷſ�
			(*p)->tag = 0;//pΪ�ϲ���Ľ��ͷ����ַ
			(*p)->a.llink = t->a.llink;//p��ǰ��Ϊԭt��ǰ��
			(*p)->a.llink->rlink = *p;//p��ǰ���ĺ��Ϊp
			(*p)->rlink = t->rlink;//p�ĺ��Ϊԭt�ĺ��
			(*p)->rlink->a.llink = *p;//p�ĺ�̵�ǰ��Ϊp
			(*p)->size+=t->size;//�µĿ��п�Ĵ�С
			//�½��ײ�(ԭt�ĵײ�)ָ��ָ���½���ͷ��
			(FootLoc(t))->a.uplink = *p;
			//�����ÿռ���ͷָ��ָ��t(t�Ѳ��ǿ��н���׵�ַ��)
			if(*pav==t){
				//�޸�pav������ͷŵĽ��Ϊ�´η���ʱ�����Ȳ�ѯ�Ľ��
				*pav = *p;
			}
		}else{//����������Ϊ���п�
			s->size += (*p)->size + t->size;//�����½��Ĵ�С
			t->a.llink->rlink = t->rlink;//ɾȥ���ڿ��п���
			t->rlink->a.llink = t->a.llink;
			//�½��ײ�(ԭt�ĵײ�)ָ��ָ����ͷ��
			(FootLoc(t))->a.uplink = s;
			if(*pav==t){//�����ÿռ���ͷָ��ָ��t(t�Ѳ��ǿ��н���׵�ַ��)
				*pav = s;//�޸�pav������ͷŵĽ��Ϊ�´η���ʱ�����Ȳ�ѯ�Ľ��
			}
		}
	}
	*p = NULL;//����ͷŵĽ���ָ��Ϊ��
}

// ���p��ָ�Ŀ����ÿռ��
void Print(Space p){
	Space h,f;
	printf("Available space table:\n");
	if(p){//�����ÿռ����
		h = p;//hָ���һ������ͷ����(�׵�ַ)
		f = FootLoc(h);//fָ���һ�����ĵײ���
		do{
			//��������Ϣ
			printf("Block size = %d,Block header address=%u,Block first address=%u;",h->size,h,f->a.uplink);
			//f(h�����һ���ּ��ײ�)����һ���ֽڼ�f+1�����ڿ���׵�ַ
			printf("Block tag=%d(0:extra 1:own),next block header address=%u\n",h->tag,f+1);
			//ָ����һ������ͷ����(�׵�ַ)��֪���Ȳ�����f+1,����ʹ��printf��ӡ��ַ
			//printf("Next block header address=%u\n",h);//���������ȷ������h=f+1
			h = h->rlink;
			f = FootLoc(h);//fָ����һ�����ĵײ���
		}while(h!=p);//û��ѭ������ı�β
	}else{
		printf("There is no extra space.\n");
	}
	printf("\n");
}

// ���p������ָ���ѷ���ռ�
void PrintUser(Space p[]){
	int i;
	printf("Allocated space table:\n");
	for(i=0;i<MAX/E;i++){
		if(p[i]){//ָ�벻Ϊ0(ָ��һ��ռ�ÿ�)
			printf("Block %d header address=%u;",i,p[i]);//��������Ϣ
			printf("Block size=%d Block header tag=%d(0:extra 1:own);",p[i]->size,p[i]->tag);
			printf("Block footer tag=%d\n",(FootLoc(p[i]))->tag);
		}
	}
	printf("\n");
}

main(){
	Space pav,//���п�ָ��
		p;//�н��õ�ָ��
	Space v[MAX/E] = {NULL};//ռ�ÿ�ָ������(��ʼ��Ϊ��),MAX=100,E=10
	int n;
	//���β��Ե��ڴ��Ĵ�С�Խṹ��word���ֽ���Ϊ��λ���Ƶġ�
	printf("struct Word occupy %d Bytes\n\n",sizeof(Word));
	//�����СΪMAX*sizeof(Word)���ֽڵĿռ䣬��ס�������2���ֱ���ͷβ���
	p = (Word*)malloc((MAX+2)*sizeof(Word));
	
	//���õ�ַ�߽磬�Է����������ڿ�ʱ������ʱ��p��������Ŀ�ʼ
	p->tag = 1;//1��ʾռ��
	//��ʼ�������õĿռ��
	pav = p+1;//�����ÿռ��ı�ͷ,pav��p��һ��Word������
	//��ʼ�������ÿռ�(һ������)��˫��ѭ������
	pav->rlink = pav->a.llink = pav;
	pav->tag = 0;//��־Ϊ0������
	pav->size = MAX;
	p = FootLoc(pav);//pָ��ײ���
	p->a.uplink = pav;//�ײ���pָ�򱾽��ͷ��pav
	p->tag = 0;//��־Ϊ0������
	
	//��ʼ������ռ��������п���Ϣ
	printf("After initialized:\n");
	Print(pav);
	
	//��һ�η���
	printf("--------------------allocate--------------------------\n");
	n = 300;
	printf("After allocate %u bytes:\n",n);
	v[0] = AllocBoundTag(&pav,n);//��һ��ռ�ÿ�ָ��v[0]
	Print(pav);
	PrintUser(v);//����ѱ����õĿռ��б�
	
	//�ڶ��η���
	printf("----------------------------------------------\n");
	n = 450;
	printf("After allocate %u bytes:\n",n);
	v[1] = AllocBoundTag(&pav,n);//�ڶ���ռ�ÿ�ָ��v[1]
	Print(pav);
	PrintUser(v);
	
	//���䲻�ɹ���
	printf("----------------------------------------------\n");
	n = 300;
	printf("After allocate %u bytes:\n",n);
	v[2] = AllocBoundTag(&pav,n);
	Print(pav);
	PrintUser(v);
	
	//����������(250)
	printf("----------------------------------------------\n");
	n = 242;
	printf("After allocate %u bytes,pav:\n",n);
	v[2] = AllocBoundTag(&pav,n);
	Print(pav);
	PrintUser(v);
	printf("-----------------------------------------------------\n");
	
	//���տ�v[0]
	printf("--------------------reclaim--------------------------\n");
	printf("After retrieve v[0](%d)(when pav is empty),pav:\n",v[0]->size);
	Reclaim(&pav,&v[0]);//pavΪ��
	Print(pav);
	PrintUser(v);
	
	//���տ�v[2]
	printf("----------------------------------------------\n");
	printf("After retrieve v[2](%d)(left block and right block are owned),pav:\n",v[2]->size);
	Reclaim(&pav,&v[2]);//����������Ϊռ�ÿ�
	Print(pav);
	PrintUser(v);
	printf("----------------------------------------------\n");
	
	//���պ��ٴη���
	printf("--------------------allocate--------------------------\n");
	n = 270;
	printf("After allocate %u bytes(find big enough block),pav:\n",n);
	v[0] = AllocBoundTag(&pav,n);
	Print(pav);
	PrintUser(v);
	
	//�ڵ�ǰ���Ϸ���
	printf("----------------------------------------------\n");
	n = 30;
	printf("After allocate %u bytes(in the current block),pav:\n",n);
	v[2] = AllocBoundTag(&pav,n);
	Print(pav);
	PrintUser(v);
	printf("----------------------------------------------\n");
	
	//���տ�
	printf("--------------------reclaim--------------------------\n");
	printf("After retrieve v[1](%d)(right block is free and left block is owned),pav:\n",v[1]->size);
	Reclaim(&pav,&v[1]);//������Ϊռ�ÿ飬������Ϊ���п�
	Print(pav);
	PrintUser(v);
	printf("----------------------------------------------\n");
	
	//���տ�
	printf("After retrieve v[0](%d)(left block is free and right block is owned),pav:\n",v[0]->size);
	Reclaim(&pav,&v[0]);//������Ϊ���п飬������Ϊռ�ÿ�
	Print(pav);
	PrintUser(v);
	printf("----------------------------------------------\n");
	
	//���տ�
	printf("After retrieve v[2](%d)(left block and right block are free),pav:\n",v[2]->size);
	Reclaim(&pav,&v[2]);//����������Ϊ���п�
	Print(pav);
	PrintUser(v);
	
	return 0;
}