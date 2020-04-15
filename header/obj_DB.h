#define NAME_SIZE 10
#define MEMO_SIZE 90
#define READ_SIZE  512 // search_record()에서 읽을 만큼의 버퍼 크기 지정

typedef struct _person {
  char name[NAME_SIZE];
  char memo[MEMO_SIZE];
} PERSON;