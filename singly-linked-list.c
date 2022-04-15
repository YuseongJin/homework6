/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>//standard input/output library, 표준 입출력 라이브러리
#include<stdlib.h>//c표준 유틸리티 함수들을 모아 놓은 헤더파일

/* 필요한 헤더파일 추가 */

typedef struct Node {//구조체 선언
	int key;//int 형 변수 key 멤버 선언
	struct Node* link; 
} listNode;//구조체 별칭

typedef struct Head {//구조체 선언
	struct Node* first;
}headNode;//구조체 별칭


/* 함수 리스트 */
//함수 원형 선언
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()//메인함수
{
	char command;//char형 변수 선언, 명령어
	int key;//int형 변수 선언, 키보드
	headNode* headnode=NULL;//headnode의 값을 NULL로 초기화

	printf("[----- [Yuseong Jin] [2018038022] -----]");//이름, 학번 출력


	do{//do-while문을 통하여 반복 출력
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");
		//메뉴 출력

		printf("Command = ");
		scanf(" %c", &command);//명령어 입력받기

		switch(command) {//스위치문
		//소문자와 대문자 모두 입력 받기
		case 'z': case 'Z'://z키를 입력 받았을 때
			headnode = initialize(headnode);
			break;//스위치문 끝
		case 'p': case 'P'://p키를 입력 받았을 때
			printList(headnode);//printList 함수 실행
			break;//스위치문 끝
		case 'i': case 'I'://i키를 입력 받았을 때
			printf("Your Key = ");
			scanf("%d", &key);
			//키 값 입력받기
			insertNode(headnode, key);//insertNode 함수 실행
			break;//스위치문 끝
		case 'd': case 'D'://d키를 입력 받았을 때
			printf("Your Key = ");
			scanf("%d", &key);
			//키 값 입력받기
			deleteNode(headnode, key);//deleteNode 함수 실행
			break;//스위치문 끝
		case 'n': case 'N'://n키를 입력 받았을 때
			printf("Your Key = ");
			scanf("%d", &key);
			//키 값 입력받기
			insertLast(headnode, key);//insertLast함수 실행
			break;//스위치문 끝
		case 'e': case 'E'://e키를 입력 받았을 때
			deleteLast(headnode);//deleteLast 함수 실행
			break;//스위치문 끝
		case 'f': case 'F'://f키를 입력 받았을 때
			printf("Your Key = ");
			scanf("%d", &key);
			//키 값 입력받기
			insertFirst(headnode, key);//insertFirst 함수 실행
			break;//스위치문 끝
		case 't': case 'T'://t키를 입력 받았을 때
			deleteFirst(headnode);//deleteFirst 함수 실행
			break;//스위치문 끝
		case 'r': case 'R'://r키를 입력 받았을 때
			invertList(headnode);//invertList 함수 실행
			break;//스위치문 끝
		case 'q': case 'Q'://q키를 입력 받았을 때
			freeList(headnode);//freeList 함수 실행
			break;//스위치문 끝
		default://이 외의 입력을 받았을 때 
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");//경고문 출력
			break;//스위치문 끝
		}

	}while(command != 'q' && command != 'Q');//q키를 사용하기 전까지 계속 반복

	return 1;//종료
}

headNode* initialize(headNode* h) {//초기화 함수

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;//첫번째 노드를 NULL로 초기화
	return temp;//temp 값 반환
}

int freeList(headNode* h){//리스트 할당해제 함수
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;//p에 h의 첫번째 값 대입

	listNode* prev = NULL;//prev를 NULL로 초기화
	while(p != NULL) {//p가 NULL이랑 다르다면
		prev = p;//prev에 p값 대입
		p = p->link;//p에 link값 대입
		free(prev);//prev 할당 해제
	}
	free(h);//malloc함수로 동적한 메모리를 해제
	return 0;//종료
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {//노드 삽입 함수

	listNode* node = (listNode*)malloc(sizeof(listNode));
	/* listNode에 대한 메모리를 할당하여 리턴 */
	node->key = key;//key값 대입
	node->link = NULL;//link값을 NULL로 초기화

	if (h->first == NULL)//첫번째 값이 NULL이라면
	{
		h->first = node;//첫번째 값에 노드값 대입
		return 0;//종료
	}

	listNode* n = h->first;
	listNode* trail = h->first;

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {
		if(n->key >= key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {
				h->first = node;
				node->link = n;
			} else { /* 중간이거나 마지막인 경우 */
				node->link = n;
				trail->link = node;
			}
			return 0;//종료
		}

		trail = n;//trail에 n값 대입
		n = n->link;//n에 n포인터 link값 대입
	}

	/* 마지막 노드까지 찾지 못한 경우 , 마지막에 삽입 */
	trail->link = node;
	return 0;//종료
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {//last에 node 추가 함수

	listNode* node = (listNode*)malloc(sizeof(listNode));//구조체 포인트 선언, 동적메모리할당
	node->key = key;//node포인터 key에 key값 대입
	node->link = NULL; //node포인터link를 NULL로 초기화

	if (h->first == NULL)//h포인터 first가 NULL이라면
	{
		h->first = node;//h포인터 first에 node값 대입
		return 0;//종료
	}

	listNode* n = h->first;//listnode 포인트 변수 n 선언후 h포인터 first값 대입
	while(n->link != NULL) {//n포인터link값이 NULL값이 아니라면
		n = n->link;//n포인터 link값을 n에 대입
	}
	n->link = node;//n포인터link에 node 대입
	return 0;//종료
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {//list 처음에 노드 추가 함수

	listNode* node = (listNode*)malloc(sizeof(listNode));
	//구조체 포인트 선언, 동적메모리할당
	node->key = key;//key값을 node 포인터 key에 대입

	node->link = h->first;
	//h포인터 first값을 node포인터의 link값 대입
	h->first = node;
	//node값을 h포인터 first값 대입

	return 0;//종료
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {//노드 삭제 함수

	if (h->first == NULL)//머리노드가 가르키는 값이 NULL일때
	{
		printf("nothing to delete.\n");//삭제 할 것이 없음을 알림
		return 0;//종료
	}

	listNode* n = h->first;//listnode n 선언후 머리노드가 가르키는 값 삽입
	listNode* trail = NULL;//listnode trail 선언후 NULL로 초기화

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {
		if(n->key == key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {
				h->first = n->link;
			} else { /* 중간인 경우거나 마지막인 경우 */
				trail->link = n->link;
			}
			free(n);//malloc함수로 동적한 메모리를 해제
			return 0;//종료
		}

		trail = n;//trail에 n값 대입
		n = n->link;//n에 n포인터 link값 대입
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	//못 찾았음을 알림 
	return 0;//종료

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {//마지막노드 삭제 함수

	if (h->first == NULL)//머리노드가 가르키는 값이 NULL일때
	{
		printf("nothing to delete.\n");//삭제할 수 없음을 알림
		return 0;//종료
	}

	listNode* n = h->first;//listnode n 선언후 머리노드가 가르키는 값 삽입
	listNode* trail = NULL;//listnode trail 선언후 NULL로 초기화

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->link == NULL) {
		h->first = NULL;
		free(n);//malloc함수로 동적한 메모리를 해제
		return 0;//종료
	}

	/* 마지막 노드까지 이동 */
	while(n->link != NULL) {
		trail = n;//trail에 n값 대입
		n = n->link;//n포인터 link에 n대입
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->link = NULL;
	free(n);//malloc함수로 동적한 메모리를 해제

	return 0;//종료
}
/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {//첫번째 노드 삭제 함수

	if (h->first == NULL)//머리노드의 첫번쨰 가르키는 값이 NULL일 경우
	{
		printf("nothing to delete.\n");//삭제 할 값이 없음을 알림
		return 0;//종료
	}
	listNode* n = h->first;//listnode 포인트 변수n선언후 머리노드의 첫번쨰 가르키는 값 대입

	h->first = n->link;//머리노드의 첫번쨰 가르키는 값에 n포인터 link값 대입
	free(n);//malloc함수로 동적한 메모리를 해제

	return 0;//종료
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {//리스트 역순 출력 함수


	if(h->first == NULL) {//머리노드의 첫번쨰 가르키는 값이 NULL일 경우
		printf("nothing to invert...\n");//순서를 바꿀 값이 없음을 알림
		return 0;//종료
	}
	listNode *n = h->first;//리스트 노드n에 머리노드의 첫번쨰 가르키는 값 대입
	listNode *trail = NULL;
	listNode *middle = NULL;
	//trail, middle 리스트 노드 생성 후 NULL로 초기화

	while(n != NULL){//n이 NULL이 아니라면
		trail = middle;//trail에 middle 값 대입
		middle = n;//middle에 n값 대입
		n = n->link;//n에 n포인터link값 대입
		middle->link = trail;//middle포인터 link에 trail값 대입
	}

	h->first = middle;//h포인터 first에 middle값 대입

	return 0;//종료
}


void printList(headNode* h) {//리스트 출력 함수
	int i = 0;//int형 변수 i 선언후 0으로 초기화
	listNode* p;//구조체 포인트 p 선언

	printf("\n---PRINT\n");

	if(h == NULL) {//headnode가 NULL일때
		printf("Nothing to print....\n");//출력할 수 없음을 출력
		return;//종료
	}

	p = h->first;//p를 머리노드의 첫번째 값으로 초기화
//
	while(p != NULL) {//p가 NULL이 아니라면
		printf("[ [%d]=%d ] ", i, p->key);//i, 입력한 키 값 출력
		p = p->link;
		//다음 노드를 가르킴
		i++;//i값 증감
	}

	printf("  items = %d\n", i);//입력한 노드 수 출력
}

