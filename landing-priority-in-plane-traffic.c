#include <stdio.h>
#include <stdlib.h>

//d???m
typedef struct node {
	int ucak_id;
	int oncelik_id;
	int oncelik_id2;
	int talep_edilen_inis_saati;
	int inis_saati;
	struct node* next;

}Node;
//inis yapan ucaklar i?in kalk?? kuyrugu pointerlar? tan?mland?.
Node *kalkisroot=NULL,*kalkisend=NULL;
//ini? yapmam?? ucaklar i?in yeni d???m olustulur.
Node* newNode(int yeni_ucak_id, int talep_edilen_inis_saati, int yeni_oncelik_id)
{
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->ucak_id = yeni_ucak_id;
	temp->oncelik_id = yeni_oncelik_id;
	temp->oncelik_id2 = yeni_oncelik_id;
	temp->talep_edilen_inis_saati = talep_edilen_inis_saati;
	temp->inis_saati = talep_edilen_inis_saati;
	temp->next = NULL;
	return temp;//olusturulan d???m adresi d?nd?r?l?r
}
// talep_edilen_inis_saati bilgisine g?re s?ral? kuyruk olusturulur.
void push(Node** head, int yeni_ucak_id, int talep_edilen_inis_saati,int yeni_oncelik_id)
{
	Node* baslangic = (*head);

	Node* temp = newNode(yeni_ucak_id, talep_edilen_inis_saati,yeni_oncelik_id);

	if ((*head)->talep_edilen_inis_saati > talep_edilen_inis_saati) {
		temp->next = *head;
		(*head) = temp;
	}
	else {
		while (baslangic->next != NULL &&baslangic->next->talep_edilen_inis_saati < talep_edilen_inis_saati) 
		{
			baslangic = baslangic->next;
		}
		temp->next = baslangic->next;
		baslangic->next = temp;
	}
}
//olusan linked list ba?lar?n? koparmadan bubble sortla belirlenen iki d???m?n yer de?i?tirmesine yarar.
void swap(Node *a,Node *b)
{
    Node* temp = (Node*)malloc(sizeof(Node)); //bilgiler de?i?tirilirken kaybolmamas? i?in temp olusturuldu.
	temp->ucak_id = a->ucak_id;
	temp->oncelik_id = a->oncelik_id;
	temp->talep_edilen_inis_saati = a->talep_edilen_inis_saati;
	temp->inis_saati=a->inis_saati;
	
	a->ucak_id=b->ucak_id;
	a->oncelik_id=b->oncelik_id;
	a->talep_edilen_inis_saati=b->talep_edilen_inis_saati;
	a->inis_saati=b->inis_saati;
    
	b->ucak_id=temp->ucak_id;
	b->oncelik_id=temp->oncelik_id;
	b->talep_edilen_inis_saati=temp->talep_edilen_inis_saati;
	b->inis_saati=temp->inis_saati;
	
	free(temp);//temp silinir.
}
//inis saatleri esit oldugu surece oncelik idlerine g?re yerinin de?i?ip de?i?meyece?ini belirleme
void bubbleSort(Node **head)
{
    int swapped,saat=0;
    Node *temp;
    Node *ltemp = NULL;
    do
    {
        swapped = 0;
        temp = (*head);
        while(temp->next!=ltemp)
        {
            if (temp->oncelik_id > temp->next->oncelik_id && temp->inis_saati==temp->next->inis_saati)
            { 
                swap(temp, temp->next);
                swapped = 1;
            }
            temp = temp->next;
        }
        ltemp = temp;
    }
    while (swapped);
}
//kalk?s pisti i?in s?ra olusturur. sondan ekler.(s?ral? liste eklenir)
void kalkis_pisti_kullanim_sirasi(int yeni_ucak_id, int yeni_oncelik_id, int yeni_talep_edilen_inis_saati,int yeni_inis_saati )
{	 
	if(kalkisroot==NULL){ /// ilk d???m olu?turulmad?ysa ?nce onu olu?turuyoruz.
        kalkisroot = (Node *)malloc(sizeof(Node));
        kalkisroot->ucak_id = yeni_ucak_id;
        kalkisroot->oncelik_id = yeni_oncelik_id;
        kalkisroot->talep_edilen_inis_saati = yeni_talep_edilen_inis_saati;
        kalkisroot->inis_saati = yeni_talep_edilen_inis_saati;
        kalkisroot->next = NULL;
        kalkisend = kalkisroot; /// Sadece ilk d???m i?in, head = tail
    } else {
        Node *temp = (Node *)malloc(sizeof(Node)); /// Eklenecek d???mler i?in memory allocation
        temp->ucak_id = yeni_ucak_id;
        temp->oncelik_id = yeni_oncelik_id;
        temp->talep_edilen_inis_saati = yeni_talep_edilen_inis_saati;
        temp->inis_saati = yeni_talep_edilen_inis_saati;
        temp->next = NULL;
        kalkisend->next=temp;
        kalkisend = kalkisend->next;
    }
}
//havaliman? kapasite de?eri d?nd?r?r.
int havalimani_kapasitesi(Node **head)
{
	Node *iter=(*head);
	int kapasite=0;
	while(iter!=NULL){
		iter=iter->next;
		kapasite++;
	}
	return kapasite;
}
//inis talebi reddedilen u?aklara bilgi yollan?r.
void uyari(int izinli, int izinsiz)
{
	printf("\n\nUYARI\n");
	printf("Alici: %d\n", izinsiz);
	printf("Acil inis yapmas? gereken %d uca??ndan dolay? Sabiha G?k?en havaliman?na y?nlendiriliyorsunuz.\n ",izinli);
}
//havaliman?nda o saatte inmek isteyen u?ak ?nceli?i en fazla olana izin verilir, kalk?? s?ras?na al?n?r.
Node* inis_izni(Node **head, Node **head2)
{
	Node *iter1=(*head), *iter2=(*head2);
	
	if(iter1->inis_saati!=iter2->inis_saati)//o saatte acil gelen ucak var m? onu kontrol eder.
	{	
		kalkis_pisti_kullanim_sirasi(iter1->ucak_id,iter1->oncelik_id2,iter1->talep_edilen_inis_saati,iter1->inis_saati);//inis izni verilen ucak direkt kalk?? s?ras?na al?n?r.
		output(iter1->ucak_id,iter1->oncelik_id2,iter1->talep_edilen_inis_saati,iter1->inis_saati);
	}
	else if(iter1->oncelik_id>iter2->oncelik_id && iter1->inis_saati==iter2->inis_saati)//ayn? saatte acil gelen ucaklar i?in ?ncelik k?yaslamas? yapar
	{
		uyari(iter2->ucak_id,iter1->ucak_id);//izin vermeyen uca?a uyar? yollar.
		kalkis_pisti_kullanim_sirasi(iter2->ucak_id,iter2->oncelik_id2,iter2->talep_edilen_inis_saati,iter2->inis_saati);//inis izni verilen ucak direkt kalk?? s?ras?na al?n?r.
		output(iter2->ucak_id,iter2->oncelik_id2,iter2->talep_edilen_inis_saati,iter2->inis_saati);
		
		Node* temp = *head2;//ayn? saatte inmek isteyen acil listesinden silinir
		(*head2)=(*head2)->next;
		free(temp);
	}
	else if(iter1->oncelik_id<=iter2->oncelik_id && iter1->inis_saati == iter2->inis_saati)//ayn? saatte acil gelen ucaklar i?in ?ncelik k?yaslamas? yapar
	{
		uyari(iter1->ucak_id,iter2->ucak_id);//izin vermeyen uca?a uyar? yollar.
		kalkis_pisti_kullanim_sirasi(iter1->ucak_id,iter1->oncelik_id2,iter1->talep_edilen_inis_saati,iter1->inis_saati);//inis izni verilen ucak direkt kalk?? s?ras?na al?n?r.
		output(iter1->ucak_id,iter1->oncelik_id2,iter1->talep_edilen_inis_saati,iter1->inis_saati);
	
		Node* temp = *head2;//ayn? saatte inmek isteyen acil listesinden silinir
		(*head2)=(*head2)->next;
		free(temp);
	}

	Node* temp2 = *head;//inis s?ras?ndan ??kar?l?r.
	(*head)=(*head)->next;
	free(temp2);
}
//talep ettikleri saatte inemeyen u?aklar?n saatleri ertelenir, e?er 3 ten fazla ertelenme durumu varsa ?nceli?i en ?st olan 0'a (s?f?ra) al?n?r.
void inis_saati_duzenle(Node **head, int saat)
{
	Node *iter=(*head);
	while(iter->inis_saati==saat){//istenilen saatte inemeyen u?aklar?n saati ertelenir
		iter->inis_saati++;
		if(iter->inis_saati-iter->talep_edilen_inis_saati>=3){//gecikme s?resi 3ten fazlaysa ?ncelik 0 yap?l?r.
			iter->oncelik_id=0;
		}
		iter=iter->next;
	}
}
void print_kalkisroot()
{
	Node* iter=kalkisroot;//inis s?ras?ndan ??kar?l?r.
	while(iter!=NULL){
		printf("|%3d|%3d|%3d|%3d|%3d|\n",iter->talep_edilen_inis_saati,iter->inis_saati,iter->inis_saati+1,iter->ucak_id,iter->oncelik_id);
		iter=iter->next;
	}	
}
void print_inisroot(Node **head)
{
	Node* iter=(*head);	
	while(iter!=NULL){
		printf("|%3d|%3d|%3d|%3d|%3d|\n",iter->talep_edilen_inis_saati,iter->inis_saati,iter->inis_saati+1,iter->ucak_id,iter->oncelik_id2);
		iter=iter->next;
	}
}

void output(int ucak_id,int oncelik_id,int talep,int inis){
	
	int gecikme=inis-talep;
	int kalkis=inis+1;
	
	FILE *outF=fopen("output.txt","r+");
	if(outF==NULL){
		printf("Dosya acilamadi...");
	}
	else{
		fseek(outF,0,SEEK_END);
		fprintf(outF,"|%3d|%3d|%3d|%3d|%3d|%3d|\n",ucak_id,oncelik_id,talep,inis,gecikme,kalkis);
		fclose(outF);
	}
}

int main()
{	
	FILE *fp=fopen("input.txt","r"); //input.txt ve output.txt  pointer tan?mland?
	if(fp==NULL){//dosya a??lamad?ysa programdan ??k?l?r
		printf("Dosya acilamadi...");
	}
	else
	{
		int oncelik_id, ucak_id, talep_edilen_inis_saati;//input dosyas?ndan al?nacak bilgiler tan?mland?
		
		fscanf(fp,"%d%d%d",&oncelik_id,&ucak_id,&talep_edilen_inis_saati);//ilk bilgiler al?n?r.		
		Node *root=newNode(ucak_id,talep_edilen_inis_saati,oncelik_id);//inis kuyrugu i?in ilk eleman bilgileri girilir.(kapasite dolmadan)
		
		Node *root2=NULL;//kapasite dolduktan sonra gelen u?aklar?n listesi i?in
		while(fscanf(fp,"%d%d%d",&oncelik_id,&ucak_id,&talep_edilen_inis_saati)!=EOF){//input.txt dosyas? bitene kadar bilgiler al?n?p kuyruga eklenir.
			
			if(havalimani_kapasitesi(&root)<24){//havaliman? kapasitesi kadar ucak bilgisi inis s?ras?na eklenir
				push(&root,ucak_id,talep_edilen_inis_saati,oncelik_id);	
			}
			else if(havalimani_kapasitesi(&root)==24 && havalimani_kapasitesi(&root2)==0){//havaliman?na sonradan gelen ucaklar ayr? bir listeye al?n?r.
				root2=newNode(ucak_id,talep_edilen_inis_saati,oncelik_id);//sonradan gelen ilk u?ak
			}
			else{
				push(&root2,ucak_id,talep_edilen_inis_saati,oncelik_id);//sonradan gelen ucaklar s?ral? ?ekilde listelenir.
			}	
		}				
		bubbleSort(&root);//talep edilen inis saati e?it olanlar aras?nda oncelik s?ralamas? yap?l?r.
		
		Node *iter2=root2;
		int saat=0;
		while(root!=NULL){
			printf("\n\nsaat %d\n\n",saat);
			printf("\n\ninisroot\n\n");
			print_inisroot(&root);
			printf("\n\nInis izni isteyen ucaklar:\n");
			iter2=root2;
			if(iter2->talep_edilen_inis_saati==saat){
				printf("|%3d|%3d|%3d|%3d|%3d|\n",iter2->talep_edilen_inis_saati,iter2->inis_saati,iter2->inis_saati+1,iter2->ucak_id,iter2->oncelik_id);
			}
			else if(iter2->talep_edilen_inis_saati!=saat){
				printf("---\n\n");
			}
			inis_izni(&root,&root2);
			saat++;
			inis_saati_duzenle(&root,saat);
			bubbleSort(&root);
			printf("\n\nkalkisroot\n\n");
			print_kalkisroot();			
		}	
	}
	fclose(fp);//fp dosyas? kapat?l?r.
	return 0;
}


