#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct st_book{
	int category; // 분류코드 (0:전공, 1:교양, 2:취미)
	char title[100];  // 도서명
	char pub[100]; // 출판사
	int year;  // 출간년도
	int status; // 상태코드 (0:보관, 1:대여, 2:분실)
	char borrower[100]; // 대여자명
};
char CATEGORY[3][20] = {"전공","교양","취미"};
char STATUS[3][20] = {"보관","대여","분실"};


int load_books(struct st_book* list[]);		// 도서정보 읽어오기
void view_library(struct st_book* list[], int n);	// 현재 서재 정보 출력하기
void add_book(struct st_book* list[], int* n);		// 도서 추가하기
void lost_book(struct st_book* list[], int n);	// 도서 분실 처리하기
void find_books(struct st_book* list[], int n);	// 도서 검색
void update_book(struct st_book* list[], int n);	// 도서정보 수정하기
void save_report(struct st_book* list[], int n);	// 서재 정보 보고서 만들기

int main(){
	struct st_book* my_library[50]; 	// 최대 50개의 객실을 관리할 수 있는 구조체 포인터 배열
	int count;	// 현재 등록된 카드 수
	int menu;	// 메뉴번호
	printf("\n서재 정보입니다.\n");

	count = load_books(my_library);	// 도서정보 읽어오기
	while(1)
	{
		// 메뉴 출력
		printf("\n[1]목록 [2]추가 [3]분실 [4]검색 [5]수정 [6]저장 [0]종료 >> ");
		scanf("%d",&menu);	// 메뉴를 읽음

		if(menu==1){
			view_library(my_library, count);	// 현재 서재 정보 출력하기
		}
		else if(menu==2){
			add_book(my_library, &count);	// 도서 추가하기
		}
		else if(menu==3){
			lost_book(my_library, count); // 도서 분실 처리하기
		}
		else if(menu==4){
			find_books(my_library, count);	// 도서 검색
		}
		else if(menu==5){
			update_book(my_library, count);	// 도서정보 수정하기
		}
		else if(menu==6){
			save_report(my_library, count);	// 서재 정보 보고서 만들기
		}
		else {
			break;
		}
	}
}

int load_books(struct st_book* list[]){
	FILE *file;
	int n=0;
	char bookname[100];
	char line[100];
	file = fopen("books.txt","r");
	while(!feof(file)){
		if(!fgets(bookname, 100, file)) break;
		list[n]=(struct st_book*)malloc(sizeof(struct st_book));
		bookname[strlen(bookname)-1]='\0';
		strcpy(list[n]->title, bookname);
		fgets(line, 100, file);
		sscanf(line,"%d %s %d",&(list[n]->category),list[n]->pub,&(list[n]->year));
		list[n]->status=0;
		n++;
	}
	fclose(file);
	printf("%d개의 도서 정보를 읽었습니다.\n",n);
	return n;
}

void view_library(struct st_book* list[], int n){
	int i;
	printf("\n서재 정보입니다. (총 %d권)\n", n);
	printf("번호 / 분류 / 도서명 / 출판사 / 출간년도 / 상태\n");
	
	for(i=0; i<n; i++){
		printf("%2d / ", i+1);
		printf("%s / ", CATEGORY[list[i]->category]);
		printf("%s / ", list[i]->title);
		printf("%s / ", list[i]->pub);
		printf("%d년 / ", list[i]->year);
		printf("%s ", STATUS[list[i]->status]);
		if(list[i]->status==1) printf("(%s)", list[i]->borrower);
		printf("\n");
	}
}

////////// 여기부터 코드 작성 ////////////////////////

void add_book(struct st_book* list[], int* n){
 /*
  도서 정보를 입력받는다.
    "도서명 > "
    "출판사 > "
    "출간년도 > "
    "분류코드 (0:전공, 1:교양, 2:취미) > "
    각각을 입력받아서 list에 해당 member에 넣는다.
    도서 상태는 0으로 초기화
    *n은 1 증가
*/
  char blank[10];
  printf("도서명 > ");
  fgets(blank, 10, stdin);
  fgets(list[*n]->title, 100, stdin);
  list[*n]->title[strlen(list[*n]->title)-1]='\0';
  printf("출판사 > ");
  fgets(list[*n]->pub, 100, stdin);
  list[*n]->pub[strlen(list[*n]->pub)-1]='\0';
  printf("출간년도 > ");
  scanf("%d", &list[*n]->year);
  printf("분류코드 (0:전공, 1:교양, 2:취미) > ");
  scanf("%d", &list[*n]->category);
  list[*n]->status=0;
  (*n)++;
}

void lost_book(struct st_book* list[], int n){
 /*
  "분실한 도서 번호는? > "
  도서 번호 입력받아서 분실한 도서(list[num-1]) 정보 출력
  "이 도서를 분실처리하겠습니까? (1:Yes, 0:No) > 
  check에다가 넣기
  만약에 check==1이면 
    list[num-1]->status를 2로 변경
    printf("분실처리하였습니다.\n")
*/
  int num, check;
  printf("분실한 도서 번호는? > ");
  scanf("%d", &num);
  printf("%s / ", CATEGORY[list[num-1]->category]);
	printf("%s / ", list[num-1]->title);
	printf("%s / ", list[num-1]->pub);
	printf("%d년 / ", list[num-1]->year);
	printf("%s ", STATUS[list[num-1]->status]);
	if(list[num-1]->status==1) printf("(%s)", list[num-1]->borrower);
	printf("\n");
  printf("이 도서를 분실처리하겠습니까? (1:Yes, 0:No) > ");
  scanf("%d", &check);
  if (check==1) {
    list[num-1]->status=2;
    printf("분실처리하였습니다.\n");
  }
}

void find_books(struct st_book * list[], int n){
/*
  변수 선언
    char blank[10]-> 빈칸 넣을 배열
    char str[100]->문자 입력받을 변수
    int i->반복문 변수
    int which->도서검색 방법 수력받을 변수
    int count->검색된 권 수
  "도서검색 방법은? (1:도서명 2:출판사 3:출간년도 4:카테고리 5:상태 ) > "
  scanf(which)에 입력받기
  만약에 which가 
  1) 1이라면..
    "도서명 일부를 입력하세요. > 
    fgets해서 str에 넣기
    printf("번호 / 분류 / 도서명 / 출판사 / 출간년도 / 상태\n")
    반복문 사용
      만약 strstr(list[i]->title, str)이면
        list[i]에 해당하는 도서 정보 출력
        count++
    printf("%d권의 도서가 검색되었습니다.\n", count)
  2) 2라면..
    printf("출판사명 일부를 입력하세요. > ")
    fgets해서 str에 넣기
    번호/분류...출력
    반복문 사용
      만약 strstr(list[i]->pub, str)이면
        list[i]에 해당하는 도서 정보 출력
        count++
    printf("%d권의 도서가 검색되었습니다.\n", count)
  3) 3이라면..
    출간년도를 입력받을 변수 int year 선언
    printf("출간년도를 입력하세요. > ");
    scanf(year);
    위와 같이 번호/분류/...출력하고
    반복문 사용
      만약 list[i]->year가 year랑 같으면
        list[i]에 해당하는 도서 정보 출력
        count++
    printf(%d권의 도서가 검색되었습니다.)
  4) 4라면..
    분류코드를 입력받을 변수 int code 선언
    printf("분류코드 (0:전공, 1:교양, 2:취미)를 입력하세요. > ")
    scanf해서 code에 넣기
    번호/분류/...출력
    반복문 사용
      만약 list[i]->category가 code와 일치하면
        list[i]에 해당하는 도서 정보 출력
        count++
    printf(%d권의 도서가 검색되었습니다.)
  5) 5라면..
    상태코드를 입력받을 수 있는 변수 int code 선언
    printf("상태코드 (0:보관, 1:대여, 2:분실)를 입력하세요. > ")
    scanf해서 code에 저장
    4에서 했던 방식이랑 똑같음. (list[i]->status)
*/
  int which;
  char blank[10];
  char str[100];
  int i, count=0;
  printf("도서검색 방법은? (1:도서명 2:출판사 3:출간년도 4:카테고리 5:상태 ) > ");
  scanf("%d", &which);
  if (which==1) {
    //도서명
    printf("도서명 일부를 입력하세요. > ");
    fgets(blank, 10, stdin);
    fgets(str, 100, stdin);
    str[strlen(str)-1]='\0';
    printf("번호 / 분류 / 도서명 / 출판사 / 출간년도 / 상태\n");
    for (i=0; i<n; i++) {
      if (strstr(list[i]->title, str)) {
        printf("%2d / ", i+1);
		    printf("%s / ", CATEGORY[list[i]->category]);
		    printf("%s / ", list[i]->title);
        printf("%s / ", list[i]->pub);
        printf("%d년 / ", list[i]->year);
        printf("%s ", STATUS[list[i]->status]);
        if(list[i]->status==1) printf("(%s)", list[i]->borrower);
        printf("\n");
        count++;
      }
    }
    printf("%d권의 도서가 검색되었습니다.\n", count);
  }
  else if (which==2) {
    //출판사
    printf("출판사명 일부를 입력하세요. > ");
    fgets(blank, 10, stdin);
    fgets(str, 100, stdin);
    str[strlen(str)-1]='\0';
    printf("번호 / 분류 / 도서명 / 출판사 / 출간년도 / 상태\n");
    for (i=0; i<n; i++) {
      if (strstr(list[i]->pub, str)) {
        printf("%2d / ", i+1);
		    printf("%s / ", CATEGORY[list[i]->category]);
		    printf("%s / ", list[i]->title);
        printf("%s / ", list[i]->pub);
        printf("%d년 / ", list[i]->year);
        printf("%s ", STATUS[list[i]->status]);
        if(list[i]->status==1) printf("(%s)", list[i]->borrower);
        printf("\n");
        count++;
      }
    }
    printf("%d권의 도서가 검색되었습니다.\n", count);
  }
  else if (which==3) {
    //출간년도
    int year;
    printf("출간년도를 입력하세요. > ");
    scanf("%d", &year);
    printf("번호 / 분류 / 도서명 / 출판사 / 출간년도 / 상태\n");
    for (i=0; i<n; i++) {
      if (list[i]->year==year) {
        printf("%2d / ", i+1);
		    printf("%s / ", CATEGORY[list[i]->category]);
		    printf("%s / ", list[i]->title);
        printf("%s / ", list[i]->pub);
        printf("%d년 / ", list[i]->year);
        printf("%s ", STATUS[list[i]->status]);
        if(list[i]->status==1) printf("(%s)", list[i]->borrower);
        printf("\n");
        count++;
      }
    }
    printf("%d권의 도서가 검색되었습니다.\n", count);
  }
  else if (which==4) {
    //카테고리
    int code;
    printf("분류코드 (0:전공, 1:교양, 2:취미)를 입력하세요. > ");
    scanf("%d", &code);
    printf("번호 / 분류 / 도서명 / 출판사 / 출간년도 / 상태\n");
    for (i=0; i<n; i++) {
      if (list[i]->category==code) {
        printf("%2d / ", i+1);
		    printf("%s / ", CATEGORY[list[i]->category]);
		    printf("%s / ", list[i]->title);
        printf("%s / ", list[i]->pub);
        printf("%d년 / ", list[i]->year);
        printf("%s ", STATUS[list[i]->status]);
        if(list[i]->status==1) printf("(%s)", list[i]->borrower);
        printf("\n");
        count++;
      }
    }
    printf("%d권의 도서가 검색되었습니다.\n", count);
  }
  else if (which==5) {
    //상태
    int code;
    printf("상태코드 (0:보관, 1:대여, 2:분실)를 입력하세요. > ");
    scanf("%d", &code);
    printf("번호 / 분류 / 도서명 / 출판사 / 출간년도 / 상태\n");
    for (i=0; i<n; i++) {
      if (list[i]->status==code) {
        printf("%2d / ", i+1);
		    printf("%s / ", CATEGORY[list[i]->category]);
		    printf("%s / ", list[i]->title);
        printf("%s / ", list[i]->pub);
        printf("%d년 / ", list[i]->year);
        printf("%s ", STATUS[list[i]->status]);
        if(list[i]->status==1) printf("(%s)", list[i]->borrower);
        printf("\n");
        count++;
      }
    }
    printf("%d권의 도서가 검색되었습니다.\n", count);
  }
}

void update_book(struct st_book* list[], int n){
  /*
  printf("정보를 수정하려는 도서 번호는 > ")
  scanf(num)에다가 받아서
  list[num-1]에 저장돼있는 도서정보 출력
  printf("이 도서에 대해 원하는 작업은? (1:도서정보 수정, 2:대여 처리, 3:반납처리 ) > ");
  어떤 처리할 건지 which에다가 입력받음
  만약에 which==1이면
    printf("도서 정보를 입력하세요.\n");
    add_book함수처럼. list[num-1]수정
  만약에 which==2이면
    만약에 list[num-1]도서가 이미 대여되어있거나 분실처리 되어있으면
      대여할 수 없는 도서입니다. 출력하고 return
    printf("대여자 이름은? ");
    scanf(name)에 넣기
    list[num-1]->borrower랑 list[num-1]->status 수정
    도서 대여처리하였습니다. 출력
  만약에 which==3이면
    list[num-1]의 status를 0으로 바꾸고
    도서 반납처리하였습니다. 출력
  */
  int num, which;
  printf("정보를 수정하려는 도서 번호 > ");
  scanf("%d", &num);
  printf("%s / ", CATEGORY[list[num-1]->category]);
	printf("%s / ", list[num-1]->title);
  printf("%s / ", list[num-1]->pub);
  printf("%d년 / ", list[num-1]->year);
  printf("%s ", STATUS[list[num-1]->status]);
  if(list[num-1]->status==1) printf("(%s)", list[num-1]->borrower);
  printf("\n");
  printf("이 도서에 대해 원하는 작업은? (1:도서정보 수정, 2:대여 처리, 3:반납처리 ) > ");
  scanf("%d", &which);
  if (which==1) {
    printf("도서 정보를 입력하세요.\n");
    char blank[10];
    printf("도서명 > ");
    fgets(blank, 10, stdin);
    fgets(list[num-1]->title, 100, stdin);
    list[num-1]->title[strlen(list[num-1]->title)-1]='\0';
    printf("출판사 > ");
    fgets(list[num-1]->pub, 100, stdin);
    list[num-1]->pub[strlen(list[num-1]->pub)-1]='\0';
    printf("출간년도 > ");
    scanf("%d", &list[num-1]->year);
    printf("분류코드 (0:전공, 1:교양, 2:취미) > ");
    scanf("%d", &list[num-1]->category);
  }
  else if (which==2) {
    if (list[num-1]->status==2|| list[num-1]->status==1) {
      printf("대여할 수 없는 도서입니다.\n");
      return;
    }
    printf("대여자 이름은? ");
    scanf("%s", list[num-1]->borrower);
    list[num-1]->status=1;
    printf("도서 대여처리하였습니다\n");
  }
  else if (which==3) {
    if(list[num-1]->status==0) {
      printf("반납할 수 없는 도서입니다.\n");
      return;
    }
    list[num-1]->status=0;
    printf("도서 반납처리하였습니다.\n");
  }
}

void save_report(struct st_book* list[], int n){
   /*
  n1, n2, n3 -> 전공, 교양, 취미 개수
  s1, s2, s3 -> 보관, 대여, 분실 개수
  FILE *file;
  library.txt 파일 쓰기모드로 열기
  printf("나의 서재 정보 (총 %d권)\n\n", n);
  printf("번호 / 분류 / 도서명 / 출판사 / 출간년도 / 상태\n");
  반복문 사용해서 출력
    책 개수 count
  printf("\n분류별 : 전공 %d권 교양 %d권 취미 %d권\n", n1, n2, n3)
  printf("상태별 : 보관 %d권 대여 %d권 분실 %d권\n", s1, s2, s3)
  */
  int n1=0, n2=0, n3=0; 
  int s1=0, s2=0, s3=0;
  int i;
  FILE *file;
  file = fopen("library.txt", "w");
  fprintf(file, "나의 서재 정보 (총 %d권)\n\n", n);
  fprintf(file, "번호 / 분류 / 도서명 / 출판사 / 출간년도 / 상태\n");
  for (i=0; i<n; i++) {
    fprintf(file, "%2d / ", i+1);
		fprintf(file, "%s / ", CATEGORY[list[i]->category]);
		fprintf(file, "%s / ", list[i]->title);
		fprintf(file, "%s / ", list[i]->pub);
		fprintf(file, "%d년 / ", list[i]->year);
		fprintf(file, "%s ", STATUS[list[i]->status]);
		if(list[i]->status==1) fprintf(file, "(%s)", list[i]->borrower);
		fprintf(file, "\n");

    // 카테고리 
    if (list[i]->category==0) n1++;
    else if (list[i]->category==1) n2++;
    else if (list[i]->category==2) n3++;

    // 상태
    if (list[i]->status==0) s1++;
    else if (list[i]->status==1) s2++;
    else if (list[i]->status==2) s3++;
  }
  fprintf(file, "\n분류별 : 전공 %d권 교양 %d권 취미 %d권\n", n1, n2, n3);
  fprintf(file, "상태별 : 보관 %d권 대여 %d권 분실 %d권\n", s1, s2, s3);
  fclose(file);
  printf("도서정보를 저장하였습니다.\n");
}