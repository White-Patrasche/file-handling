#ifndef _STUDENT_H_
#define _STUDENT_H_

#define RECORD_SIZE \
    85  // id(8) + name(10) + department(12) + address(30) + email(20) +
        // 5*delimiter
#define HEADER_SIZE 8  // #records(4 bytes) + reserved(4 bytes)
#define STRING_LEN 1024
#define TRUE 1
#define FALSE 0
#define ID_LEN 9
#define NAME_LEN 11
#define DEPT_LEN 13
#define ADDR_LEN 31
#define EMAIL_LEN 21

// 필요한 경우 'define'을 추가할 수 있음.

typedef enum FIELD { ID = 0, NAME, DEPT, ADDR, EMAIL } FIELD;

typedef struct _STUDENT {
    char id[9];      // 학번
    char name[11];   // 이름
    char dept[13];   // 학과
    char addr[31];   // 주소
    char email[21];  // 이메일 주소
} STUDENT;

#endif
