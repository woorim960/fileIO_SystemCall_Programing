// search_record.c
// header : search_record.h

// 헤더
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// 구조체 DB
#include "header/obj_DB.h"

// scanf 보안 경고로 인한 컴파일 에러 방지
#define _CRT_SECURE_NO_WARNINGS

// search_record.c의 메인 함수
void search_record(char const *argv[]) {

  // PERSON 객체를 user로 사용함.
  PERSON user;

  // 변수 선언
  int read_fd;                      // 파일 디스크립터
  int line, line_cnt, word_cnt;     // 사용자가 검색할 line 변수와 사용자가 요구한 line에 맞게 출력될 수 있도록 도와줄 cnt 변수들
  char rd_buffer[READ_SIZE];        // 읽은 데이터를 저장할 변수

  // argv[1]의 데이터를 읽기 위한 파일 생성 => 에러시 내부 구문 실행
  if ( (read_fd = open(argv[1], O_RDONLY|O_CREAT, 0644)) == -1 ) {
    puts("open() Error!!");
    perror(argv[1]);
    exit(1); // 강제 종료
  }

  while(1) {

    // 라인 입력 받기
    puts(":: 몇 번째 줄을 검색하시겠습니까?(종료:'-1') ::");
    scanf("%d", &line);

    // 파일 데이터를 읽어서 rd_buffer에 저장해 놓음.
    if( read(read_fd, rd_buffer, READ_SIZE) == -1 ) {
      puts("read() Error");
    }

    // 라인 입력에 따라 word_cnt 변경 => 이후 word_cnt만큼의 커서를 이동하게 된다.
    // 즉, 라인이 3이면 세 번째 줄부터 출력하도록 하기 위함.
    word_cnt = 0;  // 라인 입력에 따라 word_cnt가 변경되어야되므로 반복문이 돌 때마다 0으로 초기화 시켜줌.
    if(line == -1) {
     // 라인이 -1일 경우 break
      break;
    } else if(line >= 2) {
      // 라인이 2 이상일 경우 실행
      line_cnt = 0;  // 라인 입력에 따라 line_cnt가 변경되어야되므로 반복문이 돌 때마다 0으로 초기화 시켜줌.

      // rd_buffer에 저장된 글자들을 하나씩 카운팅 => ex) 라인이 3이면 세 번째 줄부터 출력하도록 하기 위함.
      for(int i=0; i < strlen(rd_buffer); i++) {
        word_cnt += 1; // 글자당 카운팅

        // 사용자가 입력한 line과 line_cnt가 동일해지면 반복문 종료
        if(rd_buffer[i] == '\n') {
          line_cnt += 1; // 한 줄마다 카운팅
          if(line-1 == line_cnt) break; // 첫 번째 줄을 0번째 줄로 출력하기 위해 line에서 1을 차감하였음.
        }
      }
    }

    // Line(cursor) 이동 전 메모리 초기화
    memset(rd_buffer, 0, READ_SIZE);
    // 실제 Line(cursor) 이동
    lseek(read_fd, word_cnt, SEEK_SET);

    // 실제로 화면에 출력할 부분을 읽어서 rd_buffer에 저장
    if( read(read_fd, rd_buffer, READ_SIZE) == -1 ) {
      puts("read() Error");
    }

    // 화면에 출력
    if(strlen(rd_buffer) > 0) {
      // rd_buffer에 값이 있는 경우 => 즉, 검색하여 출력될 데이터가 있을 경우
      printf("검색한 데이터 :\n%s", rd_buffer);
    } else {
      // rd_buffer가 빈 경우 => 즉, 파일에 저장된 데이터 이상의 라인을 입력하여 출력할 데이터의 범위를 넘어선 경우
      puts("검색 데이터가 없습니다.\n저장된 데이터보다 초과된 라인 수를 입력하셨습니다.");
    }
  }

  // search_record 종료
  puts("레코드 검색을 종료합니다.");
  return;
}