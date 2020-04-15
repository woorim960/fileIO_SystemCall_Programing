/*
===========================================================================
Name        : main.c
Author      : Park Woo Rim
Version     : v1.0
Copyright   : Your copyright notice
Description : 수정 내역 요약

구분    날짜        내용
----   ---------- -----------------------------------------------------------
생성    2020/04/13 파일을 통한 데이터 입력 및 검색 프로그램 구현

코딩구분 설명
생성 : 처음으로 프로그램 개발했을 때
추가 : 기존의 프로그램에서 알고리즘(로직)을 추가했을 때, 함수 추가
수정 : 기존의 프로그램의 알고리즘(로직)을 수정했을 때
삭제 : 기존의 프로그램 알고리즘 일부를 삭제했을 때
===========================================================================
*/

// 헤더
#include <stdio.h>
#include <stdlib.h>

// 개발자 정의 헤더
#include "header/write_record.h"
#include "header/search_record.h"

// scanf 보안 경고로 인한 컴파일 에러 방지
#define _CRT_SECURE_NO_WARNINGS

// 사용자 정의 함수 선언
void empty_buffer();

// main => 전체 시스템의 동작 실행
int main(int const argc, char const *argv[]) {

  // 변수 선언
  short selector; // 효율적인 메모리 관리를 위한 short 타입(2바이트 정수형) 선언

  // argument count 확인 => 2개 아니면 에러 출력 후 프로세스 종료
  if (argc != 2) {
    puts("데이터가 입력될 파일을 입력하십시오.");
    fprintf(stderr, "사용법 : %s '파일 이름'\n", argv[0]);
    exit(1); // 강제 종료
  }

  // 개발자 정의 함수 실행 => 별도의 c 파일로 모듈화하였음.
  while (1) {
    puts("=================================");
    puts(":: 무엇을 수행하시겠습니까? ::");
    puts("레코드 쓰기 : 1\n레코드 검색 : 2\n종료 : 그 외");
    puts("=================================");
    printf(">> ");

    // 선택자 입력 받기
    if(scanf("%hd", &selector) == 0) {
      // 문자를 입력한 경우
      puts("정수를 입력해주세요.");
    } else {
      // 숫자를 입력한 경우
      // scanf로 인해 입력 버퍼에 개행 문자 "\n"가 남아있게 된다.
      empty_buffer(); // 추가 입력을 받기 위해 입력 버퍼를 비워주는 함수 실행.
    }

    // 입력된 값에 따라 기능 수행
    switch(selector) {
      case 1:
        write_record(argv);     // 레코드 쓰기 기능
        break;
      case 2:
        search_record(argv);    // 레코드 검색 기능
        break;
      default:
        puts("프로그램을 종료합니다.");
        exit(0); // 정상 종료
    }
  }

  // 프로그램 정상 종료
  exit(0);
}

// 입력 버퍼 비우는 함수 정의
void empty_buffer(){
  while (getchar() != '\n');
}