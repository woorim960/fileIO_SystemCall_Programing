// write_record.c
// header : write_record.h

// 헤더
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// 구조체 DB
#include "header/obj_DB.h"

// 이름과 메모 상태를 나타낼 상수 정의
#define NAME_STATUS 1
#define MEMO_STATUS 2

// 사용자 정의 함수 선언
int write_in_file();

// write_record.c의 메인 함수
void write_record(char const *argv[]) {

  // PERSON 객체를 user로 사용함.
  PERSON user;

  // 변수 정의
  int write_fd, is_exit; // 파일 디스크립터와 exit을 입력했는지의 여부를 판단할 변수 선언
  char *separator[2] = { // 파일에 데이터 저장시에 ID와 MEMO를 구분짓기 위한 구분자 정의
    "====USER NAME >>>>>> ", 
    "====MEMO : " 
  };

  // input data를 argv[1]에 쓰기 위해 파일 생성 => 에러시 내부 구문 실행
  if ( (write_fd = open(argv[1], O_WRONLY|O_CREAT|O_APPEND, 0644)) == -1 ) {
    puts("open() Error!!");
    perror(argv[1]);
    exit(1); // 강제 종료
  }

  // 사용자 이름 입력 함수 실행
  is_exit = write_in_file(NAME_STATUS, write_fd, user.name, NAME_SIZE, separator[0]);

  // write_in_file()의 반환 값이 1이면 무한 반복된다. => "exit" 입력시 반복문을 종료함.
  while(is_exit) {

    // 사용자 MEMO 입력 함수 실행
    is_exit = write_in_file(MEMO_STATUS, write_fd, user.memo, MEMO_SIZE, separator[1]);
  }

  // write_record 종료
  puts("레코드 쓰기를 종료합니다.");
  return;
}

// 파일에 쓰기 함수 정의 => 파라미터( 상태 상수, 파일디스크립터, write 데이터, 입력받을 데이터 크기 )
int write_in_file(int status, int write_fd, char *data, int MAX_SIZE, char *separator){

  // 상태에 따른 안내문구 출력
  switch(status) {
    case 1:
      puts(":: 사용자 이름을 입력해주세요(종료:'exit') ::");
      break;
    case 2:
      puts(":: 메모를 남겨주세요(종료:'exit') ::");
      break;
    default: 
      puts("STATUS Error!!");
      break;
  }

  // 사용자 입력 받기 => 에러시 내부 구문 실행
  if (fgets(data, MAX_SIZE, stdin) == NULL) {
    puts("fgets Error - write_record.c");
    exit(3); // 강제 종료
  }

  // 입력 데이터가 "exit"이면 함수 종료 후 0반환 => 여기서 반환된 값을 while에서 사용할 것임.
  if (!strncmp(data, "exit", 4)) {
    return 0;
  }
  
  // 구분자를 파일에 쓰기 => write() 에러시 내부 구문 실행
  if ( write(write_fd, separator, strlen(separator)) == -1 ) {
    puts("write() Error!!");
    exit(2);
  }

  // 입력 데이터를 파일에 쓰기 => write() 에러시 내부 구문 실행
  if ( write(write_fd, data, strlen(data)) == -1 ) {
    puts("write() Error!!");
    exit(4);
  }

  return 1;
}